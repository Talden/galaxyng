/*  $Id$ */

/****h* Galaxy/ARE
 * NAME
 *   ARE - automatic registration engine
 * SYNOPSIS
 *   are join|drop

 * FUNCTION
 *   Automate the registration process for a game.
 *   The program processes email send in by players wishing to join or
 *   drop a particular game. 
 *
 *   Email looks like a regular game orders
 *
 *   #GALAXYNG gamename racename [password]
 *   k <size of planet 1> <size of planet 2> ... <size of planet n>
 *   n 1 firstname
 *   n 2 secondname
 *   o no txtreport
 *   o no xmlreport
 *   #END
 *   
 * INPUTS
 *   command line:  join - a player wants to join a game
 *                  drop - a player wants to drop a game they signed
 *                  up for
 *
 *   rcfile: in xml format
 *           <are version="1.0">
 *             <game name="GameName">
 *               <playerlimit></playerlimit>
 *               <totalplanetsize></totalplanetsize>
 *               <maxplanetsize></maxplanetsize>
 *               <maxnbrplanets></maxnbrplanets>
 *             </game>
 *           </are>
 *
 * RESULTS
 *   A confirmation message is send to the players.
 *   Four kinds of messages can be generated:
 *   (1)  You are accepted.
 *   (2)  The game is full.
 *   (3)  You made an error in your configuration line(s).
 *   (4)  You tried to drop a game you weren't in
 *
 *   The email address and planet sizes are written to two files:
 *   (1) $GALAXYHOME/<game name>.players  for players that were accepted
 *   (2) $GALAXYHOME/<game name>.standby  for players that were rejected.
 *   The contents of these files can be pasted into your .glx file.
 *   $GALAXYHOME is either the value you gave it, or if it is undefined, 
 *   $HOME/Games.
 *
 *
 *   The programs does the following checks on the k line:
 *   (1) Whether the size of a single planet exceeds the limit set.
 *   (2) Whether too many planets are specified.
 *   (3) Whether the sum of all sizes exceeds the limit set.
 *   (4) Whether the sum of all sizes is too small. This will be most
 *       likely be because the player made an error. If this error then
 *       shows up in the turn 0 the player is most likely to drop out.
 *
 *   If any errors occur the player is notified and has
 *   to retransmit the enroll request.
 *
 * EXAMPLE
 *
 *   The entry in the .arerc file to accept 25 players for the
 *   game Jangi.  Players can specify a maximum of 5 planets, of which
 *   the total size should not exceed 2000.0. Each single planet
 *   should be no larger than 1000.0
 *
 *   <are version="1.0">
 *      <game name="Jangi">
 *         <playerlimit>25</playerlimit>
 *         <totalplanetsize>2000.0</totalplanetsize>
 *         <maxplanetsize>1000.0</maxplanetsize>
 *         <maxnbrplanets>5</maxnbrplanets>
 *      </game>
 *   </are>
 *
 *     GALAXYNGHOME=$HOME/Games
 *
 *     :0 rw :are.lock
 *     * ^Subject.*Join
 *     |/usr/bin/formail -rkbt -s $GALAXYNGHOME/are join | /usr/sbin/sendmail -t 
 *
 *   This assumes the program is installed in $GALAXYNGHOME
 *
 *   Players can now enroll in the game sending you an email with 
 *   the subject:
 *
 *      Join
 *******
 */

#include "are.h"

char* gamename;

int join(serverOpts* so, envelope* env);
int drop(serverOpts* so, envelope* env);

int main(int argc, char *argv[]) {
	serverOpts* so;				/* server options */
	envelope*   received_env;

	char*       value;
	int         errorCode = EXIT_FAILURE;
	
	DBUG_ENTER("main");
	DBUG_PROCESS(argv[0]);
	DBUG_PUSH_ENV("DBUG");
	
	if ((value = getenv("GALAXYNGHOME"))) {
		galaxynghome = strdup(value);
	}
	else if ((value = getenv("HOME"))) {
		sprintf(lineBuffer, "%s/Games", value);
		galaxynghome = strdup(lineBuffer);
	}
	else {
		galaxynghome =
			strdup("/please/set/your/HOME/or/GALAXYNGHOME/variable");
	}

	if (argc > 1) {
		DBUG_PUSH(&(argv[1][2]));
	}

	DBUG_PRINT("env", ("home dir: %s", galaxynghome));
	
	errorCode = EXIT_FAILURE;
  
	/* load the configuration file */
	if ((so = loadAREConfig(galaxynghome)) == NULL) {
		DBUG_RETURN(errorCode);
	}

	received_env = readEnvelope(stdin);
	
	DBUG_PRINT("mail", ("returnAddress: %s/%s",
						received_env->from, received_env->replyto));
	DBUG_PRINT("mail", ("subject: %s", received_env->subject));

	if (noCaseStrncmp(received_env->subject, "join", 4) == 0) {
		errorCode = join(so, received_env);
	}
	else if (noCaseStrncmp(received_env->subject, "drop", 4) == 0) {
		errorCode = drop(so, received_env);
	}

	DBUG_RETURN(errorCode);
}



