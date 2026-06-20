FROM httpd:latest

COPY httpd.conf /usr/local/apache2/conf/httpd.conf

# Install c++ compiler and other necessary tools
RUN apt-get update && apt-get install -y build-essential && apt-get install -y libmariadb-dev
