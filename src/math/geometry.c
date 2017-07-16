#include "math/geometry.h"
#include "system/error.h"

/* Plane */

Plane plane_new(Vect3D position, Vect3D direction) {
    Plane plane;
    plane.position = position;
    plane.direction = direction;
    return plane;
}

Plane plane_transform(Plane plane, Mat4x4 world, Mat3x3 world_normal) {
    return plane_new(mat4x4_mult_vect3D(world, plane.position),
                     vect3D_normalize(mat3x3_mult_vect3D(world_normal, plane.direction)));
}

Plane plane_transform_space(Plane plane, Mat3x3 space, Mat3x3 space_normal) {
    return plane_new(mat3x3_mult_vect3D(space, plane.position),
                     vect3D_normalize(mat3x3_mult_vect3D(space_normal, plane.direction)));
}

float plane_distance(Plane plane, Vect3D point) {
    return vect3D_dot(vect3D_sub(point, plane.position), plane.direction);
}

bool point_inside_plane(Vect3D point, Plane plane) {
    return vect3D_dot(vect3D_sub(point, plane.position), plane.direction) < 0;
}

bool point_outside_plane(Vect3D point, Plane plane) {
    return vect3D_dot(vect3D_sub(point, plane.position), plane.direction) > 0;
}

bool point_intersects_plane(Vect3D point, Plane plane) {
    return vect3D_dot(vect3D_sub(point, plane.position), plane.direction) == 0;
}

bool point_swept_inside_plane(Vect3D point, Vect3D vect, Plane plane) {
    float angle = vect3D_dot(plane.direction, vect), dist = vect3D_dot(plane.direction, vect3D_sub(point, plane.position));
    if (-dist <= 0.0) return false;
    return !between_or(-dist / angle, 0, 1);
}

bool point_swept_outside_plane(Vect3D point, Vect3D vect, Plane plane) {
    float angle = vect3D_dot(plane.direction, vect), dist = vect3D_dot(plane.direction, vect3D_sub(point, plane.position));
    if (dist <= 0.0) return false;
    return !between_or(-dist / angle, 0, 1);
}

bool point_swept_intersects_plane(Vect3D point, Vect3D vect, Plane plane) {
    float angle = vect3D_dot(plane.direction, vect), dist = vect3D_dot(plane.direction, vect3D_sub(point, plane.position));
    if (dist == 0.0) return true;
    return between_or(-dist / angle, 0, 1);
}

Vect3D plane_closest(Plane plane, Vect3D vect) {
    return vect3D_sub(vect, vect3D_mult(plane.direction, plane_distance(plane, vect)));
}

Vect3D plane_project(Plane plane, Vect3D vect) {
    return vect3D_sub(vect, vect3D_mult(plane.direction, vect3D_dot(vect, plane.direction)));
}

/* Box */

Box box_new(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max) {
    Box new_box;
    new_box.top    = plane_new(vect3D_new(0, y_max, 0), vect3D_new( 1, 1, 0));
    new_box.bottom = plane_new(vect3D_new(0, y_min, 0), vect3D_new( 0,-1, 0));
    new_box.left   = plane_new(vect3D_new(x_max, 0, 0), vect3D_new( 1, 0, 0));
    new_box.right  = plane_new(vect3D_new(x_min, 0, 0), vect3D_new(-1, 0, 0));
    new_box.front  = plane_new(vect3D_new(0, 0, z_max), vect3D_new( 0, 0, 1));
    new_box.back   = plane_new(vect3D_new(0, 0, z_min), vect3D_new( 0, 0,-1));
    return new_box;
}

Box box_sphere(Vect3D center, float radius) {
    Box new_sphere;
    new_sphere.top    = plane_new(vect3D_add(center, vect3D_new(0, radius,0)), vect3D_new(0, 1,0));
    new_sphere.bottom = plane_new(vect3D_add(center, vect3D_new(0,-radius,0)), vect3D_new(0,-1,0));
    new_sphere.left   = plane_new(vect3D_add(center, vect3D_new( radius,0,0)), vect3D_new( 1,0,0));
    new_sphere.right  = plane_new(vect3D_add(center, vect3D_new(-radius,0,0)), vect3D_new(-1,0,0));
    new_sphere.front  = plane_new(vect3D_add(center, vect3D_new(0,0, radius)), vect3D_new(0,0, 1));
    new_sphere.back   = plane_new(vect3D_add(center, vect3D_new(0,0,-radius)), vect3D_new(0,0,-1));
    return new_sphere;
}

Box box_merge(Box box1, Box box2) {
    float x_min = min(box1.right.position.x,  box2.right.position.x);
    float x_max = max(box1.left.position.x,   box2.left.position.x);
    float y_min = min(box1.bottom.position.y, box2.bottom.position.y);
    float y_max = max(box1.top.position.y,    box2.top.position.y);
    float z_min = min(box1.back.position.z,   box2.back.position.z);
    float z_max = max(box1.front.position.z,  box2.front.position.z);
    return box_new(x_min, x_max, y_min, y_max, z_min, z_max);
}

Box box_transform(Box box, Mat4x4 world, Mat3x3 world_normal) {
    Box transformed_box;
    transformed_box.top    = plane_transform(box.top,    world, world_normal);
    transformed_box.bottom = plane_transform(box.bottom, world, world_normal);
    transformed_box.left   = plane_transform(box.left,   world, world_normal);
    transformed_box.right  = plane_transform(box.right,  world, world_normal);
    transformed_box.front  = plane_transform(box.front,  world, world_normal);
    transformed_box.back   = plane_transform(box.back,   world, world_normal);
    return transformed_box;
}

Box box_invert(Box box) {
    Box inv;
    inv.front.direction  = vect3D_negative(box.front.direction);
    inv.back.direction   = vect3D_negative(box.back.direction);
    inv.left.direction   = vect3D_negative(box.left.direction);
    inv.right.direction  = vect3D_negative(box.right.direction);
    inv.top.direction    = vect3D_negative(box.top.direction);
    inv.bottom.direction = vect3D_negative(box.bottom.direction);
    return inv;
}

Box box_invert_depth(Box box) {
    Box inv;
    inv.front.direction  = vect3D_negative(box.front.direction);
    inv.back.direction   = vect3D_negative(box.back.direction);
    inv.left.direction   = box.left.direction;
    inv.right.direction  = box.right.direction;
    inv.top.direction    = box.top.direction;
    inv.bottom.direction = box.bottom.direction;
    return inv;
}

