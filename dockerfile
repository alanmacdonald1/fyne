FROM rocker/shiny:latest


RUN apt-get update && apt-get install libcurl4-openssl-dev libv8-dev -y && \
    mkdir -p /var/lib/shiny-server/bookmarks/shiny


RUN apt-get update && \
    apt-get install -y python3 && \
    ln -s /usr/bin/python3 /usr/bin/python


RUN R -e "install.packages(c('reshape2', 'ggmap' , 'readxl', 'magrittr', 'shinyalert','leaflet', 'Hmisc', 'lubridate', 'gridExtra','shiny','hablar', 'RMariaDB', 'shinydashboard', 'shinyjs', 'V8','shinyBS','ggplot2' ,'png' , 'DT'), dependencies = TRUE)"

COPY /app/ /srv/shiny-server/

RUN chmod 755 /usr/bin/shiny-server

RUN chmod -R a+w /srv/shiny-server/


RUN chmod -R a+w /usr/local/lib/R/etc



EXPOSE 3838

ENV SHINY_LOG_STDOUT=1
ENV SHINY_LOG_STDERR=1



CMD ["/usr/bin/shiny-server"]
