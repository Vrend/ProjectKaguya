#!/bin/bash

function delay_echo() {
  while read line; do
    echo "  $line"
    sleep 0.25
  done < $1
}

function main_prompt() {
  while true; do
    clear
    echo -n "Enter Flag> "
    read flag
    echo "Your flag is: $flag"
    echo -n "Press q to quit, or any other key to continue."
    read -rsn 1 k
    if [[ $k = q ]]; then
      echo " "
      return
    fi
  done
}

if [[ -e "SHARED/STARTED" ]]
then
  main_prompt
else
  source ./greetings.sh
  touch "SHARED/STARTED"
  main_prompt
fi;
