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



			<h2><a name="toc">Table of Contents</a></h2>
				<ol type="A">
					<li><a href="#intro">Introduction</a>
						<ol>
							<li><a href="#galaxy">The Galaxy</a></li>
							<li><a href="#players">Players</a></li>
							<li><a href="#names">Names</a></li>
							<li><a href="#victory">Victory and Defeat</a></li>
						</ol>
					</li>
					<li><a href="#planets">Planets</a>
						<ol>
							<li><a href="#owner">Owner</a></li>
							<li><a href="#size">Size</a></li>
							<li><a href="#pop">Population</a></li>
							<li><a href="#ind">Industry</a></li>
							<li><a href="#res">Resources</a></li>
							<li><a href="#stock">Stockpiles</a></li>
						</ol>
					</li>
					<li><a href="#ships">Ships</a>
						<ol>
							<li><a href="#types">Ship Types</a></li>
							<li><a href="#groups">Groups</a></li>
							<li><a href="#fleets">Fleets</a></li>
							<li><a href="#tech">Technology</a></li>
							<li><a href="#mass">Ship Mass</a></li>
							<li><a href="#move">Movement</a></li>
							<li><a href="#speed">Speed</a></li>
							<li><a href="#locate">Locating Ships</a></li>
							<li><a href="#cargo">Cargo</a></li>
							<li><a href="#routes">Routes</a></li>
						</ol>
					</li>
					<li><a href="#prod">Production</a>
						<ol>
							<li><a href="#mat">Materials</a></li>
							<li><a href="#cap">Capital</a></li>
							<li><a href="#tres">Technology Research</a></li>
							<li><a href="#build">Ship Building</a></li>
							<li><a href="#upgrade">Upgrading Groups</a></li>
						</ol>
					</li>
					<li><a href="#combat">Combat</a>
						<ol>
							<li><a href="#war">War and Alliances</a></li>
							<li><a href="#bat">Battles</a>
							<li><a href="#bomb">Bombing Planets</a></li>
						</ol>
					</li>
					<li><a href="#orders">Orders</a>
						<ol>
							<li><a href="#send">Sending Orders</a></li>
							<li><a href="#fore">Forecast and Errors</a></li>
							<li><a href="#adv">Advance Orders</a></li>
							<li><a href="#ex">Example Orders</a></li>
							<li><a href="#form">Order Format</a></li>
							<li><a href="#ordA">@ [race name...]</a></li>
							<li><a href="#ordE">= &lt;FirstName LastName&gt;</a></li>
							<li><a href="#orda">a &lt;race name&gt;</a></li>
							<li><a href="#ordb">b &lt;group number&gt; &lt;number of ships&gt;
							<br>b &lt;group number&gt; FLEET</a></li>
							<li><a href="#ordc">c &lt;new race name&gt;</a></li>
							<li><a href="#ordd">d &lt;name&gt; &lt;drive mass&gt; &lt;attacks&gt; &lt;weapons mass&gt; &lt;shields mass&gt; &lt;cargo mass&gt;
							<br>d FLEET &lt;fleet name&gt;</a></li>
							<li><a href="#orde">e &lt;ship type name&gt;
							<br>e &lt;fleet name&gt;</a></li>
							<li><a href="#ordf">f &lt;race name&gt;</a></li>
							<li><a href="#ordg">g &lt;group number&gt; [number of ships]</a></li>
							<li><a href="#ordi">i &lt;group number&gt; &lt;planet name&gt; [number of ships]
							<br>i &lt;fleet name&gt; &lt;planet name&gt;</a></li>
							<li><a href="#ordj">j &lt;group number&gt; &lt;fleet name&gt; [number of ships]
							<br>j &lt;fleet name&gt; &lt;fleet name&gt;</a></li>
							<li><a href="#ordl">l &lt;group number&gt; &lt;CAP | COL | MAT&gt; [number of ships] [AMOUNT &lt;amount&gt;]</a></li>
							<li><a href="#ordm">m &lt;x&gt; &lt;y&gt; &lt;extent&gt;</a></li>
							<li><a href="#ordn">n &lt;current planet name&gt; &lt;new planet name&gt;</a></li>
							<li><a href="#ordo">o [NO] &lt;anonymous | autounload | battleprotocol | compress | gplus | groupforecast | machinereport | planetforecast | prodtable | routesforecast | shiptypeforecast | sortgroups | txtreport | xmlreport&gt;</a></li>
							<li><a href="#ordp">p &lt;planet name&gt; &lt;CAP | MAT | DRIVE | WEAPONS | SHIELDS | CARGO | ship type name&gt;</a></li>
							<li><a href="#ordq">q &lt;race name&gt;</a></li>
							<li><a href="#ordr">r &lt;origin planet name&gt; &lt;CAP | COL | EMP | MAT&gt; [destination planet name]</a></li>
							<li><a href="#ords">s &lt;group number&gt; &lt;planet name&gt; [number of ships]
							<br>s &lt;fleet name&gt; &lt;planet name&gt;</a></li>
							<li><a href="#ordt">t &lt;current ship type name&gt; &lt;new ship type name&gt;
							<br>t &lt;current fleet name&gt; &lt;new fleet name&gt;</a></li>
							<li><a href="#ordu">u &lt;group number&gt; [number of ships] [AMOUNT &lt;amount&gt;]</a></li>
							<li><a href="#ordv">v &lt;planet name&gt;</a></li>
							<li><a href="#ordw">w &lt;race name&gt;</a></li>
							<li><a href="#ordx">x &lt;group number&gt; [number of ships]</a></li>
							<li><a href="#ordy">y &lt;new password&gt;</a></li>
							<li><a href="#ordz">z &lt;new email address&gt;</a></li>
							<li>Things to Note</li>
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
					<li>email</li>
					<li>Hints and Tips</li>
					<li>Links to More Information</li>
				</ol>

			<hr>

			<h2><a name="intro">Introduction</a></h2>
				<p>GalaxyNG is a multiplayer game of interstellar war.  The objective of the game is to conquer the galaxy.</p>
				<p>Players email a GalaxyNG server to register for games, submit orders and receive turn reports.  The server automatically processes turns and responds to player email.  Most games run one to five turns per week.  The Game Master (GM) maintains the server, selects game options, creates the galaxy, answers player questions and solves problems.</p>

				<h3><a name="galaxy">The Galaxy</a></h3>
					<p>The area of the galaxy in which the game is played is a square (for the sake of simplicity the third dimension is ignored) which contains a number of habitable planets which can build ships, conduct technology research, produce capital or produce materials.  Ships are used to explore, colonize uninhabited planets, haul cargo, conduct warfare and conquer planets inhabited by other races.  Technology improvements allow ships to fly faster and farther, haul more cargo and fight better.</p>
					<p>Distances are measured in light-years.  Each unit of population represents ten million people and each unit of capital or materials represents about ten million tons.  Each turn represents about four years of time.</p>
					
				<h3><a name="players">Players</a></h3>
					<p>Each player is the leader of one race.  Players can communicate by sending <a href="#ordA">messages</a> or <a href="#email">email</a> to each other.  Players are <a href="#ordo">anonymous</a> but can choose to reveal their identities to other players.  Players can  provide their <a href="#ordE">real name</a> to the GM for inclusion in the Hall of Fame without breaking their anonymity.</p>

				<h3><a name="names">Names</a></h3>
					<p>Races, planets, ship types and fleets can be named.  Names may be no more than twenty characters (a character is a letter, digit, or underscore) and may not include spaces.  Names must be unique.  For example, a race cannot have the same name as a fleet.  Each player should <a href="#ordc">provide a name</a> by which their race will be known, e.g. Mutant_Camels or Zzyaxians - if this is not done they will simply be known by number, e.g. Race_4 or Race_5.  Ship types are given names when <a href="#ordd">designed</a> and can be <a href="#ordt">renamed</a>.  Planets are numbered at the start of the game and can be <a href="#ordn">renamed</a> by their current owner.</p>

				<h3><a name="victory">Victory and Defeat</a></h3>
					<p>The game can be won by a single race or by an alliance of races, depending upon the game settings.  Races are ranked based on the total production of their planets.  A race is eliminated if it owns no planets and has no ships.  The game is complete when all surviving players agree to end it and notify the game master.</p>

			<hr>

			<h2><a name="planets">Planets</a></h2>
					<p>Planets are located in the galaxy by X and Y coordinates.  Planets have seven characteristics: owner, size, population, industry, resources, production and stockpiles.</p>

				<h3><a name="owner">Owner</a></h3>
					<p>Inhabited planets are owned by one race at a time (except in the special case of a standoff when an inhabited planet is unowned).  Uninhabited planets are not owned by any race.</p>

				<h3><a name="size">Size</a></h3>
					<p>Planets vary in size from 0.01 to 1000.00.  The size of a planet reflects the habitability of the terrain, the suitability of the climate for agriculture, and other features.  At the beginning of the game, the galaxy is divided into inhabited planets (home planets), uninhabited development planets (size 200.00 to 1000.00) and uninhabited stuff planets (size 0.01 to 200.00).</p>

				<h3><a name="pop">Population</a></h3>
					<p>Each inhabited planet has a population, which can never be larger than the planet's size but may be smaller.  A planet with zero population is uninhabited.  Home planets are fully populated at the beginning of the game.  Each planet's population grows by 8% per turn.  Excess population is stockpiled as colonists.  Each unit of colonists represents eight population.</p>

				<h3><a name="ind">Industry</a></h3>
					<p>Each inhabited planet has industry, which can never be larger than the planet's population but may be smaller.  If population exceed industry, the industry may be increased by adding capital.  If there is not an existing stockpile of capital, it may be <a href="#ordp">produced</a> at the planet or be shipped in from another planet by cargo ships.  For example, if a size 500 planet with 500 population and 200 industry produces 75 capital, the industry will increase to 275.  If a size 500 planet with 200 population and 200 industry has a stockpile of 100 capital, on the following turn the population and industry will both increase to 216 and there will be 84 capital left (because population grows by 8% per turn).</p>

				<h3><a name="res">Resources</a></h3>
					<p>Each planet has a resources value which indicates how rich it is in metals, coal, oil, wood and other products.  Home planets have a resources value of 10.00.  Other planets have a resources value between 0.01 and 10.00, with the average being 1.00.  Planets high in resources can easily <a href="#ordp">produce</a> materials such as sheet steel, copper wire and plastics.  Materials are necessary to build ships and produce capital.</p>

				<h3><a name="stock">Stockpiles</a></h3>
					<p>Each planet may have stockpiles of colonists, capital and materials.  Population increases beyond the planet's size are converted into colonists.  Eight population are converted into one colonist.  These are people automatically stored in containers in deep freeze.  Excess capital and materials are stockpiled at a one-to-one ratio.  Stockpiles may be saved for later use or transported to other planets by cargo ships.</p>

			<hr>

			<h2><a name="ships">Ships</a></h2>
				<p>Ships are organized into groups and fleets which are used for exploration, scouting, attack, defence and cargo transport.  Ships have the following characteristics: ship type (name, drive mass, attacks, weapons mass, shields mass, cargo mass and ship mass), group number, fleet name, drive technology, weapons technology, shields technology, cargo technology, cargo carried type, cargo carried mass, destination planet, and distance to destination planet.  Ships can be <a href="#ordp">built</a> at planets.</p>

				<h3><a name="types">Ship Types</a></h3>
					<p>Each player can <a href="#ordd">design</a> ship types, which are unique to that player, by specifying: name, drive mass (the power of the hyperdrive engines), attacks (the number of guns), weapons mass (the strength of the guns), shields mass (the power of the shields generator), and cargo mass (the size of the cargo bay).  Drive mass, weapons mass, shields mass, and cargo mass must equal zero or be equal to or greater than one.  Thus, drive mass 0.00 and 1.50 are allowed but drive mass 0.75 is not.  Attacks must be an integer.  Some example ship types are:</p>
