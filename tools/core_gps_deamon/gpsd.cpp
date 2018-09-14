#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <mutex>
#include <queue>

#include "libnaza/pca9685.h"
#include "libnaza/naza_serial_gps.h"
#include "thread_safe_queue.cpp"

using namespace std;

void *clientHandler(void *);
void *gpsDataStream(void *);

static int connFd;

ThreadSafeQueue<std::string> sq[50];

int main(int argc, char* argv[])
{
    int pId, portNo, listenFd;
    socklen_t len; //store size of the address
    bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;

    pthread_t threadA;
    pthread_t threadGPS;

    if (argc < 2)
    {
        cerr << "Syntam : ./server <port>" << endl;
        return 0;
    }

    portNo = atoi(argv[1]);

    if((portNo > 65535) || (portNo < 2000))
    {
        cerr << "Please enter a port number between 2000 - 65535" << endl;
        return 0;
    }

    // start gps data thread
    pthread_create(&threadGPS, NULL, gpsDataStream, NULL);

    //create socket
    listenFd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }

    bzero((char*) &svrAdd, sizeof(svrAdd));

    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);

    //bind socket
    if(bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        cerr << "Cannot bind" << endl;
        return 0;
    }

    listen(listenFd, 5);

    len = sizeof(clntAdd);

    int thread_count = 0;
    while (true)
    {
        cout << "Listening" << endl;

        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);
        thread_count++;

        if (connFd < 0)
        {
            cerr << "Cannot accept connection" << endl;
            return 0;
        }
        else
        {
            cout << "Connection successful" << endl;
        }
        pthread_create(&threadA, NULL, clientHandler, (void *)&thread_count);
    }
}

void *clientHandler (void *args)
{
    int local_thread_count = *((int *)args);
    cout << "Thread No: " << local_thread_count << endl;
    bool loop = false;
    int size = 0;
    string res = "";
    while(!loop)
    {
      size = sq[local_thread_count].dequeue(res);
      cout << local_thread_count << endl;
      write(connFd, res.c_str(), strlen(res.c_str()));
      usleep(500);
    }
    cout << "\nClosing thread and conn" << endl;
    close(connFd);
}

void *gpsDataStream (void *args)
{
  cout << "GPS Thread" << endl;
  bool loop = false;

  // -- Reading GPS from Serial port

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

  // -- Reading GPS from Serial port END
  while(!loop)
  {
      nextTime = millis () + 300 ;

      if (millis () > nextTime)
      {
        nextTime += 300 ;
        ++count ;
      }
      delay (3) ;
      int i = 0;
      while (serialDataAvail (fd))
      {
          uint8_t decodedMessage = NazaDecoder.decode(serialGetchar (fd));
          // sats, lat, lon, heading, alt
          string gpsDataString = to_string(round(NazaDecoder.getNumSat())) + "," + to_string(NazaDecoder.getLat()) + "," + to_string(NazaDecoder.getLon()) + "," + to_string(round(NazaDecoder.getHeadingNc())) + "," + to_string(NazaDecoder.getGpsAlt()) + " \n";
          char buffer[1024];
          strncpy(buffer, gpsDataString.c_str(), sizeof(buffer));
          buffer[sizeof(buffer) - 1] = 0;
          usleep(500);
          for (i=0; i<50; i++)
          {
            sq[i].enqueue(buffer);
          }
      }
  }
  cout << "\nClosing thread and conn" << endl;
  close(connFd);
}
