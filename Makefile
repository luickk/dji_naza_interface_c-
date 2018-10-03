PREFIX?=/usr
BUILDDIR=build
LIB_NAME=libnaza
SO_SUFFIX=so
LIB_SO_NAME=$(LIB_NAME).$(SO_SUFFIX)

all: libso

libso: naza_interface_manual.o naza_interface_auto.o pca9685.o Chameleon.o ConfigFile.o naza_serial_gps.o
	@echo [LINK] $(LIB_NAME)
	g++ naza_interface_manual.o naza_interface_auto.o pca9685.o Chameleon.o ConfigFile.o naza_serial_gps.o -o build/$(LIB_SO_NAME) -fPIC -L/usr/local/lib -shared -lbcm2835

naza_interface_manual.o: src/naza_interface_manual.cpp src/naza_interface_manual.h
	g++ -c src/naza_interface_manual.cpp
naza_interface_auto.o: src/naza_interface_auto.cpp src/naza_interface_auto.h
	g++ -c src/naza_interface_auto.cpp
	
pca9685.o: src/pca9685.cpp
	g++ -c src/pca9685.cpp
Chameleon.o: src/Chameleon.cpp
	g++ -c src/Chameleon.cpp
ConfigFile.o: src/ConfigFile.cpp
	g++ -c src/ConfigFile.cpp
naza_serial_gps.o: src/naza_serial_gps.cpp
	g++ -c src/naza_serial_gps.cpp

$(shell mkdir -p $(BUILDDIR) >/dev/null)

install: real_uninstall
	@echo [INSTALL] $(LIB_NAME)
	@echo build: build/$(LIB_NAME)
	@mkdir -p "$(PREFIX)/include/$(LIB_NAME)"
	@rm -f "$(PREFIX)/lib/$(LIB_SO_NAME)"
	@cp src/*.h "$(PREFIX)/include/$(LIB_NAME)"
	@cp build/$(LIB_SO_NAME) "$(PREFIX)/lib"
	@mkdir -p "/etc/naza"
	@cp -vn template/pwm_config.txt.template /etc/naza/pwm_config.txt | true

uninstall: uninstall_banner real_uninstall

uninstall_banner:
	@echo [UNINSTALL] $(LIB_NAME)

real_uninstall:
	@rm -rf "$(PREFIX)/include/$(LIB_NAME)" "$(PREFIX)/lib/$(LIB_SO_NAME)"

clean:
	@rm -rf build/*
