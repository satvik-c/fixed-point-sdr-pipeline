#include <stdlib.h>
#include <stdio.h>
#include "rtl-sdr.h"
#include "fixed_point.h"

#define MAX_COUNT 2048000
#define SAMPLE_RATE 2048000

typedef struct {
    q15_t* buffer;
    int count;
    rtlsdr_dev_t* dev;
} capture_ctx_t;

q15_t convert(uint8_t val) {
    return ((q15_t)(val - 127) << 8);
}

void callback(uint8_t* buf, uint32_t len, void* ctx) {
    capture_ctx_t* c = (capture_ctx_t*) ctx;
    for (int i = 0; i < len; i += 2) {
        if (c->count >= MAX_COUNT) {
            rtlsdr_cancel_async(c->dev);
            return;
        }
        c->buffer[c->count*2] = convert(buf[i]);
        c->buffer[c->count*2 + 1] = convert(buf[i+1]);
        c->count++;
    }
}

int main() {
    rtlsdr_dev_t* dev = NULL;
    rtlsdr_open(&dev, 0);

    rtlsdr_set_sample_rate(dev, SAMPLE_RATE);
    rtlsdr_set_center_freq(dev, 100000000);
    rtlsdr_set_tuner_gain_mode(dev, 0);

    capture_ctx_t c;
    c.buffer = (q15_t*) malloc(MAX_COUNT * 2 * sizeof(q15_t));
    c.count = 0;
    c.dev = dev;

    rtlsdr_reset_buffer(dev);
    rtlsdr_read_async(dev, callback, &c, 0, 0);

    FILE* f = fopen("iq_capture.bin", "wb");
    fwrite(c.buffer, sizeof(q15_t), c.count * 2, f);
    fclose(f);

    rtlsdr_close(dev);
    free(c.buffer);
}