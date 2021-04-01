FROM bitnami/minideb:stretch
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install -y openssh-server gcc make gdb gcc-multilib
ADD src/main.c src/main.h src/Makefile run.sh /program/
RUN echo "d3@dM3nT3llN0t@1ls" > /program/flag.txt && chmod 700 /program/flag.txt && chmod 700 /program/run.sh
RUN cd /program/ && make
RUN adduser --disabled-password --gecos "" fmoperator && echo 'fmoperator:O@%8xQ$Rv3xOLhhRbSgkq32sEJivWL' | chpasswd
RUN chmod -R 774 /var/log/ && chmod +x /var/log/
ENTRYPOINT service ssh start && /program/run.sh
