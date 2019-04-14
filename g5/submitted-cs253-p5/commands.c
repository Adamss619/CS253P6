#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>
#include <unistd.h>
#include "smash.h"
#include "history.h"


char commandString[1000];
extern int firstSequenceNumber;
int commandCount;

void executeCommand(char* str){
commandCount++;
  if(commandCount>10){
	firstSequenceNumber++;
}
  strncpy(commandString,"",1); //resets string
  strncat(commandString,"cd ",3);//keeps track of command for cd
  char* token = strtok(str," ");
  int i=0;
  while (token != NULL) {
  if(!strcmp(token,"cd")){
    token = strtok (NULL, " "); //do something to get to the next token
    if(token == NULL){
      perror("Invalid argument"); // checks for an empty cd command
      add_history(strncat(commandString,token,strlen(token)),1);
    }
    else if(chdir(token) == 0){
      chdir(token);
      printf("%s\n",token); //checks if dir exists then goes in and prints it
      add_history(strncat(commandString,token,strlen(token)),0);
    }else{
      perror(token); //prints error
      add_history(strncat(commandString,"no-such-directory",strlen("no-such-directory")),1);
    }

  }else if(!strcmp(token,"exit")){ //looks for error command
    //print_history(firstSequenceNumberCount);
    clear_history();
    exit(0);

  }else if(!strcmp(token,"history")){
    add_history(token,0);
    print_history(firstSequenceNumber);
  }else{
    printf("%d %s\n",i++,token); //if command isnt recognized prints each argument with a #
    add_history("no-such-command",127);
  }
  token = strtok (NULL, " ");
  }
  fputs("$ ",stderr);
}
