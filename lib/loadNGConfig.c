#include "galaxy.h"
#include "galaxyng.h"
#include "util.h"

/****f* LoadGame/readDefaults
 * NAME 
 *   readDefaults -- read game defaults
 * FUNCTION
 *   Read defaults from a configuration file : .galaxyngrc
 * NOTES
 *   Has a memory leak.
 * SEE ALSO
 *   game
 ******
 */

void readDefaults(game *aGame, FILE * f) {
	char* isRead;			/* to check for EOF */
	char* key;					/* the key part of the name/value pair */
	
	/* initialize values */
	aGame->serverOptions.sendmail = NULL;
	aGame->serverOptions.encode = NULL;
	aGame->serverOptions.compress = NULL;
	aGame->serverOptions.GMemail = NULL;
	aGame->serverOptions.GMpassword = NULL;
	aGame->serverOptions.SERVERemail = NULL;
	aGame->serverOptions.fontpath = NULL;
	aGame->serverOptions.due = NULL;
	aGame->serverOptions.tick_interval = NULL;
	
	for (isRead = fgets(lineBuffer, LINE_BUFFER_SIZE, f);
		 isRead; isRead = fgets(lineBuffer, LINE_BUFFER_SIZE, f)) {
		
		key = getstr(lineBuffer);
		if (key[0] != '\0') {
			if (noCaseStrcmp("GMemail", key) == 0) {
				aGame->serverOptions.GMemail = strdup(getstr(0));
			}
			else if (noCaseStrcmp("GMpassword", key) == 0) {
				aGame->serverOptions.GMpassword = strdup(getstr(0));
			}
			else if (noCaseStrcmp("SERVERemail", key) == 0) {
				aGame->serverOptions.SERVERemail = strdup(getstr(0));
			}
			else if (noCaseStrcmp("compress", key) == 0) {
				aGame->serverOptions.compress = strdup(getstr(0));
			}
			else if (noCaseStrcmp("encode", key) == 0) {
				aGame->serverOptions.encode = strdup(getstr(0));
			}
			else if (noCaseStrcmp("sendmail", key) == 0) {
				aGame->serverOptions.sendmail = strdup(getstr(0));
			}
			else if (noCaseStrcmp("starttime", key) == 0) {
				aGame->starttime = strdup(getstr(0));
			}
			else if (noCaseStrcmp("fontpath", key) == 0) {
				aGame->serverOptions.fontpath = strdup(getstr(0));
			}
			else if (noCaseStrcmp("due", key) == 0) {
				aGame->serverOptions.due = strdup(getstr(0));
			}
			else if (noCaseStrcmp("tick", key) == 0) {
				aGame->serverOptions.tick_interval = strdup(getstr(0));
			}
			else {
				printf("Unknown key %s\n", key);
			}
		}
	}
	
	if (aGame->serverOptions.due == NULL)
		aGame->serverOptions.due = strdup("soon");
	
	if (aGame->serverOptions.tick_interval == NULL)
		aGame->serverOptions.tick_interval = strdup("48");
	
	if (aGame->serverOptions.SERVERemail == NULL) {
		char* logfile = createString("%s/Games/log/%s", galaxynghome, aGame->name);
		FILE* logfp = fopen(logfile, "+w");
		fprintf(stderr, "SERVERemail is a required entry in your .galaxyngrc\n");
		fprintf(logfp, "SERVERemail is a required entry in your .galaxyngrc\n");
		fclose(logfp);
		exit(EXIT_FAILURE);
	}
    
	if (aGame->serverOptions.GMemail == NULL)
		aGame->serverOptions.GMemail =
			strdup(aGame->serverOptions.SERVERemail);
	
	if (aGame->serverOptions.GMpassword == NULL)
		aGame->serverOptions.GMpassword = strdup("");
}

/****f* LoadGame/loadConfig
 * NAME
 *   loadConfig -- read configuration files
 * FUNCTION
 *   reads defaults from $GALAXYNGHOME/.galaxyngrc
 *   and then from $GALAXYNGHOME/data/<gamename>/.galaxyngrc
 ****
 */

void loadNGConfig(game *aGame) {
	FILE           *f;
	
	sprintf(lineBuffer, "%s/.galaxyngrc", galaxynghome);
	if ((f = fopen(lineBuffer, "r"))) {
		readDefaults(aGame, f);
		fclose(f);
	}
	sprintf(lineBuffer, "%s/data/%s/.galaxyngrc", galaxynghome, aGame->name);
	if ((f = fopen(lineBuffer, "r"))) {
		readDefaults(aGame, f);
		fclose(f);
	}
}


