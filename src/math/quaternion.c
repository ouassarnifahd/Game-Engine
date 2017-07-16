#include "math/quaternion.h"

Quat quaternion_new(float x, float y, float z, float t) {
    return vect4D_new(x, y, z, t);
}

Quat quaternion_id() {
    return quaternion_new(0, 0, 0, 1);
}

Quat quaternion_from_euler(Vect3D r) {
    float fc1 = cosf(r.z/2.0f), fc2 = cosf(r.x/2.0f), fc3 = cosf(r.y/2.0f);
    float fs1 = sinf(r.z/2.0f), fs2 = sinf(r.x/2.0f), fs3 = sinf(r.y/2.0f);
    return quaternion_new(fc1 * fc2 * fs3 - fs1 * fs2 * fc3,
                          fc1 * fs2 * fc3 + fs1 * fc2 * fs3,
                          fs1 * fc2 * fc3 - fc1 * fs2 * fs3,
                          fc1 * fc2 * fc3 + fs1 * fs2 * fs3);
}

float quaternion_length(Quat quat) {
    return sqrtf(vect4D_dot((Vect4D)quat, (Vect4D)quat));
}

Quat quaternion_normalize(Quat quat) {
    float scale = quaternion_length(quat);
    if (scale > FLT_EPSILON)
        return quaternion_new(quat.x / scale,
                              quat.y / scale,
                              quat.z / scale,
                              quat.t / scale);
    else
        return quaternion_new(0, 0, 0, 0);
}

Quat quaternion_angle_axis(float angle, Vect3D axis) {
    float sine = sinf(angle/2.0f), cosine = cosf(angle/2.0f);
    return quaternion_normalize(quaternion_new(axis.x * sine,
                                               axis.y * sine,
                                               axis.z * sine,
                                               cosine));
}

Quat quaternion_rotation_x(float angle) {
    return quaternion_angle_axis(angle, vect3D_new(1, 0, 0));
}

Quat quaternion_rotation_y(float angle) {
    return quaternion_angle_axis(angle, vect3D_new(0, 1, 0));
}

Quat quaternion_rotation_z(float angle) {
    return quaternion_angle_axis(angle, vect3D_new(0, 0, 1));
}

float quaternion_at(Quat quat, int i) {
    float* values = (float*)(&quat);
    return values[i];
}

float quaternion_real(Quat quat) {
    return quat.t;
}

Vect3D quaternion_imaginaries(Quat quat) {
    return vect3D_new(quat.x, quat.y, quat.z);
}

void quaternion_to_angle_axis(Quat quat, Vect3D* axis, float* angle) {
    *angle = 2.0f * acosf(quat.t);
    float divisor = sinf(*angle/2.0f);
    if (max(divisor, -divisor) < FLT_EPSILON) {
        axis->x = 0.0f;
        axis->y = 1.0f;
        axis->z = 0.0f;
    } else {
        axis->x = quat.x / divisor;
        axis->y = quat.y / divisor;
        axis->z = quat.z / divisor;
        *axis = vect3D_normalize(*axis);
    }
}

Vect3D quaternion_to_euler(Quat quat) {
    float sqrx = quat.x * quat.x, sqry = quat.y * quat.y, sqrz = quat.z * quat.z, sqrw = quat.t * quat.t;
    return vect3D_new(asinf(-2.0f * (quat.x * quat.z - quat.y * quat.t)),
                      atan2f( 2.0f * (quat.y * quat.z + quat.x * quat.t), -sqrx - sqry + sqrz + sqrw),
                      atan2f( 2.0f * (quat.x * quat.y + quat.z * quat.t), sqrx - sqry - sqrz + sqrw));
}

Quat quaternion_negative(Quat quat) {
    return (Quat)vect4D_negative((Vect4D)quat);
}

float quaternion_dot(Quat quat1, Quat quat2) {
    return vect4D_dot((Vect4D)quat1, (Vect4D)quat2);
}

Quat quaternion_scale(Quat quat, float f) {
    return (Quat)vect4D_mult((Vect4D)quat, f);
}

