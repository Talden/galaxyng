m4_include(`base.m4')m4_dnl
m4_include(`general.m4')m4_dnl
DocStart
AHeader(`GalaxyNG Quick Reference Manual')
BodyStart
m4_include(`mannavigator.m4')m4_dnl
<!-- $Id$ -->

ATitle(`GalaxyNG Quick Reference Manual')

ASection(`GalaxyNG release-4-1 (Dec 1999)')

<TABLE>
<TR><TD COLSPAN=3 ALIGN=CENTER><FONT COLOR="red"><STRONG>General Orders</STRONG></FONT></TD>
<TR><TD>@ [nation ...]</TD>
    <TD>Send a message to one or more nations.</TD>
<TR><TD>= &lt;Your real name&gt;</TD>
    <TD>Set your real name for inclusion in the Hall of Fame.</TD>
<TR><TD>A &lt;nation&gt;</TD>
    <TD>Declare peace to another nation.</TD>
<TR><TD>B &lt;group&gt; &lt;number of ships&gt;</TD>
    <TD>Break off a number of ships from a group to form a new group.</TD>
<TR><TD>C &lt;new name&gt;</TD>
    <TD>Rename your nation.</TD>
<TR><TD>D &lt;type name&gt; &lt;drive&gt; &lt;attacks&gt; &lt;weapons&gt; &lt;shields&gt; &lt;cargo&gt;</TD>
    <TD>Design a new ship type.</TD>
<TR><TD>E &lt;type name&gt;</TD>
    <TD>Erease a ship type.</TD>
<TR><TD>F &lt;nation&gt;</TD>
    <TD>Find the email address of another nation.</TD>
<TR><TD>G &lt;group&gt; [number of ships]</TD>
    <TD>Upgrade the tech levels of a group.</TD>
<TR><TD>H &lt;group&gt;</TD>
    <TD>Reverse course of a group.</TD>
<TR><TD>I &lt;group&gt; &lt;planet&gt; [number of ships]</TD>
    <TD>Send a group on an intercept mission.</TD>
<TR><TD>L &lt;group&gt; &lt;cargo type&gt; [number-of-ships] [AMOUNT &lt;amount&gt;]</TD>
    <TD>Load a group with cargo.</TD>
<TR><TD>M &lt;x&gt; &lt;y&gt; &lt;size&gt;</TD>
    <TD>Change the map size of your report.</TD>
<TR><TD>N &lt;old planet name&gt; &lt;new planet name&gt;</TD>
    <TD>Rename a planet.</TD>
<TR><TD>O &lt;option&gt;</TD>
    <TD>Set a game option.</TD>
<TR><TD>P &lt;planet&gt; &lt;product&gt;</TD>
    <TD>Set the production type for a planet.</TD>
<TR><TD>Q &lt;your nation name&gt;</TD>
    <TD>Quit the game.</TD>
<TR><TD>R &lt;origin planet&gt; &lt;cargo type&gt; [destination planet]</TD>
    <TD>Set a cargo route between two planets.</TD>
<TR><TD>S &lt;group&gt; &lt;planet&gt; [number of ships]</TD>
    <TD>Send a groups or a number of ships from a group to a planet.</TD>
<TR><TD>T &lt;type name&gt; &lt;new name&gt;</TD>
    <TD>Rename a ship type.</TD>
<TR><TD>U &lt;group&gt; [number-of-ships] [AMOUNT &lt;amount&gt;]</TD>
    <TD>Unload cargo from a group.</TD>
<TR><TD>V &lt;planet&gt;</TD>
    <TD>Claim ownership over a planet.</TD>
<TR><TD>W &lt;nation&gt;</TD>
    <TD>Declare war on a nation.</TD>
<TR><TD>X &lt;group&gt; [number-of-ships]</TD>
    <TD>Scrap a group of ships.</TD>
<TR><TD>Y &lt;passwd&gt;</TD>
    <TD>Change your password.</TD>
<TR><TD>Z &lt;new address&gt;</TD>
    <TD>Change the email address turn reports are sent to.</TD>
<TR><TD COLSPAN=3 ALIGN=CENTER><FONT COLOR="red"><STRONG>Fleet Orders</STRONG></FONT></TD>
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
