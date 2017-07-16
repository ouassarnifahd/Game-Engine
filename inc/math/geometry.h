#ifndef _GEOMETRY_
#define _GEOMETRY_

#include <stdlib.h>
#include "Matrix4x4.h"

/* Plane */

typedef struct {
    Vect3D direction;
    Vect3D position;
} Plane;

Plane plane_new(Vect3D position, Vect3D direction);
Plane plane_transform(Plane plane, Mat4x4 world, Mat3x3 world_normal);
Plane plane_transform_space(Plane plane, Mat3x3 space, Mat3x3 space_normal);
float plane_distance(Plane plane, Vect3D point);

bool point_inside_plane(Vect3D point, Plane plane);
bool point_outside_plane(Vect3D point, Plane plane);
bool point_intersects_plane(Vect3D point, Plane plane);

bool point_swept_inside_plane(Vect3D point, Vect3D vect, Plane plane);
bool point_swept_outside_plane(Vect3D point, Vect3D vect, Plane plane);
bool point_swept_intersects_plane(Vect3D point, Vect3D vect, Plane plane);

Vect3D plane_closest(Plane plane, Vect3D vect);
Vect3D plane_project(Plane plane, Vect3D vect);

/* Box */

typedef struct {
    Plane top;   Plane bottom;
    Plane left;  Plane right;
    Plane front; Plane back;
} Box;

Box box_new(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);
Box box_sphere(Vect3D center, float radius);
Box box_merge(Box box1, Box box2);
Box box_transform(Box b1, Mat4x4 world, Mat3x3 world_normal);
Box box_invert(Box box);
Box box_invert_depth(Box box);
Box box_invert_width(Box box);
Box box_invert_height(Box box);

bool point_inside_box(Vect3D point, Box box);
bool point_outside_box(Vect3D point, Box box);
bool point_intersects_box(Vect3D point, Box box);

/* Frustum */

typedef struct {
	Vect3D ntr, ntl, nbr, nbl;
    Vect3D ftr, ftl, fbr, fbl;
} Frustum;

Frustum frustum_new(Vect3D ntr, Vect3D ntl, Vect3D nbr, Vect3D nbl, Vect3D ftr, Vect3D ftl, Vect3D fbr, Vect3D fbl);
Frustum frustum_new_clipbox();
Frustum frustum_new_camera(Mat4x4 view, Mat4x4 proj);
Frustum frustum_slice(Frustum frust, float start, float end);
Frustum frustum_transform(Frustum frust, Mat4x4 mat);
Frustum frustum_translate(Frustum frust, Vect3D vect);

Vect3D frustum_center(Frustum frust);
Vect3D frustum_maximums(Frustum frust);
Vect3D frustum_minimums(Frustum frust);

box frustum_box(Frustum frust);

bool frustum_outside_box(Frustum frust, Box box);

/* Sphere */

typedef struct {
    Vect3D center;
    float radius;
} Sphere;

Sphere sphere_unit();
Sphere sphere_point();
Sphere sphere_new(Vect3D center, float radius);
Sphere sphere_merge(Sphere sphere1, Sphere sphere2);
Sphere sphere_merge_many(sphere* spheres, int count);
Sphere sphere_transform(Sphere sphere, Mat4x4 world);
Sphere sphere_translate(Sphere sphere, Vect3D x);
Sphere sphere_scale(Sphere sphere, float x);
Sphere sphere_transform_space(Sphere sphere, Mat3x3 space);

Sphere sphere_of_box(Box box);
Sphere sphere_of_frustum(Frustum frust);

bool sphere_inside_box(Sphere sphere, Box box);
bool sphere_outside_box(Sphere sphere, Box box);
bool sphere_intersects_box(Sphere sphere, Box box);

bool sphere_inside_frustum(Sphere sphere, Frustum frust);
bool sphere_outside_frustum(Sphere sphere, Frustum frust);
bool sphere_intersects_frustum(Sphere sphere, Frustum frust);

bool sphere_outside_sphere(Sphere sphere1, Sphere sphere2);
bool sphere_inside_sphere(Sphere sphere1, Sphere sphere2);
bool sphere_intersects_sphere(Sphere sphere1, Sphere sphere2);

bool point_inside_sphere(Sphere sphere, Vect3D point);
bool point_outside_sphere(Sphere sphere, Vect3D point);
bool point_intersects_sphere(Sphere sphere, Vect3D point);

bool line_inside_sphere(Sphere sphere, Vect3D start, Vect3D end);
bool line_outside_sphere(Sphere sphere, Vect3D start, Vect3D end);
bool line_intersects_sphere(Sphere sphere, Vect3D start, Vect3D end);

bool sphere_inside_plane(Sphere sphere, Plane plane);
bool sphere_outside_plane(Sphere sphere, Plane plane);
bool sphere_intersects_plane(Sphere sphere, Plane plane);