<pre>                  D    A     W      S      C
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

					<p>Players can <a href="#ordt">change</a> the name of an existing ship type.  Ship types can be <a href="#orde">eliminated</a> if no ships of that type exist or are under construction.</p>

				<h3><a name="groups">Groups</a></h3>
					<p>A race can have hundreds or even thousands of ships, which would be inconvenient to handle individually.  Hence ships are handled in groups, which can contain one or more ships all of the same type, in the same place, carrying the same quantity and type of cargo (if any) and built with the same technology levels.</p>
					<p>Groups can be ordered to <a href="#ords">travel</a> to another planet, <a href="#ordi">intercept</a> other ships, <a href="#ordh">reverse</a> course, <a href="#ordb">break</a> off ships into a new group, <a href="#ordj">join</a> a fleet, <a href="#ordb">leave</a> a fleet, <a href="#ordg">upgrade</a> technology levels, <a href="#ordl">load</a> cargo, or <a href="#ordu">unload</a> cargo.  Groups may also be <a href="#ordx">scrapped</a>, which automatically unloads all cargo and deposits the materials used to produce the ships at the current planet.  If <a href="#ordr">routes</a> have been established, groups will follow them.</p>
					<p>Each group is assigned a number, which is used to issue orders to ships in the corresponding group.  When new groups are created, they are assigned a number N+1, where N is the highest numbered group in existence.  Whenever a group number is required as an order parameter, the keyword MAX may be used instead. This will apply the order to the group with the highest group number, i.e. the most recently created group.</p>
					<p>In several phases of the turn, groups containing identical ships, carrying identical cargo (if any), in the same place and in the same fleet (if applicable) will be merged using the lower group number.  For example, if group 5 containing 48 ships is merged with group 12 containing 52 ships, group 5 will contain 100 ships and group 12 will be eliminated.</p>
					<p>If the SortGroups <a href="#ordo">option</a> is turned on, at the end of each turn groups will be automatically sorted and renumbered as follows: Owner's groups at owner's planets; Owner's groups at other race's planets; Owner's groups at uninhabited planets; Owner's groups in fleets.</p>

				<h3><a name="fleets">Fleets</a></h3>
					<p>Fleets contain groups, allowing players to gather different ship types together in a single unit.  Many of the orders for groups can also be used for fleets.  Players can <a href="#ordd">create</a>, <a href="#orde">eliminate</a>, <a href="#ordj">merge</a> and <a href="#ordt">rename</a> fleets.  Fleets can be ordered to <a href="#ords">travel</a> to another planet, <a href="#ordi">intercept</a> other ships, or <a href="#ordh">reverse</a> course.  The slowest group in the fleet sets the maximum speed for the entire fleet.</p>
					<p>A group in a fleet that is given a <a href="#ords">send</a> or <a href="#ordi">intercept</a> order is automatically removed from the fleet.  Ships in a fleet that are <a href="#ordb">broken</a> from groups are also removed from the fleet.  Groups in fleets that are ordered to <a href="#ordg">upgrade</a>, <a href="#ordl">load</a> or <a href="#ordu">unload</a> cargo remain in the fleet.  Groups in fleets will not travel on <a href="#ordr">routes</a>.</p>

				<h3><a name="tech">Technology</a></h3>
					<p>Technology determines the effectiveness of ships.  There are four technologies: drive, weapons, shields and cargo.  Each race begins the game with 1.00 levels in each technology.  Technology can be increased by ordering planets to conduct <a href="#ordp">research</a>.</p>
					<p>Ships are assigned the technology levels of the race at the time they are <a href="#ordp">produced</a>.  As the race's technology level increases, ships can be <a href="#ordg">upgraded</a> at planets owned by the player.</p>
					<p>A ship with drive technology 4.00 is twice as fast as an equivalent ship with drive technology 2.00, a ship with weapons technology 1.50 has a 50% more powerful attack than the same ship with weapons technology 1.00, and so forth.  Ships without a component are considered to have a matching technology of zero.  For example, a ship with weapons mass zero is consdered to have weapons technology zero.</p>
  
  			<h3><a name="mass">Ship Mass</a></h3>
					<p>Ship types with zero or one attack have a ship mass of drive mass + weapon mass + shield mass + cargo mass.  Each additional attack beyond the first adds 50% of the weapon mass to the ship mass.  For example:</p>
