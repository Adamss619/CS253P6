#include <stdio.h>
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>
#include "smash.h"
#include "history.h"

int firstSequenceNumber;

#define MAXLINE 4096
int main(int argc, char ** argv){
  firstSequenceNumber = 1;
  char bfr[MAXLINE];
  fputs("$ ",stderr);
  init_history(); // starts history
  while (fgets(bfr, MAXLINE, stdin) != NULL) {
  bfr[strlen(bfr) - 1] = '\0'; //replace newline with NUL
  executeCommand(bfr);
  }
  //close eveything
  exit(0);
}
