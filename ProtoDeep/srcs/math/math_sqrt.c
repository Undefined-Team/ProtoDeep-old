<<<<<<< HEAD
#include "pd_math.h"

float math_sqrt(const float x)  
=======
#include "pd_main.h"

float   math_sqrt(const float x)
>>>>>>> 09a507c0fe53c6ad2f58040d792c556504825e4c
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
<<<<<<< HEAD
}  
=======
}
>>>>>>> 09a507c0fe53c6ad2f58040d792c556504825e4c
