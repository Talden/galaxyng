#include "create.h"
#include "report_xml.h"

static char    *loadtypename[] =
{
  "CAP",
  "MAT",
  "COL",
  "EMP",
};

/* History :

199906 : copy of report_m, changed to output xml
199911 : update to match new game paradigm
199911 : FS, report_xml closed the XMLreport file. This is 
         the task of the function that calls report_xml...
         resulted in a coredump. 
200002 : [BJE] fixed bugs and XML spec violations
200003 : [BJE] fixed doubled groups bug
200104:  CB, updated to add the game options section.

TODO :  write a doc :).

*/

static FILE* reportFP;

void
report_xml(game* aGame, player* P, FILE* XMLreport)
{

  reportFP = XMLreport;		/* local global */

  rHE_XML(aGame, P);	/* Writes header of report file */
  rMM_XML(aGame, P, aGame->messages, "global");	/* Global messages */
  rMM_XML(aGame, P, P->messages, "personal"); /* Personal messages */
  rGO_XML(aGame);	/* Game options CB-20010401 ; see galaxy.h*/
  rOP_XML(aGame, P);	/* Options */
  rOD_XML(aGame, P);	/* Orders */
  rMK_XML(aGame, P);	/* Mistakes in orders */
  rST_XML(aGame, P);	/* Players status */
  rSH_XML(aGame, P);	/* Ships types */
  rBT_XML(aGame, P);	/* Battles */
  rBB_XML(aGame, P);	/* Bombing */
  rMP_XML(aGame, P);	/* Text map */
  rIC_XML(aGame, P);	/* Incoming groups */
  rAP_XML(aGame, P);	/* All planets */
  rPT_XML(aGame, P);	/* Production table */
  rRT_XML(aGame, P);	/* Routes */
  fprintf(reportFP, "    <grouplist>\n");
  rGG_XML(aGame, P);	/* Player's groups */
  rGS_XML(aGame, P);	/* Others players groups */
  fprintf(reportFP, "    </grouplist>\n");
  rFL_XML(aGame, P);	/* Fleets */
  rEN_XML();		/* Writes last line of XML report file */
}

/* Write header of report file */
void
rHE_XML(game* aGame, player *P)
{
  fprintf(reportFP, "<?xml version=\"1.0\"?>\n\n");
  fprintf(reportFP,
	  "<report>\n"
	  "  <version>%5.2f</version>\n"
	  "  <turn>%d</turn>\n"
	  "  <gamename>%s</gamename>\n"
	  "  <galaxysize>%8.2f</galaxysize>\n",
	  XMLREPORT_VERSION, aGame->turn, aGame->name, aGame->galaxysize);

  fprintf(reportFP, "  <nation name=\"%s\"", P->name);

  if (P->pswdstate != 2)
    {
      fprintf(reportFP, " password=\"%s\"",
	    P->pswd);
    }
  fprintf(reportFP, ">\n");
}

