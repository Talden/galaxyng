<?php echo '<?xml version="1.0" encoding="UTF-8"?>'; ?> 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
   "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US">

<!-- $Id$ -->

	<head>
		<link rel="stylesheet" href="main.css" />
		<title>GalaxyNG Players' Manual</title>
	</head>

	<body>
		<h1>Galaxy Next Generation Players' Manual</h1>



			<h2><a link="toc">Table of Contents</a></h2>
				<ol>
					<li><a href="#intro">Introduction</a>
						<ol>
							<li><a href="#galaxy">The Galaxy</a></li>
							<li><a href="#names">Names</a></li>
							<li>Victory and Defeat</li>
						</ol>
					</li>
					<li>Planets
						<ol>
							<li>Owner</li>
							<li>Size</li>
							<li>Population</li>
							<li>Industry</li>
							<li>Resources</li>
							<li>Stockpiles</li>
						</ol>
					</li>
					<li>Ships
						<ol>
							<li>Ship Types</li>
							<li>Groups</li>
							<li>Fleets</li>
							<li>Technology</li>
							<li>Ship Mass</li>
							<li>Movement
							<li>Speed</li>
							<li>Locating Ships</li>
							<li>Cargo</li>
							<li>Routes</li>
						</ol>
					</li>
					<li>Production
						<ol>
							<li>Materials</li>
							<li>Capital</li>
							<li>Technology</li>
							<li>Ships</li>
						</ol>
					</li>
					<li>Combat
						<ol>
							<li>War and Alliances</li>
							<li>Conquering Planets</li>
						</ol>
					</li>
					<li>Orders
						<ol>
							<li>Sending Orders</li>
							<li>Advance Orders</li>
						 <li>Example Sets of Orders</li>
						 <li>Order Format</li>
						 <li>@ [race...]</li>
						 <li>= &lt;your real name&gt;</li>
						 <li>A &lt;race&gt;</li>
						 <li>B &lt;group&gt; &lt;number of ships&gt;</li>
						 <li>...</li>
						 <li>Things to Note</li>
						 <li>Fleet Orders</li>
						</ol>
					</li>
					<li>Turns</li>
					<li>A Few Things to Note</li>
					<li>Inactivity</li>
					<li>Turn Reports
						<ol>
							<li>Your Options</li>
							<li>Messages</li>
							<li>Mistakes</li>
							<li>Status of Players</li>
							<li>...</li>
							<li>Getting a Copy of Your Turn Report</li>
						</ol>
					</li>
					<li>Hints and Tips</li>
					<li>Links to More Information</li>
				</ol>



			<h2><a link="intro">Introduction</a></h2>
				<p>GalaxyNG is a multiplayer game of interstellar war.  Each player is the leader of one race.  The objective of the game is to conquer the galaxy.</p>
				<p>Players email a GalaxyNG server to <a href="#register">register</a> for games, submit <a href="#orders">orders</a> and receive <a href="#reports">turn reports</a>.  The server automatically processes turns and responds to player email.  Most games run one to five <a href="#turns">turns</a> per week.  The Game Master (GM) maintains the server, selects game options, creates the galaxy, answers player questions and solves problems.</p>

				<h3><a link="galaxy">The Galaxy</a></h3>
					<p>The area of the galaxy in which the game is played is a square (for the sake of simplicity the third dimension is ignored) which contains a number of habitable planets.  Each race starts off occupying one or more planets which can build ships, conduct technology research, produce capital or produce materials.  Ships are used to explore, colonize uninhabited planets, haul cargo, conduct warfare and conquer planets inhabited by other races.  Technology improvements allow ships to fly faster and farther, haul more cargo and fight better.</p>
					<p>Distances are measured in light-years.  Each unit of population represents ten million people and each unit of goods or raw materials represents about ten million tons.  Each turn represents about four years of time.</p>

				<h3><a link="names">Names</a></h3>
					<p>Races, planets and ship types can be named.  Names may be no more than twenty characters (a character is a letter, digit, or underscore) and may not include spaces.  Each player should <a href="#ordc">provide a name</a> by which their race will be known, e.g. Mutant_Camels or Zzyaxians - if this is not done they will simply be known by number, e.g. Race_4 or Race_5.  Ship types are given names when <a href="#ordd">designed</a> and can be <a href="#ordt">renamed</a>.  Planets are numbered at the start of the game and can be <a href="#ordn">renamed</a> by their current owner.</p>

				<h3><a link="victory">Victory and Defeat</a></h3>
					<p>The game can be won by a single race or by an alliance of races, depending upon the game settings.  Races are ranked based on the total production of their planets.  A race is eliminated if it owns no planets and has no ships.  The game is complete when all surviving players agree to end it and notify the game master.</p>



			<h2><a link="planets">Planets</a></h2>
					<p>Planets are located in the galaxy by X and Y coordinates.  Planets have seven characteristics: owner, size, population, industry, resources, production and stockpiles.</p>

				<h3><a link="owner">Owner</a></h3>
					<p>Inhabited planets are owned by one race at a time (except in the special case of a standoff when an inhabited planet is unowned).  Uninhabited planets are not owned by any race.</p>

				<h3><a link="size">Size</a></h3>
					<p>Planets vary in size from 0.01 to 1000.00.  The size of a planet reflects the habitability of the terrain, the suitability of the climate for agriculture, and other features.  At the beginning of the game, the galaxy is divided into inhabited planets (home planets), uninhabited development planets (size 200.00 to 1000.00) and uninhabited stuff planets (size 0.01 to 200.00).</p>

				<h3><a link="pop">Population</a></h3>
					<p>Each inhabited planet has a population, which can never be larger than the planet's size but may be smaller.  A planet with zero population is uninhabited.  Home planets are fully populated at the beginning of the game.  Each planet's population grows by 8% each turn.</p>

				<h3><a link="ind">Industry</a></h3>
					<p>Each inhabited planet has industry, which can never be larger than the planet's population but may be smaller.  If population exceed industry, the industry may be increased by adding capital.  If there is not an existing stockpile of capital, it may be <a href="#ordp">produced</a> at the planet or be shipped in from another planet by cargo ships.  For example, if a size 500 planet with 500 population and 200 industry produces 75 units of capital, the industry will increase to 275.  If a size 500 planet with 200 population and 200 industry has a stockpile of 100 capital, on the following turn the population and industry will both increase to 216 and there will be 84 units of capital left (because population grows by 8% per turn).</p>

				<h3><a link="res">Resources</a></h3>
					<p>Each planet has a resources value which indicates how rich it is in metals, coal, oil, wood and other products.  Planets high in resources can easily <a href="#ordp">produce</a> materials such as sheet steel, copper wire and plastics.  Home planets have a resources value of 10.00.  Other planets have a resources value between 0.01 and 10.00, with the average being 1.00.  The resources value equals the number of units of materials that will be produced per point of production devoted to the task.  A planet with 5.00 resources will produce 5.00 units of materials per point of production, while a planet with 0.10 resources would only produce 0.10 units of materials per point of production.  Materials are necessary to build ships and produce capital.</p>

				<h3><a link="stock">Stockpiles</a></h3>
					<p>Each planet may have stockpiles of colonists, capital and materials.  Population increases beyond the planet's size are converted into colonists.  Eight population units are converted into one unit of colonists.  These are people automatically stored in containers in deep freeze.  Excess units of capital and materials are stockpiled at a one-to-one ratio.  Stockpiles may be saved for later use or transported to other planets by cargo ships.</p>



			<h2><a link="ships">Ships</a></h2>
				<p>Ships are organized into groups and fleets which are used for exploration, scouting, attack, defence and cargo transport.  Ships have the following characteristics: ship type (name, drive mass, attacks, weapons mass, shields mass, cargo mass and ship mass), group number, fleet name, drive technology, weapons technology, shields technology, cargo technology, cargo carried type, cargo carried mass, destination planet, and distance to destination planet.  Ships can be <a href="#ordp">built</a> at planets.</p>

				<h3><a link="shiptypes">Ship Types</a></h3>
					<p>Each player can <a href="#ordd">design</a> ship types, which are unique to that player, by specifying: name, drive mass (the power of the hyperdrive engines), attacks (the number of guns), weapons mass (the strength of the guns), shields mass (the power of the shields generator), and cargo mass (the size of the cargo bay).  Drive mass, weapons mass, shields mass, and cargo mass must equal zero or be equal to or greater than one.  Thus, drive mass 0.00 and 1.50 are allowed but drive mass 0.75 is not.  Attacks must be an integer.  Some example ship types are:<p>
					<pre>                    D    A     W      S      C
  Drone            1.00   0   0.00   0.00   0.00
  Flak             1.00   0   0.00   2.00   0.00
  FastFlak         1.01   0   0.00   1.01   0.00
  Fighter          2.48   1   1.20   1.27   0.00
  Gunship          4.00   2   2.00   4.00   0.00
  Destroyer        6.00   3   4.00   4.00   0.00
  Cruiser         16.50  30   1.50   9.75   0.00
  BattleCruiser   49.50  25   3.00   9.50   1.00
  Battleship      33.00   3  25.00  16.00   1.00
  BattleStation   99.00   1  50.00  49.00   0.00
  OrbitalFort      0.00  11  10.00  39.00   0.00
  SpaceGun         0.00   1   9.90   9.90   0.00
  Hauler           2.00   0   0.00   0.00   1.00
  Freighter       30.00   0   0.00   9.50  10.00
  MegaFreighter  120.00   0   0.00  38.43  39.57</pre>

				<h3><a link="groups">Groups</a></h3>
					<p>A race can have hundreds or even thousands of ships, which would be inconvenient to handle individually.  Hence ships are handled in groups, which can contain one or more ships all of the same type, in the same place, carrying the same quantity and type of cargo (if any) and built with the same technology levels.</p>
					<p>Groups can be ordered to <a href="#ords">travel</a> to another planet, <a href="#ordi">intercept</a> other ships, <a href="#ordh">reverse</a> course, <a href="#ordb">break</a> off ships into a new group, <a href="#ordj">join</a> a fleet, <a href="#ordb">leave</a> a fleet, <a href="#ordg">upgrade</a> technology levels, <a href="#ordl">load</a> cargo, or <a href="#ordu">unload</a> cargo.  Groups may also be <a href="#ordx">scrapped</a>.  Groups can also <a href="#routes">routed</a>.</p>
					<p>Each group is assigned a number, which is used to issue orders to ships in the corresponding group.  When new groups are created, they are assigned a number N+1, where N is the highest numbered group in existence.  Whenever a group number is required as an order parameter, the keyword MAX may be used instead. This will apply the order to the group with the highest group number, i.e. the most recently created group.</p>
					<p>In several phases of the turn, groups containing identical ships, carrying identical cargo (if any), in the same place and in the same fleet (if applicable) will be merged using the lower group number.  For example, if group 5 containing 48 ships is merged with group 12 containing 52 ships, group 5 will contain 100 ships and group 12 will be eliminated.</p>
					<p>If the SortGroups <a href="#ordo">option</a> is turned on, at the end of each turn groups will be automatically sorted and renumbered as follows: Owner's groups at owner's planets; Owner's groups at other race's planets; Owner's groups at uninhabited planets; Owner's groups in fleets.</p>

				<h3><a link="fleets">Fleets</a></h3>
					<p>Fleets contain groups, allowing players to gather different ship types together in a single unit.  Many of the orders for groups can also be used for fleets.  Players can <a href="#ordd">create</a>, <a href="#orde', 'erase</a>, <a href="#ordj">merge</a> and <a href="#ordt">rename</a> fleets.  Fleets can be ordered to <a href="#ords">travel</a> to another planet, <a href="#ordi">intercept</a> other ships, or <a href="#ordh">reverse</a> course.  The slowest group in the fleet sets the maximum speed for the entire fleet.</p>
					<p>A group in a fleet that is given a <a href="#ords">send</a> or <a href="#ordi">intercept</a> order is automatically removed from the fleet.  Ships in a fleet that are <a href="#ordb', 'broken</a> from groups are also removed from the fleet.  Groups in fleets that are ordered to <a href="#ordg">upgrade</a>, <a href="#ordl">load</a> or <a href="#ordu">unload</a> cargo remain in the fleet.  Groups in fleets will not travel on <a href="#routes">routes</a>.</p>

				<h3><a link="tech">Technology</a></h3>
					<p>Technology determines the effectiveness of ships.  There are four technologies: drive, weapons, shields and cargo.  Each race begins the game with 1.00 levels in each technology.  Technology can be increased by ordering planets to conduct <a href="#ordp">research</a>.</p>
					<p>A ship with drive technology 4.00 is twice as fast as an equivalent ship with drive technology 2.00, a ship with weapons technology 1.50 has a 50% more powerful attack than the same ship with weapons technology 1.00, and so forth.  Ships without a component are considered to have a matching technology of zero.  For example, a ship with weapons mass zero is consdered to have weapons technology zero.</p>
  
  			<h3>Ship Mass</h3>
					<p>Ship types with zero or one attack have a ship mass of drive mass + weapon mass + shield mass + cargo mass.  Each additional attack beyond the first adds 50% of the weapons mass to the ship mass.  For example:</p>
					<pre>                    D   +     W   +    Additional    +     S   +   C   =  Ship
                                        Attacks                           Mass
  Drone            1.00 +    0.00 +        0         +    0.00 +  0.00 =   1.00
  Flak             1.00 +    0.00 +        0         +    2.00 +  0.00 =   3.00
  FastFlak         1.01 +    0.00 +        0         +    1.01 +  0.00 =   2.02
  Fighter          2.48 +    1.20 +        0         +    1.27 +  0.00 =   4.95
  Gunship          4.00 +    2.00 + ( 1 *  2.00 / 2) +    4.00 +  0.00 =  11.00
  Destroyer        6.00 +    4.00 + ( 2 *  4.00 / 2) +    4.00 +  0.00 =  18.00
  Cruiser         16.50 +    1.50 + (29 *  1.50 / 2) +    9.75 +  0.00 =  49.50
  BattleCruiser   49.50 +    3.00 + (24 *  3.00 / 2) +    9.50 +  1.00 =  99.00
  Battleship      33.00 +   25.00 + ( 2 * 25.00 / 2) +   16.00 +  1.00 =  99.00
  BattleStation   99.00 +   50.00 +        0         +   49.00 +  0.00 = 198.00
  OrbitalFort      0.00 +   10.00 + (10 * 10.00 / 2) +   39.00 +  0.00 =  99.00
  SpaceGun         0.00 +    9.90 +        0         +    9.90 +  0.00 =  19.80
  Hauler           2.00 +    0.00 +        0         +    0.00 +  1.00 =   3.00
  Freighter       30.00 +    0.00 +        0         +    9.50 + 10.00 =  49.50
  MegaFreighter  120.00 +    0.00 +        0         +   38.43 + 39.57 = 198.00</pre>
  
				<h3><a link="move">Movement</a></h3>
					<p>Ships are equipped with hyperspace drives, except ships with a drive mass of zero which remain forever at the planet where they were built.  Hyperspace travel is only possible from one concentration of mass to another, i.e. from one planet to another.  Ships can only travel at maximum speed in hyperspace, unless they are part of a fleet.  When ships enters hyperspace, no time passes for the ship or those on board; a ship in hyperspace can only go forward or reverse and cannot participate in combat.  <a href="#ords">Send</a>, <a href="#ordi">intercept</a> and <a href="#ordh">reverse</a> orders can be issued to groups and fleets to move them between planets.</p>

				<h3><a link="speed">Speed</a></h3>
					<p>Ships move a number of light years per turn according to the following formula:  Speed = 20 * drive technology * (drive mass / (ship mass + effective cargo carried mass)).</p>
					<p>Note that unless your drive technology is very high, large ships should have correspondingly large drives or they will be very slow.  On the other hand the fastest ships you can possibly build (all numbers except drive mass being zero in the design) can only travel at a speed of twenty times your drive technology.  For example, using the ship types above and assuming drive technology 1.00:<p>
					<pre>                 20 * Drive * (  Drive / (   Ship +   Effective   )) = Speed
                       Tech       Mass       Mass   Cargo Carried
  Drone          20 *  1.00 * (   1.00 / (   1.00 +      0.00     )) = 20.00
  Flak           20 *  1.00 * (   1.00 / (   3.00 +      0.00     )) =  6.66
  FastFlak       20 *  1.00 * (   1.01 / (   2.02 +      0.00     )) = 10.00
  Fighter        20 *  1.00 * (   2.48 / (   4.95 +      0.00     )) = 10.02
  Gunship        20 *  1.00 * (   4.00 / (  11.00 +      0.00     )) =  7.27
  Destroyer      20 *  1.00 * (   6.00 / (  18.00 +      0.00     )) =  6.66
  Cruiser        20 *  1.00 * (  16.50 / (  49.50 +      0.00     )) =  6.66
  BattleCruiser  20 *  1.00 * (  49.50 / (  99.00 +      0.00     )) = 10.00
  Battleship     20 *  1.00 * (  33.00 / (  99.00 +      0.00     )) =  6.66
  BattleStation  20 *  1.00 * (  99.00 / ( 198.00 +      0.00     )) = 10.00
  OrbitalFort    20 *  1.00 * (   0.00 / (  99.00 +      0.00     )) =  0.00
  SpaceGun       20 *  1.00 * (   0.00 / (  19.80 +      0.00     )) =  0.00
  Hauler         20 *  1.00 * (   2.00 / (   3.00 +      0.00     )) = 13.33
  Freighter      20 *  1.00 * (  30.00 / (  49.50 +      0.00     )) = 12.12
  MegaFreighter  20 *  1.00 * ( 120.00 / ( 198.00 +      0.00     )) = 12.12</pre>
					<p>Note that, when fully loaded, cargo ships can be much slower.  For example:</p>
					<pre>  BattleCruiser  20 *  1.00 * (  49.50 / (  99.00 +      1.10     )) =  9.79
  Battleship     20 *  1.00 * (  33.00 / (  99.00 +      1.10     )) =  6.52
  Hauler         20 *  1.00 * (   2.00 / (   3.00 +      1.10     )) =  9.75
  Freighter      20 *  1.00 * (  30.00 / (  49.50 +     20.00     )) =  8.63
  MegaFreighter  20 *  1.00 * ( 120.00 / ( 198.00 +    196.14     )) =  6.09</pre>

				<h3><a link="locate">Locating Ships</a></h3>
					<p>Each race's administrative staff will keep a record of its own ships on planets or in hyperspace.  Planet owners have full knowledge of all ships orbiting their planets.  Players also receive complete reports on ships at planets visited by their own ships.</p>
					<p>Locating alien ships in hyperspace is much more problematic.  Detectors to accurately locate the position of alien ships in hyperspace are installed on each planet.  Accurate readings of mass, speed, origin and distance from destination can be obtained for ships heading directly toward a detector (i.e. inbound to a planet).  A rough indication of the location of other alien groups is indicated on the <a href="#ordm">map</a>, but their mass, speed and direction of travel are unknown.</p>

				<h3><a link="#cargo">Cargo</a></h3>
					<p>Cargo ships can <a href="#ordl">load</a> stockpiles of colonists, capital and materials to <a href="#ords">transport</a> them to other planets where they can be <a href="#ordu">unloaded</a>.  Each ship may only carry one type of cargo at a time.  The base amount of cargo a ship can carry is determined by the following formula: base cargo = cargo mass + cargo mass^2/10.  Thus, at cargo technology 1.00, some examples would be:</p>

					<pre>                 Cargo + Cargo Mass^2/10 =  Base Cargo
                  Mass                        Carried
  BattleCruiser   1.00 +       0.10      =      1.10
  Battleship      1.00 +       0.10      =      1.10
  Hauler          1.00 +       0.10      =      1.10
  Freighter      10.00 +      10.00      =     20.00
  MegaFreighter  39.57 +     156.57      =    196.14</pre>

       <p>Cargo technology increases the amount of cargo that a ship can carry.  Thus, a Hauler with cargo technology 2.00 can carry 2.20 units of cargo and a Freighter with cargo technology 3.00 can carry 60.00 units of cargo.  This does not slow down the ships, as the cargo carried is divided by the cargo technology to obtain the effective cargo carried.  Thus, at cargo technology 3.00, a Freighter carrying 60.00 units of cargo has an effective cargo carried of 20.00, while the same Freighter carrying 35.00 units of cargo has an effective cargo carried of 11.66.</p>

     <h3><a link="#routes">Routes</a></h3>

      <p>Four routes (capital, colonists, materials, and empty) can be <a href="#ordr">established</a> from each planet.  Cargo ships that have not been ordered to load, unload or travel between planets will automatically follow routes.  A route from planet A to B for a particular cargo type means that the computer will try to get that type of cargo from planet A to planet B using all available cargo ships.  Any empty ships at planet A each turn will be loaded with cargo (if any of that type is present on planet A) and sent to planet B.  Any ships at planet A which already are loaded with the appropriate  type of cargo will also be sent to planet B.  Any ships which arrive at planet B carrying that type of cargo (even if they didn't come from planet A) will be automatically unloaded, regardless of the status of the autounload option.  Players can only establish routes from planets that they own, however routes can terminate at any planet at all, so they can be used to ship colonists to uninhabited planets.  Routes are assigned transport ships in the following order of priority:  colonists, capital, materials and empty transports.</p>

			<h2><a link="produce">Production</a></h2>
				<p>The productive capacity of a planet is determined mostly by its industry value and partly by its population.  Each point of industry on a planet yields one production point, and every four points of population over and above industry yields an additional production point.  The formula is: Production = Industry + ((Population - Industry)/4).  A planet with 500.00 industry and 500.00 population has 500.00 production points, while a planet with 250.00 industry and 500.00 population has 312.50 production points.  A planet can be ordered to <a href="#ordp">produce</a> materials, capital, technology research or ships.  Each planet can only perform one type of production each turn.</p>
				
				<h3>Materials</h3>
					<p>Each planet may have a stockpile of materials and if present this will be used.  If no stockpile exists, some production points will be diverted to producing materials.</p>
				
				<h3>Capital</h3>
					<p>A planet's industry level is increased by the production of
capital goods.  These represent things like machine tools, computers
and transport vehicles.  To produce one unit of capital requires 5
production points and 1 unit of raw materials.  If the planet's
industry level is below its population it will then be increased by
one unit.  Otherwise the capital units will be stockpiled.  If shipped
to a planet whose industry level is below its population, that
planet's industry level will be increased.  This is useful for quickly
building up the economy of a colony planet.</p>
				
				<h3>Technology</h3>
					<p>A planet can research one of the four technologies each turn.  It costs 5,000 production points to increase Drive, Weapons, or Shields technology by one point and 2,500 production points to increase Cargo technology by one point.  Fractional increases are effective immediately (e.g. if you spend 500 production points on research into Weapons, your Weapons technology will go up by one tenth of a point).</p>
					
				<h3>Ships</h3>
					<p>A planet can produce one type of ships each turn.  The production cost of a ship is equal to its mass times ten.  In addition, one unit of materials is required for every ten units of production.</p>
					<pre>                    Mass  Production  Materials
  Drone             1.00     10.00       1.00
  Flak              3.00     30.00       1.00
  FastFlak          2.02     20.20       2.02
  Fighter           4.95     49.50       4.95
  Gunship          11.00    110.00      11.00
  Destroyer        18.00    180.00      18.00
  Cruiser          49.50    495.00      49.50
  BattleCruiser    99.00    990.00      99.00
  Battleship       99.00    990.00      99.00
  BattleStation   198.00   1980.00     198.00
  OrbitalFort      99.00    990.00      99.00
  SpaceGun         19.80    198.00      19.80
  Hauler            3.00     30.00       3.00
  Freighter        49.50    495.00      49.50
  MegaFreighter   198.00   1980.00     198.00	</pre>
					<p>For example: If a planet with 1000.00 production and 10.00 resources with no stockpile of materials was producing Drones, it would produce 99.01 per turn.  About 9.90 production would be diverted to producing 99.01 materials to build the probes.  However, if it was producing Cruisers, it would only produce 2.00 per turn.  A planet with 750 production and 10.00 resources with no stockpile of materials would produce 1.50 Cruisers per turn.</p>



			<h2><a link="#combat">Combat</a></h2>

				<h3><a link="war">War and Alliances</a></h3>
					<p>At the start of the game all races are assumed to be at war with all the other races (except in team games).  <a href="#orda">Alliances</a> may be declared at the beginning of any turn.  Ships will not initiate combat with allied ships, nor will they bomb allied planets.  However, there is no way to tell if the allied race has also declared an alliance until warships are encountered.  Ships will always shoot back if fired on (battles will be fought just as if both sides were at war with each other; declaring an alliance puts warships at no disadvantage in combat).  Having declared an alliance, <a href="#ordw">war</a> may be declared again at the start of any subsequent turn and vice versa.</p>
					
<p>
Ships in hyperspace cannot be attacked but whenever hostile
warships are present at the same planet a battle will take
place.  This proceeds as follows:  
A battle consists of a number of rounds.
In each round the following steps are repeated until all ships have fired.
<OL>
<li>Randomly select a ship (attacker) from all the surviving ships that  
    have not fired yet.</li>
<li>For each gun on the ship:
  <OL><li>Randomly select a ship (target) from all the ships of the enemies 
          of the owner of the ship that is about to fire.</li>
      <li>Let the attacker fire on the target</li>
  </OL>
</li>
</OL>
</p>
<p>
Note that if a ship gets destroyed before it gets a chance to fire it will
not fire.
</p>

<p>Battle rounds continue until the battle is either a draw or a win.
A battle is a draw if:</p>
<OL>
<li>there there are two or more players left that are at war with 
    eachother.</li>  
<li>One or more players have armed ships left, but  
    none of these ships have guns big enough to penetrate the shields of
    the ships of their enemies. (see below)</li>
</OL> 
<p>A battle is won if:</p>
<OL>
<li>One or more players with ships are left.</li>
<li>All the players that are left are at peace with eachother.</li>
</OL>
</p>

<p> The success of an attacker firing on a target is calculated as follows: 
The power of
the attack is equal to the Weapons number multiplied by the Weapons
tech level.  The power of the defense is equal to the Shields number
multiplied by the Shields tech level and divided by the diameter of
the target ship.  (A ship's diameter depends on the cube root of its
total mass).  This is because a large ship's shields will have a larger
area to protect and so be diluted and, other things equal, weaker.  A
ship with numbers 8 1 8 8 0 will have only 4 times the effective
shields strength of one with numbers 1 1 1 1 0, even though it has 8
times the Shields number.  (It might arguably be more realistic to
dilute shields as the 2/3 power of the ship mass, but this would make
large ships too vulnerable.)  </p>

<p> Note that any cargo carried adds to the total mass for purposes of
shields strength calculation, as the shields generator must protect the
cargo as well as the ship.  Thus, the "total mass" of the ship for
purposes of calculating shields strength is the same as the "total
mass" for purposes of calculating speed.  (This means that a freighter
loaded with a given amount of cargo will have its shields strength
diluted less if it has higher cargo technology.)  </p>

