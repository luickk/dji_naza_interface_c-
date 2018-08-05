/*
  DJI Naza (v1, v1 Lite, V2) data decoder library
  (c) Pawelsky 20141130
  Not for commercial use

  Refer to naza_decoder_wiring.jpg diagram for proper connection

  The RC PWM input code taken from https://www.instructables.com/id/RC-Quadrotor-Helicopter/step12/Arduino-Demo-PWM-Input/
*/

#ifndef __NAZA_DECODER_LIB_H__
#define __NAZA_DECODER_LIB_H__

#include <stdint.h>
#include<iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include <wiringSerial.h>
#include <wiringPi.h>
#include <errno.h>
#include <string.h>

using namespace std;

#define NAZA_MESSAGE_NONE    0x00
#define NAZA_MESSAGE_GPS     0x10
#define NAZA_MESSAGE_COMPASS 0x20

class NazaDecoderLib
{
  public:
    typedef enum { NO_FIX = 0, FIX_2D = 2, FIX_3D = 3, FIX_DGPS = 4 } fixType_t;

    NazaDecoderLib();

    void getAll(double &lat, double &lon, double &alt, double &speed, double &heading, uint8_t &sats);

    uint8_t decode(int input);
    uint8_t decodeSingle(int input, int &seq);
    double getLat();
    double getLon();
    double getGpsAlt();
    double getSpeed();
    double getHeadingNc();
    uint8_t getNumSat();

    fixType_t getFixType();
    double getCog();
    double getGpsVsi();
    double getHdop();
    double getVdop();
    uint8_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour(); // Note that for time between 16:00 and 23:59 the hour returned from GPS module is actually 00:00 - 7:59.
    uint8_t getMinute();
    uint8_t getSecond();

  private:
    int payload[58];
    int seq;
    int cnt;
    int msgId;
    int msgLen;
    uint8_t cs1; // checksum #1
    uint8_t cs2; // checksum #2
    int16_t magXMin;
    int16_t magXMax;
    int16_t magYMin;
    int16_t magYMax;

    double lon;     // longitude in degree decimal
    double lat;     // latitude in degree decimal
    double gpsAlt;  // altitude in m (from GPS)
    double spd;     // speed in m/s
    fixType_t fix;   // fix type
    uint8_t sat;     // number of satellites
    double headingNc;// heading (not tilt compensated) in degrees
    double cog;     // course over ground
    double gpsVsi;  // vertical speed indicator (from GPS) in m/s (a.k.a. climb speed)
    double hdop;    // horizontal dilution of precision
    double vdop;    // vertical dilution of precision
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    int32_t  decodeLong(uint8_t idx, uint8_t mask);
    int16_t  decodeShort(uint8_t idx, uint8_t mask);
    void     updateCS(int input);

};

extern NazaDecoderLib NazaDecoder;

#endif // __NAZA_DECODER_LIB_H__
