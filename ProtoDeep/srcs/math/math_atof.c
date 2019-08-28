#include "pd_main.h"

float math_atof(const char *p)
{
    int frac;
    float sign, value, scale;

    while (white_space(*p) )
        p += 1;
    sign = 1.0;
    if (*p == '-')
    {
        sign = -1.0;
        p += 1;
    }
    else if (*p == '+')
        p += 1;
    for (value = 0.0; valid_digit(*p); p += 1)
        value = value * 10.0 + (*p - '0');
    if (*p == '.')
    {
        float pow10 = 10.0;
        p += 1;
        while (valid_digit(*p))
        {
            value += (*p - '0') / pow10;
            pow10 *= 10.0;
            p += 1;
        }
    }
    frac = 0;
    scale = 1.0;
    if ((*p == 'e') || (*p == 'E'))
    {
        unsigned int expon;
        p += 1;
        if (*p == '-')
        {
            frac = 1;
            p += 1;
        }
        else if (*p == '+')
            p += 1;
        for (expon = 0; valid_digit(*p); p += 1)
            expon = expon * 10 + (*p - '0');
        if (expon > 308) expon = 308;
        while (expon >= 50) { scale *= 1E50; expon -= 50; }
        while (expon >=  8) { scale *= 1E8;  expon -=  8; }
        while (expon >   0) { scale *= 10.0; expon -=  1; }
    }
    return sign * (frac ? (value / scale) : (value * scale));
}