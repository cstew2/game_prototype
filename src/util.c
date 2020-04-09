#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#include "util.h"

const float PI = 3.14159265358979323846;
const float PI_2 = 1.57079632679489661923;
const float PI_4 = 0.78539816339744830962;

float minf(float a, float b)
{
	return (a < b ? a : b);
}
	
float maxf(float a, float b)
{
	return (a > b ? a : b);
}

int mini(int a, int b)
{
	return (a < b ? a : b);
}
	
int maxi(int a, int b)
{
	return (a > b ? a : b);
}

float min_arrayf(float *array, int length)
{
	float min = FLT_MAX;

	for(int i=0; i < length; i++) {
		if(array[i] < min) {
			min = array[i];
		}
	}
	return min;
}

float min_arrayi(int *array, int length)
{
	int min = INT_MAX;

	for(int i=0; i < length; i++) {
		if(array[i] < min) {
			min = array[i];
		}
	}
	return min;
}

float max_arrayf(float *array, int length)
{
	float max = FLT_MIN;

	for(int i=0; i < length; i++) {
		if(array[i] > max) {
			max = array[i];
		}
	}
	return max;
}

float max_arrayi(int *array, int length)
{
	int max = INT_MIN;

	for(int i=0; i < length; i++) {
		if(array[i] > max) {
			max = array[i];
		}
	}
	return max;
}

void sortf(float *array, int length)
{
	for(int i=0; i < length; i++) {
		int min = i;
		for(int j=0; j < length; j++) {
			if(array[j] < array[min]) {
				min = j;
			}
		}
		if(min != i) {
			float t = array[min];
			array[i] = t;
			array[min] = array[i];
		}
	}
}

void sorti(int *array, int length)
{
	for(int i=0; i < length; i++) {
		int min = i;
		for(int j=0; j < length; j++) {
			if(array[j] < array[min]) {
				min = j;
			}
		}
		if(min != i) {
			int t = array[min];
			array[i] = t;
			array[min] = array[i];
		}
	}
}

bool point_in_poly(int x, int y, int loc_x, int loc_y, point *vertices, size_t vertex_count)
{
	bool inside = false;
	int j=vertex_count-1;
	
	for(int i=0; i < vertex_count; i++) {
		int xi = loc_x + vertices[i].x;
		int yi = loc_y + vertices[i].y;
		
		int xj = loc_x + vertices[j].x;
		int yj = loc_y + vertices[j].y;
		
		bool a = (yi > y) != (yj > y);
		
		int grad = xi + (xj - xi) * (y - yi) / (yj - yi);
		if(a && x < grad) {
			inside = !inside;
		}

		j=i;
	}
	return inside;
}

point circle_poly_collision(int x1, int y1, int radius,
			    int x2, int y2, point *vertices, size_t vertex_count)
{
	if(point_in_poly(radius + x1, y1, x2, y2, vertices, vertex_count)) {
		return (point){radius + x1, y1};
	}
	if(point_in_poly(x1, radius + y1, x2, y2, vertices, vertex_count)) {
		return (point){x1, radius + y1};
	}
	if(point_in_poly(radius - x1, y1, x2, y2, vertices, vertex_count)) {
		return (point){radius - x1, y1};
	}
	if(point_in_poly(x1, radius - y1, x2, y2, vertices, vertex_count)){
		return (point){x1, radius - y1};
	}
	if(point_in_poly(radius + x1, radius + y1, x2, y2, vertices, vertex_count)) {
		return (point){radius + x1, radius + y1};
	}
	if(point_in_poly(radius - x1, radius + y1, x2, y2, vertices, vertex_count)) {
		return (point){radius - x1, radius + y1};						
	}
	if(point_in_poly(radius + x1, radius - y1, x2, y2, vertices, vertex_count)) {
		return (point){radius + x1, radius - y1};
	}
	if(point_in_poly(radius - x1, radius - y1, x2, y2, vertices, vertex_count)) {
		return (point){radius - x1, radius - y1};
	}
	return (point){-1, -1};
}

point circle_collision(int x1, int y1, int r1, int x2, int y2, int r2)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	int distance = sqrt(dx * dx + dy * dy);

	if(distance < r1 + r2) {
		return (point){dx, dy};
	}
	return (point){-1, -1};
}

point *poly_collision(int x1, int y1, point *v1, size_t v1_count,
		      int x2, int y2, point *v2, size_t v2_count)
{
        point *p = calloc(2, sizeof(point));

	return p;
}
