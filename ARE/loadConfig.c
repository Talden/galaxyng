#include "are.h"

#define ENUM_ONLY
#include "storage.h"

static void getTechElements(xmlNodePtr tech, gameOpts* go);
static void getPlanets(xmlNodePtr planets, enum ELEMENT_VALS ev, gameOpts* go);
static planetTemplate* instantiatePlanet(xmlNodePtr planet);
static int validatePlanets(FILE* emfFP, gameOpts* go,
						   planetSpec* ps, char* title);

envelope* env;
static char* errorMailFile;
static FILE* emfFP;


xmlXPathObjectPtr getNodeSet(xmlDocPtr doc, xmlChar* xpath) {
	xmlXPathContextPtr context;
	xmlXPathObjectPtr  result;

	context = xmlXPathNewContext(doc);
	if ((result = xmlXPathEvalExpression(xpath, context)) == NULL) {
		xmlXPathFreeContext(context);
		fprintf(stderr, "No result\n");
		return NULL;
	}


	if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		xmlXPathFreeContext(context);
		fprintf(stderr, "No result\n");
		return NULL;
	}

	xmlXPathFreeContext(context);

	return result;
}

xmlDocPtr getDoc(char* filename) {
	xmlDocPtr doc;
	xmlXPathObjectPtr are_node;
	xmlChar* version;
	
	doc = xmlParseFile(filename);

	if (doc == NULL) {
		fprintf(stderr, "Document not successfully parsed.\n");
		return NULL;
	}

	if ((are_node = getNodeSet(doc, (xmlChar*)"/are")) == NULL) {
		fprintf(stderr, "Document is not an ARE config file.\n");
		xmlFreeDoc(doc);
		return NULL;
	}

	version =
		xmlGetProp(are_node->nodesetval->nodeTab[0], (xmlChar*)"version");

	if (version == NULL || strcmp((char*)version, "1.0") != 0) {
		fprintf(stderr, "Incorrect ARE version. Continuing, but some"
				" new features may not be used.\n");
	}

	free(version);
	
	xmlXPathFreeObject(are_node);
	return doc;
}

