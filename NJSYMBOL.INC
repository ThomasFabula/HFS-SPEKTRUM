
(* Datei   : NJSYMBOL.INC                                      *)

(* Programm: Include-Datei zur Berechnung von 3j, 6j und 9j-   *)
(*           Symbolen                                          *)
(* Autor   : Thomas Brenner, IAP Bonn                          *)
(* Datum   : 9.3.1987                                          *)


const   maxfac   = 100;
type    wurm     = array[0..maxfac] of real;
var     facarr   : wurm;


function min1hocha(x:real):real;
begin
  min1hocha:=1-2*(round(x) and 1);
end;


procedure ladefacarr;
var i     :integer;
begin
  facarr[0]:=0;
  for i:=1 to maxfac do facarr[i]:=facarr[i-1]+ln(i)
end;


function lnfac(x:real):real;
begin
  if frac(x)<>0 then writeln('Argument von FAC nicht ganzzahlig ! ',x);
  if x<0 then writeln('Argument von FAC ist < 0   ! ',x);
  if x> maxfac then writeln(' zu gross ! ',x);
  lnfac:=facarr[round(x)];
end;


function clebsch(j1,j2,j,m1,m2,m:real;kmin,kmax:integer):real;
var   lnvorfaktor,sum         :real;
      k                       :integer;

begin
  lnvorfaktor:=0.5*(
  lnfac(2*j+1)
              +lnfac(j1+j2-j)
              +lnfac(j1-j2+j)
              +lnfac(-j1+j2+j)
              +lnfac(j1+m1)
              +lnfac(j1-m1)
              +lnfac(j2+m2)
              +lnfac(j2-m2)
              +lnfac(j+m)
              +lnfac(j-m)
              -lnfac(j1+j2+j+1) );
   sum:=0;
   for k:=kmin to kmax do
   begin
     sum:=sum +min1hocha(k)*
                            exp(  lnvorfaktor
                            -lnfac(k)
                            -lnfac(j1+j2-j-k)
                            -lnfac(j1-m1-k)
                            -lnfac(j2+m2-k)
                            -lnfac(j-j2+m1+k)
                            -lnfac(j-j1-m2+k) )
    end;
    clebsch:=sum;
 end;


function dreij(j1,j2,j3,m1,m2,m3:real):real;
var kmin,kmax   : integer;
    j,m,k1,kv              :real;
begin
  m:=-m3;
  j:=j3;
  if round(m1+m2+m3)=0 then
  begin
    k1:=j1+j2-j;
    kv  :=j1-m1;
    if kv<k1 then k1:=kv;
    kv  :=j2+m2;
    if kv<k1 then k1:=kv;
    kmax:=round(k1);
    k1:=0;
    kv  :=j-j2+m1;
    if kv<k1 then k1:=kv;
    kv  :=j-j1-m2;
    if kv<k1 then k1:=kv;
    kmin:=-round(k1);
    if kmin<=kmax
      then
           dreij:=min1hocha(j1-j2-m3)
           /sqrt(2*j3+1)
           *clebsch(j1,j2,j,m1,m2,m,kmin,kmax)
      else
           dreij:=0;
     end
   else    dreij:=0
end;


function lndeltasq(A,B,C:real):real;
begin
  lndeltasq:=lnfac(A+B-C)+lnfac(A-B+C)+lnfac(-A+B+C)-lnfac(A+B+C+1);
end;


function kmax6j(j1,j2,j3,l1,l2,l3:real):integer;
var kv,k1 : real;
begin
  k1:=j1+j2+l1+l2+1;
  kv:=j1+j2-j3;
  if kv<k1 then k1:=kv;
  kv:=l1+l2-j3;
  if kv<k1 then k1:=kv;
  kv:=j1+l2-l3;
  if kv<k1 then k1:=kv;
  kv:=l1+j2-l3;
  if kv<k1 then k1:=kv;
  kmax6j:=round(k1);
end;


function kmin6j(j1,j2,j3,l1,l2,l3:real):integer;
var  kv,k2  : real;
begin
  k2:=0;
  kv:=-j2-l2+j3+l3;
  if kv<k2 then k2:=kv;
  kv:=-j1-l1+j3+l3;
  if kv<k2 then k2:=kv;
  kmin6j:=-round(k2);
end;


function sum6j(j1,j2,j3,l1,l2,l3,lnvorf:real;kmin,kmax:integer):real;
var  k   : integer;
     sum : real;

begin
  sum:=0;
  for k:=kmin to kmax do
  begin
    sum:=sum+
    min1hocha(k)*
    exp(
    lnvorf+
    lnfac(j1+j2+l1+l2+1-k)-
    (    lnfac(k)
    +lnfac(j1+j2-j3-k)
    +lnfac(l1+l2-j3-k)
    +lnfac(j1+l2-l3-k)
    +lnfac(l1+j2-l3-k)
    +lnfac(-j1-l1+j3+l3+k)
    +lnfac(-j2-l2+j3+l3+k) ) );
  end;
  sum6j:=sum;
end;


function sechsJ(j1,j2,j3,l1,l2,l3:real):real;
var kmin,kmax    : integer;
    lnvorfaktor  : real;

begin
  kmin:=kmin6j(j1,j2,j3,l1,l2,l3);
  kmax:=kmax6j(j1,j2,j3,l1,l2,l3);
  if kmax<kmin
    then sechsJ:=0
    else
      begin
        lnvorfaktor:=0.5* (
        lndeltasq(j1,j2,j3)+
        lndeltasq(l1,l2,j3)+
        lndeltasq(l1,j2,l3)+
        lndeltasq(j1,l2,l3));
        sechsj:=min1hocha(j1+j2+l1+l2)*
        sum6j(j1,j2,j3,l1,l2,l3,lnvorfaktor,kmin,kmax);
      end;
end;


function neunj(j1,j2,j12,j3,j4,j34,j13,j24,tau:real):real;
var   t,tmin,tmax,tv,neunjv    :real;
      imax,i       :integer;

begin
  tmax:=j1+tau;
  tv  :=j3+j24;
  if tv<tmax then tmax:=tv;
  tv  :=j2+j34;
  if tv<tmax then tmax:=tv;
  tmin:=abs(j1-tau);
  tv  :=abs(j3-j24);
  if tv>tmin then tmin:=tv;
  tv  :=abs(j2-j34);
  if tv>tmin then tmin:=tv;
  neunj:=0;
  neunjv:=0;
  if tmax>=tmin
    then
      begin
        imax:=round(tmax-tmin);
        for i:=0 to imax do
        begin
          t:=tmin+i;
          neunjv:=neunjv+min1hocha(2*t)*(2*t+1)
                  *sechsj(j1,j2,j12,j34,tau,t)
                  *sechsj(j3,j4,j34,j2,t,j24)
                  *sechsj(j13,j24,tau,t,j1,j3)
        end;
        neunj:=neunjv;
      end;
end;

(* ------------------------------------------------------------ *)
