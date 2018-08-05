all: rgps

rgps: rgps.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -o rgps.exe rgps.o
rgps.o:
		g++ -c rgps.cpp
clean:
		rm -f *.o
