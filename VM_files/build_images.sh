#!/bin/bash

[ "root" != "$USER" ] && exec sudo $0 "$@"

cd ../docker_images
cd client_base && make build
cd ..
cd client1 && make build
cd ..
cd client2 && make build
cd ..
cd client3 && make build
cd ..
cd flag_system && make build
cd ..
cd ftp && make build
cd ..
cd irc && make build
cd ..
cd target && make build
cd ..
cd webserver && make build
cd ..
