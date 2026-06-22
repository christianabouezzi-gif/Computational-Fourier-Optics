
%importing the rice image and converting it to an array
og = imread('rice.tif');
image = double(imread('rice.tif'));
%finding the maximum value of the array for scaling factor use
M = max(image, [], 'all');
%The scaling factor is found by 1/the max value in the array
scale_factor = 1/M;
%multiply the image by the scaling factor so that its normalized max value is 1. 
norm_image = image*scale_factor;

%creating a uniform wave plane of Ein, which is an array of all ones the
%same size as the image
illumination = ones(256,256);
%this is the Eout, calculated by Eout = Ein*e^(-1 * delta phi), where delta
%phi is the phase shift of my normal image. This equation keeps the
%brightness the same but shifts the timing of the light wave as it passes
%through rice
illuminated_image = illumination .* exp(-1i * norm_image);

%amplitude tells us the stregnth of the brightness, but the matrix will be
%all ones, proving that the object is a phase object. It doesnt absorb or
%block any light
amplitude = abs(illuminated_image);
%this gives the delay of the light wave. The speed of light is changed.
phase_shift = angle(illuminated_image);

figure('Name', 'Amplitude image and phase image')
subplot(1, 2, 1)
amp_val = imshow(amplitude, []);
title('Amplitude Image')

subplot(1, 2, 2)
phase_val = imshow(phase_shift, []);
title('Phase image')
%%


%aperture function should have the diameter half the size of the array
imsize = 256;
radius_big = (1/4)*imsize;


%this was to set the orgin
range=imsize*(-floor(imsize/2):ceil(imsize/2)-1)/floor(imsize/2);
%made the grid for the aperature
[x,y]=meshgrid(range);

%created a array of zeroes for the aperature, and made the equation of a
%circle for the orgin
r = sqrt(x.^2 + y.^2);


%made it so that inside the radius is white, and outside is black
A_large = zeros(imsize);
A_large(r<radius_big) = 1;


%did fft of the original image, propogate through the first lens to the
%fourier plane. ffshift to center the component
output=fftshift(fft2(ifftshift(illuminated_image)));



%solved for eout, which is E_out = A * Ein, where E_in is the fft of the
%image and A is the aperture. Aperture acts as a low-pass filtler blocing
%high spatial frequecny
E_filtered = output .* A_large;
%taking the inverse fft of the E_filtered after fingin E_out in fourier
%space. Propegated through the second lens back to the spatial domain.
E_out_flipped = fftshift(ifft2(ifftshift(E_filtered)));

%Finding I_out is the E_out squared
I_out = abs(E_out_flipped).^2;

figure ('Name', 'Aperture 1/2 of array and its intensity')

subplot(1, 2, 1)
imshow(A_large, []);
title('Aperture 1/2 array');
colormap(gca, gray);

subplot(1, 2, 2)
imshow(I_out, [])
title('1/2 array radius aperture intensity')
colormap(gca, gray);


%The phase are invisible, the rice is a phase object with E = 1 everywhere,
%and the standard circular aperture does not convert the phase shifts into
%intensity changes. The aperture acts as a lowpass filter, removing high
%freuqency making the phase of the image blurry. This shows a 4f microscope
%cant image transparent phase objects without an added modification. 

%%

%Used size 256, bc array size is 256x256  
imsize = 256;

%calculates the radius of the phase dot. It asks for a diameter of 1/32,
%the radius is half, whihc is 1/64
radius_small = (1/64)*imsize;

%This creates a centered vector, it defines the orgin (0,0) at the center
%of the ray, than the top left corner
range2 = imsize*(-floor(imsize/2):ceil(imsize/2)-1)/floor(imsize/2);

%makes 1D vector into 2D matrix coordinates, allowing for radical
%calculations
[x2, y2] = meshgrid(range2, range2);

%Formula for a circle, creates the circular aperture distances. 
r2 = sqrt(x2.^2 + y2.^2);

%Creates a phase contrast shift of pi/2, or 90 degrees. This is like
%multiplying by e^i*pi/2
phase_shift2 = exp(1i*pi/2);

%creates a black picture the size of the aray
A_total_small = zeros(imsize);

%creates the main aperture, aka low pass filter, allowing light to pass
%with value of 1, only within the limits of the lens, which is half the
%array size. 
A_total_small(r2<radius_big) = 1;


%creates a tiny citcle that shows where the Ballistic, unscattered light,
%is focused in the Fourier plane
mask1 = (r2<radius_small);

