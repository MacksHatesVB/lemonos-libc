#include <3d.h>
#include <graphics.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

void transform_triangle(tri_3d_t * triangle, vect_3d_t * thing) {
	triangle->a.x += thing->x;
	triangle->b.x += thing->x;
	triangle->c.x += thing->x;

	triangle->a.y += thing->y;
	triangle->b.y += thing->y;
	triangle->c.y += thing->y;

	triangle->a.z += thing->z;
	triangle->b.z += thing->z;
	triangle->c.z += thing->z;
}

void transform_2d_triangle(tri_2d_t * triangle, vect_2d_t * thing) {
	triangle->a.x += thing->x;
	triangle->b.x += thing->x;
	triangle->c.x += thing->x;

	triangle->a.y += thing->y;
	triangle->b.y += thing->y;
	triangle->c.y += thing->y;
}

void transform_mesh(mesh_t * mesh, vect_3d_t * vector) {
	int count = mesh->tri_count;
	mesh->origin.x += vector->x;
	mesh->origin.y += vector->y;
	mesh->origin.z += vector->z;
	for (int i = 0; i < count; i++) {
		tri_3d_t * tri = mesh->triangles[i];
		transform_triangle(tri, vector);
	}
}

void create_rotmat(mat3x3_t * mat, float deg, int axis) {
	float θ = deg * 0.0174;
	switch (axis) {
		case X_AXIS:
			mat->v[0][0] = 1; mat->v[0][1] = 0;		mat->v[0][2] = 0;
			mat->v[1][0] = 0; mat->v[1][1] = fcos(θ);	mat->v[1][2] = -fsin(θ);
			mat->v[2][0] = 0; mat->v[2][1] = fsin(θ);	mat->v[2][2] = fcos(θ);
			return;
		case Y_AXIS:
			mat->v[0][0] = fcos(θ);	 mat->v[0][1] = 0; mat->v[0][2] = fsin(θ);
			mat->v[1][0] = 0;	 mat->v[1][1] = 1; mat->v[1][2] = 0;
			mat->v[2][0] = -fsin(θ); mat->v[2][1] = 0; mat->v[2][2] = fcos(θ);
			return;
		case Z_AXIS:
			mat->v[0][0] = fcos(θ); mat->v[0][1] = -fsin(θ); mat->v[0][2] = 0;
			mat->v[1][0] = fsin(θ); mat->v[1][1] = fcos(θ);	 mat->v[1][2] = 0;
			mat->v[2][0] = 0;	mat->v[2][1] = 0;	 mat->v[2][2] = 1;
			return;
	}
}

void rot_vert(mat3x3_t * rotmat, mat3x1_t * mat, int axis) {
	mat3x3_mul_max3x1(rotmat, mat);
}

void rot_verts(mat3x1_t * a, mat3x1_t * b, mat3x1_t * c, float θ, int axis) {
	if (θ == 0) {
		return;
	}
	mat3x3_t rotmat;
	create_rotmat(&rotmat, θ, axis);
	rot_vert(&rotmat, a, axis);
	rot_vert(&rotmat, b, axis);
	rot_vert(&rotmat, c, axis);

}

void rot_triangle(tri_3d_t * tri, float xθ, float yθ, float zθ) {
	mat3x1_t * a = (void *) &tri->a;
	mat3x1_t * b = (void *) &tri->b;
	mat3x1_t * c = (void *) &tri->c;
	rot_verts(a, b, c, xθ, X_AXIS);
	rot_verts(a, b, c, yθ, Y_AXIS);
	rot_verts(a, b, c, zθ, Z_AXIS);
}

void rot_mesh(mesh_t * mesh, float xθ, float yθ, float zθ) {
	int count = mesh->tri_count;
	vect_3d_t origin = mesh->origin;
	vect_3d_t copy = {origin.x, origin.y, origin.z};
	vect_3d_t flipped = {-origin.x, -origin.y, -origin.z};
	transform_mesh(mesh, &flipped);
	for (int i = 0; i < count; i++) {
		tri_3d_t * tri = mesh->triangles[i];
		rot_triangle(tri, xθ, yθ, zθ);
	}
	transform_mesh(mesh, &copy);
}

float edge(vect_2d_t * a, vect_2d_t * b, vect_2d_t * c) {
	return ((b->x - a->x) *
		(c->y - a->y)) -
		((b->y - a->y) *
		(c->x - a->x));
}

void project_point(vect_3d_t * in, vect_2d_t * out, camera_t * camera) {
	out->x = in->x * (camera->fov / in->z);
	out->y = in->y * (camera->fov / in->z);
}

void project_triangle(tri_3d_t * in, tri_2d_t * out, camera_t * camera) {
	project_point(&in->a, &out->a, camera);
	project_point(&in->b, &out->b, camera);
	project_point(&in->c, &out->c, camera);
}

void blit(uint32_t * fb, int width, int height, int x, int y, uint32_t colour) {
	if (x < 0 || y < 0 || x >= width || y >= height) {
		return;
	}
	fb[(y * width) + x] = colour;
}

void rasterise_triangle(tri_3d_t * triangle, rect_2d_t * rect, camera_t * camera) {
	vect_2d_t p = {0, 0};
	tri_2d_t triangle_2d;
	vect_2d_t origin = {(float) (rect->size.width / 2), (float) (rect->size.height / 2)};

	project_triangle(triangle, &triangle_2d, camera);
	transform_2d_triangle(&triangle_2d, &origin);

	float minx = min3(triangle_2d.a.x, triangle_2d.b.x, triangle_2d.c.x);
	float miny = min3(triangle_2d.a.y, triangle_2d.b.y, triangle_2d.c.y);
	float maxx = max3(triangle_2d.a.x, triangle_2d.b.x, triangle_2d.c.x);
	float maxy = max3(triangle_2d.a.y, triangle_2d.b.y, triangle_2d.c.y);

	minx = max2(minx, 0);
	miny = max2(miny, 0);

	maxx = min2(maxx, rect->size.width);
	maxy = min2(maxy, rect->size.height);

	for (p.y = miny; p.y < maxy; p.y++) {
		for (p.x = minx; p.x < maxx; p.x++) {
			float abp = edge(&triangle_2d.a, &triangle_2d.b, &p);
			float bcp = edge(&triangle_2d.b, &triangle_2d.c, &p);
			float cap = edge(&triangle_2d.c, &triangle_2d.a, &p);
			if (abp < 0 || bcp < 0 || cap < 0) {
				continue;
			}
			blit(rect->fb, rect->size.width, rect->size.height, p.x, p.y, triangle->colour);
		}
	}
}

void rasterise_mesh(mesh_t * mesh, rect_2d_t * rect, camera_t * camera) {
	int count = mesh->tri_count;
	for (int i = 0; i < count; i++) {
		tri_3d_t * tri = mesh->triangles[i];
		rasterise_triangle(tri, rect, camera);
	}
}
