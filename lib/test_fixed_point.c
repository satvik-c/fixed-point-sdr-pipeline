#include "fixed_point.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

void print_test_header(const char* name) {
    printf("\n--- Testing %s ---\n", name);
}

void test_conversions() {
    print_test_header("Conversions");
    
    assert(q15_from_float(0.5f) == 16384);
    assert(q15_from_float(-0.5f) == -16384);
    assert(q15_from_float(0.0f) == 0);
    
    assert(q15_from_float(-1.0f) == Q_MIN);
    assert(q15_from_float(1.0f) == Q_MAX); 
    assert(q15_from_float(1.5f) == Q_MAX);
    assert(q15_from_float(-2.0f) == Q_MIN);

    assert(fabs(float_from_q15(16384) - 0.5f) < 0.0001f);
    assert(fabs(float_from_q15(Q_MIN) - (-1.0f)) < 0.0001f);
    
    printf("Conversions: PASSED\n");
}

void test_addition() {
    print_test_header("Addition & Saturation");
    
    q15_t half = q15_from_float(0.5f);
    q15_t quart = q15_from_float(0.25f);
    
    assert(q15_add(quart, quart) == half);
    
    q15_t p6 = q15_from_float(0.6f);
    assert(q15_add(p6, p6) == Q_MAX);
    
    q15_t n7 = q15_from_float(-0.7f);
    q15_t n4 = q15_from_float(-0.4f);
    assert(q15_add(n7, n4) == Q_MIN);

    printf("Addition: PASSED\n");
}

void test_multiplication() {
    print_test_header("Multiplication");
    
    q15_t a = q15_from_float(0.5f);
    q15_t b = q15_from_float(0.5f);
    
    assert(q15_mul(a, b) == q15_from_float(0.25f));
    
    assert(q15_mul(q15_from_float(-0.5f), a) == q15_from_float(-0.25f));
    
    q15_t neg1 = q15_from_float(-1.0f);
    assert(q15_mul(neg1, neg1) == Q_MAX);
    
    assert(q15_mul(1, 1) == 0);

    printf("Multiplication: PASSED\n");
}

void test_mac() {
    print_test_header("Multiply-Accumulate (MAC)");
    
    int32_t acc = 0;
    q15_t val = q15_from_float(0.5f);
    
    q15_mac(val, val, &acc);
    assert(acc == 268435456);
    
    q15_mac(val, val, &acc);
    assert(acc == 536870912);
    
    acc = 0;
    q15_mac(q15_from_float(-0.5f), val, &acc);
    assert(acc == -268435456);

    printf("MAC: PASSED\n");
}

void test_utilities() {
    print_test_header("Utilities (Negate/Abs/Shift)");
    
    q15_t val = q15_from_float(0.5f);
    q15_t nval = q15_from_float(-0.5f);
    
    assert(q15_negate(val) == nval);
    assert(q15_negate(q15_from_float(-1.0f)) == Q_MAX);
    
    assert(q15_abs(nval) == val);
    assert(q15_abs(q15_from_float(-1.0f)) == Q_MAX);

    assert(q15_shift_right(val, 1) == q15_from_float(0.25f));
    assert(q15_shift_right(nval, 1) == q15_from_float(-0.25f));

    printf("Utilities: PASSED\n");
}

int main() {
    printf("Starting Q15 Arithmetic Test Suite...\n");
    
    test_conversions();
    test_addition();
    test_multiplication();
    test_mac();
    test_utilities();
    
    printf("\n==============================\n");
    printf("  ALL TESTS PASSED SUCCESSFULLY\n");
    printf("==============================\n");
    
    return 0;
}