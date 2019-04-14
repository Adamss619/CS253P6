#include <string.h>
#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)#include <string.h>
#include "history.h"

typedef struct Cmd* command;
command *cmdHistory;

static int counting;

void init_history(){
  cmdHistory = malloc(sizeof(struct Cmd*)*11);
  for (int i=0; i<11; i++) {
      cmdHistory[i] = malloc(sizeof(struct Cmd));
	    cmdHistory[i]->cmd = NULL;
   }
}

char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}

void changeExitStatus(int exit){ //changes last history command exist status
  if(counting<10){
    printf("%d\n",exit);
    cmdHistory[counting-1]->exitStatus = exit;
  }else{
    cmdHistory[9]->exitStatus = exit;
  }
}

void add_history(char *cmd, int exitStatus){
  counting++;
  if(counting > 10){
    for(int i = 0;i<9;i++){
	     free(cmdHistory[i]->cmd);
       cmdHistory[i]->cmd = strdup(cmdHistory[i+1]->cmd);
       cmdHistory[i]->exitStatus = cmdHistory[i+1]->exitStatus;
    }
    printf("%s\n",cmd);
    free(cmdHistory[9]->cmd);

    if(cmdHistory[10]->cmd){
	     free(cmdHistory[10]->cmd);
	}

    cmdHistory[9]->cmd = strdup(cmd);
    cmdHistory[9]->exitStatus = exitStatus; // this^
    cmdHistory[10]->cmd = strdup(cmd);
    cmdHistory[10]->exitStatus = exitStatus;
    //printf("%s%s\n",cmdHistory[10]->cmd," value inside cmdHistory[10]");

  }else{
    cmdHistory[counting-1]->cmd = strdup(cmd);
    cmdHistory[counting-1]->exitStatus = exitStatus;
  }

  //printf("%s\n before",cmd);
  //cmdHistory[counting-1]->cmd = cmd;
  //int len = strlen(cmd);
}

void clear_history(){
  for(int i = 0;i<11;i++){
    free(cmdHistory[i]->cmd);
    free(cmdHistory[i]);
  }
  free (cmdHistory);
}

void print_history(int firstSequenceNumber){
if(counting<10){
    for(int i = 0;i<counting;i++){
      printf("%d%s%s%d%s%s\n",i+1," ","[",cmdHistory[i]->exitStatus,"] ",cmdHistory[i]->cmd);
    }
}else{
	int x = firstSequenceNumber;
	for(int i = 0; i<10;i++){
	printf("%d%s%s%d%s%s\n",x," ","[",cmdHistory[i]->exitStatus,"] ",cmdHistory[i]->cmd);
	x++;
}
}

}
