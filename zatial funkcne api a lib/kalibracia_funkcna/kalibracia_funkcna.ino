
#include "AeroShield.h"


AMS_5600 ams5600;

 float angle;
    float startangle;
    float lastangle;
    int MOTOR_PWM=0;
int lang = 0;
float value;
float sensorValue;   // Variable to store value from analog read
float current;       // Calculated current value
 

void setup() {
  AeroShield.begin();
  Serial.begin(115200);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> ");
  if(ams5600.detectMagnet() == 0 ){
    while(1){
        if(ams5600.detectMagnet() == 1 ){
            Serial.println("Magnet detected ");
            break;
        }
        else{
            Serial.println("Can not detect magnet ");
        }
        delay(1000);
    }
  }
 startangle = AeroShield.calibration(ams5600.getRawAngle());
 lastangle=startangle+1024;
}


void loop() {
  
value = AutomationShield.mapFloat(ams5600.getRawAngle(),startangle,lastangle,0.00,90.00);

Serial.println(value);
}





  void manualControl(){
    
    
    }

  
  
