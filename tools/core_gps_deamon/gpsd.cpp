#include <iostream>
#include <websocketpp/server.hpp>
#include <wiringSerial.h>
#include <wiringPi.h>

#include "libnaza/pca9685.h"
#include "libnaza/naza_serial_gps.h"
#include "web_socket/broadcast_server.cpp"
#include "tcp_raw/mythread.h"
#include "tcp_raw/server.h"
#include "tcp_raw/client.h"

using namespace std;

int main(int argc, char* argv[]) {

  /*
  Config
  */
  int tcp_rawPort = 30666;
  int web_socketPort = 9002;
  /*
  Config
  */

  /*
  Websockets
  */
  broadcast_server websocket;
  // Start a thread to run the processing loop
  thread m_proc(bind(&broadcast_server::process_messages,&websocket));
  // Run the asio loop with the main thread
  thread tb(bind(&broadcast_server::run,&websocket, web_socketPort));
  cout << "WebSocket Broadcast Server running on port " << web_socketPort << endl;
  /*
  Websockets
  */

  /*
  Raw TCP sockets
  */
  Client *c;
  Server *s;
  MyThread *t;
  t = new MyThread();
  s = new Server(tcp_rawPort);
  c = new Client();
  // creating gps data decoding thread. -> server_gps_decoder.cpp
  cout << "TCP Socket Broadcast Server running on port " << tcp_rawPort << endl;
  //Main loop
  thread aad(bind(&Server::AcceptAndDispatch, std::ref(s)));
  /*
  Raw TCP sockets
  */

  /*
  Serial GPS reading
  */
  int fd;
	int count;
	unsigned int nextTime;
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
      strncpy(buffer, gpsData.c_str(), sizeof(buffer));
        // sending GPS data to all clients
        if (clock()%100==0){
          //std::cout << "GPS Sats: " << round(NazaDecoder.getNumSat()) << ", Lat: " << NazaDecoder.getLat() << ", Long: " << NazaDecoder.getLon() << ", Heading: " << round(NazaDecoder.getHeadingNc()) << ", Alt: " << NazaDecoder.getGpsAlt() << " \n";
          Server::SendToAll(buffer);
          websocket.SendToAll(gpsData);
      }
    }
  }
  /*
  Serial GPS reading
  */

  return 0;
}
