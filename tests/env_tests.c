#include "minunit.h"
#include "env.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ENV_TEST(name, function) char *(name)(){\
  char * tmp;\
  tmp = bstr2cstr (function(), (char) '\0');\
  debug("%s", tmp);\
  bcstrfree (tmp);\
  tmp = bstr2cstr (function(), (char) '\0');\
  debug("%s", tmp);\
  bcstrfree (tmp);\
	return NULL;\
}

ENV_TEST(test_core_number, env_getCoreNumber);
ENV_TEST(test_proc_model, env_getProcModel);
ENV_TEST(test_memory_total, env_getMemoryTotal);
ENV_TEST(test_date, env_date);

char *all_tests()
{
  mu_suite_start();
  
  mu_run_test(test_core_number);
  mu_run_test(test_proc_model);
  mu_run_test(test_memory_total);
  mu_run_test(test_date);

  return NULL;
}

RUN_TESTS(all_tests);