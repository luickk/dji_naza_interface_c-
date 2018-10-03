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

naza_interface_manual_c::naza_interface_manual_c(){}
naza_interface_manual_c::~naza_interface_manual_c(){}

/**
    init_naza requires the drone NOT to be in the air!
		ONLY USE ON GROUND!

    init_naza sets all control elements to neutral and prints pwm config values.
*/
void naza_interface_manual_c::init_naza(ConfigFile &cf, PCA9685 &pca9685){
	cout << "Initializing Naza Interface Controller \n";

	cout << "-" << "\n";
	cout << "A Channel PWM Values " << "left: " << cf.Value("A", "left") << " middle: " << cf.Value("A", "middle") << " right: " << cf.Value("A", "right") << "\n";
	cout << "E Channel PWM Values " << "left: " << cf.Value("E", "left") << " middle: " << cf.Value("E", "middle") << " right: " << cf.Value("E", "right") << "\n";
	cout << "T Channel PWM Values " << "left: " << cf.Value("T", "left") << " right: " << cf.Value("T", "right") << "\n";
	cout << "R Channel PWM Values " << "left: " << cf.Value("R", "left") << " middle: " << cf.Value("R", "middle") << " right: " << cf.Value("R", "right") << "\n";
	cout << "U Channel PWM Values " << "GPS: " << cf.Value("U", "gps") << " Failsafe: " << cf.Value("U", "failsafe") << " Selectable: " << cf.Value("U", "selectable") << "\n";
	cout << "-" << "\n";

	set_neutral(cf, pca9685);
	cout << "Setting all channels on neutral!" << "\n";
	cout << "---IMPORTANT---" << "\n";
	cout << "   Check channels for command calibration before giving power to motors!" << "\n";
}


/**
    Only use fly_forward in the AIR.

    fly_forward sets channel E to given percentage value
*/
void naza_interface_manual_c::fly_forward(ConfigFile &cf, PCA9685 &pca9685, int speed){
  int rel_pwm=calc_pwm_gradient_right(cf.Value("E","stick_motion"), speed, cf.Value("E","left"), cf.Value("E","middle"), cf.Value("E","right"));
	cout << "Flying Forward with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
	pca9685.Write(CHANNEL(cf.Value("E","channel")), VALUE(rel_pwm));
}

/**
    Only use fly_back in the AIR.

    fly_back sets channel E to given percentage value
*/
void naza_interface_manual_c::fly_back(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_left(cf.Value("E","stick_motion"), speed, cf.Value("E","left"), cf.Value("E","middle"), cf.Value("E","right"));
        cout << "Flying Back with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("E","channel")), VALUE(rel_pwm));
}

/**
    Only use fly_throttle in the air OR on take off.

    fly_throttle sets channel T to given percentage value
*/
void naza_interface_manual_c::fly_throttle(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_throttle(cf.Value("T","stick_motion"), speed, cf.Value("T","left"), cf.Value("T","right"));
        cout << "Setting throttle with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("T","channel")), VALUE(rel_pwm));
}

/**
    Only use fly_left in the AIR.

    fly_left sets channel A to given percentage value
*/
void naza_interface_manual_c::fly_left(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_left(cf.Value("A","stick_motion"), speed, cf.Value("A","left"), cf.Value("A","middle"), cf.Value("A","right"));
        cout << "Flying Left with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("A","channel")), VALUE(rel_pwm));
}

/**
    Only use fly_right in the AIR.

    fly_right sets channel A to given percentage value
*/
void naza_interface_manual_c::fly_right(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_right(cf.Value("A","stick_motion"), speed, cf.Value("A","left"), cf.Value("A","middle"), cf.Value("A","right"));
        cout << "Flying Right with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("A","channel")), VALUE(rel_pwm));
}

/**
    Only use fly_turn_right in the AIR.

    fly_turn_right sets channel R to given percentage value
*/
void naza_interface_manual_c::fly_turn_right(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_right(cf.Value("R","stick_motion"), speed, cf.Value("R","left"), cf.Value("R","middle"), cf.Value("R","right"));
        cout << "Turning Right with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("R","channel")), VALUE(rel_pwm));
}

/**
    Only use fly_turn_left in the AIR.

    fly_turn_left sets channel R to given percentage value
*/
void naza_interface_manual_c::fly_turn_left(ConfigFile &cf, PCA9685 &pca9685, int speed){
        int rel_pwm=calc_pwm_gradient_left(cf.Value("R","stick_motion"), speed, cf.Value("R","left"), cf.Value("R","middle"), cf.Value("R","right"));
        cout << "Turning Left with Relative PWM signal: " << rel_pwm << " which is " << speed << " \n";
        pca9685.Write(CHANNEL(cf.Value("R","channel")), VALUE(rel_pwm));
}

