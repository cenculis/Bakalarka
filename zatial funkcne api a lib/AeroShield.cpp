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
  delay(5000);
  
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
    /*     
  while(angle<=startangle+90.0){
    analogWrite(AERO_UPIN,MOTOR_PWM);
    delay(300);
    angle=AeroShield.convertRawAngleToDegrees(ams5600.getRawAngle());
    MOTOR_PWM=MOTOR_PWM+5;
    }
    */
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