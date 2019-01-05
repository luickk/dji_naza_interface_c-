#ifndef NAZA_INTERFACE_AUTO_H_
#define NAZA_INTERFACE_AUTO_H_

#include<iostream>
#include <math.h>
#include <cmath>

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
		void fly_to_gps_pos(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, float lat, float lon, float* live_lat, float* live_lon, int* live_heading);
		void turn_to_deg(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, double deg, int* live_heading);
		void auto_hover(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza);

	private:
		bool inRange(unsigned low, unsigned high, unsigned x);
		double distance(double lat1, double lon1, double lat2, double lon2);
		double _ftod(float fValue);
};


#endif
