<!-- start menu.php -->

<?php
if (!function_exists("file_get_contents")) {
  function file_get_contents($filename, $use_include_path = 0) {
   $data = ""; // just to be safe. Dunno, if this is really needed
   $file = @fopen($filename, "rb", $use_include_path);
   if ($file) {
     while (!feof($file)) $data .= fread($file, 1024);
     fclose($file);
   }
   return $data;
  }
}

$base = file_get_contents('base_url.txt');
?>

<p class="menu"><?php
$self = trim($base) . "index.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;GalaxyNG&nbsp;Home&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>">GalaxyNG&nbsp;Home</a>&nbsp;]
<?php } ?>	

<?php
$self = trim($base) . "start.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Getting&nbsp;Started&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>start.php">Getting&nbsp;Started</a>&nbsp;]
<?php } ?>

<?php
$self = trim($base) . "manual.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Players'&nbsp;Manual&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>manual.php">Players'&nbsp;Manual</a>&nbsp;]
<?php } ?>

<?php
$self = trim($base) . "quickref.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Quick&nbsp;Reference&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>quickref.php">Quick&nbsp;Reference</a>&nbsp;]
<?php } ?>

[&nbsp;<a href="http://galaxyview.sourceforge.net/tools.html">Tools</a>&nbsp;]

<?php
$self = trim($base) . "turns.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Turn&nbsp;Reports&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>turns.php">Turn&nbsp;Reports</a>&nbsp;]
<?php } ?>

<?php
$self = trim($base) . "faq.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;FAQ&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>faq.php">FAQ</a>&nbsp;]
<?php } ?>

<?php
$self = trim($base) . "etiquette.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Etiquette&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>etiquette.php">Etiquette</a>&nbsp;]
<?php } ?>

[&nbsp;<a href="http://lists.sourceforge.net/lists/listinfo/galaxyng-players">Mailing&nbsp;List</a>&nbsp;]

<?php
$self = trim($base) . "hall.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Hall&nbsp;Of&nbsp;Fame&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>hall.php">Hall&nbsp;Of&nbsp;Fame</a>&nbsp;]
<?php } ?>

<?php
$self = trim($base) . "links.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Links&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>links.php">Links</a>&nbsp;]
<?php } ?>

<?php
$self = trim($base) . "server.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Server&nbsp;Manual&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>server.php">Server&nbsp;Manual</a>&nbsp;]
<?php } ?>

[&nbsp;<a href="http://sourceforge.net/projects/galaxyng/">Development</a>&nbsp;]

<?php
$self = trim($base) . "variants.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Galaxy&nbsp;Variants&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>variants.php">Galaxy&nbsp;Variants</a>&nbsp;]
<?php } ?>

<?php
$self = trim($base) . "whyng.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Why&nbsp;GalaxyNG&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>whyng.php">Why&nbsp;GalaxyNG</a>&nbsp;]
<?php } ?>

<?php
$self = trim($base) . "credits.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<span class="bold">[&nbsp;Credits&nbsp;]</span>
<?php } else { ?>
	[&nbsp;<a href="<?php include 'base_url.txt'; ?>credits.php">Credits</a>&nbsp;]
<?php } ?>

</p>

<table class="wide"><tr><td class="h1"><?php echo $title; ?></td><td class="right"><?php
$self = trim($base) . "index.php";
if ($_SERVER['PHP_SELF'] == $self) {
?>
	<img src="galaxyng.png" alt="GalaxyNG" />
<?php } else { ?>
	<a href="<?php include 'base_url.txt'; ?>"><img src="galaxyngsmall.png" alt="GalaxyNG" /></a>
<?php } ?>
</td></tr></table>

<hr class="menu" />

<!-- end menu.php -->
