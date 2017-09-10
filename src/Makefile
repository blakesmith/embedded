CC=arm-none-eabi-g++
OBJCOPY=arm-none-eabi-objcopy
OPENOCD=openocd
OPENOCD_CONFIG=/usr/share/openocd/scripts/board/stm32f4discovery.cfg

BUILDDIR=.

STM32_ROOT=../third_party/STM
FW_CMSIS_DIR=$(STM32_ROOT)/CMSIS
FW_CORE_DIR=$(STM32_ROOT)/CMSIS/Device/ST/STM32F4xx

FW_STDDRIVER_DIR=$(STM32_ROOT)/STM32F4xx_StdPeriph_Driver
FW_STDDRIVER_SRCDIR=$(FW_STDDRIVER_DIR)/src

LOCAL_DRIVERS_SRCDIR = drivers

VPATH += $(FW_STDDRIVER_SRCDIR) $(LOCAL_DRIVERS_SRCDIR)

ARCHFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mlittle-endian -mfpu=fpv4-sp-d16 -mthumb-interwork -funroll-loops
ASFLAGS=$(ARCHFLAGS)

CFLAGS= \
	-Wall \
	$(ARCHFLAGS) \
	-std=c++11 \
	-include stm32f4xx_conf.h \
	-I. \
	-I$(STM32_ROOT)/CMSIS/Include \
	-I$(FW_CORE_DIR)/Include \
	-I$(FW_STDDRIVER_DIR)/inc \
	-DSTM32F411xE \
	-Os \
	-c

CC_FLAGS=-fno-exceptions -fno-rtti

LDFLAGS= \
	$(ARCHFLAGS) \
	-DSTM32F411xE \
	-specs=nosys.specs \
	-T$(STM32_ROOT)/STM32F411RETx_FLASH.ld \
	-L$(FW_CMSIS_DIR)/Lib/GCC \
	-larm_cortexM4l_math \
	-larm_cortexM4lf_math \
	-Wl,--gc-sections

DRIVERS_C_FILES = $(notdir $(wildcard $(patsubst %,%/*.c,$(FW_STDDRIVER_SRCDIR))))
LOCAL_DRIVERS_CC_FILES = $(notdir $(wildcard $(patsubst %,%/*.cc,$(LOCAL_DRIVERS_SRCDIR))))

C_FILES=$(DRIVERS_C_FILES)

CC_FILES=system_stm32f4xx.cc \
	stm32f4xx_it.cc \
	main.cc \
	$(LOCAL_DRIVERS_CC_FILES)

AS_FILES = startup_stm32f411xe.s

OBJECTS=$(CC_FILES:.cc=.o) $(C_FILES:.c=.o) $(AS_FILES:.s=.o)

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
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(HEX): $(EXECUTABLE)
	$(OBJCOPY) -Oihex $(EXECUTABLE) $@

$(BUILDDIR)/%.o: %.cc
	$(CC) $(CFLAGS) $(CC_FLAGS) $< -o $@

$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.s
	$(CC) -c -x assembler-with-cpp $(ASFLAGS) $< -o $@

