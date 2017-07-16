#ifndef _REAL_
#define _REAL_

#include "common.h"

int rawcast(float x);

#ifndef max
    float max(float x, float y);
#endif
#ifndef min
    float min(float x, float y);
#endif

float clamp(float x, float bottom, float top);
float saturate(float x);
bool between(float x, float bottom, float top);
bool between_or(float x, float bottom, float top);

float lerp(float p1, float p2, float amount);
float smoothstep(float p1, float p2, float amount);
float smootherstep(float p1, float p2, float amount);
float cosine_interp(float p1, float p2, float amount);
float cubic_interp(float p1, float p2, float p3, float p4, float amount);
float nearest_interp(float p1, float p2, float amount);

float binearest_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);
float bilinear_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);
float bicosine_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);
float bismoothstep_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);
float bismootherstep_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);

#endif /* end of include guard: _REAL_ */
