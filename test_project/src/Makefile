CC_FILES=system_stm32f4xx.cc \
	stm32f4xx_it.cc \
	main.cc

AS_FILES = startup_stm32f411xe.s

EXECUTABLE=main.elf
HEX=main.hex

OBJECTS = $(CC_FILES:.cc=.o) $(AS_FILES:.s=.o)
EXTRA_OBJECTS=$(LOCAL_DRIVERS_SRCDIR)/ht16K33_display.o \
	$(LOCAL_DRIVERS_SRCDIR)/pec11_renc.o \
	$(STM32_ROOT)/misc.o \
	$(STM32_ROOT)/stm32f4xx_exti.o \
	$(STM32_ROOT)/stm32f4xx_i2c.o \
	$(STM32_ROOT)/stm32f4xx_gpio.o \
	$(STM32_ROOT)/stm32f4xx_rcc.o \
	$(STM32_ROOT)/stm32f4xx_syscfg.o \

default: all

clean:
	rm -rf *.o
	rm -rf *.hex
	rm -rf *.elf

all: $(HEX)

%.o: %.cc
	$(CC) $(CFLAGS) $(CC_FLAGS) $< -o $@

%.o: %.s
	$(CC) -c -x assembler-with-cpp $(ASFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(EXTRA_OBJECTS) $(LDFLAGS) -o $@

$(HEX): $(EXECUTABLE)
	$(OBJCOPY) -Oihex $(EXECUTABLE) $@

flash: $(HEX)
	$(OPENOCD) -f $(OPENOCD_CONFIG) \
	-c "init" \
	-c "reset halt" \
	-c "flash write_image erase $(HEX)" \
	-c "reset run" \
	-c "exit"

