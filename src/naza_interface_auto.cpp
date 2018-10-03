#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fstream>

#include "naza_interface_auto.h"
#include "naza_interface_manual.h"
#include "pca9685.h"
#include "ConfigFile.h"

using namespace std;

naza_interface_auto_c::naza_interface_auto_c(){}
naza_interface_auto_c::~naza_interface_auto_c(){}

/**
    !!!NOT TESTED YET, HIGHLY EXPERIMENTAL!!!

    auto_liftoff requires the drone NOT to be in the air!
		ONLY USE ON GROUND!

    auto_liftoff sets all control elements to neutral and increases the throttle to 60%
    when the drone is in the air, throttle is reseted to 50% to hover (auto_hover method is called).
*/
void naza_interface_auto_c::auto_liftoff(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, double height){
  naza.set_neutral(cf, pca9685);
  naza.fly_throttle(cf, pca9685, 50);
  sleep(5);
  naza.fly_throttle(cf, pca9685, 60);
  sleep(3);
  auto_hover(cf, pca9685, naza);
}
/**
    !!!NOT TESTED YET, HIGHLY EXPERIMENTAL!!!
    Only use auto_hover in the AIR.

    auto_hover sets all channels to neutral and throttle to 50%
*/
void naza_interface_auto_c::auto_hover(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza){
  naza.fly_back(cf, pca9685, 0);
  naza.fly_throttle(cf, pca9685, 50);
  naza.fly_right(cf, pca9685, 0);
  naza.fly_turn_right(cf, pca9685, 0);
}
/**
    !!!NOT TESTED YET, HIGHLY EXPERIMENTAL!!!
    Only use auto_landing in the AIR.

    auto_landing switches to failsafe mode to land the drone at arming position.
*/
void naza_interface_auto_c::auto_landing(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza){
	naza.set_flight_mode(cf, pca9685, "failsafe");
}
void naza_interface_auto_c::fly_to_gps_pos(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, double lat, double lon, double height){
}
void naza_interface_auto_c::turn_to_deg(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, double deg){
}
