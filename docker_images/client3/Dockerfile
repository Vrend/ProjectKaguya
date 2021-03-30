FROM vulhub/samba:4.6.3
COPY smb.conf /usr/local/samba/etc/
RUN adduser --disabled-password --gecos "" kyle && echo "kyle:,!9Cc8/AZd-Zu_4=" | chpasswd
RUN mkdir /home/kyle/.irssi && mkdir /home/kyle/.irssi/logs
ADD 07-11-04-priv0.log /home/kyle/.irssi/logs/
RUN chown -R kyle:kyle /home/kyle/.irssi/
ENTRYPOINT smbd -FS && bash
