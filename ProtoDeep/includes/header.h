#ifndef HEADER_H
#define HEADER_H

// Dependences
#include <stdlib.h>

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


#endif