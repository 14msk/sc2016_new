#!/bin/bash

cd ~
#find ~/blatt_3/Kurs-C -type f -size +500k -mtime +70 -ls
find ~/blatt_3/Kurs-C -type f -size +500k -atime +90 -ls

exit 0
