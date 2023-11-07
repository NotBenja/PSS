#include <string.h>


extern inline int countWords(char *a4){
  int a0 = 0;
  int inWord = 0;
  char c1;
  while(*a4){
    c1 = *a4;
    if(c1 != 32 && !inWord){
      inWord = 1;
      a0++;
    } else if (c1 == 32){
      inWord = 0;
    }
    a4++;
  }
  return a0;
}

int strCmp(char *s1, char *s2) {
    int t1= (countWords(s1) - countWords(s2));
    return t1;
}

void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {

    int t1= strCmp(p[0], p[1]);

    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}
