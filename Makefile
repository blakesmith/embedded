SRC_DIR=src

default: all

test_project:
	$(MAKE) -C $(SRC_DIR) test_project	

all:
	$(MAKE) -C $(SRC_DIR) all

clean:
	$(MAKE) -C $(SRC_DIR) clean

install:
	$(MAKE) -C $(SRC_DIR) install

flash:
	$(MAKE) -C $(SRC_DIR) flash
