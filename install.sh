#!/bin/bash

#
# $Id$
#

#
# If you like to install the server in a directory other than
# $HOME/Games, change the following line, and add the line
# export GALAXYNGHOME=<the dir you install it in> 
# to your .bash_profile file.
#

GALAXY_HOME=$HOME/Games

echo "*** GalaxyNG Install Script ***"
echo "This script creates and installs all files necessary to run Galaxy Games"
echo "Files will be installed in" $GALAXY_HOME
echo

if { test ! -d $GALAXY_HOME; } then {
  echo "Creating "$GALAXY_HOME;
  mkdir $GALAXY_HOME;
}
fi
for NAME in log orders notices data reports statistics forecasts ; do
  if { test ! -d $GALAXY_HOME/$NAME; } then { 
    mkdir $GALAXY_HOME/$NAME; 
  } 
  fi 
done

#===================================================
#     Determine Users email address.
#===================================================

echo "o What is your email address (GM reports are send to this address)?"
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
#   Try to find the location of the public WWW directory.
# ===========================================================

echo "o Trying to locate the WWW directory."
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
  echo "  I can't seem to find the your WWW directory,"
  echo "  Using "$GALAXY_HOME/WWW" for now."
  WWW=$GALAXY_HOME/WWW
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
  echo "  Found an existing version of " $RUN_GAME;
  RUN_GAME=$GALAXY_HOME/run_game.new;
  echo "  Writing the new version to "  $RUN_GAME;
}
fi

echo "#!/bin/bash" > $RUN_GAME
cat Util/run_game.header >> $RUN_GAME
echo "BASE="$GALAXY_HOME >> $RUN_GAME
echo "WWWHOME="$WWW >> $RUN_GAME
echo "GALAXYNGHOME="$GALAXY_HOME >> $RUN_GAME
cat Util/run_game.tail >> $RUN_GAME
chmod +x $RUN_GAME

# =========================================================
#              Create .procmail file
# =========================================================

PROCRC=$GALAXY_HOME/procmailrc
FORMAIL=`which formail`
echo "o Creating" $PROCRC
#echo "  You can use this file in combination with procmail"
#echo "  to automagically check incoming orders."
#echo "  To use it copy it to " $HOME " as "$HOME"/.procmailrc"
if { test -e $PROCRC; } then {
  echo "  Found an existing version of " $PROCRC;
  PROCRC=$GALAXY_HOME/procmailrc.new
  echo "  Writing the new version to "  $PROCRC;
}
fi

echo "PATH=\$HOME/bin:/usr/bin:/bin:/usr/local/bin:." > $PROCRC
echo "# Make sure that this exists!" >> $PROCRC
echo "MAILDIR=\$HOME/Mail" >> $PROCRC
echo "DEFAULT=\$MAILDIR/mbox" >> $PROCRC
echo "LOGFILE=\$MAILDIR/from" >> $PROCRC
echo "LOCKFILE=\$HOME/.lockmail" >> $PROCRC
echo "LOGABSTRACT=all" >> $PROCRC
echo "GALAXYNGHOME="$GALAXY_HOME >> $PROCRC
echo "" >> $PROCRC
echo "# Don't reply to anything from a mail daemon, but store it" >> $PROCRC
echo "# in a folder called postmaster." >> $PROCRC
echo ":0:" >> $PROCRC
echo "* ^FROM_MAILER" >> $PROCRC
echo "postmaster" >> $PROCRC
echo "" >> $PROCRC
echo "# The following prevents mail loops. These happen when the server" >> $PROCRC
echo "# starts replying to its own messages or messages from another server." >> $PROCRC
echo "# Mail loops usually annoy the heck out of sysadmins." >> $PROCRC
echo ":0:" >> $PROCRC
echo "* ^Subject:.*(orders checked|copy of turn|major trouble|orders received|message sent)" >> $PROCRC
echo "checkedorders" >> $PROCRC
echo "" >> $PROCRC
echo "# Someone sent-in orders, check them.." >> $PROCRC
echo ":0 rw :turno" >> $PROCRC
echo "* ^Subject:.*order" >> $PROCRC
echo "|"$FORMAIL" -rkbt -s "$GALAXY_HOME"/galaxyng -check" >> $PROCRC
echo "" >> $PROCRC
echo "# Someone requested a copy of a turn report, send a copy..." >> $PROCRC
echo "# However don't reply to the GM report nor to turn reports." >> $PROCRC
echo ":0 rw :turno" >> $PROCRC
echo "* ^Subject:.*report" >> $PROCRC
echo "* !^Subject:.*GM Report" >> $PROCRC
echo "* !^Subject:.*report for" >> $PROCRC
echo "|"$FORMAIL" -rkbt -s "$GALAXY_HOME"/galaxyng -report" >> $PROCRC
echo "" >> $PROCRC
echo "# A player wants to relay a message to another player." >> $PROCRC
echo ":0 rw :turno" >> $PROCRC
echo "* ^Subject:.*relay" >> $PROCRC
echo "|"$FORMAIL" -rkbt -s "$GALAXY_HOME"/galaxyng -relay" >> $PROCRC
echo "" >> $PROCRC
echo "# Anything else, or messages that causes the engine to fail" >> $PROCRC
echo "# are stored in Mail/mbox." >> $PROCRC

