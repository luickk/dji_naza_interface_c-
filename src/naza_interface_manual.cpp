#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "naza_interface_manual.h"
#include "pca9685.h"


naza_interface_manual_c::naza_interface_manual_c(){

	std::cout << "Starting Naza Interface";

}

void naza_interface_manual_c::configure_pins(int A, int E, int T, int R, int U){
	PCA9685 pca9685;

	pca9685.SetFrequency(100);

	pca9685.Write(CHANNEL(0), VALUE(350));
}
void naza_interface_manual_c::fly_forward(int speed){

}
void naza_interface_manual_c::fly_backward(int speed){

}
void naza_interface_manual_c::fly_up(int speed){

}
void naza_interface_manual_c::fly_down(int speed){

}
void naza_interface_manual_c::fly_left(int speed){

}
void naza_interface_manual_c::fly_right(int speed){

}
