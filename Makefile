# Компилятор
CC=g++

# Стандарт
STD=c++11

OPENCVLIBS = $(shell pkg-config --libs opencv)

SFMLLIBS = -lsfml-graphics -lsfml-window -lsfml-system 

OPENGLLIBS = -lGL -lglut -lGLU -lGLEW 

.PHONY: all

all: exec clean

exec: main.o Detector.o SfSurface.o Surface.o Ball.o SfBall.o BallLauncher.o SfBallLauncher.o Robot.o SfRobot.o
	$(CC) Detector.o Surface.o SfSurface.o Ball.o SfBall.o BallLauncher.o SfBallLauncher.o Robot.o SfRobot.o main.o -o exec $(SFMLLIBS) $(OPENCVLIBS) $(OPENGLLIBS)
main.o: main.cpp
	$(CC) -std=$(STD) -c main.cpp
Detector.o: Detector.cpp Detector.hpp
	$(CC) -std=$(STD) -c Detector.cpp
Surface.o: Surface.cpp Surface.hpp
	$(CC) -std=$(STD) -c Surface.cpp
SfSurface.o: SfSurface.cpp SfSurface.hpp
	$(CC) -std=$(STD) -c SfSurface.cpp
Robot.o: Robot.cpp Robot.hpp
	$(CC) -std=$(STD) -c Robot.cpp
SfRobot.o: SfRobot.cpp SfRobot.hpp
	$(CC) -std=$(STD) -c SfRobot.cpp
Ball.o: Ball.cpp Ball.hpp
	$(CC) -std=$(STD) -c Ball.cpp
SfBall.o: SfBall.cpp SfBall.hpp
	$(CC) -std=$(STD) -c SfBall.cpp
BallLauncher.o: BallLauncher.cpp BallLauncher.hpp
	$(CC) -std=$(STD) -c BallLauncher.cpp
SfBallLauncher.o: SfBallLauncher.cpp SfBallLauncher.hpp
	$(CC) -std=$(STD) -c SfBallLauncher.cpp
clean:
	rm -rf *.o
