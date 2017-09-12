C_FILES = $(notdir $(wildcard $(patsubst %,%/*.c,$(FW_STDDRIVER_SRCDIR))))

VPATH += $(FW_STDDRIVER_SRCDIR)

all: $(C_FILES:.c=.o)

clean:
	rm -rf *.o

%.o: %.c
	$(CC) $(CFLAGS) $(C_FLAGS) $< -o $@
