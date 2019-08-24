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

t_farr   math_softmax(t_farr x)
{
    float sum = 0;
    t_farr y;

    y = dast_new_farr(x.len);
    for (size_t i = 0; i < y.len; i++)
    {
        y.arr[i] = math_exp(x.arr[i]);
        sum += y.arr[i];
    }
    for (size_t i = 0; i < y.len; i++)
        y.arr[i] /= sum;
    return y;
}