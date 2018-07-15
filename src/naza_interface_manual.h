#ifndef NAZA_INTERFACE_MANUAL_H_
#define NAZA_INTERFACE_MANUAL_H_

#include<iostream>

#include "pca9685.h"
#include "ConfigFile.h"

using namespace std;

class naza_interface_manual_c{
	public:

		naza_interface_manual_c();
		~naza_interface_manual_c();

		void init_naza(ConfigFile &cf, PCA9685 &pca9685);
		void fly_forward(ConfigFile &cf, PCA9685 &pca9685, int speed);
		void fly_back(ConfigFile &cf, PCA9685 &pca9685, int speed);
		void fly_throttle(ConfigFile &cf, PCA9685 &pca9685, int speed);
		void fly_left(ConfigFile &cf, PCA9685 &pca9685, int speed);
		void fly_right(ConfigFile &cf, PCA9685 &pca9685, int speed);
		void fly_turn_right(ConfigFile &cf, PCA9685 &pca9685, int speed);
		void fly_turn_left(ConfigFile &cf, PCA9685 &pca9685, int speed);

		void set_neutral(ConfigFile &cf, PCA9685 &pca9685);
		void recalibrate(ConfigFile &cf, PCA9685 &pca9685);
		void set_flight_mode(ConfigFile &cf, PCA9685 &pca9685, string mode);
		void arm_motors(ConfigFile &cf, PCA9685 &pca9685);
	private:
		int calc_pwm_gradient_right(string stick_motion, int speed_in_perc, int left, int middle, int right);
		int calc_pwm_gradient_left(string stick_motion, int speed_in_perc, int left, int middle, int right);
		int calc_pwm_gradient_throttle(string stick_motion, int speed_in_perc,int left, int right);
};


#endif
