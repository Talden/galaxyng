#include "galaxy.h"

/****f* GalaxyNG/usage
 * NAME
 *   usage -- print usage info.
 *******
 */

void
usage()
{
	printf("%s\n", vcid);
	printf("Usage: galaxyng <command> <parameters> <options>\n"
		   "\nCommands Available:\n"
		   " General Commands\n"
		   "   -template   <game name> <number of players>\n"
		   "   -create     <specifcation file>\n"
		   "   -mail0      <game name>\n"
		   "   -check\n"
		   "   -run        <game name> <file with all orders> [turn]\n"
		   "   -score      <game name>\n"
		   "   -toall      <game name>\n"
		   "   -relay\n"
		   "   -hall       <game name>\n"
		   "   -lastorders <game name> [turn]\n"
		   "   -players    <game name> [turn]\n"
		   "   -teaminfo   <game name> <turn> <team number>\n");
	
	printf(" Debug commands\n"
		   "   -dummyrun   <game name> <file with all orders> [turn]\n"
		   "   -dummymail0 <game name>\n"
		   "   -dummycheck <game name> <file with all orders> [turn]\n"
		   "   -test       <game name>\n"
		   " Experimental Commands\n"
		   "   -teaminfo   <game name> <turn> <team number>\n"
		   "   -graph      <game name> [turn]\n"
		   "   -map        <game name> [turn]\n"
#if defined(DRAW_INFLUENCE_MAP)
		   "   -influence  <game name> <type> [turn]\n"
		   "               (<type> is all, industry, attack, defend)\n"
#endif		   
		   "   -gnuplot    <game name> [turn]\n");
	printf("\nExplanation:\n"
		   " -template   - create a template .glx file for use with -create.\n"
		   " -create     - create a new game.\n"
		   " -mail0      - mail the turn 0 reports.\n"
		   " -check      - check incoming orders, orders are read from stdin.\n");
	printf(" -run        - run a game and mail the turn reports.\n"
		   " -score      - creates highscore list in HTML format.\n"
		   " -relay      - relay email between players,"
		   " orders are read from stdin.\n"
		   " -hall       - create information for the Hall of Fame.\n"
		   " -dummyrun   - run a game but do not mail the turn reports.\n");
	printf(" -dummycheck - check orders, but do not mail the forecast.\n"
		   "               orders are read from stdin.\n"
		   " -dummymail0 - create the turn 0 reports, but do not email them.\n"
		   " -test       - test the integrity of a game file.\n"
		   " -teaminfo   - create an info report for a team captain\n"
		   " -graph      - dump game data for graph creation.\n"
		   " -map        - dump ASCII game map.\n");
	printf(" -influence  - create influence map(s). The available maps are\n"
		   "               Effective Industry, Attack Strength, Defense "
		   "Strength\n"
		   " -lastorders - list the turn when players last sent in orders.\n"
		   " -players    - list address and password of all players.\n");
}