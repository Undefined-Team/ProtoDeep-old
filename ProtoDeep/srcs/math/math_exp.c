#include "pd_math.h"

static float fpow(float p)
{
    union { float f; uint32_t i; } vp = { p };
    int sign = (vp.i >> 31);
    int w = p;
    float z = p - w + sign;
    union { uint32_t i; float f; } v = { (1 << 23) * (p + 121.2740838f + 27.7280233f / (4.84252568f - z) - 1.49012907f * z) };
    return v.f;
}

float math_exp(float x)
{
    return fpow(1.442695040f * x);
}