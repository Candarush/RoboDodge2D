# Компилятор
CC=g++

# Стандарт
STD=c++11

OPENCVLIBS = $(shell pkg-config --libs opencv)

OPENGLLIBS = -lGL -lglut -lGLU -lGLEW 

.PHONY: all

all: exec clean

exec: main.o Detector.o OpenGLRenderer.o Surface.o Ball.o BallLauncher.o Robot.o DBclient.o
	$(CC) DBclient.o OpenGLRenderer.o Detector.o Surface.o  Ball.o BallLauncher.o Robot.o main.o -o exec $(OPENCVLIBS) $(OPENGLLIBS)
main.o: main.cpp
	$(CC) -std=$(STD) -c main.cpp
DBclient.o: DBclient.cpp
	$(CC) -std=$(STD) -c DBclient.cpp
Detector.o: Detector.cpp Detector.hpp
	$(CC) -std=$(STD) -c Detector.cpp
OpenGLRenderer.o: OpenGLRenderer.cpp
	$(CC) -std=$(STD) -c OpenGLRenderer.cpp
Surface.o: Surface.cpp Surface.hpp
	$(CC) -std=$(STD) -c Surface.cpp
Robot.o: Robot.cpp Robot.hpp
	$(CC) -std=$(STD) -c Robot.cpp
Ball.o: Ball.cpp Ball.hpp
	$(CC) -std=$(STD) -c Ball.cpp
BallLauncher.o: BallLauncher.cpp BallLauncher.hpp
	$(CC) -std=$(STD) -c BallLauncher.cpp
clean:
	rm -rf *.o
