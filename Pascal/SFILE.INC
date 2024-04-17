{  FILE.INC

   liesst die Parameter von Disk und speichert
   sie wieder ab.

}


{-----------------------------------------}
{---------   Dummy - Belegungen   --------}
{-----------------------------------------}

procedure belegen;
begin
{  for ii:=1 to lmax do
  begin
    linie.energy[ii]:=0.0;
    linie.fo:=0.0;
    linie.fu:=0.0;
    linie.linewidth:=0.0;
    linie.intensity:=0.0;
    linie.linewidth:=0.0;
  end; }
end;

{-----------------------------------------}
{-----  Kosmetik der Ausgaberoutine   ----}
{-----------------------------------------}

procedure tabs(var tabzahl:integer);
begin
  if test then
  begin
    for ij:=1 to tabzahl do write(#196);
    writeln;
  end;
end;

{-----------------------------------------}
{-------  Parameterdatei einlesen   ------}
{-----------------------------------------}

procedure parameter_load;

  { Fehlermeldung: Parameter-Datei nicht in Ordnung }
  procedure file_error;
  begin
  {if ioresult then
    begin
      writeln(#7,#7,#7,meldung_param);
      exit;
    end;}
  end;

begin
  { Parameterdatei einlesen }
  meldung_param:='Parameterdatei SPEKTRUM.PAR nicht in Ordnung !';
  pardatei:='SPEKTRUM.PAR';
  assign(filvar,pardatei);
  reset(filvar);
  readln(filvar);     { Die ersten beiden Zeilen ueberlesen }
  readln(filvar);
  readln(filvar,defaultelement);
  readln(filvar,defaultvon);
  readln(filvar,defaultnach);
  readln(filvar,ao);
  readln(filvar,au);
  readln(filvar,bo);
  readln(filvar,bu);
  readln(filvar,jo);
  readln(filvar,ju);
  readln(filvar,ikern);
  readln(filvar,kommentar);
  close(filvar);
  file_error;
end;

{-----------------------------------------}
{-------  Parameterdatei speichern  ------}
{-----------------------------------------}

procedure parameter_save;
begin
  clrscr;
  gotoxy(1,3);
  write('Letztgltiger Parametersatz wird gespeichert in SPEKTRUM.PAR');
  gotoxy(1,9); write('                                                ');
  gotoxy(1,9);
  write('Kommentar zum Datensatz:');
  gotoxy(1,10);
  for ij:=1 to 80 do write(#205);
  gotoxy(1,12);
  for ij:=1 to 80 do write(#205);
  gotoxy(1,11);
  write(kommentar);
  gotoxy(1,11);
  readln(kom);
  if (kom<>'') then kommentar:=kom;

  pardatei:='SPEKTRUM.PAR';
  assign(filvar,pardatei);
  rewrite(filvar);
  writeln(filvar,'Spektrumparameter: (Element/unt. Zust./ober. Zust./');
  writeln(filvar,'------------------   Ao/Au/Bo/Bu/Jo/Ju/I/Kommentar)');
  writeln(filvar,element);
  writeln(filvar,vonzustand);
  writeln(filvar,nachzustand);
  writeln(filvar,ao:12:4);
  writeln(filvar,au:12:4);
  writeln(filvar,bo:12:4);
  writeln(filvar,bu:12:4);
  writeln(filvar,jo:3:1);
  writeln(filvar,ju:3:1);
  writeln(filvar,ikern:3:1);
  writeln(filvar,kommentar);
  close(filvar);
end;

{--------------------------------------}
{-------  Profilparameter lesen  ------}
{--------------------------------------}

procedure profil_parameter_load;
begin
  profildatei:='SPROFIL.PAR';
  assign(filvar,profildatei);
  reset(filvar);
  readln(filvar);
  readln(filvar,untergrund);
  readln(filvar,FWHM);
  readln(filvar,aufloesung);
  close(filvar);
end;

{------------------------------------------}
{-------  Profilparameter schreiben  ------}
{------------------------------------------}

procedure profil_parameter_save;
begin
  gotoxy(1,4);
  write('Letztgltige Profilparameter werden gespeichert in SPROFIL.PAR');
  untergrund:=untergrund-205;
  profildatei:='SPROFIL.PAR';
  assign(filvar,profildatei);
  rewrite(filvar);
  writeln(filvar,'Profilparameter (Untergrund/FWHM/Aufloesung):');
  writeln(filvar,untergrund:4:2);
  writeln(filvar,FWHM:4:2);
  writeln(filvar,aufloesung:4);
  close(filvar);
  gotoxy(1,14);
end;
