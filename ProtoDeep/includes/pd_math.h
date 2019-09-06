#ifndef PD_MATH_H
# define PD_MATH_H

// Lib

// Macro
#define PD_EXPO_E           2.718281801
#define pd_white_space(c)   ((c) == ' ' || (c) == '\t')
#define pd_valid_digit(c)   ((c) >= '0' && (c) <= '9')
#define pd_math_abs(x)      (x < 0 ? x * -1 : x)   

// Structures

// Prototypes
float                       pd_math_max(float x, float y);
float                       pd_math_min(float x, float y);
float                       pd_math_max_a(pd_float_a x);
float                       pd_math_min_a(pd_float_a x);
float                       pd_math_atof(const char* s);
pd_char_a                   pd_math_itoa(int n);
void                        pd_math_si_sort(pd_arr arr);
float                       pd_math_rand(float bound_a, float bound_b);

float                       pd_math_sigmoid(float x);
float                       pd_math_relu(float x);
float                       pd_math_lrelu(float x);
float                       pd_math_tanh(float x);
pd_float_a                  pd_math_softmax(pd_float_a x);

float                       pd_math_log(float x);
float                       pd_math_exp(float p);
float                       pd_math_pow(float x, float e);
float                       pd_math_sqrt(const float x);

float                       pd_math_mean(pd_float_a x);
float                       pd_math_stdev(pd_float_a x, float mean);

#endif