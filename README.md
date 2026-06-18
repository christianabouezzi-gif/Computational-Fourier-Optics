# Computational-Fourier-Optics

# Optical Microscopy Simulations in MATLAB

---

## Project Overview

This collection contains three MATLAB-based simulations completed for **BE 518: Modern Optical Microscopy for Biomedical Imaging** at Boston University.

The projects model fundamental biomedical imaging modalities using Fourier optics, signal processing, and computational image reconstruction techniques:

1. **Phase Contrast Microscopy (Homework 3)**
2. **Confocal Microscopy (Homework 5)**
3. **Optical Coherence Tomography (Homework 6)**

These simulations demonstrate how optical systems transform light fields into measurable images and how computational methods can recover information that is otherwise invisible using conventional imaging techniques.

---

# Project 1: Simulation of Phase Contrast Microscopy

### Objective

Model the imaging of transparent phase objects and investigate methods used to convert phase variations into observable intensity contrast.

### Techniques

* Complex optical field propagation
* Fourier optics
* 4f coherent imaging systems
* Zernike phase contrast
* Differential Interference Contrast (DIC)
* FFT-based image reconstruction

### Key Results

* Demonstrated that conventional coherent imaging fails to visualize transparent phase objects.
* Implemented Zernike phase contrast using a Fourier-plane phase plate.
* Compared phase-shift mask diameters and showed that smaller phase dots produced stronger contrast.
* Simulated DIC microscopy with variable bias and shear distances.
* Investigated how phase gradients generate pseudo-relief images.

---

# Project 2: Simulation of Confocal Microscopy

### Objective

Model confocal fluorescence microscopy through sample scanning and investigate the effect of finite pinhole size on image resolution.

### Techniques

* Point Spread Functions (PSFs)
* Optical Transfer Functions (OTFs)
* Fourier-domain image formation
* Sample scanning
* Spatial filtering
* Resolution analysis

### Key Results

* Simulated fluorescence excitation and detection using illumination and detection PSFs.
* Constructed confocal images through two-dimensional sample scanning.
* Evaluated pinhole radii of 1, 5, and 20 pixels.
* Generated normalized line profiles for resolution analysis.
* Demonstrated that smaller pinholes improve resolution while reducing detected signal intensity.

---

# Project 3: Simulation of Optical Coherence Tomography (OCT)

### Objective

Simulate Spectral-Domain Optical Coherence Tomography (SD-OCT) and investigate how depth information is reconstructed from spectral interference measurements.

### Techniques

* Gaussian pulse modeling
* Fourier transforms
* Spectral-domain signal processing
* Reflectivity map reconstruction
* Interference analysis

### Key Results

* Generated Gaussian-modulated optical pulses.
* Simulated interference between reference and delayed sample pulses.
* Reconstructed depth-resolved reflectivity maps.
* Demonstrated the relationship between temporal delay and reconstructed depth.
* Investigated multi-reflector samples and artifact formation.
* Showed how stronger reference signals suppress unwanted cross-interference terms.

---

## Software

* MATLAB
* FFT-based numerical methods
* Image Processing Toolbox

---

## Learning Outcomes

These projects provided hands-on experience with:

* Fourier optics
* Optical system modeling
* Computational microscopy
* Image formation theory
* Signal reconstruction
* Biomedical imaging systems
* Frequency-domain analysis

---

## Author

Christian Abou-Ezzi
