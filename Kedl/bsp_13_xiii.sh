#!/bin/bash

WORKDIR=~/sc2016/blatt_2/jacobi_13_xiii/matrix/bin
cd ${WORKDIR}
LOGFILE=jacobi_out_${$}_$(date '+%Y%m%d_%H%M%S').txt

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13; do
    echo "Genauigkeit: 10e-${i}
    "
    ./matrix 10e-${i}
done | awk '
  BEGIN {
    ;
  }
  
  /Toleranz/
  /Genauigkeit/ {
    txt=$0;
  }

  /Iterationen/ {
    printf ( "%-20s %s\n", txt, $0 );
    txt="";
  }

  {
    ;
  }

  END {
    ;
  }
' > ${LOGFILE}

cat ${LOGFILE} | awk '{print $2 " " $6}' | gnuplot -p -e "set xrange[0:1];  plot  '<cat' with lines"


cd ~
exit 0
