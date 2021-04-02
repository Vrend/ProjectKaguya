#!/bin/bash

function delay_echo() {
  while read line; do
    echo "  $line"
    sleep 0.25
  done < $1
}

clear
echo " "
delay_echo "greetings.txt"
echo " "
echo " Press any key to accept or CTRL^C to Decline."
read -rsn 1 dummy
clear
echo " "
echo " Your first flag is: g3tt1ngSt@rt3d"
echo " "
echo " Press any key to continue."
read -rsn 1 dummy
