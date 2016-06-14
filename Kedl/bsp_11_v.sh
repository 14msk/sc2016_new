#!/bin/bash

cd ~/blatt_3
URL="http://imsc.uni-graz.at/haasegu/Lectures/SciComp/SS16/kurs.tar.gz"
TAR_FILE=kurs.tar.gz
curl -C - -# ${URL} -o ${TAR_FILE}

#Entpacen des Files
tar -xvzf ${TAR_FILE}

#Bestimmen wieviel Plattenplatz das neue Verzeichnis benoetigt
du -sh Kurs-C
#Bestimmen wieviel Plattenplatz die einzelnen Verzeichnisse darin benoetigen
find Kurs-C/* -type d -exec du -h {} \+
#Loeschen aller .doc,.s*,.o Files
find Kurs-C/* -type f \( -name *.doc -o -name *.s* -o -name *.o \) -exec rm {} \+

cd ~
exit 0
 
