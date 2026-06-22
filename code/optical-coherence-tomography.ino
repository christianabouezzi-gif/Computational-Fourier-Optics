

%time domain, vector of time points size of 1024
t = (0:1023);

%Oscillation freqeuncy
f_p = 1/16;

%pulse filed of oscillating cosine wave
pulse_field = cos(2*pi*f_p*t);

%the 1/e half width
sigma = 8;

%center of the envelope at 36
t0 = 36;

% Gaussian envelope equation
E = pulse_field .* exp(-((t - t0).^2) / (sigma^2));

% Plot
figure;
plot(t, E);
xlabel('Time');
ylabel('E(t)');
title('Gaussian Envelope Cosine Pulse');
%%


%Spectrum of my reference field
s_f = abs(fft(E)).^2;
S_f_indexed = s_f(1:512);
f_s = (0:511);

%indexing the first 128 points like directed
t_ploted = (0:127);
S_f_ploted = (S_f_indexed(1:128));

%plotting the indexed 128 points
figure
subplot(3,1,1)
plot(t_ploted, S_f_ploted)
xlabel('Frequency');
ylabel('S(f)')
title('Positive Spectrum Values')

%plot of increased f_p
subplot(3,1,2)
f_p_2 = 1/10;
pulse_field_2 = cos(2*pi*(f_p_2)*t);
E_2 = pulse_field_2 .* exp(-((t - t0).^2) / (sigma^2));
s_f_2 = abs(fft(E_2)).^2;
S_f_ploted_2 = (s_f_2(1:128));
plot(t_ploted, S_f_ploted_2)
xlabel('Frequency');
ylabel('S(f)')
title('f_p Increased')

%plot of increased pulse width
subplot(3,1,3)
sigma_2 = 10;
E_3 = pulse_field .* exp(-((t - t0).^2) / (sigma_2^2));
s_f_3 = abs(fft(E_3)).^2;
S_f_ploted_3 = (s_f_3(1:128));
plot(t_ploted, S_f_ploted_3)
xlabel('Frequency');
ylabel('S(f)')
title('Pulse Waist Increased')
sgtitle('Positive Freqeuncies of the Spectrum')

disp('When the pulse freqeuncy is increased, the spectrum is shifted to the right to higher frequencies.')
disp('When the pulse waist increases, the spectrum amplitude increases while the spectrum becomes more narrow.')
%%


%time domain, vector of time points size of 1024
t = (0:1023);

%Oscillation freqeuncy
f_p = 1/16;
tau = 120;

%pulse filed of oscillating cosine wave
pulse_field = cos(2*pi*f_p*t);
pulse_delayed = cos(2*pi*f_p*(t-tau));

%the 1/e half width
sigma = 8;

%center of the envelope at 36
t0 = 36;

% Gaussian envelope equation
E = pulse_field .* exp(-((t - t0).^2) / (sigma^2));
%delayed Gaussian
E_delayed = pulse_delayed .* exp(-((t - t0 - tau).^2) / (sigma^2));

E_combined = E_delayed + E;

figure
subplot(3,1,1)
plot(t, E);
xlabel('Time');
ylabel('E(t)');
title('Gaussian Envelope Cosine Pulse');

%plotting the delayed gassian
subplot(3,1,2)
plot(t, E_delayed);
xlabel('Time');
ylabel('E(t)');
title('Gaussian Time Delayed');


%Combined E
subplot(3,1,3)
plot(t, E_combined);
xlabel('Time');
ylabel('E(t)');
title('Gaussian Combined');
sgtitle('Normal vs Time Delayed Gaussian vs Combined Gaussian')

%plotting the spectrums
figure
subplot(3,1,1)
plot(t_ploted, S_f_ploted)
xlabel('Frequency');
ylabel('S(f)')
title('Positive Spectrum Values')

%delayed subplot spectrum
subplot(3,1,2)
s_f_delayed = abs(fft(E_delayed)).^2;
S_f_ploted_delayed = (s_f_delayed(1:128));
plot(t_ploted, S_f_ploted_delayed)
xlabel('Frequency');
ylabel('S(f)')
title('Positive Spectrum Values Delayed')

%combined spectrum subplot
subplot(3,1,3)
s_f_combined = abs(fft(E_combined)).^2;
S_f_ploted_combined = (s_f_combined(1:128));
plot(t_ploted, S_f_ploted_combined)
xlabel('Frequency');
ylabel('S(f)')
title('Positive Spectrum Values combined')
sgtitle('Normal vs Time Delayed Spectrum vs Combined Spectrum')


figure
%combined spectrum subplot
subplot(3,1,1)
plot(t_ploted, S_f_ploted_combined)
xlabel('Frequency');
ylabel('S(f)')
title('Positive Spectrum Values combined')


%smaller delay
t3 = 60;

% Gaussian envelope equation for smaller delay
pulse_delayed2 = cos(2*pi*f_p*(t-t3));
E_delayed_smaller = pulse_delayed2 .* exp(-((t - t0 - t3).^2) / (sigma^2));

%larger delayed Gaussian
t4 = 240;
pulse_delayed3 = cos(2*pi*f_p*(t-t4));
E_delayed_larger = pulse_delayed3 .* exp(-((t - t0 - t4).^2) / (sigma^2));

%combined larger and smaller delay
E_combined_2 = E_delayed_smaller + E;
E_combined_3 = E_delayed_larger +E;


