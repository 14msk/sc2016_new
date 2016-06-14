#!/bin/bash

cd ~
#Alle Files eines Verzeichnisbaums anzeigen und Speichern des Outputs in einer Datei
find ~/blatt_3 -type f -print > ~/blatt_3/bsp_11ii_out.txt
#Anzeigen der Files des Verzeichnisbaumes mit Endung .hpp
find ~/blatt_3 -type f -name \*.hpp
#Bei allen Files des Verzeichnisbaumes den Zeitstempel auf die aktuelle Zeit setzen 
find ~/blatt_3 -type f -name \*.cpp -exec touch {} \+

cd ~
exit 0
