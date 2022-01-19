#!/bin/bash

function delay_echo() {
  while read line; do
    echo "  $line"
    sleep 0.25
  done < $1
}

clear
IFS=
RAW_STR=$(< greetings2.txt)
IP1=$(sed -n '1p' SHARED/IPFILE)
IP2=$(sed -n '2p' SHARED/IPFILE)
STR=${RAW_STR/IPOFMAINSYSTEM/$IP1}
STR=${STR/IPOFROUTER/$IP2}
echo $STR > tmp.txt
echo " "
delay_echo 'tmp.txt'
rm tmp.txt
echo " "