serverOpts* loadAREConfig(const char* pathname) {
	serverOpts* so = NULL;		/* the options structure */
	char*       configName;		/* where the values are kept */
	xmlDocPtr   doc;			/* root of the xml document */
	char*       attr;			/* attribute pointer */

	errorMailFile = createString("%s/log/are.%d", galaxynghome, getpid());
	if ((emfFP = fopen(errorMailFile, "w")) == NULL) {
		fprintf(stderr,
				"**FATAL** cannot create \"%s\" for error email.\n",
				errorMailFile);
		return NULL;
	}

	configName = createString("%s/.arerc", pathname);

	xmlInitParser();

	if ((doc = getDoc(configName)) == NULL) {
		free(configName);
		return NULL;
	}

	initElementLookup();		/* initialize the lookup structure */
	
	/* get the server info */
	{
		xmlXPathObjectPtr server_node;
		xmlNodePtr nptr;
		enum ELEMENT_VALS ev;
		
		if ((server_node = getNodeSet(doc, (xmlChar*)"/are/server")) == NULL) {
			fprintf(emfFP, "Cannot find server element, exiting.\n");
			return NULL;
		}
		so = (serverOpts*)malloc(sizeof(serverOpts));
		so->from = so->sub_succeed = so->sub_fail = so->replyto = NULL;
		so->cc = NULL;
		so->games = NULL;
		for (nptr = server_node->nodesetval->nodeTab[0]->children;
			 nptr != NULL; nptr = nptr->next) {
			char* content;
			switch(nptr->type) {
				case XML_ELEMENT_NODE:
					ev = lookupElement((char*)nptr->name);
					content = (char*)xmlNodeGetContent(nptr);
					switch(ev) {
						case fromElement:
							so->from = content;
							break;

						case subjectElement:
							attr =
								(char *)xmlGetProp(nptr, (xmlChar*)"type");
							if (noCaseStrcmp(attr, "success") == 0)
								so->sub_succeed = content;
							else
								so->sub_fail = content;
							free(attr);
							break;

						case replytoElement:
							so->replyto = content;
							break;

						case ccElement:
							so->cc = content;
							break;

						case UnknownElement:
							fprintf(emfFP, "Unrecognized element \"%s\", "
									"exiting\n", nptr->name);
							return NULL;
							break;
							
						default: /* no other elements are in the server area */
							break;
					}
					break;

				default:
					break;
			}
		}

		xmlXPathFreeObject(server_node);
	}

	/* get the game info */
	{
		int i;
		xmlChar* name;
		gameOpts* go;
		xmlNodePtr nptr;
		enum ELEMENT_VALS ev;
		xmlXPathObjectPtr game_nodes;
		int errors;
		planetSpec* ps;
		
		if ((game_nodes = getNodeSet(doc, (xmlChar*)"/are/game")) == NULL) {
			fprintf(emfFP, "**INFO** No games defined.\n");
		}

		for (i = 0; i < game_nodes->nodesetval->nodeNr; i++) {
			errors = 0;
			name =
				xmlGetProp(game_nodes->nodesetval->nodeTab[i],
						   (xmlChar*)"name");
			go = allocStruct(gameOpts);
			setName(go, (char*)name);
			go->from = NULL;
			go->sub_succeed = go->sub_fail = go->replyto = go->cc = NULL;
			go->minplayers = go->maxplayers = go->pax_galactica = 0;
			go->galaxy_size = go->nation_spacing = 0.0;
			go->initial_drive = go->initial_weapons = 0.0;
			go->initial_shields = go->initial_cargo = 0.0;
			go->game_options = 0L;
			memset(&go->home, '\0', sizeof(planetSpec));
			memset(&go->dev, '\0', sizeof(planetSpec));
			memset(&go->stuff, '\0', sizeof(planetSpec));
			memset(&go->asteroid, '\0', sizeof(planetSpec));
			go->po = NULL;
			
			for (nptr = game_nodes->nodesetval->nodeTab[i]->children;
				 nptr != NULL; nptr = nptr->next) {
				char* content;
				switch(nptr->type) {
					case XML_ELEMENT_NODE:
						ev = lookupElement((char*)nptr->name);
						content = (char*)xmlNodeGetContent(nptr);
						switch(ev) {
							case fromElement:
								go->from = content;
								break;

							case subjectElement:
								attr =
									(char *)xmlGetProp(nptr, (xmlChar*)"type");
								if (noCaseStrcmp(attr, "success") == 0)
									go->sub_succeed = content;
								else
									go->sub_fail = content;
								free(attr);
								break;

							case replytoElement:
								go->replyto = content;
								break;

							case ccElement:
								go->cc = content;
								break;

							case minplayersElement:
								go->minplayers = atoi(content);
								break;

							case maxplayersElement:
								go->maxplayers = atoi(content);
								break;

							case galaxysizeElement:
								go->galaxy_size = atoi(content);
								break;

							case nationspacingElement:
								go->nation_spacing = atof(content);
								break;

							case paxgalacticaElement:
								go->pax_galactica = atoi(content);
								break;

							case initialtechElement:
								getTechElements(nptr->children, go);
								break;

							case homeworldsElement:
							case developElement:
							case stuffElement:
							case asteroidsElement:
								getPlanets(nptr->children, ev, go);
								break;
								
							case UnknownElement:
								fprintf(emfFP, "Unrecognized element \"%s\", "
										"exiting\n", nptr->name);
								return NULL;
								break;

							default:
								break;
						}

					default:
						break;
				}
			}
			/* normalize data */
			go->from = (go->from == NULL) ?
				strdup(so->from) : go->from;

			go->sub_succeed = (go->sub_succeed == NULL) ?
				strdup(so->sub_succeed) : go->sub_succeed;

			go->sub_fail = (go->sub_fail == NULL) ?
				strdup(so->sub_fail) : go->sub_fail;

			go->replyto = (go->replyto == NULL) ?
				strdup(so->replyto) : go->replyto;

			go->cc = (go->cc == NULL) ? strdup(so->cc) : go->cc;

			if (go->maxplayers < go->minplayers) {
				int tmp = go->maxplayers;
				go->maxplayers = go->minplayers;
				go->minplayers = tmp;
				fprintf(emfFP, "**INFO** %s: maxplayers less than "
						"minplayers, switching\n", go->name);
			}

			if (go->minplayers <= 0 || go->maxplayers <= 0) {
				fprintf(emfFP, "*ERROR** you must specify a postive number of "
						"players in game %s\n", go->name);
				errors++;
			}

			if (go->galaxy_size <= 0) {
				int gsize;
				fprintf(emfFP, "**INFO** %s: incorrect value (%d) for galaxy "
						"size, setting default galaxy size ",
						go->name, go->galaxy_size);
				/* ensure the galaxy size is a multiple of 10 */
				gsize = (int) (42.0 * ceil(sqrt((double)(go->maxplayers+1))));
				gsize /= 10;
				gsize *= 10;
				go->galaxy_size = gsize;
				fprintf(emfFP, "(%d).\n", go->galaxy_size);
			}

			if (go->galaxy_size % 10) {
				fprintf(emfFP, "**INFO** %s: galaxy must be a multiple of 10, "
						"adjusting from %d to ", go->name, go->galaxy_size);
				go->galaxy_size = (go->galaxy_size+5) / 10;
				go->galaxy_size *= 10;
				fprintf(emfFP, "%d.\n", go->galaxy_size);
			}
			
			if (go->nation_spacing <= 0.0) {
				fprintf(emfFP, "**INFO** %s: incorrect value for nation "
						"spacing (%.2f), setting to default nation spacing "
						"(30.0)\n", go->name, go->nation_spacing);
				go->nation_spacing = 30.0;
			}

			if (go->pax_galactica < 0) {
				fprintf(emfFP, "**INFO** %s: incorrect value for Pax Galactica"
						" (%d), resetting to 0\n", go->name,
						go->pax_galactica);
				go->pax_galactica = 0;
			}

			if (go->initial_drive < 1.0) {
				fprintf(emfFP, "**INFO** %s: incorrect value for initial drive"
						" (%.2f), resetting to 1.0\n",
						go->name, go->initial_drive);
				go->initial_drive = 1.0;
			}
			
			if (go->initial_weapons < 1.0) {
				fprintf(emfFP, "**INFO** %s: incorrect value for initial "
						"weapons (%.2f), resetting to 1.0\n",
						go->name, go->initial_weapons);
				go->initial_weapons = 1.0;
			}
			
			if (go->initial_shields < 1.0) {
				fprintf(emfFP, "**INFO** %s: incorrect value for initial shields "
						"(%.2f), resetting to 1.0\n",
						go->name, go->initial_shields);
				go->initial_shields = 1.0;
			}
			
			if (go->initial_cargo < 1.0) {
				fprintf(emfFP, "**INFO** %s: incorrect value for initial cargo "
						"(%.2f), resetting to 1.0\n", go->name, go->initial_cargo);
				go->initial_cargo = 1.0;
			}

			ps = &go->home;
			errors += validatePlanets(emfFP, go, ps, "Home Worlds");
			ps = &go->dev;
			errors += validatePlanets(emfFP, go, ps, "Develop Worlds");
			ps = &go->stuff;
			errors += validatePlanets(emfFP, go, ps, "Stuff Worlds");
			ps = &go->asteroid;
			errors += validatePlanets(emfFP, go, ps, "Asteroids");
		
			if (errors) {
				fprintf(emfFP, "There are errors in game %s, skipping.\n",
						go->name);
			}
			else {
				addList(&so->games, go);
			}
			
			free(name);
		}
	}

	if (ftell(emfFP)) {
		game* aGame;
		
		fclose(emfFP);
		
		aGame->name = strdup("ARE Engine");
		loadNGConfig(aGame);
		env = createEnvelope();
		
		env->to = strdup(aGame->serverOptions.GMemail);
		env->from = strdup(aGame->serverOptions.SERVERemail);
		env->subject = createString("ARE Config Problems");
		eMail(aGame, env, errorMailFile);
		destroyEnvelope(env);
	}				
	xmlCleanupParser();
	return so;
}


