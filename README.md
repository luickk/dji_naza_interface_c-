# DJI Naza V2 C++ PWM Interface

A C++ interface for Raspberry to interact with DJI Naza V2 Flight controller. To generate the PWM signal it uses the [PWM/Servo Driver - I2C interface - PCA9685](https://www.adafruit.com/product/815). The lib consists of two different section, manual and autonomous, manual offers standard function to controll the drone, autonomous provides functions which require a serial connection with the Naza V2 to fly for example to differnt waypoints and is highly experimental.

Setup
-------------------

### Installation

> - `git clone https://github.com/MrGrimod/dji_naza_interface_c-.git` <br>
Clone the project 

> - `cd dji_naza_interface_c-`<br>

> - `make`<br>
Build the library's share object file.

> - `make install`<br>
Install config and Headers to include dir  

### Configuration & Calibration (required)

To make the library work you need to configure the library's config file (`/etc/naza/pwm_config.txt`) <br>
Each variable (left,middle,right) defines the transmitters throttle endpoint stick location. To find them you need to open your Naza Assistant and go to `Rc` section where you have to recalibrate the Naza for your transmitter. Next, start `examples/mod_pwm/` and find the fitting values for the throttle endpoints of left, right and "middle" value for each channel and add them to `pwm_config`.

### Library functions
	
#### Manual:

- fly_throttle: <br>
Sets the drone throttle for all motors. <br>
*Corresponds to channel T*

- fly_forward: <br>
Lets the drone fly forward <br>
*Corresponds to channel E*

- fly_back: <br>
Lets the drone fly backwards <br>
*Corresponds to channel E*

- fly_left: <br>
Lets the drone fly sideways left <br>
*Corresponds to channel A*

- fly_right: <br>
Lets the drone fly sideways right <br>
*Corresponds to channel A*

- fly_turn_right: <br>
Lets the drone turn right <br>
*Corresponds to channel R*

- fly_turn_left: <br>
Lets the drone turn left <br>
*Corresponds to channel R*
	
- set_neutral: <br>
Sets all stick positions to neutral.

- recalibrate: <br>
Moves all sticks to throttle endpoints

- set_flight_mode: <br>
Sets the flight mode. You can select between: `gps, failsafe, selectable`
*Corresponds to channel U*

- arm_motors: <br>
**Arms the motors**

### Usage

After successful installation you can include the header files `#include "libnaza/naza_interface_manual.h"` <br>
in your own project and link libnaza by using `-lnaza` flag.

### Examples/Tools

> Usage:
> 
> Build: `./rebuild` <br> Start: `./<tool>`

#### -  flight_sim
Command Line tool to test and debug the functionallity of basic functions of the project.

CMD commands:
*forward,back,throttle,left,right,tright,tleft,flm,neutral,arm*

#### -  mod_pwm
Command Line tool to manually set relative PWM pulse lengths for certain channels

#### -  recalibrate
Tool to calibrate the Naza V2. Start the calibration process in the Naza V2 Assistant Software, then start the recalibration tool and wait until it's done setting the endpoints for all channels.

### Wiring

Connect the PCA9685 over I2C with your raspberry pi and the Naza V2 input channels with the different output channels of the PCA9685.

Dependencies
-------------------

> - bcm2835 <br>
    `wget http://www.open.com.au/mikem/bcm2835/bcm2835-1.49.tar.gz` <br>
    `tar xvfz bcm2835-1.49.tar.gz` <br>
    `cd bcm2835-1.49 `<br>
    `./configure `<br>
    `make `<br>    
    `sudo make install `<br>

> - WiringPi

Pwm Reference
-------------------

The Naza V2 can adapt to different controll interfaces. PWM, PPM and S-Bus are possible.
Here I will focus on PWM since that is the one I chose to use to communicate. It's one of the easiest
ways to communicate with the Naza.

PWM input signal: <br> 
Hz: 50 <br>
Pulse: 0.5-2.5 ms <br>

To generate a proper signal you need to calculate the relative pulse length. For that you need two other values which represent the overall pulse period and the pulse length. The difference of both mustn't be greater than the period itself. The period is decomposed in 4096 values which is equivalent to a 12 Bit accuracy (2^12). So the difference of both of those values mustn't be greater than 4096. This relative pulse length can be calculated by multiplying the Hz rate, the period length and the pulse length together.

    50Hz:
        
        50Hz* 0.0005s * 4096 = 102 (relative pulse length) 
    
        50Hz* 0.0025s * 4096 = 512 (relative pulse length) 
    
To summarize, to control the Naza V2 we need a relative pulse length that reaches from 102-512 (depends on calibration).