<p> The numbers are calculated so that if a ship with numbers 10 1 10
10 0 fires at an identical ship, it will have a 50% chance of
destroying the target.  If the effective attack is four times as
strong, the attack will always succeed.  If the effective defense is
four times as strong, the attack will always fail.  The exact formula
is: </p>

<PRE>
  Eff_Weapons = Weapons_Mass * Weapons Tech
  Eff_Shields  = Shields_Mass * Shields Tech / mass^(1/3) * 30^(1/3)
                    
  p[kill] = (log[4](Eff_Weapons / Eff_Shields) + 1) / 2
         
  Where log[4](x)  is the log with base 4 of x, which
  can be computed with log(x)/log(4).
</PRE>

<h3><a link="#conquest">Conquering Planets</a></h3>

<p> If an armed ship is left at one of an enemy race's planets after
all fighting has been done, it will bomb the planet and wipe out 75%
of the population and industry (both population and industry are
reduced to 25% of their original value). The ownership of the planet
goes to the race that bombed the planet. This is how you conquer
planets occupied by another race.  </p>


<p> You will ask, who gets the planet when two friendly races have
ships above the same planet?  Normally this is the races that comes
first in the list with races (as shown in the turn report).  This is
unfair of course, allies will like to divide the planets they conquer
amongst each other.  This is possible though with the V command, that
allows a races to claim a planet. You use it to indicate that you
claim ownership of a planet when it is bombed. It of course only works
when you have ships left above the planet when it is bombed.  In case
2 or more races claim the same planet, nobody gets ownership over
the planet.  </p>

