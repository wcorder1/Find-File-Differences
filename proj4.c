#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>


/* step1 receives 2 file arguments.  It then uses a while and nested
   if loop to iterrate through both files until both of them reach the end and
   during this iterration it takes any chars that are not equal from the first file 
   and puts them in a new writable file called, differencesFoundInFile1.txt then prints
   how long in milliseconds it took to run this function */

void step1(FILE * f1, FILE * f2);


/* fileLength finds the number of chars stored in a file */

int fileLength(FILE * f);


/* fileStore stores the values from file f into the dynamic array p by iterrating
   from 0 to the length of the file found with fileLength */

void fileStore(FILE * f, int len, char ** p);


/* step2 acts similarly to step 1 but then uses fileLength and fileStore to place
   the values of file1 and file2 into two separate dynamic arrays.  It then checks
   one by one if the chars in array 1 are equal to the chars in array 2 and places
   any differences into a third array.  Finally it puts all the values within the
   third array into a new file called differencesFoundInFile2 then prints how long
   in milliseconds it took to run this function */

void step2(FILE * f1, FILE * f2);


int main(int argc, char * argv[]) {

  FILE * f1 = fopen(argv[1],"r");
  FILE * f2 = fopen(argv[2],"r");
  
  if (argv[3] != NULL || argv[2] == NULL) {
    printf("Usage: proj4.out <file1> <file2>\n");
  }

  else if (f1 == NULL || f2 == NULL) {
    printf("There was an error reading a file.\n");
  }
  
  else {   
    step1(f1,f2);

    rewind(f1);
    rewind(f2);
    
    step2(f1,f2);

    fclose(f1);
    fclose(f2);
  }
  return 0;
}



void step1(FILE * f1, FILE * f2) {
  
  struct timeval start, end;
  gettimeofday(&start,NULL);

  FILE * difF1 = fopen("differencesFoundInFile1.txt","w");
  
  char c1 = getc(f1), c2 = getc(f2);

  while (((c1 != EOF) && (c2 != EOF)) || ((c1 != EOF) && (c2 == EOF))) {
    if (c1 != c2) {
      putc(c1,difF1);
    }
    c1 = getc(f1);
    c2 = getc(f2);
  }
  
  gettimeofday(&end,NULL);
  
  fclose(difF1);
    
  double t = (double) ((end.tv_sec * 1000  + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)) / 1000.0;
  printf("Step 1 took %lf milliseconds\n", t);
}



int fileLength(FILE * f) {
  
  int count = 0;
  char c = getc(f);

  while (c != EOF) {
    count++;
    c = getc(f);
  }
  
  rewind(f);
  return count;
}



void fileStore(FILE * f, int len, char ** p) {
  
  for (int i = 0; i < len; i++) {
    *(*p+i) = getc(f);
  }
}



void step2(FILE * f1, FILE * f2) {
  
  struct timeval start, end;
  gettimeofday(&start,NULL);

  FILE * difF2 = fopen("differencesFoundInFile2.txt","w");
  int len1 = fileLength(f1), len2 = fileLength(f2), len3 = 0;

  char * p1 = (char *) malloc(len1), * p2 = (char *) malloc(len2), * p3 = (char *) malloc(len3);

  fileStore(f1,len1,&p1);
  fileStore(f2,len2,&p2);

  for (int i = 0; ((*(p1+i) != '\0') && (*(p2+i) != '\0')) || ((*(p1+i) == '\0') && (*(p2+i) != '\0')); i++) {
    if(*(p1+i) != *(p2+i)) {
      len3++;
      p3 = (char *) realloc (p3,len3);
      *(p3+i) = *(p2+i);
      putc(*(p3+i),difF2);
    }
  }
  
  gettimeofday(&end,NULL);
  
  fclose(difF2);
  free(p1);
  free(p2);
  free(p3);
  
  double t = (double) ((end.tv_sec * 1000  + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)) / 1000.0;
  printf("Step 2 took %lf milliseconds\n", t);
}
