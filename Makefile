
PREFIX?=/usr
BUILDDIR=build
LIB_NAME=libnaza
SO_SUFFIX=so
LIB_SO_NAME=$(LIB_NAME).$(SO_SUFFIX)

all: libso

libso: naza_interface_manual.o pca9685.o
	@echo [LINK] $(LIB_NAME)
	g++ -fPIC -L/usr/local/lib -shared naza_interface_manual.o pca9685.o -lbcm2835 -o build/$(LIB_SO_NAME)

naza_interface_manual.o: src/naza_interface_manual.cpp src/naza_interface_manual.h
	g++ -c src/naza_interface_manual.cpp

pca9685.o: src/pca9685.cpp
	g++ -c src/pca9685.cpp


$(shell mkdir -p $(BUILDDIR) >/dev/null)

install: real_uninstall
	@echo [INSTALL] $(LIB_NAME)
	@echo build: build/$(LIB_NAME)
	@mkdir -p "$(PREFIX)/include/$(LIB_NAME)"
	@rm -f "$(PREFIX)/lib/$(LIB_SO_NAME)"
	@cp src/*.h "$(PREFIX)/include/$(LIB_NAME)"
	@cp build/$(LIB_SO_NAME) "$(PREFIX)/lib"

uninstall: uninstall_banner real_uninstall

uninstall_banner:
	@echo [UNINSTALL] $(LIB_NAME)

real_uninstall:
	@rm -rf "$(PREFIX)/include/$(LIB_NAME)" "$(PREFIX)/lib/$(LIB_SO_NAME)"

clean:
	@rm -rf build/*
