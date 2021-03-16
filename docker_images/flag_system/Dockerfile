FROM bitnami/minideb:stretch
RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install -y nano telnetd xinetd
RUN apt-get install -y ncurses-bin sudo
RUN adduser --disabled-password --gecos "" anonymous && chpasswd anonymous:a && passwd -d anonymous
ADD telnet /etc/xinetd.d/telnet
COPY scripts/* /wrkdr/
RUN chmod -R 774 /wrkdr/*
RUN mkdir /wrkdr/SHARED && chmod 777 /wrkdr/SHARED
RUN echo "trap '' 2\ncd /wrkdr\nclear\nbash ./main.sh\nexit" >> /home/anonymous/.profile
RUN usermod -aG sudo anonymous
WORKDIR /wrkdr
ENTRYPOINT service xinetd start && bash
