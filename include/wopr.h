#ifndef GNG_WOPR_H
#define GNG_WOPR_H


#define READING_NONE   0
#define READING_TYPES  1
#define READING_GROUPS 2

game *wopr_createGame(  );

shiptype *wopr_createShiptype( char *name, double drive,
                               int attacks, double weapons, double shields,
                               double cargo );

void wopr_allies( game * aGame, char *playerName1, char *playerName2 );

int wopr_battle( int argc, char **argv );

player *wopr_addPlayer( game * aGame, char *name );

int parse_group( game * aGame, player * aPlayer );

int parse_type( game * aGame, player * aPlayer );

int wopr_parse_scenario( FILE * scenario, game * aGame );

void wopr_usage(  );

#endif /* GNG_WOPR_H */
