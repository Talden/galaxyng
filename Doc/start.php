<?php echo '<?xml version="1.0" encoding="iso-8859-1"?>'; ?> 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
   "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US">

<!-- $Id$ -->

	<head>
		<link rel="stylesheet" href="main.css" />
		<title>GalaxyNG Getting Started</title>
		<?php $title="Getting Started"; ?>
	</head>

	<body>
		<?php include 'menu.php'; ?>
			
			<h2>Join a new game:</h2>
					<p>To join a new game send an email to the GalaxyNG game server (e.g. <tt>server@somewhere.com</tt>) with the subject "<tt>Join GameName</tt>." You will receive a confirmation email from the server.  To find a game, <a href="http://lists.sourceforge.net/lists/listinfo/galaxyng-players">subscribe to GalaxyNG-Players</a> or visit a GalaxyNG server:</p>
				<ul>
					<!--<li><a href="http://www.gioco.net/galaxy/">GalaxyNG GIGA Server</a> (Italian)</li>-->
					<li><a href="http://galaxy.gesserit.net/">Nine Lives GalaxyNG Server</a></li>
					<li><a href="http://www.refs-home.net/galaxyng/">REF's GalaxyNG Site</a></li>
				</ul>
				
			<hr />
			
			<h2>Get a turn viewer:</h2>
				<p>To display the map and create orders, download a <a href="http://galaxyview.sourceforge.net/tools.html">turn viewer</a>. Galaxyview and MkGal are very popular.  Download some <a href="turns.php">turn reports and orders</a> so you can experiment with the turn viewer.</p>
			
			<hr />
			
			<h2>Learn about the game:</h2>
				<ul>
					<li><a href="manual.php">Players Manual</a></li>
					<li><a href="quickref.php">Quick Reference</a></li>
					<li><a href="faq.php">FAQ</a></li>
					<li><a href="etiquette.php">Galaxy Etiquette</a></li>
					<li><a href="http://web.archive.org/web/20011006200732/http://www.jacobean.demon.co.uk/galaxy/galaxy.beginner.txt">Beginner's Guide</a> (Note that it is not completely accurate in all details, as it describes original Galaxy and not GalaxyNG.)</li>
					<li>Howard Bampton's <a href="http://www.indyramp.com/galaxy/strategy.html">Ship Design in Galaxy and Blind Galaxy</a></li>
					<li><a href="http://web.archive.org/web/20011005182146/http://www.jacobean.demon.co.uk/galaxy/tips.html">Tim's Galaxy Tips and Tricks</a></li>
					<li>Jacco van Weert's Galaxy Military Strategy Guide <a href="http://web.archive.org/web/20010216194758/www.jacobean.demon.co.uk/galaxy/galstrat1.html">Part 1</a> |<a href="http://web.archive.org/web/20010216194758/www.jacobean.demon.co.uk/galaxy/galstrat2.html">Part 2</a> |<a href="http://web.archive.org/web/20010216194758/www.jacobean.demon.co.uk/galaxy/galstrat3.html">Part 3</a> |<a href="http://web.archive.org/web/20010216194758/www.jacobean.demon.co.uk/galaxy/galstrat4.html">Part 4</a> (You have to read this to be able to survive more than a few turns.)</li>
				</ul>
			
			<hr />
			
			<h2>Ask for help:</h2>
				<p>Players and GMs alike will be happy to help you.  Ask questions on the <a href="http://lists.sourceforge.net/lists/listinfo/galaxyng-players">GalaxyNG-Players mailing list</a> or send an email to your GM.</p>
			
			<hr />
			
			<h2>Submit orders for the first turn:</h2>
					<p>When the game begins, you will receive a Turn 0 report. You <span class="bold">must</span> send your first <a href="http://galaxyng.sourceforge.net/manual.php#orders">set of orders</a> prior to Turn 1 deadline, and continue sending orders on subsequent turns, otherwise you will be <a href="http://galaxyng.sourceforge.net/manual.php#inactive">eliminated from the game</a>. Send an email to the GalaxyNG server with the subject "<tt>orders</tt>." The first line of your orders should be "<tt>#GALAXY <em>GameName</em> <em>RaceName</em> <em>Password</em></tt>" and the last line should be "<tt>#END</tt>."</p>
					
				<hr />
				
				<h2>Send anonymous email to other races:</h2>
					<p>Send an email to the GalaxyNG server with the subject "<tt>relay <em>RaceName</em></tt>". The first line of the message should be "<tt>#GALAXY <em>GameName</em> <em>RaceName</em> <em>Password</em></tt>."  The body of your message <a href="http://galaxyng.sourceforge.net/manual.php">will be relayed</a> to the other player by the server. Remember to end your message with "<tt>#END</tt>" to prevent your opponents from reading your signature. Also, if you send your message in HTML or HTML+text, the other player will get a copy of your email address, racename and password - causing all kinds of havoc! Make sure that your email client <a href="http://www.expita.com/nomime.html">sends plain ASCII text only</a>.</p>
					
				<hr />
				
				<h2>Conquer the galaxy:</h2>
					<p>Hard work and experience will pay off in the end, as you conquer the galaxy and destroy your enemies!</p>
 		
 		<?php include 'footer.php'; ?>
 	</body>
</html> 	