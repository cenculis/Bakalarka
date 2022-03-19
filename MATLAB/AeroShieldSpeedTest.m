% clear all objects and variables
clear all
clear a
clc 

NumOSamples = 500;                                                  % Desired number of samples
platform = 'Mega2560';                                               % 'Uno', 'Due', etc.

disp('Testing...')                                                  % Message

A = arduino('COM3',platform,'Libraries','I2C');                     % Creates arduino object
configurePin(A,'A3','AnalogInput');                                 % Reads analog value from potentiometer
configurePin(A,'D5','DigitalOutput')

AS5600 = device(A,'I2CAddress',0x36,'bitrate',400000);  % Initializes I2c communication
tet = zeros(100,1);                                                 % Pre-allocate memory for execution time measurements
for i = 1:NumOSamples                                               % Performs several measurements
    tic;                                                            % Starts stopwatch
    y = readVoltage(A,'A3');                                        % Reads voltage from the Hall sensor to variable y
    writePWMVoltage(A,'D5', 0.2);
    write(AS5600, 0x0c, 'uint8');                                   % send command for reading angle
    write(AS5600, 0x0d, 'uint8');                                   % send command for reading angle
    RAW = read(AS5600, 1, 'uint16');                                % read answer from sensor
    tet(i,1) = toc;                                                 % Stops stopwatch and notes execution time
end

disp('Done.')                                                       % Message.

t = 1:NumOSamples;                                                   % Vector for axis
plot(t,tet,'o')                                                     % Plot results
grid on;                                                            % Grid
ylabel('Total execution time [s]')                                  % Y axis label
xlabel('Sample (-)')                                                % X axis label
legend('AeroShield MATLAB Communication Speed Test')             % Legend

filename = ['AeroShield_Speed_Test_Data_',platform];              % Create filename
save(filename,'tet')                           