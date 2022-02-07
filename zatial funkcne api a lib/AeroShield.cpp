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


#include "AeroShield.h"



// Initializes hardware pins
void AeroShieldClass::begin(){  
      pinMode(AERO_UPIN,OUTPUT);  		// Thermistor pin
      Wire.begin();                       //
}

float AeroShieldClass::ams5600_initialization(bool isDetected){  
  if(isDetected == 0 ){
    while(1){
        if(isDetected == 1 ){
            AutomationShield.serialPrint("Magnet detected \n");
            break;
        }
        else{
            AutomationShield.serialPrint("Can not detect magnet \n");
      }
    }
  }
}

float AeroShieldClass::convertRawAngleToDegrees(word newAngle) {
  float retVal = newAngle * 0.087;
  ang = retVal;
  return ang;
}


float AeroShieldClass::calibration(word RawAngle) {

  AutomationShield.serialPrint("Calibration running...\n");
  startangle=0;
  analogWrite(AERO_UPIN,50);
  delay(250);
  analogWrite(AERO_UPIN,0);
  delay(4000);
  
  startangle = RawAngle;
  analogWrite(AERO_UPIN,0);
    for(int i=0;i<3;i++){
      analogWrite(AERO_UPIN,1);
      delay(200);
      analogWrite(AERO_UPIN,0);
      delay(200);
      }

  AutomationShield.serialPrint("Calibration done");
    return startangle;
}


  float AeroShieldClass::referenceRead(void) {                                                      // Reference read
  referenceValue = (float)analogRead(AERO_RPIN);                                           // Reads the actual analog value of potentiometer runner
  referencePercent = AutomationShield.mapFloat(referenceValue, 0.0, 1024.0, 0.0, 100.0);   // Remapps the analog value from original range 0.0-1023 to percentual range 0.0-100.0
  return referencePercent;                                                                  // Returns the percentual position of potentiometer runner
}

void AeroShieldClass::actuatorWrite(float PotPercent) {
  float mappedValue = AutomationShield.mapFloat(PotPercent, 0.0, 100.0, 0.0, 255.0);       // Takes the float type percentual value 0.0-100.0 and remapps it to range 0.0-255.0
  mappedValue = AutomationShield.constrainFloat(mappedValue, 0.0, 255.0);                // Constrains the remapped value to fit the range 0.0-255.0 - safety precaution
  analogWrite(AERO_UPIN, (int)mappedValue);                                            
}

/*
void AeroShieldClass::actuatorWrite(float percent){  
      analogWrite(HEAT_UPIN,AutomationShield.percToPwm(percent)); // Write to actuator
}

/*
// Reads thermistor voltage
float AeroShieldClass::getThermistorVoltage() { 
      return (float)analogRead(HEAT_YPIN) * ARES;
}

// Reads thermistor resistance
// Voltage divider circuit (Kirchhoffs law)
float AeroShieldClass::getThermistorResistance() {
	float Vterm = getThermistorVoltage();
	 return ((Vterm*VD_RES)/(VD_REF-Vterm));
}*/

AeroShieldClass AeroShield;