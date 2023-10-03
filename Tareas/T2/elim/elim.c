#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"



void eliminar(char *str, char *pat) {
    char *result = str;
    
    while (*str) { //Leemos todo el str
        char *p_str = str; //Puntero aux para str
        char *p_pat = pat; //Puntero aux para el patrón
        while (*p_str && *p_pat && *p_str == *p_pat) { //El ciclo se romperá cuando alguno de los str se acabe o cuando no coincidan los caracteres
            p_str++; 
            p_pat++;
        }

        if (*p_pat == '\0') { //En caso de que el patrón haya sido leído por completo, actualizamos adonde apunta el puntero str, saltando el patrón
            str = p_str; 
        } else { //En caso contrario, guardamos lo que llevamos leído del str y seguimos avanzando.
            *result = *str; 
            str++;
            result++;
        }
    }
    
    *result = '\0'; //Cerramos el resultado 
}
  
//Función Auxiliar, funciona igual al patrón anterior, solo que cuenta las repeticiones 

int contarRepeticiones(char *str, char *pat) {
    int count = 0;  //Variable para contar las repeticiones del patrón

    while (*str) {
        char *p_str = str;
        char *p_pat = pat;

        while (*p_str && *p_pat && *p_str == *p_pat) {
            p_str++;
            p_pat++;
        }

        if (*p_pat == '\0') {
            count++;  //Incrementa el contador cuando se encuentra una coincidencia
            str = p_str;
        } else {
            str++;
        }
    }

    return count; //Retornamos el contador
}


char* eliminados(char *str, char *pat) {
    int reps = contarRepeticiones(str,pat); //Utilizamos la función auxiliar anterior para ver cuántas veces se repite el patrón
    char *result = (char *)malloc(strlen(str)-(strlen(pat)*reps)+1); //Pedimos la memoria exacta equivalente al largo del str original - el largo del patrón según aparezca + el 0 final
    char *result_ptr = result; 
//Utilizamos el mismo algoritmo de eliminar
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
            *result_ptr = *str;
            str++;
            result_ptr++;
        }
    }
    
    *result_ptr = '\0';
    return result; 
}

