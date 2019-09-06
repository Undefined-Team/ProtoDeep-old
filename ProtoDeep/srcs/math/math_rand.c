#include "pd_main.h"

float   pd_math_rand(float bound_a, float bound_b)
{
    static bool first_coming = true;
    static long time;
    
    if (first_coming)
    {
        struct timeval timestamp;
        first_coming = false;
        gettimeofday (&timestamp, NULL);
        time = timestamp.tv_usec;
    }
    else time *= 3;
    srand(time);
    float scale = rand() / (float) RAND_MAX;
    return bound_a < bound_b ? scale * (bound_b - bound_a) + bound_a : scale * (bound_a - bound_b) + bound_b;
}