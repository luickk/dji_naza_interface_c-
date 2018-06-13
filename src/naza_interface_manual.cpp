#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "naza_interface_manual.h"
#include "PCA9685/pca9685.h"

void naza_interface_manual::configure_pins(int A, int E, int T, int R, int U){
	uint16_t OnValue, OffValue;

	PCA9685 pca9685;

	pca9685.SetFrequency(100);

	pca9685.SetFullOn(CHANNEL(16), true); 					// Channel 0 Full On

	pca9685.Write(CHANNEL(16), VALUE(PCA9685_VALUE_MAX/2));	// Channel 1, Duty Cycle = 50 %

	pca9685.SetFullOff(CHANNEL(16), true); 					// Channel 0 Full Off
}
void naza_interface_manual::fly_forward(int speed){

}
void naza_interface_manual::fly_backward(int speed){

}
void naza_interface_manual::fly_up(int speed){

}
void naza_interface_manual::fly_down(int speed){

}
void naza_interface_manual::fly_left(int speed){

}
void naza_interface_manual::fly_right(int speed){

}
