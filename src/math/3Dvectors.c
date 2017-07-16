#include "math/3Dvectors.h"

Vect3D vect3D_new(float x, float y, float z) {
    Vect3D vect;
    vect.x = x;
    vect.y = y;
    vect.z = z;
    return vect;
}

Vect3D vect3D_zero() {
    return vect3D_new(0, 0, 0);
}

Vect3D vect3D_one() {
    return vect3D_new(1, 1, 1);
}

Vect3D vect3D_up() {
    return vect3D_new(0, 1, 0);
}

Vect3D vect3D_red() {
    return vect3D_new(1, 0, 0);
}

Vect3D vect3D_green() {
    return vect3D_new(0, 1, 0);
}

Vect3D vect3D_blue() {
    return vect3D_new(0, 0, 1);
}

Vect3D vect3D_white() {
    return vect3D_new(1, 1, 1);
}

Vect3D vect3D_black() {
    return vect3D_new(0, 0, 0);
}

Vect3D vect3D_grey() {
    return vect3D_new(0.5, 0.5, 0.5);
}

Vect3D vect3D_light_grey() {
    return vect3D_new(0.75,0.75,0.75);
}

Vect3D vect3D_dark_grey() {
    return vect3D_new(0.25,0.25,0.25);
}

Vect3D vect3D_add(Vect3D vect1, Vect3D vect2 {
    Vect3D vect;
    vect.x = vect1.x + vect2.x;
    vect.y = vect1.y + vect2.y;
    vect.z = vect1.z + vect2.z;
    return vect;
}

Vect3D vect3D_sub(Vect3D vect1, Vect3D vect2) {
    Vect3D vect;
    vect.x = vect1.x - vect2.x;
    vect.y = vect1.y - vect2.y;
    vect.z = vect1.z - vect2.z;
    return vect;
}

Vect3D vect3D_mult(Vect3D vect, float fact) {
    Vect3D vect_mult;
    vect_mult.x = vect.x * fact;
    vect_mult.y = vect.y * fact;
    vect_mult.z = vect.z * fact;
    return vect_mult;
}

Vect3D vect3D_mult_vect3D(Vect3D vect1, Vect3D vect2) {
    Vect3D vect;
    vect.x = vect1.x * vect2.x;
    vect.y = vect1.y * vect2.y;
    vect.z = vect1.z * vect2.z;
    return vect;
}

Vect3D vect3D_div(Vect3D vect, float fact) {
    Vect3D vect_div;
    vect_div.x = vect.x / fact;
    vect_div.y = vect.y / fact;
    vect_div.z = vect.z / fact;
    return vect_div;
}

Vect3D vect3D_div_vect3D(Vect3D vect1, Vect3D vect2) {
    Vect3D vect;
    vect.x = vect1.x / vect2.x;
    vect.y = vect1.y / vect2.y;
    vect.z = vect1.z / vect2.z;
    return vect;
}

Vect3D vect3D_pow(Vect3D vect, float power) {
    Vect3D vect_pow;
    vect_pow.x = pow(vect.x, power);
    vect_pow.y = pow(vect.y, power);
    vect_pow.z = pow(vect.z, power);
    return vect;
}

Vect3D vect3D_negative(Vect3D vect) {
    Vect3D vect_neg;
    vect_neg.x = -vect.x;
    vect_neg.y = -vect.y;
    vect_neg.z = -vect.z;
    return vect_neg;
}

Vect3D vect3D_abs(Vect3D vect) {
    Vect3D vect_abs;
    vect_abs.x = max(vect.x, -vect.x);
    vect_abs.y = max(vect.y, -vect.y);
    vect_abs.z = max(vect.z, -vect.z);
    return vect_abs;
}

Vect3D vect3D_floor(Vect3D vect) {
    Vect3D vect_floor;
    vect_floor.x = (int)vect.x;
    vect_floor.y = (int)vect.y;
    vect_floor.z = (int)vect.z;
    return vect_floor;
}

Vect3D vect3D_fmod(Vect3D vect, float val) {
    Vect3D vect_fmod;
    vect_fmod.x = vect.x - val * (int)(vect.x / val);
    vect_fmod.y = vect.y - val * (int)(vect.y / val);
    vect_fmod.z = vect.z - val * (int)(vect.z / val);
    return vect_fmod;
}

bool vect3D_equ(Vect3D vect1, Vect3D vect2) {
    if (vect1.x != vect2.x) return false;
    if (vect1.y != vect2.y) return false;
    if (vect1.z != vect2.z) return false;
    return true;
}

bool vect3D_neq(Vect3D vect1, Vect3D vect2) {
    if (vect1.x != vect2.x) return true;
    if (vect1.y != vect2.y) return true;
    if (vect1.z != vect2.z) return true;
    return false;
}

float vect3D_dot(Vect3D vect1, Vect3D vect2) {
    return vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z;
}

float vect3D_length_sqrd(Vect3D vect) {
    return vect3D_dot(vect, vect);
}

float vect3D_length(Vect3D vect) {
    return sqrt(vect3D_length_sqrd(vect));
}

float vect3D_dist_sqrd(Vect3D vect1, Vect3D vect2) {
    Vect3D vect = vect3D_sub(vect1, vect2);
    return vect3D_dot(vect, vect);
}

float vect3D_dist(Vect3D vect1, Vect3D vect2) {
    return sqrt(vect3D_dist_sqrd(vect1, vect2));
}

float vect3D_dist_manhattan(Vect3D vect1, Vect3D vect2) {
    return max(vect1.x - vect2.x, vect2.x - vect1.x)
         + max(vect1.y - vect2.y, vect2.y - vect1.y)
         + max(vect1.z - vect2.z, vect2.z - vect1.z);
}

Vect3D vect3D_cross(Vect3D vect1, Vect3D vect2) {
    Vect3D vect;
    vect.x = vect1.y * vect2.z - vect1.z * vect2.y;
    vect.y = vect1.z * vect2.x - vect1.x * vect2.z;
    vect.z = vect1.x * vect2.y - vect1.y * vect2.x;
    return vect;
}

Vect3D vect3D_normalize(Vect3D vect) {
    if (vect3D_length(vect))
        return vec3D_div(vect, vect3D_length(vect));
    else
        return vect3D_zero();
}

Vect3D vect3D_reflect(Vect3D vect1, Vect3D vect2) {
    return vect3D_sub(vect1, vect3D_mult(vect2, 2 * vect3D_dot(vect1, vect2)));
}

Vect3D vect3D_project(Vect3D vect1, Vect3D vect2) {
    return vect3D_sub(vect1, vect3D_mult(vect2, vect3D_dot(vect1, vect2)));
}

Vect3D vect3D_from_string(char* s) {
    char* pEnd;
    double d1, d2, d3;
    d1 = strtod(s,&pEnd);
    d2 = strtod(pEnd,&pEnd);
    d3 = strtod(pEnd,NULL);
    Vect3D vect;
    vect.x = d1;
    vect.y = d2;
    vect.z = d3;
    return vect;
}

void vect3D_print(Vect3D vect) {
    printf("Vect3D(%4.2f,%4.2f,%4.2f)", vect.x, vect.y, vect.z);
}

void vect3D_to_array(Vect3D vect, float* out) {
    out[0] = vect.x;
    out[1] = vect.y;
    out[2] = vect.z;
}

int vect3D_hash(Vect3D vect) {
    return max(rawcast(vect.x)^rawcast(vect.y)^rawcast(vect.z), -(rawcast(vect.x)^rawcast(vect.y)^rawcast(vect.z)));
}

Vect3D vect3D_saturate(Vect3D vect) {
    Vect3D vect_saturate;
    vect_saturate.x = saturate(vect.x);
    vect_saturate.y = saturate(vect.y);
    vect_saturate.z = saturate(vect.z);
    return vect_saturate;
}

Vect3D vect3D_lerp(Vect3D vect1, Vect3D vect2, float amount) {
    Vect3D vect_lerp;
    vect_lerp.x = lerp(vect1.x, vect2.x, amount);
    vect_lerp.y = lerp(vect1.y, vect2.y, amount);
    vect_lerp.z = lerp(vect1.z, vect2.z, amount);
    return vect_lerp;
}

Vect3D vect3D_smoothstep(Vect3D vect1, Vect3D vect2, float amount) {
    float scaled_amount = amount * amount * (3 - 2 * amount);
    return vect3D_lerp(vect1, vect2, scaled_amount);
}

Vect3D vect3D_smootherstep(Vect3D vect1, Vect3D vect2, float amount) {
    float scaled_amount = amount * amount * amount * (amount * (amount * 6 - 15) + 10);
    return vect3D_lerp(vect1, vect2, scaled_amount);
}
