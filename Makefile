export OPENOCD=openocd
export OPENOCD_CONFIG=/usr/share/openocd/scripts/board/stm32f4discovery.cfg

# Global default variables for all sub-make files. Can be overridden in sub makes
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

export LOCAL_DRIVERS_SRCDIR = $(ROOT_DIR)/drivers/src
export STM_SRCDIR = $(ROOT_DIR)/third_party/STM
export PROJECT_SRCDIR = $(ROOT_DIR)/$(PROJECT)/src

export CFLAGS= \
	-Wall \
	$(ARCHFLAGS) \
	-std=c++11 \
	-include stm32f4xx_conf.h \
	-I$(LOCAL_DRIVERS_SRCDIR) \
	-I$(STM32_ROOT)/CMSIS/Include \
	-I$(FW_CORE_DIR)/Include \
	-I$(FW_STDDRIVER_DIR)/inc \
	-Os \
	-c

export LDFLAGS= \
	$(ARCHFLAGS) \
	-specs=nosys.specs \
	-L$(FW_CMSIS_DIR)/Lib/GCC \
	-larm_cortexM4l_math \
	-larm_cortexM4lf_math \
	-Wl,--gc-sections

ifeq ($(TARGET),prototype)
	CFLAGS += -DTARGET_PROTOTYPE -DSTM32F413_423xx
	LDFLAGS += -DSTM32F413_423xx \
		-T$(STM32_ROOT)/STM32F413ZHTx_FLASH.ld
else
	CFLAGS += -DTARGET_BREADBOARD -DSTM32F411xE
	LDFLAGS += -DSTM32F411xE\
		-T$(STM32_ROOT)/STM32F411RETx_FLASH.ld
endif


all: project

project: drivers
	$(MAKE) -C $(PROJECT_SRCDIR) all

drivers: stm
	$(MAKE) -C $(LOCAL_DRIVERS_SRCDIR) all

stm:
	$(MAKE) -C $(STM_SRCDIR) all

flash:
	$(MAKE) -C $(PROJECT_SRCDIR) flash

clean:
	$(MAKE) -C $(PROJECT_SRCDIR) clean

clean_all:
	$(MAKE) -C $(LOCAL_DRIVERS_SRCDIR) clean
	$(MAKE) -C $(STM_SRCDIR) clean
	$(MAKE) -C $(ROOT_DIR)/test_project/src clean
	$(MAKE) -C $(ROOT_DIR)/nome/src clean


bazel-periph:
	bazel build -s --crosstool_top=@stm32//tools/arm_compiler:toolchain --cpu=armeabi-v7a //third_party/STM:stm_std_periph

bazel-drivers:
	bazel build -s --crosstool_top=@stm32//tools/arm_compiler:toolchain --cpu=armeabi-v7a //drivers:stm_drivers
