#!/bin/bash

#
# $Id$
#

#
# If you want to install the server in a directory other than
# $HOME/Games, change the following line, and add the line
#   export GALAXYNGHOME=<the dir you install it in> 
# to your .bash_profile file.
#

GALAXY_HOME=$HOME/Games

echo "*** GalaxyNG Install Script ***"
echo "This script creates and installs all files necessary to run Galaxy Games"
echo "Files will be installed in" $GALAXY_HOME
echo

#===================================================
#     Create directories, if necessary.
#===================================================

if { test ! -d $GALAXY_HOME; } then {
  echo "Creating "$GALAXY_HOME;
  mkdir -p $GALAXY_HOME;
}
fi
for NAME in log orders notices data reports statistics forecasts ; do
  if { test ! -d $GALAXY_HOME/$NAME; } then { 
    mkdir $GALAXY_HOME/$NAME; 
  } 
  fi 
done

#===================================================
#     Determine GM email address.
#===================================================

echo "o What is your email address (GM reports are sent to this address)?"
read EMAIL

#====================================================
#    Try to find the sendmail command.
#====================================================

SENDMAIL=none
echo "o Trying to locate the sendmail command..." 
# Check the usual locations,  "which" does not work usually.
for NAME in /usr/bin /usr/sbin /sbin /bin ; do
#  echo "  Checking: " $NAME
  if { test -x $NAME/sendmail ; } then {  
    SENDMAIL=$NAME/sendmail ;
  } 
  fi 
done
# If it was not found, ask the user...
if { test $SENDMAIL = none; } then {
  echo "  I can't seem to find the sendmail command." ;
  echo "  Please enter the full path for sendmail:" ;
  read SENDMAIL
}
fi
echo "  The full path for sendmail is" $SENDMAIL

# ===========================================================
#   Try to find the location of the public web directory.
# ===========================================================

echo "o Trying to locate the web directory."
echo "  GalaxyNG uses this directory to store the high score lists."

WWW=none
for NAME in $HOME/public_html $HOME/WWW $HOME/www ; do
#  echo "  Checking: " $NAME
  if { test -d $NAME; } then { 
    WWW=$NAME; 
  } 
  fi 
done

if { test $WWW = none; } then {
  echo "  I can't seem to find the your web directory,"
  echo "  Using "$GALAXY_HOME/public_html" for now."
  WWW=$GALAXY_HOME/public_html
  if { test ! -d $WWW; } then { 
    mkdir $WWW; 
  } fi
} else {
  echo "  Using: " $WWW
}
fi


# =========================================================
#   Check for a /tmp directory
# =========================================================

echo "o Trying to locate a tmp directory."
if { test -d /tmp; } then { 
  TEMP=/tmp; 
} else { 
  TEMP=$GALAXY_HOME;
}
fi
echo "  Using: " $TEMP

# ========================================================
#                Create run_game
# ========================================================

RUN_GAME=$GALAXY_HOME/run_game
echo "o Creating" $RUN_GAME
#echo "  This command is used to run a turn."
if { test -e $RUN_GAME; } then {
  echo "  Found an existing version of " $RUN_GAME
  RUN_GAME=$GALAXY_HOME/run_game.new
  echo "  Writing the new version to "  $RUN_GAME
}
fi

echo "#!/bin/bash" > $RUN_GAME
cat Util/run_game.header >> $RUN_GAME
echo "BASE="$GALAXY_HOME >> $RUN_GAME
echo "WWWHOME="$WWW >> $RUN_GAME
echo "GALAXYNGHOME="$GALAXY_HOME >> $RUN_GAME
echo "declare -x GDFONTPATH="$GALAXY_HOME"/Games" >> $RUN_GAME
cat Util/run_game.tail >> $RUN_GAME
chmod +x $RUN_GAME

# =========================================================
#  Try to find the formail command
# =========================================================

PROCRC=$GALAXY_HOME/procmailrc

