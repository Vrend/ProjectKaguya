FROM ubuntu:18.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y
RUN apt-get install -y software-properties-common
RUN add-apt-repository ppa:ondrej/php
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y apache2 php5.6 php5.6-mysql mysql-server
ADD init_db.sh /tmp/init_db.sh
RUN chmod +x /tmp/init_db.sh
RUN /tmp/init_db.sh
ADD index.php /var/www/html/index.php
ADD about.html /var/www/html/about.html
ADD upload.php /var/www/html/upload.php
ADD style.css /var/www/html/style.css
ENTRYPOINT service apache2 start > /dev/null && service mysql start > /dev/null && bash
