all: test

test: test.o
		g++ -L/usr/lib/ -lnaza -o test.exe test.o

set_pwm: set_pwm.o
		g++ -L/usr/lib/ -lnaza -o set_pwm.exe set_pwm.o
set_pwm.o:
		g++ -c set_pwm.cpp

test.o:
		g++ -c test.cpp

clean:
		rm -f *.o
