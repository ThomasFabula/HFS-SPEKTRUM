{  SPROFIL.INC      (C) 1986  T. Fabula
                    Institut fuer Angewandte Physik
                    Universitaet Bonn   }

{  Die Variablen

      -  Untergrund :  Untergrundrate der Linien-Intensitaeten
      -  FWHM       :  Halbwertsbreite der Linie
                       (Full-Width-Half-Maximum)

   stehen in der Parameterdatei SPEKTRUM.PAR als letzte Eintraege.
}

var  untergrund  : real;
     FWHM        : real;

{------------------------------}
{-----   Lorentzprofil   ------}
{------------------------------}

function lorentz(var energie,e_0,intensy : real) : real;
var zaehler,nenner : real;
begin
  zaehler:=sqr(FWHM);
  nenner:=sqr(energie - e_0);
  nenner:=nenner+0.25*zaehler;
  if (nenner=0) then
    begin
      writeln(#7,#7,#7);
      writeln('Lorentz: Division durch Null');
      halt;
    end;
  lorentz:=intensy*zaehler/nenner;
end;

{----------------------------}
{-----   Gaussprofil   ------}
{----------------------------}

function gauss(var energie,e_0,intensy : real) : real;
var argum : real;
begin
  argum:=(energie-e_0);
  if (FWHM=0) then
    begin
      writeln(#7,#7,#7);
      writeln('Gauss:  FWHM = Null');
      halt;
    end;
  argum:=sqr(argum/FWHM);
  gauss:=intensy*exp(-argum);
end;