Quat quaternion_mult_quaternion(Quat quat1, Quat quat2) {
    return quaternion_new(quat1.t * quat2.x + quat1.x * quat2.t + quat1.y * quat2.z - quat1.z * quat2.y,
                          quat1.t * quat2.y - quat1.x * quat2.z + quat1.y * quat2.t + quat1.z * quat2.x,
                          quat1.t * quat2.z + quat1.x * quat2.y - quat1.y * quat2.x + quat1.z * quat2.t,
                          quat1.t * quat2.t - quat1.x * quat2.x - quat1.y * quat2.y - quat1.z * quat2.z);
}

Quat quaternion_unit_inverse(Quat quat) {
    return quaternion_new(-quat.x, -quat.y, -quat.z, quat.t);
}

Quat quaternion_inverse(Quat quat) {
    float scale = quaternion_length(quat);
    Quat result = quaternion_unit_inverse(quat);
    if (scale > FLT_EPSILON) {
        result.x /= scale;
        result.y /= scale;
        result.z /= scale;
        result.t /= scale;
    }
    return result;
}

Vect3D quaternion_mult_vect3D(Quat quat, Vect3D vect) {
    Quat work = quat;
    work = quaternion_mult_quaternion(work, quaternion_normalize(quaternion_new(vect.x, vect.y, vect.z, 0.0)));
    work = quaternion_mult_quaternion(work, quaternion_inverse(quat));
    Vect3D result = vect3D_new(work.x, work.y, work.z);
    return vect3D_mult(result, vect3D_length(vect));
}

Quat quaternion_exp(Vect3D w) {
    float theta = sqrt(vect3D_dot(w, w));
    float len = theta < FLT_EPSILON ? 1 : sin(theta) / theta;
    Vect3D vect = vect3D_mult(w, len);
    return quaternion_new(vect.x, vect.y, vect.z, cos(theta));
}

Vect3D quaternion_log(Quat quat) {
    float len = vect3D_length(quaternion_imaginaries(quat));
    float angle = atan2(len, quat.t);
    len = len > FLT_EPSILON ? angle / len : 1;
    return vect3D_mult(quaternion_imaginaries(quat), len);
}

Quat quaternion_slerp(Quat from, Quat to, float amount) {
    float scale0, scale1, afto1[4], cosom = quaternion_dot(from, to);
    if (cosom < 0.0f) {
        cosom = -cosom;
        afto1[0] = -to.x;
        afto1[1] = -to.y;
        afto1[2] = -to.z;
        afto1[3] = -to.t;
    } else {
        afto1[0] = to.x;
        afto1[1] = to.y;
        afto1[2] = to.z;
        afto1[3] = to.t;
    }

    const float QUATERNION_DELTA_COS_MIN = 0.01f;

    if ( (1.0f - cosom) > QUATERNION_DELTA_COS_MIN ) {
        /* This is a standard case (slerp). */
        float omega = acosf(cosom);
        float sinom = sinf(omega);
        scale0 = sinf((1.0f - amount) * omega) / sinom;
        scale1 = sinf(amount * omega) / sinom;
    } else {
        /* "from" and "to" quaternions are very close */
        /*  so we can do a linear interpolation.      */
        scale0 = 1.0f - amount;
        scale1 = amount;
    }

    return quaternion_new(scale0 * from.x + scale1 * afto1[0],
                          scale0 * from.y + scale1 * afto1[1],
                          scale0 * from.z + scale1 * afto1[2],
                          scale0 * from.t + scale1 * afto1[3]);
}

static Quat quaternion_get_value(float t, Vect3D axis) {
	return quaternion_exp(vect3D_mult(axis, t / 2.0));
}

Quat quaternion_constrain(Quat quat, Vect3D axis) {
    const Quat orient = quaternion_new(0, 0, 0, 1);
    Vect3D v0 = quaternion_imaginaries(orient), vs = quaternion_imaginaries(quat);
    float a = quat.t * orient.t + vect3D_dot(vs, v0);
    float b = orient.t * vect3D_dot(axis, vs) - quat.t * vect3D_dot(axis, v0) + vect3D_dot(vs, vect3D_mult_vect3D(axis, v0));
    float alpha = atan2(a, b);
    float t1 = -2 * alpha + M_PI, t2 = -2 * alpha - M_PI;
    if (quaternion_dot(quat, quaternion_get_value(t1, axis)) > quaternion_dot(quat, quaternion_get_value(t2, axis)))
        return quaternion_get_value(t1, axis);
    else
        return quaternion_get_value(t2, axis);
}

