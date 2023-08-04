FROM rocker/shiny:3.5.1

RUN apt-get update && apt-get install libcurl4-openssl-dev libv8-3.14-dev -y &&\
  mkdir -p /var/lib/shiny-server/bookmarks/shiny 

RUN apt-get install -y default-libmysqlclient-dev 


RUN apt-get install -y libssl-dev 


RUN sudo apt-get install -y libjpeg-dev


RUN apt-get install -y mysql-server


# Download and install library

RUN sudo apt-get install -y libcurl4-gnutls-dev

RUN R -e "install.packages(c('ggmap' , 'readxl', 'magrittr', 'shinyalert','leaflet', 'Hmisc', 'lubridate', 'gridExtra','shiny','hablar', 'RMariaDB',  'shinydashboard', 'shinyjs', 'V8','shinyBS','ggplot2' ,'png' ), dependencies = TRUE)"

# copy the app to the image COPY shinyapps /srv/shiny-server/
# make all app files readable (solves issue when dev in Windows, but building in Ubuntu)

# Copy the app to the image
COPY /app/ /srv/shiny-server/


RUN chmod -R 755 /srv/shiny-server/

# Make all app files readable
RUN chmod -R +r /srv/shiny-server/


EXPOSE 3838

# Enable Logging from stdout
ENV SHINY_LOG_STDOUT=1
ENV SHINY_LOG_STDERR=1


CMD ["/usr/bin/shiny-server.sh"] 
