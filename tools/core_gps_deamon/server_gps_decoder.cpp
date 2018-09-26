#include "tcp_raw/server.h"

using namespace std;

void *Server::gpsDataStream(void *args){
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
  std::string gpsData = "";
  char buffer[1024];
  uint8_t decodedMessage = 0 ;
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
        decodedMessage = NazaDecoder.decode(serialGetchar (fd));
        gpsData = std::to_string(round(NazaDecoder.getNumSat())) + "," + std::to_string(NazaDecoder.getLat()) + "," + std::to_string(NazaDecoder.getLon()) + "," + std::to_string(round(NazaDecoder.getHeadingNc())) + "," + std::to_string(NazaDecoder.getGpsAlt()) + " \n";
        //std::cout << "GPS Sats: " << round(NazaDecoder.getNumSat()) << ", Lat: " << NazaDecoder.getLat() << ", Long: " << NazaDecoder.getLon() << ", Heading: " << round(NazaDecoder.getHeadingNc()) << ", Alt: " << NazaDecoder.getGpsAlt() << " \n";
        strncpy(buffer, gpsData.c_str(), sizeof(buffer));
        // sending GPS data to all clients
        Server::SendToAll(buffer);
    }
  }
	printf ("\n") ;
}