/* report global or personnal messages */
void
rMM_XML(game* aGame, player *P, strlist *messages, char *c)
{
  strlist        *s;
  int             nb_mes = 0;

  s = messages;
  nb_mes = numberOfElements(s);	/* Sorry, only the number of lines is *
				 * counted. */

  s = messages;
  if (messages) {
    fprintf(reportFP, "    <messages type=\"%s\" lines=\"%i\" >\n",
	    c, nb_mes);
    while (s) {
      fprintf(reportFP, "%s\n", s->str);
      s = s->next;
    }
    fprintf(reportFP, "    </messages>\n");
  }
}
/* report game options CB-20010401*/
void
rGO_XML(game* aGame)
{

  fprintf(reportFP, "    <game-options>\n");
  if (aGame->gameOptions.gameOptions & GAME_NONGBOMBING) {  
    fprintf(reportFP, "      <%s state=\"ON\"/>\n", "fullbombing");
  } else {
    fprintf(reportFP, "      <%s state=\"OFF\"/>\n", "fullbombing");
  }
  if (aGame->gameOptions.gameOptions & GAME_KEEPPRODUCTION) {  
    fprintf(reportFP, "      <%s state=\"ON\"/>\n", "keepproduction");
  } else {
    fprintf(reportFP, "      <%s state=\"OFF\"/>\n", "keepproduction");
  }
  if (aGame->gameOptions.gameOptions & GAME_NODROP) {  
    fprintf(reportFP, "      <%s state=\"OFF\"/>\n", "dontdropdead");
  } else {
    fprintf(reportFP, "      <%s state=\"ON\"/>\n", "dontdropdead");
  }
  if (aGame->gameOptions.gameOptions & GAME_SPHERICALGALAXY) {
    fprintf(reportFP, "      <%s state=\"ON\"/>\n", "sphericalgalaxy");
  } else {
    fprintf(reportFP, "      <%s state=\"OFF\"/>\n", "sphericalgalaxy");
  }
  fprintf(reportFP,
	  "      <initialtechlevels>\n"
	  "        <drive>%.2f</drive>\n"
	  "        <weapons>%.2f</weapons>\n"
	  "        <shields>%.2f</shields>\n"
	  "        <cargo>%.2f</cargo>\n",
	  aGame->gameOptions.initial_drive,\
	  aGame->gameOptions.initial_weapons,\
	  aGame->gameOptions.initial_shields,\
	  aGame->gameOptions.initial_cargo);
  fprintf(reportFP, "      </initialtechlevels>\n");
  fprintf(reportFP, "    </game-options>\n");
}
/* report options */
void
rOP_XML(game* aGame, player *P)
{
  option         *curOption;

  int             nb_opt = 0;

  curOption = options;
  while (curOption->optionName) {
    nb_opt++;
    curOption++;
  }

  fprintf(reportFP, "    <options>\n");

  for (curOption = options; curOption->optionName; curOption++) {
    fprintf(reportFP, "      <%s state=", curOption->optionName);
    fprintf(reportFP, "\"%s\"/>\n",
	    P->flags & curOption->optionMask ? "ON" : "OFF");
  }

  fprintf(reportFP, "    </options>\n");
}
/* report oders */
void
rOD_XML(game* aGame, player *P)
{
  strlist        *s;
  int             nb_ord = 0;
  int             i = 1;

  s = P->orders;
  nb_ord = numberOfElements(s);

  if (nb_ord == 0)
    {
      fprintf(reportFP, "    <orders/>\n");
    }
  else
    {
      fprintf(reportFP, "    <orders>\n");

      if (P->orders)
	{
	  for (s = P->orders; s; s = s->next)
	    {
	      fprintf(reportFP, "      <line sequence=\"%d\">%s</line>\n",
		      i++, s->str);
	    }
	}
      fprintf(reportFP, "    </orders>\n");
    }
}

