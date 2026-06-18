# Optical Microscopy Simulations in MATLAB

---

## Overview

This repository contains three MATLAB-based optical microscopy simulations completed as part of coursework in biomedical imaging. These projects explore how light interacts with biological samples and how modern imaging systems reconstruct information using Fourier optics, signal processing, and computational imaging techniques.

| Phase Contrast Microscopy              | Confocal Microscopy              | Optical Coherence Tomography |
| -------------------------------------- | -------------------------------- | ---------------------------- |
| <img width="248" height="240" alt="Screenshot 2026-06-17 at 8 11 57 PM" src="https://github.com/user-attachments/assets/38ffbdd0-f2b2-4a20-aba8-0ef261738366" />
 | ![](images/confocal_preview.png) | ![](images/oct_preview.png)  |

---

# Project 1: Phase Contrast Microscopy

## Overview

Transparent biological specimens often alter the phase of light without significantly changing intensity. This project investigates how phase information can be converted into visible contrast using Zernike Phase Contrast and Differential Interference Contrast (DIC) microscopy.

### Input Phase Object

<img width="284" height="293" alt="Screenshot 2026-06-17 at 8 15 42 PM" src="https://github.com/user-attachments/assets/853a7817-ee1a-4020-ac59-e14dd9a626b7" />


The rice image was normalized and modeled as a pure phase object. A uniform illumination field was propagated through the sample and represented as a complex optical field.

### Conventional 4f Imaging System

<img width="611" height="332" alt="Screenshot 2026-06-17 at 8 13 39 PM" src="https://github.com/user-attachments/assets/6f3b4d52-e06c-4208-a97d-c0b679ab37ff" />


The object was propagated through a simulated 4f optical system using Fourier transforms. A circular aperture was applied in the Fourier plane, acting as a low-pass spatial filter.

### Zernike Phase Contrast

<img width="530" height="487" alt="Screenshot 2026-06-17 at 8 13 55 PM" src="https://github.com/user-attachments/assets/384ebba1-6b71-4c56-bf14-0832269cd312" />


A π/2 phase-shifting dot was introduced at the center of the Fourier plane. This phase plate selectively shifts unscattered light while leaving scattered light unchanged.

<img width="595" height="310" alt="Screenshot 2026-06-17 at 8 14 03 PM" src="https://github.com/user-attachments/assets/51338e0d-8212-475b-bcb3-fcd55be591ed" />


Comparison of phase-dot diameters:

* Diameter = 1/32 image width
* Diameter = 1/8 image width

The smaller phase dot produced stronger contrast because it affected primarily the background illumination.

### Differential Interference Contrast (DIC)

<img width="607" height="306" alt="Screenshot 2026-06-17 at 8 14 58 PM" src="https://github.com/user-attachments/assets/41240ca4-617e-48bd-9cca-53c3894e438d" />


DIC imaging was simulated by laterally shifting optical fields and applying phase biases.

Key findings:

* π/2 bias produced the strongest contrast
* ±2 pixel shear produced sharper images
* ±4 pixel shear increased contrast but reduced resolution

### Skills Demonstrated

* Fourier Optics
* Complex Field Propagation
* Zernike Phase Contrast
* Differential Interference Contrast
* FFT-Based Image Reconstruction
* MATLAB

---

# Project 2: Confocal Microscopy

## Overview

This project simulates confocal fluorescence microscopy and investigates how pinhole size affects image quality and spatial resolution.

### Simulation Inputs

![](images/usaf_psfs.png)

Inputs included:

* USAF Resolution Target
* Illumination Point Spread Function
* Detection Point Spread Function

### Confocal Image Formation

The sample was scanned across the optical axis using nested loops.

For each scan position:

1. Sample shifted using circshift()
2. Fluorescence excitation calculated using PSF illumination
3. Detection PSF applied using the Optical Transfer Function
4. Signal filtered through a finite pinhole
5. Intensity summed to generate one image pixel

### Pinhole Comparison

![](images/pinhole_comparison.png)

Three pinhole radii were investigated:

* 1 pixel
* 5 pixels
* 20 pixels

### Reconstructed Confocal Images

![](images/confocal_results.png)

Smaller pinholes rejected more out-of-focus light and improved image sharpness.

### Resolution Analysis

![](images/intensity_profiles.png)

Normalized line profiles showed:

* Radius 1 produced highest resolution
* Radius 20 produced strongest signal
* Radius 5 provided a compromise

### Skills Demonstrated

* Confocal Microscopy
* Point Spread Functions
* Optical Transfer Functions
* Fourier-Domain Imaging
* Resolution Analysis
* MATLAB

---

# Project 3: Optical Coherence Tomography (OCT)

## Overview

This project simulates Spectral-Domain Optical Coherence Tomography (SD-OCT) using Gaussian optical pulses and Fourier-based depth reconstruction.

### Reference Pulse

![](images/reference_pulse.png)

A Gaussian-modulated cosine pulse was generated to represent the OCT reference arm.

### Pulse Spectrum

![](images/reference_spectrum.png)

The spectral response was calculated using:

S(f) = |FFT(E)|²

The effects of pulse frequency and pulse width on spectral bandwidth were investigated.

### Pulse Interference

![](images/interference_signal.png)

Delayed pulses were combined with the reference pulse to simulate reflections from different sample depths.

### Reflectivity Map

![](images/reflectivity_map.png)

Depth information was recovered using:

R(z) = |FFT(S(f))|²

The resulting peaks corresponded to optical path differences between reference and sample reflections.

### Multiple Reflectors

![](images/multiple_reflectors.png)

Additional delayed pulses were added to simulate multiple reflecting layers.

Observed features:

* Reference-to-sample peaks
* Sample-to-sample interference peaks
* Signal wrapping effects

### Skills Demonstrated

* Optical Coherence Tomography
* Interferometry
* Fourier Transforms
* Spectral Analysis
* Signal Processing
* MATLAB

---

## Software

* MATLAB
* Image Processing Toolbox
* FFT-Based Numerical Methods

---

## Author

Christian Abou-Ezzi
