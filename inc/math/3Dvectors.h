#ifndef _3D_VECTORS_
#define _3D_VECTORS_

#include "real.h"

typedef struct {
    float x; float y; float z;
} Vect3D;

Vect3D vect3D_new(float x, float y, float z);
Vect3D vect3D_zero();
Vect3D vect3D_one();
Vect3D vect3D_up();

Vect3D vect3D_red();
Vect3D vect3D_green();
Vect3D vect3D_blue();
Vect3D vect3D_white();
Vect3D vect3D_black();
Vect3D vect3D_grey();
Vect3D vect3D_light_grey();
Vect3D vect3D_dark_grey();

Vect3D vect3D_add(Vect3D vect1, Vect3D vect2);
Vect3D vect3D_sub(Vect3D vect1, Vect3D vect2);
Vect3D vect3D_mult(Vect3D vect, float fact);
Vect3D vect3D_mult_vect3D(Vect3D vect1, Vect3D vect2);
Vect3D vect3D_div(Vect3D vect, float fact);
Vect3D vect3D_div_vect3D(Vect3D vect1, Vect3D vect2);
Vect3D vect3D_pow(Vect3D vect, float power);
Vect3D vect3D_negative(Vect3D vect);
Vect3D vect3D_abs(Vect3D vect);
Vect3D vect3D_floor(Vect3D vect);
Vect3D vect3D_fmod(Vect3D vect, float val);

bool vect3D_equ(Vect3D vect1, Vect3D vect2);
bool vect3D_neq(Vect3D vect1, Vect3D vect2);

float vect3D_dot(Vect3D vect1, Vect3D vect2);
float vect3D_length_sqrd(Vect3D vect);
float vect3D_length(Vect3D vect);
float vect3D_dist_sqrd(Vect3D vect1, Vect3D vect2);
float vect3D_dist(Vect3D vect1, Vect3D vect2);
float vect3D_dist_manhattan(Vect3D vect1, Vect3D vect2);
Vect3D vect3D_cross(Vect3D vect1, Vect3D vect2);
Vect3D vect3D_normalize(Vect3D vect);

Vect3D vect3D_reflect(Vect3D vect1, Vect3D vect2);
Vect3D vect3D_project(Vect3D vect1, Vect3D vect2);

Vect3D vect3D_from_string(char* s);
void vect3D_print(Vect3D vect);

void vect3D_to_array(Vect3D vect, float* out);

int vect3D_hash(Vect3D vect);

Vect3D vect3D_saturate(Vect3D vect);
Vect3D vect3D_lerp(Vect3D vect1, Vect3D vect2, float amount);
Vect3D vect3D_smoothstep(Vect3D vect1, Vect3D vect2, float amount);
Vect3D vect3D_smootherstep(Vect3D vect1, Vect3D vect2, float amount);

#endif /* end of include guard: _3D_VECTORS_ */
