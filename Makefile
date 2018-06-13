output: main.o naza_interface_manual.o pca9685.o
		g++ -L/usr/local/lib main.o naza_interface_manual.o pca9685.o -lbcm2835 -o output

main.o: main.cpp
		g++ -c main.cpp

naza_interface_manual.o: src/naza_interface_manual.cpp src/naza_interface_manual.h
		g++ -c src/naza_interface_manual.cpp

pca9685.o: src/PCA9685/pca9685.cpp src/PCA9685/pca9685.h
		g++ -c src/PCA9685/pca9685.cpp

clean:
		rm *.o output
