CXX = g++
CXXFLAGS ?= -ansi -Winline -Wshadow -Wall -O3
BIN = readIn
SOURCES = readin.cpp
HEADERS = 
LIBS = 

.PHONY: all clean

all: ${BIN}

${BIN}: ${SOURCES}
	${CXX} ${CXXFLAGS} -o $@ $< 

clean:
	rm -f *.o *~ *.swp ${BIN}
