#include <env.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcthw/mlBuilder.h>

bstring coreNumber = NULL;
bstring procModel = NULL;
bstring memoryTotal = NULL;
bstring date = NULL;

bstring exec_command(char *command){
  
  /*static const_bstring tab = bfromcstr("\t");
  static const_bstring empty = bfromcstr("");*/
  
  FILE* file = popen(command, "r");
  char buffer[100];
  fgets(buffer, 100, file);
  pclose(file);
  //printf("buffer is :%s\n", buffer);
	//return btrimws(bfromcstr(buffer));
  bstring str = (bfromcstr(buffer));
  btrimws(str);
  bfindreplace(str, bfromcstr("\t"), bfromcstr(""), 0);
  return str;
}

bstring env_getCoreNumber() {
  if(coreNumber == NULL){
    coreNumber = exec_command("cat /proc/cpuinfo | grep processor | wc -l 2>&1");
  }
  return coreNumber;
}
bstring env_getProcModel(){
  if(procModel == NULL){
    procModel = exec_command("cat /proc/cpuinfo | grep \"model name\" | head -n 1 2>&1");
  }
  return procModel;
}
bstring env_getMemoryTotal(){
  if(memoryTotal == NULL){
    memoryTotal = exec_command("cat /proc/meminfo | grep MemTotal 2>&1");
  }
  return memoryTotal;
}
bstring env_date(){
  if(date == NULL){
    date = exec_command("date");
  }
  return date;
}
