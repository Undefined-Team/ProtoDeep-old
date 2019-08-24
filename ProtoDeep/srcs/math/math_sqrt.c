#include "pd_main.h"

float   math_sqrt(const float x)
{
  union
  {
    int i;
    float x;
  } u;
  u.x = x;
  u.i = (1<<29) + (u.i >> 1) - (1<<22); 
  u.x = u.x + x/u.x;
  u.x = 0.25f*u.x + x/u.x;

  return u.x;
}