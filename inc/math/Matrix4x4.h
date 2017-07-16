#ifndef _MATRIX_4x4_
#define _MATRIX_4x4_

#include "Matrix3x3.h"
#include "quaternion.h"

typedef struct {
    float xx; float xy; float xz; float xt;
    float yx; float yy; float yz; float yt;
    float zx; float zy; float zz; float zt;
    float tx; float ty; float tz; float tt;
} Mat4x4;

Mat4x4 mat4x4_id();
Mat4x4 mat4x4_zero();
Mat4x4 mat4x4_new(float xx, float xy, float xz, float xt,
                  float yx, float yy, float yz, float yt,
                  float zx, float zy, float zz, float zt,
                  float tx, float ty, float tz, float tt);
float mat4x4_at(Mat4x4 mat, int i, int j);
void mat4x4_set(Mat4x4* mat, int x, int y, float val);
Mat4x4 mat4x4_transpose(Mat4x4 mat);

Mat4x4 mat4x4_mult_mat4x4(Mat4x4 mat1, Mat4x4 mat2);

Vect4D mat4x4_mult_vect4D(Mat4x4 mat, Vect4D vect);
Vect3D mat4x4_mult_vect3D(Mat4x4 mat, Vect3D vect);

float mat4x4_det(Mat4x4 mat);
Mat4x4 mat4x4_inverse(Mat4x4 mat);

Mat4x4 mat3x3_to_mat4x4(Mat3x3 mat);
Mat3x3 mat4x4_to_mat3x3(Mat4x4 mat);
Quat mat4x4_to_quaternion(Mat4x4 mat);
Quat_dual mat4x4_to_quaternion_dual(Mat4x4 mat);

void mat4x4_to_array(Mat4x4 mat, float* out);
void mat4x4_to_array_trans(Mat4x4 mat, float* out);

void mat4x4_print(Mat4x4 mat);

Mat4x4 mat4x4_translation(Vect3D vect);
Mat4x4 mat4x4_scale(Vect3D vect);

Mat4x4 mat4x4_rotation_x(float angle);
Mat4x4 mat4x4_rotation_y(float angle);
Mat4x4 mat4x4_rotation_z(float angle);
Mat4x4 mat4x4_rotation_axis_angle(Vect3D axis, float angle);

Mat4x4 mat4x4_rotation_euler(float x, float y, float z);
Mat4x4 mat4x4_rotation_quaternion(Quat quat);
Mat4x4 mat4x4_rotation_quaternion_dual(Quat_dual qd);

Mat4x4 mat4x4_view_look_at(Vect3D position, Vect3D target, Vect3D up);
Mat4x4 mat4x4_perspective(float fov, float near_clip, float far_clip, float ratio);
Mat4x4 mat4x4_orthographic(float left, float right, float bottom, float top, float near, float far);

Mat4x4 mat4x4_world(Vect3D position, Vect3D scale, Quat rotation);

Mat4x4 mat4x4_lerp(Mat4x4 mat1, Mat4x4 mat2, float amount);
Mat4x4 mat4x4_smoothstep(Mat4x4 mat1, Mat4x4 mat2, float amount);

#endif /* end of include guard: _MATRIX_4x4_ */
