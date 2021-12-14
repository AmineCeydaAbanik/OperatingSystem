#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* arguments[]){
    int x = atoi(arguments[0]);
    int y = atoi(arguments[1]);
    int result = x + y;
    printf("%d + %d = %d \n",x,y,result);
    return 0;
}
