program hfix_ersatz;

{ Restauriert die HERCULES-Grafikanzeige bei einem
  Systemabsturz. Dieses Programm funktioniert 
  n u r   vom DOS-Betriebssystem aus, d.h. es muss
  als COM-File vorliegen.

  Nach Aufruf des Programms schaltet sich die Grafik-
  Karte wieder in den Textmodus.
  (Ersatz fuer das HERCULES-Programm HFIX.COM)
}

{$I TYPEDEF.SYS}
{$I GRAPHIX.SYS}
{$I KERNEL.SYS}

begin { main }
  InitGraphic;
  Leavegraphic;
  writeln('HERCULES Grafik- & Textseite restauriert.');
end { main }.
