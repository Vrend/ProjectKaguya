FROM kaguya_client_base
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get install -y postgresql
RUN apt-get install -y sudo nano
RUN adduser --disabled-password --gecos "" paul && echo 'paul:j431#354$fa' | chpasswd
COPY encrypt.py decrypt.py pw_reminder.txt /home/paul/
RUN chmod +rx /home/paul/*.py && chmod +r /home/paul/pw_reminder.txt
RUN mkdir /home/paul/notes
COPY note1 note2 note3 /home/paul/notes/
RUN chown -R paul:paul /home/paul/notes/ && chmod +r /home/paul/notes/*
RUN python3 /home/paul/encrypt.py /home/paul/notes/note1 7 4 && python3 /home/paul/encrypt.py /home/paul/notes/note2 7 4 && rm /home/paul/notes/note1 /home/paul/notes/note2
RUN sed -i "s/#listen_addresses = 'localhost'/listen_addresses = '*'/g" /etc/postgresql/12/main/postgresql.conf
RUN sed -i "s/127.0.0.1\/32/all/g" /etc/postgresql/12/main/pg_hba.conf
RUN sed -i "s/md5/trust/g" /etc/postgresql/12/main/pg_hba.conf
RUN sed -i "s/#ListenAddress 0.0.0.0/ListenAddress 0.0.0.0/g" /etc/ssh/sshd_config
ENTRYPOINT service postgresql start && service ssh start && bash
