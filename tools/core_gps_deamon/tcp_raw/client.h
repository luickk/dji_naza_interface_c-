#ifndef _client_h_
#define _client_h_

#include <iostream>

#include <cstdio>
#include <cstdlib>

#define MAX_NAME_LENGHT 20

using namespace std;

class Client {
  public:
    char *name;
    int id;

    //Socket stuff
    int sock;

  public:
    Client();
    void SetName(const char *name);
    void SetId(int id);
};

#endif
