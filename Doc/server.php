<?php echo '<?xml version="1.0" encoding="UTF-8"?>'; ?> 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
   "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US">

<!-- $Id$ -->

	<head>
		<link rel="stylesheet" href="main.css" />
		<title>GalaxyNG Server Manual</title>
		<?php $title="GalaxyNG Server Manual"; ?>
	</head>

	<body>
		<h1><a href="<?php include 'base_url.txt'; ?>"><img src="galaxyngsmall.png" alt="GalaxyNG" /></a><br>Server Manual</h1>

			<hr />

			<h2>Table of Contents</h2>
				<ul>
					<li><a href="#intro">Introduction</a></li>
					<li><a href="#compile">Compilation</a></li>
					<li><a href="#install">Installation</a></li>
					<li><a href="#files">Files and Directories</a></li>
					<li><a href="#config">Configuration</a></li>
					<li><a href="#use">Use</a></li>
					<li><a href="#register">Game Registration</a></li>
					<li><a href="#create">Creating a New Game</a></li>
					<li><a href="#mail">Mailing the Turn 0 Reports</a></li>
 					<li><a href="#process">Processing Orders</a></li>
					<li><a href="#auto">Auto Checking Orders</a></li>
					<li><a href="#run">Running Turns</a></li>
					<li><a href="#command">Command Summary</a></li>
					<li><a href="#ex">Example Files</a></li>
					<li><a href="#host">Hosting Team Games</a></li>
				</ul>
 				
 			<hr />
 			
 			<h2 id="intro">Introduction</h2>
 			
				<p>The two basic items to host a game are a Linux box and an internet connection. GalaxyNG should compile and run right out of the box on Linux. This software is required:</p>
<pre>C (gcc) compiler; to compile the server 
crontab; to automatically run turns at a given time 
procmail; to automatically process in comming orders</pre>
				<p>The GalaxyNG server is command line based, so you don't need X-windows. It requires little memory, and even runs on a 2 MB Amiga. Depending on the mumber of players and planets, you need up to 20 MB of disk space per game. It isn't so much that the GalaxyNG server large but that the data files can become quite large. For instance, turn reports with the battleprotocol option enabled can be 500 KB. So if there are 30 players left, this would amount to 15 MB of disk space just to store the reports before they are sent. In these times of GB hard disks this should not be a problem though :)</p>
				<p>It isn't that difficult to start up your own game. It takes a while to configure the server and set up a game, but once it runs it needs pratically no time at all. The whole process is automated, except for a possible bug fix or answering questions. Before you run a game you should make sure you have enough time, and a connection to the internet for at least one year, since games can run that long. If you start a game, please continue it to the end, as it is very frustrating for players if a game just ends somewhere in the middle without comming to a conclusion.</p>

			<hr />
 			
			<h2 id="compile">Compilation</h2>
				<p>To extract the code, run:</p>
<pre>tar -xvzf galaxy-#.tar.gz</pre>
				<p>This creates the directory <tt>NG/</tt>. 				
				<p>Most of the configuration is done after compilation and is handled by the program <tt>NG/install.sh</tt>.  Before compiling the GalaxyNG server you should review <tt>NG/Source/makefile</tt> to make sure it fit your computer's configuration.  The following variables can be configured:</p>
<pre>CC     = gcc
CFLAGS = -Wall -pedantic -g 
LIBS   = -lm</pre>
				<p>The above settings are valid for most systems that have <tt>GCC</tt> installed. They have been tested on Debian, Slackware, SuSE, and RedHat systems and should compile without changes on most Linux boxes.  Do not add any optimization options otherwise the code will not function properly! The server only runs a couple of times per week, so speed is not an issue.</p>
				<p>To compile the code, in the <tt>NG/</tt> directory run:</p>
<pre>make</pre>
				<p>This creates the executable <tt>NG/Source/galaxyng</tt>.</p> 

			<hr />

			<h2 id="install">Installation</h2>
				<p>To install the GalaxyNG server, in the <tt>NG/</tt> directory run:</p>
<pre>make install</pre>
				<p>It creates <tt>$HOME/Games</tt> and installs a number of files in it.</p>
				<p>To install the GalaxyNG server in a different directory, you must edit the first line of <tt>NG/install.sh</tt>.  You also <strong>must</strong> set the environment variable <tt>GALAXYNGHOME</tt> to this directory.  You can do this by adding a line to your <tt>.bash_profile</tt> file (or the appropriate file for your favourite shell).  For instance, if you have installed the GalaxyNG server in <tt>/home/gng/mygames</tt>, add:</p>
