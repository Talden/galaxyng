m4_include(`wwwbase.m4')m4_dnl
m4_include(`general.m4')m4_dnl
DocStart
AHeader(`Download')
BodyStart
m4_include(`navigator.m4')m4_dnl
ATitle(`Download')

www_section(`docu', `Documentation')

<P>Some additional documentation:</P>
<UL>
  <LI>ALink(`NonM4/gettiquite.html', `Getiquette'), Chris Orr's
      list of things to do and not to do in Galaxy.</LI>
  <LI>ALink(`Download/methods.ps', `method.ps'), an article 
      that outlines some methods to analyze the economic situation 
      in Galaxy.</LI>
  <LI>ALink(`NonM4/FAQ.html', `FAQ.html'), galaxy FAQ.</LI>
  <LI>ALink(`NonM4/ManGalaxyNG.html', `ManGalaxyNG.html'), 
      game documentation.</LI>
  <LI>ALink(`NonM4/RefManual.html', `RefManual.html'), 
      a quick reference manual that lists all orders.
  <LI>ALink(`Download/manual.txt', `manual.txt'), Text File, 
      game manual in ASCII format.</LI>
  <LI>ALink(`NonM4/server.html', `server.html'), server 
      documentation (also included in the server archive).</LI>
</UL>


www_section(`sercode', `Server Source')

<P>Download one of these files if you want to host a galaxy game.
(Or if you just want to look at the code:)</P>


www_subSection(`stable', `Stable Version')

m4_define(`www_size', `m4_esyscmd(./getsize.sh $1)')

<P>GalaxyNG Release 5-0g, March 2001,
(ALink(`Download/history.txt', `history.txt')):</P>
<UL>
  <LI>ALink(`ftp://ftp.galaxyng.com/pub/galaxyng.tar.gz', `galaxyng.tar.gz'), 
      www_size(`/home/ftp/galaxy/galaxyng.tar.gz')  bytes, gzipped tar file</li>
  <LI>ALink(`ftp://ftp.galaxyng.com/pub/galaxyng.zip', `galaxyng.zip') 
      www_size(`/home/ftp/galaxy/galaxyng.zip') bytes, zip file</li>
</UL>

www_subSection(`beta', `Development Version')

<P>GalaxyNG Release 5-1, March 2002,
(ALink(`Download/history.txt', `history.txt')):</P>
<UL>
    <LI>ALink(`ftp://ftp.galaxyng.com/pub/galaxyngbeta.tar.gz', 
              `galaxyngbeta.tar.gz (ftp)') 
      www_size(`/home/ftp/galaxy/galaxyng.tar.gz') bytes, 
              gzipped tar file</li>
</UL>


BodyEnd
DocEnd