Box box_invert_width(Box box) {ox
    Box inv;
    inv.front.direction  = box.front.direction;
    inv.back.direction   = box.back.direction;
    inv.left.direction   = vect3D_negative(box.left.direction);
    inv.right.direction  = vect3D_negative(box.right.direction);
    inv.top.direction    = box.top.direction;
    inv.bottom.direction = box.bottom.direction;
    return inv;
}

Box box_invert_height(Box box) {
    Box inv;
    inv.front.direction  = box.front.direction;
    inv.back.direction   = box.back.direction;
    inv.left.direction   = box.left.direction;
    inv.right.direction  = box.right.direction;
    inv.top.direction    = vect3D_negative(box.top.direction);
    inv.bottom.direction = vect3D_negative(box.bottom.direction);
    return inv;
}

bool point_inside_box(Vect3D point, Box box) {
    if (!point_inside_plane(point, box.top))    return false;
    if (!point_inside_plane(point, box.bottom)) return false;
    if (!point_inside_plane(point, box.left))   return false;
    if (!point_inside_plane(point, box.right))  return false;
    if (!point_inside_plane(point, box.front))  return false;
    if (!point_inside_plane(point, box.back))   return false;
    return true;
}

bool point_outside_box(Vect3D point, Box box) {
    return !(point_intersects_box(point, box) || point_inside_box(point, box));
}

bool point_intersects_box(Vect3D point, Box box) {
    bool in_left = !point_outside_plane(point, box.left), in_right = !point_outside_plane(point, box.right);
    bool in_front = !point_outside_plane(point, box.front), in_back = !point_outside_plane(point, box.back);
    bool in_top = !point_outside_plane(point, box.top), in_bottom = !point_outside_plane(point, box.bottom);
    if (point_intersects_plane(point, box.top) && in_left && in_right && in_front && in_back) return true;
    if (point_intersects_plane(point, box.bottom) && in_left && in_right && in_front && in_back) return true;
    if (point_intersects_plane(point, box.left) && in_top && in_bottom && in_front && in_back) return true;
    if (point_intersects_plane(point, box.right) && in_top && in_bottom && in_front && in_back) return true;
    if (point_intersects_plane(point, box.front) && in_top && in_bottom && in_left && in_right) return true;
    if (point_intersects_plane(point, box.back) && in_top && in_bottom && in_left && in_right) return true;
    return false;
}

/* Frustum */

Frustum frustum_new(Vect3D ntr, Vect3D ntl, Vect3D nbr, Vect3D nbl, Vect3D ftr, Vect3D ftl, Vect3D fbr, Vect3D fbl) {
    Frustum frust;
    frust.ntr = ntr;
    frust.ntl = ntl;
    frust.nbr = nbr;
    frust.nbl = nbl;
    frust.ftr = ftr;
    frust.ftl = ftl;
    frust.fbr = fbr;
    frust.fbl = fbl;
    return frust;
}

Frustum frustum_new_clipbox() {
    return frustum_new(vect3D_new(1, 1,-1), vect3D_new(-1, 1,-1),
                       vect3D_new(1,-1,-1), vect3D_new(-1,-1,-1),
                       vect3D_new(1, 1, 1), vect3D_new(-1, 1, 1),
                       vect3D_new(1,-1, 1), vect3D_new(-1,-1, 1));
}

Frustum frustum_new_camera(Mat4x4 view, Mat4x4 proj) {
    Frustum frust = frustum_new_clipbox();
    frust = frustum_transform(frust, mat4x4_inverse(proj));
    frust = frustum_transform(frust, mat4x4_inverse(view));
    return frust;
}

Frustum frustum_slice(Frustum frust, float start, float end) {
    Frustum r;
    r.ntr = vect3D_add(frust.ntr, vect3D_mult(vect3D_sub(frust.ftr, frust.ntr), start));
    r.ftr = vect3D_add(frust.ntr, vect3D_mult(vect3D_sub(frust.ftr, frust.ntr), end  ));

    r.ntl = vect3D_add(frust.ntl, vect3D_mult(vect3D_sub(frust.ftl, frust.ntl), start));
    r.ftl = vect3D_add(frust.ntl, vect3D_mult(vect3D_sub(frust.ftl, frust.ntl), end  ));

    r.nbr = vect3D_add(frust.nbr, vect3D_mult(vect3D_sub(frust.fbr, frust.nbr), start));
    r.fbr = vect3D_add(frust.nbr, vect3D_mult(vect3D_sub(frust.fbr, frust.nbr), end  ));

    r.nbl = vect3D_add(frust.nbl, vect3D_mult(vect3D_sub(frust.fbl, frust.nbl), start));
    r.fbl = vect3D_add(frust.nbl, vect3D_mult(vect3D_sub(frust.fbl, frust.nbl), end  ));
    return r;
}

Frustum frustum_transform(Frustum frust, Mat4x4 mat) {
    Frustum r;
    r.ntr = mat4x4_mult_vect3D(mat, frust.ntr);
    r.ftr = mat4x4_mult_vect3D(mat, frust.ftr);
    r.ntl = mat4x4_mult_vect3D(mat, frust.ntl);
    r.ftl = mat4x4_mult_vect3D(mat, frust.ftl);
    r.nbr = mat4x4_mult_vect3D(mat, frust.nbr);
    r.fbr = mat4x4_mult_vect3D(mat, frust.fbr);
    r.nbl = mat4x4_mult_vect3D(mat, frust.nbl);
    r.fbl = mat4x4_mult_vect3D(mat, frust.fbl);
    return r;
}

Frustum frustum_translate(Frustum frust, Vect3D vect) {
    Frustum r;
    r.ntr = vect3D_add(frust.ntr, vect);
    r.ftr = vect3D_add(frust.ftr, vect);
    r.ntl = vect3D_add(frust.ntl, vect);
    r.ftl = vect3D_add(frust.ftl, vect);
    r.nbr = vect3D_add(frust.nbr, vect);
    r.fbr = vect3D_add(frust.fbr, vect);
    r.nbl = vect3D_add(frust.nbl, vect);
    r.fbl = vect3D_add(frust.fbl, vect);
    return r;
}

Vect3D frustum_center(Frustum frust) {
    Vect3D total = vect3D_zero();
    total = vect3D_add(total, frust.ntr);
    total = vect3D_add(total, frust.ftr);
    total = vect3D_add(total, frust.ntl);
    total = vect3D_add(total, frust.ftl);
    total = vect3D_add(total, frust.nbr);
    total = vect3D_add(total, frust.fbr);
    total = vect3D_add(total, frust.nbl);
    total = vect3D_add(total, frust.fbl);
    return vect3D_div(total, 8);
}

