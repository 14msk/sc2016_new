#!/bin/bash
cd ~/blatt_3/Kurs-C

#Bestimmung des gesamten verfuegbaren Festplattenplatzes

df -h --total | awk '
BEGIN {
;
}

/Filesystem/ {
  printf ("%-25s %s\n", "-------------------------", $4);
}

/total/ {
  printf ("%-25s %s\n", "available disk space", $4);
}

{
  ;
}

END {
;
}
'


cd ~
exit 0
