#include <math.h>
#include <dbg.h>
#include "distances.h"

float seuppSqrt(const float* point1, const float* point2, const int pointWidth){
	float result = 0;
	for(int i=0;i<pointWidth;++i){
		result+=(point1[i]-point2[i])*(point1[i]-point2[i]);
	}
	return sqrtf(result);
}

float seuppSqr(const float* point1, const float* point2, const int pointWidth){
	float result = 0;
	for(int i=0;i<pointWidth;++i){
		result+=(point1[i]-point2[i])*(point1[i]-point2[i]);
	}
	return sqrtf(result);
}

float smnpp2(const float* point1, const float* point2, const int pointWidth){
	float result = 0;
	for(int i=0;i<pointWidth;++i){
		result+=fabs(point1[i]-point2[i]);
	}
	return result;
}

// s(ingle) - float, ge - generic, v - vector x vector
void sgev(const float* data, float* const distances, const int n, const int pointWidth, Pp_distance pp_distance){
	float point[pointWidth] __attribute__((aligned(64)));
	for(int i=0;i<n; ++i){
    for(int j=0;j<pointWidth;++j){
      point[j]=data[i*pointWidth+j];
    }
	
		for(int j=0;j<n;++j){
			distances[i*n+j] = pp_distance(point, data+j*pointWidth, pointWidth);
		}
	}
}