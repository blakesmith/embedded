CC=arm-none-eabi-g++
OBJCOPY=arm-none-eabi-objcopy
OPENOCD=openocd
OPENOCD_CONFIG=/usr/share/openocd/scripts/board/stm32f4discovery.cfg

STM_CUBE_ROOT=../../STM32Cube_FW_F4_V1.16.0

CFLAGS=-Wall \
	-mcpu=cortex-m4 \-mlittle-endian \
	-mthumb \
	-I$(STM_CUBE_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
	-I$(STM_CUBE_ROOT)/Drivers/CMSIS/Include \
	-DSTM32F401xE \
	-Os \
	-c

LDFLAGS=-mcpu=cortex-m4 \
	-mlittle-endian \
	-mthumb \
	-DSTM32F401xE \
	-T$(STM_CUBE_ROOT)/Projects/STM32F401-Discovery/Templates/TrueSTUDIO/STM32F401-Discovery/STM32F401CC_FLASH.ld \
	-Wl,--gc-sections

SOURCES=system_stm32f4xx.cc \
	stm32f4xx_it.cc \
	main.cc

OBJECTS=$(SOURCES:.cc=.o) startup_stm32f4xx.s
EXECUTABLE=main.elf
HEX=main.hex

flash: $(HEX)
	$(OPENOCD) -f $(OPENOCD_CONFIG) -c "init"
	$(OPENOCD) -f $(OPENOCD_CONFIG) -c "reset halt"
	$(OPENOCD) -f $(OPENOCD_CONFIG) -c "flash write_image erase $(HEX)"
	$(OPENOCD) -f $(OPENOCD_CONFIG) -c "reset run"

all: $(SOURCES) $(HEX)

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(HEX): $(EXECUTABLE)
	$(OBJCOPY) -Oihex $(EXECUTABLE) $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@