Vect3D frustum_maximums(Frustum frust) {
    Vect3D r;
    r.x = max(max(max(max(max(max(max(frust.ntr.x, frust.ftr.x), frust.ntl.x), frust.ftl.x), frust.nbr.x), frust.fbr.x), frust.nbl.x), frust.fbl.x);
    r.y = max(max(max(max(max(max(max(frust.ntr.y, frust.ftr.y), frust.ntl.y), frust.ftl.y), frust.nbr.y), frust.fbr.y), frust.nbl.y), frust.fbl.y);
    r.z = max(max(max(max(max(max(max(frust.ntr.z, frust.ftr.z), frust.ntl.z), frust.ftl.z), frust.nbr.z), frust.fbr.z), frust.nbl.z), frust.fbl.z);
    return r;
}

Vect3D frustum_minimums(Frustum frust) {
    Vect3D r;
    r.x = min(min(min(min(min(min(min(frust.ntr.x, frust.ftr.x), frust.ntl.x), frust.ftl.x), frust.nbr.x), frust.fbr.x), frust.nbl.x), frust.fbl.x);
    r.y = min(min(min(min(min(min(min(frust.ntr.y, frust.ftr.y), frust.ntl.y), frust.ftl.y), frust.nbr.y), frust.fbr.y), frust.nbl.y), frust.fbl.y);
    r.z = min(min(min(min(min(min(min(frust.ntr.z, frust.ftr.z), frust.ntl.z), frust.ftl.z), frust.nbr.z), frust.fbr.z), frust.nbl.z), frust.fbl.z);
    return r;
}

Box frustum_box(Frustum frust) {
    Box box;
    box.top     = plane_new(frust.ntr, vect3D_normalize(vect3D_cross(vect3D_sub(frust.ftr, frust.ntr), vect3D_sub(frust.ntl, frust.ntr))));
    box.bottom  = plane_new(frust.nbr, vect3D_normalize(vect3D_cross(vect3D_sub(frust.nbl, frust.nbr), vect3D_sub(frust.fbr, frust.nbr))));
    box.left    = plane_new(frust.ntl, vect3D_normalize(vect3D_cross(vect3D_sub(frust.ftl, frust.ntl), vect3D_sub(frust.nbl, frust.ntl))));
    box.right   = plane_new(frust.ntr, vect3D_normalize(vect3D_cross(vect3D_sub(frust.nbr, frust.ntr), vect3D_sub(frust.ftr, frust.ntr))));
    box.front   = plane_new(frust.ftr, vect3D_normalize(vect3D_cross(vect3D_sub(frust.ftl, frust.ftr), vect3D_sub(frust.fbr, frust.ftr))));
    box.back    = plane_new(frust.ntr, vect3D_normalize(vect3D_cross(vect3D_sub(frust.nbr, frust.ntr), vect3D_sub(frust.ntl, frust.ntr))));
    return box;
}

bool frustum_outside_box(Frustum frust, Box box) {
    error("Unimplemented");
    return false;
}

/* Sphere */

Sphere sphere_new(Vect3D center, float radius) {
    Sphere sphere;
    sphere.center = center;
    sphere.radius = radius;
    return sphere;
}

Sphere sphere_unit() {
    return sphere_new(vect3D_zero(), 1);
}

Sphere sphere_point() {
    return sphere_new(vect3D_zero(), 0);
}

Sphere sphere_merge(Sphere sphere1, Sphere sphere2) {
    Vect3D dir = vect3D_sub(sphere2.center, sphere1.center);
    Vect3D dirnorm = vect3D_normalize(dir);
    Vect3D p0 = vect3D_sub(sphere1.center, vect3D_mult(dirnorm, sphere1.radius));
    Vect3D p1 = vect3D_add(sphere2.center, vect3D_mult(dirnorm, sphere2.radius));
    Vect3D center = vect3D_div(vect3D_add(p0, p1), 2);
    float dist = vect3D_dist(center, p0);
    return sphere_new(center, dist);
}

Sphere sphere_merge_many(Sphere* spheres, int count) {
    Sphere result = spheres[0];
    for (int i = 1; i < count; i++) result = sphere_merge(result, spheres[i]);
    return result;
}

Sphere sphere_transform(Sphere sphere, Mat4x4 world) {
    return sphere_new(mat4x4_mult_vect3D(world, sphere.center), sphere.radius * max(max(world.xx, world.yy), world.zz));
}

Sphere sphere_translate(Sphere sphere, Vect3D x) {
    return sphere_new(vect3D_add(sphere.center, x), sphere.radius);
}

Sphere sphere_scale(Sphere sphere, float x) {
    return sphere_new(sphere.center, sphere.radius * x);
}

Sphere sphere_transform_space(Sphere sphere, Mat3x3 space) {
    return sphere_new(mat3x3_mult_vect3D(space, sphere.center), sphere.radius * max(max(space.xx, space.yy), space.zz));
}

Sphere sphere_of_box(Box box) {
    float x_max = bb.left.position.x, x_min = bb.right.position.x;
    float y_max = bb.top.position.y, y_min = bb.bottom.position.y;
    float z_max = bb.front.position.z, z_min = bb.back.position.z;
    Vect3D center;
    center.x = (x_min + x_max) / 2;
    center.y = (y_min + y_max) / 2;
    center.z = (z_min + z_max) / 2;
    float radius = 0;
    radius = max(radius, vect3D_dist(center, vect3D_new(x_min, y_min, z_min)));
    radius = max(radius, vect3D_dist(center, vect3D_new(x_max, y_min, z_min)));
    radius = max(radius, vect3D_dist(center, vect3D_new(x_min, y_max, z_min)));
    radius = max(radius, vect3D_dist(center, vect3D_new(x_min, y_min, z_max)));
    radius = max(radius, vect3D_dist(center, vect3D_new(x_min, y_max, z_max)));
    radius = max(radius, vect3D_dist(center, vect3D_new(x_max, y_max, z_min)));
    radius = max(radius, vect3D_dist(center, vect3D_new(x_max, y_min, z_max)));
    radius = max(radius, vect3D_dist(center, vect3D_new(x_max, y_max, z_max)));
    return sphere_new(center, radius);
}