<p> There is one other special situation. This is when after battle,
both the owner of the planet, and the race(s) that attacked the
planet all have ships left, a so called standoff.  This can happen
when there are ships with small guns and big shields.  In this case,
the planet is bombed but nobody gets ownership over the planet.  </p>



<h2><a link="#orders">Orders</a></h2>

<h3><a link="#sendord">Sending Orders</a></h2>

<p> To enter orders for Galaxy, you should send a mail message
containing the following:  </p>

<PRE>
  #GALAXY &lt;gamename&gt; &lt;race-name&gt; &lt;password&gt;
  ...orders...
  #END
</PRE>

<p> The #GALAXY line should be in the body of the message, not in the
subject line.  It is very important to type this line correctly, as
otherwise all of your orders will be discarded. Everything before the
#GALAXY line or after the #END line in the message is ignored by the
program.  </p>

<p>As subject for the message use "orders" the server checks your
orders and send you a forecast of what your situation will be the
comming turn.  Replacement sets of orders may be sent anytime before
the deadline. The last set of orders received at the time of running
the turn is used.  </p>

<h3><a link="#advanc">Advance Orders</a></h3>

<p> If you are away for a couple of days and are not able to send in
orders on those days, you can sent in advance orders. For this sent in
orders with as subject, "orders &lt;turn number&gt;".  Where the turn
number indictates the turn the orders are intended for.  The server
will store the orders (but not check them), and use them when the turn
runs.  </p>

