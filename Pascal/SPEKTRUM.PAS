{   SPEKTRUM.PAS

    berechnet das HFS-Spektrum eines Elementes in Abhaengigkeit
    der A- und B-Konstanten bei bekannten Drehimpulseigen-
    werten ( J, I ).
    Die F-, K-, W- und Energiewerte fuer jeweils den unteren bzw.
    oberen Zustand werden berechnet und ausgegeben.
    Die Linien lassen sich als einzelne Lorentz- bzw. Gau疳rofile
    ausgeben, oder auf Wunsch als Summenprofil am Bildschirm oder
    auf dem Drucker anzeigen.
    Fuer die Druckerausgabe benetigt man bei der HERCULES-Karte das
    Systemprogramm HGC.COM mit den Optionen (HGC FULL HPRINT).
    Hiernach ist der residente Teil des Print-Screen Hardcopy-
    Programms auf die Grafikseite "umgebogen", und bei Dr…ken der
    Tastenkombination <Shift>+<Prt-Sc>+<n> erscheint ein Hardcopy
    auf dem jeweils angeschlossenem Drucker.
    ( n = 0, Ausdruck quer  im Format DIN A4 )
    Fuer weitere Informationen siehe Datei SPEKTRUM.TXT


    (C) 1986/1987  Institut fuer Angewandte Physik
                   der Universitaet Bonn

    Thomas Fabula, Wolfgang Rupprecht

}

program spektrum;

{ Einbinden der GRAPHIX Turbo-Toolbox notwendigen Zeichenroutinen,   }
{ GRAPHIX.SYS angepasst auf Hercules-Grafikkarte (720x348 pixel)      }
{ d.h. zur Installation vorher GRAPHIX.HGH nach GRAPHIX.SYS kopieren.}

{$I typedef.sys}          { System unabhaengige Typendefinitionen     }
{$I graphix.sys}          { System abhaengige Definitionen & Routinen }
{$I kernel.sys}           { System unabhaengige Support Routinen      }

{$I sdeclare.inc}         { Deklarationen (const, type, var)         }
{$I njsymbol.inc}         { Berechnung der nj-Symbole    (T.Brenner) }
{$I srealin.inc}          { REAL-Zahl Einleseroutine                 }
{$I sfile.inc}            { Disketten I/O-Routinen f〉 Parameter     }
{$I sparam.inc}           { Parameter editieren                      }
{$I sfunct.inc}           { Programmfunktionen: Drucken,Plotten,etc. }

const  grafik_skal = 500;      { Skalierung der Intensitaeten fuer Bildschirm }

var    intensi      : real;            { Hilfsvariable }
       skal_intensi : real;            { Skalierung Int(max) = 100 % }
       x_links      : real;            { linke  Bildschirmkante }
       x_rechts     : real;            { rechte Bildschirmkante }
       xlo,ylo      : real;            { Hilfsvariablen Lorentz }
       deltalo      : real;            {       "           "    }
       x_min,x_max  : real;            { Hilfsvariablen Grafik  }
       delta_X,null : real;            {       "           "    }
       offset       : real;            {       "           "    }
       profil       : char;            { Auswahl Profilart (L/G)}
       sum          : char;            { Auswahl Summation      }
       profanz      : integer;         { akt. gez. Profil       }
       ysum         : array [1..1000] of real;
                                       { Aufsummiertes Linienprofil }
       skal_sum     : real;            { Skalierung Sum(max) = 100 % }
       hfsaufsp     : real;            { Gesamte Hfs-Aufspaltung }
       ijk          : integer;         { Laufindex              }
       schalter     : boolean;         { Steuervariable         }
       summi        : integer;         { Zaehler fuer Profilberechnung }

{ ACHTUNG : Die maximale Aufoesung der HFS-Spektren
            [ Variable : aufloesung ] betraegt 1000 }

{------------------------------}
{-----   Lorentzprofil   ------}
{------------------------------}

