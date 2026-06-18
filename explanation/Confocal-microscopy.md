# Confocal Microscopy Simulation in MATLAB

---

## Project Overview

This project simulates image formation in a confocal fluorescence microscope.

The objective was to investigate how illumination, detection optics, and pinhole size affect image resolution.

---

## Code Structure

### 1. Loading Optical Components

The simulation loads:

```matlab
USAF128.tif
psf_ill.tif
psf_det.tif
```

These represent:

* Sample
* Illumination PSF
* Detection PSF

---

### 2. Creating the Pinhole

The pinhole is modeled as a binary circular mask.

```matlab
r = sqrt(x.^2+y.^2);
A(r<radius)=1;
```

Three radii were tested:

```text
1 pixel
5 pixels
20 pixels
```

---

### 3. Sample Scanning

The USAF target is scanned through the optical system.

```matlab
shifted_sample = circshift(USAF,[x y]);
```

Each shift represents one confocal scan position.

---

### 4. Excitation

Fluorescence excitation is calculated using:

```matlab
Fluo_intensity = shifted_sample .* PSF_ill;
```

Only regions illuminated by the excitation beam emit fluorescence.

---

### 5. Detection Using OTF

The detection PSF is converted into an Optical Transfer Function.

```matlab
OTF = fftshift(fft2(ifftshift(PSF_det)));
```

The fluorescence image is transformed into frequency space.

```matlab
FFT_fluo = fft2(Fluo_intensity);
```

Detection blur is applied through:

```matlab
FFT_fluo .* OTF
```

---

### 6. Pinhole Filtering

The image arriving at the pinhole is spatially filtered.

```matlab
image_at_pinhole .* A
```

Only light passing through the pinhole reaches the detector.

---

### 7. Confocal Pixel Formation

The detector measures total intensity.

```matlab
sum(sum(image_at_pinhole .* A))
```

This value becomes one pixel in the final confocal image.

---

## Results

### Simulation Inputs

<img width="579" height="196" alt="Screenshot 2026-06-17 at 8 20 35 PM" src="https://github.com/user-attachments/assets/64dec316-3e69-4bf3-b331-29be197ae491" />


### Pinhole Masks

<img width="608" height="203" alt="Screenshot 2026-06-17 at 8 20 46 PM" src="https://github.com/user-attachments/assets/1bfb98b0-2802-40a6-940b-0ed86132a78f" />


### Confocal Reconstructions

<img width="1232" height="405" alt="Screenshot 2026-06-17 at 8 20 09 PM" src="https://github.com/user-attachments/assets/2cc7b346-660b-4bb5-b070-5638323a1028" />


### Resolution Analysis

<img width="633" height="517" alt="Screenshot 2026-06-17 at 8 21 03 PM" src="https://github.com/user-attachments/assets/cb00b34a-54e1-47dd-af13-f1a92fe3e126" />


---

## Key Findings

* Smaller pinholes reject out-of-focus light.
* Radius = 1 produced the highest resolution.
* Radius = 20 produced the highest signal.
* Resolution and signal intensity must be balanced in practical systems.

---

## Skills Demonstrated

* Confocal Microscopy
* Point Spread Functions
* Optical Transfer Functions
* Fourier Imaging
* Resolution Analysis
* MATLAB
