#include "pd_math.h"

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

float   *math_softmax(float *x, size_t len)
{
    float sum = 0;
    float *y;

    y = malloc(sizeof(int) * len);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = math_exp(x[i]);
        sum += y[i];
    }
    for (size_t i = 0; i < len; i++)
        y[i] /= sum;
    return y;
}