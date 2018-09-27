#include <iostream>
#include <websocketpp/server.hpp>

#include "tcp_raw/mythread.h"
#include "tcp_raw/server.h"
#include "tcp_raw/client.h"

#include "web_socket/broadcast_server.cpp"

using namespace std;

int main(int argc, char* argv[]) {

  /* Websockets */
  broadcast_server server_instance;
  // Start a thread to run the processing loop
  thread m_proc(bind(&broadcast_server::process_messages,&server_instance));
  // Run the asio loop with the main thread
  //server_instance.run(9002);
  thread tb(bind(&broadcast_server::run,&server_instance));
  cout << "WebSocket Broadcast Server running on port 90002" << endl;
  /* Websockets */

  /* Raw TCP sockets */
  Client *c;
  Server *s;
  MyThread *t;
  t = new MyThread();
  s = new Server();
  c = new Client();
  // creating gps data decoding thread. -> server_gps_decoder.cpp
  t->Create((void *) Server::gpsDataStream, c);
  cout << "TCP Socket Broadcast Server running on port 30666" << endl;
  //Main loop
  s->AcceptAndDispatch();
  /* Raw TCP sockets */


  return 0;
}