static void getTechElements(xmlNodePtr tech, gameOpts* go) {
	enum ELEMENT_VALS ev;
	char* content;

	for (; tech != NULL; tech = tech->next) {
		switch(tech->type) {
			case XML_ELEMENT_NODE:
				ev = lookupElement((char*)tech->name);
				content = (char*)xmlNodeGetContent(tech);
				switch(ev) {
					case driveElement:
						go->initial_drive = atof(content);
						if (go->initial_drive < 1.0)
							go->initial_drive = 1.0;
						break;
						
					case weaponsElement:
						go->initial_weapons = atof(content);
						if (go->initial_weapons < 1.0)
							go->initial_weapons = 1.0;
						break;
						
					case shieldsElement:
						go->initial_shields = atof(content);
						if (go->initial_shields < 1.0)
							go->initial_shields = 1.0;
						break;
						
					case cargoElement:
						go->initial_cargo = atof(content);
						if (go->initial_cargo < 1.0)
							go->initial_cargo = 1.0;
						break;
						
					default:
						break;
				}
				break;
				
			default:
				break;
		}
	}
	return;
}

static void getPlanets(xmlNodePtr planets, enum ELEMENT_VALS worldtype,
					   gameOpts* go) {
	enum ELEMENT_VALS ev;
	char* content;
	planetSpec* ps;
	xmlNodePtr  nptr;
	
	switch(worldtype) {
		case homeworldsElement:
			ps = &go->home;
			break;

		case developElement:
			ps = &go->dev;
			break;

		case stuffElement:
			ps = &go->stuff;
			break;

		case asteroidsElement:
			ps = &go->asteroid;
			break;

		default:
			break;
	}
	
	for (; planets != NULL; planets = planets->next) {
		switch(planets->type) {
			case XML_ELEMENT_NODE:
				ev = lookupElement((char*)planets->name);
				content = (char*)xmlNodeGetContent(planets);

				switch(ev) {
					case countElement:
						for (nptr = planets->children; nptr != NULL;
							 nptr = nptr->next) {
							switch(nptr->type) {
								case XML_ELEMENT_NODE:
									content = (char*)xmlNodeGetContent(nptr);
									
									if (noCaseStrcmp((char*)nptr->name, "min") == 0) {
										ps->count_min = atoi(content);
									}
									else {
										ps->count_max = atoi(content);
									}
									break;

								default:
									break;
							}
						}
						break;
						
					case sizesElement:
						for (nptr = planets->children; nptr != NULL;
							 nptr = nptr->next) {
							switch(nptr->type) {
								case XML_ELEMENT_NODE:
									content = (char*)xmlNodeGetContent(nptr);
									
									if (noCaseStrcmp((char*)nptr->name, "min") == 0) {
										ps->size_min = atof(content);
									}
									else if (noCaseStrcmp((char*)nptr->name, "max") == 0) {
										ps->size_max = atof(content);
									}
									else {
										ps->size_total = atof(content);
									}
									break;

								default:
									break;
							}
						}
						break;

					case resElement:
						for (nptr = planets->children; nptr != NULL;
							 nptr = nptr->next) {
							switch(nptr->type) {
								case XML_ELEMENT_NODE:
									content = (char*)xmlNodeGetContent(nptr);
									
									if (noCaseStrcmp((char*)nptr->name, "min") == 0) {
										ps->res_min = atof(content);
									}
									else if (noCaseStrcmp((char*)nptr->name, "max") == 0) {
										ps->res_max = atof(content);
									}
									break;

								default:
									break;
							}
						}
						break;

					case radiusElement:
						ps->radius = atof(content);
						break;

					case planetElement:
					{
						planetTemplate* pt;
						pt = instantiatePlanet(planets->children);
						addList(&ps->pt, pt);
					}
					break;
					
					default:
						break;
				}

			default:
				break;
		}
	}
	return;
}