<pre>                  D   +     W   +    Additional    +     S   +   C   =  Ship
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
  
				<h3><a name="move">Movement</a></h3>
					<p>Ships are equipped with hyperspace drives, except ships with a drive mass of zero which remain forever at the planet where they were built.  Hyperspace travel is only possible from one concentration of mass to another, i.e. from one planet to another.  Ships always travel at maximum speed in hyperspace, unless they are part of a fleet.  When ships enters hyperspace, no time passes for the ship or those on board; a ship in hyperspace can only go forward or reverse and cannot participate in combat.</p>
					<p>Groups can be <a href="#ords">sent</a> to other planets.</p>	
					<p>Groups can be ordered to <a href="#ordi">intercept</a> alien ships at a target planet.  Intercepting groups will attempt to follow alien ships leaving the target planet, but can only intercept at destination planets within two turns range of the intercepting group.  The intercepting group will be sent toward whichever destination planet is within two turns range and has the largest total mass of alien ships departing toward it from the target planet that turn.  If all destination planets are farther than two turns range, or if no alien groups leave the target planet, the intercepting group will be sent to the target planet.  Note that the mass of ships leaving the target planet is the sole determinant of potential interception locations.  If a single Probe departs a target planet and 2,000 ships remain behind, the intercepting group will follow the Probe.</p>
					<p>Groups in hyperspace that are more than four turns from their destination planet may be ordered to <a href="#ordh">reverse</a> course and return to their planet of origin.  This is useful for retrieving groups accidentally sent to the wrong planet.</p>

				<h3><a name="speed">Speed</a></h3>
					<p>Ships move a number of light years per turn according to the following formula:</p>
<pre>Speed = 20 * drive technology * (drive mass / (ship mass + effective cargo carried mass)).</pre>
					<p>Note that unless your drive technology is very high, large ships should have correspondingly large drives or they will be very slow.  On the other hand the fastest ships you can possibly build (all numbers except drive mass being zero in the design) can only travel at a speed of twenty times your drive technology.  For example, using the ship types above and assuming drive technology 1.00:<p>