FORMAIL=none
echo "o Trying to locate the formail command..." 
# Check the usual locations
for NAME in /usr/bin /usr/sbin /sbin /bin ; do
#  echo "  Checking: " $NAME
  if { test -x $NAME/formail ; } then {  
    FORMAIL=$NAME/formail ;
  } 
  fi 
done
# If it was not found, try which...
if { test $FORMAIL = none; } then {
	FORMAIL=`which formail`
}
fi
# If it was not found, ask the user...
if { test $FORMAIL = none; } then {
  echo "  I can't seem to find the formail command."
  echo "  This may mean you don't have procmail installed."
  echo "  Please enter the full path for formail:"
  read FORMAIL
}
fi
echo "  The full path for formail is" $FORMAIL

# =========================================================
#              Create .procmailrc file
# =========================================================

echo "o Creating" $PROCRC
echo "  You can use this file in combination with procmail"
echo "  to automatically check incoming orders."
echo "  To use it copy it to "$HOME" as "$HOME"/.procmailrc"
echo "  Note that is "$HOME"/-dot-procmailrc"
if { test -e $PROCRC; } then {
  echo "  Found an existing version of " $PROCRC
  PROCRC=$GALAXY_HOME/procmailrc.new
  echo "  Writing the new version to "  $PROCRC
}
fi

