# fixed-point-sdr-pipeline

I'm building a software defined radio DSP pipeline from scratch in C, using a cheap RTL-SDR USB dongle as the hardware front end. My goal is to understand how DSP algorithms map directly to hardware by implementing everything in fixed-point Q1.15 arithmetic, which mirrors how FPGA multipliers and DSP blocks work. I'm not using any signal processing libraries, just C and the fixed-point arithmetic I write myself.

## Pipeline

Raw IQ samples come in from the dongle over USB, get filtered by a windowed-sinc FIR low-pass filter, decimated down to baseband sample rate, then FM demodulated using CORDIC atan2 to extract audio. A fixed-point FFT runs in parallel for spectrum visualization. Each stage has defined input/output Q-formats, structured the same way as an RTL datapath pipeline.

## Progress

- [X] Fixed-point math library (`lib/`) — Q1.15 arithmetic covering saturating multiply, saturating add, multiply-accumulate with a 32-bit accumulator, absolute value, negate, and arithmetic right shift. All operations use 32-bit intermediates to avoid precision loss before truncating back to Q1.15. Unit tested against floating-point reference values.
- [X] IQ ingestion (`ingest/`) — reads raw 8-bit IQ samples from the RTL-SDR dongle via librtlsdr, converts to Q15, and writes to a binary file. Verified by plotting the FFT spectrum in Python (`/tools`) and confirming FM station peaks are visible at correct frequencies.
- [ ] FIR low-pass filter
- [ ] Decimation
- [ ] FM demodulation (CORDIC atan2)
- [ ] Fixed-point FFT