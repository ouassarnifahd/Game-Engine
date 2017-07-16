#ifndef _MATRIX_3x3_
#define _MATRIX_3x3_

#include "3Dvectors.h"
#include "Matrix2x2.h"

typedef struct {
    float xx; float xy; float xz;
    float yx; float yy; float yz;
    float zx; float zy; float zz;
} Mat3x3;

Mat3x3 mat3x3_id();
Mat3x3 mat3x3_zero();
Mat3x3 mat3x3_new(float xx, float xy, float xz,
                  float yx, float yy, float yz,
                  float zx, float zy, float zz);
Mat3x3 mat3x3_mult_mat3x3(Mat3x3 mat1, Mat3x3 mat2);
Vect3D mat3x3_mult_vect3D(Mat3x3 mat, Vect3D vect);

Mat3x3 mat3x3_transpose(Mat3x3 mat);
float mat3x3_det(Mat3x3 mat);
Mat3x3 mat3x3_inverse(Mat3x3 mat);

void mat3x3_to_array(Mat3x3 mat, float* out);
void mat3x3_print(Mat3x3 mat);

Mat3x3 mat3x3_scale(Vect3D scale);
Mat3x3 mat3x3_rotation_x(float angle);
Mat3x3 mat3x3_rotation_y(float angle);
Mat3x3 mat3x3_rotation_z(float angle);
Mat3x3 mat3x3_rotation_angle_axis(float angle, Vect3D axis);

#endif /* end of include guard: _MATRIX_3x3_ */
