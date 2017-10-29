CC_FILES=adsr_envelope.cc \
	beat.cc \
	settings.cc \
	user_interface.cc \
	osc.cc

EXTRA_OBJECTS=$(LOCAL_DRIVERS_SRCDIR)/ht16K33_display.o \
	$(LOCAL_DRIVERS_SRCDIR)/pec11_renc.o \
	$(LOCAL_DRIVERS_SRCDIR)/status_led.o \
	$(LOCAL_DRIVERS_SRCDIR)/cs43l22_dac.o \
	$(STM32_ROOT)/stm32f4xx_dma.o \
	$(STM32_ROOT)/stm32f4xx_exti.o \
	$(STM32_ROOT)/stm32f4xx_i2c.o \
	$(STM32_ROOT)/stm32f4xx_gpio.o \
	$(STM32_ROOT)/stm32f4xx_rcc.o \
	$(STM32_ROOT)/stm32f4xx_spi.o \
	$(STM32_ROOT)/stm32f4xx_syscfg.o \
	$(STM32_ROOT)/misc.o \

ifeq ($(PLATFORM),linux)
	CC=g++
	CFLAGS=-c -Wall -std=c++11 -D__LINUX__
	LDFLAGS=-lm -lasound
	CC_FILES += main_linux.cc alsa_output.cc
	EXTRA_OBJECTS=
else
	CC_FILES += main_stm32.cc \
	stm32f4xx_it.cc \
	system_stm32f4xx.cc \
	gpio_bus.cc \
	gpio_pin.cc

	AS_FILES = startup_stm32f411xe.s
endif

OBJECTS=$(CC_FILES:.cc=.o) $(AS_FILES:.s=.o)

EXECUTABLE=nome
HEX=$(EXECUTABLE).hex

all: $(EXECUTABLE)

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
	rm -rf *.o $(EXECUTABLE) $(HEX)

install: all
	cp $(EXECUTABLE) /usr/local/bin

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(EXTRA_OBJECTS) $(LDFLAGS) -o $@

%.o: %.cc
	$(CC) $(CFLAGS) $(CC_FLAGS) $< -o $@

%.o: %.s
	$(CC) -c -x assembler-with-cpp $(ASFLAGS) $< -o $@
