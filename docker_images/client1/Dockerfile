FROM kaguya_client_base
ENV DEBIAN_FRONTEND=noninteractive
RUN adduser --disabled-password --gecos "" paul && echo "paul:j431#354$fa" | chpasswd
COPY encrypt.py decrypt.py /home/paul/
RUN chmod +rx /home/paul/*.py
USER paul
WORKDIR /home/paul
ENTRYPOINT bash
