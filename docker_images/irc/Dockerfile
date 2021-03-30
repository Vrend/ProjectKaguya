FROM ubuntu:14.04
RUN apt-get -y update && apt-get -y install automake build-essential git libssl-dev wget
RUN wget http://stalkr.net/files/unrealircd/Unreal3.2.8.1_backdoor.tar.gz
RUN tar xzf Unreal3.2.8.1_backdoor.tar.gz
WORKDIR /Unreal3.2
RUN sed -i 's/inline void parse_addlag/void parse_addlag/' src/parse.c
RUN ./Config -quick && make
COPY unrealircd.conf /Unreal3.2/
RUN echo "Work Hard!" > /Unreal3.2/ircd.motd.fr && echo "1. Work Hard\n2. You're here forever :)" > /Unreal3.2/ircd.rules.fr
COPY ircd.log /var/log/
ENTRYPOINT ./unreal start && bash