Sphere sphere_of_frustum(Frustum frust) {
    Sphere sphere;
    sphere.center = frustum_center(frust);
    sphere.radius = 0;
    sphere.radius = max(sphere.radius, vect3D_dist(sphere.center, frust.ntr));
    sphere.radius = max(sphere.radius, vect3D_dist(sphere.center, frust.ftr));
    sphere.radius = max(sphere.radius, vect3D_dist(sphere.center, frust.ntl));
    sphere.radius = max(sphere.radius, vect3D_dist(sphere.center, frust.ftl));
    sphere.radius = max(sphere.radius, vect3D_dist(sphere.center, frust.nbr));
    sphere.radius = max(sphere.radius, vect3D_dist(sphere.center, frust.fbr));
    sphere.radius = max(sphere.radius, vect3D_dist(sphere.center, frust.nbl));
    sphere.radius = max(sphere.radius, vect3D_dist(sphere.center, frust.fbl));
    return sphere;
}

bool sphere_inside_box(Sphere sphere, Box box) {
    if (!sphere_inside_plane(sphere, box.front))  return false;
    if (!sphere_inside_plane(sphere, box.back))   return false;
    if (!sphere_inside_plane(sphere, box.top))    return false;
    if (!sphere_inside_plane(sphere, box.bottom)) return false;
    if (!sphere_inside_plane(sphere, box.left))   return false;
    if (!sphere_inside_plane(sphere, box.right))  return false;
    return true;
}

bool sphere_outside_box(Sphere sphere, Box box) {
    return !(sphere_inside_box(sphere, box) || sphere_intersects_box(sphere, box));
}

bool sphere_intersects_box(Sphere sphere, Box box) {
    bool in_left = !sphere_outside_plane(sphere, box.left), in_right = !sphere_outside_plane(sphere, box.right);
    bool in_front = !sphere_outside_plane(sphere, box.front), in_back = !sphere_outside_plane(sphere, box.back);
    bool in_top = !sphere_outside_plane(sphere, box.top), in_bottom = !sphere_outside_plane(sphere, box.bottom);
    if (sphere_intersects_plane(sphere, box.top) && in_left && in_right && in_front && in_back) return true;
    if (sphere_intersects_plane(sphere, box.bottom) && in_left && in_right && in_front && in_back) return true;
    if (sphere_intersects_plane(sphere, box.left) && in_top && in_bottom && in_front && in_back) return true;
    if (sphere_intersects_plane(sphere, box.right) && in_top && in_bottom && in_front && in_back) return true;
    if (sphere_intersects_plane(sphere, box.front) && in_top && in_bottom && in_left && in_right) return true;
    if (sphere_intersects_plane(sphere, box.back) && in_top && in_bottom && in_left && in_right) return true;
    return false;
}

bool sphere_inside_frustum(Sphere sphere, Frustum frust) {
    return sphere_inside_box(sphere, frustum_box(frust));
}

bool sphere_outside_frustum(Sphere sphere, Frustum frust) {
    return sphere_outside_box(sphere, frustum_box(frust));
}

bool sphere_intersects_frustum(Sphere sphere, Frustum frust) {
    return sphere_intersects_box(sphere, frustum_box(frust));
}

bool sphere_outside_sphere(Sphere sphere1, Sphere sphere2) {
    float rtot = sphere1.radius + sphere2.radius;
    return vect3D_dist_sqrd(sphere1.center, sphere2.center) > rtot * rtot;
}

bool sphere_inside_sphere(Sphere sphere1, Sphere sphere2) {
    error("Unimplemented");
    return false;
}

bool sphere_intersects_sphere(Sphere sphere1, Sphere sphere2);

bool point_inside_sphere(Sphere sphere, Vect3D point) {
    return vect3D_dist(sphere.center, point) < sphere.radius;
}

bool point_outside_sphere(Sphere sphere, Vect3D point) {
    return vect3D_dist(sphere.center, point) > sphere.radius;
}

bool point_intersects_sphere(Sphere sphere, Vect3D point) {
    return vect3D_dist(sphere.center, point) == sphere.radius;
}

bool line_inside_sphere(Sphere sphere, Vect3D start, Vect3D end) {
    return point_swept_inside_sphere(sphere, vect3D_sub(end, start), start);
}

bool line_outside_sphere(Sphere sphere, Vect3D start, Vect3D end) {
    return point_swept_outside_sphere(sphere, vect3D_sub(end, start), start);
}

bool line_intersects_sphere(Sphere sphere, Vect3D start, Vect3D end) {
    return point_swept_intersects_sphere(sphere, vect3D_sub(end, start), start);
}

bool sphere_inside_plane(Sphere sphere, Plane plane) {
    return -plane_distance(plane, sphere.center) > sphere.radius;
}

bool sphere_outside_plane(Sphere sphere, Plane plane) {
    return plane_distance(plane, sphere.center) > sphere.radius;
}

bool sphere_intersects_plane(Sphere sphere, Plane plane) {
    return max(plane_distance(plane, sphere.center), -plane_distance(plane, sphere.center)) <= sphere.radius;
}

static bool quadratic(float a, float b, float c, float* t0, float* t1) {
    float descrim = b * b - 4 * a * c;
    if (descrim < 0) {
        return false;
    } else {
        float d = sqrtf(descrim);
        float q = (b < 0) ? (-b - d) / 2.0 : (-b + d) / 2.0;
        *t0 = q / a;
        *t1 = c / q;
        return true;
    }
}

bool point_swept_inside_sphere(Sphere sphere, Vect3D vect, Vect3D point) {
    error("Unimplemented");
    return false;
}

bool point_swept_outside_sphere(Sphere sphere, Vect3D vect, Vect3D point) {
    float sdist = vect3D_dist_sqrd(point, sphere.center);
    if (sdist <= sphere.radius * sphere.radius) return false;
    Vect3D o = vect3D_sub(point, sphere.center);
    float A = vect3D_dot(vect, vect);
    float B = 2 * vect3D_dot(vect, o);
    float C = vect3D_dot(o, o) - (sphere.radius * sphere.radius);
    float t0, t1, t;
    if (!quadratic(A, B, C, &t0, &t1)) return true;
    return (!between_or(t0, 0, 1) && !between_or(t1, 0, 1));
}

bool point_swept_intersects_sphere(Sphere sphere, Vect3D vect, Vect3D point) {
    error("Unimplemented");
    return false;
}

bool sphere_swept_inside_plane(Sphere sphere, Vect3D vect, Plane plane) {
    float angle = vect3D_dot(plane.direction, vect);
    float dist  = vect3D_dot(plane.direction, vect3D_sub(sphere.center, plane.position));
    if (-dist <= sphere.radius) return false;
    float t0 = ( sphere.radius - dist) / angle;
    float t1 = (-sphere.radius - dist) / angle;
    return (!between_or(t0, 0, 1) && !between_or(t1, 0, 1));
}

