FROM bitnami/minideb:stretch
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install -y openssh-server gcc make gdb gcc-multilib
ADD src/main.c src/main.h src/Makefile /program/
RUN cd /program/ && make
ENTRYPOINT setarch linux32 -R /program/main
