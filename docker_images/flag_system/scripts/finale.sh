#!/bin/bash

function delay_echo() {
  while read line; do
    echo "  $line"
    sleep 0.25
  done < $1
}

clear
echo " "
delay_echo "finale.txt"
echo " "
echo "  Press any key to continue."
read -rsn 1 dummy
