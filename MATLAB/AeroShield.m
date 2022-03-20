%   AeroShield MATLAB API.
%
%
%   This code is part of the AutomationShield hardware and software
%   ecosystem. Visit http://www.automationshield.com for more
%   details. This code is licensed under a Creative Commons
%   Attribution-NonCommercial 4.0 International License.
%
%   Created by Peter Tibensky.
%   Last update: 13.3.2022.

classdef AeroShield < handle

    properties
        arduino;
        as5600;
    end

    properties(Constant)
            AERO_UPIN = 'D5';          % actuator pin
            AERO_RPIN = 'A3';          % potentiometer pin
            VOLTAGE_SENSOR_PIN = 'A2'; % current measure pin 
            voltageReference = 5.0;    % voltage reference value
            ShuntRes = 0.1;            % value of shunt resistor in ohms
            correction1 = 4.1220;	   % correction for measuring current 				  
            correction2 = 0.33;        % correction for measuring current
            repeatTimes = 50;          % number of loops for current measure
    end

    methods
        function begin(AeroShieldObject)          % initialization function
            AeroShieldObject.arduino = arduino(); % constructing arduino object 
            AeroShieldObject.as5600 = device(AeroShieldObject.arduino,'I2CAddress',0x36); % constructing sensor object
            configurePin(AeroShieldObject.arduino,AeroShieldObject.AERO_UPIN, 'DigitalOutput') % pin configuration as output
            disp('AeroShield initialized.') % display message 
        end
        
         function startangle = calibration(AeroShieldObject) % calibration function 
            write(AeroShieldObject.as5600, 0x0c, 'uint8');  % send command for reading angle
            write(AeroShieldObject.as5600, 0x0d, 'uint8');  % send command for reading angle
            startangle = read(AeroShieldObject.as5600, 1, 'uint16'); % read answer from sensor
        end

        function PWM = referenceRead(AeroShieldObject)  % reference read 
           PWM= readVoltage(AeroShieldObject.arduino, AeroShieldObject.AERO_RPIN); % read potentiometer value 
        end
        
        function actuatorWrite(AeroShieldObject, PWM) % actuator write 
            writePWMVoltage(AeroShieldObject.arduino, AeroShieldObject.AERO_UPIN, PWM); % write voltage level to the motor pin
        end
       
        
        function RAW = getRawAngle(AeroShieldObject)              % get raw angle value 
            write(AeroShieldObject.as5600, 0x0c, 'uint8');        % send command for reading angle
            write(AeroShieldObject.as5600, 0x0d, 'uint8');        % send command for reading angle
            RAW = read(AeroShieldObject.as5600, 1, 'uint16');     % read answer from sensor
        end
        
        
        function currentMean = getCurrent()  % get current reading 
              for r = 1:repeatTimes
              voltageValue = readVoltage(AeroShieldObject.arduino, AeroShieldObject.VOLTAGE_SENSOR_PIN); % read pin voltage value 
              voltageValue= (voltageValue * voltageReference) / 1024;                      % Remap the ADC value into a voltage number (5V reference)
              Current= Current + correction1-(voltageValue / (10 * ShuntRes));             % Equation given by the INA169 datasheet to
              end                                                                          % determine the current flowing through ShuntRes. RL = 10k          
                                                                                           % Is = (Vout x 1k) / (RS x RL)
        currentMean= Current/repeatTimes;                                                  % Callculating mean current value 
        currentMean= currentMean-correction2;                                              % Small correction of current value(determined by multimeter)
        if currentMean < 0.000                                                             % Correction for occasional bug causing the value to be negative. 
        currentMean= 0.000;                                                                % When it so happens, zero out the value. 
        end
        current= 0;                                                                        % Zero out current value        
        voltageValue= 0;                                                                                                                                                                          
        end 
        
    end
end