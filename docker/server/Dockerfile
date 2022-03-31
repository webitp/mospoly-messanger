FROM ubuntu

# COPY ../../server/ ./serverQt 
 
WORKDIR /usr/share/server
 
ENV TZ=Europe/Moscow 
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone 
RUN apt-get update 
RUN apt-get install qt5-default -y 
#RUN apt-get -y install qtcreator 
RUN apt-get install qtbase5-dev -y 
RUN apt-get install qt5-qmake 
RUN apt-get install build-essential -y  
 
# ТУТ УКАЗАТЬ НОРМАЛЬНЫЙ ПУТЬ ДО СТАРТОГО ФАЙЛА 
# RUN qmake mospolymessenger.pro
# RUN make 
# CMD ["./mospolymessenger"]