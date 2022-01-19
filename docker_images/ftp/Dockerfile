FROM ubuntu:18.04
RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install -y vsftpd
RUN adduser --disabled-password --gecos "" amanda && echo "amanda:4rfU2x1b" | chpasswd
RUN usermod --home /srv/ftp amanda && touch /srv/ftp/test.txt
RUN mkdir /var/run/vsftpd && mkdir /var/run/vsftpd/empty
COPY vsftpd.conf /etc/vsftpd.conf
COPY src/* /srv/ftp/
RUN chmod 644 /etc/vsftpd.conf
ENTRYPOINT vsftpd
