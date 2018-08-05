#include "libnaza/pca9685.h"
#include "libnaza/naza_serial_gps.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <errno.h>
#include <string.h>

int main(){
	double lat, lon, alt, speed, heading; uint8_t sats;

	NazaDecoder.getAll(lat,lon,alt,speed,heading,sats);
	std::cout << round(sats) << "," << lat << "," << lon << "," << heading << "," << alt << "," << speed << " \n";

	return 0;
}
