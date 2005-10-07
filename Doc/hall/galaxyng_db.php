<?php
// connect to the database
$link = mysql_connect("mysql4-g.sourceforge.net", "g48224rw", "of") or die("Could not connect " . mysql_error());
// make galaxyng the current db
mysql_select_db("g48224_galaxyng", $link) or die("Can\'t use g48224_galaxyng  " . mysql_error());
?>