static planetTemplate* instantiatePlanet(xmlNodePtr planet) {
	static int planet_nbr = 1;
	
	planetTemplate* pt;
	enum ELEMENT_VALS ev;
	char* content;
	char  name[16];
	
	pt = allocStruct(planetTemplate);
	pt->size = pt->res = pt->pop = pt->ind = pt->cap = pt->col = pt->mat = 0.0;
	sprintf(name, "%d", planet_nbr++);
	setName(pt, name);
	
	for (; planet != NULL; planet = planet->next) {
		switch(planet->type) {
			case XML_ELEMENT_NODE:
				ev = lookupElement((char*)planet->name);
				content = (char*)xmlNodeGetContent(planet);

				switch(ev) {
					case sizeElement:
						pt->size = atof(content);
						break;

					case resElement:
						pt->res = atof(content);
						break;

					case popElement:
						pt->pop = atof(content);
						break;

					case indElement:
						pt->ind = atof(content);
						break;

					case capElement:
						pt->cap = atof(content);
						break;

					case colElement:
						pt->col = atof(content);
						break;

					case matElement:
						pt->mat = atof(content);
						break;
						
					default:
						break;
				}
				break;

			default:
				break;
		}
	}

	return pt;
}

static int validatePlanets(FILE* fp, gameOpts* go,
						   planetSpec* ps, char* title) {
	planetTemplate* pt;
	int errors = 0;
	int total_count;
	float total_size;
	int   homeworlds = !noCaseStrcmp(title, "Home Worlds");
	fprintf(stderr, "title: \"%s\"  homeworlds: %d\n", title, homeworlds);
	if (ps->res_min > ps->res_max) {
		float tmp = ps->res_min;
		ps->res_min = ps->res_max;
		ps->res_max = tmp;
		fprintf(fp, "**INFO** %s: resources reversed, fixing.\n", title);
	}

	if (ps->res_max > 10.0) {
		fprintf(fp, "**INFO** %s: maximum allowable resource is 10, "
				"adjusting.\n", title);
		ps->res_max = 10.0;
	}

	if (homeworlds) {
		ps->res_min = 10.0;
		ps->res_max = 10.0;
	}
	
	if (ps->size_min > ps->size_max) {
		float tmp = ps->size_min;
		ps->size_min = ps->size_max;
		ps->size_max = tmp;
		fprintf(fp, "**INFO** %s: sizes reversed, fixing.\n", title);
	}

	if (ps->size_min == 0.0) {
		if (homeworlds) {
			fprintf(fp,
					"**INFO** %s: HomeWorlds have a minimum size of 100.\n",
					title);
			ps->size_min = 100.0;
		}
	}
	
	if (ps->radius < 0.0) {
		fprintf(fp, "**INFO** %s radius is negative, reversing the sign.\n",
				title);
		ps->radius = -1 * ps->radius;
	}
	
	if (ps->radius > go->galaxy_size) {
		fprintf(fp, "**INFO** %s radius (%.2f) is larger than galaxy size, "
				"resetting to %.2f\n", title, ps->radius,
				(float)go->galaxy_size);
		ps->radius = (float)go->galaxy_size;
	}

	if (ps->count_min < 0) {
		fprintf(fp, "**INFO** %s: planet minium count must be positive, "
				"reversing.\n", title);
		ps->count_min *= -1;
	}

	if (ps->count_max < 0) {
		fprintf(fp, "**INFO** %s: planet maximum count must be positive, "
				"reversing.\n", title);
		ps->count_max *= -1;
	}

	if (ps->count_min > ps->count_max) {
		int tmp = ps->count_max;
		ps->count_max = ps->count_min;
		ps->count_min = tmp;
		fprintf(fp, "**INFO** %s: planet count reversed, fixing.\n", title);
	}

	if (ps->count_max > 0 && ps->radius == 0.0) {
		fprintf(fp, "**ERROR** %s: radius must be > 0 if more than one planet "
				"is expected.\n", title);
		errors++;
	}

	total_count = 0;
	total_size = 0.0;
	
	for(pt = ps->pt; pt != NULL; pt = pt->next) {
		total_count++;
		if (pt->size < 0.0) {
			fprintf(fp, "**ERROR** planet %s has a negative size.\n",
					pt->name);
			errors++;
		}
		else 
			total_size += pt->size;

		if (pt->res < 0.0) {
			fprintf(fp, "**ERROR** planet %s has a negative resource.\n",
					pt->name);
			errors++;
		}

		if (pt->res < ps->res_min || pt->res > ps->res_max) {
			if (homeworlds) {
				fprintf(fp, "**INFO** %s: setting resources to 10.0 for "
						"planet %s\n", title, pt->name);
				pt->res = 10.0;
			}
			else {
				fprintf(fp, "**ERROR** %s: planet %s has an out of range "
						"resource: range: %.2f to %.2f, value: %.2f\n",
						title, pt->name, ps->res_min, ps->res_max, pt->res);
				errors++;
			}
		}

		if (pt->pop < 0) {
			fprintf(fp, "**INFO** %s: population on %s is negative, "
					"reversing sign.\n", title, pt->name);
			pt->pop *= -1;
		}
		
		if (pt->pop > pt->size) {
			fprintf(fp, "**INFO** %s: population on %s is greater than size, "
					"adjusting.\n", title, pt->name);
			pt->pop = pt->size;
		}

		if (pt->ind < 0) {
			fprintf(fp, "**INFO** %s: industry on %s is negative, "
					"reversing sign.\n", title, pt->name);
			pt->ind *= -1;
		}
		
		if (pt->ind > pt->size) {
			fprintf(fp, "**INFO** %s: industry on %s is greater than size, "
					"adjusting.\n", title, pt->name);
			pt->ind = pt->size;
		}

		if (pt->cap < 0) {
			fprintf(fp, "**INFO** %s: CAP on %s is negative, reversing "
					"sign.\n", title, pt->name);
			pt->cap *= -1;
		}

		if (pt->col < 0) {
			fprintf(fp, "**INFO** %s: COL on %s is negative, reversing "
					"sign.\n", title, pt->name);
			pt->col *= -1;
		}

		if (pt->mat < 0) {
			fprintf(fp, "**INFO** %s: MAT on %s is negative, reversing "
					"sign.\n", title, pt->name);
			pt->mat *= -1;
		}
	}
	
	if (total_size > ps->size_total) {
		fprintf(fp, "**ERROR** %s: you specified planets that add up to %.2f "
				"in size, the maximum is %2.f\n", title, total_size,
				ps->size_total);
		errors++;
	}

	if (total_count > 0 && total_count != ps->count_max) {
		fprintf(fp, "**ERROR** %s: you must specify %d default planets if you "
				"specify any - you only specified %d\n", title, ps->count_max,
				total_count);
		errors++;
	}
	
	return errors;
}