/* report mistakes */
void
rMK_XML(game* aGame, player *P)
{
  strlist        *s;
  int             nb_mis = 0;
  int             i = 1;

  s = P->mistakes;
  nb_mis = numberOfElements(s);	/* number of lines in fact */

  if (nb_mis == 0)
    {
      fprintf(reportFP, "    <mistakes/>\n");
    }
  else
    {
      fprintf(reportFP, "    <mistakes>\n");
      for (s = P->mistakes; s; s = s->next)
	{
	  fprintf(reportFP, "      <line sequence=\"%d\">%s</line>\n",
		  i++, s->str);
	}
      fprintf(reportFP, "    </mistakes>\n");
    }

}
/* report status of players */
void
rST_XML(game* aGame, player *P)
{
  player         *P2;
  int             nb_pla = 0;

  P2 = aGame->players;
  nb_pla = numberOfElements(P2);

  fprintf(reportFP, "    <playerlist>\n");
  for (P2 = aGame->players; P2; P2 = P2->next) 
    {
      fprintf(reportFP,
	      "      <player name=\"%s\">\n"
	      "        <drive>%.2f</drive>\n"
	      "        <weapons>%.2f</weapons>\n"
	      "        <shields>%.2f</shields>\n"
	      "        <cargo>%.2f</cargo>\n"
	      "        <totpop>%.2f</totpop>\n"
	      "        <totind>%.2f</totind>\n"
	      "        <nbrOfPlanets>%d</nbrOfPlanets>\n",
	      P2->name, P2->drive, P2->weapons, P2->shields, P2->cargo,
	      P2->totPop, P2->totInd, P2->numberOfPlanets);

      if (P2 != P)
	{
	  fprintf(reportFP, "        <diplomatic>%s</diplomatic>\n",
		  (atwar(P, P2) ? "War" : "Peace"));
	}
      else
	{
	  fprintf(reportFP, "        <diplomatic>-</diplomatic>\n");
	}

      if (P2->addr[0])
	{
	  if (P2->flags & F_ANONYMOUS)
	    {
	      fprintf(reportFP, "        <address>anonymous</address>\n");
	    }
	  else
	    {
	      fprintf(reportFP, "        <address>%s</address>\n", P2->addr);
	    }
	}
      else
	{
	  fprintf(reportFP, "        <address>none</address>\n");
	}
      fprintf(reportFP, "      </player>\n");
    }
  fprintf(reportFP, "    </playerlist>\n");

}
/* report ship types */
void
rSH_XML(game* aGame, player *P)
{
  player         *P2;
  shiptype       *t;

  int             nbr_typ = 0;

  for (P2 = aGame->players; P2; P2 = P2->next)
    {
      if ((P2 eq P) || visibleShipTypes(aGame, P2, P))
	{
	  for (t = P2->shiptypes; t; t = t->next)
	    {
	      if ((P2 eq P) || (t->flag))
		{
		  nbr_typ++;
		}
	    }
	}
    }

  if (nbr_typ == 0)
    {
      fprintf(reportFP, "    <shiptypes/>\n");
    }
  else
    {
      fprintf(reportFP, "    <shiptypes>\n");
      
      for (P2 = aGame->players; P2; P2 = P2->next)
	{
	  if ((P2 eq P) || visibleShipTypes(aGame, P2, P))
	    {
	      for (t = P2->shiptypes; t; t = t->next)
		{
		  if ((t->flag) || (P eq P2))
		    {
		      fprintf(
			      reportFP,
			      "      <type owner=\"%s\" name=\"%s\">\n"
			      "        <drive>%.2f</drive>\n"
			      "        <attacks>%d</attacks>\n"
			      "        <weapons>%.2f</weapons>\n"
			      "        <shields>%.2f</shields>\n"
			      "        <cargo>%.2f</cargo>\n"
			      "      </type>\n",
			      P2->name, t->name, t->drive, t->attacks,
			      t->weapons, t->shields, t->cargo);
		    }
		}
	    }
	}
      fprintf(reportFP, "    </shiptypes>\n");
    }
}


/* report battles */
/* patched this to fix nested loops using same variables */

void
rBT_XML(game* aGame, player *P)
{
  battle         *b;
  participant    *r;
  int             nbr_bat = 0;

  for (b = aGame->battles; b; b = b->next)
  {
    /*Count battles in which P is involved.*/
    for (r = b->participants; r; r = r->next)
    {
      if (r->who eq P)
      {
	nbr_bat++;
      }
    }
  }
  
  if (nbr_bat == 0)
  {
    fprintf(reportFP, "    <battles/>\n");
  }
  else
  {
    fprintf(reportFP, "    <battles>\n");
    for (b = aGame->battles; b; b = b->next)
    {
      for (r = b->participants; r; r = r->next) 
      {
	if (r->who eq P)
	{
	  int             nbr_par = 0;
	  participant	  *plr;
	  
	  for (plr = b->participants; plr; plr = plr->next)
	  {
	    nbr_par++;
	  }
	  
	  fprintf(reportFP, "      <battle location=\"%s\">\n",
		  b->where->name);
	  
	  for (plr = b->participants; plr; plr = plr->next) 
	  {
	    group          *g;
	    int             nbr_grp = 0;
	    
	    for (g = plr->groups; g; g = g->next)
	    {
	      nbr_grp++;
	    }
	    
	    fprintf(reportFP, "      <groups name=\"%s\">\n",
		    plr->who->name);
	    
	    for (g = plr->groups; g; g = g->next)
	    {
	      rGP_XML(g, 0, G_MODE_BATTLE);
	    }
	    fprintf(reportFP, "      </groups>\n");
	  }
	  fprintf(reportFP, "    </battle>\n");
	}
      }
    }
    fprintf(reportFP, "  </battles>\n");
  }
  
}