Quat quaternion_constrain_y(Quat quat) {
    return quaternion_constrain(quat, vect3D_new(0, 1, 0));
}

float quaternion_distance(Quat quat0, Quat quat1) {
    Quat comb = quaternion_mult_quaternion(quaternion_inverse(quat0), quat1);
    return sin(vect3D_length(quaternion_log(comb)));
}

Quat quaternion_interpolate(Quat* qs, float* ws, int count) {
    Quat ref = quaternion_id();
    Quat ref_inv = quaternion_inverse(ref);
    Vect3D acc = vect3D_zero();
    for (int i = 0; i < count; i++) {
        Vect3D qlog0 = quaternion_log(quaternion_mult_quaternion(ref_inv, qs[i]));
        Vect3D qlog1 = quaternion_log(quaternion_mult_quaternion(ref_inv, quaternion_negative(qs[i])));
        if (vect3D_length(qlog0) < vect3D_length(qlog1))
            acc = vect3D_add(acc, vect3D_mult(qlog0), ws[i]);
        else
            acc = vect3D_add(acc, vect3D_mult(qlog1), ws[i]);
    }
    Quat result = quaternion_mult_quaternion(ref, quaternion_exp(acc));
    return quaternion_normalize(result);
}

Quat_dual quaternion_dual_new(Quat real, Quat dual) {
    Quat_dual qd;
    qd.real = real;
    qd.dual = dual;
    return qd;
}

Quat_dual quaternion_dual_id() {
    return quaternion_dual_new(quaternion_id(), vect4D_zero());
}

Quat_dual quaternion_dual_normalize(Quat_dual qd) {
    float len = quaternion_length(qd.real);
    Quat real = vect4D_mult(qd.real, 1.0 / len);
    Quat dual = vect4D_mult(qd.dual, 1.0 / len);
    return quaternion_dual_new(real, vect4D_sub(dual, vect4D_mult(real, quaternion_dot(real, dual))));
}

Quat_dual quaternion_dual_transform(Quat quat, Vect3D t) {
    Quat_dual qd;
    qd.real = quat;
    qd.dual = quaternion_new(0.5 * (t.x * quat.t + t.y * quat.z - t.z * quat.y),
                             0.5 * (-t.x * quat.z + t.y * quat.t + t.z * quat.x),
                             0.5 * ( t.x * quat.y - t.y * quat.x + t.z * quat.t),
                            -0.5 * ( t.x * quat.x + t.y * quat.y + t.z * quat.z));
    return qd;
}

Quat_dual quaternion_dual_mult(Quat_dual qd0, Quat_dual qd1) {
    return quaternion_dual_new(quaternion_mult_quaternion(qd0.real, qd1.real),
                               vect4D_add(quaternion_mult_quaternion(qd0.real, qd1.dual),
                                          quaternion_mult_quaternion(qd0.dual, qd1.real)));
}

Vect3D quaternion_dual_mult_vect3D(Quat_dual qd, Vect3D vect) {
    Vect3D rvc = vect3D_cross(quaternion_imaginaries(qd.real), vect);
    Vect3D real = vect3D_cross(quaternion_imaginaries(qd.real), vect3D_add(rvc, vect3D_mult(vect, qd.real.t)));

    Vect3D rdc = vect3D_cross(quaternion_imaginaries(qd.real), quaternion_imaginaries(qd.dual));
    Vect3D rimg = vect3D_mult(quaternion_imaginaries(qd.real), qd.dual.t);
    Vect3D dimg = vect3D_mult(quaternion_imaginaries(qd.dual), qd.real.t);
    Vect3D dual = vect3D_sub(rimg , vect3D_add(dimg, rdc));

    return vect3D_add(vect, vect3D_add(vect3D_mult(real, 2), vect3D_mult(dual, 2)));
}

Vect3D quaternion_dual_mult_vect3D_rot(Quat_dual qd, Vect3D vect) {
    Vect3D rvc = vect3D_cross(quaternion_imaginaries(qd.real), vect);
    Vect3D real = vect3D_cross(quaternion_imaginaries(qd.real), vect3D_add(rvc, vect3D_mult(vect, qd.real.t)));
    return vect3D_add(vect, vect3D_mult(real, 2.0)); 
}