<pre>export GALAXYNGHOME=/home/gng/mygames</pre>

			<hr />

			<h2 id="files">Files and Directories</h2>
				<p>The following files are created.</p>
				<table>
					<tr>
						<th>File</th>
						<th>Explanation</th>
					</tr>
					<tr>
						<td><tt>Games/galaxyng</tt></td>
						<td>The server program.  You use it to create new games, check orders, and run turns.</td>
					</tr>
					<tr>
						<td><tt>Games/run_game</tt></td>
						<td>A shell script to run a game.  It is used in combination with cron, and allows you to automatically run turns at specified times.</td>
					</tr>
					<tr>
						<td><tt>Games/procmailrc</tt></td>
						<td>An example .procmailrc file. This contains the commands to automatically process incoming orders and other email received by the server. Edit it with your own local settings and copy it to <tt>$HOME/.procmail</tt>.</td>
					</tr>
					<tr>
						<td><tt>Games/.galaxyngrc</tt></td>
						<td>The server configuration file.  The installation script tries to figure out the location of <tt>sendmail</tt> and <tt>formail</tt>.  It also asks for the GM email address.</td>
					</tr>
				</table>
				<p>The installation program also creates a number of directories:</p>
				<table>
					<tr>
						<th>Directory</th>
						<th>Explanation</th>
					</tr>
					<tr>
						<td><tt>Games/data/</tt></td>
						<td>Game data is stored in a subdirectory for each game.</td>
					</tr>
					<tr>
						<td><tt>Games/orders/</tt></td>
						<td>Players' orders are stored in a subdirectory for each game, with the name <tt>&lt;nation_name&gt;.&lt;turn_number&gt;</tt>.</td>
					</tr>
					<tr>
						<td><tt>Games/forecasts/</tt></td>
						<td>Forecasts are stored in a subdirectory for each game. This is only used for debugging the program.</td>
					</tr>
					<tr>
						<td><tt>Games/reports/</tt></td>
						<td>Turn reports are stored in a subdirectory for each game. This is only used for debugging the program.</td>
					</tr>
					<tr>
						<td><tt>Games/log/</tt></td>
						<td>Contains log files that contain information on processed orders, and game runs.</td>
					</tr>
					<tr>
						<td><tt>Games/statistics/</tt></td>
						<td>For experimental purposes.</td>
					</tr>
					<tr>
						<td><tt>Games/notices/</tt></td>
						<td>This contains game notices. You can use these to provide additional information to the turn reports.</td>
					</tr>
				</table>
				<p>There are three kind of notices available:</p>
				<table>
					<tr>
						<th>Notice</th>
						<th>Explanation</th>
					</tr>
					<tr>
						<td><tt>Games/notices/global.bulletin</tt></td>
						<td>Information that applies to all your games.</td>
					</tr>
					<tr>
						<td><tt>Games/notices/&lt;game name&gt;.info</tt></td>
						<td>Information that applies to a particular game.</td>
					</tr>
					<tr>
						<td><tt>Games/notices/&lt;game name&gt;.&lt;turn number&gt;.notice</tt></td>
						<td>Information that applies to a particular turn of a game.</td>
					</tr>
				</table>

			<hr />

			<h2 id="config">Configuration</h2>
				<p>The server is configured with a <tt>.galaxyngrc</tt> file. The server looks for this file in the directory <tt>$HOME/Games/</tt>. It also looks for the file in <tt>$HOME/Games/data/&lt;game name&gt;/</tt>, whcih overrides the global settings for that particular game. A documented <tt>.galaxyngrc</tt> file can be found in the <tt>Doc/</tt> directory. You can use it to specify the following parameters:</p>
				<table>
					<tr>
						<th>Parameter</th>
						<th>Explanation</th>
					</tr>
					<tr>
						<td><tt>GMemail</tt></td>
						<td>The GM email address.  If this is not present, the GM report will not be mailed.</td>
					</tr>
					<tr>
						<td><tt>sendmail</tt></td>
						<td>The command that is used to send email, usually <tt>{ /usr/sbin/sendmail -t }</tt>.</td>
					</tr>
					<tr>
						<td><tt>compress</tt></td>
						<td>The command that is used to compress email, usually <tt>{ /usr/bin/zip }</tt>.</td>
					</tr>
					<tr>
						<td><tt>encode</tt></td>
						<td>The command that is used to attach compressed files to email, usually <tt>{ /usr/bin/mmencode }</tt> or or <tt>{ /usr/bin/mimencode }</tt> or <tt>{ /usr/bin/uuencode }</tt>.</td>
					</tr>
					<tr>
						<td><tt>StartTime</tt></td>
						<td>On some systems cron behaves a bit oddly after a system reset, and re-runs many old cron jobs. You can use the following option to protect against this.  The server will refuse to run a turn if the current time is not almost equal to the time specified.  A start time of 13:00 would only run a turn if the current time is between 13:00 and 13:09. (It treats the last digit of the time as a wild card, so specifying 13:05 would have the same effect.)</td>
					</tr>
				</table>

			<hr />

			<h2 id="use">Use</h2>
				<p>Running a galaxy game consists of steps:</p>
				<ol>
					<li>register players,</li>
					<li>create a new game,</li>
					<li>mail the turn 0 report,</li>
					<li>check and store the orders that the players sent in,</li>
					<li>run a turn,</li>
					<li>mail the turn reports.</li>
				</ol>
				<p>Then repeat steps 4, 5, and 6 until the players request the game be stopped.</p>

			<hr />

			<h2 id="register">Game Registration</h2>
				<p>Game registration is handled by the Automatic Registration Engine (ARE), which is invoked by procmail.  See the files in /ARE for more details.  You will need to manually configure the ARE.</p>

			<hr />

			<h2 id="create">Creating a New Game</h2>
				<p>To create a game use the command:</p>