/* report bombings */
void
rBB_XML(game* aGame, player *P)
{

  if (canseeBombing(aGame, P))
    {
      bombing        *B;
      alliance       *a;
      int             nbr_bom = 0;

      for (B = aGame->bombings; B; B = B->next)
	{
	  for (a = B->viewers; a; a = a->next)
	    {
	      if (a->who eq P)
		{
		  nbr_bom++;
		}
	    }
	}
      
      if (nbr_bom == 0)
	{
	  fprintf(reportFP, "    <bombings/>\n");
	}
      else
	{
	  fprintf(reportFP, "    <bombings>\n");
	  for (B = aGame->bombings; B; B = B->next)
	    {
	      for (a = B->viewers; a; a = a->next)
		{
		  if (a->who eq P)
		    {
		      break;
		    }
		}
	      
	      if (a)
		{
		  fprintf(reportFP,
			  "      <bombing attacker=\"%s\" defender=\"%s\">\n",
			  B->who->name, B->owner->name);
		  fprintf(reportFP,
			  "        <planet>%s</planet>\n"
			  "        <population>%.2f</population>\n"
			  "        <industry>%.2f</industry>\n",
			  B->name, B->pop, B->ind);
		  
		  if (B->producing eq PR_SHIP)
		    {
		      fprintf(reportFP, "        <producing>%s</producing>",
			      B->producingshiptype->name);
		    }
		  else
		    {
		      fprintf(reportFP, "        <producing>%s</producing>",
			      productname[B->producing]);
		    }
		  
		  fprintf(reportFP,
			  "        <cap>%.2f</cap>\n"
			  "        <mat>%.2f</mat>\n"
			  "        <col>%.2f</col>\n"
			  "      </bombing>\n",
			  B->cap, B->mat, B->col);
		}
	    }
	}
      fprintf(reportFP, "    </bombings>\n");
    }
  else
    {
      fprintf(reportFP, "    <bombings/>\n");
    }


}
/* report text based map */
void
rMP_XML(game* aGame, player *P)
{
  player         *P2;
  int             i, j;
  group          *g;
  planet         *p;
  mapdimensions   mapDim;

  mapDim.x1 = P->mx;
  mapDim.x2 = P->mx + P->msize;
  mapDim.y1 = P->my;
  mapDim.y2 = P->my + P->msize;

  fprintf(reportFP, "    <textmap>\n");

  fprintf(reportFP,
	  "      <xmin>%.2f</xmin>\n"
	  "      <xmax>%.2f</xmax>\n"
	  "      <ymin>%.2f</ymin>\n"
	  "      <ymax>%.2f</ymax>\n",
	  mapDim.x1, mapDim.x2, mapDim.y1, mapDim.y2);

  memset(map, ' ', sizeof map);

  for (P2 = aGame->players; P2; P2 = P2->next)
    {
      if (P2 != P)
	{
	  for (g = P2->groups; g; g = g->next)
	    {
	      putmap(&mapDim, groupx(aGame, g), groupy(aGame, g), '-');
	    }
	}
    }

  for (g = P->groups; g; g = g->next)
    {
      putmap(&mapDim, groupx(aGame, g), groupy(aGame, g), '.');
    }

  for (p = aGame->planets; p; p = p->next)
    {
      if (!p->owner)
	{
	  putmap(&mapDim, p->x, p->y, 'o');
	}
    }

  for (p = aGame->planets; p; p = p->next)
    {
      if (p->owner && p->owner != P)
	{
	  putmap(&mapDim, p->x, p->y, '+');
	}
    }

  for (p = aGame->planets; p; p = p->next)
    {
      if (p->owner eq P)
	{
	  putmap(&mapDim, p->x, p->y, '*');
	}
    }

  for (i = 0; i != MAPHEIGHT; i++)
    {
      for (j = 0; j != MAPWIDTH; j++)
	{
	  if (map[j][i] != ' ')
	    {
	      fprintf(reportFP,
		      "      <symbol x=\"%d\" y=\"%d\">%c</symbol>\n",
		      j, i, map[j][i]);
	    }
	}
    }

  fprintf(reportFP, "    </textmap>\n");

}

