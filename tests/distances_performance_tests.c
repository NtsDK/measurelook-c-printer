/*#include <stdio.h>
#include <omp.h>
#include <math.h>
//#include <mkl_vsl.h>
#include <float.h>
#include "macro.h"
#include "csv.h"
#include "pam.h"
#include "clusteringTest.h"
#include "testUtils.h"
#include "euclidDistances.h"*/
#include "distances.h"
#include "distancesPerformanceTest.h"
#include <stdlib.h>
#include "minunit.h"

#include "lcthw/mlBuilder.h"

#include <string.h>

char *dist_test(DistTestOpts opts, Pp_distance pp_distance, char *algName, char *saveFilePath);

DistTestOpts getOpts(){
  DistTestOpts opts;
  opts.begin = 1024;
  opts.step = 1024;
  //opts.n = 1024*10;
  opts.n = 1024*5;
  //opts.pointWidth = 193;
  opts.pointWidth = 3;
  opts.nTrials = 5;
  return opts;
}

#define DIST_TEST(name, type, opts, pp_distance, algName) char *(name##_##type)(){ \
  return dist_test(opts(), (pp_distance), (algName), "testRes/distances/" algName ".json"); \
}

DIST_TEST(euSqrt, performance, getOpts, seuppSqrt, "euclidSqrt");
DIST_TEST(euSqr, performance, getOpts, seuppSqr, "euclidSqr");
DIST_TEST(smnpp2, performance, getOpts, smnpp2, "manhattan");


char *dist_test(DistTestOpts opts, Pp_distance pp_distance, char *algName, char *saveFilePath){

  float* data = (float*) malloc(sizeof(float)*opts.n*opts.pointWidth);
  mu_assert(data != NULL, "Failed to allocate array for data.");

  double seed = 123.45;
  data[0] = seed;
  for(int i=1;i<opts.n*opts.pointWidth;++i){
    data[i] = fmod(data[i-1] * 11.56, 337);
  }
  
  debug("Initialization...");fflush(0); // stdout

  bstring res;
  
  res = distancesPerformanceTest(opts, data, pp_distance, algName, "some dataset name");
  log_info("%s", bdata(res));
  
  FILE *fp = fopen(saveFilePath, "wb");
  mu_assert(fp != NULL, "Failed to open file for writing.");
  if (fp != NULL)
  {
      fputs(bdata(res), fp);
      fclose(fp);
  }
  
  bdestroy(res);
  fflush(0);
  free(data);
  return NULL;
}


char *all_tests()
{
  mu_suite_start();
  mu_run_test(euSqrt_performance);
  mu_run_test(euSqr_performance);
  mu_run_test(smnpp2_performance);
  return NULL;
}

RUN_TESTS(all_tests);