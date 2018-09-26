#include "mythread.h"

using namespace std;

//Need to actually "allocate" static member
pthread_mutex_t MyThread::mutex;

MyThread::MyThread() {
}

int MyThread::Create(void *Callback, void *args) {
  int tret=0;

  //Supercreepy typecast
  tret = pthread_create(&this->tid, NULL, (void *(*)(void *))Callback, args);

  if(tret) {
    cerr << "Error while creating threads." << endl;
    return tret;
  }
  else {
    return 0;
  }
}

int MyThread::Join() {
  pthread_join(this->tid, NULL);
  return 0;
}

int MyThread::InitMutex() {

  if(pthread_mutex_init(&MyThread::mutex, NULL) < 0) {
    cerr << "Error while initializing mutex" << endl;
    return -1;
  }
  else {
    return 0;
  }
}

/*
    LockMutex():
		Blocks until mutex becomes available
*/
int MyThread::LockMutex(const char *identifier) {
  if(pthread_mutex_lock(&MyThread::mutex) == 0) {
    return 0;
  }
  else {
   cerr << "Error while " << identifier << " was trying to acquire the lock" << endl;
   return -1;
  }
}

int MyThread::UnlockMutex(const char *identifier) {
  if(pthread_mutex_unlock(&MyThread::mutex) == 0) {
    return 0;
  }
  else {
   cerr << "Error while " << identifier << " was trying to release the lock" << endl;
   return -1;
  }
}
