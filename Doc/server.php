m4_include(`base.m4')m4_dnl
m4_include(`general.m4')m4_dnl
DocStart
AHeader(`GalaxyNG Server Manual')
BodyStart
m4_include(`snavigator.m4')m4_dnl
<!-- $Id$ -->


ATitle(`GalaxyNG Server Manual For release-5-0g')

<P>By Frans Slothouber (rfsber@xs4all.nl)</P>
<P>Last update March 2001</P>
				<ul>
					<li><a href="house_rules.txt">Example House Rules</a></li>
					<li><a href="globab.bulletin">Example Global Bulletin</a></li>
					<li><a href="galaxyngrc">Example Server Configuration File</a></li>
					<li><a href="example.glx">Example Game Configuration File</a></li>
 					<li><a href="intro.txt">Example Game Introduction Text</a></li>
 					<li><a href="hosting_a_team_game.txt">How to Host a Team Game</a></li>
 				</ul>

www_section(`toc', `Table of Contents')

m4_include(stoc.html)

www_section(`comp', `Compilation')

<P>Most of the configuration is done after compilation and is handled
by the install program.  Before compiling galaxyng you might want to
edit the <TT>makefile</TT> in the <TT>Source/</TT> directory
to make it fit your machine's configuration.  The following variables
can be configured:</P>
<PRE>
  CC     = gcc
  CFLAGS = -Wall -pedantic -g 
  LIBS   = -lm
</PRE>
<P> The above settings are valid for most Unix systems that have
<TT>GCC</TT> installed. It should compile without changes on a
Linux box. (Has been tested on a Debian, Slackware, SuSE, and Redhat
system).  Do not add any optimization options otherwise the code will
not function properly! The server only runs a couple of times per
week, so speed is not an issue.</P>

<P>To compile the code just type</P>
<PRE>
  make 
</PRE>
<P>in the top level directory <TT>GalaxyNG/</TT>, 
this creates the executable <TT>Source/galaxyng</TT>.
</P> 


www_section(`instl', `Installation')

<P>
After you compiled the code, do a
</P>
<PRE>
  make install
</PRE>
<P>to install galaxyng. It creates a directory called <TT>Games</TT>
in your home directory and installs a number of files in it.</P>


www_subSection(`instl2', `Installing in a Different Directory')

<P>If you want to have the game installed in a different directory you
have to edit the first line of the <TT>install.sh</TT> script.  You
also <STRONG>must</STRONG> set the environment variable
<TT>GALAXYNGHOME</TT> to this directory.  You can do this by adding
a line to your <TT>.bash_profile</TT> file (or the appropriate
file for your favourite shell).  For instance if you have
installed the game in /home/gng/mygames, add</P>
<PRE>
export GALAXYNGHOME=/home/gng/mygames
</PRE>


www_subSection(`filesc', `Files Created by the Install Process')

<P>The following files are created.</P>
<TABLE >
<TR>
  <TD><TT>galaxyng</TT></TD>
  <TD>The server program.  You use it to create
  new games, check orders, and run turns.</TD>
</TR>
<TR>
  <TD><TT>run_game</TT></TD>
  <TD>A shell script to run a game.  It is used
  in combination with cron, and allows you to automatically run
  turns at specified times.</TD>
</TR>
<TR>
  <TD><TT>procmailrc</TT></TD>
  <TD>An example procmailrc file. This
  contains the command to automatically process incoming orders 
  when ever a player send you an email with orders and
  a specific subject. To use it copy it to <TT>$HOME/.procmail</TT>.
  </TD>
</TR>
<TR>
  <TD><TT>.galaxyngrc</TT></TD>
  <TD>The configuration file for the the server.
  here you can specify the email address the GM reports are send to,
  as well what command should be used to send email.</TD>
</TR>
</TABLE>

<P>The installation script tries to figure out the location of all
programs needed to run the game, <TT>sendmail</TT> and
<TT>formail</TT>.  It also asks you for an email address. The GM
status reports go to this address.</P>

<P>The installation program also creates a number of directories:</P>

<TABLE >
<TR><TD><TT>orders/</TT></TD>
    <TD>This is where the players orders are stored. For
        each game there is a subdirectory. Orders are stored here under the
        name <VAR>&lt;nation_name&gt;.&lt;turn_number&gt;</VAR>.</TD>
</TR>
<TR><TD><TT>data/</TT></TD>
    <TD>This is where the game data is stored, there is
        a subdirectory for each game.</TD>
</TR>
<TR><TD><TT>reports/</TT></TD> 
    <TD>Contains, for each game a subdirectory where the
        turn reports are stored. It is only used for debug purposes.</TD>
</TR>
<TR><TD><TT>log/</TT></TD>
    <TD>Contains log files that contain information on
        processed orders, and game runs.</TD>
</TR>
<TR><TD><TT>statistics/</TT></TD>
    <TD>For experimental  purposes.</TD>
</TR><TR>
     <TD><TT>data</TT></TD>
     <TD>Contains, for each game a subdirectory where all the game 
         data is stored.</TD>
</TR>
<TR><TD><TT>notices/</TT></TD>
    <TD>This contains game notices. You can use these
        to provide additional information to the turn reports.</TD>
</TR>
</TABLE>

<P>There are three kind of notices available:</P>
<TABLE >
<TR><TD><TT>global.bulletin</TT></TD>
    <TD>In this you can store information that applies to 
        all your games. You can find an example in the <TT>Doc/</TT>
        directory.</TD>
</TR>
<TR><TD><VAR>&lt;game name&gt;</VAR><TT>.info</TT></TD> 
    <TD>In this you can store information that applies to a 
        particular game.</TD>
</TR>
<TR><TD><VAR>&lt;game name&gt;.&lt;turn number&gt;</VAR><TT>.notice</TT></TD>
    <TD>In this you can store information that applies to a 
        particular turn of a game.</TD>
</TR>
</TABLE>


www_section(`use', `Use')

<P>
Running a galaxy game consists of steps:
</P>
<OL>
<LI>create a new game,</LI>
<LI>mail the turn 0 report,</LI>
<LI>check and store the orders that the players sent in,</LI>
<LI>run a turn,</LI>
<LI>mail the turn reports.</LI>
</OL>

<P>
Then repeat steps 3, 4, and 5, until the players request the game to
stopped.
</P>


www_subSection(`create', `Creating a New Game')

<P>
To create a game use the command:
</P>

<PRE>
  ./galaxyng -create &lt;specification file&gt;  
</PRE>

<P>The specification file specifies the structure of the galaxy, that
is the number of home planets, empty planets, stuff planets, the name
of the galaxy and the size of the galaxy as well as the the email
address of each of the players.</P>  

<P>You can create a template <TT>.glx</TT> file by using the
<TT>-template</TT> command.</P>

<PRE>
  ./galaxyng -template &lt;game name&gt; &lt;number of players&gt;  
</PRE>

<P>This creates a <TT>.glx</TT> file with default values for all
parameters, plus documentation about what each parameter does.  You
will have to edit this file to insert the email addresses of the
players. For instance, say you got eight players to play in a galaxy
game, and want to call this game Orion. You can then create this game
as follows</P>

<PRE>
  ./galaxyng -template Orion 8  
</PRE>

<P>Edit the <TT>Orion.glx</TT> and change the dummy email addresses
to the real email addresses of the players, then run</P>

<PRE>
  ./galaxyng -create Orion.glx
</PRE>

<P>The server gives a detailed list of what it is doing and what
planets are created. When the game is created a map is printed.  A lot
of output is created so you might want to redirect the output of the
server to some file, say <TT>orionlayout.txt</TT>:</P>

<PRE>
  ./galaxyng -create Orion.glx  &gt; orionlayout.txt
</PRE>



www_subSection(`turn0', `Mailing the Turn 0 Reports')

<P>If you are happy with the galaxy you created, you can mail the turn 0
reports with:</P>

<PRE>
  ./galaxyng -mail0 <VAR>&lt;game name&gt;</VAR>
</PRE>

<P>Before you start any real games you might want to try to run a
couple of test games with yourself as player. This way you can see if
everything works OK.</P>

<P>So</P>
<PRE>
  ./galaxyng -mail0 Orion
</PRE>
<P>for your Orion game.</P>


www_subSection(`proc', `Processing Orders')

<P>
When you receive orders from a player, you can store and check them
with the following command:
</P>

<PRE>
  ./galaxyng -check &lt; &lt;file with orders&gt;
</PRE>

<P>The file with orders has to be a properly formatted email message,
with a To: field and a Subject: field with the word "orders" in it.</P>

<P>
The orders are stored in the directory <TT>orders/</TT><VAR>&lt;game
name&gt;</VAR> and the program sends a forecast to the player. A log
file is kept of all orders that are checked. It can be found at
<TT>$HOME/Games/log/orders_processed.txt</TT>.
</P>



www_subSection(`autck', `Auto Checking')

<P>Checking orders by hand is of course a very cumbersome process that
is best automated. You can automate with <TT>procmail</TT> and
<TT>formail</TT>. They are program that can reformat and process
incomming emails.</P>

<P>If you never used <TT>procmail</TT> before, read the man pages, and
then use the example procmailrc installed in
<TT>$HOME/Games/procmailrc</TT>. Also read the example procmailrc file
as it contains additional documentation.</P>

<P>Procmail can be difficult to get working.  On some systems
<TT>procmail</TT> works by just creating a <TT>.procmailrc</TT> file
in your home directory.  On other systems you have to create a
<TT>.forward</TT> file, that contains <TT>| /usr/bin/procmail</TT> to
get <TT>procmail</TT> to work.</P>

<P>Each entry in a <TT>.procmailrc</TT> defines recipe. It that tells
what has to be done to a message and under what condition.
The recipe for order messages looks as follows.</P>
<PRE>
  :0 rw :turno
  * ^Subject:.*Order
  |/usr/bin/formail -rkbt -s $HOME/Games/galaxyng -check
</PRE>

<P>Translated it means: if the subject of the message contains the word
"order", pipe the message to <TT>formail</TT>. The condition is case
insensitive, so Order, or ORDER also works. A lock file with the name
turno.lock is used to prevent the simultaneous execution of the same recipe if
two or more message that arrive at the same time.</P>

<P><TT>formail</TT> reformats the message. All mail header lines are
thrown away. A To: line is generated with the address of person that
send the message. A Subject: line is generated, with the original
subject prepended with Re:. This together with the body of the message
is fed to the galaxy server, running the check command.

<P>The server will analyse the orders in the body, and send a reply to
the person that send the message.</P>

<P>There are similar entries for the command to request a copy
of a turn report, and the command to relay an message to another
player. You will find them in the example <TT>procmailrc</TT> file.</P>

<P>If you want to keep a copy of the orders players sent-in, you
can use the following entry</P>

<TT>
<PRE>
# Someone sent-in orders, check them..
:0
* ^Subject:.*order
{
        :0 c
        $HOME/mail/orders

        :0 rw:order.lock
        |/usr/bin/formail -rkbt -s /home/gng/Games/galaxyng -check
}

</PRE>
</TT>

<P>
Do not use:
</P>
<TT>
<PRE>
# Someone sent-in orders, check them..
:0 rw :order.lock
* ^Subject:.*order
{
        :0 c
        $HOME/mail/orders

        :0
        |/usr/bin/formail -rkbt -s /home/gng/Games/galaxyng -check
}
</PRE>
</TT>
<P>In this case procmail ignores the lock file, and it can happen that
when two players send in orders shortly after eachother the orders of
the first player are overwritten</P>


www_subSection(`runturn', `Running a Turn')

<P>When it is time to run a turn you do this with:</P>

<PRE>
  ./run_game &lt;game name&gt;
</PRE>

<P>This shell script collects all orders in one file, runs the turn
based on these orders, and then sends out all the turn reports to the
players.  It also creates high-score lists in HTML and places it in you
<TT>$HOME/public_html</TT> directory, if you have one.  You can edit
the script and add other commands that need to be run for each
turn.</P>

<P>After each turn you are send a GM status report. It tells you
whether the turn ran successfully. It is especially handy if the
server runs on some remote computer. It also contains information on
the status of all nations in the game, a list of all bombings and a
map. That way you can follow the game.</P>


www_subSection(`rerunturn', `Rerunning a Turn')

<P>If for some reason there was a problem with a turn ran, you can
rerun, execute:</P>

<PRE>
  ./run_game &lt;game name&gt; &lt;turn&gt;
</PRE>

<P>The game will be rerun and new turn reports are send to the
players.  This only works for turns that already ran.</P>



www_subSection(`autorun', `Running Turns Automatically')

<P>
Although it is simple to run a turn it becomes cumbersome after a few
turns. Automization is again the solution. You can do this with
cron. For instance if you have a game called Orion, that runs on
Monday, Wednesday, and Friday around 21:15 hours, you can use the
following cron file:
</P>
<PRE>
#           day            day 
#  Min Hour of     month   the     Command to run
#           month         week
    15   21   *      *     1     /home/yourname/Games/run_game Orion
    15   21   *      *     3     /home/yourname/Games/run_game Orion
    15   21   *      *     5     /home/yourname/Games/run_game Orion
</PRE>

<P>To enable a cron file run</P>

<PRE>
   crontab &lt;your cron file&gt;
</PRE>

<P>To see what cron file you have enabled run</P>

<PRE>
   crontab -l
</PRE>

<P>An example file can be found at <TT>$HOME/GalaxyNG/games.crontab</TT>

<P>To enable it run.</P>

<P>See the <TT>crontab</TT> and <TT>cron</TT> manual for more information.</P>


www_section(`summ', `Command Summary')

<TABLE >
<TR><TH>Command</TH>
    <TH>Parameters</TH>
    <TH>Explanation</TH>
</TR>
<TR><TD><TT>template</TT></TD>
    <TD><TT>&lt;game name&gt; &lt;number of players&gt;</TT></TD>
    <TD>Create a template specification file.</TD>
</TR>
<TR><TD><TT>create</TT></TD>
    <TD><TT>&lt;game specification file&gt;</TT></TD>
    <TD>Create a new game.</TD>
</TR>
<TR><TD><TT>mail0</TT></TD>
    <TD><TT>&lt;game name&gt;</TT></TD>
    <TD>Create and email the turn 0 reports.<TD>
</TR>
<TR><TD><TT>dummymail0</TT></TD>
    <TD><TT>&lt;game name&gt;</TT></TD>
    <TD>Create the turn 0 reports, but don't email them.
        You can find them in <TT>reports/&lt;game name&gt;</TT><TD>
</TR>
<TR><TD><TT>run</TT></TD>
    <TD><TT>&lt;game name&gt; &lt;file with orders&gt; [turn number]</TT></TD>
    <TD>Run a turn, and mail the turn reports.</TD>
</TR>
<TR><TD><TT>dummyrun</TT></TD>
    <TD><TT>&lt;game name&gt; &lt;file with orders&gt; [turn number]</TT></TD>
    <TD>Run a turn but do not mail the turn reports.
        Store them in <TT>reports/</TT> instead.</TD>
</TR>
<TR><TD><TT>check</TT></TD>
    <TD>message via stdin</TD>
    <TD>Check orders and mail a forecast, used
        in combination with procmail.</TD>
<TR><TD><TT>dummycheck</TT></TD>
    <TD>message via stdin</TD>
    <TD>Check orders, do not mail a forecast.</TD>
</TR>
<TR><TD><TT>report</TT></TD>
    <TD>message via stdin</TD>
    <TD>Mail a copy of a turn report, used in
        combination with procmail.</TD>
</TR>
<TR><TD><TT>relay</TT></TD>
    <TD>message via stdin</TD>
    <TD>Relay a message from one player to another player,
        used in combination with procmail.</TD>
</TR>
<TR><TD><TT>lastorders</TT></TD>
    <TD><TT>&lt;game name&gt; [turn number]</TT></TD>
    <TD>List for each player the last turn orders were sent-in.</TD>
</TR>
<TR><TD><TT>players</TT></TD>
    <TD><TT>&lt;game name&gt; [turn number]</TT></TD>
    <TD>List password and address of each player.</TD>
</TR>
<TR><TD><TT>toall</TT></TD>
    <TD><TT>&lt;game name&gt;</TT></TD>
    <TD>Create a mail header to mail a message to all players.<TD>
</TR>
<TR><TD><TT>map</TT></TD>
    <TD><TT>&lt;game name&gt; [turn number]</TT></TD>
    <TD>Show a map of the galaxy.</TD>
</TR>
<TR><TD><TT>score</TT></TD>
    <TD><TT>&lt;game name&gt;</TT></TD>
    <TD>Create a high-score list in HTML format.</TD>
</TR>
<TR><TD><TT>hall</TT></TD>
    <TD><TT>&lt;game name&gt; [turn number]</TT></TD>
    <TD>Create a table with information for the Hall of Fame.
        At the end of a game, run this command and send the output
        to fslothouber@acm.org.</TD>
</TR>
</TABLE>


www_section(`config', `Configuration')

www_subSection(`serverconfig', `Server Configuration File')

<P>The server can be configured with a <TT>.galaxyngrc</TT> file.  
The server looks for this file in the directory <TT>$HOME/Games/</TT>.
It also looks for the file in <TT>$HOME/Games/data/&lt;game name&gt;/</TT>.
You can use this to override settings for a particular game.
An example
<TT>.galaxyngrc</TT> file is generated when you install the game.  A documented
<TT>.galaxyngrc</TT> file can be found in the <TT>Docs/</TT> directory. You can
use it to specify the following parameters.  Only the first two are essential
to run games.</P>

<TABLE >
<TR><TD><TT>GMemail</TT></TD>
    <TD>The address the GM status reports are send to.</TD>
</TR>
<TR><TD><TT>sendmail</TT></TD>
    <TD>The command that is used to send mail to the players.</TD>
</TR>
<TR><TD><TT>compress</TT></TD>
    <TD>The command to compress email with, 
        usually <TT>{ /usr/bin/zip }</TT>.</TD>
</TR>
<TR><TD><TT>encode</TT></TD>
    <TD>Path to the command to attach a file to an email with, 
        usually <TT>{ /usr/bin/mmencode }</TT>.</TD>
</TR>
<TR><TD><TT>FullBombing</TT></TD>
    <TD>Switch to turn on old style galaxy bombing rule.</TD>
</TR>
<TR><TD><TT>DontDropDead</TT></TD>
    <TD>Switch, idle players are not dropped from the game.</TD>
</TR>
<TR><TD><TT>SaveReportCopy</TT></TD>
    <TD>When running a turn also save a copy of each turn report
        in <TT>reports/&lt;game name&gt;/</TT>.</TD>
</TR>
</TABLE>



www_subSection(`envvar', `Environment Variables')

<P>You can override where the server looks for all its data files by
setting the <TT>GALAXYNGHOME</TT> variable. If it is not set the
server looks in <TT>$HOME/Games/</TT>.</P>


BodyEnd
DocEnd


