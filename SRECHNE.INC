{  SRECHNE.INC

    berechnet alle noetigen Werte
    fuer das HFS-Spektrum :

    (C) 1986  Institut fuer Angewandte Physik
              Universitaet Bonn

}


{-----------------------------------------}
{-------  Berechnen der F-Werte:  --------}
{----   F = I + J , ... , abs(I - J)   ---}
{-----------------------------------------}

procedure berechne_f;
begin
  tabs(t);
  { Berechnung fuer den unteren Zustand }
  j:=ju;
  if j>=ikern then max:=ikern
  else max:=j;
  maxxu:=trunc(2*max+1+0.1);     { Integerzahl aus Drehimpuls machen }
  maxxu:=maxxu-1;                { und sicher gehen, das nicht       }
  for n:=0 to maxxu do           { abgerundet wird                   }
  begin
    fu[n] := ikern + j - n;
    if test then WRITELN('Fu(',n,') = ',FU[N]:10:1);
  end;
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
  end;
end;

{-----------------------------------------}
{------  Berechnen der K-Werte:  ---------}
{----  K = F(F+1) - I(I+1) - J(J+1)  -----}
{----        ( Casimir )             -----}
{-----------------------------------------}

procedure berechne_k;
begin
  tabs(t);
  { Berechnung fuer den unteren Zustand }
  for n:=0 to maxxu do
  begin
    j:=ju;
    f:=fu[n];
    ku[n]:=f*(f+1)-ikern*(ikern+1)-j*(j+1);
    if test then writeln('Ku(',n,') = ',ku[n]:10:1);
  end;
  tabs(t);
  { Berechnung fÅr den oberen Zustand }
  for n:=0 to maxxo do
  begin
    j:=jo;
    f:=fo[n];
    ko[n]:=f*(f+1)-ikern*(ikern+1)-j*(j+1);
    if test then writeln('Ko(',n,') = ',ko[n]:10:1);
  end;
end;


{--------------------  Berechnen der W-Werte:  ------------------------}
{   W = 1/2h ( K*A + (3/4 K(K+1)-I(I+1)J(J+1))*B/(I(2I-1)J(2J-1)) )    }
{                Energiewerte W in [MHz] - Einheiten                   }
{                h  =    Planck'sches Wirkungsquantum                  }
{----------------------------------------------------------------------}
procedure berechne_w;

  function w_zahl(var a,b,k,i,j : real):real;
  var  sum1,zaehler,nenner,wzahl : real;
  begin
    sum1:=k*a*0.5;
    zaehler:=i*(i+1)*j*(j+1);
    zaehler:=0.75*k*(k+1)-zaehler;
    if b=0
      then nenner:=1
      else nenner:=2*i*(2*i-1)*j*(2*j-1);
    wzahl:=zaehler*b/nenner;
    w_zahl:=(sum1+wzahl)*h;
  end;

begin
  tabs(t);
  { Berechnung fuer den unteren Zustand  }
  for m:=0 to maxxu do
  begin
    f:=fu[m];
    k:=ku[m];
    wu[m]:=w_zahl(au,bu,k,ikern,ju);
   if test then writeln('Wu(',m,') = ',wu[m]:15:6);
  end;
  tabs(t);
  { Berechnung fuer den oberen Zustand  }
  for m:=0 to maxxo do
  begin
    f:=fo[m];
    k:=ko[m];
    wo[m]:=w_zahl(ao,bo,k,ikern,jo);
    if test then writeln('Wo(',m,') = ',wo[m]:15:6);
  end;
end;

{------------------------------------------------}
{-------  Berechnet alle noetigen Werte  --------}
{------------------------------------------------}

procedure rechne;
begin
  berechne_f;
  berechne_k;
  berechne_w;
end;
