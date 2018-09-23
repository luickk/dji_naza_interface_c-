all: gpsd

gpsd: gpsd.o client.o mythread.o server.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -lwiringPi -lpthread -o gpsd.exe gpsd.o client.o mythread.o server.o

gpsd.o:
		g++ -c gpsd.cpp
client.o:
		g++ -c client.cpp
mythread.o:
		g++ -c mythread.cpp
server.o:
		g++ -c server.cpp
clean:
		rm -f *.o
