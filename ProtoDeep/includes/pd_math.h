#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef PD_MATH_H
# define PD_MATH_H

// Macro
#define EXPO_E 2.718281801

// Structures

// Prototypes
float   math_max(float x, float y);
float   math_sigmoid(float x);
float   math_relu(float x);
float   math_lrelu(float x);
float   math_tanh(float x);
float   math_exp(float x);
float   *math_softmax(float *x, int len);
float math_log(float x);
float math_exp(float p);
float math_pow(float x, float e);

#endif