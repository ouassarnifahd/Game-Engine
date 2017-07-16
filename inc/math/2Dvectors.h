#ifndef _2D_VECTORS_
#define _2D_VECTORS_

#include "real.h"

typedef struct {
    float x; float y;
} Vect2D;

Vect2D vect2D_new(float x, float y);
Vect2D vect2D_zero();
Vect2D vect2D_one();

Vect2D vect2D_add(Vect2D vect1, Vect2D vect2);
Vect2D vect2D_sub(Vect2D vect1, Vect2D vect2);
Vect2D vect2D_mult(Vect2D vect, float fact);
Vect2D vect2D_mult_vect2D(Vect2D vect1, Vect2D vect2);
Vect2D vect2D_div(Vect2D vect, float fact);
Vect2D vect2D_div_vect2D(Vect2D vect1, Vect2D vect2);
Vect2D vect2D_pow(Vect2D vect, float exp);
Vect2D vect2D_negative(Vect2D vect);
Vect2D vect2D_abs(Vect2D vect);
Vect2D vect2D_floor(Vect2D vect);
Vect2D vect2D_fmod(Vect2D vect, float val);

Vect2D vect2D_max(Vect2D vect, float x);
Vect2D vect2D_min(Vect2D vect, float x);
Vect2D vect2D_clamp(Vect2D vect, float b, float t);

bool vect2D_equ(Vect2D vect1, Vect2D vect2);

float vect2D_dot(Vect2D vect1, Vect2D vect2);
float vect2D_length_sqrd(Vect2D vect);
float vect2D_length(Vect2D vect);
float vect2D_dist_sqrd(Vect2D vect1, Vect2D vect2);
float vect2D_dist(Vect2D vect1, Vect2D vect2);
float vect2D_dist_manhattan(Vect2D vect1, Vect2D vect2);
Vect2D vect2D_normalize(Vect2D vect);

Vect2D vect2D_reflect(Vect2D vect1, Vect2D vect2);

Vect2D vect2D_from_string(char* s);
void vect2D_print(Vect2D vect);

void vect2D_to_array(Vect2D vect, float* out);

int vect2D_hash(Vect2D vect);
int vect2D_mix_hash(Vect2D vect);

Vect2D vect2D_saturate(Vect2D vect);
Vect2D vect2D_lerp(Vect2D vect1, Vect2D vect2, float amount);
Vect2D vect2D_smoothstep(Vect2D vect1, Vect2D vect2, float amount);
Vect2D vect2D_smootherstep(Vect2D vect1, Vect2D vect2, float amount);

#endif /* end of include guard: _2D_VECTORS_ */