/* report incomming */
void
rIC_XML(game* aGame, player *P)
{
  int             nbr_inc = 0;
  player         *P2;

  nbr_inc = 0;
  for (P2 = aGame->players; P2; P2 = P2->next)
    {
      if (P2 != P)
	{
	  group          *g;

	  for (g = P2->groups; g; g = g->next)
	    {
	      if (g->dist && g->where->owner eq P)
		{
		  nbr_inc++;
		}
	    }
	}
    }

  if (nbr_inc == 0)
    {
      fprintf(reportFP, "    <incoming/>\n");
    }
  else
    {
      fprintf(reportFP, "    <incoming>\n");
      for (P2 = aGame->players; P2; P2 = P2->next)
	{
	  if (P2 != P)
	    {
	      group          *g;

	      for (g = P2->groups; g; g = g->next)
		{
		  if (g->dist && g->where->owner eq P)
		    {
		      fprintf(reportFP,
			      "      <group from=\"%s\">\n"
			      "        <where>%s</where>\n"
			      "        <dist>%.2f</dist>\n",
			      g->from->name, g->where->name, g->dist);

		      if (g->thefleet)
			{
			  fprintf(reportFP,
				  "        <speed>%.2f</speed>\n",
				  g->thefleet->fleetspeed);
			}
		      else
			{
			  fprintf(reportFP,
				  "        <speed>%.2f</speed>\n",
				  g->type->drive * g->drive * DRIVEMAGIC /
				  shipmass(g));
			}
		      fprintf(reportFP,
			      "        <mass>%.2f</mass>\n"
			      "      </group>\n",
			      shipmass(g) * g->ships);
		    }
		}
	    }
	}
      fprintf(reportFP, "    </incoming>\n");
    }
}
/* report production tables */
void
rPT_XML(game* aGame, player *P)
{
  planet         *p;
  int             nbr_pro = 0;

  if (P->flags & F_PRODTABLE)
    {
      for (p = aGame->planets; p; p = p->next)
	{
	  if (p->owner eq P && p->producing eq PR_SHIP)
	    {
	      nbr_pro++;
	    }
	}
    }

  if (nbr_pro == 0)
    {
      fprintf(reportFP, "    <production/>\n");
    }
  else
    {
      fprintf(reportFP, "    <production>\n");
      for (p = aGame->planets; p; p = p->next)
	{
	  if (p->owner eq P && p->producing eq PR_SHIP)
	    {
	      rPD_XML(p);
	    }
	}
      fprintf(reportFP, "</production>\n");
    }
}
/* report production (it's a sub routine) */
void
rPD_XML(planet *p)
{
  double          mass;
  double          theshipmass;
  double          prog;

  fprintf(reportFP,
	  "      <planet name=\"%s\">\n"
	  "        <ship>%s</ship>\n",
	  p->name, p->producingshiptype->name);

  theshipmass = typemass(p->producingshiptype);
  mass = theshipmass * INDPERSHIP;
  prog = p->inprogress;
  if (theshipmass > p->mat)
    {
      mass += (theshipmass - p->mat) / p->resources;
    }

  fprintf(reportFP,
	  "        <mass>%.2f</mass>\n"
	  "        <progress>%.2f</progress>\n"
	  "      </planet>\n",
	  mass, prog);
}
/* report routes */
void
rRT_XML(game* aGame, player *P)
{
  int             nbr_rou = 0;
  planet         *p;

  for (p = aGame->planets; p; p = p->next)
    {
      if (p->owner eq P && (p->routes[0] || p->routes[1] ||
			    p->routes[2] || p->routes[3]))
	{
	  nbr_rou++;
	}
    }

  if (nbr_rou == 0)
    {
      fprintf(reportFP, "    <routes/>\n");
    }
  else
    {
      fprintf(reportFP, "    <routes>\n");
      for (p = aGame->planets; p; p = p->next)
	{
	  if (p->owner eq P && (p->routes[0] || p->routes[1] ||
				p->routes[2] || p->routes[3]))
	    {
	      int             i;
	      for (i = 0; i != MAXCARGO; i++)
		{
		  if (p->routes[i])
		    {
		      fprintf(reportFP, "      <%s>\n", loadtypename[i]);
		      fprintf(reportFP,
			      "        <from>%s</from>\n",
			      p->name);
		      fprintf(reportFP,
			      "        <to>%s</to>\n",
			      p->routes[i]->name);
		      fprintf(reportFP, "      </%s>\n", loadtypename[i]);
		    }
		}
	    }
	}				/* for */
      fprintf(reportFP, "    </routes>\n");
    }
}

