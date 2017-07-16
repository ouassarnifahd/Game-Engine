#include "math/Matrix4x4.h"

Mat4x4 mat4x4_new(float xx, float xy, float xz, float xt,
                  float yx, float yy, float yz, float yt,
                  float zx, float zy, float zz, float zt,
                  float tx, float ty, float tz, float tt) {
    Mat4x4 mat;
    mat.xx = xx; mat.xy = xy; mat.xz = xz; mat.xt = xt;
    mat.yx = yx; mat.yy = yy; mat.yz = yz; mat.yt = yt;
    mat.zx = zx; mat.zy = zy; mat.zz = zz; mat.zt = zt;
    mat.tx = tx; mat.ty = ty; mat.tz = tz; mat.tt = tt;
    return mat;
}

Mat4x4 mat4x4_id() {
    return mat4x4_new(1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);
}

Mat4x4 mat4x4_zero() {
    return mat4x4_new(0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 0, 0, 0);
}

float mat4x4_at(Mat4x4 mat, int i, int j) {
    float* arr = (float*)(&mat);
    return arr[x + 4 * y];
}

void mat4x4_set(Mat4x4* mat, int x, int y, float val) {
    float* arr = (float*)mat;
    arr[x + 4 * y] = val;
}

Mat4x4 mat4x4_transpose(Mat4x4 mat) {
    Mat4x4 tmat;
    tmat.xx = mat.xx; tmat.xy = mat.yx; tmat.xz = mat.zx; tmat.xt = mat.tx;
    tmat.yx = mat.xy; tmat.yy = mat.yy; tmat.yz = mat.zy; tmat.yt = mat.ty;
    tmat.zx = mat.xz; tmat.zy = mat.yz; tmat.zz = mat.zz; tmat.zt = mat.tz;
    tmat.tx = mat.xt; tmat.ty = mat.yt; tmat.tz = mat.zt; tmat.tt = mat.tt;
    return tmat;
}

Mat4x4 mat4x4_mult_mat4x4(Mat4x4 mat1, Mat4x4 mat2) {
    Mat4x4 mat_mult;
    mat_mult.xx = mat1.xx * mat2.xx + mat1.xy * mat2.yx + mat1.xz * mat2.zx + mat1.xt * mat2.tx;
    mat_mult.xy = mat1.xx * mat2.xy + mat1.xy * mat2.yy + mat1.xz * mat2.zy + mat1.xt * mat2.ty;
    mat_mult.xz = mat1.xx * mat2.xz + mat1.xy * mat2.yz + mat1.xz * mat2.zz + mat1.xt * mat2.tz;
    mat_mult.xt = mat1.xx * mat2.xt + mat1.xy * mat2.yt + mat1.xz * mat2.zt + mat1.xt * mat2.tt;

    mat_mult.yx = mat1.yx * mat2.xx + mat1.yy * mat2.yx + mat1.yz * mat2.zx + mat1.yt * mat2.tx;
    mat_mult.yy = mat1.yx * mat2.xy + mat1.yy * mat2.yy + mat1.yz * mat2.zy + mat1.yt * mat2.ty;
    mat_mult.yz = mat1.yx * mat2.xz + mat1.yy * mat2.yz + mat1.yz * mat2.zz + mat1.yt * mat2.tz;
    mat_mult.yt = mat1.yx * mat2.xt + mat1.yy * mat2.yt + mat1.yz * mat2.zt + mat1.yt * mat2.tt;

    mat_mult.zx = mat1.zx * mat2.xx + mat1.zy * mat2.yx + mat1.zz * mat2.zx + mat1.zt * mat2.tx;
    mat_mult.zy = mat1.zx * mat2.xy + mat1.zy * mat2.yy + mat1.zz * mat2.zy + mat1.zt * mat2.ty;
    mat_mult.zz = mat1.zx * mat2.xz + mat1.zy * mat2.yz + mat1.zz * mat2.zz + mat1.zt * mat2.tz;
    mat_mult.zt = mat1.zx * mat2.xt + mat1.zy * mat2.yt + mat1.zz * mat2.zt + mat1.zt * mat2.tt;

    mat_mult.tx = mat1.tx * mat2.xx + mat1.ty * mat2.yx + mat1.tz * mat2.zx + mat1.tt * mat2.tx;
    mat_mult.ty = mat1.tx * mat2.xy + mat1.ty * mat2.yy + mat1.tz * mat2.zy + mat1.tt * mat2.ty;
    mat_mult.tz = mat1.tx * mat2.xz + mat1.ty * mat2.yz + mat1.tz * mat2.zz + mat1.tt * mat2.tz;
    mat_mult.tt = mat1.tx * mat2.xt + mat1.ty * mat2.yt + mat1.tz * mat2.zt + mat1.tt * mat2.tt;
    return mat_mult;
}

