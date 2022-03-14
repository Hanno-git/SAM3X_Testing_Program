# SAM3X_Peripheral_Testing_Program on Microchip Studio

This is a simple peripheral test program for the ATSAM3X8E-CU chip. 

# Everything is not tested
These peripherals were tested using the Arduino Duo board

Tested features:
USART0,DAC,ADC,PIO (Input and Output mode),PWM, multithreading with FREERTOS

Semi tested feature:
TWI (See Test_Results folder for more info)

Untested features:
SPI

The goal of this is just to test each peripheral and confirm that a correct initializing and utilization process was followed

the pins and ports used can be found in pio_init.h




