# DJI Naza V2 C++ PWM Interface

A C++ interface for Raspberry to interact with DJI Naza V2 Flight controller

Dependencies
-------------------

> - bcm2835 <br>
    `wget http://www.open.com.au/mikem/bcm2835/bcm2835-1.49.tar.gz` <br>
    `tar xvfz bcm2835-1.49.tar.gz;` <br>
    `cd bcm2835-1.49; `<br>

> - WiringPi

Pwm Reference
-------------------

### Naza V2 
The Naza V2 can adapt to different controll interfaces. PWM, PPM and S-Bus are possible.
Here I will focus on PWM since that is the one I chose to use to communicate. It's one of the simplest 
ways to communicate with the Naza.

PWM input signal: <br> 
Hz: 100 <br>
Pulse: 0.5-2.5 ms <br>

To generate a proper signal you need to calculate the relative pulse length. For that you need two other values which represent the overall pulse period and the pulse length. The difference of both mustn't be greater than the period itself. The period is decomposed in 4096 values which is equivalent to a 12 Bit accuracy (2^12). So the difference of both of those values mustn't be greater than 4096. This relative pulse length can be calculated by multiplying the Hz rate, the period length and the pulse length together.

    50Hz:
        
        50Hz* 0.0005s * 4096 = 102 (relative pulse length) 
    
        50Hz* 0.0025s * 4096 = 512 (relative pulse length) 
    
    100Hz:
        
        100Hz* 0.0005s * 4096 = 204 (relative pulse length) 
    
        100Hz* 0.0025s * 4096 = 1024 (relative pulse length) 


To summarize, to control the Naza V2 we need a relative pulse length that reaches from 200-1024 (depends on calibration).
