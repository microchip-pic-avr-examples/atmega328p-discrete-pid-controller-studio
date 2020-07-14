<!-- Please do not change this html logo with link -->
<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# Discrete PIC Controller on tinyAVR and megaAVR Devices

This repository describes a simple implementation of a discrete Proportional- Integral-Derivative (PID) controller. 
When working with applications where control of the system output due to changes in the reference value or state is needed, implementation of a control algorithm may be necessary. Examples of such applications are motor control, control of temperature, pressure, flow rate, speed, force, or other variables. The PID controller can be used to control any measurable variable, as long as this variable can be affected by manipulating some other process variables. Many control solutions have been used over the time, but the PID controller has become the ‘industry standard’ due to its simplicity and good performance. 

This code example is based on the document [AVR221 - Discrete PID Controller on tinyAVR and megaAVR devices](http://ww1.microchip.com/downloads/en/Appnotes/Atmel-2558-Discrete-PID-Controller-on-tinyAVR-and-megaAVR_ApplicationNote_AVR221.pdf), and will be performed on the ATmega328p device.

## Related Documentation

- [AVR221 - Discrete PID Controller on tinyAVR and megaAVR devices](http://ww1.microchip.com/downloads/en/Appnotes/Atmel-2558-Discrete-PID-Controller-on-tinyAVR-and-megaAVR_ApplicationNote_AVR221.pdf)
- [ATmega328p Device Page](https://www.microchip.com/wwwproducts/en/ATmega328p)

## Software Used

- [Atmel Studio](https://www.microchip.com/mplab/avr-support/atmel-studio-7) 7.0.2397 or later
- [ATmega DFP](http://packs.download.atmel.com/) 1.4.351 or later
- AVR/GNU C Compiler (Built-in compiler) 5.4.0 or later


## Hardware Used

- [ATmega328p](https://www.microchip.com/wwwproducts/en/ATmega328p)
- Customboard
- Alternatively the [ATmega Xplained Mini](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/ATMEGA328P-XMINI) can be used

## Operation

1. Connect the board to the PC.

2. Download the zip file or clone the example to get the source code.

3. Open the .atsln file with Atmel Studio.

4. Build the solution and program the device. Press *Start without debugging* or use CTRL+ALT+F5 hotkeys to run the application for programming the device.

## Conclusion

This code example has illustrated how to create a simple PID controller for tinyAVR and megaAVR devices from Microchip.