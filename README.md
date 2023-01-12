# ARDUINO AUTOPILOT FOR SMALL BOATS - short description

This project was created with the goal of creating a low-cost device for automatic navigation using the arduino mega microcontroller interface. The picture shows the finished device with all parts installed in the control box. 4 buttons installed on the control box, 1 rotary encoder and a remote control with 4 buttons are used to set and control the device. Steering is provided by the use of a stepper motor and a threaded rod, which enables the steering wheel to be turned by approximately 5 degrees in each direction.

![image](https://user-images.githubusercontent.com/59554693/210934740-e4eb608b-85bb-4bcf-9f62-ae426279ec6d.png)

The power supply of the microcontroller and the stepper motor driver are separate. The main power source is the ship's batteries, which are charged using photovoltaic panels. The voltage on the accumulators is between 13 and 14 V which is fine for the stepper motor driver, but too high for the arduino microcontroller. Therefore, powermodule DC-DC 15-80 to 12V step-down power supply converter is used to power the microcontroller. Since the stepper motor driver is built into the control box, the heatsink part faces outwards to promote heat dissipation and reduce the heating of the microcontroller. The temperature in the control box is continuously controlled using a thermistor. In the event that the temperature exceeds a critical value (which can be adjusted in the device settings), an alarm is triggered and the operation of the stepper motor is disabled.The parts installed in the control box are shown in the picture:

![image](https://user-images.githubusercontent.com/59554693/210935334-3d9cb4bf-1560-4f62-a52b-f1e53331b489.png)

# Settings and device management are achieved through the menu system shown in the images below.

## Init menu layout
Used for the initial positioning of the steering wheel and to setting the system.

![image](https://user-images.githubusercontent.com/59554693/210937331-6c9e9ce8-ae55-45db-87f3-193b9283c990.png)

## Main manu layout
Used for the function of anchoring, manual control and automatic control of the boat.

![image](https://user-images.githubusercontent.com/59554693/210937401-84aa4125-d78c-44be-9deb-f19b6d336759.png)

# Programming Arduino 

## Program flow diagrams
The simplified flow charts shown below are only a general indication of how the program works. The program modules contains a lot of details that significantly affect the functionality of the device.
  
### ** Main program flow diagram: **
![image](https://user-images.githubusercontent.com/59554693/211130463-953db1b7-dd84-49c4-98d6-2a1d53a4f874.png)

### ** Initialization flow diagram: **
![image](https://user-images.githubusercontent.com/59554693/211297155-72839fae-fb72-4347-af66-56d695ba8d17.png)


### ** Flow diagram for "manually" setting the neutral position of the rudder: **
Since the use of encoders is not provided for determining the initial position of the rudder, it is necessary to "manually" adjust the neutral position of the rudder before starting the automatic operation of the autopilot. 
  
![image](https://user-images.githubusercontent.com/59554693/211052769-49a9c543-280b-4893-976e-ae1ac76a6715.png)

### ** Flow diagram for system parameter settings: **
Note: The program enables the setting of more system parameters than shown in the flowchart.
![image](https://user-images.githubusercontent.com/59554693/211130668-4012870e-8b3b-4ea5-af9a-32a5b4d1507e.png)

### ** Flow diagram for autopilot main menu: **
The main menu consists of six possible choices, two of which are hidden. The most important functionalities are navigation according to the given course and navigation according to the given destination. Applying navigation to a set course does not take into account drift due to wind and sea currents, making the final destination unreliable. In this case, the autopilot tries to maintain the given course. By applying navigation to the destination (set longitude and latitude of the destination), the course is corrected during navigation, i.e. calculated based on the current position and the position of the destination. This method of navigation is reliable, and the error depends on the precision of the GPS device (for cheaper devices, it is of the order of 10 m).
The next functionality is the anchoring function. By calling this function at the moment of lowering the anchor, the current GPS position is recorded and the permitted deviation from the current position can be entered. If during the stay on the anchor there is a greater deviation than allowed (the anchor has loosened), an alarm (buzzer) is activated.
By starting the microcontroller, multiple points of interest (POIs) stored on the SD card are loaded. The program enables the entry of one custom POI that can be used within the navigation function to the destination (fourth function in the main menu).
The fifth hidden function refers to the manual control of the boat, which is achieved by pressing the button of the rotary encoder. Calling this function enables control using the buttons on the control box or using the remote control.
The sixth function refers to the return to the home menu.

![image](https://user-images.githubusercontent.com/59554693/211131000-7295a04a-e611-4c4c-8648-82b35c23a649.png)

### ** Flow diagram for anchoring function: **
Starting the anchoring function automatically records the current GPS location. Then the input of the permitted deviation from the current position is requested. After that, monitoring of the position on the anchor is started. A circle is drawn on the screen, the radius of which represents the permissible deviation from the anchoring location (center point). The current position is plotted on the LCD screen and refreshed every 5 seconds. If the distance of the current location from the anchoring location is greater than the permitted deviation, an alarm is activated.
![image](https://user-images.githubusercontent.com/59554693/211141601-e3155ee8-b5a8-4d56-a90b-7f06efdc7cca.png)

### ** Flow diagram for input custom POI coordinates: **
Custom POI can be entered by entering two digits at a time to speed up coordinate entry. Coordinates are entered in decimal notation. Each entry must be confirmed by pressing the button on the rotary encoder. The program provides for the input of coordinates with 6 decimal places, although the flow diagram shows the input of only 4 decimal places.

![image](https://user-images.githubusercontent.com/59554693/211141983-233eaac6-8fb8-4ec0-b40f-9298b06c33f1.png)

### ** Flow diagram for navigation to destination (point of interest): **
Navigation towards the desired destination is done by first choosing a destination from the available database stored on the SD card or a custom POI that has been previously defined. After selecting the destination, the current location is read and the course towards the destination is calculated. If the speed of the boat is higher than the minimum required, which is defined in the program settings, it is checked whether the deviation of the current course from the budget is greater than the allowed tolerance. If the course deviation is greater, the rudder is turned in the appropriate direction. The process is repeated after 5 seconds. If the deviation of the course from the budget is less than allowed, the rudder returns to the neutral position. In the loop there is also the possibility to return to the main menu. In this way, the maximum precision of the navigation path is ensured, regardless of the wind and sea currents, because the course is recalculated every 5 seconds ("course over ground").

![image](https://user-images.githubusercontent.com/59554693/211142266-2d6b6457-d828-48ff-a800-173e729412fe.png)

### ** Flow diagram for navigation to desired course: **
Navigation towards the desired direction (course) starts with entering the numerical value of the desired course. After that, the current GPS position (previous position) is read. Then there is a pause of 5 seconds after which the new current GPS position (next position) is loaded. Based on the two read positions, the current exchange rate is calculated. If the speed of the boat is higher than the minimum required (defined in the system settings), the current and desired course are compared. If the deviation is greater, the rudder is turned in the appropriate direction. Then the next position is declared as the previous position and the loop is repeated. If the deviation is less than allowed, the rudder returns to the neutral position. In the loop, it is possible to return to the main menu.

![image](https://user-images.githubusercontent.com/59554693/211788248-30ffdcad-25c9-40b3-8ee7-e78ee816011d.png)

### ** Flow diagram for manual control: **
Starting the menu for manual control is done by pressing the button on the rotary encoder. This makes it possible to turn the rudder using the buttons on the device housing or using the remote control. The upper two buttons are used to gradually turn the rudder to the left or right, while pressing either of the lower two buttons returns the rudder to the neutral position. In the loop, it is possible to return to the main menu.

![image](https://user-images.githubusercontent.com/59554693/211789087-eb8f9b0f-2d11-4a77-8218-224516f5299a.png)


### ** Used components: **
1. TB6600 Single Axis 4A Stepper Motor Microstep Driver 9~40V Micro-Step - 1Pcs
2. Nema 23 Stepper Motor 3Nm/1.9Nm/1.26Nm 4-lead 2.8A/4.2A - 1Pcs
3. Beitian BN-800 Dual Module with Antenna Compass HMC5883L - 1Pcs
4. Mini 12mm Waterproof Momentary ON/OFF Push Button Round Switch - 4Pcs
5. 12mm Metal Push Button Switch Waterproof LED Light Momentary Latching - 1Pcs
6. 24V / 12V to 5V 5A powermodule DC-DC step-down power supply converter - 1Pcs
7. 315MHz/433MHz 4Buttons RF Remote Control - 1Pcs
8. 4 Channel 433MHz RF Wireless Remote Control Learning Decoding Receiver Module - 1Pcs
9. 3.2 Inch MEGA2560 Display Module HX8357B 480x320 TFT LCD Screen  - 1Pcs
10. 40 pcs Dupont Cables M-F Jumper Breadboard Wire GPIO Ribbon for connecting TFT LCD with Arduino MEGA - 1Pcs
11. MEGA 2560 R3 Arduino komp. Mikrokontroller Board Atmel ATmega2560  - 1Pcs
12. Several Dupont Cables M-F, M-M, F-F Jumper Breadboard Wire for wiring
13. NTC 3950 Thermistor 100KOhm  - 1Pcs
14. Resistor 100kOhm - 1Pcs
15. KY-040 Rotary Encoder Module - 1Pcs

### ** Wiring diagram: **
![image](https://user-images.githubusercontent.com/59554693/211296986-26492a3b-8a8e-42eb-bd9c-8b8bfb4bbc96.png)


