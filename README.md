# arduino-letsdestroybulbs
Arduino project that will toggle an AC device (light bulbs) infinitely until they break.  It will count the number of times each bulb has been toggled, and uses current sensors to determine if the bulb is pulling current (is it broken?).  All details are displayed on a 20x4 LCD display and interaction is provided with two buttons and an active buzzer. 

It utilizes the following hardware component and electrical components:

* 1 x Arduino UNO (other Arduino's should as long as there are enough outputs and inputs)
* 1 x I2C 20x4 LCD
* 1 x 4-Channel Relay
* 4 x ACS712 Current Sensor
* 1 x DC Voltage Regulator
* 4 x Medium Light Bulb Sockets
* 1 x 12V DC Power Supply
* 2 x 10K Resisters
* 1 x 2222 Transistor
* 2 x Mini Buttons
* 1 x Active Buzzer

It depends on the following published Arduino libraries:

* [ACS712](https://github.com/rkoptev/ACS712-arduino)
* [Relay](https://github.com/rafaelnsantos/Relay)
* [AceButton](https://github.com/bxparks/AceButton)
* [LiquidCrystal_PCF8574](http://www.mathertel.de/Arduino/LiquidCrystal_PCF8574.aspx)
