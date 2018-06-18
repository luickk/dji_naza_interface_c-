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

naza_interface_manual_c::naza_interface_manual_c(){
	cout << "Initializing Naza Interface Controller \n";
	string pwm_config_path = "/etc/naza/pwm_config.txt";
	cout << "PWM Config path:" << pwm_config_path << "\n";
	ifstream pwm_conf(pwm_config_path);

	ConfigFile cf(pwm_config_path);
	cout << "-" << "\n";
	cout << "A Channel PWM Values " << "left: " << cf.Value("A", "left") << " middle: " << cf.Value("A", "middle") << " right: " << cf.Value("A", "right") << "\n";
	cout << "E Channel PWM Values " << "left: " << cf.Value("E", "left") << " middle: " << cf.Value("E", "middle") << " right: " << cf.Value("E", "right") << "\n";
	cout << "T Channel PWM Values " << "left: " << cf.Value("T", "left") << " right: " << cf.Value("T", "right") << "\n";
	cout << "R Channel PWM Values " << "left: " << cf.Value("R", "left") << " middle: " << cf.Value("R", "middle") << " right: " << cf.Value("R", "right") << "\n";
	cout << "U Channel PWM Values " << "GPS: " << cf.Value("U", "GPS") << " Failsafe: " << cf.Value("U", "Failsafe") << " Atti: " << cf.Value("U", "Atti") << "\n";
	cout << "-" << "\n";
}


naza_interface_manual_c::~naza_interface_manual_c(){

}

void naza_interface_manual_c::fly_forward(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_right(speed, cf.Value("E","left"), cf.Value("E","middle"), cf.Value("E","right"));
	cout << "Flying Forward with Relative PWM signal: " << rel_pwm << " which is " << speed << "% \n";
	pca9685.Write(CHANNEL(1), VALUE(rel_pwm));
}

void naza_interface_manual_c::fly_backward(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_left(speed, cf.Value("E","left"), cf.Value("E","middle"), cf.Value("E","right"));
        cout << "Flying Backward with Relative PWM signal: " << rel_pwm << " which is " << speed << "% \n";
        pca9685.Write(CHANNEL(1), VALUE(rel_pwm));
}

int naza_interface_manual_c::calc_pwm_gradient_right(int speed_in_perc,int left, int middle, int right){
        int gradient = 0;
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
        int gradient = 0;
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

