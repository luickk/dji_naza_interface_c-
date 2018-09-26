#include <iostream>

#include "tcp_raw/mythread.h"
#include "tcp_raw/server.h"
#include "tcp_raw/client.h"

#include <websocketpp/server.hpp>

using namespace std;

int main() {
  cout << "Running!" << endl;

  /* Raw TCP sockets */
  Client *c;
  Server *s;
  MyThread *t;
  t = new MyThread();
  s = new Server();
  c = new Client();
  // creating gps data decoding thread. -> server_gps_decoder.cpp
  t->Create((void *) Server::gpsDataStream, c);
  //Main loop
  s->AcceptAndDispatch();
  /* Raw TCP sockets */

  /* Websockets */

  /* Websockets */

  return 0;
}