bool sphere_swept_outside_plane(Sphere sphere, Vect3D vect, Plane plane) {
    float angle = vect3D_dot(plane.direction, vect);
    float dist  = vect3D_dot(plane.direction, vect3D_sub(sphere.center, plane.position));
    if (dist <= sphere.radius) return false;
    float t0 = ( sphere.radius - dist) / angle;
    float t1 = (-sphere.radius - dist) / angle;
    return (!between_or(t0, 0, 1) && !between_or(t1, 0, 1));
}

bool sphere_swept_intersects_plane(Sphere sphere, Vect3D vect, Plane plane) {
    float angle = vect3D_dot(plane.direction, vect);
    float dist  = vect3D_dot(plane.direction, vect3D_sub(sphere.center, plane.position));
    if (max(dist, -dist) <= sphere.radius) return true;
    float t0 = ( sphere.radius - dist) / angle;
    float t1 = (-sphere.radius - dist) / angle;
    return between_or(t0, 0, 1) || between_or(t1, 0, 1);
}

bool sphere_swept_outside_sphere(Sphere sphere1, Vect3D vect, Sphere sphere2) {
    float sdist = vect3D_dist_sqrd(sphere1.center, sphere2.center);
    float rtot = sphere1.radius + sphere2.radius;
    if (sdist <= rtot * rtot) return false;
    Vect3D o = vect3D_sub(sphere1.center, sphere2.center);
    float A = vect3D_dot(vect, vect);
    float B = 2 * vect3D_dot(vect, o);
    float C = vect3D_dot(o, o) - rtot * rtot;
    float t0, t1, t;
    if (!quadratic(A, B, C, &t0, &t1)) return true;
    return (!between_or(t0, 0, 1) && !between_or(t1, 0, 1));
}

bool sphere_swept_inside_sphere(Sphere sphere1, Vect3D vect, Sphere sphere2) {
    error("Unimplemented");
    return false;
}

bool sphere_swept_intersects_sphere(Sphere sphere1, Vect3D vect, Sphere sphere2) {
    error("Unimplemented");
    return false;
}

bool point_inside_triangle(Vect3D point, Vect3D vect0, Vect3D vect1, Vect3D vect2) {
    Vect3D d0 = vect3D_sub(vect2, vect0);
    Vect3D d1 = vect3D_sub(vect1, vect0);
    Vect3D d2 = vect3D_sub(point, vect0);
    float dot00 = vect3D_dot(d0, d0), dot01 = vect3D_dot(d0, d1), dot02 = vect3D_dot(d0, d2);
    float dot11 = vect3D_dot(d1, d1), dot12 = vect3D_dot(d1, d2);
    float inv_dom = 1.0f / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * inv_dom;
    float v = (dot00 * dot12 - dot01 * dot02) * inv_dom;
    return (u >= 0) && (v >= 0) && (u + v < 1);
}

bool sphere_intersects_face(Sphere sphere, Vect3D vect0, Vect3D vect1, Vect3D vect2, Vect3D norm) {
    if (!sphere_intersects_plane(sphere, plane_new(vect0, norm))) return false;
    Vect3D closest = plane_closest(plane_new(vect0, norm), sphere.center);
    return point_inside_triangle(closest, vect0, vect1, vect2);
}

/* Ellipsoid */

Ellipsoid ellipsoid_new(Vect3D center, Vect3D radiuses) {
    Ellipsoid ellipse;
    ellipse.center = center;
    ellipse.radiuses = radiuses;
    return ellipse;
}

Ellipsoid ellipsoid_transform(Ellipsoid ellipse, Mat4x4 mat) {
    return ellipsoid_new(mat4x4_mult_vect3D(mat, ellipse.center),
                         mat3x3_mult_vect3D(mat4x4_to_mat3x3(mat), ellipse.radiuses));
}

Ellipsoid ellipsoid_of_sphere(Sphere sphere) {
    return ellipsoid_new(sphere.center, vect3D_new(sphere.radius, sphere.radius, sphere.radius));
}

Mat3x3 ellipsoid_space(Ellipsoid ellipse) {
    return mat3x3_new(1.0/ellipse.radiuses.x, 0, 0,
                      0, 1.0/ellipse.radiuses.y, 0,
                      0, 0, 1.0/ellipse.radiuses.z);
}

Mat3x3 ellipsoid_inv_space(Ellipsoid ellipse) {
    return mat3x3_new(ellipse.radiuses.x, 0, 0,
                      0, ellipse.radiuses.y, 0,
                      0, 0, ellipse.radiuses.z);
}

/* Capsule */

Capsule capsule_new(Vect3D start, Vect3D end, float radius) {
    Capsule capsule;
    capsule.start = start;
    capsule.end = end;
    capsule.radius = radius;
    return capsule;
}

Capsule capsule_transform(Capsule capsule, Mat4x4 mat) {
    return capsule_new(mat4x4_mult_vect3D(mat, capsule.start),
                       mat4x4_mult_vect3D(mat, capsule.end),
                       capsule.radius * max(max(mat.xx, mat.yy), mat.zz));
}

bool capsule_inside_plane(Capsule capsule, Plane plane) {
    return (sphere_inside_plane(sphere_new(capsule.start, capsule.radius), plane) &&
            sphere_inside_plane(sphere_new(capsule.end,   capsule.radius), plane));
}

bool capsule_outside_plane(Capsule capsule, Plane plane) {
    return (sphere_outside_plane(sphere_new(capsule.start, capsule.radius), plane) &&
            sphere_outside_plane(sphere_new(capsule.end,   capsule.radius), plane));
}

bool capsule_intersects_plane(Capsule capsule, Plane plane) {
    return (!capsule_inside_plane(capsule, plane) && !capsule_outside_plane(capsule, plane));
}

/* Vertex */

Vertex vertex_new() {
    Vertex vex;
    memset(&vex, 0, sizeof(Vertex));
    return vex;
}

bool vertex_equal(Vertex vex1, Vertex vex2) {
    if(!vect3D_equ(vex1.position, vex2.position)) return false;
    if(!vect3D_equ(vex1.normal, vex2.normal)) return false;
    if(!vect2D_equ(vex1.uvs, vex2.uvs)) return false;
    return true;
}

void vertex_print(Vertex vex) {
    printf("V(Position: "); vect3D_print(v.position);
    printf(", Normal: "); vect3D_print(v.normal);
    printf(", Tangent: "); vect3D_print(v.tangent);
    printf(", Binormal: "); vect3D_print(v.binormal);
    printf(", Color: "); vect4D_print(v.color);
    printf(", Uvs: "); vect2D_print(v.uvs);
    printf(")\n");
}

