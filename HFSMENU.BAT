echo off
:start
cls
echo                         Bitte wÑhlen Sie:
echo                         ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
echo.
echo               Hyperfeinstruktur-Auswerteprogramme
echo.
echo.
echo.
echo         1 - HFSFIT      Berechnung von A-,B-Faktoren
echo.
echo         2 - HFSSPEK     Spektrum ohne gerad. Isotope
echo.
echo         3 - SPEKTRUM    Spektrum mit gerad. Isotopen
echo.
echo         4 - ASPEKTRUM   mit Dateitransfer zu AutoCAD
echo.
echo         5 - ISOTOPIE    Spektrum ohne gerad. Isotope
echo.
echo.
echo.
echo         (Ctrl-C = Programmabbruch & zurÅck nach DOS)
echo.
rem Tastaturpuffer abfragen
taste
if errorlevel 54 goto start
if errorlevel 53 goto funf
if errorlevel 52 goto vier
if errorlevel 51 goto drei
if errorlevel 50 goto zwei
if errorlevel 49 goto eins
goto start
:eins
rem  Funktion 1 ist ausgewÑhlt
hf.bat
goto ende
:zwei
rem  Funktion 2 ist ausgewÑhlt
hspek.bat
goto ende
:drei
rem  Funktion 3 ist ausgewÑhlt
spek.bat
goto ende
:vier
rem  Funktion 4 ist ausgewÑhlt
sac.bat
:funf
rem  Funktion 5 ist ausgewÑhlt
iso.bat
:ende
echo.
echo Programmende
