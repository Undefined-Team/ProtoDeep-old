#include "pd_main.h"

float   math_sigmoid(float x)
{
    return 1 / (1 + math_exp(-x));
}

float   math_relu(float x)
{
    return math_max(0, x);
}

float   math_lrelu(float x)
{
    return math_max(0.1 * x, x);
}

float   math_tanh(float x)
{
    return 1 - (2 / (math_exp(2 * x) + 1));
}

t_float_a   math_softmax(t_float_a x)
{
    float sum = 0;
    t_float_a y;

    PROT_ARR_TYPE(x.type, T_FLOAT);
    y = arrInit(T_FLOAT, x.len);
    for (size_t i = 0; i < y.len; i++)
    {
        ((float*)y.val)[i] = math_exp(((float*)x.val)[i]);
        sum += ((float*)y.val)[i];
    }
    for (size_t i = 0; i < y.len; i++)
        ((float*)y.val)[i] /= sum;
    return y;
}