echo "PATH=\$HOME/bin:/usr/bin:/bin:/usr/local/bin:." > $PROCRC
echo "#" >> $PROCRC
echo "# Make sure that your mail directory exists!" >> $PROCRC
echo "MAILDIR=\$HOME/Mail" >> $PROCRC
echo "" >> $PROCRC
echo "DEFAULT=\$MAILDIR/mbox" >> $PROCRC
echo "# For maildir delivery, mailboxes end in a /, so comment out the above" >> $PROCRC
echo "# line and use this instead:" >> $PROCRC
echo "# DEFAULT=\$MAILDIR/" >> $PROCRC
echo "" >> $PROCRC
echo "LOGFILE=\$MAILDIR/galaxyng.log" >> $PROCRC
echo "LOCKFILE=\$HOME/.lockmail" >> $PROCRC
echo "LOGABSTRACT=all" >> $PROCRC
echo "GALAXYNGHOME="$GALAXY_HOME >> $PROCRC
echo "" >> $PROCRC
echo "# Store GM reports in a folder called gmreport." >> $PROCRC
echo ":0:" >> $PROCRC
echo "* ^Subject:.*GM Report" >> $PROCRC
echo "gmreport" >> $PROCRC
echo "# Some IMAP servers prefix mailbox names with a '.'  For example:" >> $PROCRC
echo "# .gmreport" >> $PROCRC
echo "# Combining this with maildir delivery would yield:" >> $PROCRC
echo "# .gmreport/" >> $PROCRC
echo "" >> $PROCRC
echo "# Don't reply to anything from a mail daemon, but store it" >> $PROCRC
echo "# in a folder called postmaster." >> $PROCRC
echo ":0:" >> $PROCRC
echo "* ^FROM_MAILER" >> $PROCRC
echo "postmaster" >> $PROCRC
echo "# .postmaster" >> $PROCRC
echo "# .postmaster/" >> $PROCRC
echo "" >> $PROCRC
echo "# The following prevents mail loops. These happen when the server" >> $PROCRC
echo "# starts replying to its own messages or messages from another server." >> $PROCRC
echo "# Mail loops usually annoy the heck out of sysadmins." >> $PROCRC
echo ":0:" >> $PROCRC
echo "* ^Subject:.*(orders checked|copy of turn|major trouble|orders received|message sent|report for)" >> $PROCRC
echo "loops" >> $PROCRC
echo "# .loops" >> $PROCRC
echo "# .loops/" >> $PROCRC
echo "" >> $PROCRC
echo "# Received a message with the word order in the subject:" >> $PROCRC
echo ":0" >> $PROCRC
echo "* ^Subject:.*order" >> $PROCRC
echo "{" >> $PROCRC
echo "  :0crw:order" >> $PROCRC
echo "  # Check the orders and send a forecast or an error message:" >> $PROCRC
echo "  |"$FORMAIL" -rkbt -s "$GALAXY_HOME"/galaxyng -check" >> $PROCRC
echo "  :0:orders" >> $PROCRC
echo "  # Save a copy of the orders message" >> $PROCRC
echo "  orders" >> $PROCRC
echo "  # .orders" >> $PROCRC
echo "  # .orders/" >> $PROCRC
echo "}" >> $PROCRC
echo "" >> $PROCRC
echo "# Received a message with the word report in the subject:" >> $PROCRC
echo ":0" >> $PROCRC
echo "* ^Subject:.*report" >> $PROCRC
echo "{" >> $PROCRC
echo "  # Send a turn report or an error message: " >> $PROCRC
echo "  :0crw:report" >> $PROCRC
echo "  |"$FORMAIL" -rkbt -s "$GALAXY_HOME"/galaxyng -report" >> $PROCRC
echo "  :0:reports" >> $PROCRC
echo "  # Save a copy of the report request" >> $PROCRC
echo "  reports" >> $PROCRC
echo "  # .reports" >> $PROCRC
echo "  # .reports/" >> $PROCRC
echo "}" >> $PROCRC
echo "" >> $PROCRC
echo "# Someone wants to relay a message to another player." >> $PROCRC
echo ":0" >> $PROCRC
echo "* ^Subject:.*relay" >> $PROCRC
echo "{" >> $PROCRC
echo "  :0crw:relay" >> $PROCRC
echo "  # Relay the message and send a confirmation or error report to the player" >> $PROCRC
echo "  |"$FORMAIL" -rkbt -s "$GALAXY_HOME"/galaxyng -relay" >> $PROCRC
echo "  :0:relays" >> $PROCRC
echo "  # Save a copy of the relay request" >> $PROCRC
echo "  relays" >> $PROCRC
echo "  # .relays" >> $PROCRC
echo "  # .relays/" >> $PROCRC
echo "}" >> $PROCRC
echo "" >> $PROCRC
echo "# Someone wants to sign up for a game" >> $PROCRC
echo "# Don't forget to change the gamename and number of players" >> $PROCRC
echo ":0" >> $PROCRC
echo "* ^Subject.*Join Jangi" >> $PROCRC
echo "{" >> $PROCRC
echo "  :0c:Jangi" >> $PROCRC
echo "  |/usr/bin/formail -rbt -s "$GALAXY_HOME"/are Jangi 25 0 0 0 | /usr/sbin/sendmail -t" >> $PROCRC
echo "  :0:JangiJoin" >> $PROCRC
echo "  # Save a copy of the registration request" >> $PROCRC
echo "  Jangi" >> $PROCRC
echo "  # .Jangi" >> $PROCRC
echo "  # .Jangi/" >> $PROCRC
echo "}" >> $PROCRC
echo "" >> $PROCRC
echo "# Someone wants to sign up for a game with custom planet sizes" >> $PROCRC
echo "# Up to ten players, max 2500 production, max planet size 1000, max planets 5" >> $PROCRC
echo "# Don't forget to change the gamename, planet sizes, and number of players." >> $PROCRC
echo ":0" >> $PROCRC
echo "* ^Subject.*Join Welland" >> $PROCRC
echo "{" >> $PROCRC
echo "  :0c:Welland" >> $PROCRC
echo "  |/usr/bin/formail -rbt -s "$GALAXY_HOME"/are Welland 10 2500 1000 5 | /usr/sbin/sendmail -t" >> $PROCRC
echo "  :0:WellandJoin" >> $PROCRC
echo "  # Save a copy of the registration request" >> $PROCRC
echo "  Welland" >> $PROCRC
echo "  # .Welland" >> $PROCRC
echo "  # .Welland/" >> $PROCRC
echo "}" >> $PROCRC
echo "" >> $PROCRC
echo "# Anything else, or messages that causes the engine to fail" >> $PROCRC
echo "# are stored in the default mailbox which was set at the top of this file." >> $PROCRC

# =========================================================
#              Create crontab file
# =========================================================

