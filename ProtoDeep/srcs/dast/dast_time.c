#include "pd_main.h"

double    pd_dast_update_time(void)
{
    static struct timeval  pd_time_before;
    static struct timeval  pd_time_after;
    static bool            first_coming = true;

    if (first_coming)
    {
        gettimeofday (&pd_time_before, NULL);
        first_coming = false;
        return 0;
    }
    gettimeofday (&pd_time_after, NULL);
    long int time = ((pd_time_after.tv_sec - pd_time_before.tv_sec) * 1000000 + pd_time_after.tv_usec) - pd_time_before.tv_usec;
    double realtime = (double)time / 1000000;
    gettimeofday (&pd_time_before, NULL);
    return realtime;
}