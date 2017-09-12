export OPENOCD=openocd
export OPENOCD_CONFIG=/usr/share/openocd/scripts/board/stm32f4discovery.cfg

# Global default variables for all sub-make files. Can be overridden in sub makes
LOCAL_DRIVERS_SRCDIR=drivers
export CC=arm-none-eabi-g++
export OBJCOPY=arm-none-eabi-objcopy

export ARCHFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mlittle-endian -mfpu=fpv4-sp-d16 -mthumb-interwork -funroll-loops
export ASFLAGS=$(ARCHFLAGS)
export CC_FLAGS=-fno-exceptions -fno-rtti

export ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

export STM32_ROOT=$(ROOT_DIR)/third_party/STM
export FW_CMSIS_DIR=$(STM32_ROOT)/CMSIS
export FW_CORE_DIR=$(STM32_ROOT)/CMSIS/Device/ST/STM32F4xx
export FW_STDDRIVER_DIR=$(STM32_ROOT)/STM32F4xx_StdPeriph_Driver
export FW_STDDRIVER_SRCDIR=$(FW_STDDRIVER_DIR)/src

export CFLAGS= \
	-Wall \
	$(ARCHFLAGS) \
	-std=c++11 \
	-include stm32f4xx_conf.h \
	-I$(ROOT_DIR) \
	-I$(STM32_ROOT)/CMSIS/Include \
	-I$(FW_CORE_DIR)/Include \
	-I$(FW_STDDRIVER_DIR)/inc \
	-DSTM32F411xE \
	-Os \
	-c

export LDFLAGS= \
	$(ARCHFLAGS) \
	-DSTM32F411xE \
	-specs=nosys.specs \
	-T$(STM32_ROOT)/STM32F411RETx_FLASH.ld \
	-L$(FW_CMSIS_DIR)/Lib/GCC \
	-larm_cortexM4l_math \
	-larm_cortexM4lf_math \
	-Wl,--gc-sections

export LOCAL_DRIVERS_SRCDIR = $(ROOT_DIR)/drivers
export STM_SRCDIR = $(ROOT_DIR)/third_party/STM
export TEST_PROJECT_SRCDIR = $(ROOT_DIR)/test_project

all: test_project

flash:
	$(MAKE) -C $(TARGET) flash

stm:
	$(MAKE) -C $(STM_SRCDIR) all

test_project: drivers
	$(MAKE) -C $(TEST_PROJECT_SRCDIR) all

drivers: stm
	$(MAKE) -C $(LOCAL_DRIVERS_SRCDIR) all

clean:
	$(MAKE) -C $(LOCAL_DRIVERS_SRCDIR) clean
	$(MAKE) -C $(STM_SRCDIR) clean
	$(MAKE) -C $(TEST_PROJECT_SRCDIR) clean