# =========================================================
#              Create crontab file
# =========================================================

CRONT=$GALAXY_HOME/games.crontab
echo "o Creating" $CRONT
if { test -e $CRONT; } then {
  echo "  Found an existing version of " $CRONT;
  CRONT=$GALAXY_HOME/games.crontab.new;
  echo "  Writing the new version to "  $CRONT;
}
fi
echo "# This is an example crontab file. It would run the game " > $CRONT
echo "# Orion on Monday, Wednesday, and Friday at 21:15 (9:15pm)" >> $CRONT
echo "# To use it, type" >> $CRONT
echo "#   crontab games.crontab" >> $CRONT 
echo "#" >> $CRONT
echo "15 21 * * 1 " $RUN_GAME "Orion" >> $CRONT
echo "15 21 * * 3 " $RUN_GAME "Orion" >> $CRONT
echo "15 21 * * 5 " $RUN_GAME "Orion" >> $CRONT

# =========================================================
#              Create a .galaxyngrc file
# =========================================================

RCFILE=$GALAXY_HOME/.galaxyngrc
COMPRESS=`which zip`
ENCODE=`which mmencode`
MUTT=`which mutt`
echo "o Creating" $RCFILE
if { test -e $RCFILE; } then {
  echo "  Found an existing version of " $RCFILE;
  RCFILE=$GALAXY_HOME/.galaxyngrc.new;
  echo "  Writing the new version to "  $RCFILE;
}
fi
echo "sendmail {"$SENDMAIL" -t }" > $RCFILE
echo "GMemail "$EMAIL >> $RCFILE
# if { test -n $MUTT ; } then {
#   echo "mutt "$MUTT >> $RCFILE
# }
# fi
if { test -n $ENCODE ; } then {
  echo "encode {"$ENCODE " }" >> $RCFILE
}
fi
if { test -n $COMPRESS ; } then {
  echo "compress {" $COMPRESS " }" >> $RCFILE
}
fi

# =========================================================
#              Copy GalaxyNG code
# =========================================================

echo "o Copying the GalaxyNG server"
NG=$GALAXY_HOME/galaxyng
if { test -e $NG; } then {
  echo "  Found an existing version of " $NG;
  NG=$GALAXY_HOME/galaxyng.new;
  echo "  Writing the new version to "  $NG;
  echo "  _Test_ this new version and if it works according to your needs"
  echo "  copy it to "i $NG;
}
fi
cp Source/galaxyng $NG
strip $NG
cp Source/cranberr.ttf $GALAXY_HOME
echo "Installation completed."