Vect4D mat4x4_mult_vect4D(Mat4x4 mat, Vect4D vect) {
    Vect4D vect_mult;
    vect_mult.x = mat.xx * vect.x + mat.xy * vect.y + mat.xz * vect.z + mat.xt * vect.t;
    vect_mult.y = mat.yx * vect.x + mat.yy * vect.y + mat.yz * vect.z + mat.yt * vect.t;
    vect_mult.z = mat.zx * vect.x + mat.zy * vect.y + mat.zz * vect.z + mat.zt * vect.t;
    vect_mult.t = mat.tx * vect.x + mat.ty * vect.y + mat.tz * vect.z + mat.tt * vect.t;
    return vect_mult;
}

Vect3D mat4x4_mult_vect3D(Mat4x4 mat, Vect3D vect) {
    Vect4D vect_homo = vect4D_new(vect.x, vect.y, vect.z, 1);
    vect_homo = mat4x4_mult_vect4D(mat, vect_homo);
    vect_homo = vect4D_div(vect_homo, vect_homo.t);
    return vect3D_new(vect_homo.x, vect_homo.y, vect_homo.z);
}

float mat4x4_det(Mat4x4 mat) {
    float cofact_xx =  mat3x3_det(mat3x3_new(mat.yy, mat.yz, mat.yt, mat.zy, mat.zz, mat.zt, mat.ty, mat.tz, mat.tt));
    float cofact_xy = -mat3x3_det(mat3x3_new(mat.yx, mat.yz, mat.yt, mat.zx, mat.zz, mat.zt, mat.tx, mat.tz, mat.tt));
    float cofact_xz =  mat3x3_det(mat3x3_new(mat.yx, mat.yy, mat.yt, mat.zx, mat.zy, mat.zt, mat.tx, mat.ty, mat.tt));
    float cofact_xt = -mat3x3_det(mat3x3_new(mat.yx, mat.yy, mat.yz, mat.zx, mat.zy, mat.zz, mat.tx, mat.ty, mat.tz));
    return cofact_xx * mat.xx + cofact_xy * mat.xy + cofact_xz * mat.xz + cofact_xt * mat.xt;
}

