#include<stdio.h>
#include<stdlib.h>
int main(int argc, char * arguments[]) {
  int i;
    for (i = 0; i < atoi(arguments[1]); i++) {
      printf("%s", arguments[0]);
      printf("\n");
    }
  
  return 0;
}