<pre>./galaxyng -create &lt;specification file&gt;</pre>
				<p>The game configuration file specifies the structure of the galaxy: number of home, empty, and stuff planets; size and name of the galaxy; the email address of each of the players; and some game options.</p>
				<p>You can create a template game configuration file by using the <tt>-template</tt> command.</p>
<pre>./galaxyng -template &lt;game name&gt; &lt;number of players&gt;</pre>
				<p>This creates a file named <tt>&lt;game name&gt;.glx</tt> with default values for all parameters, plus documentation about what each parameter does.  You will have to edit this file to insert the email addresses of the players. For instance, say you have eight players to play in a galaxy game, and want to call the game Orion. You can then create the game as follows:</p>
<pre>./galaxyng -template Orion 8</pre>
				<p>Edit the <tt>Orion.glx</tt> and change the dummy email addresses to the real email addresses of the players, then run:</p>
<pre>./galaxyng -create Orion.glx</pre>
				<p>The server gives a detailed list of what it is doing and what planets are created. When the game is created a map is printed.  A lot of output is created so you might want to redirect the output of the server to some file, say <tt>orionlayout.txt</tt>:</p>
<pre>./galaxyng -create Orion.glx  &gt; orionlayout.txt</pre>

			<hr />

			<h2 id="mail">Mailing the Turn 0 Reports</h2>
				<p>If you are happy with the galaxy you created, you can mail the turn 0 reports with:</p>
<pre>./galaxyng -mail0 &lt;game name&gt;</pre>
				<p>Before you start any real games you might want to try to run a couple of test games with yourself as player. This way you can see if everything works OK.</p>
				<p>So:</p>
<pre>./galaxyng -mail0 Orion</pre>
				<p>for your Orion game.</p>

			<hr />

			<h2 id="process">Processing Orders</h2>
				<p>When you receive orders from a player, you can store and check them with the following command:</p>
<pre>./galaxyng -check &lt; &lt;file with orders&gt;</pre>
				<p>The file with orders has to be a properly formatted email message, with a To: field and a Subject: field with the word "orders" in it.</p>
				<p>The orders are stored in the directory <tt>orders/&lt;game name&gt;</tt> and the program sends a forecast to the player. A log file is kept of all orders that are checked. It can be found at <tt>$HOME/Games/log/orders_processed.txt</tt>.</p>

			<hr />

			<h2 id="auto">Auto Checking Orders</h2>
				<p>Checking orders and running turns by hand is of course a very cumbersome process that is best automated with <tt>procmail</tt> and <tt>formail</tt>. They are programs that can reformat and process incoming emails.</p>
				<p>If you have never used <tt>procmail</tt> before, read the man pages, and then use the example procmailrc installed in <tt>$HOME/Games/procmailrc</tt>.</p>
				<p>Procmail can be difficult to get working.  On some systems <tt>procmail</tt> works by just creating a <tt>.procmailrc</tt> file in your home directory.  On other systems you have to create a <tt>.forward</tt> file, that contains <tt>| /usr/bin/procmail</tt> to get <tt>procmail</tt> to work.</p>
				<p>Each entry in a <tt>.procmailrc</tt> defines a recipe that tells what has to be done to a message and under what condition. The recipe for order messages looks as follows.</p>
