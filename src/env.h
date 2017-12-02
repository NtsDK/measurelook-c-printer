#ifndef env_h
#define env_h

#include <lcthw/mlBuilder.h>

bstring exec_command(char *command);

bstring env_getCoreNumber();
bstring env_getProcModel();
bstring env_getMemoryTotal();
bstring env_date();

#endif