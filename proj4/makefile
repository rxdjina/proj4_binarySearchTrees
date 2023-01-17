CC=gcc
CXX=g++
RM=rm -f
CXXFLAGS=-std=c++11 -Wall -pedantic
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

OBJS=$(subst .cc,.o,.x,.cpp,.hpp,$(SRCS))

proj4.x: proj4_driver.o bet.o
	$(CXX) $(CXXFLAGS) -o $@ $^

.SUFFIXES: .x

.PHONY : clean

clean:
	$(RM) $(OBJS)

distclean: clean

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
