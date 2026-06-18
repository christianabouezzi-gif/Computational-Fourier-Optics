%read the USAF, PSF ill, and PSF det as doubles to create arrays
USAF = double(imread('USAF128.tif'));
PSF_ill = double(imread('psf_ill.tif'));
PSF_det = double(imread('psf_det.tif'));

%print out each image in a suplot
figure('Name', 'USAF, PSF_ill, and PSF_det');
sgtitle('USAF, PSF ill, PSF det');

subplot(1,3,1)
imshow(USAF, []);
title('USAF');

subplot(1,3,2)
imshow(PSF_ill, []);
title('PSF ill');

subplot(1,3,3)
imshow(PSF_det, []);
title('PSF det')
%%
%pinhole function should have the radius of 5
imsize = 128;
radius = 5;


%this was to set the orgin
range=imsize*(-floor(imsize/2):ceil(imsize/2)-1)/floor(imsize/2);
%made the grid for the pinhole
[x,y]=meshgrid(range);

%created a array of zeroes for the pinhole, and made the equation of a
%circle for the orgin
r = sqrt(x.^2 + y.^2);


%made it so that inside the radius is white, and outside is black
A = zeros(imsize);
A(r<radius) = 1;
%%
%create a dummy array to store values in 
map = zeros(41,41);

%nested loop to shift 41 pixels in x and y axis
for x = -20:20
    for y = -20:20
    %circshift based on x and y values, shifting 41 pixels x and y
    shifted_sample = circshift(USAF, [x y]);
    %multiply the shifted sample by the PSF ill, det, and the aperture to
    %simulate 2D scanning.
    light_detector = shifted_sample .*PSF_ill .*PSF_det.*A;
    %storing the values in the dummy array every shift
    map(x+21, y+21) = sum(light_detector(:));
    end
end

%show the shifted values of 5 radius
figure
imshow(map,[])
title("Shifted map with 5 raidus pinhole")

%%
%simulating a confocal image

%start with a dummy array to store values
map2 = zeros(41,41);
%store the OTF value
OTF = fftshift(fft2(ifftshift(PSF_det)));

%nested loop to shift 41 pixels in x and y axis
for x2 = -20:20
    for y2 = -20:20
    %circshift based on x and y values, shifting 41 pixels x and y
    shifted_sample2 = circshift(USAF, [x2 y2]);
    %getting the fluorescent intensity by multiplying the shifted sample
    %and the PSF illumination
    Fluo_intensity = shifted_sample2 .* PSF_ill;
    %take the fourier transform to work in the fourier space
    FFT_fluo = fftshift(fft2(ifftshift(Fluo_intensity)));
    %multiply the intesntiy and the OTF
    image_at_pinhole_FFT = FFT_fluo .* OTF;
    %bring back to the spatial domain
    image_at_pinhole = abs(fftshift(ifft2(ifftshift(image_at_pinhole_FFT))));
    %storing intensities into the dummy array
    map2(x2+21, y2+21) = sum(sum(image_at_pinhole .* A));
    end
end
%%
%pinhole function should have the radius of 1
imsize = 128;
radius2 = 1;


%this was to set the orgin
range2=imsize*(-floor(imsize/2):ceil(imsize/2)-1)/floor(imsize/2);
%made the grid for the pinhole
[x,y]=meshgrid(range2);

%created a array of zeroes for the pinhole, and made the equation of a
%circle for the orgin
r2 = sqrt(x.^2 + y.^2);


%made it so that inside the radius is white, and outside is black
A2 = zeros(imsize);
A2(r2<radius2) = 1;

%same as the 5 radius umage, but with 1 radius instead
map3 = zeros(41,41);
OTF2 = fftshift(fft2(ifftshift(PSF_det)));

for x3 = -20:20
    for y3 = -20:20
    shifted_sample3 = circshift(USAF, [x3 y3]);
    Fluo_intensity2 = shifted_sample3 .* PSF_ill;
    FFT_fluo2 = fftshift(fft2(ifftshift(Fluo_intensity2)));
    image_at_pinhole_FFT2 = FFT_fluo2 .* OTF2;
    image_at_pinhole2 = abs(fftshift(ifft2(ifftshift(image_at_pinhole_FFT2))));
    map3(x3+21, y3+21) = sum(sum(image_at_pinhole2 .* A2));
    end
end
%%
%pinhole function should have the radius of 20
imsize = 128;
radius3 = 20;


