m4_include(`wwwbase.m4')m4_dnl
m4_include(`general.m4')m4_dnl
DocStart
AHeader(`Introduction to GalaxyNG')
BodyStart
m4_include(`navigator.m4')m4_dnl

ATitle(`Introduction to GalaxyNG')

www_section(`gng', `Galaxy Next Generation')

<p>Galaxy has been around for a while, it's a great, well balanced, and
addictive game, but it can be improved since:</p>

<OL>
  <LI>The game can be slow, dragging on for more than 100 turns, without
  coming to a conclusion.</LI>

  <LI>The algorithm that generates the layout of the galaxy, that
  is the position of the planets, is rather arbitrary, leaving some
  players in very disadvantagous positions.</LI>

  <LI>The code contains core dump producing bugs, and is hard to maintain.
  </LI>
</OL>

<P>
Galaxy Next Generation tries to solve these problems these
problems.
</P>


www_subSection(`crw', `Code Rewrite')

<P>
About 70 percent of the orginal galaxy code was rewritten. This solved
a number of bugs that cause the code to core dump. The code is still a bit
of a mess though. Someday someone with a lot of spare time should completely
rewrite it in C++ :)
</P>

<P>
The bug fixes also causes GalaxyNG to behave slightly different from
Galaxy. That is:</P>
<UL>
  <LI><B>Upgrading very large ships:</B> 
  <P>
  There was a bug that prevented very large ships from being
  upgraded. To be more specific; when you had <B>one</B> very large ship
  orbiting a planet, and that planet's industry was not enough
  for a full upgrade, the ship would not be upgraded at all, even
  worse, even though no upgrade took place, the program still
  marked all industry points of that planet as spend.
  This bug has been fixed; the ship will now be partially
  upgraded.  All tech-levels will be increased by an equal amount,
  depending on the available industry.
  More practical; one can build mass 10,000 ships and keep
  them in service until eternity by upgrading them.
  </P>
  </LI>

  <LI><B>Bombing of planets:</B>
  <P>
  There was a bug that prevented armed ships that had been given a Send
  order, from bombing the planet they were orbiting before the
  hyper-space jump.
  This bug has been fixed and it is now possible to bomb two planets
  in the same turn, with the same ship or fleet.  Take a look at the 
  ALink(`NonM4/FAQ.html#4.1', `FAQ') to see how this is done.
  </P>
  </LI>

  <LI><B>Production Bug</B>.
  <P>
  There was a bug that prevented some ships from being build on a
  planet, even though it had enough industry and in particular enough
  material.
  The cause of this bug was that the program did not take in
  account that having material stock piled frees industry points
  that otherwise would have to be spend on building material.
  This bug has been fixed.
  </P>
  </LI>

  <LI><B>AUTOUNLOAD option</B>
  <P>
  Auto unload option does not work with empty planets, that is
  when you send cargo ships to a empty planet you have to manually
  unload it.  Which is silly since when you use routes galaxy
  automatically unloads cargo on empty planets.
  This bug is fixed. You can send cargo
  ships to an empty planet any cargo they carry is automatically
  unloaded upon arrival.  That is provided you activated the
  Autounload option.
  Of course cargo is also automatically unloaded to planets a player
  owns. However no auto unload takes place to planet's of other nations.
  </P>
  </LI>
</UL>


www_section(`chngs', `Changes to the Original Rules')

<P>These are the changes to the standard rules of Galaxy:</P>
<OL>

  <LI><B>Cargo:</B>
  <P>One can unload any type of cargo unto and from the planets of other
  nations.</P></LI>

  <LI><B>Bombing:</B> 
  <P>
  When a player bombs an enemy planet that player become the owner of
  that planet.  The industry and population and reduced to 25% of their
  current value.
  </P>

  <P>
  You will ask, who gets the planet when two
  friendly nations have ships above the same planet?  Normally this is
  the nations that comes first in the list with nations (as shown in the
  turn report).  This is unfair of course, allies will like to divide
  the planets they conquer amongst each other.  This is possible with a
  new command.  It has the following syntax:
  </P> 
  <PRE>
      V [planet_name]
  </PRE>

  <P>
  and is used to indicate that a player claims ownership of a planet
  when it is bombed. It of course only works when the player has ships
  left above the planet when it is bombed.  In case 2 or more nations
  claim the same planet, nobody gets the planet.
  </P>
  </LI>
</OL>

www_section(`newmap', `New Map Layout')

<P>
What was wrong with the original layout used in galaxy? Sometimes the
layout created that left some nations in rather unfair positions,
that is, some nations would have their home planet located far away
from other planets, while others nations home planets were located
near a whole bunch of good planets.  The new code tries to provide all
player with an equal chance on success, while still keeping the game
diverse and interesting.  How is this accomplished:
</P>
<OL>
  <LI><B>empty planets:</B>
  <P>
  Each nation is given the same number of planets empty planets.  That
  is within a circle of a given radius around the home planet of a
  nation a fixed number of planets is randomly allocated. The size of
  these planets differ but the total sum of the sizes is the same for
  all nations.  The resources of the planets are still chosen at random.
  Though experience shows that the total ship mass the planets can
  produce is about the same for all nations.
  </P>
  </LI>

  <LI><B>Home Planet Spacing:</B>
  <P>
  The minimum distance between home world can be specified. Home worlds
  can therefore be widely spaced from each other, ensuring that a nation
  isn't kicked out in the first few turns. 
  </P>
  </LI>

  <LI><B>Stuff Planets:</B>
  <P>
  To improve the tactical possibilities a number of stuff planets can
  be scattered across the galaxy.  These are small useless planets that
  provide players with different routes of attack.
  </P>
  </LI>

  <LI><B>Additional Home Planets:</B>
  <P>
  In addition it is possible to let nations start with more than one
  home planet, these are located within a radius of 3 ly from the
  original home planet of the nations. Starting with multiple
  home planets speeds up the game considerably.
  </P>
  </LI>
</OL>


www_section(`ocfore', `Orders Checker and Forecaster')

<P>
The orders checker has been intergrated with the game code, so both
will use the same algorithm and produce the same results.  The orders
checker has also been extended with a forecasted, which generates a
forecast on the sitation of the planets and groups as it will be the
next turn.
</P>

BodyEnd
DocEnd






