# 8051 Air Quality Monitoring System with Temperature and Gas Sensors
This project implements an air quality monitoring system using an 8051 microcontroller.
The system monitors the temperature and pollution using a temperature and a gas sensor, respectively.
The data is then displayed on a 16x2 LCD.
Other contributors: @Axy2003 @Ayush180204 @Manishkumar1062

***Hardware Requirements:***
- 8051 Microcontroller
- 16x2 LCD Display
- Temperature Sensor
- Gas Sensor
- ADC (Analog-to-Digital Converter) (optional, can be internal to the microcontroller)
- LEDs (2)
- Resistors (as required for circuit)

***Software Requirements:***
* Keil uVision (or similar IDE for 8051)
* [stcgal](https://github.com/grigorig/stcgal) (Open-source tool for flashing STC microcontrollers)

***Description:***
The code utilizes several functions to manage the LCD display, sensor data acquisition, and LED control.

_Main Function:_
Initializes LEDs, LCD, and ADC (if external).
Continuously reads sensor values and displays them on the LCD.
Controls LEDs based on the Gas sensor threshold.

_LCD Functions:_
+ LCD_Ready(): Checks if the LCD is ready to receive data.
+ LCD_CMD(): Sends a command to the LCD.
+ LCD_DATA(): Sends data to the LCD.
+ LCD_init(): Initializes the LCD display.
+ convert_display_LCD(): Converts a float value (Gas sensor voltage) to a string with two decimal places for LCD display.

_Sensor Functions:_
+ display_temp(): Displays the temperature sensor data on the LCD and controls LED_1.
+ display_gas(): Displays the gas sensor data on the LCD, controls LED_2 based on a threshold, and performs a delay.

***Notes:***
+ The code assumes a specific LCD pin configuration and instruction set. You might need to modify it based on your LCD model.
+ The ADC configuration and data reading might need adjustments depending on your specific ADC implementation (internal or external).
+ The threshold value for the gas sensor can be adjusted.

***How to Use:***
1. Connect the hardware components.
2. Compile the code using your preferred 8051 IDE.
3. Download the compiled code to your microcontroller using stcgal.
   stcgal is an open-source tool available on GitHub that can be used to program STC microcontrollers. Refer to the stcgal documentation for usage instructions specific to your system.[^1]
4. Power on the system and observe the LCD display.

***Further Development:***
- Implement functionalities based on the sensor readings (e.g., opening windows, turning on air conditioning, etc.).
- Integrate communication protocols for remote monitoring or data logging.
- Enhance the user interface with additional displays or menus.

[^1]: We used the Keil IDE to create a hex file from the C Code, and dumped that to the 8051 microcontroller using the `stcgal -p {PORTNAME} {HEXFILEPATH}` command.
