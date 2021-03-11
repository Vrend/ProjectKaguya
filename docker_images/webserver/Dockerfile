FROM ubuntu:18.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y
RUN apt-get install -y software-properties-common
RUN add-apt-repository ppa:ondrej/php
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y apache2 php5.6 php5.6-mysql mysql-server nano openssh-server
ADD init_db.sh /tmp/init_db.sh
RUN chmod +x /tmp/init_db.sh
RUN /tmp/init_db.sh
COPY index.php about.html upload.php customer_service.html style.css plane.jpg oops.jpeg /var/www/html/
RUN rm -f /var/www/html/index.html && echo "DirectoryIndex index.php" > /var/www/html/.htaccess
RUN mkdir /var/www/html/uploads && chmod 777 /var/www/html/uploads
ENTRYPOINT service apache2 start > /dev/null && service mysql start > /dev/null && bash
