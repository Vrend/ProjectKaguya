docker network rm lan
docker network rm wan
docker network create --driver=bridge --subnet=192.168.2.0/24 --gateway=192.168.2.1 lan
docker network create -d macvlan --subnet 192.168.1.0/24 --gateway 192.168.1.1 --ip-range 192.168.1.192/27 -o parent=enp0s3 wan
