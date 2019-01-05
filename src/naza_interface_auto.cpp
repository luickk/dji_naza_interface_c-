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
// Returns true if x is in range [low..high], else false
bool naza_interface_auto_c::inRange(unsigned low, unsigned high, unsigned x)
{
    return  ((x-low) <= (high-low));
}
double naza_interface_auto_c::_ftod(float fValue)
{
    char czDummy[30];
    sprintf(czDummy,"%9.5f",fValue);
    double dValue = strtod(czDummy,NULL);
    return dValue;
}
double naza_interface_auto_c::distance(double lat1, double lon1, double lat2, double lon2) {

	// Convert degrees to radians
	lat1 = lat1 * M_PI / 180.0;
	lon1 = lon1 * M_PI / 180.0;

	lat2 = lat2 * M_PI / 180.0;
	lon2 = lon2 * M_PI / 180.0;

	// radius of earth in metres
	double r = 6378100;

	// P
	double rho1 = r * cos(lat1);
	double z1 = r * sin(lat1);
	double x1 = rho1 * cos(lon1);
	double y1 = rho1 * sin(lon1);

	// Q
	double rho2 = r * cos(lat2);
	double z2 = r * sin(lat2);
	double x2 = rho2 * cos(lon2);
	double y2 = rho2 * sin(lon2);

	// Dot product
	double dot = (x1 * x2 + y1 * y2 + z1 * z2);
	double cos_theta = dot / (r * r);

	double theta = acos(cos_theta);

	// Distance in Metres
	return r * theta;
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

void naza_interface_auto_c::turn_to_deg(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, double deg, int* live_heading){
  naza.fly_turn_right(cf, pca9685, 20);
  while(1){
    if(inRange(deg-10,deg+10, (uint)live_heading)){
      naza.fly_turn_right(cf, pca9685, 0);
      break;
    }
  }
}
void naza_interface_auto_c::fly_to_gps_pos(ConfigFile &cf, PCA9685 &pca9685, naza_interface_manual_c naza, float lat, float lon,
                                          float* live_lat, float* live_lon, int* live_heading){
  // calc heading
  float begin_lat1, begin_lon1, begin_lat2, begin_lon2;
  begin_lat1 = *live_lon;
  begin_lon1 = *live_lat;
  begin_lat2 = lat;
  begin_lon2 = lon;
  float londif, head, lon1, lon2, lat1, lat2, finalans, finalans2, final_heading;
  lat2=(begin_lat2*3.14159)/180;
  lon2=(begin_lon2*3.14159)/180;
  lat1=(begin_lat1*3.14159)/180;
  lon1=(begin_lon1*3.14159)/180;
  londif=lon2-lon1;

  head=atan2((sin(londif)*cos(lat2)),((cos(lat1)*sin(lat2))-(sin(lat1)*cos(lat2)*cos(londif)))) ;
  finalans=(head*180)/3.14159;
  finalans2=0;
  if(finalans<=0)
  {
    finalans2=finalans+360;
    final_heading= finalans2;
  } else {
    final_heading= finalans;
  }
  // done calc heading
  int distance_to_dest;
  turn_to_deg(cf, pca9685, naza, (double)final_heading, live_heading);
  naza.fly_forward(cf, pca9685, 20);
  while(1){
    distance_to_dest = distance(_ftod(*live_lat), _ftod(*live_lon), _ftod(begin_lat2), _ftod(begin_lon2));
    if(distance_to_dest < 20){
      naza.fly_forward(cf, pca9685, 0);
      break;
    }
  }
}
