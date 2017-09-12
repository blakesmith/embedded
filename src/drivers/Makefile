CC_FILES = ht16K33_display.cc

OBJECTS = $(CC_FILES:.cc=.o)

clean:
	rm -rf *.o

all: $(OBJECTS)

%.o: %.cc
	$(CC) $(CFLAGS) $(CC_FLAGS) $< -o $@
