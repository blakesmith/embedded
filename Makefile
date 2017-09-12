SRC_DIR=src
DRIVERS_DIR=src/drivers

# Global default variables for all sub-make files. Can be overridden in sub makes
export CC=arm-none-eabi-g++
export OBJCOPY=arm-none-eabi-objcopy

export ARCHFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mlittle-endian -mfpu=fpv4-sp-d16 -mthumb-interwork -funroll-loops
export ASFLAGS=$(ARCHFLAGS)
export CC_FLAGS=-fno-exceptions -fno-rtti

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

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
	-I$(ROOT_DIR)/src \
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
	-L$(LOCAL_DRIVERS_SRCDIR) \
	-larm_cortexM4l_math \
	-larm_cortexM4lf_math \
	-Wl,--gc-sections

default: all

all: drivers test_project

test_project:
	$(MAKE) -C $(SRC_DIR) all

drivers:
	$(MAKE) -C $(DRIVERS_DIR) all

clean:
	$(MAKE) -C $(DRIVERS_DIR) clean
	$(MAKE) -C $(SRC_DIR) clean

install:
	$(MAKE) -C $(SRC_DIR) install

flash:
	$(MAKE) -C $(SRC_DIR) flash