/* Mesh */

Mesh* mesh_new() {
    Mesh* mesh = malloc(sizeof(Mesh));
    mesh->num_verts = 0;
    mesh->num_triangles = 0;
    mesh->verticies = malloc(sizeof(Vertex) * mesh->num_verts);
    mesh->triangles = malloc(sizeof(int) * mesh->num_triangles * 3);
    return mesh;
}

void mesh_delete(Mesh* mesh) {
    free(mesh->triangles);
    FREE(mesh->verticies);
    FREE(mesh);
}

void mesh_generate_normals(Mesh* mesh) {
    for(int i = 0; i < mesh->num_verts; i++) {
        mesh->verticies[i].normal = vect3D_zero();
    }
    int i = 0;
    while( i < mesh->num_triangles * 3) {
        int t_i1 = mesh->triangles[i], t_i2 = mesh->triangles[i+1], t_i3 = mesh->triangles[i+2];
        Vertex vert1 = mesh->verticies[t_i1], vert2 = mesh->verticies[t_i2], vert3 = mesh->verticies[t_i3];
        Vect3D face_normal = triangle_normal(vert1, vert2, vert3);
        vert1.normal = vect3D_add(face_normal, vert1.normal);
        vert2.normal = vect3D_add(face_normal, vert2.normal);
        vert3.normal = vect3D_add(face_normal, vert3.normal);
        mesh->verticies[t_i1] = vert1;
        mesh->verticies[t_i2] = vert2;
        mesh->verticies[t_i3] = vert3;
        i = i + 3;
    }
    for(int i = 0; i < mesh->num_verts; i++) {
        mesh->verticies[i].normal = vect3D_normalize( mesh->verticies[i].normal);
    }
}

void mesh_generate_tangents(Mesh* mesh) {
    for (int i = 0; i < mesh->num_verts; i++) {
        mesh->verticies[i].tangent = vect3D_zero();
        mesh->verticies[i].binormal = vect3D_zero();
    }
    int i = 0;
    while(i < mesh->num_triangles * 3) {
        int t_i1 = mesh->triangles[i], t_i2 = mesh->triangles[i+1], t_i3 = mesh->triangles[i+2];
        Vertex vert1 = mesh->verticies[t_i1], vert2 = mesh->verticies[t_i2], vert3 = mesh->verticies[t_i3];
        Vect3D face_tangent = triangle_tangent(vert1, vert2, vert3), face_binormal = triangle_binormal(vert1, vert2, vert3);
        vert1.tangent = vect3D_add(face_tangent, vert1.tangent);
        vert2.tangent = vect3D_add(face_tangent, vert2.tangent);
        vert3.tangent = vect3D_add(face_tangent, vert3.tangent);
        vert1.binormal = vect3D_add(face_binormal, vert1.binormal);
        vert2.binormal = vect3D_add(face_binormal, vert2.binormal);
        vert3.binormal = vect3D_add(face_binormal, vert3.binormal);
        mesh->verticies[t_i1] = vert1;
        mesh->verticies[t_i2] = vert2;
        mesh->verticies[t_i3] = vert3;
        i = i + 3;
    }
    for(int i = 0; i < mesh->num_verts; i++) {
        mesh->verticies[i].tangent = vect3D_normalize(mesh->verticies[i].tangent);
        mesh->verticies[i].binormal = vect3D_normalize(mesh->verticies[i].binormal);
    }
}

void mesh_generate_orthagonal_tangents(Mesh* mesh) {
    for(int i = 0; i < mesh->num_verts; i++) {
        mesh->verticies[i].tangent = vect3D_zero();
        mesh->verticies[i].binormal = vect3D_zero();
    }
    int i = 0;
    while( i < mesh->num_triangles * 3) {
        int t_i1 = mesh->triangles[i], t_i2 = mesh->triangles[i+1], t_i3 = mesh->triangles[i+2];
        Vertex vert1 = mesh->verticies[t_i1], vert2 = mesh->verticies[t_i2], vert3 = mesh->verticies[t_i3];
        Vect3D face_normal = triangle_normal(vert1, vert2, vert3);
        Vect3D face_binormal_temp = triangle_binormal(vert1, vert2, vert3);
        Vect3D face_tangent = vect3D_normalize( vect3D_cross(face_binormal_temp, face_normal));
        Vect3D face_binormal = vect3D_normalize( vect3D_cross(face_tangent, face_normal));
        vert1.tangent = vect3D_add(face_tangent, vert1.tangent);
        vert2.tangent = vect3D_add(face_tangent, vert2.tangent);
        vert3.tangent = vect3D_add(face_tangent, vert3.tangent);
        vert1.binormal = vect3D_add(face_binormal, vert1.binormal);
        vert2.binormal = vect3D_add(face_binormal, vert2.binormal);
        vert3.binormal = vect3D_add(face_binormal, vert3.binormal);
        mesh->verticies[t_i1] = vert1;
        mesh->verticies[t_i2] = vert2;
        mesh->verticies[t_i3] = vert3;
        i = i + 3;
    }
    for(int i = 0; i < mesh->num_verts; i++) {
        mesh->verticies[i].tangent = vect3D_normalize(mesh->verticies[i].tangent);
        mesh->verticies[i].binormal = vect3D_normalize(mesh->verticies[i].binormal);
    }
}

void mesh_generate_texcoords_cylinder(Mesh* mesh) {
    Vect2D unwrap_vector = vect2D_new(1, 0);
	float max_height = -99999999, min_height = 99999999;
	for(int i = 0; i < mesh->num_verts; i++) {
		float v = mesh->verticies[i].position.y;
		max_height = max(max_height, v);
		min_height = min(min_height, v);
		vec2 proj_position = vect2D_new(mesh->verticies[i].position.x, mesh->verticies[i].position.z);
		Vect2D from_center = vect2D_normalize(proj_position);
		float u = (vect2D_dot(from_center, unwrap_vector) + 1) / 8;
		mesh->verticies[i].uvs = vect2D_new(u, v);
	}
	float scale = (max_height - min_height);
	for(int i = 0; i < mesh->num_verts; i++) {
		mesh->verticies[i].uvs = vect2D_new(mesh->verticies[i].uvs.x, mesh->verticies[i].uvs.y / scale);
	}
}

