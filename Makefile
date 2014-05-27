CXX = g++
CXXFLAGS ?= -ansi  -Wshadow -Wall -O3 #-fopenmp -Winline
#-ggdb
SOURCES = readin.cpp matrixes.cpp
OBJECTS = readin.o matrixes.o
HEADERS = readin.h matrixes.h
LIBS = -lm

.PHONY: all clean

all: readin.o matrixes.o test

# generic compilation rule
readin.o : readin.cpp
	${CXX} ${CXXFLAGS} -c $<

matrixes.o : matrixes.cpp
	${CXX} ${CXXFLAGS} -c $<

#%.o : %.cpp
#	${CXX} ${CXXFLAGS} -c $<

#how to link
test: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJECTS} ${LIBS}

#readin: readin.o
#	${CXX} ${CXXFLAGS} -o $@ $@.o ${LIBS}

clean:
	rm -f *.o *~ *.txt  *.dat