function lorentz(var energie,e_0,intensy : real) : real;
var zaehler,nenner : real;
begin { lorentz }
  zaehler:=sqr(FWHM);
  nenner:=sqr(energie - e_0);
  nenner:=nenner+0.25*zaehler;
  if (nenner=0) then
    begin
      writeln(#7,#7,#7);
      writeln('Lorentz: Division durch Null');
      halt;
    end { if };
  lorentz:=intensy*zaehler/nenner;
end { lorentz };

{----------------------------}
{-----   Gaussprofil   ------}
{----------------------------}

function gauss(var energie,e_0,intensy : real) : real;
var ar,argum : real;
begin { gauss }
  argum:=abs(energie-e_0);
  if (FWHM=0) then
    begin
      writeln(#7,#7,#7);
      writeln('Gauss:  FWHM = Null');
      halt;
    end { if };
  argum:=argum/FWHM;
  ar:=sqr(argum);
  gauss:=intensy*exp(-ar*0.5);
end { gauss };

{-------------------------------------------------}
{-------  Berechnen eines Lorentzprofils  --------}
{-------------------------------------------------}

procedure lorentz_profil(var resonance,inten:real; switchi:boolean);
begin { lorentz_profil }
  ijk:=1;
  if switchi then
    begin
      gotoxy(3,23);
      write('Lorentz');
      gotoxy(73,2);
      write('Lorentz');
    end { if };
  ylo:=0;
  xlo:=x_links;
  deltalo:=abs(x_links-x_rechts)/aufloesung;
  { 0        <= Y-Achse <= 1000     }
  { x_links  <  X-Wert  <  x_rechts }
  repeat
    ylo:=0.25*lorentz(xlo,resonance,inten);
    ysum[ijk]:=ysum[ijk]+ylo;  { Aufsummierung des Signals }
    ylo:=untergrund+ylo;
    if switchi then DrawPoint(xlo,ylo);
    xlo:=xlo + deltalo;   { X-Wert erhoehen }
    ijk:=ijk+1;           { Laufindex fuer Summe erhoehen }
  until (xlo > x_rechts);
end { lorentz_profil };

{-----------------------------------------------}
{-------  Berechnen eines Gaussprofils  --------}
{-----------------------------------------------}

procedure gauss_profil(var resonanc,inte:real; switch:boolean);
begin { gauss_profil }
  ijk:=1;
  if switch then
   begin
     gotoxy(3,23);
     write('Gauss');
     gotoxy(73,2);
     write('Gauss');
   end { if };
  ylo:=0;
  xlo:=x_links;
  deltalo:=abs(x_links-x_rechts)/aufloesung;
  { 0        <= Y-Achse <= 1000     }
  { x_links  <  X-Wert  <  x_rechts }
  repeat
    ylo:=gauss(xlo,resonanc,inte);
    ysum[ijk]:=ysum[ijk]+ylo;  { Aufsummierung des Signals }
    ylo:=untergrund+ylo;
    if switch then DrawPoint(xlo,ylo);
    xlo:=xlo + deltalo;   { X-Wert erhoehen }
    ijk:=ijk+1;           { Laufindex fuer Summe erhoehen }
  until (xlo > x_rechts);
end { gauss_profil };

{----------------------------------------------}
{-------  Berechnen der Intensitaeten  --------}
{-------  Intens(ju,jo,fu,fo,ikern)   ---------}
{-------   ｜er die sechsJ-Symbole    ---------}
{----------------------------------------------}

function intens(var juu,joo,fuu,foo,ikernspin : real) : real;
var temp1,temp2,xq : real;
begin { intens }
  temp1:=2*foo+1;
  temp2:=2*fuu+1;
  temp1:=temp1*temp2;
  { SechsJ-Symbole siehe Datei : njsymbol.inc }
  xq:=sechsJ(joo,foo,ikernspin,fuu,juu,1);
  intens:=temp1*xq*xq;
end { intens };


{-----------------------------------------------}
{-------  Skalierung der Intensitaeten  --------}
{-----------------------------------------------}

procedure skal_intensity;
{ Skalierung der Intensitдen, suchen von Int(max) }
var   max_intensi,such_intensi : real;
begin { skal_intensity }
  tabs(t);
  writeln('Skalierung der Intensitдen auf 100% ... !');
  max_intensi:=0.001;
  for n:=0 to maxxu do
  begin
    for m:=0 to maxxo do
    begin
      if ( ( fu[n]-fo[m] = 0) or (abs( fu[n] - fo[m]) = 1) ) then
      begin
        {  maximale Linien-Intensitдen  }
        such_intensi:=intens(ju,jo,fu[n],fo[m],ikern)*100;
        if (such_intensi > max_intensi) then max_intensi := such_intensi;
      end { if };
    end { for };
  end { for };
  skal_intensi := 100 / max_intensi;
end { skal_intensity };


{-----------------------------------------}
{--  Abspeichern der berechneten Werte  --}
{- Fu(n), Fo(n), Wu(n), Wo(n) und E(n,m) -}
{-----------------------------------------}

procedure save;
label ende;
begin { save }
  writeln('Spektrumdaten werden gespeichert in der Datei : ',datname);
  assign(filvar,datname);
  rewrite(filvar);             { gleichnamige Datei wird 「eberschrieben }
  {  Parameter  }
  writeln(filvar,'Spektrumdaten:');
  writeln(filvar,'==============');
  writeln(filvar,'Element   : ',element);
  writeln(filvar,'Uebergang : ',vonzustand,' -> ',nachzustand);
  writeln(filvar);
  writeln(filvar,'Parameter:');
  writeln(filvar,'----------');
  writeln(filvar,'Ao [MHz] = ',ao:15:6);
  writeln(filvar,'Au [MHz] = ',au:15:6);
  writeln(filvar,'Bo [MHz] = ',bo:15:6);
  writeln(filvar,'Bu [MHz] = ',bu:15:6);
  writeln(filvar,'Ju       = ',ju:10:1);
  writeln(filvar,'Jo       = ',jo:10:1);
  writeln(filvar,'I        = ',ikern:10:1);
  {  F-Werte  }
  writeln(filvar);
  writeln(filvar,'F-Werte:');
  writeln(filvar,'--------');
  for ii:=0 to maxxu do writeln(filvar,'Fu(',ii:1,')   =  ',fu[ii]:10:1);
  writeln(filvar);
  for ii:=0 to maxxo do writeln(filvar,'Fo(',ii:1,')   =  ',fo[ii]:10:1);
  {  K-Werte  }
  writeln(filvar);
  writeln(filvar,'K-Werte:');
  writeln(filvar,'--------');
  for ii:=0 to maxxu do writeln(filvar,'Ku(',fu[ii]:3:1,')   =  ',ku[ii]:10:1);
  writeln(filvar);
  for ii:=0 to maxxo do writeln(filvar,'Ko(',fo[ii]:3:1,')   =  ',ko[ii]:10:1);
  {  W-Werte  }
  writeln(filvar);
  writeln(filvar,'W-Werte [MHz]:');
  writeln(filvar,'--------------');
  for ii:=0 to maxxu do writeln(filvar,'Wu(',fu[ii]:3:1,')   =  ',wu[ii]:15:6);
  writeln(filvar);
  for ii:=0 to maxxo do writeln(filvar,'Wo(',fo[ii]:3:1,')   =  ',wo[ii]:15:6);
  {  Energiewerte E(n,m)  }
  writeln(filvar);
  writeln(filvar,'E(Fo,Fu)-Werte [MHz]:');
  writeln(filvar,'---------------------');
  for n:=0 to maxxu do
  begin
    for m:=0 to maxxo do
    begin
      if ( ( fu[n]-fo[m] = 0) or (abs( fu[n] - fo[m]) = 1) ) then
      begin
        if ( ( fu[n]=0) and (fo[m]=0) )  then goto ende;
        energie[m,n] := wo[m] - wu[n];
        write(filvar,'E(',fo[m]:3:1,',',fu[n]:3:1,') = ',energie[m,n]:15:6);
        {  Linien-Intensitдen skaliert auf 100 % }
        intensi:=skal_intensi*intens(ju,jo,fu[n],fo[m],ikern)*100;
        writeln(filvar,'   (Int : ',intensi:6:2,'%)');
        ende:
      end { if };
    end { for };
  end { for };
  writeln(filvar);
  writeln(filvar,'Anzahl Linien   = ',linien_anzahl:3);
  writeln(filvar,'Energie [min]   = ',energmin:15:6,'  [MHz]');
  writeln(filvar,'Energie [max]   = ',energmax:15:6,'  [MHz]');
  writeln(filvar,'Hfs-Aufspaltung = ',hfsaufsp:15:6,'  [GHz]');
  writeln(filvar);
  writeln(filvar,'Kommentar :');
  writeln(filvar,'-----------');
  writeln(filvar,kommentar);
  { Ende des Abspeicherns }
  close(filvar);
end { save };


{-----------------------------------------}
{-------  Berechnen der F-Werte:  --------}
{----   F = I + J , ... , abs(I - J)   ---}
{-----------------------------------------}

procedure berechne_f;
begin { berechne_f }
  tabs(t);
  { Berechnung f〉 den unteren Zustand }
  j:=ju;
  if j>=ikern then max:=ikern
  else max:=j;
  maxxu:=trunc(2*max+1+0.1);     { Integerzahl aus Drehimpuls machen }
  maxxu:=maxxu-1;                { und sicher gehen, das nicht       }
  for n:=0 to maxxu do           { abgerundet wird                   }
  begin
    fu[n] := ikern + j - n;
    if test then WRITELN('Fu(',n,') = ',FU[N]:10:1);
  end { for };
  tabs(t);
  { Berechnung fuer den oberen Zustand }
  j:=jo;
  if j>=ikern then max:=ikern
  else max:=j;
  maxxo:=trunc(2*max+1+0.1);      { Integerzahl aus Drehimpuls machen }
  maxxo:=maxxo-1;
  for n:=0 to maxxo do
  begin
    fo[n] := ikern + j - n;
    if test then WRITELN('Fo(',n,') = ',FO[N]:10:1);
  end { for };
end { berechne_f };

{-----------------------------------------}
{------  Berechnen der K-Werte:  ---------}
{----  K = F(F+1) - I(I+1) - J(J+1)  -----}
{----        ( Casimir )             -----}
{-----------------------------------------}

procedure berechne_k;
begin { berechne_k }
  tabs(t);
  { Berechnung fuer den unteren Zustand }
  for n:=0 to maxxu do
  begin
    j:=ju;
    f:=fu[n];
    ku[n]:=f*(f+1)-ikern*(ikern+1)-j*(j+1);
    if test then writeln('Ku(',fu[n]:3:1,') = ',ku[n]:10:1);
  end { for };
  tabs(t);
  { Berechnung fuer den oberen Zustand }
  for n:=0 to maxxo do
  begin
    j:=jo;
    f:=fo[n];
    ko[n]:=f*(f+1)-ikern*(ikern+1)-j*(j+1);
    if test then writeln('Ko(',fo[n]:3:1,') = ',ko[n]:10:1);
  end { for };
end { berechne_k };


{--------------------  Berechnen der W-Werte:  ------------------------}
{   W = 1/2h ( K*A + (3/4 K(K+1)-I(I+1)J(J+1))*B/(I(2I-1)J(2J-1)) )    }
{                Energiewerte W in [MHz] - Einheiten                   }
{                h  =    Planck'sches Wirkungsquantum                  }
{----------------------------------------------------------------------}
procedure berechne_w;

  function w_zahl(var a,b,k,ij,ji : real):real;
  { Berechnung des HFS-Niveau-Energiewertes }
  var  sum1,zaehler,nenner,wzahl : real;
  begin { w_zahl }
    sum1:=k*a*0.5;
    zaehler:=ij*(ij+1)*ji*(ji+1);
    zaehler:=0.75*k*(k+1)-zaehler;
    if b=0
      then nenner:=1
      else nenner:=2*ij*(2*ij-1)*ji*(2*ji-1);
    { Falls  I,J = 1/2  dann  B = 0 }
    if ( (ij=0.5) or (ji=0.5) )
      then wzahl:=zaehler
      else wzahl:=zaehler*b/nenner;
    w_zahl:=(sum1+wzahl)*h;
  end { w_zahl };

begin { berechne_w }
  tabs(t);
  { Berechnung fuer den unteren Zustand  }
  for m:=0 to maxxu do
  begin
    f:=fu[m];
    k:=ku[m];
    wu[m]:=w_zahl(au,bu,k,ikern,ju);
   if test then writeln('Wu(',fu[m]:3:1,') = ',wu[m]:15:6);
  end { for };
  tabs(t);
  { Berechnung fuer den oberen Zustand  }
  for m:=0 to maxxo do
  begin
    f:=fo[m];
    k:=ko[m];
    wo[m]:=w_zahl(ao,bo,k,ikern,jo);
    if test then writeln('Wo(',fo[m]:3:1,') = ',wo[m]:15:6);
  end { for };
end { berechne_w };


{----------------  Berechnen der Energiezuordnungen  ------------------}
{                  unter Beachtung der Auswahlregeln:                  }
{                                                                      }
{                       delta(F) = 0, +1, -1     und                   }
{                  Ubergang F = 0 nach F = 0  verboten                 }
{                                                                      }
{                       Wo(n) - Wu(m)  ==>  E(n,m)                     }
{                Energiewerte W,E in [MHz] - Einheiten                 }
{----------------------------------------------------------------------}
procedure energien_zuordnung;
label ende;
var  ft,iii : integer;
     intens_0 : integer;
begin { energien_zuordnung }
  iii:=0;
  intens_0:=0;
  energmin:=10000.0;
  energmax:=0;
  ft:=46;
  tabs(ft);
  for n:=0 to maxxu do
  begin
    for m:=0 to maxxo do
    begin
      if ( ( fu[n]-fo[m] = 0) or (abs( fu[n] - fo[m]) = 1) )  then
      begin
        if ( ( fu[n]=0) and (fo[m]=0) )  then goto ende;
        energie[m,n] := wo[m] - wu[n];
        linien_anzahl:=linien_anzahl+1;
        if test then write('E(',fo[m]:3:1,',',fu[n]:3:1,') = ',energie[m,n]:15:6);
        {  Linien-Intensitaeten  }
        intensi:=skal_intensi*intens(ju,jo,fu[n],fo[m],ikern)*100;
        writeln('   (Int : ',intensi:6:2,'%)');
        {  Aussortieren der Linien mit Intensitaet = 0  }
        if (intensi=0) then intens_0:=intens_0 + 1;
        {  Aussortieren von Emax und Emin  }
        if energmin >= energie[m,n] then energmin:=energie[m,n];
        if energmax <= energie[m,n] then energmax:=energie[m,n];
        ende:
      end { if };
    end { for };
    writeln;
    { Gesamt Hfs-Aufspaltung in  GHz  berechnen }
    hfsaufsp:=(abs(energmin)+abs(energmax))*0.001;
end { for };
  tabs(ft);
  if test then
    begin
      linien_anzahl:=linien_anzahl - intens_0;
      writeln('Hfs-Aufspaltung   = ',hfsaufsp:15:6,' [GHz]');
      writeln('Anzahl der Linien : ',linien_anzahl:2);
      tabs(ft);
      write('Bitte <RETURN> druecken : ');
      readln(ch);
    end { if };
end { energien_zuordnung };

{--------------------------------------}
{-------  Linien aufsummieren  --------}
{--------------------------------------}

procedure summation(var doit:boolean);
{ Aufsummiertes Spektrum einzeichnen }
var  ll,ysumme,summax : real;
begin { summation }
  if doit then
    begin
      gotoxy(73,3); write('- Summe');
    end { if };
  { Aufsummiertes Spektrum auf 100% normieren }
  {
  summax:=0;
  for i:=1 to aufloesung do
   if (ysum[i] > summax) then summax:=ysum[i];
  skal_sum:= 100 / summax;
  }
  ylo:=0;
  xlo:=x_links;
  deltalo:=abs(x_links-x_rechts)/aufloesung;
  ll:=1;
  repeat
    { Aufsummiertes Signal einzeichnen }
    { ysumme:=untergrund+ysum[trunc(ll)]*5*skal_sum;  }
    ysumme:=untergrund+ysum[trunc(ll)];
    DrawPoint(xlo,ysumme);
    xlo:=xlo + deltalo;   { X-Wert erhoehen }
    ll:=ll+1;             { Laufindex fuer Summe erhoehen }
  until (xlo > x_rechts);
  gotoxy(62,24); write('        <<RETURN>>');
  readln(ch);
  LeaveGraphic;
end { summation };

{--------------------------------------------}
{-------  Nur Einhuellende zeichnen  --------}
{--------------------------------------------}

procedure einhuellende(var character: char);
{ nur Aufsummiertes Spektrum einzeichnen }
label  wende;

begin { einhuellende }
  summi:=1;
  gotoxy(72,2);
  write('Rechnung');
  gotoxy(72,3);
  write('lеft:');
  for n:=0 to maxxu do
  begin
    for m:=0 to maxxo do
    begin
      if (( fu[n]-fo[m] = 0) or (abs( fu[n] - fo[m]) = 1)) then
         begin
           if ( ( fu[n]=0) and (fo[m]=0) )  then goto wende;
           x:=energie[m,n];
           intensity:=intens(ju,jo,fu[n],fo[m],ikern)*skal_intensi;
           intensity:=intensity*grafik_skal;
           schalter:=FALSE;  { Benutze Routinen nur f〉 Berechnungen,
                               d.h. Einzel-Linien nicht einzeichnen }
           gotoxy(78,3);     { anzeigen welche Linie berechnet wird }
           write(summi:2);
           case character of
             'L' : lorentz_profil(x,intensity,schalter);
             'G' : gauss_profil(x,intensity,schalter);
           end { of case };
           summi:=summi+1;
           wende:
         end { if };
    end { for };
  end { for };

  case character of

   'L' :  begin
            gotoxy(72,2);
            write(' Lorentz');
            gotoxy(72,3);
            write(' -Profil');
            summation(schalter);
          end;

   'G' :  begin
            gotoxy(72,2);
            write(' Gauss  ');
            gotoxy(72,3);
            write(' -Profil');
            summation(schalter);
          end;
  end { of case };
end { einhuellende };


{--------------------------------------}
{-------  Y-Achse einzeichnen  --------}
{--------------------------------------}

procedure y_axis;
var  iu : integer;
     x_achse,y_einh,dd : real;
begin { y_axis }
  dd:=delta_X/150;
  y_einh:=0.10*grafik_skal+205;
  x_achse:=x_min-offset/2;            { 0  <= Y-Achse <= 100 % }
  drawline(x_achse,205,x_achse,790);  { Achse einzeichnen }

  { Markierungen }
  for iu:=1 to 10 do
  begin
    DrawLine(x_achse-dd,y_einh,x_achse+dd,y_einh);
    y_einh:=y_einh+0.10*grafik_skal;
  end { for };

  gotoxy(6,6);  write(#30);      { Pfeil einzeichnen }
  gotoxy(2,5);  write('Intens.');
  gotoxy(2,6);  write('[%]');
  gotoxy(2,8);  write('100');
  gotoxy(2,13); write(' 60');
  gotoxy(2,18); write(' 20');
end { y_axis };

{-------------------------------------}
{-------  Grafik vorbereiten  --------}
{-------------------------------------}

procedure begin_grafik;
begin { begin_grafik }
  null:=0;
  delta_X:=abs(energmax)+abs(energmin);
  offset:=delta_X*0.2;
  x_min:=energmin;
  x_max:=energmax;
  InitGraphic;                            {init the system and screen}
  SelectScreen(1);
  ClearScreen;                         { Wertebereiche fuer Grafik:     }
  x_links:=x_min-offset;            { 0      <= Y-Achse <= 1000     }
  x_rechts:=x_max+offset;           { x_links < X-Wert  <  x_rechts }
  DefineWorld(1,x_links,0,x_rechts,1000); {define a world for drawing}
  SelectWorld(1);                         {select it}
  SelectWindow(1);
  SetBackground(0);
  DrawBorder;
  DrawLine(x_links,200,x_rechts,200);      {  doppelte Energieachse  }
  DrawLine(x_links,205,x_rechts,205);      {  [MHz] zeichnen         }

  DrawLine(x_links,870,x_rechts,870);      { Fenster fuer Fu/Fo-Werte }
  DrawLine(x_links,850,x_rechts,850);
  y_axis;                                  { Y-Achse einzeichnen     }
  SetLineStyle(3);                         { gestrichelte Linie      }
  DrawLine(null,200,null,870);         {  Linienschwerpunkt zeichnen }
  SetLineStyle(0);
  gotoxy(3,2);
  write(element);                             {  Elementbezeichnung  }
  writeln(',  喘ergang : ',vonzustand,' -> ',nachzustand);
  gotoxy(52,2);
  write('HFS - SPEKTRUM');
  gotoxy(52,3);
  write('* Simulation *');
  gotoxy(3,22);
  write('Profilart <L>orentz / <G>auss : ');
  readln(profil);
  profil:=upcase(profil);
  gotoxy(35,22); write(profil);
  profanz:=0;
  gotoxy(65,21);
  write('Energie [MHz]');
end { begin_grafik };


{----------------------------------------}
{-------   Grafik abschliessen   --------}
{----------------------------------------}

procedure end_grafik;
var art : char;
    zeige : boolean;
begin { end_grafik }
  { Loeschen der Abfrage }
  gotoxy(3,22);
  write('                                     ');
  gotoxy(3,23);
  write('                                     ');
  gotoxy(3,22);  write('Au = ',au:11:6);
  gotoxy(23,22); write('Ao = ',ao:11:6);
  gotoxy(3,23);  write('Bu = ',bu:11:6);
  gotoxy(23,23); write('Bo = ',bo:11:6);
  gotoxy(3,24);  write('Ju = ',ju:2:1);
  gotoxy(18,24); write('Jo = ',jo:2:1);
  gotoxy(32,24); write('I = ',ikern:2:1);
  gotoxy(42,22); write('E(min) = ',energmin:7:3);
  gotoxy(42,23); write('E(max) = ',energmax:7:3);
  gotoxy(42,24); write('Anzahl = ',linien_anzahl:3);

  gotoxy(62,22); write('Untergrund = ',unt:3:0);
  gotoxy(62,23); write('FWHM [MHz] = ',FWHM:3:0);
  gotoxy(62,24); write('<S>ummiere : ');

  readln(sum);
  sum:=upcase(sum);
  if (sum='S')
   then
    begin
      if ((profil='L') or (profil='G'))
       then
        begin
          zeige:=TRUE;
          summation(zeige);
          exit;
        end { if }
       else
        begin
          gotoxy(62,24); write('Profil [L/G] : ');
          readln(art);
          art:=upcase(art);
          gotoxy(77,24); write(art,' ');
          einhuellende(art);
          LeaveGraphic;
        end { else };
    end { if }
   else LeaveGraphic;
end { end_grafik };


{----------------------------------------------------------------------}
{ Zeichnet die gefundenen HFS-Uebergangsfrequenzen auf den Bildschirm.  }
{----------------------------------------------------------------------}

procedure zeige_Spektrum_CRT;
label ende;
var  switcher : boolean;
begin { zeige_spektrum_crt }
  begin_grafik;
  { Zeichnen der E[n,m] auf dem Bildschirm }
  for n:=0 to maxxu do
  begin
    for m:=maxxo downto 0 do
    begin
      if (( fu[n]-fo[m] = 0) or (abs( fu[n] - fo[m]) = 1)) then
         begin
           if ( ( fu[n]=0) and (fo[m]=0) )  then goto ende;
           profanz:=profanz+1;

           {  HFS-Uebergang einzeichnen:    }
           x:=energie[m,n];

           {  Linien-Intensitaeten  }
           intensity:=intens(ju,jo,fu[n],fo[m],ikern)*skal_intensi;
           intensity:=intensity*grafik_skal;

           { Markierungen am oberen Rand setzen }
           DrawLine(x,850,x,870);

           { Linienschwerpunkt einzeichnen }
           DrawLine(x,205,x,205+intensity);
           switcher:=TRUE;  { Einzel-Linien suchen & einzeichnen }
           gotoxy(11,23);
           write('- Profil No. : ',profanz:2);
             case profil of
               'L' : lorentz_profil(x,intensity,switcher);
               'G' : gauss_profil(x,intensity,switcher);
             end { of case };
           ende:
         end { if };
    end { for };
  end { for };
  end_grafik;
end { zeige_spektrum_crt };

{===================    H a u p t p r o g r a m m    ==================}

begin { main }
  t:=40;
  test:=TRUE;
  werte_save:=TRUE;
  belegen;
  ladefacarr;  { Fakultaeten-Array belegen }
  parameter_load;
  profil_parameter_load;
  untergrund:=untergrund+205;
  intro;
  repeat
    { Summen initialisieren }
    for i:=1 to aufloesung do ysum[i]:=0;
    linien_anzahl:=0;
    parameter_eingeben;
    werte_speichern;
    clrscr;
    berechne_f;
    berechne_k;
    berechne_w;
    skal_intensity;
    energien_zuordnung;
    zeige_spektrum_CRT;
    if werte_save then save;
    write('Noch eine Zuordnung (J/N) ? ');
    readln(ch);
    ch:=upcase(ch);
  until ch='N';
  parameter_save;
  profil_parameter_save;
end { main }.

{====================   P r o g r a m m - E n d e    ==================}