/* report (all) planets */
void
rAP_XML(game* aGame, player *P)
{
  planet         *p;
  player         *P2;
  int             nbr_pla;
  int             total_planets = 0;

  /* First : the player is the owner, or he can see the planet, owned by * 
   * another player */
  for (P2 = aGame->players; P2; P2 = P2->next)
    {
      nbr_pla = 0;
      for (p = aGame->planets; p; p = p->next)	/* count planets */
	{
	  if (
	      ((P2 eq P) && (p->owner eq P)) ||
	      ((P2 != P) && (p->owner eq P2) &&
	       canseeplanet(P, p))
	      )
	    {
	      nbr_pla++;
	    }
	}


      if (nbr_pla != 0)
	{
	  if (total_planets == 0)
	    {
	      fprintf(reportFP, "    <planetlist>\n");
	    }
	  total_planets += nbr_pla;
	  for (p = aGame->planets; p; p = p->next)
	    {	/* examines all the planets */
	      if (
		  ((P2 eq P) && (p->owner eq P)) ||
		  ((P2 != P) && (p->owner eq P2) &&
		   canseeplanet(P, p))
		  )
		{
		  /* if (p->owner eq P || (isunidentified(P, p) && *
		   * canseeplanet(P,p))) */
		  rPL_XML(p, P2->name);
		}
	    }
	}
    }

  /* Second : planets owned by others players, but not visible */
  for (p = aGame->planets; p; p = p->next)/* count planets */
    {
      if (p->owner != P && isunidentified(P, p) && !canseeplanet(P, p))
	{
	  nbr_pla++;
	}
    }

  if (nbr_pla)
    {
      if (total_planets == 0)
	{
	  fprintf(reportFP, "    <planetlist>\n");
	}
      total_planets += nbr_pla;

      for (p = aGame->planets; p; p = p->next)/* examines all the planets */
	{ 
	  if (p->owner != P && isunidentified(P, p) && !canseeplanet(P, p))
	    {
	      fprintf(reportFP,
		      "      <planet name=\"%s\">\n"
		      "        <owner>unidentified</owner>\n"
		      "        <x>%.2f</x>\n"
		      "        <y>%.2f</y>\n"
		      "      </planet>\n",
		      p->name, p->x, p->y);
	    }
	}
    }

  /* Third : uninhabited planets */
  nbr_pla = 0;
  for (p = aGame->planets; p; p = p->next) /* count planets */
    {
      if (isuninhabited(P, p))
	{
	  nbr_pla++;
	}
    }

  if (nbr_pla)
    {
      if (total_planets == 0)
	{
	  fprintf(reportFP, "    <planetlist>\n");
	}
      total_planets += nbr_pla;

      for (p = aGame->planets; p; p = p->next)	/* examines all the planets */
	{
	  if (isuninhabited(P, p))
	    {
	      fprintf(reportFP,
		      "      <planet name=\"%s\">\n"
		      "        <owner>uninhabited</owner>\n"
		      "        <x>%.2f</x>\n"
		      "        <y>%.2f</y>\n",
		      p->name, p->x, p->y);

	      if (canseeplanet(P, p))
		{
		  fprintf(reportFP,
			  "        <size>%.2f</size>\n"
			  "        <resources>%.2f</resources>\n",
			  p->size, p->resources);
		}
	      fprintf(reportFP, "      </planet>\n");
	    }
	}
    }

  if (total_planets == 0)
    {
      fprintf(reportFP, "    <planetlist/>\n");
    }
  else
    {
      fprintf(reportFP, "    </planetlist>\n");
    }
}
/* report groups */
void
rGG_XML(game* aGame, player *P)
{

  int             nbr_grp = 0;
  group          *g;

  for (g = P->groups; g; g = g->next)
    {
      if (!g->thefleet)
	{
	  nbr_grp++;
	}
    }

  if (nbr_grp == 0)
    {
      fprintf(reportFP, "      <groups owner=\"%s\"/>\n", P->name);
    }
  else
    {
      planet         *p;

      fprintf(reportFP, "      <groups owner=\"%s\">\n", P->name);
      for (p = aGame->planets; p; p = p->next)	/* First : player's planets */
	{
	  if (p->owner eq P)
	    {
	      for (g = P->groups; g; g = g->next)
		{
		  if (!g->thefleet) /* It's not a fleet */
		    {
		      if ((g->location eq p) ||
			  (!g->location && g->where eq p))
			{
			  rGP_XML(g, g->number, G_MODE_OWN);
			}
		    }
		}
	    }
	}

    for (p = aGame->planets; p; p = p->next) /* Next :
					 planets owned by others players */
      {
	if (p->owner && p->owner != P)
	  {
	    for (g = P->groups; g; g = g->next)
	      {
		if (!g->thefleet)
		  {
		    if ((g->location eq p) ||
			(!g->location && g->where eq p))
		      {
			rGP_XML(g, g->number, G_MODE_OWN);
		      }
		  }
	      }
	  }
      }

    for (p = aGame->planets; p; p = p->next)	/* Next : uninhabited planets */
      {
	if (!p->owner)
	  {
	    for (g = P->groups; g; g = g->next)
	      {
		if (!g->thefleet)
		  {
		    if ((g->location eq p) ||	/* bje: doubled groups fixed */
			(!g->location && g->where eq p))
		      {
			rGP_XML(g, g->number, G_MODE_OWN);
		      }
		  }
	      }
	  }

      }
    
      fprintf(reportFP, "      </groups>\n");
    }
}
/* Report groups seen */
void
rGS_XML(game* aGame, player *P)
{
  player         *P2;

  for (P2 = aGame->players; P2; P2 = P2->next)
    {
      if (P2 != P)
	{
	  int             nbr_grp = 0;
	  group          *g;

	  for (g = P2->groups; g; g = g->next)
	    {
	      if (canseegroup(P, g))
		{
		  nbr_grp++;
		}
	    }

	  if (nbr_grp == 0)
	    {
	      fprintf(reportFP, "      <groups owner=\"%s\"/>\n", P2->name);
	    }
	  else
	    {
	      group          *g;
	      
	      fprintf(reportFP, "      <groups owner=\"%s\">\n", P2->name);
	      for (g = P2->groups; g; g = g->next)
		{
		  if (canseegroup(P, g))
		    {
		      rGP_XML(g, 0, G_MODE_ALIEN);
		    }
		}
	      fprintf(reportFP, "</groups>\n");
	    }
	}
    }
}

