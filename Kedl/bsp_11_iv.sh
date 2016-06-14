#!/bin/bash
#Sortieren von Dateien bei Ausgabe

cd ~/blatt_3/sub_1
echo '//1234567890987654321' > file_1b.hpp
echo '//1' > file_1c.cpp

echo "nach Dateigroesse"
ls -Sl
echo "nach Dateiname"
ls -1
echo "nach Zeitstempel"
ls -tl
echo "nach Zeitstempel umgekehrt"
ls -tlr

echo -n > file_1b.hpp
echo -n > file_1c.cpp

cd ~/
exit 0
