all: gpsc

gpsc: gpsc.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -lwiringPi -lpthread -o gpsc.exe gpsc.o
gpsc.o:
		g++ -c gpsc.cpp
clean:
		rm -f *.o
