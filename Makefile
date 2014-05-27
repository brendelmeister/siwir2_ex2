CXX = g++
CXXFLAGS ?= -ansi -Wall  #-pedantic -O3 #-fopenmp -Winline
#-ggdb
SOURCES = readin.cpp matrixes.cpp
OBJECTS = readin.o matrixes.o iteration.o
HEADERS = readin.h matrixes.h iteration.h 
LIBS = -lm

.PHONY: all clean

all: readin.o matrixes.o test

# generic compilation rule
%.o : %.cpp
	${CXX} ${CXXFLAGS} -c $<

#how to link
test: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJECTS} ${LIBS}

#readin: readin.o
#	${CXX} ${CXXFLAGS} -o $@ $@.o ${LIBS}

clean:
	rm -f *.o *~ *.txt  *.dat
