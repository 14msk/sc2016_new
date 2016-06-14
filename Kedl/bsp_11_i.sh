#!/bin/bash

#Anlegen eines Verzeichnisses mit zwei Unterverzeichnissen und Anlegen von .cpp und .hpp Dateien in diesen:

cd ~
pwd

for i in 1 2; do
    mkdir -p ./blatt_3/sub_${i}
    for j in a b c; do
	for k in c h; do
	    touch ./blatt_3/sub_${i}/file_${i}${j}.${k}pp
	done
    done
done

#Anzeigen der .cpp-files in einem Unterverzeichnis 
ls -l ./blatt_3/sub_1/*.cpp
cd ~

#Änderung der Zugriffsrechte, so dass nur der user darauf lesend zugreifen kann
chmod -R go-r ./blatt_3

cd ~
exit 0

