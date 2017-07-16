#ifndef _QUATERNIONS_
#define _QUATERNIONS_

#include "4Dvectors.h"

typedef Vect4D Quat;

Quat quaternion_id();
Quat quaternion_new(float x, float y, float z, float t);
Quat quaternion_from_euler(Vect3D r);
Quat quaternion_angle_axis(float angle, Vect3D axis);
Quat quaternion_rotation_x(float angle);
Quat quaternion_rotation_y(float angle);
Quat quaternion_rotation_z(float angle);

float quaternion_at(Quat quat, int i);
float quaternion_real(Quat quat);
Vect3D quaternion_imaginaries(Quat quat);

void quaternion_to_angle_axis(Quat quat, Vect3D* axis, float* angle);
Vect3D quaternion_to_euler(Quat quat);

Quat quaternion_neg(Quat quat);
float quaternion_dot(Quat quat1, Quat quat2);
Quat quaternion_scale(Quat quat, float f);
Quat quaternion_mult_quaternion(Quat quat1, Quat quat2);
Vect3D quaternion_mult_vect3D(Quat quat, Vect3D v);

Quat quaternion_inverse(Quat quat);
Quat quaternion_unit_inverse(Quat quat);
float quaternion_length(Quat quat);
Quat quaternion_normalize(Quat quat);

Quat quaternion_exp(Vect3D w);
Vect3D quaternion_log(Quat quat);

Quat quaternion_slerp(Quat from, Quat to, float amount);

Quat quaternion_constrain(Quat quat, Vect3D axis);
Quat quaternion_constrain_y(Quat quat);

float quaternion_distance(Quat quat0, Quat quat1);
Quat quaternion_interpolate(Quat* qs, float* ws, int count);

typedef struct {
  Quat real;
  Quat dual;
} Quat_dual;

Quat_dual quaternion_dual_id();
Quat_dual quaternion_dual_normalize(Quat_dual qd);
Quat_dual quaternion_dual_new(Quat real, Quat dual);
Quat_dual quaternion_dual_transform(Quat quat, Vect3D t);
Quat_dual quaternion_dual_mult(Quat_dual qd0, Quat_dual qd1);
Vect3D quaternion_dual_mult_vect3D(Quat_dual qd, Vect3D vect);
Vect3D quaternion_dual_mult_vect3D_rot(Quat_dual qd, Vect3D vect);


#endif /* end of include guard: _QUATERNIONS_ */
