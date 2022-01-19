#!/bin/bash

[ "root" != "$USER" ] && exec sudo $0 "$@"

cd $(dirname $0)

# Build docker images
source ./build_images.sh

# Cleanup anything prior
cd ../VM_files
source ./cleanup.sh

cd ../docker_images
cd client1 && make run
cd ..
cd client2 && make run
cd ..
cd client3 && make run
cd ..
cd flag_system && make run
cd ..
cd ftp && make run
cd ..
cd irc && make run
cd ..
cd target && make run
cd ..
cd webserver && make run
cd ..
cd .. # Now at root directory

cd VM_files
source share_docker_ip.sh
