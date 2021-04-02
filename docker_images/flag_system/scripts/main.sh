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
      source ./greetings2.sh
      ;;
    cUst0m3rS3rv1c34321413)
      echo " "
      delay_echo "customer_service.txt";
      echo " "
      ;;
    0ut0fTh3Fry1ngP@n1nt0Th3F1r3)
      echo " "
      delay_echo "frying_pan.txt";
      echo " "
      ;;
    sTr@ng3-p1@nz-1nD33d5123413)
      echo " "
      delay_echo "strange_plans.txt";
      echo " "
      ;;
    *)
      echo " "
      echo " That's not a valid flag, Agent. Don't waste our time."
      echo " "
      ;;
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
