#include <iostream>
#include <fstream>
#include "libnaza/pca9685.h"
#include "libnaza/naza_interface_manual.h"
#include "libnaza/pca9685.h"

int main(){
	naza_interface_manual_c naza;

	PCA9685 pca9685;
	ConfigFile cf("/etc/naza/pwm_config.txt");

	naza.fly_backward(cf, pca9685, 100);
}