#if 0
/****** ARE/playerMessage
 * NAME
 *   playerMessage -- write the "accepted" message
 * FUNCTION
 *   Prints the "You Are Accepted" message to stdout. 
 ******
 */

void
playerMessage(char *gameName, char *address, char *planets)
{
  printf(
	 "I am happy to report that you have been accepted for the game %s.\n"
	 "Your address:\n"
	 "   %s\n"
	 "has been added to the list.\n"  
	 " \n",
	 gameName, address);
  if (planets) {
    printf("Your planet sizes will be:\n  %s\n\n", planets);
  }
  printf(
	 "Please note that I am a program. My only function is to register\n"
	 "your name. I am not smart enough to answer any questions that you\n"
	 "might have put in your mail.\n"
	 "\n"
	 "For more information about GalaxyNG, have a look at\n"
	 "  http://galaxyng.sourceforge.net/\n"
	 "Now is a good time to read the manual:\n"
	 "  http://galaxyng.sourceforge.net/manual.php\n"
	 "and the FAQ: \n"
	 "   http://galaxyng.sourceforge.net/faq.php\n\n"
	 "If you then still have questions, join the galaxyng-players mailing list:\n"
	 "  http://lists.sourceforge.net/lists/listinfo/galaxyng-players\n"
	 "\n"
	 "Happy Hunting in Galaxy %s!\n\n",
	 gameName);
}


void
standbyMessage(char *gameName)
{
  printf(
	 "\nIt's my sad duty to report that the game %s is already full.\n"
	 "\n\n"
	 "Please note that I am a program, and that my only function is to\n"
	 "register your name.  I am not smart enough to answer any\n"
	 "questions that you might have put in your email, so please do\n"
	 "not get angry because they are not answered.\n"
	 "\n"
	 "Have Fun!\n\n",
	 gameName);
}



/****f* ARE/getstr 
 *
 * NAME 
 *   getstr -- extract a word from a longer string 
 * SYNOPSIS 
 *   char *getstr(char *s)
 *   word = getstr(someString)
 * FUNCTION
 *   Extract a word from a string of words.  A word is any things that
 *   is separated by white spaces or a comma, any string that is
 *   delimited by quotes ("), or or any string delimited by { }.
 *
 *   The function is intended to parse a string word by word. It
 *   should be first called as:
 *
 *     firstword = getstr(myStringOfWords);
 *
 *   This gets the first word from the string pointed to by
 *   myStringOfWords.  Then consecutive calls of
 *
 *     nextword = getstr(NULL);
 *
 *   you get the remaining words.
 *
 *   White spaces inside a quote delimited word are turned into 
 *   underscores.  
 *
 *   In a string a ';' signifies the start of a comment. Any words
 *   after a ';' are not parsed.
 * 
 *   In the non comment part ';' and '<' are removed before the words
 *   are returned.
 *  
 * RESULTS
 *   word = a pointer to a nul terminated string.
 *
 *   Program is aborted if the length of the word is longer than 256,
 *   since then some is most likely trying to crack your system.
 * 
 *   When there are no more words"\0" is returned.
 * NOTES
 *   This function can only work on one string at the time since it
 *   works with a statically allocated buffer.  This function is used
 *   almost every where in the program.
 * SOURCE
 */