/**
    arm_motors requires the drone NOT to be in the air!
		ONLY USE ON GROUND!

    arm_motors arms the motors and then returns all channels to neutral
*/
void naza_interface_manual_c::arm_motors(ConfigFile &cf, PCA9685 &pca9685){
	cout << "-------- ARMING MOTORS --------" << "\n";
  fly_left(cf, pca9685, 100);
	fly_back(cf, pca9685, 100);
	fly_throttle(cf, pca9685, 0);
	fly_turn_left(cf, pca9685, 100);

	sleep(2);

	set_neutral(cf, pca9685);
}

/**
    Use set_flight_mode to switches between different flight modes.
*/
void naza_interface_manual_c::set_flight_mode(ConfigFile &cf, PCA9685 &pca9685, std::string mode){
    if(mode=="gps"){
			pca9685.Write(CHANNEL(cf.Value("U","channel")), VALUE(cf.Value("U", "gps")));
			cout << "Setting flight mode: " << mode << " \n";
		} else if(mode=="failsafe"){
			pca9685.Write(CHANNEL(cf.Value("U","channel")), VALUE(cf.Value("U", "failsafe")));
			cout << "Setting flight mode: " << mode << " \n";
		} else if(mode=="selectable"){
			pca9685.Write(CHANNEL(cf.Value("U","channel")), VALUE(cf.Value("U", "selectable")));
			cout << "Setting flight mode: " << mode << " \n";
		}
}

/**
    set_neutral requires the drone NOT to be in the air!
		ONLY USE ON GROUND!

    set_neutral sets all channels to neutral including THROTTLE TO 0%
*/
void naza_interface_manual_c::set_neutral(ConfigFile &cf, PCA9685 &pca9685){
		fly_back(cf, pca9685, 0);
		fly_throttle(cf, pca9685, 0);
		fly_right(cf, pca9685, 0);
		fly_turn_right(cf, pca9685, 0);
}

/**
    recalibrate requires the drone NOT to be in the air!
		ONLY USE ON GROUND!

		recalibrate recalibrate all channels to corresponding config values.
*/
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

 		sleep(1);
    cout << "Recalibration of channel U (1/2)" << " \n";
    pca9685.Write(CHANNEL(cf.Value("U","channel")), VALUE(cf.Value("U","gps")));
    sleep(1);
    cout << "Recalibration of channel U (2/2)" << " \n";
    pca9685.Write(CHANNEL(cf.Value("U","channel")), VALUE(cf.Value("U","selectable")));

}

int naza_interface_manual_c::calc_pwm_gradient_right(string stick_motion, int speed_in_perc,int left, int middle, int right){

  float gradient = 0;
	if(stick_motion=="rev"){

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

	} else if(stick_motion=="norm"){

		if(middle<right){
			gradient=middle-right;
	        	gradient=gradient/100;
	        	gradient=gradient*speed_in_perc;
	        	gradient=middle-gradient;
		} else if(right<middle){
			gradient=right-middle;
			gradient=gradient/100;
			gradient=gradient*speed_in_perc;
			gradient=middle-gradient;
		}

	}
	return gradient;
}


int naza_interface_manual_c::calc_pwm_gradient_left(string stick_motion, int speed_in_perc,int left, int middle, int right){
        float gradient = 0;
				if(stick_motion=="rev"){
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

			} else if(stick_motion=="norm"){

        if(middle<left){
                gradient=middle-left;
                gradient=gradient/100;
                gradient=gradient*speed_in_perc;
                gradient=gradient+middle;
        } else if(left<middle){
                gradient=left-middle;
                gradient=gradient/100;
                gradient=gradient*speed_in_perc;
                gradient=gradient+middle;
        }

			}
        return gradient;
}

int naza_interface_manual_c::calc_pwm_gradient_throttle(string stick_motion, int speed_in_perc,int left, int right){
        float gradient = 0;
				if(stick_motion=="rev"){
	        if(right>left){
	          gradient=right-left;
						gradient=gradient/100;
	          gradient=gradient*speed_in_perc;
						gradient=left-gradient;
	        } else if(right<left){
	          gradient=left-right;
	          gradient=gradient/100;
	          gradient=gradient*speed_in_perc;
	          gradient=left-gradient;
	        }
				} else if(stick_motion=="norm"){
					if(right<left){
						gradient=left-right;
						gradient=gradient/100;
						gradient=gradient*speed_in_perc;
						gradient=right+gradient;
					} else if(right>left){
						gradient=right-left;
						gradient=gradient/100;
						gradient=gradient*speed_in_perc;
						gradient=right-gradient;
					}
				}
        return gradient;
}
