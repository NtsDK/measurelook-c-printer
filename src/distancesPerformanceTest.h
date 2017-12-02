#ifndef _DISTANCES_PERFORMANCE_TEST_H_
#define _DISTANCES_PERFORMANCE_TEST_H_

#include "distances.h"
#include "stddef.h"
#include "lcthw/mlBuilder.h"

typedef struct DistTestOpts DistTestOpts;

struct DistTestOpts {
  size_t begin;
  size_t n;
  int step; 
  int nTrials;
  size_t pointWidth;
};

bstring distancesPerformanceTest(const DistTestOpts opts, 
							float* data, 
							Pp_distance pp_distance,
							const char* algName,
							const char* dataset);
              
void distancesPerformanceTest_core(const DistTestOpts opts, 
							float* data, 
							Pp_distance pp_distance, 
							MLBuilder *mlBuilder);

#endif