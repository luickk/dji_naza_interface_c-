#include <iostream>
#include <fstream>

#include "libnaza/pca9685.h"
#include "libnaza/naza_interface_manual.h"

int main(){

	PCA9685 pca9685;
	pca9685.SetFrequency(50);
	ConfigFile cf("/etc/naza/pwm_config.txt");

	naza_interface_manual_c naza;
	naza.init_naza(cf, pca9685);


	//naza.fly_back(cf, pca9685, 60);
	//naza.fly_forward(cf, pca9685, 0);
	//naza.fly_throttle(cf, pca9685, 80);
	//naza.fly_left(cf, pca9685, 60);
	//naza.fly_right(cf, pca9685, 0);
	//naza.fly_turn_right(cf, pca9685, 0);
	//naza.fly_turn_left(cf, pca9685, 80);

}
