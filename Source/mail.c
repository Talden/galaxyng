#include "mail.h"
#include "util.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void createMailToAllHeader(game *aGame)
{
  player *aPlayer;
  int state;

  printf("To: %s\nBcc: ", aGame->serverOptions.GMemail); 
  for (aPlayer = aGame->players, state = 0;
       aPlayer;
       aPlayer = aPlayer->next) {
    if (!(aPlayer->flags & F_DEAD)) { 
      if (state == 0) {
	printf("  %s", aPlayer->addr);
	state = 1;
      } else {
      	printf(",\n  %s", aPlayer->addr);
      }
    }
  }
  printf("\nSubject:\n");
}

/****f* GalaxyNG/createEnvelope
 * NAME
 *   createEnvelope -- create an envelope.
 * FUNCTION
 *   Creates and initializes and envelope.
 ******
 */

envelope *createEnvelope() 
{
  envelope *e;
  e = malloc(sizeof(envelope));
  assert(e != NULL);
  e->to = NULL;
  e->from = NULL;
  e->subject = NULL;
  e->compress = FALSE;
  return e; 
}


/****f* GalaxyNG/setHeader
 * NAME
 *   setHeader -- write something on the envelope.
 * SYNOPSIS
 *   void setHeader(envelope *e, int headerType, char *format, ...)
 * FUNCTION
 *   Dynamically create a mail header. 
 *******
 */

void setHeader(envelope *e, int headerType, char *format, ...) {
  int   n;

  va_list         ap;

  assert(e != NULL);

  va_start(ap, format);
#ifdef WIN32
  vsprintf(lineBuffer, format, ap);
#else
  n = vsnprintf(lineBuffer, LINE_BUFFER_SIZE, format, ap);
  assert(n != -1);
#endif
  va_end(ap);

  switch(headerType) {
  case MAILHEADER_TO:
    if (e->to) free(e->to);
    e->to = strdup(lineBuffer);
    break;
  case MAILHEADER_FROM:
    if (e->from) free(e->from);
    e->from = strdup(lineBuffer);
    break;
  case MAILHEADER_SUBJECT:
    if (e->subject) free(e->subject);
    e->subject = strdup(lineBuffer);
    break;
  default: assert(0);
  }
}

/****f* GalaxyNG/destroyEnvelope
 * NAME
 *   destroyEnvelope -- free memory used by an envelope.
 * SYNOPSIS
 *   destroyEnvelope(envelope *e)
 ********
 */

void destroyEnvelope(envelope *e)
{
  assert(e != NULL);
  if (e->to) free(e->to);
  if (e->from) free(e->from);
  if (e->subject) free(e->subject);
  free(e);
}


/****f* GalaxyNG/eMail 
 * NAME
 *   eMail -- mail the contents of a file to someone.
 * FUNCTION
 *   Mail a file to someone. 
 * INPUTS
 *   e        -- envelope
 *   aGame    -- game structure, contains settings for mailer etc.
 *   fileName -- name of the file to send.
 * RESULT
 *   status  0, all OK.
 *          >0, something went wrong
 * BUGS
 *   Does not write anything to the log file.
 ******
 */

    int
eMail(game *aGame, envelope *e, char *fileName)
{
    char           *tempName;
    int             result;

    pdebug(DFULL, "eMail\n");

    assert(fileName != NULL);
    assert(aGame != NULL);

    tempName = tmpnam(NULL);
    result = 1;
    if (tempName != NULL) {
	FILE           *mailFile;
	if ((mailFile = GOS_fopen(tempName, "w"))) {
	    assert(e->to);
	    assert(e->subject);

	    fprintf(mailFile, "To: %s\n", e->to);
	    fprintf(mailFile, "Subject: %s\n", e->subject);
#ifndef WIN32
	    if (e->compress && aGame->serverOptions.compress && aGame->serverOptions.encode) {
		addMimeHeader(mailFile);
	    }
	    fprintf(mailFile, "\n\n");
	    if (e->compress && aGame->serverOptions.compress && aGame->serverOptions.encode) {
		char *relative_path; 
		addMimeText(mailFile);
		fprintf(mailFile, "Turn report is attached as .zip file.\n\n");
		relative_path = strstr(fileName, "reports");
		if (relative_path == NULL) {
			fprintf(stderr, 
					"Reports are not in their standards position\n");
			relative_path = fileName;
		}
		result = ssystem("%s %s.zip %s",
			aGame->serverOptions.compress,
			fileName,
			relative_path);
		result |= ssystem("%s %s.zip > %s", 
			aGame->serverOptions.encode, 
			fileName, 
			fileName);
		addMimeZip(mailFile);
		result |= appendToMail(fileName, mailFile);
		addMimeEnd(mailFile);
		result |= ssystem("rm %s.zip", fileName);
	    } else {
		result = appendToMail(fileName, mailFile);
	    }
#endif
	    fclose(mailFile);
#ifndef WIN32
	    result |= ssystem("%s < %s", aGame->serverOptions.sendmail, tempName);
	    result |= ssystem("rm %s", tempName);
#endif
	} else {
	    fprintf(stderr, "Can't open \"%s\".\n", tempName);
	}
    } else {
	fprintf(stderr, "Can't create temporary file.\n");
    }
    return result;
}



void addMimeHeader(FILE *mailFile) 
{
	fprintf(mailFile, "Mime-Version: 1.0\n");
	fprintf(mailFile, 
		"Content-Type: multipart/mixed; boundary=\"9jxsPFA5p3P2qPhR\"\n");
	fprintf(mailFile, "Content-Disposition: inline\n");
}



void addMimeText(FILE *mailFile)
{
   fprintf(mailFile, "--9jxsPFA5p3P2qPhR\n");
   fprintf(mailFile, "Content-Type: text/plain; charset=us-ascii\n");
   fprintf(mailFile, "Content-Disposition: inline\n");
   fprintf(mailFile, "\n");
}



void addMimeZip(FILE *mailFile)
{
   fprintf(mailFile, "--9jxsPFA5p3P2qPhR\n");
   fprintf(mailFile, "Content-Type: application/zip\n");
   fprintf(mailFile, "Content-Disposition: attachment; filename=\"turn.zip\"\n");
   fprintf(mailFile, "Content-Transfer-Encoding: base64\n");
   fprintf(mailFile, "\n");
}



void addMimeEnd(FILE *mailFile)
{
   fprintf(mailFile, "\n--9jxsPFA5p3P2qPhR--\n");
}



int appendToMail(char *fileName, FILE *mailFile)
{
  FILE *f;
  char *isRead;
  f = GOS_fopen(fileName, "r");
  if (f) {
    for (isRead = fgets(lineBuffer, LINE_BUFFER_SIZE, f);
         isRead;
         isRead = fgets(lineBuffer, LINE_BUFFER_SIZE, f)) {
      fputs(lineBuffer, mailFile);
    }
	fclose(f);
	return FALSE;
  } else {
    return TRUE;
  }
}