/* Report fleets */
void
rFL_XML(game* aGame, player *P)
{
  if (P->fleetnames)
    {
      fleetname      *fl;
      int             nbr_flt;

      nbr_flt = numberOfElements(P->fleetnames);
      fprintf(reportFP,
	      "    <fleets>\n");

      for (fl = P->fleetnames; fl; fl = fl->next)
	{
	  group          *g;
	  int             nbr_grp = 0;

	  for (g = P->groups; g; g = g->next)
	    {
	      if (g->thefleet eq fl)
		{
		  nbr_grp++;
		}
	    }

	  fprintf(reportFP,
		  "      <fleet name=\"%s\">\n", fl->name);
	  fprintf(reportFP,
		  "        <speed>%.2f</speed>\n", fl->fleetspeed);
	  for (g = P->groups; g; g = g->next)
	    {
	      if (g->thefleet eq fl)
		{
		  rGP_XML(g, g->number, G_MODE_OWN);
		}
	    }
	  fprintf(reportFP, "      </fleet>\n");
	}
      fprintf(reportFP, "    </fleets>\n");
    }
  else
    {
      fprintf(reportFP, "    <fleets/>\n");
    }
}
/* Write last line of file report */
void
rEN_XML()
{
  fprintf(reportFP, "  </nation>\n</report>\n");
}