<pre>               20 * Drive * (  Drive / (   Ship +   Effective   )) = Speed
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
<pre>BattleCruiser  20 *  1.00 * (  49.50 / (  99.00 +      1.10     )) =  9.79
Battleship     20 *  1.00 * (  33.00 / (  99.00 +      1.10     )) =  6.52
Hauler         20 *  1.00 * (   2.00 / (   3.00 +      1.10     )) =  9.75
Freighter      20 *  1.00 * (  30.00 / (  49.50 +     20.00     )) =  8.63
MegaFreighter  20 *  1.00 * ( 120.00 / ( 198.00 +    196.14     )) =  6.09</pre>

				<h3><a name="locate">Locating Ships</a></h3>
					<p>Each race's administrative staff will keep a record of its own ships on planets or in hyperspace.  Planet owners have full knowledge of all ships orbiting their planets.  Players also receive complete reports on ships at planets visited by their own ships.</p>
					<p>Locating alien ships in hyperspace is much more problematic.  Detectors to accurately locate the position of alien ships in hyperspace are installed on each planet.  Accurate readings of mass, speed, origin and distance from destination can be obtained for ships heading directly toward a detector (i.e. inbound to a planet).  A rough indication of the location of other alien groups is indicated on the <a href="#ordm">text map</a>, but their mass, speed and direction of travel are unknown.</p>

				<h3><a name="cargo">Cargo</a></h3>
					<p>Cargo ships can <a href="#ordl">load</a> stockpiles of colonists, capital and materials to <a href="#ords">transport</a> them to other planets where they can be <a href="#ordu">unloaded</a>.  Each ship may only carry one type of cargo at a time.  The base amount of cargo a ship can carry is determined by the following formula: base cargo = cargo mass + cargo mass^2/10.  Thus, at cargo technology 1.00, some examples would be:</p>
<pre>               Cargo + Cargo Mass^2/10 =  Base Cargo
                Mass                        Carried
BattleCruiser   1.00 +       0.10      =      1.10
Battleship      1.00 +       0.10      =      1.10
Hauler          1.00 +       0.10      =      1.10
Freighter      10.00 +      10.00      =     20.00
MegaFreighter  39.57 +     156.57      =    196.14</pre>
       <p>Cargo technology increases the amount of cargo that a ship can carry.  Thus, a Hauler with cargo technology 2.00 can carry 2.20 cargo and a Freighter with cargo technology 3.00 can carry 60.00 cargo.  This does not slow down the ships, as the cargo carried is divided by the cargo technology to obtain the effective cargo carried.  Thus, at cargo technology 3.00, a Freighter carrying 60.00 cargo has an effective cargo carried of 20.00, while the same Freighter carrying 35.00 cargo has an effective cargo carried of 11.66.</p>
       <p>Colonists that are unloaded at an uninhabited planet will claim the planet for their race.  Each colonist becomes eight population.  Capital and materials unloaded at an
uninhabited planet will be stockpiled until the planet is colonized.</p>

     <h3><a name="routes">Routes</a></h3>

      <p>Colonists, capital, materials, and empty routes can be <a href="#ordr">established</a> between planets.  Each planet can be the origin for only one route of each type.  A planet can be the destination of an unlimited number of routes.  For example, colonists routes can be set from planets 105, 82 and 243 to planet 56 but planet 105 cannot simultaneously have a colonists route to planet 97.  Players may only establish routes from their own planets, however any planet may be the destination of a route.</p>      
      <p>Cargo ships that are not in fleets and have not been ordered to <a href="#ordl">load</a>, <a href="#ordu">unload</a> or <a href="#ords">travel</a> between planets will automatically follow routes.  They will load cargos, travel to destination planets, and unload cargos.  Cargo ships that are already loaded will also follow routes.</p>
      <p>Routes are assigned to cargo ships in the following order of priority: colonists, capital, materials and empty.  Ships are used in order by group number to full capacity, if possible.  For example, planet 105 has colonists and capital routes to planet 56, an empty route to planet 74, forty cargo ships with 2.00 capacity each, 10.00 colonists and 31.00 capital.  Five cargo ships will carry colonists to planet 56, sixteen cargo ships will carry capital to planet 56 and the remaining nineteen cargo ships will travel empty to planet 74.  However, if there is an additional cargo ship with capacity 40.00 and a lower group number than the 2.00 capacity ships, it will be used to carry 10.00 colonists to planet 56.  If it has a higher group number, it will travel empty to planet 74.</p>
      <p>All ships, regardless of origin planet, that arrive at a destination planet for a route will be unloaded if they carry the appropriate cargo.  Unloading at route destinations ignores the status of the <a href="#ordo">autounload</a> option.</p>
     
			<hr>

			<h2><a name="prod">Production</a></h2>
				<p>The productive capacity of a planet is determined mostly by its industry value and partly by its population.  Each unit of industry on a planet yields one production unit, and every four units of population over and above industry yields an additional production unit.  The formula is:</p>
<pre>Production = Industry + (Population - Industry)/4</pre>
				
				<p>For example, a planet with 500.00 population and 500.00 industry has 500.00 production (500 + 0), a planet with 500.00 population and 250.00 industry has 312.50 production (250 + 250/4) and a planet with 500.00 population and 0 industry has 125.00 production (0 + 500/4).  A planet can be ordered to <a href="#ordp">produce</a> materials, capital, technology research or ships.  Each planet can only perform one type of production each turn.</p>
				
				<h3><a name="mat">Materials</a></h3>
					<p>Materials production is determined by the resources values of the planet, which equals the number of materials that will be produced per point of production devoted to the task.  For example, a planet with 5.00 resources and 100.00 production will produce 500.00 materials, while a planet with 0.10 resources would only produce 10.00 materials.</p>
				
				<h3><a name="cap">Capital</a></h3>
					<p>Producing 1.00 capital requires 5.00 production and 1.00 materials.  If the planet does not have a stockpile of materials, some production will automatically be diverted to producing materials.  For example, a planet with 1000.00 production and a stockpile of 200.00 materials will produce 200.00 capital.  With no stockpile of materials and 10.00 resources, 196.08 capital will be produced.  With 0.10 resources, the planet will produce 66.67 capital.</p>
				
				<h3><a name="tres">Technology</h3>
					<p>A planet can research one of the four technologies each turn.  It costs 5,000.00 production to increase drive, weapons, or shields technology by one point and 2,500.00 production to increase cargo technology by one point.  Fractional increases are effective immediately: if you spend 500.00 production on research into Weapons, your weapons technology will go up by 0.10.</p>

				<h3><a name="build">Ship Building</a></h3>
					<p>A planet can produce one type of ships each turn.  The production cost of a ship is equal to its mass times ten.  In addition, one unit of materials is required for every ten units of production.  If the planet does not have a stockpile of materials, some production will automatically be diverted to producing materials.</p>