<pre>:0 rw :turno
* ^Subject:.*order
|/usr/bin/formail -rkbt -s $HOME/Games/galaxyng -check</pre>
				<p>Translated it means: if the subject of the message contains the word "order", pipe the message to <tt>formail</tt>. The condition is case insensitive, so Order, or ORDER also works. A lock file with the name turno.lock is used to prevent the simultaneous execution of the same recipe if two or more message that arrive at the same time.</p>
				<p><tt>formail</tt> reformats the message. All mail header lines are thrown away. A <tt>To:</tt> line is generated with the address of person that sent the message. A <tt>Subject:</tt> line is generated, with the original subject prepended with <tt>Re:</tt>. This together with the body of the message is fed to the GalaxyNG server to run the check command.</p>
				<p>The server will analyze the orders in the body, and send a reply to the person that sent the message.</p>
				<p>There are similar entries for the commands to request a copy of a turn report and relay messages to other players. You will find them in <tt>Games/procmailrc</tt>.</p>
				<p>If you want to keep a copy of the orders players send in, you can use the following entry:</p>
<pre># Someone sent in orders, check them
:0
* ^Subject:.*order
{
	:0 c
	$HOME/mail/orders
	:0 rw:order.lock
	|/usr/bin/formail -rkbt -s /home/gng/Games/galaxyng -check
}

</pre>
				<p>Do not use:</p>
<pre># Someone sent-in orders, check them
:0 rw :order.lock
* ^Subject:.*order
{
	:0 c
	$HOME/mail/orders
	:0
	|/usr/bin/formail -rkbt -s /home/gng/Games/galaxyng -check
}</pre>
				<p>In this case procmail ignores the lock file, and it can happen that when two players send in orders shortly after each other the orders of the first player are overwritten.</p>

			<hr />

			<h2 id="run">Running Turns</h2>
				<p>When it is time to run a turn you do this with:</p>
<pre>./run_game &lt;game name&gt;</pre>
				<p>This shell script collects all orders in one file, runs the turn based on these orders, and then sends out all the turn reports to the players.  It also creates high-score lists in HTML and places it in your <tt>$HOME/public_html</tt> directory, if you have one.  You can edit the script and add other commands that need to be run for each turn.</p>
				<p>After each turn you are sent a GM status report. It tells you whether the turn ran successfully. It is especially handy if the server runs on some remote computer. It also contains information on the status of all nations in the game, a list of all bombings and a map. That way you can follow the game.</p>
				<p>If for some reason there was a problem with a turn, you can rerun it by executing:</p>
<pre>./run_game &lt;game name&gt; &lt;turn&gt;</pre>
				<p>The game will be rerun and new turn reports are sent to the players.  This only works for turns that already ran.</p>
				<p>Although it is simple to run a turn it becomes cumbersome after a few turns. Automization is again the solution. You can do this with cron. For instance if you have a game called Orion, that runs on Monday, Wednesday, and Friday around 21:15 hours, you can use the following cron file:</p>
<pre>#           day            day 
#  Min Hour of     month   the     Command to run
#           month         week
    15   21   *      *     1     /home/yourname/Games/run_game Orion
    15   21   *      *     3     /home/yourname/Games/run_game Orion
    15   21   *      *     5     /home/yourname/Games/run_game Orion</pre>
				<p>To enable a cron file run:</p>
<pre>crontab &lt;your cron file&gt;</pre>
				<p>To see what cron files you have enabled run:</p>
<pre>crontab -l</pre>
				<p>An example file can be found at <tt>$HOME/GalaxyNG/games.crontab</tt></p>
				<p>To enable it run:</p>
