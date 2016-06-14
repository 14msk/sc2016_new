#!/bin/bash

cd ~/blatt_3 || exit 1

SRC_DIR="Kurs-C"
TAR_FILE="archive_${SRC_DIR}.tar"

#Falls archive_Kurs-C.tar.gz vorhandes ist wird es entpackt
[ -f ${TAR_FILE}.gz ] && gunzip ${TAR_FILE}.gz
#Falls es archive_Kurs-C.tar nicht gibt wird das File angelegt
[ ! -f ${TAR_FILE} ] && tar -cvf ${TAR_FILE} --files-from /dev/null

#Hinzufügen von Dateien zu archive_Kurs-C.tar falls sie nicht schon darin enthalten sind
tar -uvf ${TAR_FILE} ./${SRC_DIR}

#Falls es archive_Kurs-C.tar gibt wird das File komprimiert
[ -f ${TAR_FILE} ] && gzip -v ${TAR_FILE}

cd ~
exit 0
