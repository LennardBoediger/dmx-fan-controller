# DMX Fan Controller
Speed controller for two old industrial fans.

https://user-images.githubusercontent.com/11893651/213900107-9a194785-94d3-4e1d-9f15-b6ec5db4715c.mov

<br>
The final installation will use two fans, a powerful fog machine and a stroboscope to create a neat effect.<br>

## Documentation 
The Fans are powerd by three-phase alternating current and come with an 0-10V control line. The lowest possible speed setting during runtime is 1.6V but 2.6V is needed to start them.

The controller board is based on the Arduino Nano (ATmega328).<br>
For the Fan Control line a 0-5V 10Bit DAC is used. The output voltage is then aplified, so that we end up with an 0-10V 10Bit DAC.<br>
To communicate over the DMX-Bus, the board is equipped with an MAX485E RS-485 transceiver.<br>
The DMX channel can be selected using a DIP switch.<br>
Additionally there is an manual control override, which allows the fan to be set to a constant speed.<br>
Mounting holes are M3.
#### Schematic:
![Schematic-v2](https://github.com/LennardBoediger/dmx-fan-controller/blob/main/hardware/fan-controller-pcb/fan-controller-pcb.svg)

## Safety instructions
Please don't die when using large spinning fan blades that are powered by three-phase current.
