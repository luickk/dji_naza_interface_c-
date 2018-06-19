#include "libnaza/pca9685.h"
#include <iostream>

int main(){

	PCA9685 pca9685;

	pca9685.SetFrequency(50);
	std::cout << "Enter Channel: ";
	std::string ch_val;
	std::getline(std::cin, ch_val);
	int cha_value = atoi(ch_val.c_str());

	while(1){
		std::string pwm_val;
		std::getline(std::cin, pwm_val);
		int pwm_value = atoi(pwm_val.c_str());
		std::cout << "Pwm val: " << pwm_value << "\n";
		pca9685.Write(CHANNEL(cha_value), VALUE(pwm_value));
	}

}
