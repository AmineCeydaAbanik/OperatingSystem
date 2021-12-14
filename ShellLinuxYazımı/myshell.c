#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void parseSpace(char * str, char ** parsed);
void parseOperator(char * str, char ** parsed);
int pipeSearch(char * str);
int commandLength(char * commandInput);
int Clear(int i);
void executekomut(char * commands[]);


  
void parseSpace(char * str, char ** parsed) {
  // komutlari bosluklara bakilarak bolme islemi
  int i;
  for (i = 0; i < 100; i++) {
    parsed[i] = strsep( & str, " ");

    if (parsed[i] == NULL) {
      break;
    }
    if (strlen(parsed[i]) == 0) {
      i--;
    }
  }
}

void parseOperator(char * str, char ** parsed) {
  // pipe yapisýna göre komutlarin ayrilmasiný saðlarken iþlemleri sýrayla yazmayý da saðlamýþ olur.
  int i;
  for (i = 0; i < 2; i++) {
    parsed[i] = strsep( & str, "|");

    if (parsed[i] == NULL) {
      break;
    }
  }

}
int pipeSearch(char * str) {
  // coklu islem icin gerekli dik cizgi sembolu aranir.
  int flag = 0;
  int i;
  
  for (i = 0; i < commandLength(str); i++) {
    if (str[i] == '|') {
      flag = 1;
      break;
    }

  }
  return flag;
}
int commandLength(char * commandInput) {
  return strlen(commandInput);
}

int Clear(int i) {
  i = execvp("clear", (char *const []) {
   "clear",NULL});
  return i;
}
void executeKomut(char * commandArr[]) {

  char * elemanlar[4];
  int i;
  elemanlar[0] = cArr[1];
  elemanlar[1] = cArr[2];
  elemanlar[2] = cArr[3];
  elemanlar[3] = NULL;

  int f1 = fork();

    if (f1 == 0) { // fork edilme durumu

    if (strcmp(cArr[0], "clear") == 0) { // clear komutu
      Clear(i);
      perror("Yanlis Komut Girdiniz! \n");
    } else if (strcmp(cArr[0], "cat") == 0) {
      char * cArguments[3]={cArr[0],cArr[1],NULL}; // Arguman atamalari 
      int cFile;
      int f2 = fork();
      if (f2 == 0) {
        cFile = execv("/bin/cat", cArguments); 
        perror("Yanlis bir Komut girdiniz! \n"); 

      } else {
        wait(NULL);
      }

    } else {
      i = execv(cArr[0], elemanlar);
      perror("Yanlis Komut Girdiniz! \n");
    }
  } else  if (f1 < 0) {	// fork fail olma durumu
    printf("\nFailed..");
    exit(EXIT_FAILURE);
  } else {
    wait( & i); // forku bekle    
  }
}




int main() {
  char * cArray[100];
  char * wArray[100];
  char * inp[1000];
  int i;

  while (1) {
    memset( & wArray, 0, sizeof(wArray)); 
    memset( & cArray, 0, sizeof(cArray));  
    int i = 0;

    printf("\nmyshell>>");
    scanf("%[^\n]%*c",inp);

    if (strcmp(inp, "exit") == 0) {
      printf("\nProgram kapandi.\n");
      exit(EXIT_FAILURE);
      break;
    }

    if (pipeSearch(inp) == 1) { // Coklu islem
      parseOperator(inp, cArray);
      for (i = 0; i < 2; i++) {
        parseSpace(cArray[i], wArray); //parsed
        executeKomut(wArray);
      }
    } else {

      parseSpace(inp, wArray); // tekli islem
      executeKomut(wArray);
    }

  }
  return 0;
}
