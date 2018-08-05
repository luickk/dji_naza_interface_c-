all: ccontrol

ccontrol: ccontrol.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -o ccontrol.exe ccontrol.o

ccontrol.o:
		g++ -c ccontrol.cpp

clean:
		rm -f *.o