CRONT=$GALAXY_HOME/games.crontab
echo "o Creating" $CRONT
echo "  Edit it and run crontab"
echo "    games.crontab"
if { test -e $CRONT; } then {
  echo "  Found an existing version of " $CRONT;
  CRONT=$GALAXY_HOME/games.crontab.new;
  echo "  Writing the new version to "  $CRONT;
}
fi
echo "# This is an example crontab file. It would run the game " > $CRONT
echo "# Jangi on Monday, Wednesday, and Friday at 21:15 (9:15pm)" >> $CRONT
echo "# and the game Welland on Tuesday and Friday at 08:00 (8:00am)" > $CRONT
echo "# To use it, type" >> $CRONT
echo "#   crontab games.crontab" >> $CRONT 
echo "#" >> $CRONT
echo "15 21 * * 1,3,5 " $RUN_GAME "Jangi" >> $CRONT
echo "0 8 * * 2,5 " $RUN_GAME "Welland" >> $CRONT

# =========================================================
#              Create a .galaxyngrc file
# =========================================================

echo "o Creating" $RCFILE
echo "  This file contains basic configuration information for the server."
echo "  You can edit it by hand.  It will be created at " $GALAXY_HOME "/.galaxyngrc"
echo "  Note that is " $GALAXY_HOME "/-dot-galaxyngrc"
RCFILE=$GALAXY_HOME/.galaxyngrc
COMPRESS=`which zip`
ENCODE=`which mmencode`
if { test -z $ENCODE ; } then {
  ENCODE=`which mimencode`
}
fi
if { test -z $ENCODE ; } then {
  ENCODE=`which uuencode`
}
fi
if { test -e $RCFILE; } then {
  echo "  Found an existing version of " $RCFILE
  RCFILE=$GALAXY_HOME/.galaxyngrc.new
  echo "  Writing the new version to "  $RCFILE
}
fi
echo "; This file is documented in Doc/galaxyngrc" > $RCFILE
echo "; and http://galaxyng.sourceforge.net/server.php" >> $RCFILE
echo "sendmail { "$SENDMAIL" -t }" >> $RCFILE
echo "GMemail "$EMAIL >> $RCFILE
if { test -n $ENCODE ; } then {
  echo "encode { "$ENCODE " }" >> $RCFILE
}
fi
if { test -n $COMPRESS ; } then {
  echo "compress { " $COMPRESS " }" >> $RCFILE
}
fi
echo "fontpath { " $GALAXY_HOME " }" >> $RCFILE


# =========================================================
#              Copy GalaxyNG code
# =========================================================

echo "o Copying the GalaxyNG server"
NG=$GALAXY_HOME/galaxyng
if { test -e $NG; } then {
  echo "  Found an existing version of " $NG
  NG=$GALAXY_HOME/galaxyng.new
  echo "  Writing the new version to "  $NG
  echo "  _Test_ this new version and if it works according to your needs"
  echo "  copy it to " $GALAXY_HOME "/galaxyng"
}
fi
cp Source/galaxyng $NG
strip $NG

# =========================================================
#              Copy ARE code
# =========================================================

echo "o Copying the Automatic Registration Engine (ARE)"
ARE=$GALAXY_HOME/are
if { test -e $ARE; } then {
  echo "  Found an existing version of " $ARE
  ARE=$GALAXY_HOME/are.new
  echo "  Writing the new version to "  $ARE
  echo "  _Test_ this new version and if it works according to your needs"
  echo "  copy it to " $GALAXY_HOME "/are"
}
fi
cp ARE/are $ARE
strip $ARE

# =========================================================
#              Fonts for influence mapping
# =========================================================

if [ -f Source/cranberr.ttf ]; then
	cp Source/cranberr.ttf $GALAXY_HOME
fi

if [ -f Source/angostur.ttf ]; then
	cp Source/angostur.ttf $GALAXY_HOME
	cp Source/angostur.ttf $GALAXY_HOME/influence.ttf
fi

# =========================================================
#              Finished
# =========================================================

echo "Installation completed."

