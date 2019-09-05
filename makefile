#Matthew Smith-Kennedy makefile for Project 6

all:	proj6.x
proj6.x:	proj6.o
	g++ -std=c++11 -o proj6.x proj6.o
proj6.o:	proj6.cpp
	g++ -std=c++11 -c proj6.cpp