<p>Be careful <STRONG>not</STRONG> to change your race name or
password, right before sending in advance orders. Since then your
advance orders will be rejected when the turn runs.</p>

<h3><a link="#examor">Example Set of Orders</a></h3>

<p>Writing orders for the first time can be a daunting task,
so here is an example set of orders.</p>

<PRE>
  #GALAXY Jangi Nation_200 P981231231  
  ; Nation_200 and the password P981231231 are just an example,
  ; you can find the correct line at the begining of your turn 0 report.

  C Vogons         ; give your race a name
  N 67  Vogonia    ; Give your first home planet a name
                   ; notice that your home planet probably has a different
                   ; number. You can find it in the `Your Planets'
                   ; section of the report.
  N 111 Moon       ; Give your second home planet a name
  D Probe 1 0 0 0 0  ; Design a ship
  P 67 Probe       ; Have the ship produced at the first home planet
                   ; Notice that we still use the old name of the planet
                   ; as the name change won't go in effect until the next
                   ; turn.
  P 111 DRIVE      ; Have the other planet develop Drive technology
  #END
</PRE>

<h3><a link="#orderformat">Order Format</a></h3>

<p>Each type of order is designated by giving a letter or keyword as
the first non-blank character on the line. The program only checks the
first letter, so you can either give a whole word or just the
letter. Parameters are given after this, separated by spaces or
tabs. Blank lines are permitted, as are comments; anything after a
semicolon on a line is treated as a comment and ignored.  (Messages
(see below) are an exception; semicolons in message text are treated
as part of the text rather than comments.)  </p>

<p> The parser is not case sensitive, so all commands, names etc. may
be given in upper case, lower case or a mixture of the two. However,
when supplying names containing spaces, the name must be surrounded by
double quotes, or else underscore characters must be used in place of
spaces in the name.  Examples of correct order lines:
</p>

<PRE>
  Send 100 "Zzyax Prime"
  send 100 zzyax_prime
  s 100 "zzyax prime"	; Attack the Zzyaxian homeplanet
</PRE>

<p>
Examples of incorrect order lines:
</p>

<PRE>
  Send 100 Zzyax Prime
  s 100 "zzyax prime"	Attack the Zzyaxian homeplanet
</PRE>

<p>The following sections show what orders are available.</p>

<h3><a link="#ordat">@ [race ...]</a></h3>

<p> This command sends a message to one or more other players. All
lines between this line and the next one with an @ as its first
non-blank character are treated as message text. The to-whom parameter
should be a list of natio names separated by spaces. The message will
be sent to all of these, e.g.  </p>

<PRE>
  @ Zzyaxians "Mutant Camels"
  You are all a bunch of raving lunatics...
  @
</PRE>


<p> If no list of races is provided (or if a race name is provided
with no space between it and the @ sign - take care to avoid this),
the message will be sent to all races. The program does not
automatically sign your name, so you should sign it yourself unless
you wish the message to be anonymous.  </p>

<h3><a link="#ordeq">= &lt;your real name&gt;</a></h3>

<p>Sets your real name. It is used for the Hall of Fame.  If you set
your real name, and are still around when the game ends you will be
awarded victory points. This information is only made available to the
GM and the maintainer of the Hall of Fame.</p>

<p>Use quotes cause your name will most likely include spaces, for
instance</p>
<PRE>
= "John Wayne"
</PRE>

<h3><a link="#orda">A &lt;race&gt;</a></h3>

<p> Declare peace on another race.  </p>

<h3><a link="#ordb">B &lt;group&gt; &lt;number of ships&gt;</a>

<p> Break off a number of ships from a group.  </p>

<h3><a link="#ordc">C &lt;new name&gt;</a></h3>

<p> Change the name of your race.  </p>

<h3><a link="#ordd">D &lt;type name&gt; &lt;drive&gt; &lt;attacks&gt; &lt;weapons&gt; &lt;shields&gt; &lt;cargo&gt;</a></h3>

<p> Design a new ship type with the given numbers.  </p>

<h3><a link="#orde">E &lt;type name&gt;</a></h3>

<p> Erase a ship type (only works if you have no ships of that type in
existence or being built).  </p>

<h3><a link="#ordf">F &lt;race&gt;</a></h3>

<p> This gives the address of the indicated player. If there is no
address, this means that that position is either not being played, or
being played by the GM, or being played by someone who cannot be
contacted by email.  </p>

<h3><a link="#ordg">G &lt;group&gt; [number of ships]</a></h3>

<p> Upgrade a group of ships. The group must be at one of your
planets, and must remain there during the turn long enough for the
upgrade to be performed; this means that it cannot be given a Send or
Intercept command that turn, though it may be automatically sent on a
route, as this happens later in the turn. Ships in the group will be
upgraded to the latest technology levels as of the start of the
current turn (if they are already at the latest tech levels, nothing
will happen). The cost of upgrading a ship is equal to a fraction of
the cost of building a new one; for example, if the ship is currently
at 2/3 of the latest tech levels, the cost of upgrading will be 1/3 of
the cost of building a new ship. (Effectively it will be even cheaper
than this, because upgrading uses no raw materials.) The exact formula
for the cost is: </p>

<PRE>
10 * ((1 - ship-drive-tech/current-drive-tech) * ship-drive-mass +
      (1 - ship-weapons-tech/current-weapons-tech) * ship-weapons-mass +
      (1 - ship-shields-tech/current-shields-tech) * ship-shields-mass +
      (1 - ship-cargo-tech/current-cargo-tech) * ship-cargo-mass)
</PRE>

<p> If the number-of-ships parameter is given (even as 0 to explicitly
specify the entire group), exactly that many ships will be upgraded,
even if only enough production points are available to do a partial
upgrade. If the parameter is omitted, only as many ships will be
upgraded as can be fully upgraded. So if you have an expensive ship
which will cost more than a full turn's production to upgrade, you
must partially upgrade it the first turn, and issue another order next
turn to upgrade it again. (This is different from building expensive
ships, where a single production order will cause a planet to keep
working until told to stop.) Production points spent on upgrading
ships during a turn are deducted from that planet's production that
turn.  </p>

<h3><a link="#ordh">H &lt;group&gt;</a></h3>

<p> Call back a group. This order can be used to call back groups that
have sent by mistake to a far away planet. It only works on groups
that need at least 4 more turns to arrive at their destination planet.
The group will return to the planet they departed from.  </p>


<h3><a link="#ordi">I &lt;group&gt; &lt;planet&gt; [number of ships]</a></h3>

<p>Order your group to intercept alien ships at another planet. With
this command, you specify one of your groups, and a target
planet. Typically there will be an alien ship or fleet at the planet,
which you want your group to attack and destroy. However if you use an
ordinary "Send" order, the alien fleet may leave the target planet on
the same turn, so your group would arrive to find it gone.  With the
Intercept order, if alien ships leave the target planet that turn,
your group will be sent towards whatever planet has the largest total
mass of alien ships <b>sent</b> to it from the target planet, except
that only planets which your group can reach in no more than two turns
will be considered. Otherwise your group will be sent to the target
planet itself.  </p> 

<p> In the intercept case the mass of ships left at the named planet
is ignored.  The command only looks at the outgoing mass. So if a
player has a big fleet at a planet, and send one probe from that
planet, you will follow the probe.  </p>


<h3><a link="#ordl">L &lt;group&gt; &lt;cargo type&gt; [number-of-ships] [AMOUNT &lt;amount&gt;]</a></h3>

<p> Load a specific amount cargo onto a group of ships or a number of
ships in the group.  The amount parameter specifies the amount loaded
per ship. For any order you should make sure that you load at least
0.01 per ship, otherwise the order is refused.  For instance do not
try to load 1 colonists onto a group of 1000 <TT>1 0 0 0 1</TT> ships.
</p>


<p>The following cargo types are available: </p>

<TABLE >
<TR><TD>CAP</TD><TD>Capital</TD></TR>
<TR><TD>MAT</TD><TD>Materials</TD></TR>
<TR><TD>COL</TD><TD>Colonists</TD></TR>
</TABLE>


<h3><a link="#ordm">M &lt;x&gt; &lt;y&gt; &lt;size&gt;</a></h3>

<p> Change the area covered by the map on your turn report. X and Y
are the coordinates of the top left corner of the map and size is the
size you want covered in light years, e.g. M 10 20 50 will give you a
map starting at (10,20) and 50 light years on a side. Useful for
zooming in on a particular area for greater detail or zooming out
again to get a wide picture. The position and size of the area covered
by the map is included in your turn report.  </p>

<h3><a link="#ordn">N &lt;old planet name&gt; &lt;new planet name&gt;</a></h3>

<p>Change the name of a planet that you own.</p>

<h3><a link="#ordo">O &lt;option&gt;</a></h3>


<p>Sets a game options.  You cannot set more than one option using one
O command, separate commands must be used. The following options are
currently available: </p>

<TABLE >
<TR><TH>Option</TH>
    <TH>Effect</TH>
    <TH>Default</TH>
</TR>

<TR><TD>Anonymous</TD>
    <TD>This prevents that your email address is 
        made available to other players.</TD>
    <TD>On</TD>
</TR>

<TR>
<TD>AutoUnload</TD>
<TD>Automatically unloads all cargo arriving at one of your planets. This
does not work at a planet occupied by another race.</TD>
<TD>On</TD>
</TR>

<TR>
<TD>BattleProtocol</TD>
<TD>If you switch this option on you get an extra section for each battle
section. This section tells you which ship fired on which ship and
whether the ship survived. Can be used to analyse you battles, and
some turn viewers seem to use it to make animations of the battles.</TD>
<TD>Off</TD>
</TR>

<TR>
<TD>Compress</TD>
<TD>Your turn report is compressed (zipped) before
it is send. It is not always supported, so please ask the game master
for information before you turn it on.</TD>
<TD>Off</TD>
</TR>

<TR>
<TD>Gplus</TD>
<TD>You will receive your turn report in the format used
by Galaxy G+. A variation of Galaxy that is used in Russia.</TD>
<TD>Off</TD>
</TR>

<TR>
<TD>GroupForecast</TD>
<TD>
When you orders are being checked by the orders checker, you
will recieve a forecast on the position of your groups will have
the next turn.</TD>
<TD>On</TD>
</TR>

<TR>
<TD>MachineReport</TD> 
<TD>If you switch this option on you will receive two
turn reports:  one in normal format, and one in a format that is easier
readable for a machine.  This machine report is still in ascii and human
readable though. It was coded by Chris Barbier.</TD>  
<TD>Off</TD>
</TR>


<TR>
<TD>PlanetForecast</TD>
<TD>When you orders are being checked by the orders checker, you
will recieve a forecast on the status that your planets will have
the next turn.</TD>
<TD>On</TD>
</TR>

<TR>
<TD>ProdTable</TD>
<TD>Makes the `Ships In Production' table be displayed.</TD>
<TD>On</TD>
</TR>