<pre>(need info here)</pre>
				<p>See the <tt>crontab</tt> and <tt>cron</tt> manual for more information.</p>

			<hr />

			<h2 id="command">Command Summary</h2>
				<table>
					<tr>
						<th>Command</th>
						<th>Explanation</th>
					</tr>
					<tr>
						<td><tt>galaxyng -template &lt;game name&gt; &lt;number of players&gt;</tt></td>
						<td>Create a template specification file.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -create &lt;game specification file&gt;</tt></td>
						<td>Create a new game.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -mail0 &lt;game name&gt;</tt></td>
						<td>Create and email the turn 0 reports.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -dummymail0 &lt;game name&gt;</tt></td>
						<td>Create the turn 0 reports, but don't email them. You can find them in <tt>reports/&lt;game name&gt;</tt><td>
					</tr>
					<tr>
						<td><tt>run_game &lt;game name&gt;</tt></td>
						<td>Run a game turn.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -run &lt;game name&gt; &lt;file with orders&gt; [turn number]</tt></td>
						<td>Run a turn, and mail the turn reports.  Used in combination with run_game.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -dummyrun &lt;game name&gt; &lt;file with orders&gt; [turn number]</tt></td>
						<td>Run a turn but do not mail the turn reports. Store them in <tt>reports/</tt> instead.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -check &lt;message via stdin&gt;</td>
						<td>Check orders and mail a forecast, used in combination with procmail.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -dummycheck &lt;message via stdin&gt;</td>
						<td>Check orders, do not mail a forecast.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -report &lt;message via stdin&gt;</td>
						<td>Mail a copy of a turn report, used in combination with procmail.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -relay &lt;message via stdin&gt;</td>
						<td>Relay a message from one player to another player, used in combination with procmail.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -lastorders &lt;game name&gt; [turn number]</tt></td>
						<td>List for each player the last turn orders were sent in.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -players &lt;game name&gt; [turn number]</tt></td>
						<td>List password and address of each player.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -toall &lt;game name&gt;</tt></td>
						<td>Create a mail header to mail a message to all players.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -map &lt;game name&gt; [turn number]</tt></td>
						<td>Show a map of the galaxy.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -score &lt;game name&gt;</tt></td>
						<td>Create a high score list in HTML format.</td>
					</tr>
					<tr>
						<td><tt>galaxyng -hall &lt;game name&gt; [turn number]</tt></td>
						<td>Create a table with information for the Hall of Fame. At the end of a game, run this command and send the output to the <a href="http://www.refs-home.net/galaxyng/hof/">Hall of Fame maintainer</a>.</td>
					</tr>
				</table>

			<hr />
			
			<h2 id="ex">Example Files</h2>
				<ul>
					<li><a href="house_rules.txt">House Rules</a></li>
					<li><a href="global.bulletin">Global Bulletin</a> <tt>global.bulletin</tt></li>
					<li><a href="galaxyngrc">Server Configuration File</a> <tt>.galaxyngrc</tt></li>
					<li><a href="example.glx">Game Configuration File</a> <tt>&lt;game name&gt;.glx</tt></li>
 					<li><a href="intro.text">Game Introduction Text</a> <tt>&lt;game name&gt;.0<tt>.notice</tt></li>
 				</ul>

			<hr />

			<h2 id="host">Hosting Team Games</h2>
				<p>First get two teams...  best is to have the players themselves form the team and appoint a team captain for each team.  After that you will have two lists with email addreses. You add them in the .glx file and above the first list you add:</p>
<pre>team 0</pre>
				<p>and before the second list you add:</p>
<pre>team 1</pre>
				<p>At the top of the .glx file you add:</p>
<pre>teamgame</pre>
				<p>and then depending on the number of players there are:</p>
<pre>rows 10
colums 10</pre>
				<p>(in this case the game would have 100 players).  You then run the create command and the game is ready.  You can create a special report for each of the team captains with:</p>
<pre>./galaxyng -teaminfo  game  turn  team_number</pre>
				<p>All very simple :)  except...   depending on the number of players you will have to edit the creategame.c file. The galaxy that is created looks something like:</p>
<pre>t0   t1   t0  ...  t1   t0   t1 

t1   t0   t1  ...  t0   t1   t1 
      .            .
      .            .
      .            .
t0   t1   t0  ...  t1   t0   t1 

t1   t0   t1  ...  t0   t1   t1</pre>
				<p>Where t0 is the home planet of a team 0 player and t1 is the home planet of a team 1 player.  (That way each team player is surrounded by an equal amount of allies and enemies).</p>
				<p>The number of rows and colums is defined in the .glx file. However, rows x colums must be equal to the number of players that join. And in some case this gives odd results. For instance if  16 players join  the galaxy will be  4 by 4.  However if  14 player join the galaxy will be 2 x 7   which will look very odd. This can be solved by using a bigger number of row and colums and removing some of the planets  (I did that for Tiger3). For instance for the 14 player one, you can make it
4 by 4 and remove 2 planets:</p>
<pre>t1   t0   t1 

t1   t0   t1   t0 

t0   t1   t0   t1 

t1   t0   t1</pre>
				<p>You can find out how this is done in createCheckeredLayout()...  it is currently setup for a 7 by 7 grid and the removed of the corner players and 4 players in the middle...</p>

		<?php include 'footer.php'; ?>
 	</body>
</html>

