SUBDIR=src

default: all

all:
	$(MAKE) -C $(SUBDIR) all

clean:
	$(MAKE) -C $(SUBDIR) clean

install:
	$(MAKE) -C $(SUBDIR) install

flash:
	$(MAKE) -C $(SUBDIR) flash