<TR>
<TD>RoutesForecast</TD>
<TD>When you orders are being checked by the orders checker, you
will recieve a forecast on the routes between your planets that will
exist the next turn.</TD>
<TD>On</TD>
</TR>

<TR>
<TD>ShipTypeForecast</TD>
<TD>When you orders are being checked by the orders checker, you
will recieve a forecast on the ShipTypes that will be available
the next turn.</TD>
<TD>On</TD>
</TR>

<TR>
<TD>SortGroups</TD>
<TD>Sorts the groups with respect to planet order. All your groups at your
planets will be displayed first in planet order, then all your groups
at planets belonging to other races will be displayed in orders and
finally groups at unoccupied planets will be displayed. The group
number will be changed so that all groups are still numbered
logically.</TD>
<TD>On</TD>
</TABLE>


<p>
You can turn off options using by added a NO after the O, for instance:
</p>
<PRE>
  O NO sortGroups
</PRE>



<h3><a link="#ordp">P &lt;planet&gt; &lt;product&gt;</a></h3>

<p> Set production for a planet.  Every time you change production,
production that was in progress is lost.  So if you built a mass 400
ship at you home planet, and decide to stop after 2 turns, you loose
2000 production points.  The following products can be produced: </p>
<TABLE > <TR><TD>CAP</TD><TD> Capital</TD></TR>
<TR><TD>MAT</TD><TD> Materials</TD></TR> <TR><TD>DRIVE</TD><TD> Drive
research</TD></TR> <TR><TD>WEAPONS</TD><TD> Weapons research</TD></TR>
<TR><TD>SHIELDS</TD><TD> Shields research</TD></TR>
<TR><TD>CARGO</TD><TD> Cargo bay research</TD></TR>
<TR><TD>type-name</TD><TD>Ships of the named type</TD></TR> </TABLE>


