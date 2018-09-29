#ifndef _server_h_
#define _server_h_

#include <iostream>
#include <vector>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>

#include "mythread.h"
#include "client.h"

using namespace std;

class Server {

  private:
    static vector<Client> clients;

    //Socket stuff
    int serverSock, clientSock;
    struct sockaddr_in serverAddr, clientAddr;
    char buff[256];

  public:
    Server(int p);
    void AcceptAndDispatch();
    static void SendToAll(char *message);
    static void * HandleClient(void *args);

  private:
    static void ListClients();
    static int FindClientIndex(Client *c);
};

#endif
