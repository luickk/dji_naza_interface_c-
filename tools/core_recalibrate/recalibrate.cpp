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

  naza.recalibrate(cf, pca9685);
}
