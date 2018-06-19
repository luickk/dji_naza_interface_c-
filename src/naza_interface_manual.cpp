#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fstream>

#include "naza_interface_manual.h"
#include "pca9685.h"
#include "ConfigFile.h"

using namespace std;

naza_interface_manual_c::naza_interface_manual_c(ConfigFile &cf, PCA9685 &pca9685){
	cout << "Initializing Naza Interface Controller \n";

	cout << "-" << "\n";
	cout << "A Channel PWM Values " << "left: " << cf.Value("A", "left") << " middle: " << cf.Value("A", "middle") << " right: " << cf.Value("A", "right") << "\n";
	cout << "E Channel PWM Values " << "left: " << cf.Value("E", "left") << " middle: " << cf.Value("E", "middle") << " right: " << cf.Value("E", "right") << "\n";
	cout << "T Channel PWM Values " << "left: " << cf.Value("T", "left") << " right: " << cf.Value("T", "right") << "\n";
	cout << "R Channel PWM Values " << "left: " << cf.Value("R", "left") << " middle: " << cf.Value("R", "middle") << " right: " << cf.Value("R", "right") << "\n";
	cout << "U Channel PWM Values " << "GPS: " << cf.Value("U", "GPS") << " Failsafe: " << cf.Value("U", "Failsafe") << " Atti: " << cf.Value("U", "Atti") << "\n";
	cout << "-" << "\n";

	set_neutral(cf, pca9685);
	cout << "Setting all channels on neutral!" << "\n";
	cout << "---IMPORTANT---" << "\n";
	cout << "   Check channels for command calibration before giving power to motors!" << "\n";
}


naza_interface_manual_c::~naza_interface_manual_c(){
}

void naza_interface_manual_c::fly_forward(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_right(speed, cf.Value("E","left"), cf.Value("E","middle"), cf.Value("E","right"));
	cout << "Flying Forward with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
	pca9685.Write(CHANNEL(cf.Value("E","channel")), VALUE(rel_pwm));
}

void naza_interface_manual_c::fly_back(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_left(speed, cf.Value("E","left"), cf.Value("E","middle"), cf.Value("E","right"));
        cout << "Flying Back with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("E","channel")), VALUE(rel_pwm));
}

void naza_interface_manual_c::fly_throttle(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_throttle(speed, cf.Value("T","left"), cf.Value("T","right"));
        cout << "Setting throttle with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("T","channel")), VALUE(rel_pwm));
}

void naza_interface_manual_c::fly_left(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_left(speed, cf.Value("A","left"), cf.Value("A","middle"), cf.Value("A","right"));
        cout << "Flying Left with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("A","channel")), VALUE(rel_pwm));
}

void naza_interface_manual_c::fly_right(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_right(speed, cf.Value("A","left"), cf.Value("A","middle"), cf.Value("A","right"));
        cout << "Flying Right with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("A","channel")), VALUE(rel_pwm));
}

void naza_interface_manual_c::fly_turn_right(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_right(speed, cf.Value("R","left"), cf.Value("R","middle"), cf.Value("R","right"));
        cout << "Turning Right with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("R","channel")), VALUE(rel_pwm));
}

void naza_interface_manual_c::fly_turn_left(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_left(speed, cf.Value("R","left"), cf.Value("R","middle"), cf.Value("R","right"));
        cout << "Turning Left with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("R","channel")), VALUE(rel_pwm));
}

void naza_interface_manual_c::set_neutral(ConfigFile &cf, PCA9685 &pca9685){
		fly_back(cf, pca9685, 0);
		fly_throttle(cf, pca9685, 0);
		fly_right(cf, pca9685, 0);
		fly_turn_right(cf, pca9685, 0);
}

void naza_interface_manual_c::recalibrate(ConfigFile &cf, PCA9685 &pca9685){

		cout << "Resetting all channels!" << " \n";
		set_neutral(cf, pca9685);
		sleep(1);

		cout << "Recalibration of channel A (1/2)" << " \n";
		pca9685.Write(CHANNEL(cf.Value("A","channel")), VALUE(cf.Value("A","left")));
		sleep(1);
		cout << "Recalibration of channel A (2/2)" << " \n";
		pca9685.Write(CHANNEL(cf.Value("A","channel")), VALUE(cf.Value("A","right")));

		sleep(1);
		cout << "Recalibration of channel E (1/2)" << " \n";
		pca9685.Write(CHANNEL(cf.Value("E","channel")), VALUE(cf.Value("E","left")));
		sleep(1);
		cout << "Recalibration of channel E (2/2)" << " \n";
		pca9685.Write(CHANNEL(cf.Value("E","channel")), VALUE(cf.Value("E","right")));

		sleep(1);
		cout << "Recalibration of channel T (1/2)" << " \n";
		pca9685.Write(CHANNEL(cf.Value("T","channel")), VALUE(cf.Value("T","left")));
		sleep(1);
		cout << "Recalibration of channel T (2/2)" << " \n";
		pca9685.Write(CHANNEL(cf.Value("T","channel")), VALUE(cf.Value("T","right")));

		sleep(1);
		cout << "Recalibration of channel R (1/2)" << " \n";
		pca9685.Write(CHANNEL(cf.Value("R","channel")), VALUE(cf.Value("R","left")));
		sleep(1);
		cout << "Recalibration of channel R (2/2)" << " \n";
		pca9685.Write(CHANNEL(cf.Value("R","channel")), VALUE(cf.Value("R","right")));
}

int naza_interface_manual_c::calc_pwm_gradient_right(int speed_in_perc,int left, int middle, int right){
        float gradient = 0;
	if(middle>right){
		gradient=middle-right;
        	gradient=gradient/100;
        	gradient=gradient*speed_in_perc;
        	gradient=middle-gradient;
	} else if(right>middle){
		gradient=right-middle;
		gradient=gradient/100;
		gradient=gradient*speed_in_perc;
		gradient=middle-gradient;
	}
	return gradient;
}


int naza_interface_manual_c::calc_pwm_gradient_left(int speed_in_perc,int left, int middle, int right){
        float gradient = 0;
        if(middle>left){
                gradient=middle-left;
                gradient=gradient/100;
                gradient=gradient*speed_in_perc;
                gradient=gradient+middle;
        } else if(left>middle){
                gradient=left-middle;
                gradient=gradient/100;
                gradient=gradient*speed_in_perc;
                gradient=gradient+middle;
        }
        return gradient;
}

int naza_interface_manual_c::calc_pwm_gradient_throttle(int speed_in_perc,int left, int right){
        float gradient = 0;
        if(right>left){
                gradient=right-left;
		gradient=gradient/100;
                gradient=gradient*speed_in_perc;
		gradient=gradient+left;
        } else if(right<left){
                gradient=left-right;
                gradient=gradient/100;
                gradient=gradient*speed_in_perc;
                gradient=gradient+right;
        }
        return gradient;
}
