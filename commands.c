#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>
#include <unistd.h>
#include "smash.h"
#include "history.h"


char commandString[1024];
extern int firstSequenceNumber;
int commandCount;
char *argument[1024];


//takes two arguments takes in command line and sets second argument to parsed information
void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' &&
                 *line != '\t' && *line != '\n')
               line++;             /* skip the argument until ...    */
     }
     *argv = NULL;                 /* mark the end of argument list  */
}

void executeExternalCommand(char **argv){
    //pid_t parent = getpid();
    pid_t pid = fork();
    //printf("%s","Inside executeExternalCommand");
    if(pid == -1){
			fprintf(stderr, "Fork error\n");

    }else if(pid > 0){
      int status;
      waitpid(pid, &status, 0);

    if ( WIFEXITED(status) ) {
        const int es = WEXITSTATUS(status);
        //changeExitStatus(es);
        //printf("exit status was %d\n", es);
    }
    }
    else{
      if(execvp(*argv,argv) < 0 ){
         printf("%s\n","error");
         exit(0);
      }

    }
}



void executeCommand(char* str){
commandCount++;
  if(commandCount>10){
	firstSequenceNumber++;
}
  char *oldstr=malloc(1026);
  strncpy(oldstr,str,strlen(str));

  strncpy(commandString,"",1); //resets string
  strncat(commandString,"cd ",3);//keeps track of command for cd
  char* token = strtok(str," ");
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
    free(oldstr);
    clear_history();
    exit(0);

  }else if(!strcmp(token,"history")){
    add_history(token,0);
    print_history(firstSequenceNumber);
  }else{
    while (token != NULL) {
      token = strtok (NULL, " ");
    }
    add_history(oldstr,0);
    parse(oldstr,argument);
    executeExternalCommand(argument);
    //printf("%d %s\n",i++,token); //if command isnt recognized prints each argument with a #
  }
  token = strtok (NULL, " ");
  }
  fputs("$ ",stderr);
}
