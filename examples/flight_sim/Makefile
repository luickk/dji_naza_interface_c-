all: flight_sim

flight_sim: flight_sim.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -o flight_sim.exe flight_sim.o

flight_sim.o:
		g++ -c flight_sim.cpp

clean:
		rm -f *.o
