
<!-- begin footer.php -->
<!-- $Id$ -->
<hr />

<p><?php
$self = trim($base) . "index.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>GalaxyNG 6.6<?php } else { ?><a href="<?php include 'base_url.txt'; ?>">GalaxyNG 6.6</a><?php } ?>	| <?php
$self = trim($base) . "credits.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>Credits and License<?php } else { ?><a href="<?php include 'base_url.txt'; ?>credits.php">Credits and License</a><?php } ?></p>
<p><?php echo $title; ?>
<br /><?php echo "Last modified " . date( "F d, Y", getlastmod() ); ?>
<br /><?php
$self = trim($base) . "index.php";
if ($_SERVER['PHP_SELF'] == $self) {
	echo "http://galaxyng.sourceforge.net/";
} else {
	echo "http://galaxyng.sourceforge.net/$_SERVER[PHP_SELF]";
} ?></p>
<p><a href="http://sourceforge.net/"><img src="http://sourceforge.net/sflogo.php?group_id=48224&amp;type=6" width="210" height="62" alt="SourceForge.net Logo" /></a></p>
<!-- end footer.php -->