<h3><a link="#ordq">Q &lt;your race name&gt;</a></h3>

<p> Quit the game. You must provide your race name as the parameter as
a safeguard to prevent Quit orders being issued accidentally.  </p>



<h3><a link="#ordr">R &lt;origin planet&gt; &lt;cargo type&gt; [destination planet]</a></h3>

<p>
Set a route. The following cargo types are available:
</p>

<ul>
<li><b>CAP</b> - Capital</li>
<li><b>MAT</b> - Materials</li>
<li><b>COL</b> - Colonists</li>
<li><b>EMP</b> - Empty transports</li>
</ul>

<p> Specifying no destination planet indicates that an existing route
should be cancelled.  </p>


<h3><a link="#ords">S &lt;group&gt; &lt;planet&gt; [number of ships]</a></h3>

<p> Send ships to a planet.  </p>


<h3><a link="#ordt">T &lt;type name&gt; &lt;new name&gt;</a></h3>

<p> Change the name of a ship type.  </p>


<h3><a link="#ordu">U &lt;group&gt; [number-of-ships] [AMOUNT &lt;amount&gt;]</a></h3>

<p> Unload a group's cargo onto the planet it's currently at.  At the
moment you unload colonist onto un uninhabited planet, you will become
the owner of that planet.  Capital and materials unloaded onto an
uninhabited planet will sit there until someone colonizes the planet.
The amount parameter specifies the amount to be unloaded per ship.
This should be at least 0.01.  </p>


<h3><a link="#ordv">V &lt;planet&gt;</a></h3>

<p> Use this command to indicate that you claim ownership of a planet.
This command is of use when you and your allies jointly attack an
enemy and you want to divide the captures planets among eachother
(share the loot).  It only works if the race that claims the planet
has armed ships left after the battle.  In case one of your allies
cheat, that is in case 2 or more races claim the same planet, nobody
gets the planet.  </p>

<h3><a link="#ordw">W &lt;race&gt;</a></h3>

<p> Declare war on another race.  </p>


<h3><a link="#ordx">X &lt;group&gt; [number-of-ships]</a></h3>

<p> Scraps old spacecraft. The ships are converted into raw materials
which are deposited on the planet where the group is located (must be
at a planet, not in hyperspace). Any cargo the ships were carrying is
unloaded first. The command will not work if the ships are carrying
colonists or are over an alien planet.  </p>


<h3><a link="#ordy">Y &lt;passwd&gt;</a>

<p> Sets your password to passwd.  </p>


<h3><a link="#ordz">Z &lt;new address&gt;</a>

<p> Change the address to which your reports are sent.  </p>



<h3><a link="#note">Things to note</a></h3>