%smaller combined delay
subplot(3,1,2)
s_f_combined_smaller = abs(fft(E_combined_2)).^2;
S_f_ploted_combined_smaller = (s_f_combined_smaller(1:128));
plot(t_ploted, S_f_ploted_combined_smaller)
xlabel('Frequency');
ylabel('S(f)')
title('Smaller combined')

%larger combined delay
subplot(3,1,3)
s_f_combined_larger = abs(fft(E_combined_3)).^2;
S_f_ploted_combined_larger = (s_f_combined_larger(1:128));
plot(t_ploted, S_f_ploted_combined_larger)
xlabel('Frequency');
ylabel('S(f)')
title('Larger combined')
sgtitle('Normal vs Larger vs Smaller Combined Spectrum')

disp('When the reference and delayed pulses are added, the spectrum has a wavy pattern on top of the Gaussian shape, showing how the two pulses interfere.')
disp('The delayed spectrum is identical to the reference spectrum.')
disp('A smaller delay produces wider ends.')
disp('A larger delay produces more closely spaced ends.')
%%

%reflectivity map of the combined spectrum.
s_combined = abs(fft(E_combined)).^2;
R_z = abs(fft(s_combined)).^2;

z = 1:128;

figure
plot(z,R_z(1:128))
xlabel('Depth z ');
ylabel('R(z)');
title('R(z) Map from Combined Spectrum');

disp('The scalling factor is found by the peak index/tau, where the peak index is 121 and tau is 120, so we have 121/120 and the scaling factor is 1.008. ')
%%


t = (0:1023);

%Oscillation freqeuncy
f_p = 1/16;
tau = 120;
tau8 = 180;

%pulse filed of oscillating cosine wave
pulse_field = cos(2*pi*f_p*t);
pulse_delayed = cos(2*pi*f_p*(t-tau));
pulse_delayed8 = cos(2*pi*f_p*(t-tau8));

%the 1/e half width
sigma = 8;

%center of the envelope at 36
t0 = 36;

% Gaussian envelope equation
E = pulse_field .* exp(-((t - t0).^2) / (sigma^2));
%delayed Gaussian
E_delayed = pulse_delayed .* exp(-((t - t0 - tau).^2) / (sigma^2));
E_delayed8 = pulse_delayed8 .* exp(-((t - t0 - tau8).^2) / (sigma^2));


%three pulses combined
E_combined = E_delayed + E;
E_combined8 = E_delayed8 + E_delayed + E;

%two pulses
s_combined = abs(fft(E_combined)).^2;
R_z = abs(fft(s_combined)).^2;
z = 1:128;

%reflection of the three pulses
s_combined8 = abs(fft(E_combined8)).^2;
R_z8 = abs(fft(s_combined8)).^2;

figure
subplot(2,1,1)
plot(z, s_combined8(1:128))
xlabel('Frequency');
ylabel('S(f)')
title('Specturm triple combined')


subplot(2,1,2)
plot(z, R_z8(1:128))
xlabel('Depth z ');
ylabel('R(z)');
title('R(z) Map from triple Combined Spectrum');
sgtitle('question 5')

disp('We have three pulses technically, the reference, the 120 delay and the 180 delay, so we have a peak for each one.')
disp('at z=8, this is the mirror peak of the first sample pulse, at point 61, this is the interference peak of 180 and 120 delay, at 121 peak, this is the first reference sample interfering with the first delay sample. Because we have 128 points plotted, the peak at 180 is wrapped around.')
%%

t = (0:1023);

%Oscillation freqeuncy
f_p = 1/16;
tau = 120;
tau8 = 180;

%pulse filed of oscillating cosine wave
pulse_field = cos(2*pi*f_p*t);
pulse_delayed = cos(2*pi*f_p*(t-tau));
pulse_delayed8 = cos(2*pi*f_p*(t-tau8));

%the 1/e half width
sigma = 8;

%center of the envelope at 36
t0 = 36;

% Gaussian envelope equation
E = 10*pulse_field .* exp(-((t - t0).^2) / (sigma^2));
%delayed Gaussian
E_delayed = pulse_delayed .* exp(-((t - t0 - tau).^2) / (sigma^2));
E_delayed8 = pulse_delayed8 .* exp(-((t - t0 - tau8).^2) / (sigma^2));


%three pulses combined
E_combined = E_delayed + E;
E_combined8 = E_delayed8 + E_delayed + E;

%two pulses
s_combined = abs(fft(E_combined)).^2;
R_z = abs(fft(s_combined)).^2;
z = 1:128;

%reflection of the three pulses
s_combined8 = abs(fft(E_combined8)).^2;
R_z8 = abs(fft(s_combined8)).^2;

figure
subplot(2,1,1)
plot(z, s_combined8(1:128))
xlabel('Frequency');
ylabel('S(f)')
title('Specturm triple combined')


subplot(2,1,2)
plot(z, R_z8(1:128))
xlabel('Depth z ');
ylabel('R(z)');
title('R(z) Map from triple Combined Spectrum');
sgtitle('question 6 ten times stronger')

disp('We find that the background near z=0 is strong, the peaks at 120 and 180 are much smaller, and there is a smaller interference peak.')

R_z(1:20)=0;
figure
plot(z, R_z(1:128))
xlabel('Depth z')
ylabel('R(z)')
title('Reflectivity Map with removed background');

disp('The first 20 elements in R_z are strong reference pulses that interfere with itself. Removing them helps remove the background so that the map only highlights the sampling pulses.')
