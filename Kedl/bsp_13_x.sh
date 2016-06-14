#!/bin/bash
cd ~

#Umbezeichnung    von    Files mmddyy.gif   yyyy_mm_dd.gif

TODAY=$(date '+%Y%m%d')

for i in 0 1 2 3 4 5 6 7 8 9; do
DAY=$(printf "%02d\n" $(echo $(($RANDOM % 28))+1|bc))
MON=$(printf "%02d\n" $(echo $(($RANDOM % 12))+1|bc))
YER=$(printf "%02d\n" $(echo $(($RANDOM % 99))|bc))
touch ${MON}${DAY}${YER}.gif
done

for i in $( ls -1 [01][0123456789][0123][0123456789][0123456789][0123456789].gif ); do
MON=${i%????.gif}
DAY=${i%??.gif}
DAY=${DAY#??}
YER=${i%.gif}
YER=${YER#????}


[ ${TODAY} -gt 20${YER}${MON}${DAY} ] &&  FNAME=20${YER}_${MON}_${DAY}.gif || FNAME=19${YER}_${MON}_${DAY}.gif
#set -x 
mv  ${i} ${FNAME}
#set +x
done

cd ~
exit 0
