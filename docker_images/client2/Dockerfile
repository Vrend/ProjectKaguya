FROM vulhub/libssh:0.8.1
ENV DEBIAN_FRONTEND=noninteractive
RUN adduser --disabled-password --gecos "" amanda && echo "amanda:M=Uy[rgZ8vG,UQ5y" | chpasswd
RUN mkdir /home/amanda/.irssi && mkdir /home/amanda/.irssi/logs
ADD 07-14-04-priv0.log 07-14-04-priv1.log /home/amanda/.irssi/logs/
RUN chown -R amanda:amanda /home/amanda/.irssi/
ADD hint.txt /
ENTRYPOINT /usr/src/build/examples/ssh_server_fork --hostkey=/etc/ssh/ssh_host_rsa_key --ecdsakey=/etc/ssh/ssh_host_ecdsa_key --dsakey=/etc/ssh/ssh_host_dsa_key --rsakey=/etc/ssh/ssh_host_rsa_key -p 22 0.0.0.0
