#include <limits.h>
#include <float.h>

#include "util.h"

const float PI = 3.14159265358979323846;
const float M_PI_2 = 1.57079632679489661923;
const float M_PI_4 = 0.78539816339744830962;

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
