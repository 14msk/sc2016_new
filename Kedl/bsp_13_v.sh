#!/bin/bash
cd ~/blatt_3/Kurs-C

#Vergleichen von Dateien

for i in $( find */bsp_25_fkt.??? ); do
    FKT=${i} 
    FKT_VEC=${i%_fkt.*}vec_fkt.${i#*bsp_25_fkt.}
    FKT_VEC_ERBE=${i%_fkt.*}vecErbe_fkt.${i#*bsp_25_fkt.}
    EXT=_sdiff.txt

    sdiff -sWB ${FKT} ${FKT_VEC}          > ${FKT##*/}-${FKT_VEC##*/}${EXT}
    sdiff -sWB ${FKT} ${FKT_VEC_ERBE}     > ${FKT##*/}-${FKT_VEC_ERBE##*/}${EXT}
    sdiff -sWB ${FKT_VEC} ${FKT_VEC_ERBE} > ${FKT_VEC##*/}-${FKT_VEC_ERBE##*/}${EXT}

    meld ${FKT} ${FKT_VEC}
    meld ${FKT} ${FKT_VEC_ERBE}    
    meld ${FKT_VEC} ${FKT_VEC_ERBE}

done

cd ~
exit 0

