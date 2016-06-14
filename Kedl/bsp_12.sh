#!/bin/bash
cd ~/blatt_3/Kurs-C/Script/latex


echo "i
"
#Finden aller tex-Files in denen "Alternative" vorkommt
grep "Alternative" *.tex
#Finden aller tex-Files die "Lauf" oder "lauf" enthalten
fgrep -ni "lauf" *.tex
grep -n "[lL]auf" *.tex

echo "ii und iii
"
#Ersetzen von "Funktion" durch "function" im gesamten File p_7.tex, sowie Entfernen aller Kommentarzeilen
#Speichern des Resultats in t_7.tex 
sed '
s/\(Funktion\)\([^a-zA-Z0-9]\)/function\2/g
s/Funktion$/function/
s/[ \t]*%.*//
' <p_7.tex >t_7.tex

#Vergleichen der beiden Files
sdiff -s p_7.tex t_7.tex | less

echo "iv
"
#Alle benutzen Graphikfiles .eps und .eps.gz finden
grep -E '\.eps|\.eps.gz' p_7.tex | awk -F'=' '{print $2}'

cd ~ 
exit 0
