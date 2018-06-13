#include "wiringPi.h"

#include "src/naza_interface_manual.h"

#include <iostream>


int main(){
	std::cout << "lool";

	naza_interface_manual ni;

	ni.configure_pins(8,8,8,8,8);

}
