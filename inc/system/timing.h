#ifndef _TIMING_
#define _TIMING_

#include "common.h"

typedef struct {
    int id;
    unsigned long start;
    unsigned long end;
    unsigned long split;
} timer;

timer timer_start(int id, const char* tag);
timer timer_split(timer t, const char* tag);
timer timer_stop(timer t, const char* tag);

void timestamp(char* out);

#endif /* end of include guard: _TIMING_ */
