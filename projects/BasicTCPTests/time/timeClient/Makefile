MUDUO_DIRECTORY ?= /home/build/release-install-cpp11
#MUDUO_DIRECTORY ?= $(HOME)/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
#SRC = ../src

CXXFLAGS = -g -O0 -Wall -Wextra -Werror \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -I$(MUDUO_INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt

EXECNAME = timeClient
# SOURCENAME = time

all: $(EXECNAME) clean

$(EXECNAME): timeClient.o
	g++ -std=c++11 $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
timeClient.o: timeClient.cc
	g++ -std=c++11 $(CXXFLAGS) -c timeClient.cc $(LDFLAGS)
# $(SOURCENAME).o: $(SOURCENAME).cc 
# 	g++ -std=c++11 $(CXXFLAGS) -c $(SOURCENAME).cc $(LDFLAGS)

.PHONY clean:
	rm -f *.o