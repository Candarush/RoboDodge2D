FROM ubuntu:16.04

RUN apt-get update

RUN apt-get install build-essential  -y
RUN apt-get install wget -y
RUN apt-get install gcc -y
RUN apt-get install clang -y
RUN apt-get install g++ -y

#OPENCV
RUN apt-get install libopencv-dev -y

#OPENGL
RUN apt-get install -y mesa-common-dev freeglut3-dev libglew-dev

#INFLUXDB
RUN apt-get install influxdb -y
RUN service influxdb start
#RUN influxd

# Сборка
COPY . /usr/src/
WORKDIR /usr/src/
RUN make

#Запуск
CMD ["./exec"]
