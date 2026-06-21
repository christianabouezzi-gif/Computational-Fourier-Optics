# Optical Coherence Tomography (OCT) Simulation in MATLAB

---

## Project Overview

This project simulates Spectral-Domain Optical Coherence Tomography (SD-OCT) using Gaussian optical pulses and Fourier-domain reconstruction.

The objective was to understand how depth information is encoded in spectral interference patterns.

---

## Code Structure

### 1. Creating the Reference Pulse

A Gaussian-modulated cosine wave is generated.

```matlab
pulse_field = cos(2*pi*f_p*t);

E = pulse_field .* exp(-((t-t0).^2)/(sigma^2));
```

This represents the OCT reference arm.

---

### 2. Spectral Analysis

The optical spectrum is calculated using:

```matlab
S_f = abs(fft(E)).^2;
```

The effects of carrier frequency and pulse width are investigated.

---

### 3. Creating Delayed Pulses

Sample reflections are modeled using delayed copies of the reference pulse.

```matlab
pulse_delayed = cos(2*pi*f_p*(t-tau));
```

```matlab
E_delayed = pulse_delayed .* exp(-((t-t0-tau).^2)/(sigma^2));
```

---

### 4. Interference Formation

The sample and reference fields are added together.

```matlab
E_combined = E + E_delayed;
```

This produces the interference pattern measured by the OCT spectrometer.

---

### 5. Reflectivity Reconstruction

The measured spectrum is calculated.

```matlab
S(f)=|FFT(E)|²
```

Depth information is recovered through a second Fourier transform.

```matlab
R(z)=|FFT(S(f))|²
```

Peaks correspond to optical path differences between reflections.

---

### 6. Multiple Reflectors

Additional delayed pulses are introduced.

```matlab
E_combined8 = E + E_delayed + E_delayed8;
```

This simulates layered tissue structures.

---

### 7. Strong Reference Beam

The reference pulse amplitude is increased:

```matlab
E = 10*E;
```

This demonstrates how stronger reference signals improve OCT reconstruction quality.

---

## Results

### Reference Pulse

<img width="628" height="517" alt="Screenshot 2026-06-17 at 8 22 30 PM" src="https://github.com/user-attachments/assets/f36b27e6-4dca-4427-a50b-5c6688144c2f" />


### Spectrum

<img width="639" height="474" alt="Screenshot 2026-06-17 at 8 22 53 PM" src="https://github.com/user-attachments/assets/5c796c7a-0b59-4863-a952-3b0cbf33d262" />


### Interference Signal

<img width="649" height="484" alt="Screenshot 2026-06-17 at 8 23 26 PM" src="https://github.com/user-attachments/assets/cc9f1185-3437-4e16-a229-0ff42bdab9d2" />


### Reflectivity Map

<img width="653" height="518" alt="Screenshot 2026-06-17 at 8 23 31 PM" src="https://github.com/user-attachments/assets/a6b6d1be-c492-4138-aaab-d61ae547bb6a" />


### Multiple Reflectors

<img width="639" height="504" alt="Screenshot 2026-06-17 at 8 24 06 PM" src="https://github.com/user-attachments/assets/57305019-06cc-4f56-bc29-fa6497824f7f" />


---

## Key Findings

* Temporal delay is converted into depth information.
* Larger delays create more closely spaced spectral fringes.
* Multiple reflectors generate multiple peaks in R(z).
* Stronger reference beams improve signal quality.
* Fourier transforms enable depth-resolved imaging.

---

## Skills Demonstrated

* Optical Coherence Tomography
* Interferometry
* Fourier Transforms
* Spectral Analysis
* Signal Processing
* MATLAB

## Author
### Christian Abou-Ezzi