bool point_swept_inside_sphere(Sphere sphere, Vect3D vect, Vect3D point);
bool point_swept_outside_sphere(Sphere sphere, Vect3D vect, Vect3D point);
bool point_swept_intersects_sphere(Sphere sphere, Vect3D vect, Vect3D point);

bool sphere_swept_inside_plane(Sphere sphere, Vect3D vect, Plane plane);
bool sphere_swept_outside_plane(Sphere sphere, Vect3D vect, Plane plane);
bool sphere_swept_intersects_plane(Sphere sphere, Vect3D vect, Plane plane);

bool sphere_swept_outside_sphere(Sphere sphere1, Vect3D vect, Sphere sphere2);
bool sphere_swept_inside_sphere(Sphere sphere1, Vect3D vect, Sphere sphere2);
bool sphere_swept_intersects_sphere(Sphere sphere1, Vect3D vect, Sphere sphere2);

bool point_inside_triangle(Vect3D plane, Vect3D vect0, Vect3D vect1, Vect3D vect2);
bool sphere_intersects_face(Sphere sphere, Vect3D vect0, Vect3D vect1, Vect3D vect2, Vect3D norm);

/* Ellipsoid */

typedef struct {
    Vect3D center;
    Vect3D radiuses;
} Ellipsoid;

Ellipsoid ellipsoid_new(Vect3D center, Vect3D radiuses);
Ellipsoid ellipsoid_transform(Ellipsoid ellipse, Mat4x4 mat);
Ellipsoid ellipsoid_of_sphere(Sphere sphere);

Mat3x3 ellipsoid_space(Ellipsoid ellipse);
Mat3x3 ellipsoid_inv_space(Ellipsoid ellipse);

/* Capsule */

typedef struct {
    Vect3D start;
    Vect3D end;
    float radius;
} Capsule;

Capsule capsule_new(Vect3D start, Vect3D end, float radius);
Capsule capsule_transform(Capsule capsule, Mat4x4 mat);

bool capsule_inside_plane(Capsule capsule, Plane plane);
bool capsule_outside_plane(Capsule capsule, Plane plane);
bool capsule_intersects_plane(Capsule capsule, Plane plane);

/* Vertex */

typedef struct {
  Vect3D position;
  Vect3D normal;
  Vect3D tangent;
  Vect3D binormal;
  Vect4D color;
  Vect2D uvs;
} Vertex;

Vertex vertex_new();
bool vertex_equal(Vertex vert1, Vertex vert2);
void vertex_print(Vertex vert);

/* Mesh */

typedef struct {
  int num_verts;
  int num_triangles;
  Vertex* verticies;
  uint32_t* triangles;
} Mesh;

Mesh* mesh_new();
void mesh_delete(Mesh* mesh);

void mesh_generate_normals(Mesh* mesh);
void mesh_generate_tangents(Mesh* mesh);
void mesh_generate_orthagonal_tangents(Mesh* mesh);
void mesh_generate_texcoords_cylinder(Mesh* mesh);

void mesh_print(Mesh* mesh);
float mesh_surface_area(Mesh* mesh);

void mesh_transform(Mesh* mesh, Mat4x4 transform);
void mesh_translate(Mesh* mesh, Vect3D translation);
void mesh_scale(Mesh* mesh, float scale);

Sphere mesh_bounding_sphere(Mesh* mesh);

/* Model */

typedef struct {
  int num_meshes;
  Mesh** meshes;
} Model;

Model* model_new();
void model_delete(Model* model);

void model_generate_normals(Model* model);
void model_generate_tangents(Model* model);
void model_generate_orthagonal_tangents(Model* model);
void model_generate_texcoords_cylinder(Model* model);

void model_print(Model* model);
float model_surface_area(Model* model);

void model_transform(Model* model, Mat4x4 transform);
void model_translate(Model* model, Vect3D translation);
void model_scale(Model* model, float scale);

/* Triangle */

Vect3D triangle_tangent(Vertex vert1, Vertex vert2, Vertex vert3);
Vect3D triangle_binormal(Vertex vert1, Vertex vert2, Vertex vert3);
Vect3D triangle_normal(Vertex vert1, Vertex vert2, Vertex vert3);
Vect3D triangle_random_position(Vertex vert1, Vertex vert2, Vertex vert3);
float triangle_area(Vertex vert1, Vertex vert2, Vertex vert3);

float triangle_difference_u(Vertex vert1, Vertex vert2, Vertex vert3);
float triangle_difference_v(Vertex vert1, Vertex vert2, Vertex vert3);

Vertex triangle_random_position_interpolation(Vertex vert1, Vertex vert2, Vertex vert3);

/* Tweeners */

float tween_approach(float curr, float target, float timestep, float steepness);
float tween_linear(float curr, float target, float timestep, float max);

Vect3D vect3D_tween_approach(Vect3D curr, Vect3D target, float timestep, float steepness);
Vect3D vect3D_tween_linear(Vect3D curr, Vect3D target, float timestep, float max);

#endif /* end of include guard: _GEOMETRY_ */