char* getstr(char *s) {
	static char*    s1;
	static char     buf[256];
	int             i, j;
  
	if (s)
		s1 = s; 
	/* first invocation of this function, for an order line. 
	   Each next times, for the same order line, s1 will "progress" 
	   by a word to the right */
	assert (s1 != NULL);
	
	i = 0;
	for (; *s1 && isspace(*s1); s1++)
		;	/* skips spaces */
	
	if (*s1 == '"') {
		/* Players can enclose name (ie : including spaces) with double quotes */
		for (s1++; *s1 && *s1 != '"';) {	
			buf[i] = isspace(*s1) ? '_' : *s1;
			s1++;
			i++;
			assert(i < 256);	/* abort execution if s1 too long */
		}
	}
	else if (*s1=='{') {		
		for (s1++; *s1 && *s1 != '}';) {
			buf[i] = *s1;
			s1++;
			i++;
			assert(i < 256);	/* abort execution if s1 too long */
		}
	}
	else {
		if (*s1 != ';') {		/* otherwise, it's a comment */
			for (; *s1 && !isspace(*s1) && *s1 != ',';) {
				/* space or ',' can be  used as separators, */
				buf[i] = *s1;
				s1++;
				i++;
				assert(i < 256);  /* abort execution if s1 too long */
			}
		}
	}
	
	buf[i] = '\0';
	if (*s1) s1++;  /* Skip ',' or space */
	/* CB, 19980922. Remove ";" and "<" from names (planets,  ships...), 
	   to protect machine report from corruption. Don't break messages 
	   and comments. */
	i = 0;
	j = 0;	
	while (buf[j] && j < 256) {
		if (buf[j] != ';' && buf[j] != '<') {
			buf[i] = buf[j];
			i++;
		}
		j++;
	}
	if (i)
		buf[i] = '\0';	
	
	return buf;
}

/***********/



/****f* ARE/getReturnAddress
 * NAME
 *   getReturnAddress
 * FUNCTION
 *   Extract the return address from a players email.
 ******
 */

char* getReturnAddress(FILE *orders) {
	char* isRead;
	char* c;
	
	for (isRead = fgets(lineBuffer, LINE_BUFFER_SIZE, orders);
		 isRead;
		 isRead = fgets(lineBuffer, LINE_BUFFER_SIZE, orders)) {
		if (noCaseStrncmp("To:", lineBuffer, 3) == 0) 
			break;
	}
	assert(isRead != NULL);
	for (c = lineBuffer; *c; c++) {
		if (*c == '\n') *c = '\0';
	}
	return strdup(lineBuffer + 3) ;
}


/****f* ARE/noCaseStrncmp
 * NAME
 *   noCaseStrncmp --
 * SYNOPSIS
 *   int noCaseStrncmp(char *, char *, int)
 *   result = noCaseStrncmp(s, t, n)
 * FUNCTION
 *   Compare two strings without paying no attention to the case of
 *   the letters, but compare no more than n characters.
 * RESULT
 *    0  s == t
 *   -1  s < t
 *    1  s > t
 * SOURCE
 */

int noCaseStrncmp(char *s, char *t, int n) {
	for (n--; (tolower(*s) == tolower(*t)) && (n > 0); s++, t++, n--)
		if (*s == '\0')
			return 0;
	return (int) (tolower(*s) - tolower(*t));
}

/***********/

							 
void ReadDefaults(serverOpts* so, FILE* f) {
	char* isRead;				/* a line read? if so, ptr to it */
	char* key;					/* key of the key/value pair */
	char* value;				/* value of the keyword */
	char* ptr;					/* for buffer manipulation */
	
	char  lineBuffer[LINE_BUFFER_SIZE+1]; /* for reading the config file */
	
	so->from = NULL;
	so->subject = NULL;
	so->replyto = NULL;
	so->cc = NULL;
	
	for (isRead = fgets(lineBuffer, LINE_BUFFER_SIZE, f);
		 isRead; isRead = fgets(lineBuffer, LINE_BUFFER_SIZE, f)) {
		strtok(lineBuffer, "\r\n");
		if (lineBuffer[0] == '\0' || lineBuffer[0] == '#')
			continue;
		
		key = getstr(lineBuffer);
		
		if (key[0] != '\0') {
			if (noCaseStrcmp("from", key) == 0) {
				value = getstr(0);
				if (strchr(value, '%'))
					value = substitute(value);
				so->from = (char*)malloc(sizeof(char)*(strlen(value)+16));
				sprintf(so->from, "From: %s", value);
			}
			else if (noCaseStrcmp("subject", key) == 0) {
				value = getstr(0);
				if (strchr(value, '%'))
					value = substitute(value);
				
				so->subject =
					(char*)malloc(sizeof(char)*(strlen(value)+16));
				
				sprintf(so->subject, "Subject: %s", value);
			}
			else if (noCaseStrcmp("replyto", key) == 0) {
				value = getstr(0);
				if (strchr(value, '%'))
					value = substitute(value);
				so->replyto = (char*)malloc(sizeof(char)*(strlen(value)+16));
				sprintf(so->replyto, "ReplyTo: %s", value);
			}
			else if (noCaseStrcmp("cc", key) == 0) {
				value = getstr(0);
				if (strchr(value, '%'))
					value = substitute(value);
				so->cc = (char*)malloc(sizeof(char)*(strlen(value)+16));
				sprintf(so->cc, "CC: %s", value);
			}
		}
	}
	
	return;
}
#endif


