#include "math/4Dvectors.h"

Vect4D vect4D_new(float x, float y, float z, float t) {
    Vect4D vect;
    vect.x = x;
    vect.y = y;
    vect.z = z;
    vect.t = t;
    return vect;
}

Vect4D vect4D_zero() {
    return vect3D_new(0, 0, 0, 0);
}

Vect4D vect4D_one() {
    return vect3D_new(1, 1, 1, 1);
}

Vect4D vect4D_red() {
    return vect3D_new(1, 0, 0, 1);
}

Vect4D vect4D_green() {
    return vect3D_new(0, 1, 0, 1);
}

Vect4D vect4D_blue() {
    return vect3D_new(0, 0, 1, 1);
}

Vect4D vect4D_white() {
    return vect3D_new(1, 1, 1, 1);
}

Vect4D vect4D_black() {
    return vect3D_new(0, 0, 0, 1);
}

Vect4D vect4D_grey() {
    return vect3D_new(0.5, 0.5, 0.5, 1);
}

Vect4D vect4D_light_grey() {
    return vect3D_new(0.75, 0.75, 0.75, 1);
}

Vect4D vect4D_dark_grey() {
    return vect3D_new(0.25, 0.25, 0.25, 1);
}

Vect4D vect4D_add(Vect4D vect1, Vect4D vect2) {
    Vect4D vect;
    vect.x = vect1.x + vect2.x;
    vect.y = vect1.y + vect2.y;
    vect.z = vect1.z + vect2.z;
    vect.t = vect1.t + vect2.t;
    return vect;
}

Vect4D vect4D_sub(Vect4D vect1, Vect4D vect2) {
    Vect4D vect;
    vect.x = vect1.x - vect2.x;
    vect.y = vect1.y - vect2.y;
    vect.z = vect1.z - vect2.z;
    vect.t = vect1.t - vect2.t;
    return vect;
}

Vect4D vect4D_mult(Vect4D vect, float fact) {
    Vect4D vect_mult;
    vect_mult.x = vect.x * fact;
    vect_mult.y = vect.y * fact;
    vect_mult.z = vect.z * fact;
    vect_mult.t = vect.t * fact;
    return vect_mult;
}

Vect4D vect4D_mult_vect4D(Vect4D vect1, Vect4D vect2) {
    Vect4D vect;
    vect.x = vect1.x * vect2.x;
    vect.y = vect1.y * vect2.y;
    vect.z = vect1.z * vect2.z;
    vect.t = vect1.t * vect2.t;
    return vect;
}

Vect4D vect4D_div(Vect4D vect, float fact) {
    Vect4D vect_div;
    vect_div.x = vect.x / fact;
    vect_div.y = vect.y / fact;
    vect_div.z = vect.z / fact;
    vect_div.t = vect.t / fact;
    return vect_div;
}

Vect4D vect4D_pow(Vect4D vect, float power) {
    Vect4D vect_pow;
    vect_pow.x = pow(vect.x, power);
    vect_pow.y = pow(vect.y, power);
    vect_pow.z = pow(vect.z, power);
    vect_pow.t = pow(vect.t, power);
    return vect_pow;
}

Vect4D vect4D_negative(Vect4D vect) {
    Vect4D vect_neg;
    vect_neg.x = -vect.x;
    vect_neg.y = -vect.y;
    vect_neg.z = -vect.z;
    vect_neg.t = -vect.t;
    return vect_neg;
}

Vect4D vect4D_abs(Vect4D vect) {
    Vect4D vect_abs;
    vect_abs.x = max(vect.x, -vect.x);
    vect_abs.y = max(vect.y, -vect.y);
    vect_abs.z = max(vect.z, -vect.z);
    vect_abs.t = max(vect.t, -vect.t);
    return vect_abs;
}

Vect4D vect4D_floor(Vect4D vect) {
    Vect4D vect_floor;
    vect_floor.x = (int)vect.x;
    vect_floor.y = (int)vect.y;
    vect_floor.z = (int)vect.z;
    vect_floor.t = (int)vect.t;
    return vect_floor;
}

