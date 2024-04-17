{  SDECLARE.INC

    Deklarationen zu SPEKTRUM.PAS

    (C) 1986  Institut fuer Angewandte Physik
              Universitaet Bonn

}


{-----------------------------------------}
{--------  Variablendeklarationen   ------}
{-----------------------------------------}

const   h       =  1;            {  Planck'sches Wirkungsquantum [Js] }
        anzahl  =  30;
        lmax    = 100;              {  Anzahl aller gefundenen Linien }

type    str8        = string[8];
        str12       = string[12];
        str15       = string[15];
        str80       = string[80];
        HFS_energie = array [1..anzahl,1..anzahl] of real;
        HFS_linie   = record
                        energy    : real;   { Linienschwerpunkt      }
                        fo        : real;   { Gesamtdrehimpuls oben  }
                        fu        : real;   { Gesamtdrehimpuls unten }
                        intensity : real;   { Linienamplitude        }
                        linewidth : real;   { Linienhalbwertsbreite  }
                      end;

var   au,ao,bu,bo          : real;        {  HFS-Konstanten            }
      untergrund           : real;        { siehe unten }
      FWHM                 : real;        {   "     "   }
      aufloesung           : integer;
      { Variablen - Untergrund :  Untergrundrate der Linien-Intensitaeten
                  - FWHM       :  Halbwertsbreite der Linie
                                  (Full-Width-Half-Maximum)
                  - Aufloesung :  Punktaufloesung der Lorentzlinie
        stehen in der Parameterdatei SPEKTRUM.PAR als letzte Eintraege.}

      ju,jo,ikern,j,max    : real;        {  Drehimpulse               }
      f,k                  : real;        {  Hilfsvariablen            }
      i,ii,ik,ij,t         : integer;     {  Hilfsvariablen            }
      intensity            : real;        {  Linien-Intensitaet         }
      maxxu                : integer;     {  max unterer Drehimp.wert  }
      maxxo                : integer;     {  max oberer Drehimpulswert }
      n,l,m                : integer;     {  Schleifenidices           }
      fu,fo,ku,ko          : array [0..15] of real; { Drehimpulsarrays }
      wu,wo                : array [0..15] of real; { Energiearrays    }
      ff,kk,ww             : array [0..15] of real; { Hilfsarrays      }
      antwort,ch           : char;        {  Steuervariable            }
      test                 : boolean;     {  Programmtestflag          }
      werte_save           : boolean;     {  Werteabspeicherflag       }
      nulltestok           : boolean;     {  Testflag ob Parameter I,  }
                                          {  Jo, Ju ungleich Null sind }
      x                    : real;        {  Energiewert-Abszisse      }
      energie              : HFS_energie; {  Energieverschiebung       }
      ent                  : integer;     {Anzahl von entarteten Linien}
      enten                : array [1..lmax] of real;{Entartungsenergie}
      entfo                : array [1..lmax] of real;{ Entartungs - fo }
      entfu                : array [1..lmax] of real;{ Entartungs - fu }
      linie                : array [1..lmax] of HFS_linie;
                                          {  HFS-Liniendaten           }
      energmin             : real;        {  Minimaler Energiewert     }
      energmax             : real;        {  Maximaler Energiewert     }
      element              : str15;       {  nach Periodensystem       }
      vonzustand           : str15;       {  Zustand von ...           }
      nachzustand          : str15;       {  ... nach Zustand          }
      spekname             : str12;       {  Dateiname des Spektrums   }
      profildatei          : str12;       {  Dateiname Profilparameter }
      datnam               : str8;        {  Hilsvariable              }
      datname              : str12;       {  Dateiname der berechneten }
                                          {  Werte: Fu, Fo, Wu, Wo, E  }
      filvar               : text;        {  File-variable             }
      linien_anzahl        : integer;     {  Linienanzahl im Spektrum  }
      defaultelement       : str15;       {  Element                   }
      defaultvon           : str15;       {  Zustand von ...           }
      defaultnach          : str15;       {  ... nach Zustand          }
      kom                  : str80;       {  Hilfsvariable             }
      kommentar            : str80;       {  Kommentarzeile            }
      pardatei             : str12;       {  Parameterdateiname        }
      meldung_param        : str80;       {  Fehlermeldung             }


