OPENOCD=openocd
OPENOCD_CONFIG=/usr/share/openocd/scripts/board/stm32f4discovery.cfg

BUILDDIR=.

LOCAL_DRIVERS_SRCDIR = drivers
VPATH += $(FW_STDDRIVER_SRCDIR)

DRIVERS_C_FILES = $(notdir $(wildcard $(patsubst %,%/*.c,$(FW_STDDRIVER_SRCDIR))))

C_FILES=$(DRIVERS_C_FILES)

CC_FILES=system_stm32f4xx.cc \
	stm32f4xx_it.cc \
	main.cc

AS_FILES = startup_stm32f411xe.s

OBJECTS=$(CC_FILES:.cc=.o) $(C_FILES:.c=.o) $(AS_FILES:.s=.o)

EXTRA_OBJECTS=drivers/ht16K33_display.o

EXECUTABLE=main.elf
HEX=main.hex

flash: $(HEX)
	$(OPENOCD) -f $(OPENOCD_CONFIG) \
	-c "init" \
	-c "reset halt" \
	-c "flash write_image erase $(HEX)" \
	-c "reset run" \
	-c "exit"

all: $(HEX)

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(EXTRA_OBJECTS) $(LDFLAGS) -o $@

$(HEX): $(EXECUTABLE)
	$(OBJCOPY) -Oihex $(EXECUTABLE) $@

$(BUILDDIR)/%.o: %.cc
	$(CC) $(CFLAGS) $(CC_FLAGS) $< -o $@

$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.s
	$(CC) -c -x assembler-with-cpp $(ASFLAGS) $< -o $@

