<?php echo '<?xml version="1.0" encoding="UTF-8"?>'; ?> 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
   "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US">

<!-- $Id$ -->

	<head>
		<meta name="description" content="Galaxy Next Generation, GalaxyNG, pbem, interstellar wargame, computer game, strategy wargame, galaxy pbem game" />
		<meta name="keywords" content="Galaxy Next Generation, GalaxyNG, pbem, interstellar wargame, computer game, strategy wargame, galaxy pbem game" />
		<link rel="stylesheet" href="main.css" />
		<title>GalaxyNG</title>
		<?php $title="GalaxyNG Home"; ?>
	</head>

	<body>
		<?php include 'menu.php'; ?>
		
			<h2>Introduction</h2>
				<p>GalaxyNG (Galaxy Next Generation) is a free play-by-email (PBeM) interstellar strategy wargame for multiple players. Each player gets to play one race in a galaxy filled with many planets. Races begin with one or more populated homeworlds and the other planets are empty. The object of the game is to conquer the galaxy by colonizing and developing uninhabited planets, researching drive/weapons/shield/cargo technology, building warships and attacking neighboring races. Players use <a href="http://galaxyview.sourceforge.net/tools.html">turn viewers</a> to display the map and create commands (orders). You email orders to the GalaxyNG game server and the server sends you the expected results (forecasts) of your commands. If you are not satisfied with your orders, you can resubmit them over and over again until the turn deadline. When the server runs the turn at the designated time, all players' commands are executed simultaneously. You receive a turn report and can then start preparing orders for the next turn. Most games run two or three turns a week. Winners are listed in the <a href="hall.php">Hall of Fame</a>.</p>
				<p>If you haven't played, try <a href="start.php">GalaxyNG Getting Started</a>.</p>
			
			<hr />
			
			<h2>New Games</h2>			
				<p>New games are announced on the <a href="http://lists.sourceforge.net/lists/listinfo/galaxyng-players">galaxyng-players mailing list</a> and on GalaxyNG servers:</p>
				<?php include 'newgames.php'; ?>
			
			<hr />
			
			<h2>Active Games</h2>
				<?php include 'activegames.php'; ?>

			
			<hr />

			<h2>Completed Games</h2>
				<p>The deeds and exploits of GalaxyNG champions are chronicled in the <a href="hall.php">Hall of Fame</a>.</p>
				
			<hr />

			<h2>Development</h2>
				<p>GalaxyNG is an open source project <a href="http://sourceforge.net/projects/galaxyng/">hosted on SourceForge.net</a>.  Assistance, comments, suggestions and chocolate chip cookies are always <a href="http://sourceforge.net/projects/galaxyng/">welcome</a>.</p>

 		<?php include 'footer.php'; ?>
 	</body>
</html>
