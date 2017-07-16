#include "math/Matrix2x2.h"

Mat2x2 mat2x2_new(float xx, float xy, float yx, float yy) {
    Mat2x2 mat;
    mat.xx = xx; mat.xy = xy;
    mat.yx = yx; mat.yy = yy;
    return mat;
}

Mat2x2 mat2x2_id() {
    return mat2x2_new(1, 0,
                      0, 1);
}

Mat2x2 mat2x2_zero() {
    return mat2x2_new(0, 0,
                      0, 0);
}

Mat2x2 mat2x2_mult_mat2x2(Mat2x2 mat1, Mat2x2 mat2) {
    Mat2x2 mat;
    mat.xx = mat1.xx * mat2.xx + mat1.xy * mat2.yx;
    mat.xy = mat1.xx * mat2.xy + mat1.xy * mat2.yy;
    mat.yx = mat1.yx * mat2.xx + mat1.yy * mat2.yx;
    mat.yy = mat1.yx * mat2.xy + mat1.yy * mat2.yy;
    return mat;
}

Vect2D mat2x2_mult_vec2(Mat2x2 mat, Vect2D vect) {
    Vect2D vect_mult;
    vect_mult.x = vect.x * mat.xx + vect.y * mat.xy;
    vect_mult.y = vect.x * mat.yx + vect.y * mat.yy;
    return vect_mult;
}

Mat2x2 mat2x2_transpose(Mat2x2 mat) {
    Mat2x2 tmat;
    tmat.xx = mat.xx; tmat.xy = mat.yx;
    tmat.yx = mat.xy; tmat.yy = mat.yy;
    return tmat;
}

float mat2x2_det(Mat2x2 mat) {
    return mat.xx * mat.yy - mat.yx * mat.xy;
}

Mat2x2 mat2x2_inverse(Mat2x2 mat) {
    float det = mat2x2_det(mat), fact = 1.0;
    Mat2x2 inv = mat2x2_zero();
    if (max(det, -det) > FLT_EPSILON) {
        fact /= det;
        inv.xx = fact * mat.yy; inv.xy = fact * -mat.xy;
        inv.yx = fact * -mat.yx; inv.yy = fact * mat.xx;
    }
    return inv;
}

void mat2x2_to_array(Mat2x2 mat, float* out) {
    out[0] = mat.xx; out[1] = mat.xy;
    out[2] = mat.yx; out[3] = mat.yy;
}

void mat2x2_print(Mat2x2 mat) {
    printf("|%4.2f, %4.2f|\n", mat.xx, mat.xy);
    printf("|%4.2f, %4.2f|\n", mat.yx, mat.yy);
}

Mat2x2 mat2x2_rotation(float angle) {
    Mat2x2 mat;
    mat.xx = cos(angle); mat.xy = -sin(angle);
    mat.yx = sin(angle); mat.yy = cos(angle);
    return mat;
}
