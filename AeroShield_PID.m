clear all
clear a
clc 

AeroShield=AeroShield;

% create an arduino object
AeroShield.begin();

% calibration
startangle= AeroShield.calibration(); 
lastangle=startangle+2048; % save startangle + 180° (for mapping purpose)

Kp=1.7 ;                                     % PID Gain
Ti=3.8;                                    % PID Integral time constant
Td=0.25 ;                                     % PID Derivative time constant
umax=50.0;                                   % Maximum input
umin=0.0;                                     % Minimum input

R=[45.0 23.0 75.0 32.0 58.0 10.0 35.0 19.0 9.0 43.0 23.0 65.0 15.0 80.0];                            % [oC] Closed-loop reference
Ts=3;                                       % [s] Sampling period
runTime=7200;                               % [s] Total runtime

secLength=(runTime/Ts)/length(R);           % Length of a reference trajectory section
stepEnable = 0;                             % Algorithm step flag
k=1;                                        % Algorithm step counter
j=1;                                        % Reference section counter
r=R(1);                                     % First reference
eSum=0;                                     % Error sum
ep=0;                                       % Previous error
y=0;                                        % Output initialize

tic                                         % Start measuring time
while(1)                                    % Infinite loop
    if (stepEnable)                         % If flag is enabled
     % Read the output
        RAW = AeroShield.getRawAngle();
        y = mapped(RAW, startangle, lastangle, 0, 180); % extern mapping function 
        
     % Pick reference
        if (mod(k,secLength*j)==0);         % If time for new reference 
            j=j+1;                          % Next reference section
            r=R(j);                         % Pick new reference    
        end
        
     % Compute PID
        e = r-y;                            % [oC] Reference
        eSum=eSum+e;                        % Integral
        eSum=constrain((Kp*Ts/Ti)*eSum,umin,umax)/(Kp*Ts/Ti);  % Integral windup clamp
        u =Kp*(e+(Ts/Ti)*eSum+(Td/Ts)*(e-ep)); % PID 
        ep = e;                             % Data store
        u=constrain(u,umin,umax);           % Input saturation
        
     % Write to hardware
        AeroShield.actuatorWritePercent(u);        % [%] Power

        %response(k,:)=[r y u];              % Store results
        %plotLive(response(k,:));            % Live plot
      
        k=k+1;                              % Next sample no.
        stepEnable = 0;                     % Disable step.
    end                                     % Step end
    if (toc>=Ts*k)                          % If its time
        stepEnable = 1;                     % Enable the step
    elseif (toc>=runTime)                   % Experiment over
        AeroShield.actuatorWrite(0);        % Input off
        break                               % Exit while
    end
end

%save response response                      % Data file with response