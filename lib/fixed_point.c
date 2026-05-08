#include "fixed_point.h"

q15_t q15_from_float(float f) {
    if (f >= 1) return Q_MAX;
    else if (f < -1) return Q_MIN;
    return (q15_t)(f * Q_FACTOR);
}

float float_from_q15(q15_t q) {
    return (float) q / Q_FACTOR;
}

q15_t q15_add(q15_t a, q15_t b) {
    int32_t res = (int32_t) a + (int32_t) b;
    if (res > Q_MAX) res = Q_MAX;
    else if (res < Q_MIN) res = Q_MIN;
    return (q15_t) res;
}

q15_t q15_mul(q15_t a, q15_t b) {
    int32_t intermediate = (int32_t) a * (int32_t) b;
    intermediate = intermediate >> 15;
    if (intermediate > Q_MAX) intermediate = (int32_t) Q_MAX;
    return (q15_t) intermediate;
}

void q15_mac(q15_t a, q15_t b, int32_t* acc) {
    int32_t intermediate = (int32_t) a * (int32_t) b;
    *acc += intermediate;
}

q15_t q15_negate(q15_t q) {
    if (q == Q_MIN) q = Q_MAX;
    else q = -q;
    return q;
}

q15_t q15_abs(q15_t q) {
    if (q < 0) q = q15_negate(q);
    return q;
}

q15_t q15_shift_right(q15_t q, int n) {
    return q >> n;
}