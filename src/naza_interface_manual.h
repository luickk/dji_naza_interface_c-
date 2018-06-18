#ifndef NAZA_INTERFACE_MANUAL_H_
#define NAZA_INTERFACE_MANUAL_H_

#include<iostream>

#include "pca9685.h"
#include "ConfigFile.h"

class naza_interface_manual_c{
	public:

		naza_interface_manual_c();
		~naza_interface_manual_c();

		void fly_backward(ConfigFile &cf, PCA9685 &pca9685, int speed);
		void fly_forward(ConfigFile &cf, PCA9685 &pca9685, int speed);

	private:
		int calc_pwm_gradient_right(int speed_in_perc, int left, int middle, int right);
		int calc_pwm_gradient_left(int speed_in_perc, int left, int middle, int right);
};


#endif