Mat4x4 mat4x4_inverse(Mat4x4 mat) {
    float det = mat4x4_det(mat), fact = 1.0;
    Mat4x4 inv = mat4x4_zero();
    if (max(det, -det) > FLT_EPSILON) {
        fact /= det;
        inv.xx = fact *  mat3x3_det(mat3x3_new(mat.yy, mat.yz, mat.yt, mat.zy, mat.zz, mat.zt, mat.ty, mat.tz, mat.tt));
        inv.xy = fact * -mat3x3_det(mat3x3_new(mat.yx, mat.yz, mat.yt, mat.zx, mat.zz, mat.zt, mat.tx, mat.tz, mat.tt));
        inv.xz = fact *  mat3x3_det(mat3x3_new(mat.yx, mat.yy, mat.yt, mat.zx, mat.zy, mat.zt, mat.tx, mat.ty, mat.tt));
        inv.xt = fact * -mat3x3_det(mat3x3_new(mat.yx, mat.yy, mat.yz, mat.zx, mat.zy, mat.zz, mat.tx, mat.ty, mat.tz));

        inv.yx = fact * -mat3x3_det(mat3x3_new(mat.xy, mat.xz, mat.xt, mat.zy, mat.zz, mat.zt, mat.ty, mat.tz, mat.tt));
        inv.yy = fact *  mat3x3_det(mat3x3_new(mat.xx, mat.xz, mat.xt, mat.zx, mat.zz, mat.zt, mat.tx, mat.tz, mat.tt));
        inv.yz = fact * -mat3x3_det(mat3x3_new(mat.xx, mat.xy, mat.xt, mat.zx, mat.zy, mat.zt, mat.tx, mat.ty, mat.tt));
        inv.yt = fact *  mat3x3_det(mat3x3_new(mat.xx, mat.xy, mat.xz, mat.zx, mat.zy, mat.zz, mat.tx, mat.ty, mat.tz));

        inv.zx = fact *  mat3x3_det(mat3x3_new(mat.xy, mat.xz, mat.xt, mat.yy, mat.yz, mat.yt, mat.ty, mat.tz, mat.tt));
        inv.zy = fact * -mat3x3_det(mat3x3_new(mat.xx, mat.xz, mat.xt, mat.yx, mat.yz, mat.yt, mat.tx, mat.tz, mat.tt));
        inv.zz = fact *  mat3x3_det(mat3x3_new(mat.xx, mat.xy, mat.xt, mat.yx, mat.yy, mat.yt, mat.tx, mat.ty, mat.tt));
        inv.zt = fact * -mat3x3_det(mat3x3_new(mat.xx, mat.xy, mat.xz, mat.yx, mat.yy, mat.yz, mat.tx, mat.ty, mat.tz));

        inv.tx = fact * -mat3x3_det(mat3x3_new(mat.xy, mat.xz, mat.xt, mat.yy, mat.yz, mat.yt, mat.zy, mat.zz, mat.zt));
        inv.ty = fact *  mat3x3_det(mat3x3_new(mat.xx, mat.xz, mat.xt, mat.yx, mat.yz, mat.yt, mat.zx, mat.zz, mat.zt));
        inv.tz = fact * -mat3x3_det(mat3x3_new(mat.xx, mat.xy, mat.xt, mat.yx, mat.yy, mat.yt, mat.zx, mat.zy, mat.zt));
        inv.tt = fact *  mat3x3_det(mat3x3_new(mat.xx, mat.xy, mat.xz, mat.yx, mat.yy, mat.yz, mat.zx, mat.zy, mat.zz));
        inv = mat4x4_transpose(inv);
    }
    return inv;
}

Mat4x4 mat3x3_to_mat4x4(Mat3x3 mat) {
    Mat4x4 mat4;
    mat4.xx = mat.xx; mat4.xy = mat.xy; mat4.xz = mat.xz; mat4.xt = 0.0f;
    mat4.yx = mat.yx; mat4.yy = mat.yy; mat4.yz = mat.yz; mat4.yt = 0.0f;
    mat4.zx = mat.zx; mat4.zy = mat.zy; mat4.zz = mat.zz; mat4.zt = 0.0f;
    mat4.tx = 0.0f;   mat4.ty = 0.0f;   mat4.tz = 0.0f;   mat4.tt = 1.0f;
    return mat4;
}

Mat3x3 mat4x4_to_mat3x3(Mat4x4 mat) {
    Mat3x3 mat3;
    mat3.xx = mat.xx; mat3.xy = mat.xy; mat3.xz = mat.xz;
    mat3.yx = mat.yx; mat3.yy = mat.yy; mat3.yz = mat.yz;
    mat3.zx = mat.zx; mat3.zy = mat.zy; mat3.zz = mat.zz;
    return mat3;
}

