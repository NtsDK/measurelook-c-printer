#ifndef _DISTANCES_H_
#define _DISTANCES_H_

typedef float (*Pp_distance)(const float* point1, const float* point2, const int pointWidth);

float seuppSqrt(const float* point1, const float* point2, const int pointWidth);

float seuppSqr(const float* point1, const float* point2, const int pointWidth);

float smnpp2(const float* point1, const float* point2, const int pointWidth);

// s(ingle) - float, ge - generic, v - vector x vector
void sgev(const float* data, float* const distances, const int n, const int pointWidth, Pp_distance pp_distance);

#endif