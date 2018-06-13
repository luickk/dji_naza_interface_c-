#include "wiringPi.h"

#include "naza_interface/naza_interface.h"

#include <iostream>


int main(){
	std::cout << "lool";

	naza_interface ni;

	ni.configure_pins();

}
