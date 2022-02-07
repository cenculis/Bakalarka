#include "AeroShield.h"


AMS_5600 ams5600;

  float startangle=0;
  float lastangle=0;
  float pendulumAngle;
  float referencePercent;

 

void setup() {

  Serial.begin(115200);
  AeroShield.begin();
  AeroShield.ams5600_initialization(ams5600.detectMagnet());
  startangle = AeroShield.calibration(ams5600.getRawAngle());
  lastangle=startangle+1024;
}


void loop() {
  
pendulumAngle= AutomationShield.mapFloat(ams5600.getRawAngle(),startangle,lastangle,0.00,90.00);
Serial.print("pendulum angle is: ");
Serial.print(pendulumAngle);
Serial.print(" ");

referencePercent= AeroShield.referenceRead();
Serial.print("potentiometer value is: ");
Serial.print(referencePercent);
Serial.println(" ");

AeroShield.actuatorWrite(referencePercent);

}





  void manualControl(){
    
    
    }

  
  
