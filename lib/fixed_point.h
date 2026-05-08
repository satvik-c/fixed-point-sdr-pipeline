#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <stdint.h>

#define Q_FACTOR (1 << 15)
#define Q_MAX (q15_t) 0x7FFF
#define Q_MIN (q15_t) 0x8000

typedef int16_t q15_t;
typedef int32_t q31_t;

q15_t q15_from_float(float);
float float_from_q15(q15_t);
q15_t q15_add(q15_t, q15_t);
q15_t q15_mul(q15_t, q15_t);
void q15_mac(q15_t, q15_t, int32_t*);
q15_t q15_negate(q15_t);
q15_t q15_abs(q15_t);
q15_t q15_shift_right(q15_t, int);

#endif