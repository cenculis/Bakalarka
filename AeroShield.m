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
            AERO_UPIN = 'D5';         % actuator pin
            AERO_RPIN = 'A3';
            plotTitle = 'Pendulum plot';  % plot title
            xLabel = 'Time (s)';                 % x-axis label1 
            yLabel = 'Angle (°)';                % y-axis label
            yLabelRight = 'Percent';             % x-axis label2 
            legend1 = 'potentiometer value'      % legend lable1
            legend2 = 'pendulum angle'           % legend lable2
            yMax  = 180                          % y Maximum Value
            yMin  = 0                            % y minimum Value
            plotGrid = 'on';                     % 'off' to turn off grid
            min = 0;                             % set y-min
            max = 100;                           % set y-max
    end

    methods
        function begin(AeroShieldObject)          % Initialization function
            AeroShieldObject.arduino = arduino();
            AeroShieldObject.as5600 = device(AeroShieldObject.arduino,'I2CAddress',0x36);
            configurePin(AeroShieldObject.arduino,AeroShieldObject.AERO_UPIN, 'DigitalOutput')
            disp('AeroShield initialized.')
        end
        
         function startangle = calibration(AeroShieldObject)
            write(AeroShieldObject.as5600, 0x0c, 'uint8');  % send command for reading angle
            write(AeroShieldObject.as5600, 0x0d, 'uint8');  % send command for reading angle
            startangle = read(AeroShieldObject.as5600, 1, 'uint16'); % read answer from sensor
        end

        function PWM = referenceRead(AeroShieldObject)
           PWM= readVoltage(AeroShieldObject.arduino, AeroShieldObject.AERO_RPIN);
        end
        
        function actuatorWrite(AeroShieldObject, PWM)
            writePWMVoltage(AeroShieldObject.arduino, AeroShieldObject.AERO_UPIN, PWM);
        end
        
        
        function actuatorWritePercent(AeroShieldObject, Percent)
            PWM = mapped(Percent, 0.0, 100.0, 0.0, 5.0)
            writePWMVoltage(AeroShieldObject.arduino, AeroShieldObject.AERO_UPIN, PWM);
        end
        
        function RAW = getRawAngle(AeroShieldObject)
            write(AeroShieldObject.as5600, 0x0c, 'uint8');        % send command for reading angle
            write(AeroShieldObject.as5600, 0x0d, 'uint8');        % send command for reading angle
            RAW = read(AeroShieldObject.as5600, 1, 'uint16');     % read answer from sensor
        end
    end
end