#!/bin/bash
#Automatisches Archivieren zu loeschender Dateien.

cd ~/blatt_3 || exit 1

FIND_CMD="find ./Kurs-C -type f -size +500k -print"
TAR_FILE="archive_$(date '+%Y%m%d_%H%M%S').tar"

#Archivieren aller Dateien groesser als 500kB in einem tar-File und anschliessendes Loeschen der Dateien
for i in $( ${FIND_CMD} ); do
    tar -rvf ${TAR_FILE} ${i} && rm -f ${i}
done

#Komprimieren des Archivs
gzip -v ${TAR_FILE}

cd ~
exit 0