<pre>                  Mass  Production  Materials
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
					<p>For example: If a planet with 1000.00 production and 10.00 resources with no stockpile of materials was producing Drones, it would produce 99.01 per turn.  About 9.90 production would be diverted to producing 99.01 materials to build the Drones.  The same planet with 0.10 resources would only produce 50.00 Drones per turn.</p>
					<p>Excess ship production is carried forward into the next turn.  If the planet continues producing the same ship type, the fractional production is added to the current turn production.  For example, a planet with 750 production and 10.00 resources with no stockpile of materials would produce 1.50 Cruisers per turn.  One Cruiser would be produced on the first turn and two Cruisers would be produced on the second turn.  If the planet's production is changed, the extra ship production is lost and any materials produced on the previous turn are added to the planet's stockpiles.</p>
					
				<h3><a name="upgrade">Upgrading Groups</a></h3>
					<p>Groups can be <a href="#ordg">upgraded</a> at the owning player's planets.  Groups that are upgraded cannot be ordered to <a href="#ords">travel</a> to another planet or <a href="#ordi">intercept</a> an enemy group, however they will be sent on <a href="#ordr">routes</a> and participate in combat.  Ships in the group will be upgraded to the owning player's technology levels as of the beginning of the turn (if they are already at the current technology levels, nothing will happen). The cost of upgrading a ship is equal to a fraction of the production cost of a new ship of the same type.  Ugrades do not require materials.  The exact formula for the cost is:</p>
<pre>Upgrade cost = 10 * ((1 - ship drive tech / current drive tech) * ship drive mass +
(1 - ship weapons tech / current weapons tech) * ship weapons mass +
(1 - ship shields tech / current shields tech) * ship shields mass +
(1 - ship cargo tech / current cargo tech) * ship cargo mass)</pre>
					<p>If the planet does not have enough production to upgrade the entire group, then as many ships as can be completely upgraded will be <a href="#ordb">broken</a> into a new group and upgraded.  Alternatively, if a specific number of ships are ordered upgraded (including 0 to explicitly specify the entire group), exactly that many ships will be upgraded, even if only enough production points are available to do a partial upgrade.  Groups that are partially upgraded have their each technology increased by the percentage of production points available.  The exact formula for a partial upgrade for each technology is:</p>
<pre>Tech increase = (production available / full upgrade cost) * (current tech - ship tech)</pre>
					<p>Production spent on upgrading groups during a turn is deducted from the planet's production for that turn.  Thus, if a planet uses 35% of its production on upgrades, it can only produce 65% as many materials, capital, technology or ships as normal.  If a planet uses its entire production on upgrades, it produces nothing that turn.</p>

			<hr>

			<h2><a name="combat">Combat</a></h2>

				<h3><a name="war">War and Alliances</a></h3>
					<p>At the start of the game all races are assumed to be at war with all the other races (except in team games).  <a href="#orda">Alliances</a> may be declared at the beginning of any turn.  Ships will not initiate combat with allied ships, nor will they bomb allied planets.  However, there is no way to tell if the allied race has also declared an alliance until warships are encountered.  Ships will always shoot back if fired on (battles will be fought just as if both sides were at war with each other; declaring an alliance puts warships at no disadvantage in combat).  Having declared an alliance, <a href="#ordw">war</a> may be declared again at the start of any subsequent turn and vice versa.</p>

				<h3><a name="bat">Battles</a></h3>
				 <p>Battles occur whenever a ship with weapons encounters an enemy ship at a planet.  Ships in hyperspace cannot participate in battles.  In each battle round, randomly select a ship from all surviving ships that have not yet attacked (note that if a ship is destroyed before it gets a chance to fire it will not attack).  For each gun on the ship, randomly select a surviving enemy ship and fire a shot.  Repeat until all ships have fired.  Battle rounds continue until the battle is either a standoff or a win.  A battle is a standoff if all remaining ships are invulnerable to enemy attacks.  A battle is won if all remaining ships belong to races that are allied with each other.</p>
					<p>Attack and defence strengths are calculated using the following forumlae:</p>