%this applies the phase shift to only the central component of light. It is
%essentialy identifying where the small circle is, and taking those values
%of 1, and multiplying by the phaseshift, giving the pixels a complex phase
%of 90 degrees, while the larger aperture remains real valued.
A_total_small(mask1 == 1) = A_total_small(mask1 == 1)*phase_shift2;

%Transformers the Rice field from spatial to fourier domain. The fftshift
%makes sure the 0 freqeuncy light is moved to the center to match the
%aperture. No need for circshift
output2=fftshift(fft2(ifftshift(illuminated_image)));

%This simulates the light passing through the aperture. The background
%light is phas shifted, while the light scattered by the rice passes
%through the rest of the aperture not changed. 
E_filtered2 = output2 .* A_total_small;

%This is the second lens. The inverse fast fourier transform converting the
%frequencies back into spatial images. 
E_out_flipped2 = fftshift(ifft2(ifftshift(E_filtered2)));

%This calculates the intensities. We cant see complex phases, so we do this
%to find the brightness.
I_out2 = abs(E_out_flipped2).^2;

figure;
imshow(angle(A_total_small), []);
title('Aperture 1/32 array');
colormap(gca, gray);

figure
imshow(I_out2, [])
title('1/32 array radius aperture intensity')
colormap(gca, gray);




%explanation:
%I start with setting my system to the center in a mathematical orgin, the
%center of the matrix. I then have the size of my lens, the Large apertur,
%acting as the low pass filter. The mask is basically the Zernike phase
%dot. It is plaed over the larger aperture, and multiplied by e^i*pi/2,
%treating light differently depending where it is on the fourier plane. The
%ballistic light, background, is illuminated in a uniform plane wave, and
%is focused on a tiny spot at the center of the fourier plane. It hits the
%small aperture, the mask, and gets shifted by 90 degrees. The scattered
%light, rice, diffracts in many angles. These ae higher frequencies that go
%through other parts of the biger aperture, missing the small phase dot and
%staing unchanged. When light reaches the final image plane, the background
%light and scatered light interfere with eachother. Before the shift, they
%were out of step in a way, and after the shift, the interfer, causeing
%phase delays, creating intensity values. 



%%

%aperture function should have the phase shifter of small diameter 1/8 
%times the size of the array.  
%Used size 256, bc array size is 256x256  
imsize = 256;

%calculates the radius of the phase dot. It asks for a diameter of 1/32,
%the radius is half, whihc is 1/64
radius_small2 = (1/16)*imsize;

%This creates a centered vector, it defines the orgin (0,0) at the center
%of the ray, than the top left corner
range3 = imsize*(-floor(imsize/2):ceil(imsize/2)-1)/floor(imsize/2);

%makes 1D vector into 2D matrix coordinates, allowing for radical
%calculations
[x3, y3] = meshgrid(range3, range3);

%Formula for a circle, creates the circular aperture distances. 
r3 = sqrt(x3.^2 + y3.^2);

%Creates a phase contrast shift of pi/2, or 90 degrees. This is like
%multiplying by e^i*pi/2
phase_shift3 = exp(1i*pi/2);

%creates a black picture the size of the aray
A_total_small2 = zeros(imsize);

%creates the main aperture, aka low pass filter, allowing light to pass
%with value of 1, only within the limits of the lens, which is half the
%array size. 
A_total_small2(r3<radius_big) = 1;


%creates a tiny citcle that shows where the Ballistic, unscattered light,
%is focused in the Fourier plane
mask2 = (r3<radius_small2);

%this applies the phase shift to only the central component of light. It is
%essentialy identifying where the small circle is, and taking those values
%of 1, and multiplying by the phaseshift, giving the pixels a complex phase
%of 90 degrees, while the larger aperture remains real valued.
A_total_small2(mask2 == 1) = A_total_small2(mask2 == 1)*phase_shift3;

%Transformers the Rice field from spatial to fourier domain. The fftshift
%makes sure the 0 freqeuncy light is moved to the center to match the
%aperture. No need for circshift
output3=fftshift(fft2(ifftshift(illuminated_image)));

%This simulates the light passing through the aperture. The background
%light is phas shifted, while the light scattered by the rice passes
%through the rest of the aperture not changed. 
E_filtered3 = output3 .* A_total_small2;

%This is the second lens. The inverse fast fourier transform converting the
%frequencies back into spatial images. 
E_out_flipped3 = fftshift(ifft2(ifftshift(E_filtered3)));

%This calculates the intensities. We cant see complex phases, so we do this
%to find the brightness.
I_out3 = abs(E_out_flipped3).^2;

