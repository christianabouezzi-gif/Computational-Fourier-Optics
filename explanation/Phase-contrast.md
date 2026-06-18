# Phase Contrast Microscopy Simulation in MATLAB

---

## Project Overview

This project simulates multiple phase-imaging techniques commonly used in optical microscopy. Transparent biological specimens often introduce phase shifts in transmitted light without changing intensity, making them difficult to visualize using conventional brightfield microscopy.

The goal of this project was to model how phase information can be converted into measurable intensity contrast using:

* Conventional Coherent Imaging
* Zernike Phase Contrast Microscopy
* Differential Interference Contrast (DIC) Microscopy

---

## Code Structure

### 1. Creating the Phase Object

The simulation begins by loading and normalizing a grayscale rice image.

```matlab
rice = double(imread('rice.tif'));
rice = rice/max(rice(:));
```

The image is treated as a phase-only object:

```matlab
U = exp(1i*pi*rice);
```

This represents a transparent sample that alters the phase of light but not its intensity.

---

### 2. Fourier Plane Propagation

The optical field is propagated through a simulated 4f imaging system.

```matlab
U_FT = fftshift(fft2(ifftshift(U)));
```

The Fourier transform converts the image into spatial-frequency space.

---

### 3. Circular Aperture

A circular aperture is applied in the Fourier plane.

```matlab
A = zeros(N);
A(r<R) = 1;
```

This models the microscope objective and acts as a low-pass filter.

---

### 4. Conventional Image Reconstruction

The image is reconstructed using an inverse Fourier transform.

```matlab
image = abs(ifft2(U_filtered)).^2;
```

Because the object only changes phase, very little contrast is visible.

---

### 5. Zernike Phase Contrast

A phase dot is introduced at the center of Fourier space.

```matlab
phase_dot(center_region) = exp(1i*pi/2);
```

This shifts the phase of unscattered light by π/2.

The scattered and unscattered light interfere when transformed back into image space, producing visible contrast.

---

### 6. Differential Interference Contrast

Two shifted copies of the optical field are generated.

```matlab
U1 = circshift(U,[0 shear]);
U2 = circshift(U,[0 -shear]);
```

A phase bias is applied:

```matlab
U_DIC = U1 + U2*exp(1i*bias);
```

This converts phase gradients into intensity variations.

---

## Results

### Phase Object


<img width="607" height="301" alt="Screenshot 2026-06-17 at 8 52 35 PM" src="https://github.com/user-attachments/assets/cca2e585-1131-4a73-acb8-b3aad94eb693" />



### Conventional Imaging
<img width="611" height="332" alt="Screenshot 2026-06-17 at 8 13 39 PM" src="https://github.com/user-attachments/assets/d06953a4-44ac-4cef-b53c-720c3302dc24" />



### Zernike Phase Contrast

<img width="595" height="310" alt="Screenshot 2026-06-17 at 8 14 03 PM" src="https://github.com/user-attachments/assets/52f061c2-4a17-4370-8b40-c17bd2cae84f" />



### DIC Imaging

<img width="607" height="306" alt="Screenshot 2026-06-17 at 8 14 58 PM" src="https://github.com/user-attachments/assets/34d66f86-33a0-4c6a-94de-48cf7371ca6a" />


---

## Key Findings

* Conventional imaging provides little contrast for phase objects.
* Zernike phase contrast converts phase variations into visible intensity changes.
* Smaller phase dots produce stronger image contrast.
* DIC highlights phase gradients and edges.
* Phase bias and shear distance strongly affect image appearance.

---

## Skills Demonstrated

* Fourier Optics
* Complex Field Propagation
* FFT Analysis
* Phase Contrast Microscopy
* DIC Microscopy
* MATLAB
