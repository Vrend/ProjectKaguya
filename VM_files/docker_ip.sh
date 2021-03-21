#!/bin/bash

FLAG=$(docker container inspect -f '{{ .NetworkSettings.Networks.wan.IPAddress }}' kaguya_flag)

echo "The IP of your starting system is: ${FLAG}"
