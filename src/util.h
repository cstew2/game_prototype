#ifndef __UTIL_H__
#define __UTIL_H__

extern const float PI;
extern const float M_PI_2;
extern const float M_PI_4;

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

#endif