void mesh_print(Mesh* mesh) {
    printf("Num Verts: %i\n", mesh->num_verts);
    printf("Num Tris: %i\n", mesh->num_triangles);
    for(int i=0; i < mesh->num_verts; i++) {
        vertex_print(mesh->verticies[i]); printf("\n");
    }
    printf("Triangle Indicies:");
    for(int i=0; i < mesh->num_triangles * 3; i++) {
        printf("%i ", mesh->triangles[i]);
    }
    printf("\n");
}

float mesh_surface_area(Mesh* mesh) {
    float total = 0.0;
    int i = 0;
    while(i < mesh->num_triangles * 3) {
        int t_i1 = mesh->triangles[i], t_i2 = mesh->triangles[i+1], t_i3 = mesh->triangles[i+2];
        Vertex vert1 = mesh->verticies[t_i1], vert2 = mesh->verticies[t_i2], vert3 = mesh->verticies[t_i3];
        total += triangle_area(vert1, vert2, vert3);
        i = i + 3;
    }
    return total;
}

void mesh_transform(Mesh* mesh, Mat4x4 transform) {
    int i = 0;
    while(i < mesh->num_triangles * 3) {
        int t_i1 = mesh->triangles[i], t_i2 = mesh->triangles[i+1], t_i3 = mesh->triangles[i+2];
        mesh->verticies[t_i1].position = mat4x4_mult_vect3D(transform, mesh->verticies[t_i1].position);
        mesh->verticies[t_i2].position = mat4x4_mult_vect3D(transform, mesh->verticies[t_i2].position);
        mesh->verticies[t_i3].position = mat4x4_mult_vect3D(transform, mesh->verticies[t_i3].position);
        i = i + 3;
    }
}

void mesh_translate(Mesh* mesh, Vect3D translation) {
    int i = 0;
    while(i < mesh->num_triangles * 3) {
        int t_i1 = mesh->triangles[i], t_i2 = mesh->triangles[i+1], t_i3 = mesh->triangles[i+2];
        mesh->verticies[t_i1].position = vect3D_add(mesh->verticies[t_i1].position, translation);
        mesh->verticies[t_i2].position = vect3D_add(mesh->verticies[t_i2].position, translation);
        mesh->verticies[t_i3].position = vect3D_add(mesh->verticies[t_i3].position, translation);
        i = i + 3;
    }
}

void mesh_scale(Mesh* mesh, float scale) {
    int i = 0;
    while(i < mesh->num_triangles * 3) {
        int t_i1 = mesh->triangles[i], t_i2 = mesh->triangles[i+1], t_i3 = mesh->triangles[i+2];
        mesh->verticies[t_i1].position = vect3D_mult(mesh->verticies[t_i1].position, scale);
        mesh->verticies[t_i2].position = vect3D_mult(mesh->verticies[t_i2].position, scale);
        mesh->verticies[t_i3].position = vect3D_mult(mesh->verticies[t_i3].position, scale);
        i = i + 3;
    }
}

Sphere mesh_bounding_sphere(Mesh* mesh) {
    Sphere Sphere = sphere_new(vect3D_zero(), 0);
    for (int i = 0; i < mesh->num_verts; i++) {
        sphere.center = vect3D_add(sphere.center, mesh->verticies[i].position);
    }
    sphere.center = vect3D_div(sphere.center, mesh->num_verts);
    for (int i = 0; i < mesh->num_verts; i++) {
        sphere.radius = max(sphere.radius, vect3D_dist(sphere.center, mesh->verticies[i].position));
    }
    return sphere;
}

/* Model */

Model* model_new() {
    Model* model = malloc(sizeof(Model));
    model->num_meshes = 0;
    model->meshes = malloc(sizeof(Mesh*) * model->num_meshes);
    return model;
}

void model_delete(Model* model) {
    for (int i = 0; i < model->num_meshes; i++) {
        mesh_delete(model->meshes[i]);
    }
    free(model);
}

void model_generate_normals(Model* model) {
    for(int i = 0; i < model->num_meshes; i++) {
        mesh_generate_normals(model->meshes[i]);
    }
}

void model_generate_tangents(Model* model) {
    for(int i = 0; i < model->num_meshes; i++) {
        mesh_generate_tangents(model->meshes[i]);
    }
}

void model_generate_orthagonal_tangents(Model* model) {
    for(int i = 0; i < model->num_meshes; i++) {
        mesh_generate_orthagonal_tangents(model->meshes[i]);
    }
}

void model_generate_texcoords_cylinder(Model* model) {
    for(int i = 0; i < model->num_meshes; i++) {
        mesh_generate_texcoords_cylinder(model->meshes[i]);
    }
}

void model_print(Model* model) {
    for(int i = 0; i < model->num_meshes; i++) {
        mesh_print(model->meshes[i]);
    }
}

float model_surface_area(Model* model) {
    float total = 0.0f;
    for(int i = 0; i < model->num_meshes; i++) {
        total += mesh_surface_area(model->meshes[i]);
    }
    return total;
}

void model_transform(Model* model, Mat4x4 transform) {
    for(int i = 0; i < model->num_meshes; i++) {
        mesh_transform(model->meshes[i], transform);
    }
}

void model_translate(Model* model, Vect3D translation) {
    for(int i = 0; i < model->num_meshes; i++) {
        mesh_translate(model->meshes[i], translation);
    }
}

void model_scale(Model* model, float scale) {
    for(int i = 0; i < model->num_meshes; i++) {
        mesh_scale(model->meshes[i], scale);
    }
}

/* Triangle */

Vect3D triangle_tangent(Vertex vert1, Vertex vert2, Vertex vert3) {
    Vect3D pos1 = vert1.position, pos2 = vert2.position, pos3 = vert3.position;
    Vect2D uv1 = vert1.uvs, uv2 = vert2.uvs, uv3 = vert3.uvs;
    float x1 = pos2.x - pos1.x, x2 = pos3.x - pos1.x;
    float y1 = pos2.y - pos1.y, y2 = pos3.y - pos1.y;
    float z1 = pos2.z - pos1.z, z2 = pos3.z - pos1.z;
    float s1 = uv2.x - uv1.x, s2 = uv3.x - uv1.x;
    float t1 = uv2.y - uv1.y, t2 = uv3.y - uv1.y;
    float r = 1.0f / (s1 * t2 - s2 * t1);
    Vect3D tdir = vect3D_new((s1 * x2 - s2 * x1) * r,
                           (s1 * y2 - s2 * y1) * r,
                           (s1 * z2 - s2 * z1) * r);
    return vect3D_normalize(tdir);
}

