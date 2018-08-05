all: recalibrate

recalibrate: recalibrate.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -o recalibrate.exe recalibrate.o
recalibrate.o:
		g++ -c recalibrate.cpp
clean:
		rm -f *.o
