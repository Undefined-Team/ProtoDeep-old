#ifndef PD_MATH_H
# define PD_MATH_H

// Lib

// Macro
#define EXPO_E 2.718281801

// Structures

// Prototypes
float   math_max(float x, float y);
float   math_min(float x, float y);
float   math_max_a(float *x, size_t len);
float   math_min_a(float *x, size_t len);
float   math_atof(const char* s);

float   math_sigmoid(float x);
float   math_relu(float x);
float   math_lrelu(float x);
float   math_tanh(float x);
float   *math_softmax(float *x, size_t len);

float   math_log(float x);
float   math_exp(float p);
float   math_pow(float x, float e);

float   math_mean(float *x, size_t len);
float   math_stdev(float *x, size_t len, float mean);

#endif