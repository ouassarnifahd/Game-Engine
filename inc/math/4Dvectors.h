#ifndef _4D_VECTORS_
#define _4D_VECTORS_

#include "3Dvectors.h"

typedef struct {
    float x; float y; float z; float t;
} Vect4D;

Vect4D vect4D_new(float x, float y, float z, float t);
Vect4D vect4D_zero();
Vect4D vect4D_one();

Vect4D vect4D_red();
Vect4D vect4D_green();
Vect4D vect4D_blue();
Vect4D vect4D_white();
Vect4D vect4D_black();
Vect4D vect4D_grey();
Vect4D vect4D_light_grey();
Vect4D vect4D_dark_grey();

Vect4D vect4D_add(Vect4D vect1, Vect4D vect2);
Vect4D vect4D_sub(Vect4D vect1, Vect4D vect2);
Vect4D vect4D_mult(Vect4D vect, float fact);
Vect4D vect4D_mult_vect4D(Vect4D vect1, Vect4D vect2);
Vect4D vect4D_div(Vect4D vect, float fact);
Vect4D vect4D_pow(Vect4D vect, float power);
Vect4D vect4D_negative(Vect4D vect);
Vect4D vect4D_abs(Vect4D vect);
Vect4D vect4D_floor(Vect4D vect);
Vect4D vect4D_fmod(Vect4D vect, float val);
Vect4D vect4D_sqrt(Vect4D vect);

Vect4D vect4D_max(Vect4D vect1, Vect4D vect2);
Vect4D vect4D_min(Vect4D vect1, Vect4D vect2);
bool vect4D_equ(Vect4D vect1, Vect4D vect2);

float vect4D_dot(Vect4D vect1, Vect4D vect2);
float vect4D_length_sqrd(Vect4D vect);
float vect4D_length(Vect4D vect);
float vect4D_dist_sqrd(Vect4D vect1, Vect4D vect2);
float vect4D_dist(Vect4D vect1, Vect4D vect2);
float vect4D_dist_manhattan(Vect4D vect1, Vect4D vect2);
Vect4D vect4D_normalize(Vect4D vect);

Vect4D vect4D_reflect(Vect4D vect1, Vect4D vect2);

Vect4D vect4D_from_string(char* s);
void vect4D_print(Vect4D vect);

void vect4D_to_array(Vect4D vect, float* out);

Vect4D vect3D_to_homogeneous(Vect3D vect);
Vect3D vect4D_from_homogeneous(Vect4D vect);

int vect4D_hash(Vect4D vect);

Vect4D vect4D_saturate(Vect4D vect);
Vect4D vect4D_lerp(Vect4D vect1, Vect4D vect2, float amount);
Vect4D vect4D_smoothstep(Vect4D vect1, Vect4D vect2, float amount);
Vect4D vect4D_smootherstep(Vect4D vect1, Vect4D vect2, float amount);
Vect4D vect4D_nearest_interp(Vect4D vect1, Vect4D vect2, float amount);

Vect4D vect4D_binearest_interp(Vect4D top_left, Vect4D top_right, Vect4D bottom_left, Vect4D bottom_right, float x_amount, float y_amount);
Vect4D vect4D_bilinear_interp(Vect4D top_left, Vect4D top_right, Vect4D bottom_left, Vect4D bottom_right, float x_amount, float y_amount);

#endif /* end of include guard: _4D_VECTORS_ */
