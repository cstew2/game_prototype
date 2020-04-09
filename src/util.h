#ifndef __UTIL_H__
#define __UTIL_H__

#include <stddef.h>
#include <stdbool.h>

extern const float PI;
extern const float PI_2;
extern const float PI_4;

typedef struct {
	float x;
	float y;
}point;

float minf(float a, float b);
float maxf(float a, float b);
int mini(int a, int b);
int maxi(int a, int b);
	
float min_arrayf(float *array, int length);
float min_arrayi(int *array, int length);
float max_arrayf(float *array, int length);
float max_arrayi(int *array, int length);

void sortf(float *array, int length);
void sorti(int *array, int length);

bool point_in_poly(int x, int y, int loc_x, int loc_y, point *vertices, size_t vertex_count);
point circle_poly_collision(int x1, int y1, int radius,
			    int x2, int y2, point *vertices, size_t vertex_count);
point circle_collision(int x1, int y1, int r1, int x2, int y2, int r2);
point *poly_collision(int x1, int y1, point *v1, size_t v1_count,
		      int x2, int y2, point *v2, size_t v2_count);

#endif
