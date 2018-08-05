all: set_pwm

set_pwm: set_pwm.o
		g++ -L/usr/lib/ -lnaza -lwiringPi -o set_pwm.exe set_pwm.o
set_pwm.o:
		g++ -c set_pwm.cpp
clean:
		rm -f *.o
