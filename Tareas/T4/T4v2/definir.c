#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

/*... define variables globales o funciones adicionales ...*/

int main(int argc, char *argv[]) {
    //Abrimos el archivo en modo r+
    FILE *in = fopen("dicc.txt","r+");
    //Comprobamos que el archivo es válido, sino retornamos error
    if (in == NULL){
        perror("El archivo no puede abrirse");
        exit(1);
    }
    //Calculamos el tamaño del archivo
    fseek(in, 0, SEEK_END);
    int sizeBytes= ftell(in);
    printf("El tamaño es: %d\n", sizeBytes);
    return 0;
    


}
