#include "galaxyng.h"

/****i* CLI/relayMessage
 * NAME
 *   relayMessage --
 ******
 */

int relayMessage( game *aGame, char *raceName, player* from, emailList* to ) {
    char* messageName;
	char* isRead;
    FILE* message;
	
    envelope *anEnvelope;
    int result;
	static int message_read = 0;
	static strlist* msg;
	strlist* s;
	
    result = 1;

    messageName = createString( "%s/NGmessage", tempdir );

	if (!message_read) {
		message_read = 1;
		msg = makestrlist("\n-*- Message follows -*-\n\n" );
		
		for ( isRead = fgets( lineBuffer, LINE_BUFFER_SIZE, stdin );
			  isRead;
			  isRead = fgets( lineBuffer, LINE_BUFFER_SIZE, stdin ) ) {
			char* ptr;
			
			if ((ptr = strstr(lineBuffer, from->pswd)) != NULL)
				memset(ptr, '*', strlen(from->pswd));
			
			if (noCaseStrncmp("#end", lineBuffer, 4) == 0)
				break;
			addList(&msg, makestrlist(lineBuffer));
		}

	}

    if ( to->addr ) {
        if ( ( message = fopen( messageName, "w" ) ) ) {

            anEnvelope = createEnvelope(  );

            setHeader( anEnvelope, MAILHEADER_TO, "%s", to->addr );

			if (strstr(raceName, "@") != NULL) {
				setHeader(anEnvelope, MAILHEADER_SUBJECT,
						  "[GNG] message relay GM");
			}
			else {
				setHeader( anEnvelope, MAILHEADER_SUBJECT,
						   "[GNG] message relay %s", raceName );
			}
			
            fprintf( message, "#GALAXY %s %s %s\n",
                     aGame->name, to->name, to->pswd );

			for (s = msg; s; s = s->next)
				fprintf(message, "%s\n", s->str);

			fprintf(message, "\n#END\n");
            fclose( message );
            result = eMail( aGame, anEnvelope, messageName );
            destroyEnvelope( anEnvelope );
            result |= ssystem( "rm %s", messageName );
            free( messageName );
        }
		else {
            fprintf( stderr, "Can't open \"%s\".\n", messageName );
        }
    }
	
    return result;
}