figure;
imshow(angle(A_total_small2), []);
title('Aperture 1/8 array');
colormap(gca, gray);


figure('Name', 'Question 3: Zernike Phase Contrast');

subplot(1,2,1);
imshow(I_out2, []);
title('Phase Dot Diameter: 1/32');

subplot(1,2,2);
imshow(I_out3, []);
title('Phase Dot Diameter: 1/8');

disp('Why the size matters: the 1/32 size separates the background from the rice, creating the max difference between the two, having the grains pop out more. The 1/8 size is larger, it does shift the background, but also shifts low freqeuncy parts of the rice. When the background and the rice are both shifted by the same amount, there are not out of phase with eachother anymore, and the contrast disappears.')
disp('1/32 is a better mask. It is more percise allowing for better resolution and less blurr. ')

%%


%aperture function should have the diameter half the size of the array
imsize = 256;
radius_big = (1/4)*imsize;


%this was to set the orgin
range=imsize*(-floor(imsize/2):ceil(imsize/2)-1)/floor(imsize/2);
%made the grid for the aperature
[x,y]=meshgrid(range);

%created a array of zeroes for the aperature, and made the equation of a
%circle for the orgin
r = sqrt(x.^2 + y.^2);


%made it so that inside the radius is white, and outside is black
A_large = zeros(imsize);
A_large(r<radius_big) = 1;



%showed what the aperture looked like, had a colormap of gray
figure;
imshow(A_large, []);
title('Aperture 1/2 array');
colormap(gca, gray);

%did fft of the original image, propogate through the first lens to the
%fourier plane. ffshift to center the component
output=fftshift(fft2(ifftshift(illuminated_image)));



%solved for eout, which is E_out = A * Ein, where E_in is the fft of the
%image and A is the aperture. Aperture acts as a low-pass filtler blocing
%high spatial frequecny
E_filtered = output .* A_large;
%taking the inverse fft of the E_filtered after fingin E_out in fourier
%space. Propegated through the second lens back to the spatial domain.
E_out_flipped = fftshift(ifft2(ifftshift(E_filtered)));

%Shifting the E_out_flipped by +- 2 pixels using circshift
E_out_flipped_shifted_positive = circshift(E_out_flipped, [0 2]);
E_out_flipped_shifted_negative = circshift(E_out_flipped, [0 -2]);

%this is the interference step, summing the two shifted fields. 
E_out_total = E_out_flipped_shifted_negative + E_out_flipped_shifted_positive;

%Finding I_out is the E_out squared
I_out = abs(E_out_flipped).^2;
I_out_total = abs(E_out_total).^2;


figure('Name', 'Conventional vs. Shifted');

subplot(1, 2, 1);
imshow(I_out, []);
title('1/2 Array Radius Aperture');
colormap(gca, gray);


subplot(1, 2, 2);
imshow(I_out_total, []);
title('Total Shifted by 2 Pixels');
colormap(gca, gray);



%shift with bias, this adds a constant pahse to one of the beams
bias1 = exp(1i*0);
bias2 = exp(1i*pi/4);
bias3 = exp(1i*pi/2);
bias4 = exp(1i*pi);

E_out_total1 = E_out_flipped_shifted_negative + (E_out_flipped_shifted_positive*bias1);
%Finding I_out is the E_out squared
I_out_total1 = abs(E_out_total1).^2;

E_out_total2 = E_out_flipped_shifted_negative + (E_out_flipped_shifted_positive*bias2);
%Finding I_out is the E_out squared
I_out_total2 = abs(E_out_total2).^2;

E_out_total3 = E_out_flipped_shifted_negative + (E_out_flipped_shifted_positive*bias3);
%Finding I_out is the E_out squared
I_out_total3 = abs(E_out_total3).^2;

E_out_total4 = E_out_flipped_shifted_negative + (E_out_flipped_shifted_positive*bias4);
%Finding I_out is the E_out squared
I_out_total4 = abs(E_out_total4).^2;

figure('Name', 'Question 4.1: DIC Bias 2-Pixel Shift');

subplot(2,2,1); imshow(I_out_total1, []); title('0 Bias');
subplot(2,2,2); imshow(I_out_total2, []); title('\pi/4 Bias');
subplot(2,2,3); imshow(I_out_total3, []); title('\pi/2 Bias');
subplot(2,2,4); imshow(I_out_total4, []); title('\pi Bias');

