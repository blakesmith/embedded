CC_FILES = cs43l22_dac.cc \
	ht16K33_display.cc \
	pec11_renc.cc \
	status_led.cc

OBJECTS = $(CC_FILES:.cc=.o)

default: all

clean:
	rm -rf *.o

all: $(OBJECTS)

%.o: %.cc
	$(CC) $(CFLAGS) $(CC_FLAGS) $< -o $@
