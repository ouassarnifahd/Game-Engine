#ifndef _MATRIX_2x2_
#define _MATRIX_2x2_

#include "2Dvectors.h"

typedef struct {
    float xx; float xy;
    float yx; float yy;
} Mat2x2;

Mat2x2 mat2x2_id();
Mat2x2 mat2x2_zero();
Mat2x2 mat2x2_new(float xx, float xy, float yx, float yy);
Mat2x2 mat2x2_mult_mat2x2(Mat2x2 mat1, Mat2x2 mat2);
Vect2D mat2x2_mult_vec2(Mat2x2 mat, Vect2D vect);

Mat2x2 mat2x2_transpose(Mat2x2 mat);
float mat2x2_det(Mat2x2 mat);
Mat2x2 mat2x2_inverse(Mat2x2 mat);

void mat2x2_to_array(Mat2x2 mat, float* out);
void mat2x2_print(Mat2x2 mat);
Mat2x2 mat2x2_rotation(float angle);

#endif /* end of include guard: _MATRIX_2x2_ */
