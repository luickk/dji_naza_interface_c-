#include <iostream>
#include <fstream>

#include "libnaza/pca9685.h"
#include "libnaza/naza_interface_manual.h"

using namespace std;

int main(int argc, char* argv[]){

	PCA9685 pca9685;
	pca9685.SetFrequency(50);
	ConfigFile cf("/etc/naza/pwm_config.txt");

	naza_interface_manual_c naza;

	if(std::string(argv[1])=="forward"){
	 	std::cout << "Flying forward: " << argv[2] << "\n";
		naza.fly_forward(cf, pca9685, atoi(argv[2]));
	} else if(std::string(argv[1])=="back"){
		std::cout << "Flying back: " << argv[2] << "\n";
		naza.fly_back(cf, pca9685, atoi(argv[2]));
	} else if(std::string(argv[1])=="throttle"){
		std::cout << "Setting throttle: " << argv[2] << "\n";
		naza.fly_throttle(cf, pca9685, atoi(argv[2]));
	} else if(std::string(argv[1])=="left"){
		std::cout << "Flying left: " << argv[2] << "\n";
		naza.fly_left(cf, pca9685, atoi(argv[2]));
	} else if(std::string(argv[1])=="right"){
		std::cout << "Flying right: " << argv[2] << "\n";
		naza.fly_right(cf, pca9685, atoi(argv[2]));
	} else if(std::string(argv[1])=="tright"){
		std::cout << "Turning right: " << argv[2] << "\n";
		naza.fly_turn_right(cf, pca9685, atoi(argv[2]));
	} else if(std::string(argv[1])=="tleft"){
		std::cout << "Turning left: " << argv[2] << "\n";
		naza.fly_turn_left(cf, pca9685, atoi(argv[2]));
	} else if(std::string(argv[1])=="flm"){
		std::cout << "Setting Flight Mode: " << argv[2] << "\n";
		naza.set_flight_mode(cf, pca9685, argv[2]);
	} else if(std::string(argv[1])=="arm"){
		naza.arm_motors(cf, pca9685);
	} else if(std::string(argv[1])=="neutral"){
		naza.set_neutral(cf, pca9685);
	} else {
		cout << "Func not found: "  << argv[1] << "\n";
	}
}
