#ifndef NAZA_INTERFACE_AUTO_H_
#define NAZA_INTERFACE_AUTO_H_

#include<iostream>

#include "naza_interface_manual.h"
#include "pca9685.h"
#include "ConfigFile.h"

using namespace std;

class naza_interface_auto_c{
	public:

		naza_interface_auto_c();
		~naza_interface_auto_c();

		void auto_liftoff(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, double height);
		void auto_landing(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza);
		void fly_to_gps_pos(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, double lat, double lon, double height);
		void turn_to_deg(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, double deg);
		void auto_hover(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza);
};


#endif
