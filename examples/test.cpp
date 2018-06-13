#include <iostream>
#include "naza_interface_manual.h"

int main(){

	std::cout << "Checking pins!";

	naza_interface_manual n;

	n.check_pins();
}
