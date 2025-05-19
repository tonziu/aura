#include "aura.h"

bool timer_Tick(double now, aura_Timer* timer)
{
    double elapsed = now - timer->start;
    if (elapsed > timer->rate)
    {
        timer->start = now;
        return true;
    }
    return false;
}

