m4_include(`wwwbase.m4')m4_dnl
m4_include(`general.m4')m4_dnl
DocStart
AHeader(`Hall Of Fame')
BodyStart
m4_include(`hallnavigator.m4')m4_dnl
ATitle(`Hall Of Fame')

ASection(`The Hall Of Fame')

<P> ALink(`hall.html', `The Hall Of Fame'), it is based on the results
of over 100 games.  </P>


ASection(`Scoring Method')

<P>The Hall of Fame (HOF) is based on victory points. Whenever a game
finished the top players are awarded victory points.  If a player wins
several games his or her victory points are added.
</P>

<P> How many victory points a player gets depends on the size of the
game and on the position in the hitlist of the last and final turn.
The hitlist shows the ranking of the players based on their effective
industry (1/4*(Pop-Ind)+Ind). </P>

<P> Based on this the victory points are computed as follows, if a
game started with N players:</P>
<UL>
  <LI>Player number 1 gets N victory points</LI>
  <LI>Player number 2 gets N/2 victory points</LI>  
  <LI>Player number 3 gets N/3 victory points</LI>
  <LI>etc</LI>
</UL>
<P>
Only the first N/2 active players get points. 
</P>

<P>To keep the list clean you only get points when your full name (or
alias) is known. </P>

<P>You can have a look at the ALink(`galaxybase', `database') to see
if you have lost some points.  The database contains the full
information about all the games that are listed in the hall of fame.
Players of whom the full name is not known are commented out with a
"#". If you are commented out, send me an email fslothouber@acm.org,
and you will be awarded the points.  Send a turn report as proof.</P>

<P>This ALink(`HallOfFame.c', `program') is used to compute the hall of fame
from the database.</P> 


ASection(`Special Games')

<UL>
<LI>TIGER (1998-1999) 
<P>Tiger is a special game, a team game between
players from the former soviet union (FSU) and players from the rest
of the world (ROW). The game was won by the FSU team.
The results of this game can not be used for 
the HOF. However it of course needs mentioning.
<OL>
  <LI>ALink(`Tiger/players.html', `List if Players')</LI>
  <LI>ALink(`Tiger/hitlist.html', `Hitlist Final Turn')</LI>
  <LI>ALink(`Tiger/index.html', `Graphs with the economic histroy of each player')</LI>
<LI>ALink(`Tiger/map.gif', `The map of the galaxy')</LI>
</OL>
</P></LI>
<LI>Tiger3 (2001-2001)
<P>The 3rd team game between players from the former soviet union (FSU) and
players from the rest of the world (ROW).  The game was won by the FSU
team.  Some interesting statistics:
<OL>
  <LI>ALink(`Tiger/tiger3effind.html', 
            `The effective industry per team.')</LI>
  <LI>ALink(`Tiger/tiger3ships.html', 
            `The number of ships build per team.')</LI>
</OL>
<P>
</UL>

BodyEnd
DocEnd
