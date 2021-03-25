FROM kaguya_client_base
ENV DEBIAN_FRONTEND=noninteractive
RUN adduser --disabled-password --gecos "" paul && echo "paul:j431#354$fa" | chpasswd
COPY encrypt.py decrypt.py /home/paul/
RUN chmod +rx /home/paul/*.py
RUN mkdir /home/paul/notes
COPY note1 note2 note3 /home/paul/notes/
RUN chown -R paul:paul /home/paul/notes/
RUN python3 /home/paul/encrypt.py /home/paul/notes/note1 7 4 && python3 /home/paul/encrypt.py /home/paul/notes/note2 7 4 && rm /home/paul/notes/note1 /home/paul/notes/note2
USER paul
WORKDIR /home/paul
ENTRYPOINT bash
