import numpy as np
import matplotlib.pyplot as plt

samples = np.fromfile("../ingest/iq_capture.bin", dtype=np.int16)

I = samples[0::2]
Q = samples[1::2]

iq = I + 1j * Q

spectrum = np.fft.fftshift(np.fft.fft(iq))
magnitude = 20 * np.log10(np.abs(spectrum) + 1)

freqs = np.fft.fftshift(np.fft.fftfreq(len(iq), 1/2048000))
freqs_mhz = (freqs + 100e6) / 1e6

plt.figure(figsize=(12, 5))
plt.plot(freqs_mhz, magnitude)
plt.xlabel("Frequency (MHz)")
plt.ylabel("Magnitude (dB)")
plt.title("IQ Spectrum around 100 MHz")
plt.grid(True)
plt.savefig("spectrum.png")