# Optical Microscopy Simulations in MATLAB

---

## Overview

This repository contains three MATLAB-based optical microscopy simulations completed as part of coursework in biomedical imaging. These projects explore how light interacts with biological samples and how modern imaging systems reconstruct information using Fourier optics, signal processing, and computational imaging techniques.

| Phase Contrast Microscopy              | Confocal Microscopy              | Optical Coherence Tomography |
| -------------------------------------- | -------------------------------- | ---------------------------- |
| <img width="248" height="240" alt="Screenshot 2026-06-17 at 8 11 57 PM" src="https://github.com/user-attachments/assets/38ffbdd0-f2b2-4a20-aba8-0ef261738366" /> | | <img width="248" height="240" alt="Screenshot 2026-06-17 at 8 20 09 PM" src="https://github.com/user-attachments/assets/b8c96d8b-4403-460d-bf97-5d88b889d476" />| | <img width="248" height="240" alt="Screenshot 2026-06-17 at 8 24 06 PM" src="https://github.com/user-attachments/assets/9d53da4d-9bbc-426f-a7c9-c86f52dc22dd" />  |

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

<img width="579" height="196" alt="Screenshot 2026-06-17 at 8 20 35 PM" src="https://github.com/user-attachments/assets/4fa36358-8fb2-408d-af29-7eee376263ac" />


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

<img width="608" height="203" alt="Screenshot 2026-06-17 at 8 20 46 PM" src="https://github.com/user-attachments/assets/e04b6db1-f4fb-4856-8ec5-f3d6e9806c31" />


Three pinhole radii were investigated:

* 1 pixel
* 5 pixels
* 20 pixels

### Reconstructed Confocal Images

<img width="1232" height="405" alt="Screenshot 2026-06-17 at 8 20 09 PM" src="https://github.com/user-attachments/assets/a33b7197-548a-4135-9610-5fc60833463f" />


Smaller pinholes rejected more out-of-focus light and improved image sharpness.

### Resolution Analysis

<img width="633" height="517" alt="Screenshot 2026-06-17 at 8 21 03 PM" src="https://github.com/user-attachments/assets/98d7684f-b423-45ce-97a7-10bfaf28fadb" />


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

<img width="628" height="517" alt="Screenshot 2026-06-17 at 8 22 30 PM" src="https://github.com/user-attachments/assets/4059076c-f882-4a02-bbf1-203f07db8da2" />


A Gaussian-modulated cosine pulse was generated to represent the OCT reference arm.

### Pulse Spectrum

<img width="639" height="474" alt="Screenshot 2026-06-17 at 8 22 53 PM" src="https://github.com/user-attachments/assets/450b9e08-138c-40cd-a2c0-839490d418a4" />


The spectral response was calculated using:

S(f) = |FFT(E)|²

The effects of pulse frequency and pulse width on spectral bandwidth were investigated.

### Pulse Interference

<img width="649" height="484" alt="Screenshot 2026-06-17 at 8 23 26 PM" src="https://github.com/user-attachments/assets/59169fe4-7a91-460f-ba19-03697b21b3cc" />



Delayed pulses were combined with the reference pulse to simulate reflections from different sample depths.

### Reflectivity Map

<img width="653" height="518" alt="Screenshot 2026-06-17 at 8 23 31 PM" src="https://github.com/user-attachments/assets/555c467a-8f2d-4fd4-836f-892221be2568" />



Depth information was recovered using:

R(z) = |FFT(S(f))|²

The resulting peaks corresponded to optical path differences between reference and sample reflections.

### Multiple Reflectors

<img width="626" height="483" alt="Screenshot 2026-06-17 at 8 23 50 PM" src="https://github.com/user-attachments/assets/0a54ea85-2a16-47df-a4fe-a31ce5ccd01e" />

<img width="639" height="504" alt="Screenshot 2026-06-17 at 8 24 06 PM" src="https://github.com/user-attachments/assets/dde3516e-d1e4-4c90-a5c8-ff19a6ad3f07" />


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