disp("Explaining if this is what i expect it to look like: No it doesnt look like what i expect. I only see the sharp edges, a blury grey mess. Summing two identical fields with zero bias means they are almost perfectly in pahse. Where the rice is flat, the two fields add up constructively. The difference in the pahse shift is nearly zero.")
%%
%4.2, shifted by +-4 pixels

imsize = 256;
radius_big = (1/4)*imsize;


%this was to set the orgin
range=imsize*(-floor(imsize/2):ceil(imsize/2)-1)/floor(imsize/2);
%made the grid for the aperature
[x,y]=meshgrid(range);

%created a array of zeroes for the aperature, and made the equation of a
%circle for the orgin
r = sqrt(x.^2 + y.^2);


%made it so that inside the radius is white, and outside is black
A_large = zeros(imsize);
A_large(r<radius_big) = 1;


%did fft of the original image, propogate through the first lens to the
%fourier plane. ffshift to center the component
output=fftshift(fft2(ifftshift(illuminated_image)));



%solved for eout, which is E_out = A * Ein, where E_in is the fft of the
%image and A is the aperture. Aperture acts as a low-pass filtler blocing
%high spatial frequecny
E_filtered = output .* A_large;
%taking the inverse fft of the E_filtered after fingin E_out in fourier
%space. Propegated through the second lens back to the spatial domain.
E_out_flipped = fftshift(ifft2(ifftshift(E_filtered)));

E_out_flipped_shifted_positive_4_2 = circshift(E_out_flipped, [0 4]);
E_out_flipped_shifted_negative_4_2 = circshift(E_out_flipped, [0 -4]);


E_out_total_42 = E_out_flipped_shifted_negative_4_2 + E_out_flipped_shifted_positive_4_2;
%Finding I_out is the E_out squared
I_out_total_42 = abs(E_out_total_42).^2;

figure
imshow(I_out_total_42, [])
title("1/2 array radius total shifted by 4 pixels")



%shift with bias
bias_4_1 = exp(1i*0);
bias_4_2 = exp(1i*pi/4);
bias_4_3 = exp(1i*pi/2);
bias_4_4 = exp(1i*pi);

E_out_total_4_1 = E_out_flipped_shifted_negative_4_2 + (E_out_flipped_shifted_positive_4_2*bias_4_1);
I_out_total_4_1 = abs(E_out_total_4_1).^2;

E_out_total_4_2 = E_out_flipped_shifted_negative_4_2 + (E_out_flipped_shifted_positive_4_2*bias_4_2);
I_out_total_4_2 = abs(E_out_total_4_2).^2;

E_out_total_4_3 = E_out_flipped_shifted_negative_4_2 + (E_out_flipped_shifted_positive_4_2*bias_4_3);
I_out_total_4_3 = abs(E_out_total_4_3).^2;

E_out_total_4_4 = E_out_flipped_shifted_negative_4_2 + (E_out_flipped_shifted_positive_4_2*bias_4_4);
I_out_total_4_4 = abs(E_out_total_4_4).^2;


figure('Name', 'Question 4.2: DIC Bias 4-Pixel Shift');

subplot(2,2,1); imshow(I_out_total_4_1, []); title('0 Bias');
subplot(2,2,2); imshow(I_out_total_4_2, []); title('\pi/4 Bias');
subplot(2,2,3); imshow(I_out_total_4_3, []); title('\pi/2 Bias');
subplot(2,2,4); imshow(I_out_total_4_4, []); title('\pi Bias');


figure('Name', 'Question 4.2: Impact of Shear Distance');

subplot(1,2,1);
imshow(I_out_total3, []); 
title('2 Pixel Shift (\pi/2 Bias)');

subplot(1,2,2);
imshow(I_out_total_4_3, []); 
title('4 Pixel Shift (\pi/2 Bias)');

disp("The best Bias value is pi/2, or 90 degrees. DIC shows the spatial derivative of the objects phase. 0 or pi are the peaks of a cosine curve, and the slope is 0, meaning theres no to little changes in the phase. At pi/2, we are at the steepest part of the cosine curve. Small changes in the phase shows a large change in brihgtness. This creates a 3d Shadow. one side of the rice will be bright and the other dark, negative slope, making a 3d object illuminated from the side.")

disp("The +- 4 pixel is a tradeoff. It improves the contrast by increasing the shift, which increases the distance the phase difference is measured. This makes deeper shadows and highlights brighter, making the grains pop more to the background. However, the resolution degrades bc i am now overlapping points further apart, and the edges of the rice will look double or blurry. I will see two grains rather than one 3D one.")

disp("+- 2 is sharper while +- 4 is bolder with higher contrast.")
