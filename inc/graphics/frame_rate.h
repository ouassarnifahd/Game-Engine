#ifndef _FRAME_RATE_
#define _FRAME_RATE_

#include "common.h"

void frame_begin();
void frame_end();
void frame_end_at_rate(double fps);

double frame_rate();
double frame_time();
char* frame_rate_string();

#endif /* end of include guard: _FRAME_RATE_ */
