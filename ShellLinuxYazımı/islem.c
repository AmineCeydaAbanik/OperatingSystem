#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<sys/types.h> 
#include<sys/wait.h> 
#include<unistd.h> 


int main(int argc, char *argv[])
{   
	int exec1;      
	
	char *topla[1];  //topla 
	      topla[0]="topla";
	      
	char *cikar[1];  //cikar 
	      cikar[0]="cikar";
	      	
	char *komut[1];  //komut 
	      komut[0]=argv[0];
	      
	char *array[1]; //Gonderecegim dizi
	      array[0]=argv[1];
	      array[1]=argv[2];
	   
	
	if (strcmp(komut[0],topla[0]) == 0) 
	{ 
	    exec1 = execve("topla",array,NULL);
	}
		
	else if(strcmp(komut[0], cikar[0]) == 0) 
	{
	    exec1 = execve("cikar",array,NULL);
	}
	
	else	
	{
	    wait(&exec1);
	    printf("HATA: '%s' bir komut de?ildir. \n\n",argv[0]);
	}
	
    	return 0;
}
