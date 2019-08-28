#ifndef PD_MATH_H
# define PD_MATH_H

// Lib

// Macro
#define EXPO_E 2.718281801

// Structures

// Prototypes
float       math_max(float x, float y);
float       math_min(float x, float y);
float       math_max_a(t_float_a x);
float       math_min_a(t_float_a x);
float       math_atof(const char* s);
void        math_si_sort(t_arr arr);

float       math_sigmoid(float x);
float       math_relu(float x);
float       math_lrelu(float x);
float       math_tanh(float x);
t_float_a   math_softmax(t_float_a x);

float       math_log(float x);
float       math_exp(float p);
float       math_pow(float x, float e);
float       math_sqrt(const float x);

float       math_mean(t_float_a x);
float       math_stdev(t_float_a x, float mean);

#endif