<p>
All orders involving groups can take an optional last parameter giving
the number of ships to be used. If this parameter is given, the
indicated number of ships will be broken off into a separate group
first, and the order applied only to that separate group.
</p>

<p>
Keywords used as parameters to orders must be given precisely; unlike
order keywords they cannot be abbreviated (nor expanded). The
following keywords are used: CAP, MAT, COL, EMP, DRIVE, WEAPONS,
SHIELDS, CARGO, MAX.
</p>


<h3><a link="#fleetorders">Fleet Orders</a></h3>

<p>
The following fleet orders are available:
</p>

<TABLE>
<TR><TD>B &lt;group&gt; FLEET</TD>
<TD>Remove Group groupno from it's current fleet</TD>
</TR>

<TR><TD>D FLEET &lt;fleet name&gt;</TD>
<TD>Create a fleet called fleetname</TD>
</TR>

<TR><TD>E &lt;fleet name&gt;</TD>
<TD>Disband Fleet fleet name.</TD>
</TR>

<TR><TD>I &lt;fleet&gt; &lt;planet&gt;</TD>
<TD>Intercept ships at planetname with Fleet fleetname.</TD>
</TR>

<TR><TD>J &lt;group&gt; &lt;fleet&gt; [number-of-ships]</TD>
<TD>Add Group groupno to Fleet fleetname. If it is currently with another
fleet it will be moved to the new fleet.</TD>
</TR>

<TR><TD>J &lt;fleet 1&gt; &lt;fleet 2&gt;</TD>
<TD>Merge fleet 1 into fleet 2 leaving fleet 1 empty.</TD>
</TR>

<TR><TD>S &lt;fleet&gt; &lt;planet&gt;</TD>
<TD>Send Fleet fleet to planet</TD>
</TR>

<TR><TD>T &lt;fleet&gt; &lt;new fleet name&gt;</TD>
<TD>Change the name of the fleet.</TD>
</TR>
</TABLE>

<p>
The following keyword is used: FLEET
</p>



<h2><a link="#turns">Turns</a></h2>

<p>
The following sequence of events takes place when a turn is being run:
</p>
<ol>
<li>
All orders except for renaming and upgrading orders (C, G, N and T)
are executed.
</li>
<li>
C, G, N and T orders are executed.
</li>
<li>
Hostile ships fight each other.
</li>
<li>
Ships bomb enemy planets.
</li>
<li>
Ships, which are assigned to routes are loaded and sent into
hyper space. 
</li>
<li>
Ships are sent on intercept orders.
</li>
<li>
Ships move through hyperspace.
</li>
<li>
Hostile ships fight each other again (new battles might be possible
after ships emerge from hyperspace).
</li>
<li>
Ships bomb enemy planets again.
</li>
<li>
Production takes place.
</li>
<li>
Ships, which are assigned to routes, unload their cargo.. 
</li>
<li>
Identical groups are merged.
</li>
</ol>


<h2><a link="#afewnotes">A few things to note</a></h2>

<p> When orders conflict, such as two players trying to unload
colonists onto an uninhabited planet simultaneously at the start of
the turn, whoever is first in the list of players will have his order
executed first and colonize the planet. In practice this does not
happen often enough to be relevant.  </p>

<p> A ship which takes several turns to build will be built with the
tech levels available at the start of the final turn.  </p>

<p> Because names are changed after other orders, entities which are
renamed in a turn must still be referred to by their old names for the
rest of that turn.  </p>

<p>The game engine stores numbers in double precision format but <strong>truncates</strong> values reported to players to two decimal places.  For example, drive technology 2.4389 will be reported as 2.43 and a ship designed with shields mass 18.11999999 will be reported as shields mass 18.11.  Note that galaxy size, planetary coordinates and planetary resources are the exceptions - a planet reported at 138.44,43.29 with 4.30 resources is actually at that location and will not be found at 138.4426,43.28934 with 4.3032 resources.  Negative numbers are not used in GalaxyNG.</p>

<h2><a link="#inactive">Inactivity</a></h2>

<p> Inactivity, that is not sending in orders can cause you to be
expelled from the game.  You are allowed to miss a few turn, this to
make sure you are not kicked out when your internet provider goes
down, or if you are on holidays for a few days.  However not sending
in orders, (even empty orders will do), for more than a few turns is
not allowed.<p>

<p>
You are not allowed to miss the first turn. If you do not send in
orders for turn 1, you are automaticaly removed from the game.  This
is to weed out players that sign-up for a game but then never play.
</p>

<p> During the first 10 turns you are not allowed to miss
more than 2 turns in a row. If you do so you are expelled from the
game and your empire (complete with ships and population is removed
from the game).</p>

<p>After turn 10 you are not allowed to miss more than 5
turns in a row. If you do, you are expelled from the game, your empire
continues to exists however. And without a leader it will be an easy
prey for other races to feast on.</p>


<h2><a link="#reports">Turn Reports</a></h2>

<p>After each turn runs you will receive a turn report with information
on the state of your race. If you don't play in a game yet,
you might want to look at some 
<a href="example.html">example reports</a>.</p>

<p> Your turn report will contain some or all of the following
sections: </p>

<h3><a link="#repopt">Your Options</a></h3>

<p> A list with all the options that are available. It shows if you
have switched an option on or off.  
To switch options on or off use the <a href="ordo">O order</a>.
</p>


<h3><a link="#repmes">Messages</a></h3>

<p>Messages from other players. You can send your own messages
by using the <a href="#ordat">@ command</a></p>


<h3><a link="#repmis">Mistakes</a></h3>

<p>Any mistakes in your orders.</p>


<h3><a link="#repstat">Status of Players</a></h3>

<p>This is the current status of all players in the game; the following
information is provided:</p>

<ol>
<li>Name</li>
<li>Drive Technology</li>
<li>Weapons Technology</li>
<li>Shields Technology</li>
<li>Cargo Technology</li>
<li>Total Population</li>
<li>Total Industry</li>
<li>Number of Planets Owned</li>
<li>Diplomatic Relations</li>
</ol>


<h3><a link="#repyst">Your Ship Types</a></h3>

<p>
This is a list of your ship types; the following information is provided:
</p>
<ol>
<li>Name</li>
<li>Drive</li>
<li>Attacks</li>
<li>Weapons</li>
<li>Shields</li>
<li>Cargo</li>
<li>Mass, the total mass of a ship of this type</li>
<li>Speed, the speed of a ship of this type</li>
<li>Def, the effective shields of a ship of this type</li>
</ol>
<p>
Mass, speed, and def, are computed for techlevels of 1,1,1,1.
</p>


<h3><a link="#repast">Alien Ship Types</a></h3>

<p> This is a description of each type of alien ship that you have
come into contact with this turn; the information provided is the same
as for your ship types.  </p>


<h3><a link="#repbat">Battles</a></h3>

<p>This is a description of all the battles that you have fought or
witnessed this turn. For each battle, a list of groups belonging to
each player is given. The following information is provided: </p>

<ol>
<li>Number of Ships</li>
<li>Ship Type</li>
<li>Drive Technology</li>
<li>Weapons Technology</li>
<li>Shields Technology</li>
<li>Cargo Technology</li>
<li>Cargo Type (a "-" means that the group is carrying no cargo)</li>
<li>Cargo Quantity Per Ship</li>
<li>Ships Left (survivors after the battle)</li>
</ol>


<h3><a link="#repbp">Battle Protocol</a></h3>

<p> Tels you which ships fired on which ship and whether the ship
survived.  You only get this when you switch on the option
BattleProtocol.  </p>


<h3><a link="#repbom">Bombings</a></h3>


