#include <iostream>
#include "mythread.h"
#include "server.h"

using namespace std;

int main() {
  cout << "Running!" << endl;

  Server *s;
  s = new Server();

  //Main loop
  s->AcceptAndDispatch();

  return 0;
}
