/*
  API for the AeroShield didactic hardware.
  The file is a part of the application programmers interface for
  the AeroShield didactic tool for control engineering and
  mechatronics education. The AeroShield implements an air-flow
  levitation experiment on an Arduino shield.

  This code is part of the AutomationShield hardware and software
  ecosystem. Visit http://www.automationshield.com for more
  details. This code is licensed under a Creative Commons
  Attribution-NonCommercial 4.0 International License.

  Created by Gergely Takács, Peter Chmurčiak and Erik Mikuláš.
  Last update: 2.12.2020.
*/

#ifndef AEROSHIELD_H             // Include guard
#define AEROSHIELD_H

#include "AutomationShield.h"      // Include the main library
#include <Wire.h>                  // Include the I2C protocol library
#include "lib/BasicLinearAlgebra/BasicLinearAlgebra.h"     // Include library for matrix operations

#ifndef AS5600_h                                          // If library for hall sensor is not already included  
  #include "Arduino_AS5600.h"                   // Include it from the library folder  
#endif

// Defining pins used by the AeroShield board

  #define AERO_UPIN 5              // Motor (Actuator)
  #define AERO_AVPIN A2            // Pin for reading motor voltage(current)
  #define AERO_RPIN A3             // Potentiometer 

#ifdef AS5600_h                     // If library for distance sensor was successfully included

class AeroClass {                                               // Class for AeroShield device
  public:
    void begin(void);                                            // Board initialisation - initialisation of distance sensor, pin modes and variables
    void calibrate(void);                                        // Board calibration - finding out the minimal and maximal values measured by distance sensor
   // void actuatorWrite(float);                                   // Write actuator - function takes input 0.0-100.0 and sets fan speed accordingly
   // float referenceRead(void);                                   // Reference read - returns potentiometer position in percentual range 0.0-100.0
   // float referenceReadAltitude(void);                           // Reference read altitude - returns potentiometer position in calibrated altitude range 0.0-324.0 (mm)
   // float sensorRead(void);                                      // Sensor read - returns the altitude of the ball in tube in percentual range 0.0(ball is on the fan)-100.0(ball is on the tube ceiling)
   // float sensorReadAltitude(void);                              // Sensor read altitude - returns the altitude of the ball in tube in millimetres
   // float sensorReadDistance(void);                              // Sensor read distance - returns raw reading of distance between sensor and ball in millimetres
   // bool returnCalibrated(void);                                 // Returns calibration status, true if sensor was calibrated
   // float returnMinDistance(void);                               // Returns value of minimal distance measured by sensor in millimetres
   // float returnMaxDistance(void);                               // Returns value of maximal distance measured by sensor in millimetres
   // float returnRange(void);                                     // Returns range of measured distances between minimal and maximal values in millimetres

  private:
    float _minDistance;                  // Variable for storing minimal distance measured by sensor in millimetres
    float _maxDistance;                  // Variable for storing maximal distance measured by sensor in millimetres
    float _range;                        // Variable for storing range of measured distances by sensor in millimetres
    bool _wasCalibrated;                 // Variable for storing calibration status
    float _referenceValue;               // Variable for storing potentiometer runner position as analog value 0.0-1023.0
    float _referencePercent;             // Variable for storing potentiometer runner position as percentual range 0.0-100.0
    float _sensorValue;                  // Variable for storing measured distance by sensor in millimetres
    float _sensorPercent;                // Variable for percentual altitude of the ball in the tube 0.0-100.0
    float _ballAltitude;                 // Variable for altitude of the ball in tube in millimetres
    float _rpm;                                                          // Variable for storing current value of fan rotations per minute
    float _samplingPeriod = 25.0;                                        // Variable for storing sampling period in milliseconds used for accurate RPM calculation (default 25ms)
    float _nOfSamples = ceil(150.0 / _samplingPeriod);                   // Variable for storing number of samples required for accurate RPM calculation (default 6)
    float _pulseCountToRPM = 15000.0 / (_samplingPeriod * _nOfSamples);  // Variable for storing constant used to calculate RPM from number of pulses (default 100)

};

extern AeroClass AeroShield;           // Creation of external AeroClass object

#endif
#endif                                   // End of guard