m4_include(`wwwbase.m4')m4_dnl
m4_include(`general.m4')m4_dnl
DocStart
AHeader(`Hosting a Galaxy Game')
BodyStart
m4_include(`navigator.m4')m4_dnl
ATitle(`Hosting a Galaxy Game')

www_section(`sys', `System Requirements')

<P>
The two basic items to host a game are a Linux box and an internet
connection.  All tools necessary to compile the server and
automatically run a game are present in the current slackware
distribution of Linux.  And GalaxyNG should compile and run right out
of the box on a Linux box.
</P>

<P>
To see if you can use it on another system, here's a checklist
of the softare needed:
</P>
<UL>
  <LI>C (gcc) compiler; to compile the server</LI>
  <LI>crontab; to automatically run turns at a given time</LI>
  <LI>procmail; to automatically process in comming orders</LI> 
</UL>


<P>
The system is command line based, so you don't need X-windows.  The
program requires little memory. It even runs on a 2 Mbyte Amiga.  As
for harddisk requirements; depending on the size of the game, you need
about 2 to 5 MByte of disk space.  It isn't so much that the programs
are large but that the data files can become quite large.  For
instance, in the end phase of the game, turn reports can be
100Kbyte. So if there are 30 players left at that time this would
amount to 3Mbyte of disk space just to store the reports before they
are send.  A game called Hotzone, a 13 player game, that I was
running, needed about 2 Mbyte of disk space at turn 52. In these times
of Gbyte harddisks this should not be a problem though :)
</P>


www_section(`time', `Time Requirements')

<P>
It isn't that difficult to start up your own game.  It takes a
while to configure a game and the machine, but once it runs it needs
pratically no time at all. The whole process is automated, except for
a possible bug fix or answering questions. Before you run a game you
should make sure you have enough time, and a connection to the
internet for at least one year, since games can run that long.  If you
start a game, please continue it to the end, as it is very frustrating
for players if a game just ends somewhere in the middle without
comming to a conclusion.
</P>


www_section(`int', `Interested?')

<P>
Have a look at the server ALink(`NonM4/server.html', `manual')
or download the server code from the ALink(`download.html', `Download Area').
</P>

BodyEnd
DocEnd






