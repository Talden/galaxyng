m4_define(`DocStart', `<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN"><HTML>')m4_dnl
m4_define(`AHeader', `<HEAD><LINK rel=stylesheet href="BASE/main.css"><TITLE>$1</TITLE></HEAD>')m4_dnl
m4_define(`BodyStart', `<BODY BGCOLOR="#000000" link="#FFBBBB" vlink="#33FF33" TEXT="#FFFFFF">')m4_dnl
m4_define(`BodyEnd', `</BODY>')m4_dnl
m4_define(`DocEnd', `</HTML>')m4_dnl
m4_define(`BeginButtonRow', `<p><font color="red">[</font>')m4_dnl
m4_define(`AButton', `<A HREF="'linkLevel()`$2.html">$1</A>')m4_dnl
m4_define(`ButtonSep', `<font color="red">][</font>')m4_dnl
m4_define(`EndButtonRow', `<font color="red">]</font></p>')m4_dnl
m4_define(`ATitle', `<H1 ALIGN=CENTER>$1</H1>')m4_dnl
m4_define(`ASection', `<H2><A NAME="$1">$1</A></H2>')m4_dnl
m4_define(`ASubSection', `<H3><A NAME="$1">$1</A></H3>')m4_dnl
m4_define(`AGameGal', `<li>$1 ($2) <A HREF="http://www.galaxyng.com/ng/Score/$1/hitlist.html">hitlist</A> and <A HREF="http://www.galaxyng.com/ng/Score/$1/map.txt">map</A>')m4_dnl
m4_define(`AGamePBM', `<li>$1 ($2) <A HREF="http://galaxy.pbem.net/Score/$1/hitlist.html">hitlist</A> and <A HREF="http://galaxy.pbem.net/Score/$1/map.txt">map</A>')m4_dnl
m4_define(`ALink', `<A HREF="$1">$2</A>')
m4_define(`LevelUp', `../')m4_dnl
m4_define(`LevelTop')m4_dnl
m4_define(`linkLevel', LevelTop)m4_dnl
m4_define(`www_extButton', `<A HREF="$2">$1</A>')m4_dnl
m4_define(`www_sectionCounter',0)m4_dnl
m4_define(`www_subSectionCounter',0)m4_dnl
m4_define(`www_incrCounter',`m4_define(`$1',m4_incr($1))')m4_dnl
m4_define(`www_section', `www_incrCounter(`www_sectionCounter') <H2><font color="red">www_sectionCounter  </font><A NAME="$1">$2</A></H2> m4_define(`www_subSectionCounter', 0)')m4_dnl
m4_define(`www_subSection', `www_incrCounter(`www_subSectionCounter')<H3><font color="red">www_sectionCounter.www_subSectionCounter  </font><A NAME="$1">$2</A></H3>')m4_dnl
