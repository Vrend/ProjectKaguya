#!/bin/bash

[ "root" != "$USER" ] && exec sudo $0 "$@"

function delay_echo() {
  while read line; do
    echo "  $line"
    sleep 0.25
  done < $1
}

function handle_flag() {
  clear
  case $1 in
    d3@dM3nT3llN0t@1ls)
      touch "SHARED/FINISHED"
      source ./finale.sh
      exit
      ;;
    g3tt1ngSt@rt3d)
      echo " "
      delay_echo "greetings2.txt"
      echo " "
      ;;
    *)
      echo " "
      echo " That's not a valid flag, Agent. Don't waste our time."
      echo " "
  esac
}

function main_prompt() {
  while true; do
    clear
    echo " "
    echo -n " Enter Flag> "
    read flag
    handle_flag $flag
    echo -n " Press q to quit, or any other key to continue."
    read -rsn 1 k
    if [[ $k = q ]]; then
      echo " "
      return
    fi
  done
}

if [[ -e "SHARED/FINISHED" ]]
then
  source ./finale.sh
elif [[ -e "SHARED/STARTED" ]]
then
  main_prompt
else
  source ./greetings.sh
  touch "SHARED/STARTED"
  main_prompt
fi;
