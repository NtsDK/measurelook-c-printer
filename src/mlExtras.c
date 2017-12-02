#include "mlExtras.h"
//#include "macro.h"


void printEnvData(MLBuilder *mlBuilder){
  
  mlb_addMetaString( mlBuilder, "COMPILE_VEC_ENABLED",  VEC_ENABLED ? "true" : "false" );
  
  
  //mlb_addMetaString( mlBuilder, "SCAL_THR_ARRAY", STRINGIFY(SCAL_THR_ARRAY) );
  #ifdef PLATFORM
    mlb_addMetaString( mlBuilder, "COMPILE_PLATFORM", STRINGIFY(PLATFORM) );
  #else
    mlb_addMetaString( mlBuilder, "COMPILE_PLATFORM", "HOST" );
  #endif
  
  mlb_addMetaString( mlBuilder, "COMPILE_COMPILER_VERSION",  __VERSION__ );
 // mlb_addMetaString( mlBuilder, "icc_compiler_version",  __INTEL_COMPILER_UPDATE );
  char *tmp;
  #ifdef OPTIMAL_THREAD_NUM
    mlb_addMetaString( mlBuilder, "COMPILE_OPTIMAL_THREAD_NUM", STRINGIFY(OPTIMAL_THREAD_NUM) );
  #else
    mlb_addMetaString( mlBuilder, "COMPILE_OPTIMAL_THREAD_NUM", "unspecified" );
  #endif
  
  tmp = bstr2cstr (env_getCoreNumber(), (char) '\0');
  mlb_addMetaString( mlBuilder, "env_core_number",  tmp );
  bcstrfree (tmp);
  tmp = bstr2cstr (env_getProcModel(), (char) '\0');
  mlb_addMetaString( mlBuilder, "env_proc_model",  tmp );
  bcstrfree (tmp);
  tmp = bstr2cstr (env_getMemoryTotal(), (char) '\0');
  mlb_addMetaString( mlBuilder, "env_memory_total",  tmp );
  bcstrfree (tmp);
  tmp = bstr2cstr (env_date(), (char) '\0');
  mlb_addMetaString( mlBuilder, "date",  tmp );
  bcstrfree (tmp);
}