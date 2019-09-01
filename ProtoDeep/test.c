#include <stdio.h>

int main(void)
{
    long test = 0;

    for(int y = 0; y < 10; y++)
    {
        for (int i = 0; i < 1000000000; i++)
        {
            //printf("%d\n", (int)test);
            test++;
        }
    }

    return (0);
}

// cast = 57s
// 46