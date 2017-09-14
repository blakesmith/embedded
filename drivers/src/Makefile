CC_FILES = ht16K33_display.cc \
	pec11_renc.cc

OBJECTS = $(CC_FILES:.cc=.o)

default: all

clean:
	rm -rf *.o

all: $(OBJECTS)

%.o: %.cc
	$(CC) $(CFLAGS) $(CC_FLAGS) $< -o $@