<pre>attack strength = (weapons mass * weapons technology)
defence strength = ((shields mass * shields technology) / (ship mass + effective cargo carried mass)^(1/3) * 30^(1/3).</pre>
					<p>If a shot is successful, the enemy ship is destroyed.  The attack forumula is:</p>
<pre>p[kill] = (log[4](attack strength / defence strength) + 1) / 2</pre>
					<p>Where log[4](x)  is the log with base 4 of x, which can be computed with log(x)/log(4).  If the attack strength is four times as strong as the defence strength, the attack will always succeed.  If the defence strength is four times as strong as the attack strength, the attack will always fail.  The numbers are calculated so that if a ship type 10 1 10 10 0 fires at an identical ship, it will have a 50% chance of destroying the target.</p>

				<h3><a name="bomb">Bombing Planets</a></h3>	
					<p>After all battles are resolved, ships with weapons bomb enemy planets, reducing population and industry by 75%.  If only one race has ships with weapons orbiting a bombed planet, that race becomes the new owner of the planet.  If two or more allied races have ships with weapons orbiting a bombed planet, the race that issued a <a href="#ordv">victory</a> command becomes the new owner.  If no race issued a victory command, the race that appears first in the races table of the turn report receives the planet.  If more than one race issued a victory command, or if there was a standoff, the planet becomes unowned and can be claimed by the first race to unload colonists at the planet.</p>

			<hr>

			<h2><a name="orders">Orders</a></h2>
				<p>Players command their race's activities by sending orders to the Galaxy server.  Players can only issue orders for their own groups and planets.</p>
				<p>In the orders documentation below, parameters are indicated as follows:</p>
<pre>&lt;required&gt;
[optional]
option1 | option2 | option3</pre>

				<h3><a name="send">Sending Orders</a></h2>
					<p>Players send orders to the GalaxyNG server using this format:</p>
<pre>  To: server@somewhere.org
From: player@someplace.com
Subject: orders

#GALAXY &lt;gamename&gt; &lt;race-name&gt; &lt;password&gt;
...orders...
#END</pre>

					<p>The subject should be "orders" and the #GALAXY line should be in the body of the message, not in the subject.  It is very important to type this line correctly, as otherwise all of your orders will be discarded.  Everything before the #GALAXY line or after the #END line in the message is ignored by the server.  Replacement sets of orders may be sent anytime before the turn deadline. The last set of orders received will be used by the server when the turn is run.</p>
     
				<h3><a name="fore">Forecast and Errors</a></h3>
					<p>The server sends a forecast and error report to the email address used to send orders.  The forecast is a prediction of the results of the orders sent, assuming no other races exist in the galaxy.  It contains only information about the player's planets and groups, and does not contain information about other races or uninhabited planets.  Errors with the email or with specific orders will be reported to the player so they can be corrected and resent.</p>

				<h3><a name="adv">Advance Orders</a></h3>
					<p>Players can send advance orders if they will be away from email for some time.  The subject should be  "orders &lt;turn number&gt;" - for example "orders 27" for turn 27.  The server
will store the orders (but not check them) and use them when the turn runs.  When sending advance orders, players should <strong>not</strong> change their <a href="#ordn">race name</a> or <a href="#ordy">password</a> when sending advance orders, as this can cause orders to be rejected when the turn runs.</p>

				<h3><a name="#ex">Example Set of Orders</a></h3>
					<p>Writing orders for the first time can be a daunting task, so here is an example set of orders for turn 1.</p>
<pre>#GALAXY Jangi Race_12 P981231231
c Vogons           ; Change race name.
y towel            ; Change password.
= "Arthur Dent"    ; Set player name for Hall of Fame.
n 67 Vogonia       ; Name first home world.
n 68 Ford          ; Name second home world.
n 69 Prefect       ; Name third home world.
d Haul 2 0 0 0 1   ; Design a cargo ship.
p 67 Haul          ; Produce cargo ships at the first home planet.
                   ; Notice that the old name of the planet is used
                   ; as the name change won't go in effect until the
                   ; next turn.
p 68 DRIVE         ; Research drive technology at the second planet.
d Probe 1 0 0 0 0  ; Design a ship for scouting.
p 69 Probe         ; Produce scouting ships at the third planet.
#END</pre>

				<h3><a name="form">Order Format</a></h3>
					<p>Each order is designated by giving a letter or keyword as the first non-blank character on the line, followed by a space.  The program only checks the first letter, so you can either give a whole word or just the letter.  Parameters follow the order, separated by spaces or tabs.  Blank lines are permitted, as are comments; anything (except <a href="#ordA">messages</a>) after a semicolon on a line is treated as a comment and ignored.</p>
					<p>Parameter keywords must be given precisely; unlike orders they cannot be abbreviated or expanded.  The following parameter keywords are used: AMOUNT, CAP, COL, EMP, MAT, DRIVE, WEAPONS, SHIELDS, CARGO, MAX, FLEET.</p>
					<p>All orders involving groups can take an optional last parameter giving the number of ships to be used. If this parameter is given, the indicated number of ships will be <a href="#ordb">broken</a> off into a separate group first, and the order applied only to that separate group.  If the parameter is omitted or if it is 0 (zero), the order will be applied to the entire group.</p>
					<p>The parser is not case sensitive, so all commands and names may be given in upper case, lower case or a mixture of the two. However, when supplying names containing spaces, the name must be surrounded by double quotes, or else underscore characters must be used in place of spaces in the name.  Examples of correct order lines:</p>
<pre>Send 100 "Zzyax Prime"
send 100 zzyax_prime
s 100 "zzyax prime"	; Attack the Zzyaxian homeplanet</pre>
					<p>Examples of incorrect order lines:</p>
<pre>Send 100 Zzyax Prime
s 100 "zzyax prime"	Attack the Zzyaxian homeplanet</pre>

				<h3><a name="ordA">@ [race name ...]</a></h3>
					<p>Send a message to one or more players within their turn reports.  All lines between the order and the next line with an @ symbol as its first non-blank character are treated as message text.  Semicolons between the @ symbols are treated as part of the message, and not as comments.  The server does not indicate the sender, so unsigned messages are anonymous.  The race parameter should be a list of race names separated by spaces.  If no race name is provided, or if a race name is provided with no space between it and the @ symbol, the message will be sent to all races.  This message is sent to all races anonymously:</p>
<pre>@
Hey, everyone, SpaceManSpiff breaks alliances!
@</pre>
					<p>This message is sent to SpaceManSpiff and is signed:</p>
<pre>@ SpaceManSpiff
I'll never trust you again!
- Sparky
@</pre>
					<p>Note that races may also send each other <a href="#email">email</a>.</p>

				<h3><a name="ordE">= &lt;FirstName LastName&gt;</a></h3>
					<p>Set the player's <a href="#players">real name</a> for use in the Hall of Fame.</p>

				<h3><a name="orda">a &lt;race name&gt;</a></h3>
					<p>Declare an <a href="#war">alliance</a> with another race.</p>

				<h3><a name="ordb">b &lt;group number&gt; &lt;number of ships&gt;
				<br>b &lt;group number&gt; FLEET</a></h3>
					<p>Break off a number of ships from a group, forming a new <a href="#groups">group</a>.
					<br><strong>or</strong>
					<br>Remove a group from its current <a href="#fleets">fleet</a>.</p>

				<h3><a name="ordc">c &lt;new race name&gt;</a></h3>
					<p>Change the player's race <a href="#names">name</a>.</p>

				<h3><a name="ordd">d &lt;name&gt; &lt;drive mass&gt; &lt;attacks&gt; &lt;weapons mass&gt; &lt;shields mass&gt; &lt;cargo mass&gt;
				<br>d FLEET &lt;fleet name&gt;</a></h3>
					<p>Design a new <a href="#types">ship type</a> with the given attributes.
					<br><strong>or</strong>
					<br>Create a new <a href="#fleets">fleet</a>.</p>

				<h3><a name="orde">e &lt;ship type name&gt;
				<br>e &lt;fleet name&gt;</a></h3>
					<p>Eliminate a <a href="#types">ship type</a>.
					<br><strong>or</strong>
					<br>Eliminate a <a href="#fleets">fleet</a>.</p>

				<h3><a name="ordf">f &lt;race name&gt;</a></h3>
					<p>Request a <a href="#player">player's</a> email address. If no email address is returned, the player is <a href="#ordo">anonymous</a>, the race is not being played, or the race is being played by the GM.</p>

				<h3><a name="ordg">g &lt;group number&gt; [number of ships]</a></h3>
					<p><a href="#upgrade">Upgrade</a> a group of ships.</p>
     
				<h3><a name="ordh">h &lt;group&gt;</a></h3>
					<p><a href="#move">Reverse</a> the course of a group in hyperspace.</p>

				<h3><a name="ordi">i &lt;group number&gt; &lt;planet name&gt; [number of ships]
				<br>i &lt;fleet name&gt; &lt;planet name&gt;</a></h3>
					<p><a href="#move">Intercept</a> alien groups with a group.
					<br><strong>or</strong>
					<br>Intercept alien groups with a fleet.</p>
				
				<h3><a name="ordj">j &lt;group number&gt; &lt;fleet name&gt; [number of ships]
				<br>j &lt;fleet name&gt; &lt;fleet name&gt;</a></h3>
					<p>Have a group join a <a href="#fleets">fleet</a>.
					<br><strong>or</strong>
					<br>Move all groups from the first fleet to the second fleet, leaving the first fleet empty.</p>
						
				<h3><a name="ordl">l &lt;group number&gt; &lt;CAP | COL | MAT&gt; [number of ships] [AMOUNT &lt;amount&gt;]</a></h3>
					<p>Load <a href="#cargo">cargo</a> onto a group of ships.  Ships will be fully loaded if sufficient cargo is present, otherwise the load will be split evenly between the ships.  The optional amount parameter specifies an amount of cargo to be loaded, which will be evenly divided between the ships.  Specifying an amount of less than 0.01 per ship or more than the total cargo capacity of the group will result in an error.</p>

				<h3><a name="ordm">m &lt;x&gt; &lt;y&gt; &lt;extent&gt;</a></h3>
					<p>Change the area covered by the text map.  The text map is a square with the top left at (x,y) and the extent of each side in light years.  For example, m 10 20 50 will result in a text map with corners at (10,20), (10,70), (60,20) and (60,70).  The <a href="#locate">location</a> of enemy ships in hyperspace is the only unique element on the text map.</p>

				<h3><a name="ordn">n &lt;current planet name&gt; &lt;new planet name&gt;</a></h3>
					<p>Rename a planet.</p>

				<h3><a name="ordo">o [NO] &lt;anonymous | autounload | battleprotocol | compress | gplus | groupforecast | machinereport | planetforecast | prodtable | routesforecast | shiptypeforecast | sortgroups | txtreport | xmlreport&gt;</a></h3>
					<p>Set a game option.  If the NO parameter is included, the option is turned off, otherwise it is turned on.  The following options are turned on at the beginning of the game:</p>
					<ul>
						<li>Anonymous: The player's email address is <a href="#ordf">not available</a> to other players.</li>
						<li>AutoUnload: All <a href="#cargo">cargo</a> will be automatically unloaded at the player's planets and uninhabited planets.</li>
						<li>GroupForecast: The forecast will include a prediction of the position of each group.</li>
						<li>PlanetForecast: The forecast will include a prediction of the status of each planet owned by the player, as well as any planets the might be colonized by the player.</li>
						<li>ProdTable: The report and forecast will include a Ships in Production table.</li>
						<li>RoutesForecast: The forecast will include a prediction of the player's routes.</li>
						<li>ShipTypeForecast: The forecast will include a prediction of the player's ship types.</li>
						<li>SortGroups: <a href="#groups">Groups</a> will be renumbered at the end of the turn.</li>
						<li>TXTReport: Copies of the forecast and report will be sent to the player in ASCII text format.</li>
						<li>XMLReport: Copies of the forecast and report will be sent to the player in XML format.</li>
					</ul>
					<p>The following options are turned off at the beginning of the game:</p>
					<ul>					
						<li>BattleProtocol: The report will include an extra section detailing each shot fired in each battle.  Some turn viewers use this feature to analyze and animate battles.  Turning this option on can significantly increase the size of turn reports.</li>
						<li>Compress: The forecast and report will be compressed (zipped) before being sent to the player.  The GM should be consulted before turning this option on, as it is not supported by all GalaxyNG servers.</li>
						<li>GPlus: The forecast and report will be sent to the player in Galaxy G+ format.  This allows players to use Galaxy G+ turn viewers when playing GalaxyNG.</li>
						<li>MachineReport: Copies of the forecast and report will be sent to the player in a rudimentary machine-readable format.</li>
					</ul>

				<h3><a name="ordp">p &lt;planet name&gt; &lt;CAP | MAT | DRIVE | WEAPONS | SHIELDS | CARGO | ship type name&gt;</a></h3>
					<p>Set <a href="#prod">production</a> for a planet.</a></p>

				<h3><a name="ordq">q &lt;race name&gt;</a></h3>
					<p>Quit the game. The race name is required as a parameter to protect players from accidentally quitting.</p>

				<h3><a name="ordr">r &lt;origin planet name&gt; &lt;CAP | COL | EMP | MAT&gt; [destination planet name]</a></h3>
					<p>Set a <a href="#route">route</a>.  Omitting the destination planet cancels an existing route.</p>

				<h3><a name="ords">s &lt;group number&gt; &lt;planet name&gt; [number of ships]
				<br>s &lt;fleet name&gt; &lt;planet name&gt;</a></h3>
					<p><a href="#move">Send</a> a group to a planet.
					<br><strong>or</strong>
					<br>Send a fleet to a planet.</p>


				<h3><a name="ordt">t &lt;current ship type name&gt; &lt;new ship type name&gt;
				<br>t &lt;current fleet name&gt; &lt;new fleet name&gt;</a></h3>
					<p>Change the name of a <a href="#types">ship type</a>.
					<br><strong>or</strong>
					<br>Change the name of a <a href="#fleets">fleet</a>.</p>

				<h3><a name="ordu">u &lt;group number&gt; [number of ships] [AMOUNT &lt;amount&gt;]</a></h3>
					<p>Unload <a href="#cargo">cargo</a> from a group of ships.  The optional amount parameter specifies an amount of cargo to be unloaded, which will be evenly divided between the ships.  Specifying an amount of less than 0.01 per ship or more than the total cargo carried by the group will result in an error.</p>

				<h3><a name="ordv">v &lt;planet name&gt;</a></h3>
					<p>Claim victory over an enemy planet if it is <a href="#bomb">bombed</a>.</p>

				<h3><a name="ordw">w &lt;race name&gt;</a></h3>
					<p>Cancel an alliance with another race, declaring <a href="#war">war</a>.</p>

				<h3><a name="ordx">x &lt;group number&gt; [number of ships]</a></h3>
					<p><a href="#groups">Scrap</a> a group, converting the ships into materials.  Scrapping ship that are carrying colonists or orbiting an alien planet will result in an error.</a>

				<h3><a name="ordy">y &lt;new password&gt;</a></h3>
					<p>Change the player's <a href="#orders">password</a>.</p>

				<h3><a name="ordz">z &lt;new email address&gt;</a></h3>
					<p>Change the player's <a href="#orders">email address</a>.</p>






<hr>

<h2><a name="#turns">Turns</a></h2>

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

<hr>

<h2><a name="#afewnotes">A few things to note</a></h2>

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

<h2><a name="#inactive">Inactivity</a></h2>

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


<h2><a name="#reports">Turn Reports</a></h2>

<p>After each turn runs you will receive a turn report with information
on the state of your race. If you don't play in a game yet,
you might want to look at some 
<a href="example.html">example reports</a>.</p>

<p> Your turn report will contain some or all of the following
sections: </p>

<h3><a name="#repopt">Your Options</a></h3>

<p> A list with all the options that are available. It shows if you
have switched an option on or off.  
To switch options on or off use the <a href="ordo">O order</a>.
</p>


<h3><a name="#repmes">Messages</a></h3>

<p>Messages from other players. You can send your own messages
by using the <a href="#ordat">@ command</a></p>


<h3><a name="#repmis">Mistakes</a></h3>

<p>Any mistakes in your orders.</p>


<h3><a name="#repstat">Status of Players</a></h3>

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


<h3><a name="#repyst">Your Ship Types</a></h3>

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


<h3><a name="#repast">Alien Ship Types</a></h3>

<p> This is a description of each type of alien ship that you have
come into contact with this turn; the information provided is the same
as for your ship types.  </p>


<h3><a name="#repbat">Battles</a></h3>

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


<h3><a name="#repbp">Battle Protocol</a></h3>

<p> Tels you which ships fired on which ship and whether the ship
survived.  You only get this when you switch on the option
BattleProtocol.  </p>


<h3><a name="#repbom">Bombings</a></h3>


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


<h3><a name="#repmap">Map</a></h3>

<p> This is a map of all or part of the galaxy. Symbols on the map
have the following meanings:</p>

<ol>
<li>*  - Your Planet</li>
<li>o  - Uninhabited Planet</li>
<li>+  - Alien Planet</li>
<li>.  - Your Ships</li>
<li>-  - Alien Ships</li>
</ol>


<h3><a name="#repigr">Incoming Groups</a></h3>

<p> This is a list of all the groups of alien ships currently heading
for planets owned by you. The following information is provided: </p>

<ol>
<li>Origin (which planet the group came from)</li>
<li>Destination (which planet the group is heading towards)</li>
<li>Distance Remaining</li>
<li>Speed</li>
<li>Total Mass</li>
</ol>


<h3><a name="#repypl">Your Planets</a></h3>

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


<h3><a name="#repsip">Ships In Production</a></h3>

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


<h3><a name="#reproute">Your Routes</a></h3>

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


<h3><a name="#repapln">Alien Planets</a></h3>

<p> This is a list of all those planets owned by another player, at
which you have at least one ship and which you can therefore
observe. The same information is provided as for your planets.  </p>


<h3><a name="#repuinpl">Unidentified Planets</a></h3>

<p> This is a list of those planets owned by another player, which
appear on your map but which you cannot observe. Only the name of the
planet and the X and Y coordinates are available. (Occasionally, due
to roundoff errors, a planet will appear at the edge of the map but
not be listed, or vice versa.)  </p>


<h3><a name="#repuninhab">Uninhabited Planets</a></h3>

<p> This is a list of uninhabited planets which appear on your map, or
which you can observe. For all planets on the list, the name and X and
Y coordinates are provided. For those planets which you can observe,
the Size and Natural Resources attributes are also listed.  </p>



<h3><a name="#repygrps">Your Groups</a>

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



<h3><a name="#repyflts">Your Fleets</a></h3>

<p> You will get a table for each fleet.  The header for each fleet
will be: </p>

<pre>
         `Fleet fleetname (Speed fleetspeed)'
</pre>

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



<h3><a name="#repagrps">Alien Groups</a></h3>

<p> This is a list of groups of ships belonging to other players,
which you can observe. The information provided is the same as for
your groups except without the group numbers.  </p>


<h3><a name="#copyreport">Getting a Copy a Turn Report</a></h3>

<p> You can get a copy of a turn report by sending an email to the
server. The message should contain one line: </p>

<pre>
#GALAXY &lt;gamename&gt; &lt;race-name&gt; &lt;password&gt;
</pre>

<p>As subject for the message use "report &lt;turn number&gt;".  The
server will send you a copy of the report for that turn.  The
copy is send to the email address you send the orders from.  You can
use this feature to get a copy of your report in case your ISP fails
for some reason.  </p>


<h2><a name="#hints">Hints and Tips</a></h2>

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

<h2><a name="#moreinfo">Links to More Information</a></h2>

<ol>
  <li><a href="http://badcheese.com/~steve/phpwiki/index.php/GalaxyPlay">GalaxyNG Wiki</a></li>
  <li><a href="quickref.html">Quick Reference Manual</a></li>
  <li><a href="faq.html">GalaxyNG FAQ</a></li>
</ol>

</body>
</html>