Quat mat4x4_to_quaternion(Mat4x4 mat) {
    float tr = mat.xx + mat.yy + mat.zz;
    if (tr > 0.0f) {
        float s = sqrtf(tr + 1.0f);
        float t = s / 2.0f;
        float x = (mat4x4_at(mat, 1, 2) - mat4x4_at(mat, 2, 1)) * 0.5f / s;
        float y = (mat4x4_at(mat, 2, 0) - mat4x4_at(mat, 0, 2)) * 0.5f / s;
        float z = (mat4x4_at(mat, 0, 1) - mat4x4_at(mat, 1, 0)) * 0.5f / s;
        return quaternion_new(x, y, z, t);
    } else {
        int nxt[3] = {1, 2, 0};
        float q[4];
        int i = 0, j, k;
        if (mat4x4_at(mat, 1, 1) > mat4x4_at(mat, 0, 0)) i = 1;
        if (mat4x4_at(mat, 2, 2) > mat4x4_at(mat, i, i)) i = 2;
        j = nxt[i];
        k = nxt[j];
        float s = sqrtf((mat4x4_at(mat, i, i) - (mat4x4_at(mat, j, j) + mat4x4_at(mat, k, k))) + 1.0f);
        q[i] = s * 0.5f;
        if (s != 0.0f) s = 0.5f / s;
        q[3] = (mat4x4_at(mat, j, k) - mat4x4_at(mat, k, j)) * s;
        q[j] = (mat4x4_at(mat, i, j) + mat4x4_at(mat, j, i)) * s;
        q[k] = (mat4x4_at(mat, i, k) + mat4x4_at(mat, k, i)) * s;
        return quaternion_new(q[0], q[1], q[2], q[3]);
    }
}

Quat_dual mat4x4_to_quaternion_dual(Mat4x4 mat) {
    Quat rotation = mat4x4_to_quaternion(mat);
    Vect3D translation = mat4x4_mult_vect3D(mat, vect3D_zero());
    return quaternion_dual_transform(rotation, translation);
}

void mat4x4_to_array(Mat4x4 mat, float* out) {
    out[0]  = mat.xx; out[1]  = mat.yx; out[2]  = mat.zx; out[3]  = mat.tx;
    out[4]  = mat.xy; out[5]  = mat.yy; out[6]  = mat.zy; out[7]  = mat.ty;
    out[8]  = mat.xz; out[9]  = mat.yz; out[10] = mat.zz; out[11] = mat.tz;
    out[12] = mat.xt; out[13] = mat.yt; out[14] = mat.zt; out[15] = mat.tt;
}

void mat4x4_to_array_trans(Mat4x4 mat, float* out) {
    out[0]  = mat.xx; out[1]  = mat.xy; out[2]  = mat.xz; out[3]  = mat.xt;
    out[4]  = mat.yx; out[5]  = mat.yy; out[6]  = mat.yz; out[7]  = mat.yt;
    out[8]  = mat.zx; out[9]  = mat.zy; out[10] = mat.zz; out[11] = mat.zt;
    out[12] = mat.tx; out[13] = mat.ty; out[14] = mat.tz; out[15] = mat.tt;
}

void mat4x4_print(Mat4x4 mat) {
    printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", mat.xx, mat.xy, mat.xz, mat.xt);
    printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", mat.yx, mat.yy, mat.yz, mat.yt);
    printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", mat.zx, mat.zy, mat.zz, mat.zt);
    printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", mat.tx, mat.ty, mat.tz, mat.tt);
}

Mat4x4 mat4x4_translation(Vect3D vect) {
    Mat4x4 mat = mat4x4_id();
    mat.xt = vect.x;
    mat.yt = vect.y;
    mat.zt = vect.z;
    return mat;
}

Mat4x4 mat4x4_scale(Vect3D vect) {
    Mat4x4 mat = mat4x4_id();
    mat.xx = vect.x;
    mat.yy = vect.y;
    mat.zz = vect.z;
    return mat;
}

Mat4x4 mat4x4_rotation_x(float angle) {
    Mat4x4 mat = mat4x4_id();
    mat.yy = cos(angle); mat.yz = -sin(angle);
    mat.zy = sin(angle); mat.zz = cos(angle);
    return mat;
}

Mat4x4 mat4x4_rotation_y(float angle) {
    Mat4x4 mat = mat4x4_id();
    mat.xx = cos(angle);  mat.xz = sin(angle);
    mat.zx = -sin(angle); mat.zz = cos(angle);
    return mat;
}

Mat4x4 mat4x4_rotation_z(float angle) {
    Mat4x4 mat = mat4x4_id();
    mat.xx = cos(angle); mat.xy = -sin(angle);
    mat.yx = sin(angle); mat.yy = cos(angle);
    return mat;
}

