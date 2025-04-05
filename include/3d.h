#pragma once

#include <math.h>
#include <graphics.h>

typedef struct {
        vect_3d_t position;
        float fov;
} camera_t;

typedef struct {
        tri_3d_t tri;
        uint32_t colour;
} triangle_t;

typedef struct {
        vect_3d_t origin;
        tri_3d_t ** triangles;
        int tri_count;
} mesh_t;

enum {
        X_AXIS,
        Y_AXIS,
        Z_AXIS,
};

void transform_triangle(tri_3d_t * triangle, vect_3d_t * thing);
void transform_mesh(mesh_t * mesh, vect_3d_t * vector);
void rasterise_triangle(tri_3d_t * triangle, rect_2d_t * rect, camera_t * camera);
void rasterise_mesh(mesh_t * mesh, rect_2d_t * rect, camera_t * camera);
void rot_triangle(tri_3d_t * tri, float xθ, float yθ, float zθ);
void rot_mesh(mesh_t * mesh, float xθ, float yθ, float zθ);
