all: gpsd

gpsd: gpsd.o client.o mythread.o server.o server_gps_decoder.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -lwiringPi -lpthread -o gpsd.exe gpsd.o client.o mythread.o server.o server_gps_decoder.o

gpsd.o:
		g++ -c gpsd.cpp
client.o:
		g++ -c tcp_raw/client.cpp
mythread.o:
		g++ -c tcp_raw/mythread.cpp
server.o:
		g++ -c tcp_raw/server.cpp
server_gps_decoder.o:
		g++ -c server_gps_decoder.cpp

clean:
		rm -f *.o
