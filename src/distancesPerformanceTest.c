//#include "testUtils.h"
#include "omp.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
//#include "math.h"
//#include "float.h"
//#include "euclidDistances.h"
#include <dbg.h>
#include "mlExtras.h"

#include "distancesPerformanceTest.h"

//#include <string.h>

#include "lcthw/mlBuilder.h"

bstring distancesPerformanceTest(const DistTestOpts opts, 
							float* data, 
							Pp_distance pp_distance, 
							const char* algName,
							const char* dataset)
{
	debug("Implementation name: %s", algName);
	
	MLBuilder *mlBuilder = mlb_create("0.2.0");
	
	mlb_addMetaString( mlBuilder, "Algorithm implementation name", algName );
	mlb_addMetaString( mlBuilder, "dataset",  dataset );
  
  printEnvData(mlBuilder);
	
	mlb_addMetaValue( mlBuilder, "pass number (nTrials)", i_bformat( opts.nTrials ) );
	mlb_addMetaValue( mlBuilder, "pointWidth", i_bformat( opts.pointWidth ) );
	mlb_addMetaValue( mlBuilder, "max", i_bformat( opts.n ) );
	mlb_addMetaValue( mlBuilder, "min", i_bformat( opts.begin ) );
	mlb_addMetaValue( mlBuilder, "step", i_bformat( opts.step ) );
	
	distancesPerformanceTest_core(opts, data, pp_distance, mlBuilder);
	
	debug("Printing changedParams");fflush(0);
	// changedParams
	mlb_addChangedParam(mlBuilder, "arraySize", "natural number");

	debug("Printing measuredParams");fflush(0);
	// measuredParams
	mlb_addDirectMeasuredParam( mlBuilder, "distancesCalc_duration", "seconds" );
	
	debug("Printing fillIndirectParams");fflush(0);
	//mlb_addIndirectMeasuredParam(mlBuilder, "indirectDemo_duration", "seconds", "[\"distancesCalc_duration\", \"distancesCalc_duration\"]");

	bstring mlData = mlb_build(mlBuilder);
	mlb_destroy(mlBuilder);
	return mlData;
}

void distancesPerformanceTest_core(const DistTestOpts opts, 
							float* data, 
							Pp_distance pp_distance, 
							MLBuilder *mlBuilder){
	
	const size_t n = opts.n;
	const int nTrials = opts.nTrials;
	const size_t pointWidth = opts.pointWidth;
	
  float *distanceMatrix;
  //distanceMatrix = (float*) _mm_malloc(sizeof(float) * n * n, 64);
  distanceMatrix = (float*) malloc(sizeof(float) * n * n);
	assert(distanceMatrix != NULL);

	char	measureKey[8192];
	
	// data size cycle
	for(int i=opts.begin; i < n+1; i+=opts.step){
		debug("data size %d", i);
		
    for(int j=0; j < i*i; j++){
      distanceMatrix[j]=0;
    }
    
		// pass cycle
		for(int t=0;t<nTrials;++t){
			log_info("pass %d", t);
			snprintf(measureKey, sizeof(measureKey), "%d_%d", i, t);
			
			MLMeasure *mlMeasure = mlm_create(measureKey, t);
			mlm_addEntry(mlMeasure, "arraySize", i_bformat(i));
			
			debug("Starting pass %d...", t);fflush(0);
			
			double t1 = omp_get_wtime();
      sgev(data, distanceMatrix, i, pointWidth, pp_distance);
			double t2 = omp_get_wtime();

			mlm_addEntry( mlMeasure, "distancesCalc_duration", d_bformat(t2-t1) );

			mlb_addMeasure(mlBuilder, mlMeasure);
			mlm_destroy(mlMeasure);
		}
		debug("Trials finished ");fflush(0);
		debug("");fflush(0);
	}
}