Vect3D triangle_binormal(Vertex vert1, Vertex vert2, Vertex vert3) {
    Vect3D pos1 = vert1.position, pos2 = vert2.position, pos3 = vert3.position;
    Vect2D uv1 = vert1.uvs, uv2 = vert2.uvs, uv3 = vert3.uvs;
    float x1 = pos2.x - pos1.x, x2 = pos3.x - pos1.x;
    float y1 = pos2.y - pos1.y, y2 = pos3.y - pos1.y;
    float z1 = pos2.z - pos1.z, z2 = pos3.z - pos1.z;
    float s1 = uv2.x - uv1.x, s2 = uv3.x - uv1.x;
    float t1 = uv2.y - uv1.y, t2 = uv3.y - uv1.y;
    float r = 1.0f / (s1 * t2 - s2 * t1);
    Vect3D sdir = vect3D_new((t2 * x1 - t1 * x2) * r,
                           (t2 * y1 - t1 * y2) * r,
                           (t2 * z1 - t1 * z2) * r);
    return vect3D_normalize(sdir);
}

Vect3D triangle_normal(Vertex vert1, Vertex vert2, Vertex vert3) {
    Vect3D edge1 = vect3D_sub(vert2.position, vert1.position);
    Vect3D edge2 = vect3D_sub(vert3.position, vert1.position);
    Vect3D normal = vect3D_cross(edge1, edge2);
    return vect3D_normalize(normal);
}

Vect3D triangle_random_position(Vertex vert1, Vertex vert2, Vertex vert3) {
    float r1 = (float)rand() / (float)RAND_MAX;
    float r2 = (float)rand() / (float)RAND_MAX;
    if(r1 + r2 >= 1) {
        r1 = 1 - r1;
        r2 = 1 - r2;
    }
    Vect3D ab = vect3D_sub(vert1.position, vert2.position);
    Vect3D ac = vect3D_sub(vert1.position, vert3.position);
    Vect3D a = vert1.position;
    a = vect3D_sub(a, vect3D_mult(ab , r1));
    a = vect3D_sub(a, vect3D_mult(ac , r2));
    return a;
}

float triangle_area(Vertex vert1, Vertex vert2, Vertex vert3) {
    Vect3D ab = vect3D_sub(vert1.position, vert2.position);
    Vect3D ac = vect3D_sub(vert1.position, vert3.position);
    return 0.5 * vect3D_length(vect3D_cross(ab, ac));
}

float triangle_difference_u(Vertex vert1, Vertex vert2, Vertex vert3) {
    float max = vert1.uvs.x;
    max = vert2.uvs.x > max ? vert2.uvs.x : max;
    max = vert3.uvs.x > max ? vert3.uvs.x : max;
    float min = vert1.uvs.x;
    min = vert2.uvs.x < min ? vert2.uvs.x : min;
    min = vert3.uvs.x < min ? vert3.uvs.x : min;
    return max - min;
}

float triangle_difference_v(Vertex vert1, Vertex vert2, Vertex vert3) {
    float max = vert1.uvs.y;
    max = vert2.uvs.x > max ? vert2.uvs.y : max;
    max = vert3.uvs.x > max ? vert3.uvs.y : max;
    float min = vert1.uvs.y;
    min = vert2.uvs.y < min ? vert2.uvs.y : min;
    min = vert3.uvs.y < min ? vert3.uvs.y : min;
    return max - min;
}

Vertex triangle_random_position_interpolation(Vertex vert1, Vertex vert2, Vertex vert3) {
    float r1 = (float)rand() / (float)RAND_MAX;
    float r2 = (float)rand() / (float)RAND_MAX;
    if(r1 + r2 >= 1) {
      r1 = 1 - r1;
      r2 = 1 - r2;
    }
    Vertex vert;
    Vect3D v_pos, v_norm, v_tang, v_binorm;
    Vect4D v_col;
    Vect2D v_uv;
    v_pos = vert1.position;
    v_pos = vect3D_sub(v_pos, vect3D_mult(vect3D_sub(vert1.position, vert2.position), r1));
    v_pos = vect3D_sub(v_pos, vect3D_mult(vect3D_sub(vert1.position, vert3.position), r2));
    v_norm = vert1.normal;
    v_norm = vect3D_sub(v_norm, vect3D_mult(vect3D_sub(vert1.normal, vert2.normal), r1) );
    v_norm = vect3D_sub(v_norm, vect3D_mult(vect3D_sub(vert1.normal, vert3.normal), r2) );
    v_tang = vert1.tangent;
    v_tang = vect3D_sub(v_tang, vect3D_mult(vect3D_sub(vert1.tangent, vert2.tangent), r1));
    v_tang = vect3D_sub(v_tang, vect3D_mult(vect3D_sub(vert1.tangent, vert3.tangent), r2));
    v_binorm = vert1.binormal;
    v_binorm = vect3D_sub(v_binorm, vect3D_mult(vect3D_sub(vert1.binormal, vert2.binormal), r1));
    v_binorm = vect3D_sub(v_binorm, vect3D_mult(vect3D_sub(vert1.binormal, vert3.binormal), r2));
    v_col = vert1.color;
    v_col = vect4D_sub(v_col, vect4D_mult(vect4D_sub(vert1.color, vert2.color), r1));
    v_col = vect4D_sub(v_col, vect4D_mult(vect4D_sub(vert1.color, vert3.color), r2));
    v_uv = vert1.uvs;
    v_uv = vect2D_sub(v_uv, vect2D_mult(vect2D_sub(vert1.uvs, vert2.uvs), r1));
    v_uv = vect2D_sub(v_uv, vect2D_mult(vect2D_sub(vert1.uvs, vert3.uvs), r2));
    vert.position = v_pos;
    vert.normal = v_norm;
    vert.tangent = v_tang;
    vert.binormal = v_binorm;
    vert.color = v_col;
    vert.uvs = v_uv;
    return vert;
}

/* Tweeners */

float tween_approach(float curr, float target, float timestep, float steepness) {
    return lerp(curr, target, saturate(steepness * timestep));
}

float tween_linear(float curr, float target, float timestep, float max) {
    return curr + clamp(target - curr, -max * timestep, max * timestep);
}

Vect3D vect3D_tween_approach(Vect3D curr, Vect3D target, float timestep, float steepness); {
    return vect3D_lerp(curr, target, saturate(steepness * timestep));
}

Vect3D vect3D_tween_linear(Vect3D curr, Vect3D target, float timestep, float max) {
    float  dist = vect3D_dist(curr, target);
    Vect3D dirr = vect3D_normalize(vec3_sub(target, curr));
    return vect3D_add(curr, vect3D_mult(dirr, min(dist, max * timestep)));
}
