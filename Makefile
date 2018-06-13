libso: naza_interface_manual.o pca9685.o
		g++ -L/usr/local/lib naza_interface_manual.o pca9685.o -lbcm2835 -shared -o libnazainterface.a

naza_interface_manual.o: src/naza_interface_manual.cpp src/naza_interface_manual.h
		g++ -c src/naza_interface_manual.cpp

pca9685.o: src/PCA9685/pca9685.cpp src/PCA9685/pca9685.h
		g++ -c src/PCA9685/pca9685.cpp

test.o:
		g++ -c examples/test.cpp

clean:
		rm *.o output

install: naza_interface_manual.o pca9685.o
		g++ -L/usr/local/lib naza_interface_manual.o pca9685.o -lbcm2835 -shared -o /usr/local/libnazainterface.a