<p>This is a list of all the planets that you have observed being
bombed this turn. The following information is given:</p>

<ol>
<li>Who bombed the planet</li>
<li>Owner</li>
<li>Planet Name</li>
<li>Population</li>
<li>Industry</li>
<li>Producing (capital, raw materials, research or ships)</li>
<li>Capital Stockpiled</li>
<li>Material Stockpiled</li>
<li>Colonists Stockpiled</li>
</ol>

<p>
(Obviously, most of this data is from just *before* the planet was bombed.)
</p>


<h3><a link="#repmap">Map</a></h3>

<p> This is a map of all or part of the galaxy. Symbols on the map
have the following meanings:</p>

<ol>
<li>*  - Your Planet</li>
<li>o  - Uninhabited Planet</li>
<li>+  - Alien Planet</li>
<li>.  - Your Ships</li>
<li>-  - Alien Ships</li>
</ol>


<h3><a link="#repigr">Incoming Groups</a></h3>

<p> This is a list of all the groups of alien ships currently heading
for planets owned by you. The following information is provided: </p>

<ol>
<li>Origin (which planet the group came from)</li>
<li>Destination (which planet the group is heading towards)</li>
<li>Distance Remaining</li>
<li>Speed</li>
<li>Total Mass</li>
</ol>


<h3><a link="#repypl">Your Planets</a></h3>

<p> This is a list of all the planets that you own. The following
information is provided: </p>

<ol>
<li>Name</li>
<li>X Coordinate</li>
<li>Y Coordinate</li>
<li>Size</li>
<li>Population</li>
<li>Industry</li>
<li>Natural Resources</li>
<li>Producing (capital, raw materials, research or ships)</li>
<li>Capital Stockpiled</li>
<li>Material Stockpiled</li>
<li>Colonists Stockpiled</li>
<li>The Effective Industry</li>
</ol>


<h3><a link="#repsip">Ships In Production</a></h3>

<p> This provides you will a list of ships in production with the
total cost to produce such a ship (including cost to produce any
materials required) and the production that has gone into producing
the next one of those ships. It will be displayed as follows: </p>

<ol>
<li>Planet</li>
<li>Ship Type</li>
<li>Cost to Produce</li>
<li>Production Already Used</li>
</ol>

<p>This table is displayed when the ProdTable option is set.  </p>


<h3><a link="#reproute">Your Routes</a></h3>

<p> This is a list of the routes from those of your planets which have
routes defined. For each planet, the destination planet is listed for
the following commodities: </p>

<ol>
<li>Capital</li>
<li>Raw Materials</li>
<li>Colonists</li>
<li>Empty Transports</li>
</ol>

<p> A "-" for a particular commodity means that no route is defined
from that planet for that commodity.  </p>


<h3><a link="#repapln">Alien Planets</a></h3>

<p> This is a list of all those planets owned by another player, at
which you have at least one ship and which you can therefore
observe. The same information is provided as for your planets.  </p>


<h3><a link="#repuinpl">Unidentified Planets</a></h3>

<p> This is a list of those planets owned by another player, which
appear on your map but which you cannot observe. Only the name of the
planet and the X and Y coordinates are available. (Occasionally, due
to roundoff errors, a planet will appear at the edge of the map but
not be listed, or vice versa.)  </p>


<h3><a link="#repuninhab">Uninhabited Planets</a></h3>

<p> This is a list of uninhabited planets which appear on your map, or
which you can observe. For all planets on the list, the name and X and
Y coordinates are provided. For those planets which you can observe,
the Size and Natural Resources attributes are also listed.  </p>



<h3><a link="#repygrps">Your Groups</a>

<p> This is a list of your groups of spaceships. This will be a list
of your groups which are not part of a fleet.  The following
information is provided: </p>

<ol>
<li>Group Number</li>
<li>Number of Ships</li>
<li>Ship Type</li>
<li>Drive Technology</li>
<li>Weapons Technology</li>
<li>Shields Technology</li>
<li>Cargo Technology</li>
<li>Cargo Type (a "-" means that the group is carrying no cargo)</li>
<li>Cargo Quantity Per Ship</li>
<li>Destination</li>
<li>Distance (if this is left blank, the group is at the Destination).</li>
<li>Origin</li>
</ol>



<h3><a link="#repyflts">Your Fleets</a></h3>

<p> You will get a table for each fleet.  The header for each fleet
will be: </p>

<PRE>
         `Fleet fleetname (Speed fleetspeed)'
</PRE>

<p> where fleetname and fleetspeed is the fleet name and fleet speed
respectively.  The following information is provided:
</p>

<OL>
<li>Group Number</li>
<li>Number of Ships</li>
<li>Ship Type</li>
<li>Drive Technology</li>
<li>Weapons Technology</li>
<li>Shields Technology</li>
<li>Cargo Technology</li>
<li>Cargo Type (a "-" means that the group is carrying no cargo)</li>
<li>Cargo Quantity Per Ship</li>
<li>Destination</li>
<li>Distance (if this is left blank, the group is at the Destination)</li>
<li>Origin</li>
</OL>



<h3><a link="#repagrps">Alien Groups</a></h3>

<p> This is a list of groups of ships belonging to other players,
which you can observe. The information provided is the same as for
your groups except without the group numbers.  </p>


<h3><a link="#copyreport">Getting a Copy a Turn Report</a></h3>

<p> You can get a copy of a turn report by sending an email to the
server. The message should contain one line: </p>

<PRE>
#GALAXY &lt;gamename&gt; &lt;race-name&gt; &lt;password&gt;
</PRE>

<p>As subject for the message use "report &lt;turn number&gt;".  The
server will send you a copy of the report for that turn.  The
copy is send to the email address you send the orders from.  You can
use this feature to get a copy of your report in case your ISP fails
for some reason.  </p>


<h2><a link="#hints">Hints and Tips</a></h2>

<p> In the early stages of the game, there will be plenty of planets
to spare so there will be little need to fight for territory; however,
you should ensure that your homeplanet is defended against sneak
attacks by xenophobic aliens. You will need to devote your efforts to
exploration, building up colonies, researching technology, and
contacting other races with a view to forming alliances.  </p>

<p> The map in your turn report only indicates which planets are
occupied by alien races, and the total mass of any groups of alien
ships in hyperspace heading for one of your planets. To learn of enemy
fleets which may pose a threat to your safety, you will need to send
ships to enemy planets to spy on them.  </p>

<p> If you have an "Incoming Groups" section on your turn report, this
probably means that one or more of your planets is under attack, and
your first priority should be to ensure that you have an adequate
defense. For each incoming group, divide the Distance by Speed to find
out how many turns the group will take to reach its target planet. Look
at the Total Mass figure - the bigger this is, the greater the
potential threat. Of course you don't know whether a very large group
is a huge battleship or a fleet of small fighters or anything in
between.  You could also try some last-minute diplomacy: the player
owning the group cannot turn it back, but he could declare peace on
you, so that the group would not attack you when it did arrive.  </p>

<p> In the later stages of the game, it is quite likely that one
player will develop a dominant position and appear to be heading for
victory. At this point, it is vitally important for all the other
players to immediately leave aside whatever differences they may have
among themselves and launch an attack on this player, because if he is
given a chance to pick the others off one by one at his leisure, he is
very likely to win.  </p>

<h2><a link="#moreinfo">Links to More Information</a></h2>

<ol>
  <li><a href="http://badcheese.com/~steve/phpwiki/index.php/GalaxyPlay">GalaxyNG Wiki</a></li>
  <li><a href="quickref.html">Quick Reference Manual</a></li>
  <li><a href="faq.html">GalaxyNG FAQ</a></li>
</ol>

</body>
</html>
