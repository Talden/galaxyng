<?php echo '<?xml version="1.0" encoding="iso-8859-1"?>'; ?> 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
   "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US">

<!-- $Id$ -->

	<head>
		<link rel="stylesheet" href="main.css" />
		<title>GalaxyNG Quick Reference</title>
	</head>

	<body>
		<h1>GalaxyNG Quick Reference</h1>
			<table>

				
				
				<tr><th colspan="2">Planet Orders</th></tr>
					<tr><td>Produce</td><td>&nbsp;<a href="manual.php#ordp">p &lt;planet name&gt; &lt;CAP | MAT | DRIVE | WEAPONS | SHIELDS | CARGO | ship type name&gt;</a></td></tr>
					<tr><td>Route</td><td>&nbsp;<a href="manual.php#ordr">r &lt;origin planet name&gt; &lt;CAP | COL | EMP | MAT&gt; [destination planet name]</a></td></tr>
					<tr><td>Victory</td><td>&nbsp;<a href="manual.php#ordv">v &lt;planet name&gt;</a></td></tr>
					<tr><td>Rename</td><td>&nbsp;<a href="manual.php#ordn">n &lt;current planet name&gt; &lt;new planet name&gt;</a></td></tr>
			
				
				
				<tr><th colspan="2">Ship Type Orders</th></tr>
					<tr><td>Design</td><td>&nbsp;<a href="manual.php#ordd">d &lt;name&gt; &lt;drive mass&gt; &lt;attacks&gt; &lt;weapons mass&gt; &lt;shields mass&gt; &lt;cargo mass&gt;</a></td></tr>
					<tr><td>Rename</td><td>&nbsp;<a href="manual.php#ordt">t &lt;current ship type name&gt; &lt;new ship type name&gt;</a></td></tr>
					<tr><td>Eliminate</td><td>&nbsp;<a href="manual.php#orde">e &lt;ship type name&gt;</a></td></tr>
					
					
					
				<tr><th colspan="2">Group Orders</th></tr>
					<tr><td>Send</td><td>&nbsp;<a href="manual.php#ords">s &lt;group number&gt; &lt;planet name&gt; [number of ships]</a></td></tr>
					<tr><td>Intercept</td><td>&nbsp;<a href="manual.php#ordi">i &lt;group number&gt; &lt;planet name&gt; [number of ships]</a></td></tr>
					<tr><td>Load</td><td>&nbsp;<a href="manual.php#ordl">l &lt;group number&gt; &lt;CAP | COL | MAT&gt; [number of ships] [AMOUNT &lt;amount&gt;]</a></td></tr>
					<tr><td>Unload</td><td>&nbsp;<a href="manual.php#ordu">u &lt;group number&gt; [number of ships] [AMOUNT &lt;amount&gt;]</a></td></tr>
					<tr><td>Upgrade</td><td>&nbsp;<a href="manual.php#ordg">g &lt;group number&gt; [number of ships]</a></td></tr>
					<tr><td>Break off</td><td>&nbsp;<a href="manual.php#ordb">b &lt;group number&gt; &lt;number of ships&gt;</a></td></tr>
					<tr><td>Scrap</td><td>&nbsp;<a href="manual.php#ordx">x &lt;group number&gt; [number of ships]</a></td></tr>
					
				
				
				<tr><th colspan="2">Fleet Orders</th></tr>
					<tr><td>Send</td><td>&nbsp;<a href="manual.php#ords">s &lt;fleet name&gt; &lt;planet name&gt;</a></td></tr>
					<tr><td>Intercept</td><td>&nbsp;<a href="manual.php#ordi">i &lt;fleet name&gt; &lt;planet name&gt;</a></td></tr>
					<tr><td>Design</td><td>&nbsp;<a href="manual.php#ordd">d FLEET &lt;fleet name&gt;</a></td></tr>
					<tr><td>Join</td><td>&nbsp;<a href="manual.php#ordj">j &lt;group number&gt; &lt;fleet name&gt; [number of ships]</a></td></tr>
					<tr><td>Leave</td><td>&nbsp;<a href="manual.php#ordb">b &lt;group number&gt; FLEET</a></td></tr>
					<tr><td>Eliminate</td><td>&nbsp;<a href="manual.php#orde">e &lt;fleet name&gt;</a></td></tr>
					<tr><td>Merge</td><td>&nbsp;<a href="manual.php#ordj">j &lt;fleet name&gt; &lt;fleet name&gt;</a></td></tr>
					<tr><td>Rename</td><td>&nbsp;<a href="manual.php#ordt">t &lt;current fleet name&gt; &lt;new fleet name&gt;</a></td></tr>
					
				
				
				<tr><th colspan="2">Player Orders</th></tr>
					<tr><td>Player</td><td>&nbsp;<a href="manual.php#ordE">= &lt;FirstName LastName&gt;</a></td></tr>
					<tr><td>Race</td><td>&nbsp;<a href="manual.php#ordc">c &lt;new player race name&gt;</a></td></tr>
					<tr><td>Map</td><td>&nbsp;<a href="manual.php#ordm">m &lt;x&gt; &lt;y&gt; &lt;extent&gt;</a></td></tr>
					<tr><td>Options</td><td>&nbsp;<a href="manual.php#ordo">o [NO] &lt;anonymous | autounload | battleprotocol | compress | gplus | groupforecast | machinereport | planetforecast | prodtable | routesforecast | shiptypeforecast | sortgroups | txtreport | xmlreport&gt;</a></td></tr>
					<tr><td>Password</td><td>&nbsp;<a href="manual.php#ordy">y &lt;new password&gt;</a></td></tr>
					<tr><td>Email</td><td>&nbsp;<a href="manual.php#ordz">z &lt;new email address&gt;</a></td></tr>
					<tr><td>Quit</td><td>&nbsp;<a href="manual.php#ordq">q &lt;player's race name&gt;</a></td></tr>
					
				
				
				<tr><th colspan="2">Race Orders</th></tr>
					<tr><td>Message</td><td>&nbsp;<a href="manual.php#ordA">@ [alien race name...]</a></td></tr>
					<tr><td>Alliance</td><td>&nbsp;<a href="manual.php#orda">a &lt;alien race name&gt;</a></td></tr>
					<tr><td>Find email</td><td>&nbsp;<a href="manual.php#ordf">f &lt;alien race name&gt;</a></td></tr>
					<tr><td>War</td><td>&nbsp;<a href="manual.php#ordw">w &lt;alien race name&gt;</a></td></tr>
			</table>
 		
 		<?php include 'footer.php'; ?>
 	</body>
</html> 	