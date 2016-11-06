.PHONY: all test

all:
	cd build && $(MAKE)

test:
	cd build && $(MAKE) test
