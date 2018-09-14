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

void requestStream(){
	int fd ;
	int count ;
	unsigned int nextTime ;
	if ((fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)
	{
	 fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
	}
	if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
  }
	nextTime = millis () + 300 ;
  while(1)
  {
    if (millis () > nextTime)
    {
			nextTime += 300 ;
      ++count ;
    }
    delay (3) ;

    while (serialDataAvail (fd))
    {
				uint8_t decodedMessage = NazaDecoder.decode(serialGetchar (fd));
				std::cout << "GPS Sats: " << round(NazaDecoder.getNumSat()) << ", Lat: " << NazaDecoder.getLat() << ", Long: " << NazaDecoder.getLon() << ", Heading: " << round(NazaDecoder.getHeadingNc()) << ", Alt: " << NazaDecoder.getGpsAlt() << " \n";
    }
  }
	printf ("\n") ;
}

int main(){
	requestStream();

	return 0;
}