%this was to set the orgin
range3=imsize*(-floor(imsize/2):ceil(imsize/2)-1)/floor(imsize/2);
%made the grid for the pinhole
[x,y]=meshgrid(range3);

%created a array of zeroes for the pinhole, and made the equation of a
%circle for the orgin
r3 = sqrt(x.^2 + y.^2);


%made it so that inside the radius is white, and outside is black
A3 = zeros(imsize);
A3(r3<radius3) = 1;

%same as other two radius image, but with 20 radius
map4 = zeros(41,41);
OTF3 = fftshift(fft2(ifftshift(PSF_det)));

for x4 = -20:20
    for y4 = -20:20
    shifted_sample4 = circshift(USAF, [x4 y4]);
    Fluo_intensity3 = shifted_sample4 .* PSF_ill;
    FFT_fluo3 = fftshift(fft2(ifftshift(Fluo_intensity3)));
    image_at_pinhole_FFT3 = FFT_fluo3.* OTF3;
    image_at_pinhole3 = abs(fftshift(ifft2(ifftshift(image_at_pinhole_FFT3))));
    map4(x4+21, y4+21) = sum(sum(image_at_pinhole3 .* A3));
    end
end
%%
%displaying the pinhole of radius 5
figure('Name', 'Aperture')
subplot(1,3,1)
imshow(A, []);
title('Aperture radius of 5 pixels')

%displaying the pinhole of radius 1
subplot(1,3,2)
imshow(A2, []);
title('Aperture radius of 1 pixels')

%displaying the pinhole of radius 20
subplot(1,3,3)
imshow(A3, []);
title('Aperture radius of 20 pixels')

sgtitle('Apertures')
%%
%displying the resulting image
figure('Name', 'OTF images')
subplot(1,3,1)
imshow(map2, [])
title('Confocal image OTF method radius 5')

subplot(1,3,2)
imshow(map3, [])
title('Confocal image OTF method radius 1')

subplot(1,3,3)
imshow(map4, [])
title('Confocal image OTF method radius 20')

sgtitle('OTF images')
%%

%plotting normalized intensity plots for each radius
figure('Name', 'Intensity Plot')

plot(-20:20, map2(21,:)/max(map2(21,:)))
hold on
plot(-20:20, map3(21,:)/max(map3(21,:)))
plot(-20:20, map4(21,:)/max(map4(21,:)))
hold off

title('Normalized Intensity Profiles');
xlabel('Pixels');
ylabel('Normalized Intensity (0 to 1)');
legend('5 Radius', '1 Radius', '20 Radius');
grid on;
hold off;

disp('The pinhole with the best resolution is radius = 1. We have the sharpest peaks and deepest valleys. The smaller the pinhole, the more it refects out of focus light. When the pinhole shrinks, the PSF of the system narrows, improving resolution. An infitiely small pinhole is not systematically used because a pinhole that is too small blocks almost all the light emitted by the smaple, so zero photons reach the detector. When the signal gets weak, the noise is stronger than the actual image.')

%Explanation: I began the simulation by initalizing the USAD, PSF ill, and
%PSF det. We simulate the scanning process by using a nested for loop to
%shift the smaple across a fixed optical path. The first step is to
%multiply the sample that shifted by the PSF ill to calculate fluorescence
%excitation. This is the light spot created by the laser hiting the sample.
%Only a small part of the smaple overlaps with the focused laser beam and
%capable of emiting light. In incoherent imaging, this is on a pinhole
%plane. The fluorescnece was put into the frequency domain using fft, and
%multiplied by the OTF which is the fft of the PSFdet. This is necessary bc
%it simulates how the microscope blurs the light as it traveels towards the
%detector. The inverse fft brings in back into the spatial domain. This
%gives us the intensity ariving at the pinhole. abs is used to make sure
%the intensity is real valued, get rid of artifacts.

%The last step for each scanned spot was spatial filtering and detection.
%The blurred image at the pinhole was multiplied by a binary mask which is
%a (65,65). this blocks out of focus light, allowing the central in focus
%light to pass through. The intesnity is then summed to a single scalar
%value and stored in a matrix, all repeated with using radius of 1 5 and
%20. The larger pinholes allowed more light, and the normalized intensity
%plots showed the R = 1 pinhole had the best resolution. The smaller the
%aperture, the sharper disntiction between spaced features. 
