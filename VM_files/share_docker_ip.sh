#!/bin/bash
touch ../docker_images/flag_system/SHARED/IPFILE

IP1=$(docker container inspect -f '{{ .NetworkSettings.Networks.wan.IPAddress }}' kaguya_target)
IP2=$(ip addr show dev enp0s3 | grep -o "inet [0-9]*\.[0-9]*\.[0-9]*\.[0-9]*" | grep -o "[0-9]*\.[0-9]*\.[0-9]*\.[0-9]*")
TOGETHER=$(printf '%s\n%s' "$IP1" "$IP2")
echo "$TOGETHER" > ../docker_images/flag_system/SHARED/IPFILE
