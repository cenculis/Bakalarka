% clear all objects and variables
clear all;
clear a;
clc 

AeroShield=AeroShield;

% create an arduino object
AeroShield.begin();

% calibration
startangle= AeroShield.calibration(); 
lastangle=startangle+2048; % save startangle + 180° (for mapping purpose)

% variables for counting time 
time = 0;
count = 0;

uhol = 0; % variable for angle
potentiometer = 0; % variable for potentiometer value 

% plot variables 
yyaxis right                         % Set plotting to right axis 
plotGraph = plot(time,uhol,'-r' )    % plotting angle variable
ylabel('Angle (°)','FontSize',15);        % label settings
xlabel('Time (s)','FontSize',15);        % font settings
hold on                              %hold on makes sure all of the channels are plotted

yyaxis left                          % Set plotting to left axis
plotGraph1 = plot(time,potentiometer,'-b') % plotting potentiometer variable
title('Pendulum plot','FontSize',15);      % font settings   
ylabel('Percent','FontSize',15)    % font settings 
legend('Potentiometer value','Pendulum angle')              % legend for plots
grid('on');                      % grid for plot 'off' to turn off grid

tic                                  % time keeping

while ishandle(plotGraph)      % loop when Plot is Active, will run until plot is closed
pwm = AeroShield.referenceRead();          % read potentiometer value
AeroShield.actuatorWrite(pwm);       % actuate 

RAW= AeroShield.getRawAngle();
uholl = mapped(RAW, startangle, lastangle, 0, 180); % extern mapping function 
count = count + 1;                          % cycle counter
time(count) = toc;                          % time keeping
uhol(count) = uholl(1);                     % angle value in time
percenta= mapped(pwm, 0.0, 5.0, 0.0, 100.0);% extern mapping function 
potentiometer(count) = percenta(1);         % pententiometer value in time
set(plotGraph,'XData',time,'YData',uhol);   % plot first data 
set(plotGraph1,'XData',time,'YData',potentiometer); % plot second data 
axis([time(count)-5 time(count) 0 100]);  % "running" x axis settings
end

clear all;
clear a;
clc 
disp('Plot Closed and arduino object has been deleted');
