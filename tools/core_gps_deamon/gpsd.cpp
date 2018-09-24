#include <iostream>
#include "mythread.h"
#include "server.h"
#include "client.h"

using namespace std;

int main() {
  cout << "Running!" << endl;

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

  return 0;
}
