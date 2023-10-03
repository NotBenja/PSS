#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"



void eliminar(char *str, char *pat) {
    char *result = str; 
    //int len = strlen(pat);
    
    while (*str) {
        char *p_str = str;
        char *p_pat = pat;
        while (*p_str && *p_pat && *p_str == *p_pat) {
            p_str++;
            p_pat++;
        }

        if (*p_pat == '\0') {
            str = p_str;
        } else {
            *result = *str; 
            str++;
            result++;
        }
    }
    
    *result = '\0'; 
}
  



char *eliminados(char *str, char *pat) {
  char* ans = malloc(0);
  return ans;
}
