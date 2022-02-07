/*
  API for the AeroShield hardware.
  
  The file is a part of the application programming interface for
  the AeroShield didactic tool for control engineering and 
  mechatronics education.
  
  This code is part of the AutomationShield hardware and software
  ecosystem. Visit http://www.automationshield.com for more
  details. This code is licensed under a Creative Commons
  Attribution-NonCommercial 4.0 International License.

  Created by .... 
  Last update: 05.02.2022.
*/

#ifndef AEROSHIELD_H			// Include guard
#define AEROSHIELD_H			

#include "AutomationShield.h"
#include <Wire.h>
#include <AS5600.h>
#include "Arduino.h"			// Required Arduino API in libraries


// Defining pins used by the OptoShield board
#define AERO_RPIN A3   // Input from potentiometer
#define SENSOR_PIN A2   // Input pin for measuring Vout
#define AERO_UPIN 5   // Motor (Actuator)
#define AERO_SR 0.1         // Shunt resistor value (in ohms)
#define VOLTAGE_REF 5.0 		// Voltage reference for current measurement



class AeroShieldClass{			// Class for the AeroShield device
 public:
    void begin();
    float calibration(word RawAngle);
    float convertRawAngleToDegrees(word newAngle);


  private:
    int ang;
    float startangle;

   
    
};

extern AeroShieldClass AeroShield;
#endif
