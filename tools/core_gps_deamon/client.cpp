#include "client.h"

using namespace std;

Client::Client() {
  this->name = (char *) malloc(MAX_NAME_LENGHT+1);
}

void Client::SetName(const char *name) {
  //Copies at most MAX_NAME_LENGHT + 1 (including '\0')
  snprintf(this->name, MAX_NAME_LENGHT+1, name);
}

void Client::SetId(int id) {
  this->id = id;
}
