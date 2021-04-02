#!/bin/bash

docker kill $(docker ps -q)
rm ../docker_images/flag_system/SHARED/STARTED
rm ../docker_images/flag_system/SHARED/FINISHED
rm ../docker_images/flag_system/SHARED/IPFILE
