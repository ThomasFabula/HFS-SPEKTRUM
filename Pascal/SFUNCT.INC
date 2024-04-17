{  SFUNCT.INC

    (C) 1986  Institut fuer Angewandte Physik
              Universitaet Bonn

}


{----------------------------------------------------------------------}
{--------------  Speichert das berechnete Spektrum ab  ----------------}
{----------------------------------------------------------------------}
procedure spektrum_speichern;
var  speichern : char;
begin
  writeln;
  write('Spektrum auf Diskette/Platte speichern (J/N) ? ');
  readln(speichern);
  speichern:=upcase(speichern);
  if speichern='J' then
  begin
    writeln;
    write('Dateinamen eingeben (max. 8 Zeichen, ');
    write('.SPK wird automatisch gesetzt) : ');
    readln(spekname);
    spekname:=spekname+'.SPK';
    SaveScreen(spekname);
  end;
  writeln;
end;


{----------------------------------------------------------------------}
{-----------  Speichert die berechneten Werte auf Diskette/Platte  ----}
{----------------------------------------------------------------------}
procedure werte_speichern;
const  yzeil = 16;
var  wertespeichern : char;
     l : integer;
begin
  datname:='SPEKTRUM';        { Defaulteinstellung }
  writeln;
  write('Berechnete Werte auf Diskette/Platte speichern (J/N) ? ');
  readln(wertespeichern);
  wertespeichern:=upcase(wertespeichern);
  if wertespeichern='J'
   then
     begin
       writeln;
       gotoxy(1,yzeil);
       write('Kommentar zum Datensatz:');
       gotoxy(1,yzeil+1);
       for l:=1 to 80 do write(#205);
       gotoxy(1,yzeil+2);
       write(kommentar);
       gotoxy(1,yzeil+3);
       for l:=1 to 80 do write(#205);
       gotoxy(1,yzeil+2);
       readln(kom);
       if (kom<>'') then kommentar:=kom;
       gotoxy(1,yzeil+4);
       write('Dateinamen eingeben (max. 8 Zeichen, ');
       write('.DAT wird automatisch gesetzt) : ');
       gotoxy(1,yzeil+6);
       write('Die Speicherung erfolgt nach der Berechnung des Spektrums.');
       gotoxy(72,yzeil+4);
       readln(datnam);
       if (length(datnam)<>0) then datname:=datnam;
       datname:=datname+'.DAT';
       if wertespeichern='J'
        then werte_save:=TRUE;
     end
   else  werte_save:=FALSE;
  writeln;
end;


{----------------------------------------------------------------------}
{--------------  Laedt ein berechnetes Spektrum von Disk  --------------}
{----------------------------------------------------------------------}
procedure spektrum_laden;
var  laden : char;
begin
  write('Soll ein Spektrum von Diskette/Platte geladen werden (J/N) ? ');
  readln(laden);
  laden:=upcase(laden);
  if laden='J' then
  begin
    writeln;
    write('Dateinamen eingeben (max. 8 Zeichen, ');
    write('.SPK wird automatisch gesetzt) : ');
    readln(spekname);
    spekname:=spekname+'.SPK';
    InitGraphic;
    SelectScreen(1);
    ClearScreen;
    LoadScreen(spekname);
    gotoxy(50,24);
    write('Bitte eine Taste drcken...');
    readln(ch);
    LeaveGraphic;
  end;
  writeln;
end;


{----------------------------------------------------------------------}
{--------------  Druckerausgabe des berechneten Spektrums  ------------}
{----------------------------------------------------------------------}
procedure spektrum_drucken;
label  stopdruck;
var  drucken : char;
begin
  write('Aktuelles Spektrum auf Drucker ausgeben (J/N) ? ');
  readln(drucken);
  drucken:=upcase(drucken);
  if drucken='J' then
  begin
    writeln;
    writeln('ACHTUNG: Drucker muss jetzt betriebsbereit sein !');
    write  ('         <RETURN>=Drucken / <Q>=Abbruch : ');
    readln(ch);
    ch:=upcase(ch);
    if (ch='Q') then
      begin
        writeln(#7,'Hardcopy cancelled !');
        goto stopdruck;
      end;
    write  ('         Ausdruck beginnt. Bitte einen Moment warten...');
    HardCopy(FALSE,1);                        {  EPSON-Drucker Mode=1  }
    writeln('Hardcopy beendet !');
    stopdruck:
  end;
  writeln;
end;


{----------------------------------------------------------------------}
{--------------  Plotterausgabe des berechneten Spektrums  ------------}
{----------------------------------------------------------------------}
procedure spektrum_plotten;
var  plotten : char;
begin
  write('Aktuelles Spektrum auf Plotter ausgeben (J/N) ? ');
  readln(plotten);
  plotten:=upcase(plotten);
  if plotten='J' then
  begin
    writeln;
    write('Plot beginnt. Bitte einen Moment warten...');
    {   PlotScreen;  }
    writeln('Plot beendet !');
    writeln('***   Plotter-Routine noch nicht implementiert !   ***');
  end;
  writeln;
end;
