CC_FILES= adsr_envelope.cc \
	beat.cc \
	osc.cc

ifeq ($PLATFORM,linux)
	CFLAGS=-c -Wall -std=c++11 -D__LINUX__
	LDFLAGS=-lm -lasound
	CC_FILES += nome.cc alsa_output.cc
endif

OBJECTS=$(CC_FILES:.cc=.o)
EXECUTABLE=nome
ELF_FILE=$(EXECUTABLE).elf
HEX=$(EXECUTABLE).hex

all: $(HEX)

$(HEX): $(EXECUTABLE)
	$(OBJCOPY) -Oihex $(EXECUTABLE) $@

flash: $(HEX)
	$(OPENOCD) -f $(OPENOCD_CONFIG) \
	-c "init" \
	-c "reset halt" \
	-c "flash write_image erase $(HEX)" \
	-c "reset run" \
	-c "exit"

linux: $(SOURCES) $(EXECUTABLE)

clean:
	rm -rf *.o $(EXECUTABLE)

install: all
	cp $(EXECUTABLE) /usr/local/bin

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(EXTRA_OBJECTS) $(LDFLAGS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@
