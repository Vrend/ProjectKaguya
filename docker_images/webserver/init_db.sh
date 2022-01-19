#!/bin/bash

export DEBIAN_FRONTEND=noninteractive
service apache2 start
service mysql start

mysql -e "CREATE DATABASE site"
mysql site -e "CREATE TABLE site(id int primary key, content varchar(1000) DEFAULT NULL)"
mysql site -e "INSERT INTO site VALUES (1, 'This is my first Post! I\'m really proud of it!');"
mysql site -e "INSERT INTO site VALUES (2, 'Here at Boeing, we are always trying to innovate. To that end, we are adding an upload page so that our customers can post themselves next to our planes.');"
mysqladmin -u root password Tot@llyS3cUr3P@ssword!
mysql mysql -e "alter user 'root'@'localhost' identified with 'mysql_native_password' by 'Tot@llyS3cUr3P@ssword!'"
echo "secure_file_priv=\"\"" >> /etc/mysql/mysql.conf.d/mysqld.cnf
