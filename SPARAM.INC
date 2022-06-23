{  SPARAM.INC

   Parameter einlesen fuer SPEKTRUM-Programm
   A-, B-Faktoren    >  fuer jeweils den
   J-Drehimpulse     >  unteren/oberen Zustand
   I-Kernspin

}

var  unt : real;

{-----------------------------------------}
{--- Anfangsroutine Intro: allg. Daten  --}
{-----------------------------------------}

procedure intro;
var  ok : char;
     strx,strx1,strx2 : str12;
begin
  clrscr;
  highvideo;
  write(#201); for ij:=1 to 78 do write(#205); write(#187);
  gotoxy(1,2);
  write(#186,'   SPEKTRUM    -    HFS-Spektrum in Abhaengigkeit ');
  write('der A- und B-Faktoren');
  gotoxy(80,2); write(#186);
  gotoxy(1,3);
  write(#200); for ij:=1 to 78 do write(#205); write(#188);
  lowvideo;

  gotoxy(1,15);
  for ij:=1 to 80 do write(#205);
  gotoxy(1,17);
  for ij:=1 to 80 do write(#205);
  gotoxy(1,16);
  write(kommentar);

  repeat
    gotoxy(1,5);
    write('Bitte die Spektrumdaten eingeben :');
    gotoxy(1,7);
    write(' Welches Element (z.B.: Zirkon) : ',defaultelement);
    gotoxy(35,7);
    readln(strx);
    if ((strx<>defaultelement) and (length(strx)<>0))
     then element:=strx
     else element:=defaultelement;
    gotoxy(1,9);
    writeln('Welcher Uebergang soll betrachtet werden ?');
    gotoxy(1,10);
    write(' öbergang von Zustand           : ',defaultvon);
    gotoxy(35,10);
    readln(strx1);
    gotoxy(1,11);
    write(' nach Zustand                   : ',defaultnach);
    gotoxy(35,11);
    readln(strx2);
    if ((strx1<>defaultvon) and (length(strx1)<>0))
     then vonzustand:=strx1
     else vonzustand:=defaultvon;
    if ((strx2<>defaultvon) and (length(strx2)<>0))
     then nachzustand:=strx2
     else nachzustand:=defaultnach;
    gotoxy(1,14);
    write(#7);
    write('Alle Parameter richtig (J/N) ? ');readln(ok);
    ok:=upcase(ok);
  until (ok='J');
end;

{-----------------------------------------}
{----  Eingaberoutine der Parameter  -----}
{-----------------------------------------}

procedure parameter_eingeben;
var  l,zei :integer;
     xao,xau,xbo,xbu,xjo,xju,xikern,
     xunt,xfwhm,xaufl : real;

begin
  nulltestok:=FALSE;            { Sicherheitshalber: Parameter = Null }
  repeat
    clrscr;
    writeln('Bitte Parameter eingeben (u=unterer/o=oberer Zustand):');
    writeln('(A-, B-Faktoren in [MHz], Drehimpulse in h-Vielfachen)');
    repeat
    { Parameter aus SPEKTRUM.PAR abfragen }

      zei:=4;
      gotoxy(6,zei); writeln(ao:9:4);
      xao:=realin(1,zei,'Ao = ',9);
      if xao<>0 then ao:=xao;

      gotoxy(6,zei+1); writeln(au:9:4);
      xau:=realin(1,zei+1,'Au = ',9);
      if xau<>0 then au:=xau;

      gotoxy(6,zei+2); writeln(bo:9:4);
      xbo:=realin(1,zei+2,'Bo = ',9);
      if xbo<>0 then bo:=xbo;

      gotoxy(6,zei+3); writeln(bu:9:4);
      xbu:=realin(1,zei+3,'Bu = ',9);
      if xbu<>0 then bu:=xbu;

      gotoxy(6,zei+4); writeln(jo:3:1);
      xjo:=realin(1,zei+4,'Jo = ',4);
      if xjo<>0 then jo:=xjo;

      gotoxy(6,zei+5); writeln(ju:3:1);
      xju:=realin(1,zei+5,'Ju = ',4);
      if xju<>0 then ju:=xju;

      gotoxy(6,zei+6); writeln(ikern:3:1);
      xikern:=realin(1,zei+6,'I  = ',4);
      if xikern<>0 then ikern:=xikern;

    { Parameter aus SPROFIL.PAR abfragen }
      unt:=untergrund-205;

      gotoxy(43,zei); writeln(unt:4:0);
      xunt:=realin(30,zei,'Untergrund = ',4);
      if xunt<>0 then untergrund:=xunt+205;

      gotoxy(43,zei+1); writeln(FWHM:4:0);
      xfwhm:=realin(30,zei+1,'FWHM [MHz] = ',3);
      if xfwhm<>0 then FWHM:=xfwhm;

      gotoxy(43,zei+2); writeln(aufloesung:4);
      xaufl:=realin(30,zei+2,'Auflîsung  = ',4);
      if xaufl<>0 then aufloesung:=trunc(xaufl);

      writeln(#7);
      gotoxy(1,zei+8);
      write('Alle Parameter richtig (J/N) ? ');readln(antwort);
      antwort:=upcase(antwort);
    until antwort='J';

    { Abfrage Drehimpulse ungleich Null }
    if (ju<>0) and (jo<>0) and (ikern<>0) then
       nulltestok:=TRUE
    else
      begin
        highvideo;
        gotoxy(1,19);
        for l:=1 to 80 do write(#205);
        gotoxy(1,21);
        for l:=1 to 80 do write(#205);
        gotoxy(1,20);
        writeln('ACHTUNG : Drehimpulse Ju, Jo und I mÅssen ungleich Null sein !');
        write(#7,#7,#7);
        lowvideo;
        for t:=1 to 10000 do;
        readln;
      end;
  until nulltestok;
end;
