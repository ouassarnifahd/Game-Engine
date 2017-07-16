#include "math/2Dvectors.h"

Vect2D vect2D_new(float x, float y) {
    Vect2D vect;
    vect.x = x;
    vect.y = y;
    return vect;
}

Vect2D vect2D_zero() {
    return vect2D_zero(0, 0);
}

Vect2D vect2D_one() {
    return vect2D_zero(1, 1);
}

Vect2D vect2D_add(Vect2D vect1, Vect2D vect2) {
    Vect2D vect;
    vect.x = vect1.x + vect2.x;
    vect.y = vect1.y + vect2.y;
    return vect;
}

Vect2D vect2D_sub(Vect2D vect1, Vect2D vect2) {
    Vect2D vect;
    vect.x = vect1.x - vect2.x;
    vect.y = vect1.y - vect2.y;
    return vect;
}

Vect2D vect2D_mult(Vect2D vect, float fact) {
    Vect2D mult;
    mult.x = vect.x * fact;
    mult.y = vect.y * fact;
    return mult;
}

Vect2D vect2D_mult_vect2D(Vect2D vect1, Vect2D vect2) {
    Vect2D vect;
    vect.x = vect1.x * vect2.x;
    vect.y = vect1.y * vect2.y;
    return vect;
}

Vect2D vect2D_div(Vect2D vect, float fact) {
    Vect2D vect_div;
    vect_div.x = vect.x / fact;
    vect_div.y = vect.y / fact;
    return vect_div;
}

Vect2D vect2D_div_vect2D(Vect2D vect1, Vect2D vect2) {
    Vect3D vect;
    vect.x = vect1.x / vect2.x;
    vect.y = vect1.y / vect2.y;
    return vect1;
}

Vect2D vect2D_pow(Vect2D vect, float power) {
    Vect2D vect_pow;
    vect_pow.x = pow(vect.x, power);
    vect_pow.y = pow(vect.y, power);
    return vect_pow;
}

Vect2D vect2D_negative(Vect2D vect) {
    Vect2D vect_neg;
    vect_neg.x = -vect.x;
    vect_neg.y = -vect.y;
    return vect_neg;
}

Vect2D vect2D_abs(Vect2D vect) {
    Vect2D vect_abs;
    vect_abs.x = max(vect.x, -vect.x);
    vect_abs.y = max(vect.y, -vect.y);
    return vect_abs;
}

Vect2D vect2D_floor(Vect2D vect) {
    Vect2D vect_floor;
    vect_floor.x = (int)vect.x;
    vect_floor.y = (int)vect.y;
    return vect_floor;
}

Vect2D vect2D_fmod(Vect2D vect, float val) {
    Vect2D vect_fmod;
    vect_fmod.x = vect.x - val * (int)(vect.x / val);
    vect_fmod.y = vect.y - val * (int)(vect.y / val);
    return vect_fmod;
}

Vect2D vect2D_max(Vect2D vect, float x) {
    Vect2D vect_max;
    vect_max.x = max(vect.x, x);
    vect_max.y = max(vect.y, x);
    return vect_max;
}

Vect2D vect2D_min(Vect2D vect, float x) {
    Vect2D vect_min;
    vect_min.x = min(vect.x, x);
    vect_min.y = min(vect.y, x);
    return vect_min;
}

Vect2D vect2D_clamp(Vect2D vect, float b, float t) {
    Vect2D vect_clamp;
    vect_clamp.x = clamp(vect.x, b, t);
    vect_clamp.y = clamp(vect.y, b, t);
    return vect_clamp;
}

bool vect2D_equ(Vect2D vect1, Vect2D vect2) {
    if(!(vect1.x == vect2.x)) return false;
    if(!(vect1.y == vect2.y)) return false;
    return true;
}

float vect2D_dot(Vect2D vect1, Vect2D vect2) {
    return vect1.x * vect2.x + vect1.y * vect2.y;
}