Mat4x4 mat4x4_rotation_axis_angle(Vect3D axis, float angle) {
    Mat4x4 mat = mat4x4_id();
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

Mat4x4 mat4x4_rotation_euler(float x, float y, float z) {
    Mat4x4 mat = mat4x4_zero();
    float cosx = cos(x), sinx = sin(x);
    float cosy = cos(y), siny = sin(y);
    float cosz = cos(z), sinz = sin(z);
    mat.xx = cosy * cosz;
    mat.yx = -cosx * sinz + sinx * siny * cosz;
    mat.zx = sinx * sinz + cosx * siny * cosz;
    mat.xy = cosy * sinz;
    mat.yy = cosx * cosz + sinx * siny * sinz;
    mat.zy = -sinx * cosz + cosx * siny * sinz;
    mat.xz = -siny;
    mat.yz = sinx * cosy;
    mat.zz = cosx * cosy;
    mat.tt = 1;
    return mat;
}

Mat4x4 mat4x4_rotation_quaternion(Quat quat) {
    float x2 = quat.x + quat.x, y2 = quat.y + quat.y, z2 = quat.z + quat.z;
    float xx = quat.x * x2, yy = quat.y * y2, zz = quat.z * z2;
    float tx = quat.t * x2, ty = quat.t * y2, tz = quat.t * z2;
    float xy = quat.x * y2, yz = quat.y * z2, xz = quat.x * z2;
    return mat4x4_new(1.0f - (yy + zz), xy - tz, xz + ty,	0.0f, xy + tz,
                      1.0f - (xx + zz), yz - tx, 0.0f, xz - ty, yz + tx,
                      1.0f - (xx + yy), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4x4 mat4x4_rotation_quaternion_dual(Quat_dual qd) {
    float rx = qd.real.x, ry = qd.real.y, rz = qd.real.z, rt = qd.real.t;
    float tx = qd.dual.x, ty = qd.dual.y, tz = qd.dual.z, tt = qd.dual.t;
    Mat4x4 mat = mat4x4_id();
    mat.xx = rt * rt + rx * rx - ry * ry - rz * rz;
    mat.xy = 2.0f * (rx * ry - rt * rz);
    mat.xz = 2.0f * (rx * rz + rt * ry);
    mat.yx = 2.0f * (rx * ry + rt * rz);
    mat.yy = rt * rt - rx * rx + ry * ry - rz * rz;
    mat.yz = 2.0f * (ry * rz - rt * rx);
    mat.zx = 2.0f * (rx * rz - rt * ry);
    mat.zy = 2.0f * (ry * rz + rt * rx);
    mat.zz = rt * rt - rx * rx - ry * ry + rz * rz;
    mat.xt = -2.0f * (tt * rx + rt * tx - ty * rz + ry * tz);
    mat.yt = -2.0f * (tt * ry + tx * rz - rx * tz + rt * ty);
    mat.zt = -2.0f * (tt * rz + rx * ty + rt * tz - tx * ry);
    return mat;
}

Mat4x4 mat4x4_view_look_at(Vect3D position, Vect3D target, Vect3D up) {
    Vect3D zaxis = vec3D_normalize(vec3D_sub(target, position));
    Vect3D xaxis = vec3D_normalize(vec3D_cross(up, zaxis));
    Vect3D yaxis = vec3D_cross(zaxis, xaxis);
    Mat4x4 view_matrix = mat4x4_id();
    view_matrix.xx = xaxis.x;  view_matrix.xy = xaxis.y;  view_matrix.xz = xaxis.z;
    view_matrix.yx = yaxis.x;  view_matrix.yy = yaxis.y;  view_matrix.yz = yaxis.z;
    view_matrix.zx = -zaxis.x; view_matrix.zy = -zaxis.y; view_matrix.zz = -zaxis.z;
    view_matrix = mat4x4_mult_mat4x4(view_matrix, mat4x4_translation(vect3D_negative(position)));
    return view_matrix;
}

Mat4x4 mat4x4_perspective(float fov, float near_clip, float far_clip, float ratio) {
    float right = -near_clip * tanf(fov), left = -right;
    float top = ratio * near_clip * tanf(fov), bottom = -top;
    Mat4x4 proj_matrix = mat4x4_zero();
    proj_matrix.xx = 2.0 * near_clip / (right - left);
    proj_matrix.yy = 2.0 * near_clip / (top - bottom);
    proj_matrix.xz = (right + left) / (right - left);
    proj_matrix.yz = (top + bottom) / (top - bottom);
    proj_matrix.zz = (-far_clip - near_clip) / (far_clip - near_clip);
    proj_matrix.tz = -1.0;
    proj_matrix.zt = -2.0 * near_clip * far_clip / (far_clip - near_clip);
    return proj_matrix;
}

Mat4x4 mat4x4_orthographic(float left, float right, float bottom, float top, float near, float far) {
    Mat4x4 mat = mat4x4_id();
    mat.xx = 2.0 / (right - left);
    mat.yy = 2.0 / (top - bottom);
    mat.zz = 1.0 / (clip_near - clip_far);
    mat.xt = -1.0 - 2.0 * left / (right - left);
    mat.yt =  1.0 + 2.0 * top  / (bottom - top);
    mat.zt = clip_near / (clip_near - clip_far);
    return mat;
}

Mat4x4 mat4x4_world(Vect3D position, Vect3D scale, Quat rotation) {
    Mat4x4 pos_m = mat4x4_translation(position), sca_m = mat4x4_rotation_quaternion(rotation), rot_m = mat4x4_scale(scale), result = mat4x4_id();
    result = mat4x4_mult_mat4x4(result, pos_m);
    result = mat4x4_mult_mat4x4(result, rot_m);
    result = mat4x4_mult_mat4x4(result, sca_m);
    return result;
}

Mat4x4 mat4x4_lerp(Mat4x4 mat1, Mat4x4 mat2, float amount) {
    Mat4x4 mat;
    mat.xx = lerp(mat1.xx, mat2.xx, amount);
    mat.xy = lerp(mat1.xy, mat2.xy, amount);
    mat.xz = lerp(mat1.xz, mat2.xz, amount);
    mat.xt = lerp(mat1.xt, mat2.xt, amount);
    mat.yx = lerp(mat1.yx, mat2.yx, amount);
    mat.yy = lerp(mat1.yy, mat2.yy, amount);
    mat.yz = lerp(mat1.yz, mat2.yz, amount);
    mat.yt = lerp(mat1.yt, mat2.yt, amount);
    mat.zx = lerp(mat1.zx, mat2.zx, amount);
    mat.zy = lerp(mat1.zy, mat2.zy, amount);
    mat.zz = lerp(mat1.zz, mat2.zz, amount);
    mat.zt = lerp(mat1.zt, mat2.zt, amount);
    mat.tx = lerp(mat1.tx, mat2.tx, amount);
    mat.ty = lerp(mat1.ty, mat2.ty, amount);
    mat.tz = lerp(mat1.tz, mat2.tz, amount);
    mat.tt = lerp(mat1.tt, mat2.tt, amount);
    return mat;
}

Mat4x4 mat4x4_smoothstep(Mat4x4 mat1, Mat4x4 mat2, float amount) {
    Mat4x4 mat;
    mat.xx = smoothstep(mat1.xx, mat2.xx, amount);
    mat.xy = smoothstep(mat1.xy, mat2.xy, amount);
    mat.xz = smoothstep(mat1.xz, mat2.xz, amount);
    mat.xt = smoothstep(mat1.xt, mat2.xt, amount);
    mat.yx = smoothstep(mat1.yx, mat2.yx, amount);
    mat.yy = smoothstep(mat1.yy, mat2.yy, amount);
    mat.yz = smoothstep(mat1.yz, mat2.yz, amount);
    mat.yt = smoothstep(mat1.yt, mat2.yt, amount);
    mat.zx = smoothstep(mat1.zx, mat2.zx, amount);
    mat.zy = smoothstep(mat1.zy, mat2.zy, amount);
    mat.zz = smoothstep(mat1.zz, mat2.zz, amount);
    mat.zt = smoothstep(mat1.zt, mat2.zt, amount);
    mat.tx = smoothstep(mat1.tx, mat2.tx, amount);
    mat.ty = smoothstep(mat1.ty, mat2.ty, amount);
    mat.tz = smoothstep(mat1.tz, mat2.tz, amount);
    mat.tt = smoothstep(mat1.tt, mat2.tt, amount);
    return mat;
}
