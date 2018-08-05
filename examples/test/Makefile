all: test

test: test.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -o test.exe test.o

test.o:
		g++ -c test.cpp

clean:
		rm -f *.o
