CC=g++
CFLAGS=-c -Wall -std=c++11 -D__LINUX__
LDFLAGS=-lm -lasound

SOURCES=nome.cc \
	adsr_envelope.cc \
	osc.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=nome

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -rf *.o $(EXECUTABLE)

install: all
	cp $(EXECUTABLE) /usr/local/bin

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@
