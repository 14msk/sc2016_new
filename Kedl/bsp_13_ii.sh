#!/bin/bash

#Finden  aller  Dateien,  welche  groesser  als  500kB  sind  und  seit  mehr  als  3  Monaten  nicht benutzt wurden
cd ~blatt_3/Kurs-C
ls -1R > bsp_13ii_out.txt
grep -E '\.[ch]pp' bsp_13ii_out.txt

cd ~
exit 0

