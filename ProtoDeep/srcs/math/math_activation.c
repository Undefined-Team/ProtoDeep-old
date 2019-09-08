#include "pd_main.h"

float   pd_math_sigmoid(float x)
{
    return 1 / (1 + pd_math_exp(-x));
}

float   pd_math_relu(float x)
{
    return pd_math_max(0, x);
}

float   pd_math_lrelu(float x)
{
    return pd_math_max(0.1 * x, x);
}

float   pd_math_tanh(float x)
{
    return 1 - (2 / (pd_math_exp(2 * x) + 1));
}

pd_float_a*   pd_math_softmax(pd_float_a* x)
{
    float sum = 0;
    pd_float_a* y;

    PD_PROT_ARR_TYPE(x->type, PD_T_FLOAT);
    y = pd_arr_init(PD_T_FLOAT, x->len);
    size_t y_len = y->len;
    float *a_y = (float*)y->val;
    float *a_x = (float*)x->val;
    for (size_t i = 0; i < y_len; i++)
    {
        a_y[i] = pd_math_exp(a_x[i]);
        sum += a_y[i];
    }
    for (size_t i = 0; i < y_len; i++)
        a_y[i] /= sum;
    return y;
}