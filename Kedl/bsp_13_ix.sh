#!/bin/bash

#Konvertieren von Zeichenketten in mehreren Files nacheinander

[ -z ${1} ] && WORK_DIR=~/sc2016/blatt_2 || WORK_DIR=${1}
cd ${WORK_DIR}
cp -rf ./bsp_8 ./bsp_8_copy

for i in $( find ./bsp_8_copy -type f -print ); do
INT="int"
LLINT="long long int"

#echo "# ${i} BEFORE SED ===========================================#"
#grep -En "long long int" ${i} 
sed "
s/${LLINT}/${INT}/g
" < ${i} > ${i}.tmp && mv ${i}.tmp ${i} 
#echo "# ${i} AFTER SED   ===========================================#"
#grep -En "long long int" ${i} 
done

cd ~
exit 0
