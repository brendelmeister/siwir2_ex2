CXX = g++
CXXFLAGS ?= -ansi -Wall -pedantic #-pg  -O3 #-fopenmp -Winline
SOURCES = readin.cpp matrixes.cpp cgsolver.cpp
OBJECTS = readin.o matrixes.o iteration.o cgsolver.o
LIBS = -lm

.PHONY: all clean

all: waveguide

# generic compilation rule
%.o : %.cpp
	${CXX} ${CXXFLAGS} -c $<

#how to link
waveguide: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJECTS} ${LIBS}

clean:
	rm -f *.o *~ *.txt  *.dat waveguide