Vect4D vect4D_fmod(Vect4D vect, float val) {
    Vect4D vect_fmod;
    vect_fmod.x = vect.x - val * (int)(vect.x / val);
    vect_fmod.y = vect.y - val * (int)(vect.y / val);
    vect_fmod.z = vect.z - val * (int)(vect.z / val);
    vect_fmod.t = vect.t - val * (int)(vect.t / val);
    return vect_fmod;
}

Vect4D vect4D_sqrt(Vect4D vect) {
    Vect4D vect_sqrt;
    vect_sqrt.x = sqrt(vect.x);
    vect_sqrt.y = sqrt(vect.y);
    vect_sqrt.z = sqrt(vect.z);
    vect_sqrt.t = sqrt(vect.t);
    return vect_sqrt;
}

Vect4D vect4D_max(Vect4D vect1, Vect4D vect2) {
    Vect4D vect_max;
    vect_max.x = max(vect1.x, vect2.x);
    vect_max.y = max(vect1.y, vect2.y);
    vect_max.z = max(vect1.z, vect2.z);
    vect_max.t = max(vect1.t, vect2.t);
    return vect_max;
}

Vect4D vect4D_min(Vect4D vect1, Vect4D vect2) {
    Vect4D vect_min;
    vect_min.x = min(vect1.x, vect2.x);
    vect_min.y = min(vect1.y, vect2.y);
    vect_min.z = min(vect1.z, vect2.z);
    vect_min.t = min(vect1.t, vect2.t);
    return vect_min;
}

bool vect4D_equ(Vect4D vect1, Vect4D vect2) {
    if (vect1.x != vect2.x) return false;
    if (vect1.y != vect2.y) return false;
    if (vect1.z != vect2.z) return false;
    if (vect1.t != vect2.t) return false;
    return true;
}

float vect4D_dot(Vect4D vect1, Vect4D vect2) {
    return vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z + vect1.t * vect2.t;
}

float vect4D_length_sqrd(Vect4D vect) {
    return vect4D_dot(vect, vect);
}

float vect4D_length(Vect4D vect) {
    return sqrt(vect4D_length_sqrd(vect));
}

float vect4D_dist_sqrd(Vect4D vect1, Vect4D vect2) {
    Vect4D vect = vect4D_sub(vect1, vect2);
    return vect4D_dot(vect, vect);
}

float vect4D_dist(Vect4D vect1, Vect4D vect2) {
    return sqrt(vect4D_dist_sqrd(vect1, vect2));
}

float vect4D_dist_manhattan(Vect4D vect1, Vect4D vect2) {
    return max(vect1.x - vect2.x, vect2.x - vect1.x)
         + max(vect1.y - vect2.y, vect2.y - vect1.y)
         + max(vect1.z - vect2.z, vect2.z - vect1.z)
         + max(vect1.t - vect2.t, vect2.t - vect1.t);
}

Vect4D vect4D_normalize(Vect4D vect) {
    if (vect4D_length(vect))
        return vec4D_div(vect, vect4D_length(vect));
    else
        return vect4D_zero();
}

Vect4D vect4D_reflect(Vect4D vect1, Vect4D vect2) {
    return vect4D_sub(vect1, vect4D_mult(vect2, 2 * vect4D_dot(vect1, vect2)));
}

Vect4D vect4D_from_string(char* s) {
    char* pEnd;
    double d1, d2, d3, d4;
    d1 = strtod(s,&pEnd);
    d2 = strtod(pEnd,&pEnd);
    d3 = strtod(pEnd,&pEnd);
    d4 = strtod(pEnd,NULL);
    Vect4D vect;
    vect.x = d1;
    vect.y = d2;
    vect.z = d3;
    vect.t = d4;
    return vect;
}

void vect4D_print(Vect4D vect) {
    printf("Vect4D(%4.2f, %4.2f, %4.2f, %4.2f)", vect.x, vect.y, vect.z, vect.w);
}

