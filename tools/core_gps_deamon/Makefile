all: gpsd

gpsd: gpsd.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -lwiringPi -lpthread -o gpsd.exe gpsd.o
gpsd.o:
		g++ -c gpsd.cpp
clean:
		rm -f *.o
