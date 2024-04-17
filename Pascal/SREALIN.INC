{   SREALIN.INC

    liesst eine REAL-Zahl der Laenge = laenge ein
    und uebergibt sie bei RETURN.
    Zulaessige Eingaben sind:
      0,1,2,3,4,5,6,7,8,9
      - an der ersten Stelle und
      . als Dezimalpunkt.
    Andere Eingaben werden abgefangen.
}

function realin(xcurs,ycurs:integer; question:str80; laenge:integer):real;
label  weiter;
var
    line     : string[20];
    y        : integer;
    ch       : char;
    zeichen  : set of char;
    zahl     : real;
    dez_stelle,del_zaehler : integer;
    zaehler  : integer;
    dezimal  : integer;

begin
  zahl:=0;
  dezimal:=0;
  zaehler:=0;
  dez_stelle:=0;
  del_zaehler:=0;
  zeichen:=['0'..'9','-','.'];
  line:='';
  gotoxy(xcurs,ycurs);
  write(question);
  repeat
    read(KBD,ch);

    if ch in zeichen then
    begin
      if length(line) < laenge then
      begin
        { Minuszeichen nur am Anfang erlaubt }
        if (ch='-') and (length(line) > 0)
          then goto weiter;
        {  Dezimalpunkt wird 1x zugelassen  }
        if (ch='.') then
          begin
            dezimal:=dezimal+1;
            dez_stelle:=zaehler;
          end;
        if ((dezimal > 1) and (ch='.')) then goto weiter;
        write(ch);
        line:=line+ch;
        zaehler:=zaehler+1;
        weiter:
      end;
    end;

    (*  Backspace loescht die Eingabe  *)
    if (ch=^H) and (length(line) >0) then
    begin
      write (ch,' ',^H); line:=copy(line,1,length(line)-1);
      del_zaehler:=del_zaehler+1;
      (* falls Dezimalpunkt geloescht wurde, muss er
         erneut gesetzt werden duerfen.             *)
      if (del_zaehler=dez_stelle-1) then dezimal:=0;
    end;

    if y=1 then val(copy(line,2,length(line)),zahl,y);

  until ch=^M;             { Ende, falls RETURN gedrueckt wird }
  val(line,zahl,y);
  realin:=zahl;
end;

{-----------------------------------------------------------------}
