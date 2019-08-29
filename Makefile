# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o LTexture.o
	$(CXX) $(CXXFLAGS) -o main main.o LTexture.o

# The main.o target can be written more simply

main.o: main.cpp LTexture.hpp LTexture.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

LTexture.o: LTexture.cpp LTexture.hpp
