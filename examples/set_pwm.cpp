#include "libnaza/pca9685.h"
#include <iostream>

int main(){

	PCA9685 pca9685;
	std::cout << "Enter relativ PWM value to set: ";
	while(1){
		std::string pwm_val;
		std::getline(std::cin, pwm_val);
		int pwm_value = atoi(pwm_val.c_str());
		std::cout << "Pwm val: " << pwm_value << "\n";
		pca9685.Write(CHANNEL(1), VALUE(pwm_value));
	}

}