void vect4D_to_array(Vect4D vect, float* out) {
    out[0] = vect.x;
    out[1] = vect.y;
    out[2] = vect.z;
    out[3] = vect.t;
}

Vect4D vect3D_to_homogeneous(Vect3D vect) {
    return vect4D_new(vect.x, vect.y, vect.z, 1.0);
}

Vect3D vect4D_from_homogeneous(Vect4D vect) {
    Vect3D vect3D = vect3D_new(vect.x, vect.y, vect.z);
    return vect3D_div(vect3D, vect.t);
}

int vect4D_hash(Vect4D vect) {
    return max(rawcast(vect.x)^rawcast(vect.y)^rawcast(vect.z)^rawcast(vect.t), -(rawcast(vect.x)^rawcast(vect.y)^rawcast(vect.z)^rawcast(vect.t)));
}

Vect4D vect4D_saturate(Vect4D vect) {
    Vect4D vect_saturate;
    vect_saturate.x = saturate(vect.x);
    vect_saturate.y = saturate(vect.y);
    vect_saturate.z = saturate(vect.z);
    vect_saturate.t = saturate(vect.t);
    return vect_saturate;
}

Vect4D vect4D_lerp(Vect4D vect1, Vect4D vect2, float amount) {
    Vect4D vect_lerp;
    vect_lerp.x = lerp(vect1.x, vect2.x, amount);
    vect_lerp.y = lerp(vect1.y, vect2.y, amount);
    vect_lerp.z = lerp(vect1.z, vect2.z, amount);
    vect_lerp.t = lerp(vect1.t, vect2.t, amount);
    return vect_lerp;
}

Vect4D vect4D_smoothstep(Vect4D vect1, Vect4D vect2, float amount) {
    float scaled_amount = amount * amount * (3 - 2 * amount);
    return vect4D_lerp(vect1, vect2, scaled_amount);
}

Vect4D vect4D_smootherstep(Vect4D vect1, Vect4D vect2, float amount) {
    float scaled_amount = amount * amount * amount * (amount * (amount * 6 - 15) + 10);
    return vect4D_lerp(vect1, vect2, scaled_amount);
}

Vect4D vect4D_nearest_interp(Vect4D vect1, Vect4D vect2, float amount) {
    Vect4D vect;
    vect.x = nearest_interp(vect1.x, vect2.x, amount);
    vect.y = nearest_interp(vect1.y, vect2.y, amount);
    vect.z = nearest_interp(vect1.z, vect2.z, amount);
    vect.t = nearest_interp(vect1.t, vect2.t, amount);
    return vect;
}

Vect4D vect4D_binearest_interp(Vect4D top_left, Vect4D top_right, Vect4D bottom_left, Vect4D bottom_right, float x_amount, float y_amount) {
    Vect4D vect;
    vect.x = binearest_interp(top_left.x, top_right.x, bottom_left.x, bottom_right.x, x_amount, y_amount);
    vect.y = binearest_interp(top_left.y, top_right.y, bottom_left.y, bottom_right.y, x_amount, y_amount);
    vect.z = binearest_interp(top_left.z, top_right.z, bottom_left.z, bottom_right.z, x_amount, y_amount);
    vect.t = binearest_interp(top_left.t, top_right.t, bottom_left.t, bottom_right.t, x_amount, y_amount);
    return vect;
}

Vect4D vect4D_bilinear_interp(Vect4D top_left, Vect4D top_right, Vect4D bottom_left, Vect4D bottom_right, float x_amount, float y_amount) {
    Vect4D vect;
    vect.x = bilinear_interp(top_left.x, top_right.x, bottom_left.x, bottom_right.x, x_amount, y_amount);
    vect.y = bilinear_interp(top_left.y, top_right.y, bottom_left.y, bottom_right.y, x_amount, y_amount);
    vect.z = bilinear_interp(top_left.z, top_right.z, bottom_left.z, bottom_right.z, x_amount, y_amount);
    vect.t = bilinear_interp(top_left.t, top_right.t, bottom_left.t, bottom_right.t, x_amount, y_amount);
    return vect;
}