float vect2D_length_sqrd(Vect2D vect) {
    return vect2D_dot(vect, vect);
}

float vect2D_length(Vect2D vect) {
    return sqrt(vect2D_length_sqrd(vect));
}

float vect2D_dist_sqrd(Vect2D vect1, Vect2D vect2) {
    Vect2D vect = vect2D_sub(vect1, vect2);
    return vect2D_dot(vect, vect);
}

float vect2D_dist(Vect2D vect1, Vect2D vect2) {
    return sqrt(vect2D_dist_sqrd(vect1, vect2));
}

float vect2D_dist_manhattan(Vect2D vect1, Vect2D vect2) {
    return max(vect1.x - vect2.x, vect2.x - vect1.x) + max(vect1.y - vect2.y, vect2.y - vect1.y);
}

Vect2D vect2D_normalize(Vect2D vect){
    if (vect2D_length(vect))
        return vec2D_div(vect, vect2D_length(vect));
    else
        return vect2D_zero();
}

Vect2D vect2D_reflect(Vect2D vect1, Vect2D vect2) {
    return vect2D_sub(vect1, vect2D_mult(vect2, 2 * vect2D_dot(vect1, vect2)));
}

Vect2D vect2D_from_string(char* s) {
    char* pEnd;
    double d1, d2;
    d1 = strtod(s,&pEnd);
    d2 = strtod(pEnd,NULL);
    Vect2D vect;
    vect.x = d1;
    vect.y = d2;
    return vect;
}

void vect2D_print(Vect2D vect) {
    printf("Vect2D(%4.2f,%4.2f)", vect.x, vect.y);
}

void vect2D_to_array(Vect2D vect, float* out) {
    out[0] = vect.x;
    out[1] = vect.y;
}

int vect2D_hash(Vect2D vect) {
    return max(rawcast(vect.x)^rawcast(vect.y), -(rawcast(vect.x)^rawcast(vect.y)));
}

int vect2D_mix_hash(Vect2D vect) {
    int raw_vx = abs(rawcast(v.x)), raw_vy = abs(rawcast(v.y));
    int h1 = raw_vx << 1, h2 = raw_vy << 3, h3 = raw_vx >> 8;
    int h4 = raw_vy << 7, h5 = raw_vx >> 12, h6 = raw_vy >> 15;
    int h7 = raw_vx << 2, h8 = raw_vy << 6, h9 = raw_vx >> 2;
    int h10 = raw_vy << 9, h11 = raw_vx >> 21, h12 = raw_vy >> 13;
    int res1 = h1 ^ h2 ^ h3, res2 = h4 ^ h5 ^ h6;
    int res3 = h7 ^ h8 ^ h9, res4 = h10 ^ h11 ^ h12;
    return (res1 * 10252247) ^ (res2 * 70209673) ^ (res3 * 104711) ^ (res4 * 63589);
}

Vect2D vect2D_saturate(Vect2D vect) {
    Vect2D vect_saturate;
    vect_saturate.x = saturate(vect.x);
    vect_saturate.y = saturate(vect.y);
    return vect_saturate;
}

Vect2D vect2D_lerp(Vect2D vect1, Vect2D vect2, float amount) {
    Vect2D vect_lerp;
    vect_lerp.x = lerp(vect1.x, vect2.x, amount);
    vect_lerp.y = lerp(vect1.y, vect2.y, amount);
    return vect_lerp;
}

Vect2D vect2D_smoothstep(Vect2D vect1, Vect2D vect2, float amount) {
    float scaled_amount = amount * amount * (3 - 2 * amount);
    return vect2D_lerp(vect1, vect2, scaled_amount);
}

Vect2D vect2D_smootherstep(Vect2D vect1, Vect2D vect2, float amount) {
    float scaled_amount = amount * amount * amount * (amount * (amount * 6 - 15) + 10);
    return vect2D_lerp(vect1, vect2, scaled_amount);
}
