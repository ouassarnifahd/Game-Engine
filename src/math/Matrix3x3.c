#include "math/Matrix3x3.h"

Mat3x3 mat3x3_new(float xx, float xy, float xz,
                  float yx, float yy, float yz,
                  float zx, float zy, float zz) {
    Mat3x3 mat;
    mat.xx = xx; mat.xy = xy; mat.xz = xz;
    mat.yx = yx; mat.yy = yy; mat.yz = yz;
    mat.zx = zx; mat.zy = zy; mat.zz = zz;
    return mat;
}

Mat3x3 mat3x3_id() {
    return mat3x3_new(1, 0, 0,
                      0, 1, 0,
                      0, 0, 1);
}

Mat3x3 mat3x3_zero() {
    return mat3x3_new(0, 0, 0,
                      0, 0, 0,
                      0, 0, 0);
}

Mat3x3 mat3x3_mult_mat3x3(Mat3x3 mat1, Mat3x3 mat2) {
    Mat3x3 mat;
    mat.xx = mat1.xx * mat2.xx + mat1.xy * mat2.yx + mat1.xz * mat2.zx;
    mat.xy = mat1.xx * mat2.xy + mat1.xy * mat2.yy + mat1.xz * mat2.zy;
    mat.xz = mat1.xx * mat2.xz + mat1.xy * mat2.yz + mat1.xz * mat2.zz;

    mat.yx = mat1.yx * mat2.xx + mat1.yy * mat2.yx + mat1.yz * mat2.zx;
    mat.yy = mat1.yx * mat2.xy + mat1.yy * mat2.yy + mat1.yz * mat2.zy;
    mat.yz = mat1.yx * mat2.xz + mat1.yy * mat2.yz + mat1.yz * mat2.zz;

    mat.zx = mat1.zx * mat2.xx + mat1.zy * mat2.yx + mat1.zz * mat2.zx;
    mat.zy = mat1.zx * mat2.xy + mat1.zy * mat2.yy + mat1.zz * mat2.zy;
    mat.zz = mat1.zx * mat2.xz + mat1.zy * mat2.yz + mat1.zz * mat2.zz;
    return mat;
}

Vect3D mat3x3_mult_vect3D(Mat3x3 mat, Vect3D vect) {
    Vect3D vect_mult;
    vect_mult.x = mat.xx * vect.x+ mat.xy * vect.y + mat.xz * vect.z;
    vect_mult.y = mat.yx * vect.x+ mat.yy * vect.y + mat.yz * vect.z;
    vect_mult.z = mat.zx * vect.x+ mat.zy * vect.y + mat.zz * vect.z;
    return vect_mult;
}

Mat3x3 mat3x3_transpose(Mat3x3 mat) {
    Mat3x3 tmat;
    tmat.xx = mat.xx; tmat.xy = mat.yx; tmat.xz = mat.zx;
    tmat.yx = mat.xy; tmat.yy = mat.yy; tmat.yz = mat.zy;
    tmat.zx = mat.xz; tmat.zy = mat.yz; tmat.zz = mat.zz;
    return tmat;
}

float mat3x3_det(Mat3x3 mat) {
    return mat.xx * mat.yy * mat.zz + mat.xy * mat.yz * mat.zx + mat.xz * mat.yx * mat.zy -
           mat.xz * mat.yy * mat.zx - mat.xy * mat.yx * mat.zz - mat.xx * mat.yz * mat.zy;
}

Mat3x3 mat3x3_inverse(Mat3x3 mat) {
    float det = mat3x3_det(mat), fact = 1.0;
    Mat3x3 inv = mat3x3_zero();
    if (max(det, -det) > FLT_EPSILON) {
        fact /= det;
        inv.xx = fact * mat2x2_det(mat2x2_new(mat.yy, mat.yz, mat.zy, mat.zz));
        inv.xy = fact * mat2x2_det(mat2x2_new(mat.xz, mat.xy, mat.zz, mat.zy));
        inv.xz = fact * mat2x2_det(mat2x2_new(mat.xy, mat.xz, mat.yy, mat.yz));

        inv.yx = fact * mat2x2_det(mat2x2_new(mat.yz, mat.yx, mat.zz, mat.zx));
        inv.yy = fact * mat2x2_det(mat2x2_new(mat.xx, mat.xz, mat.zx, mat.zz));
        inv.yz = fact * mat2x2_det(mat2x2_new(mat.xz, mat.xx, mat.yz, mat.yx));

        inv.zx = fact * mat2x2_det(mat2x2_new(mat.yx, mat.yy, mat.zx, mat.zy));
        inv.zy = fact * mat2x2_det(mat2x2_new(mat.xy, mat.xx, mat.zy, mat.zx));
        inv.zz = fact * mat2x2_det(mat2x2_new(mat.xx, mat.xy, mat.yx, mat.yy));
    }
    return inv;
}

void mat3x3_to_array(Mat3x3 mat, float* out) {
    out[0] = mat.xx; out[1] = mat.yx; out[2] = mat.zx;
    out[3] = mat.xy; out[4] = mat.yy; out[5] = mat.zy;
    out[6] = mat.xz; out[7] = mat.yz; out[8] = mat.zz;
}

void mat3x3_print(Mat3x3 mat) {
    printf("|%4.2f, %4.2f, %4.2f|\n", mat.xx, mat.xy, mat.xz);
    printf("|%4.2f, %4.2f, %4.2f|\n", mat.yx, mat.yy, mat.yz);
    printf("|%4.2f, %4.2f, %4.2f|\n", mat.zx, mat.zy, mat.zz);
}

Mat3x3 mat3x3_scale(Vect3D scale) {
    Mat3x3 mat = mat3x3_id();
    mat.xx = scale.x;
    mat.yy = scale.y;
    mat.zz = scale.z;
    return mat;
}

Mat3x3 mat3x3_rotation_x(float angle) {
    Mat3x3 mat = mat3x3_id();
    mat.yy = cos(angle); mat.yz = -sin(angle);
    mat.zy = sin(angle); mat.zz = cos(angle);
    return mat;
}

Mat3x3 mat3x3_rotation_y(float angle) {
    Mat3x3 mat = mat3x3_id();
    mat.xx =  cos(angle); mat.xz = sin(angle);
    mat.zx = -sin(angle); mat.zz = cos(angle);
    return mat;
}

Mat3x3 mat3x3_rotation_z(float angle) {
    Mat3x3 mat = mat3x3_id();
    mat.xx = cos(angle); mat.xy = -sin(angle);
    mat.yx = sin(angle); mat.yy = cos(angle);
    return mat;
}

Mat3x3 mat3x3_rotation_angle_axis(float angle, Vect3D axis) {
    Mat3x3 mat;
    float cosine = cos(angle), sine = sin(angle);
    mat.xx = axis.x * axis.x * (1 - cosine) + cosine;
    mat.xy = axis.x * axis.y * (1 - cosine) - axis.z * sine;
    mat.xz = axis.x * axis.z * (1 - cosine) + axis.y * sine;

    mat.yx = axis.y * axis.x * (1 - cosine) + axis.z * sine;
    mat.yy = axis.y * axis.y * (1 - cosine) + cosine;
    mat.yz = axis.y * axis.z * (1 - cosine) - axis.x * sine;

    mat.zx = axis.z * axis.x * (1 - cosine) - axis.y * sine;
    mat.zy = axis.z * axis.y * (1 - cosine) + axis.x * sine;
    mat.zz = axis.z * axis.z * (1 - cosine) + cosine;
    return mat;
}
