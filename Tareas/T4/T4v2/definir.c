#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

/*... define variables globales o funciones adicionales ...*/
void insertar(char *nom_dicc,char *llave, char *def);


int main(int argc, char *argv[]) {
   
    insertar(argv[1], argv[2], argv[3]);
    return 0;
}

void insertar(char *nom_dicc,char *llave, char *def) {
    //Abrimos el archivo en modo r+
    FILE *in = fopen(nom_dicc,"r+");
    //Comprobamos que el archivo es válido, sino retornamos error
    if (in == NULL){
        perror("El archivo no puede abrirse");
        exit(1);
    }
    //Calculamos el tamaño del archivo
    fseek(in, 0, SEEK_END);
    int sizeBytes= ftell(in);;
    //Calculamos el número de líneas
    int lineas = sizeBytes/81;
    //Definimos el índice de la llave
    int i_llave = hash_string(llave) % lineas;
    //Buscamos la línea de dicho índice
    fseek(in, i_llave, SEEK_SET);
    //Vemos si ya existe la llave a insertar
    int n = strlen(llave);
    char buf[n+1];
    buf[n] = 0;
    //Contador para ver la línea en la que estamos, debe iniciar siendo la línea dada por hash_string
    int count = i_llave;
    //Partimos buscando en el índice que retorna hash_string
    fseek(in, i_llave, SEEK_SET);
    for(;;){
        //Si llegamos a la última línea, entonces reiniciamos el contador
        if (count == lineas){
            count = 0;
        }
        //Si la línea está vacía, debería comenzar con un espacio en blanco
        if (fgetc(in) != ' '){
            fseek(in, -1, SEEK_CUR); //Retrocedemos el caracter que avanzamos en el if
            fputs(llave,in);
            fputc(':',in);
            fputs(def,in);
            break;
        } else{
            fseek(in, -1, SEEK_CUR); //Retrocedemos el caracter que avanzamos en el if
            //Corroboramos que si la línea está ocupada por la misma llave entonces retornamos error.
            if( (strcmp(buf, llave) == 0) && (count == i_llave) ){
                perror("Test con llave existente");
                exit(1);
            } else {
                //Como la línea que visitamos no estaba vacía, entonces vamos a la siguiente para repetir el bucle.
                count++;
                fseek(in,count,SEEK_SET);
            }
        }     
    }
    fclose(in);
}