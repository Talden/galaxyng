#include "galaxyng.h"

/****f* CLI/CMD_check
 * NAME
 *   CMD_check -- check incoming orders.
 * FUNCTION
 *   Check incoming orders and create a forecast of the
 *   situation at the next turn.
 * INPUTS
 *   Orders come in via stdin. The forecast is mailed directy to the player.
 *   Orders are assumed to have a proper mailheader, that is start with:
 *      To: <player>@theaddress
 *      Subject:  orders [turn number]
 *   This header can be produced with formail (see .procmailrc file).
 * RESULTS
 *   Orders are stored in
 *   $GALAXYNGHOME/orders/<game name>/<race name>.<turn number>
 *   Forecast is mailed to the player.
 *   A log is kept of all order processing in log/orders_processed.txt
 * SOURCE
 */


int
CMD_webcheck( int argc, char **argv, int kind) {
  int result;
  char *logName;
  char *forecastName;
  char *returnAddress;
  char *raceName;
  char *password;
  char *final_orders;
  game *aGame;
  FILE *forecast;
  player *aPlayer;
  
  int resNumber, theTurnNumber;
  
  result = FALSE;
  
  logName = createString("%s/log/orders_processed.txt", galaxynghome);
  openLog(logName, "a");
  free(logName);
  
  plogtime(LBRIEF);
  if (argc >= 2) {
    raceName = NULL;
    password = NULL;
    final_orders = NULL;
    aGame = NULL;
    resNumber = areValidOrders(stdin, &aGame, &raceName,
			       &password, &final_orders, &theTurnNumber);
    plog(LBRIEF, "game %s\n", aGame->name);
    
    if (resNumber == RES_OK) {
      aPlayer = findElement(player, aGame->players, raceName);
      aPlayer->orders = NULL;
      
      plog(LBRIEF, "Orders from %s\n", returnAddress);
      
      /* produce an XML forecast */
      if (aPlayer->flags & F_XMLREPORT) {
	if ((theTurnNumber == LG_CURRENT_TURN) ||
	     (theTurnNumber == (aGame->turn) + 1)) {
	  forecastName = createString("%s/NG_XML_%d_forecast",
				       tempdir, getpid());
	  copyOrders(aGame, stdin, raceName, password, final_orders,
		      aGame->turn + 1);
	  if ((forecast = fopen(forecastName, "w")) == NULL) {
	    plog(LBRIEF, "Could not open %s for forecasting\n",
		  forecastName);
	    fprintf(stderr,"Could not open %s for forecasting\n",
		    forecastName);
	    return EXIT_FAILURE;
	  }
	  
	  checkOrders(aGame, raceName, forecast, F_XMLREPORT);
	  
	  fclose(forecast);
	  if (kind == CMD_CHECK_REAL) {
	    printf("%s", forecastName);
	  }
	  else {
	    char *forecastFile;
	    forecastFile =
	      createString("%s/forecasts/%s/%s_XML",
			    galaxynghome, argv[2],
			    returnAddress);
	    GOS_copy(forecastName, forecastFile);
	  }
	  result |= GOS_delete(forecastName);
	  free(forecastName);
	}
      }
      
      /* produce a text forecast */
      if (aPlayer->flags & F_TXTREPORT) {
	if ((theTurnNumber == LG_CURRENT_TURN) ||
	     (theTurnNumber == (aGame->turn) + 1)) {
	  forecastName = createString("%s/NG_TXT_%d_forecast",
				       tempdir, getpid());
	  if ((forecast = fopen(forecastName, "w")) == NULL) {
	    plog(LBRIEF, "Could not open %s for forecasting\n",
		  forecastName);
	    return EXIT_FAILURE;
	  }
	  
	  if (aPlayer->orders == NULL)
	    copyOrders(aGame, stdin, raceName, password, final_orders,
			aGame->turn + 1);
	  
	  checkOrders(aGame, raceName, forecast, F_TXTREPORT);
	  
	  fclose(forecast);
	  
	  if (kind == CMD_CHECK_REAL) {
	    printf("%s", forecastName);
	  } else {
	    char *forecastFile;
	    forecastFile = createString("%s/forecasts/%s/%s_TXT",
					galaxynghome, argv[2],
					returnAddress);
	    GOS_copy(forecastName, forecastFile);
	  }
	  result |= GOS_delete(forecastName);
	  free(forecastName);
	}
      }
      
    }
    else {
      forecastName = createString("%s/NG_TXT_%d_errors",
				   tempdir, getpid());
      forecast = fopen(forecastName, "w");
      plog(LBRIEF, "Major Trouble %d\n", resNumber);
      
      generateErrorMessage(resNumber, aGame, raceName,
			    theTurnNumber, forecast);
      fclose(forecast);
      
      if (kind == CMD_CHECK_REAL) {
	printf("%s", forecastName);
      } else {
	char *forecastFile;
	forecastFile =
	  createString("%s/forecasts/%s/%s_ERR",
			galaxynghome, argv[2], returnAddress);
	GOS_copy(forecastName, forecastFile);
	printf("%s", forecastName);
      }
      free(forecastName);
    }
    
    /* code here for advanced orders, we need to see how to determine this */
    if (theTurnNumber > (aGame->turn+1)) {
      
      if (aPlayer->orders == NULL)
	copyOrders(aGame, stdin, raceName, password, final_orders,
		    theTurnNumber);
      
      if (final_orders) {
	plog(LBRIEF, "%s turn %d advance finalorders received for %s.\n",
	      aGame->name, theTurnNumber, raceName);
      }
      else {
	plog(LBRIEF, "%s turn %d advance orders received for %s.\n",
	      aGame->name, theTurnNumber, raceName);
      }
      
      if (aPlayer->flags & F_XMLREPORT) {
	forecastName = createString("%s/NG_XML_forecast", tempdir);
	forecast = fopen(forecastName, "w");
	
	fprintf(forecast,
		 "<galaxy>\n  <variant>GalaxyNG</variant>\n");
	fprintf(forecast, "  <version>%d.%d.%d</version>\n",
		 GNG_MAJOR, GNG_MINOR, GNG_RELEASE);
	fprintf(forecast, "  <game name=\"%s\">\n", aGame->name);
	fprintf(forecast, "    <turn num=\"%d\">\n", theTurnNumber);
	fprintf(forecast, "      <race name=\"%s\">\n", raceName);
	fprintf(forecast, "        <message>\n");
	fprintf(forecast, "          <line num=\"1\">"
		 "O wise leader, your orders for turn %d</line>",
		 theTurnNumber);
	fprintf(forecast, "          <line num=\"2\">"
		 "have been received and stored.</line>");
	fprintf(forecast, "        </message>\n");
	fprintf(forecast, "      </race>\n");
	fprintf(forecast, "    </turn>\n");
	fprintf(forecast, "  </game>\n");
	fprintf(forecast, "</galaxy>\n");
	fclose(forecast);
	if (kind == CMD_CHECK_REAL) {
	  printf("%s", forecastName);
	} else {
	  char *forecastFile;
	  
	  forecastFile =
	    createString("%s/forecasts/%s/%s_XML",
			  galaxynghome, argv[2], returnAddress);
	  GOS_copy(forecastName, forecastFile);
	}
	result |= GOS_delete(forecastName);
	free(forecastName);
      }
      
      if (aPlayer->flags & F_TXTREPORT) {
	if (aPlayer->orders == NULL)
	  copyOrders(aGame, stdin, raceName, password, final_orders,
		      theTurnNumber);
	forecastName = createString("%s/NG_TXT_forecast", tempdir);
	forecast = fopen(forecastName, "w");
	fprintf(forecast, "O wise leader your orders for turn %d "
		 "have been received and stored.\n", theTurnNumber);
	fclose(forecast);
	if (kind == CMD_CHECK_REAL) {
	  printf("%s", forecastName);
	}
	else {
	  char *forecastFile;
	  
	  forecastFile =
	    createString("%s/forecasts/%s/%s_TXT",
			  galaxynghome, argv[2], returnAddress);
	  GOS_copy(forecastName, forecastFile);
	}
	
	result |= GOS_delete(forecastName);
	free(forecastName);
      }
    }
  }
  
  if (raceName)
    free(raceName);
  if (password)
    free(password);

  result = (result) ? EXIT_FAILURE : EXIT_SUCCESS;
  
  return result;
}
