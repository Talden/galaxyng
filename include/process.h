#ifndef GNG_PROCESS_H
#define GNG_PROCESS_H

#include "galaxy.h"
#include "list.h"
#include "util.h"
#include "savegame.h"
#include "loadgame.h"
#include "phase.h"
#include "battle.h"
#include "report.h"
#include "selftest.h"

#ifdef WIN32
#include <stdarg.h>
#include <stdio.h>
/* #include <varargs.h> */
#endif

/* $Id$ */


/****s* GalaxyNG/orderinfo
 * NAME
 *   orderinfo
 * PURPOSE
 *   map a order name to its function
 * SOURCE
 */

typedef struct _orderinfo orderinfo;

struct _orderinfo {
  char           *name;
  void            (*func) (game *aGame, player *, strlist **);
};

/******/

/****d* GalaxyNG/RESCODES
 * NAME
 *   RESCODES -- Error Codes for the orders checker function 
 * SOURCE
 */

#define RES_OK            0
#define RES_NO_ORDERS     1
#define RES_ERR_GALAXY    2
#define RES_NO_GAME       3
#define RES_PASSWORD      4
#define RES_PLAYER        5
#define RES_TURNRAN       6
#define RES_DESTINATION   7
#define RES_NODESTINATION 8

/**********/


#define ORDER_SIZE 1

/* order functions */

void            at_order(game *aGame, player *, strlist **);
void            eq_order(game *aGame, player *, strlist **);    /* FS
                                                                 * 
                                                                 * * * *
                                                                 * * * *
                                                                 * * * * * 
                                                                 * * * * * 
                                                                 * * * * * 
                                                                 * *
                                                                 * 12/1999 
                                                                 * * * * * 
                                                                 * * */
void            a_order(game *aGame, player *, strlist **);
void            b_order(game *aGame, player *, strlist **);
void            c_order(game *aGame, player *, strlist **);
void            d_order(game *aGame, player *, strlist **);
void            e_order(game *aGame, player *, strlist **);
void            f_order(game *aGame, player *, strlist **);
void            g_order(game *aGame, player *, strlist **);
void            h_order(game *aGame, player *, strlist **);     /* CB-1990923 
                                                                 * 
                                                                 * * * *
                                                                 * * * *
                                                                 * * * * * 
                                                                 * * * *
                                                                 * * */
void            i_order(game *aGame, player *, strlist **);
void            j_order(game *aGame, player *, strlist **);

/* free k */
void            l_order(game *aGame, player *, strlist **);
void            m_order(game *aGame, player *, strlist **);
void            n_order(game *aGame, player *, strlist **);
void            o_order(game *aGame, player *, strlist **);
void            p_order(game *aGame, player *, strlist **);
void            q_order(game *aGame, player *, strlist **);
void            r_order(game *aGame, player *, strlist **);
void            s_order(game *aGame, player *, strlist **);
void            t_order(game *aGame, player *, strlist **);
void            u_order(game *aGame, player *, strlist **);
void            v_order(game *aGame, player *, strlist **);
void            w_order(game *aGame, player *, strlist **);
void            x_order(game *aGame, player *, strlist **);
void            y_order(game *aGame, player *, strlist **);
void            z_order(game *aGame, player *, strlist **);
void            mistake(player *P, strlist *s, char *format, ...);

void
                copyOrders(game *aGame,
                           FILE * orders,
                           char *nationName, char *password,
                           int theTurnNumber);

int
                areValidOrders(FILE * ordersFile,
                               game **aGame,
                               char **nationName, char **password,
                               int theTurnNumber);

void
                preComputeGroupData(game *aGame);

void
                removeDeadPlayer(game *aGame);

int
                getTurnNumber(FILE * orders);

char           *getReturnAddress(FILE * orders);

char           *getDestination(FILE * orders);

void
                doOrders(game *aGame,
                         player *aPlayer, orderinfo *orderInfo, int phase);

int
                runTurn(game *aGame, char *ordersFileName);

void
                checkOrders(game *aGame,
                            char *nationName, FILE * forecast);

void
                generateErrorMessage(int resNumber,
                                     game *aGame,
                                     char *nationName,
                                     int theTurnNumber, FILE * forecast);

#endif                          /* GNG_PROCESS_H */
