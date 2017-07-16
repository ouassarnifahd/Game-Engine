#include "math/real.h"

int rawcast(float x) {
    union {
        float f;
        int i;
    } u;
    u.f = x;
    return u.i;
}

float max(float x, float y) {
    return x > y ? x : y;
}

float min(float x, float y) {
    return x > y ? y : x;
}

float clamp(float x, float bottom, float top) {
    x = max(x, bottom);
    x = min(x, top);
    return x;
}

bool between(float x, float bottom, float top) {
    return (x > bottom) && (x < top);
}

bool between_or(float x, float bottom, float top) {
    return (x >= bottom) && (x <= top);
}

float saturate(float x) {
    x = max(x, 0.0);
    x = min(x, 1.0);
    return x;
}

float lerp(float p1, float p2, float amount) {
    return (p2 * amount) + (p1 * (1 - amount));
}

float smoothstep(float p1, float p2, float amount) {
    float scaled_amount = amount * amount * (3 - 2 * amount);
    return lerp(p1, p2, scaled_amount);
}

float smootherstep(float p1, float p2, float amount) {
    float scaled_amount = amount * amount * amount * (amount * ( amount * 6 - 15) + 10);
    return lerp(p1, p2, scaled_amount);
}

float cosine_interp(float p1, float p2, float amount) {
   float mu2 = (1 - cos(amount * M_PI))/2;
   return (p2 * (1 - mu2) + p1 * mu2);
}

float nearest_interp(float p1, float p2, float amount) {
    amount = roundf(amount);
    if (amount) return p2;
    else return p1;
}

float cubic_interp(float p1, float p2, float p3, float p4, float amount) {
    float amount_sqrd = amount * amount;
    float amount_cubd = amount * amount * amount;

    float a1 = p4 - p3 - p2 + p1;
    float a2 = p1 - p2 - a1;
    float a3 = p3 - p1;
    float a4 = p2;

    return (a1 * amount_cubd) + (a2 * amount_sqrd) + (a3 * amount) + a4;
}

float binearest_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount) {
    x_amount = roundf(x_amount);
    y_amount = roundf(y_amount);

    if (x_amount && !y_amount) return br;
    if (!x_amount && y_amount) return tl;
    if (!x_amount && !y_amount) return bl;
    if (x_amount && y_amount) return tr;

    return 0.0f;
}

float bilinear_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount) {
    float left = lerp(tl, bl, y_amount);
    float right = lerp(tr, br, y_amount);
    return lerp(right, left, x_amount);
}

float bicosine_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount) {
    float left = cosine_interp(tl, bl, y_amount);
    float right = cosine_interp(tr, br, y_amount);
    return cosine_interp(right, left, x_amount);
}

float bismoothstep_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount) {
    float left = smoothstep(tl, bl, y_amount);
    float right = smoothstep(tr, br, y_amount);
    return smoothstep(right, left, x_amount);
}

float bismootherstep_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount) {
    float left = smootherstep(tl, bl, y_amount);
    float right = smootherstep(tr, br, y_amount);
    return smootherstep(right, left, x_amount);
}