/* report groups (it's a sub routine) */
void
rGP_XML(group *g, int n, int mode)
{
  static int otherGroupNbr = 100000;

  if (mode eq G_MODE_OWN)
    {
      fprintf(reportFP,
	      "        <group num=\"%d\">\n", n);
    }
  else
    {
      fprintf(reportFP,
	      "        <group num=\"%d\">\n", otherGroupNbr++);
    }

  if (mode eq G_MODE_BATTLE)
    {
      fprintf(reportFP,	/* Quantity of surviving ships */
	      "          <ships>%d</ships>\n", g->left); 
    }
  else
    {
      fprintf(reportFP,
	      "          <ships>%d</ships>\n", g->ships);
    }

  fprintf(reportFP,
	  "              <name>%s</name>\n"
	  "              <drive>%.2f</drive>\n"
	  "              <weapons>%.2f</weapons>\n"
	  "              <shields>%.2f</shields>\n"
	  "              <cargo>%.2f</cargo>\n"
	  "              <loadtype>%s</loadtype>\n"
	  "              <load>%.2f</load>\n",
	  g->type->name, g->drive, g->weapons, g->shields,
	  g->cargo, loadtypename[g->loadtype], g->load);

  /*  if (mode != G_MODE_BATTLE)*/
  fprintf(reportFP,
	  "              <where>%s</where>\n",
	  g->where->name);

  if (mode eq G_MODE_OWN)
    {
      if (g->dist)
	{
	  fprintf(reportFP,
		  "        <dist>%.2f</dist>\n"
		  "        <from>%s</from>\n",
		  g->dist, g->from->name);
	}
      /* else  { fprintf(reportFP, " %s %s", "", ""); *  * } */
    }

  if (mode eq G_MODE_BATTLE)
    {
      fprintf(reportFP,
	      "        <shipsbefore>%d</shipsbefore>\n",
	      g->ships); /* Quantity of ships BEFORE a battle */
    }
  fprintf(reportFP, "      </group>\n");

}
/* report planets (it's a sub routine) */
void
rPL_XML(planet *p, char* owner)
{
  fprintf(reportFP,
	  "      <planet name=\"%s\">\n", p->name);
  fprintf(reportFP,
	  "        <owner>%s</owner>\n", owner);
  fprintf(reportFP,
	  "        <x>%.2f</x>\n"
	  "        <y>%.2f</y>\n"
	  "        <size>%.2f</size>\n"
	  "        <population>%.2f</population>\n"
	  "        <industry>%.2f</industry>\n"
	  "        <resources>%.2f</resources>\n",
	  p->x, p->y, p->size, p->pop, p->ind, p->resources);

  if (p->producing eq PR_SHIP)
    {
      fprintf(reportFP,
	      "        <producing> %s</producing>\n",
	      p->producingshiptype->name);
    }
  else
    {
      fprintf(reportFP,
	      "        <producing>%s</producing>\n",
	      productname[p->producing]);
    }
  fprintf(reportFP,
	  "        <cap>%.2f</cap>\n"
	  "        <mat>%.2f</mat>\n"
	  "        <col>%.2f</col>\n",
	  p->cap, p->mat, p->col);

  fprintf(reportFP,
	  "      </planet>\n");
}
