echo=off
cls
rem Plotter- & RS232-Initialisierung
rem rs232
rem HERCULES-Grafikkarte initialisieren
rem Ausdruck mit <Shift-Prnt-Scr-0>
rem HERCULES Drucker-Hardcopy installieren
hgc full hprint
echo Startupfile für SPEKTRUM
type spektrum.txt
pause
rem Programmstart
s
echo=on
