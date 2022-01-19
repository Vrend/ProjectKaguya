# Project Kaguya
A CTF for beginners

The name (and the CTF itself) is a homage to the game Hacknet, more specifically the Labyrinths DLC

## Dependencies

A virtual machine with the following:
- docker
- SystemD (for the service files)
- ASLR turned OFF (kernel.randomize.va_space=0)
- GCC and Make
- A promiscuous network interface

## How to Use

Assuming that your VM has all dependencies satisfied, run start_CTF.sh
in the VM_files folder.

It may take a few minutes for all of the docker images to start running,
and it will take a lot longer if you have not built the images yet.

First thing you need to do is get the IP of your VM. If you name your VM
'Project Kaguya', you can use the provided shell file to get the VM IP.

Then, run netcat on port 4444 of your VM, which will tell you the IP
of your flag system.

Telnet to the flag system, with user 'anonymous'

You can cleanup / reset everything by using the 'cleanup.sh' script

## A note about networks

By default, the images assume that the internal LAN has the subnet 192.168.2.0/24, and an external LAN of 192.168.1.0/24
This means, that if your external LAN isn't using 192.168.1.0/24, you need to update the 'create_docker_networks.sh' file. Also,
if you're using 192.168.2.0/24, be sure to change both docker networks to reflect this change. I don't believe any of the images have
their interfaces hardcoded in terms of their subnets, but I'm not sure.

## VM Image

I have a virtualbox image prepared that can be imported. All that needs to be configured are the docker networks, but be sure to pull the repository beforehand.

The VM can be found here: https://mega.nz/file/iEYzFC7A#wRD-t1exKVeqOEQ3RwtlcFdzawh22y0jbYWrn8659Ds

The credentials for the VM are: ```kaguya:by any means necessary```
