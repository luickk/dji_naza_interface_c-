# DJI Naza V2 C++ PWM Interface

A C++ interface for Raspberry to interact with DJI Naza V2 Flight controller. To generate the PWM signal it uses the [PWM/Servo Driver - I2C interface - PCA9685](https://www.adafruit.com/product/815). The lib consists of two different section, manual and autonomous, manual offers standard function to controll the drone, autonomous provides functions which require a serial connection with the Naza V2 to fly for example to differnt waypoints and is highly experimental.

## Webinterface 
[The Webinterface](https://github.com/MrGrimod/dji_naza_web_interface) is built on top of this project and uses the tools/ binaries to access the Naza. It's based on PHP and Js Ajax, the PHP scripts directly access the binaries compiled by this project.

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

### Usage

After successful installation you can include the header files `#include "libnaza/naza_interface_manual.h"` <br>
in your own project and link libnaza by using `-lnaza` and `-lwiringPi` flag.

### Wiring

Connect the PCA9685 over I2C with your raspberry pi and the Naza V2 input channels with the different output channels of the PCA9685.

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

#### Autonomous:

- auto_liftoff <br>
Lets the drone take off.

- auto_landing <br>
Lets the drone land.

- fly_to_gps_pos <br>
Lets the drone fly to a certain position.

- turn_to_deg <br>
Lets the drone fly turn to a certain position.

- auto_hover <br>
Lets the drone hover.


### Examples

> Usage:
>
> Build: `./reinstall` <br> Start: `./<tool>`

-  flight_sim <br>
Command Line tool to test and debug the functionallity of basic functions of the project. <br>

CMD commands:<br>
*forward,back,throttle,left,right,tright,tleft,flm,neutral,arm*<br>

-  mod_pwm<br>
Command Line tool to manually set relative PWM pulse lengths for certain channels<br>

-  recalibrate<br>
Tool to calibrate the Naza V2. Start the calibration process in the Naza V2 Assistant Software, then start the recalibration tool and wait until it's done setting the endpoints for all channels.<br>

-  read gps<br>
Tool to decode Serial GPS coming from the Naza GPS module. It inputs the data in a continuous stream of data.  

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

Serial Communication with Naza GPS
-------------------

### Switching to AMA0 (old serial interface)

The BCM2837 on the Raspberry Pi3 , Pi3B+, PiZeroW has 2 UARTs (as did its predecessors), however to support the Bluetooth functionality the fully featured PL011 UART was moved from the header pins to the Bluetooth chip and the mini UART made available on header pins 8 & 10.

This has a number of consequences for users of the serial interface.

The `/dev/ttyAMA0` previously used to access the UART now connects to Bluetooth.
The miniUART is now available on `/dev/ttyS0`.
In the latest operating system software there is a `/dev/serial0` which selects the appropriate device so you can replace `/dev/ttyAMA0` with `/dev/serial0` and use the same software on the Pi3 and earlier models.

Unfortunately there are a number of other consequences:-

The mini UART is a secondary low throughput UART  
  intended to be used as a console.
The mini Uart has the following features: <br>
• 7 or 8 bit operation. <br>
• 1 start and 1 stop bit. <br>
• No parities. <br>
• Break generation. <br>
• 8 symbols deep FIFOs for receive and transmit. <br>
• SW controlled RTS, SW readable CTS. <br>
• Auto flow control with programmable FIFO level. <br>
• 16550 like registers. <br>
• Baudrate derived from system clock. <br>
There is no support for parity and the throughput is limited, but the latter should not affect most uses.

There is one killer feature "Baudrate derived from system clock" which makes the miniUART useless as the this clock can change dynamically e.g. if the system goes into reduced power or in low power mode.<br>

For the GPS Data input stream we need a reliable and fast serial communication interface, so we need to disable miniUART and switch back to the old ttyAMA0 interface.
To do so follow these steps:

1. To disable bluethooth and set `/dev/ttyAM0` to real UART (as before)
Edit the file `/boot/config.txt` and add the following line at the end : <br>

    dtoverlay=pi3-disable-bt
    1
    dtoverlay=pi3-disable-bt

2. Stop the bluetooth service with sudo systemctl disable hciuart and reboot. <br>

3. To switch bluetooth to software UART and set /dev/ttyAM0 to real UART (as before)
Keep in mind that this one will remain possible software problem on bluetooth (software UART), but not on Serial (Hardware) <br>
Edit the file /boot/config.txt and add the following line at the end : <br>

    dtoverlay=pi3-miniuart-bt
    core_freq=250
    1
    2
    dtoverlay=pi3-miniuart-bt
    core_freq=250

4. Edit the file `/lib/systemd/system/hciuart.service` and replace  `/dev/ttyAMA0`  with  `/dev/ttyS0` <br>

5. If you have a system with udev rules that create `/dev/serial0`  and `/dev/serial1` (look if you have these one), and if so use `/dev/serial1` .

Then reboot

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