#if defined(LoadConfigMainNeeded)

static void dump_planets(planetSpec* ps) {
	planetTemplate* pt;
	
	printf("      resources: %.2f to %.2f\n", ps->res_min, ps->res_max);
	printf("      sizes: %.2f to %.2f (%.2f total)\n",
		   ps->size_min, ps->size_max, ps->size_total);
	printf("      radius: %.2f\n", ps->radius);
	printf("      define %d to %d planets\n", ps->count_min, ps->count_max);
	printf("      Default Planets:\n");
	for(pt = ps->pt; pt != NULL; pt = pt->next) {
		printf("        name: %s\n", pt->name);
		printf("          size: %.2f\n          res: %.2f\n"
			   "          pop: %.2f\n", pt->size, pt->res, pt->pop);
		printf("          ind: %.2f\n          cap: %.2f\n"
			   "          col: %.2f\n", pt->ind, pt->cap, pt->col);
		printf("          mat: %.2f\n", pt->mat);
	}
	
	return;
}
	
static void dump_so(serverOpts* so) {
	gameOpts* go;
	
	printf("server:\n  from: \"%s\"\n  subject (succeed): \"%s\"\n",
		   so->from, so->sub_succeed);
	printf("  subject (fail): \"%s\"\n  replyto: \"%s\"\n",
		   so->sub_fail, so->replyto);
	printf("  cc: \"%s\"\ngames:\n", so->cc);

	for(go = so->games; go != NULL; go = go->next) {
		printf("  %s\n", go->name);
		printf("    from: \"%s\"\n    subject (succeed): \"%s\"\n",
			   go->from, go->sub_succeed);
		printf("    subject (fail): \"%s\"\n    replyto: \"%s\"\n",
			   go->sub_fail, go->replyto);
		printf("    cc: \"%s\"\n    players: %d to %d\n",
			   go->cc, go->minplayers, go->maxplayers);
		printf("    galaxy size: %d\n    nation spacing: %.2f\n",
			   go->galaxy_size, go->nation_spacing);
		printf("    Pax Galactica: %d\n    initial tech:\n",
			   go->pax_galactica);
		printf("      drive: %.2f\n      weapons: %.2f\n",
			   go->initial_drive, go->initial_weapons);
		printf("      shields: %.2f\n      cargo: %.2f\n",
			   go->initial_shields, go->initial_cargo);

		printf("    HomeWorlds:\n");
		dump_planets(&go->home);
		printf("\n    Develop Worlds:\n");
		dump_planets(&go->dev);
		printf("\n    Stuff Worlds:\n");
		dump_planets(&go->stuff);
		printf("\n    Asteroids:\n");
		dump_planets(&go->asteroid);

		
	}
	
	return;
}

int
main (int argc, char *argv[])
{
	serverOpts* so;
	char* value;
	
	if ((value = getenv("GALAXYNGHOME"))) {
		galaxynghome = strdup(value);
	} else if ((value = getenv("HOME"))) {
		sprintf(lineBuffer, "%s/Games", value);
		galaxynghome = strdup(lineBuffer);
	} else {
		galaxynghome =
			strdup("/please/set/your/HOME/or/GALAXYNGHOME/variable");
	}
	
	if (argc == 1)
		so = loadAREConfig ("/home/kenw/Games");
	else
		so = loadAREConfig(argv[1]);

	dump_so(so);

	/*rewrite_rc(so);*/
	
	return EXIT_SUCCESS;
}

#endif
