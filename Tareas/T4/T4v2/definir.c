/*Nombre: Benjamín Reyes Bravo */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

/*... define variables globales o funciones adicionales ...*/
void insertar(char *nom_dicc,char *llave, char *def);


int main(int argc, char *argv[]) {
    //Corroboramos que la/el cantidad/tipo de argumentos es correcta/o
    if(argc != 4){
        fprintf(stderr, "Uso: ./definir <diccionario> <llave> <definicion>\n"); 
        exit(1);   
    }
    //Utilizamos la función auxiliar insertar
    insertar(argv[1], argv[2], argv[3]);
    return 0;
}

void insertar(char *nom_dicc, char *llave, char *def) {
    //Abrimos el archivo en modo r+
    FILE *in = fopen(nom_dicc, "r+");
    //Verificamos si el archivo existe
    if (in == NULL) {
        perror(nom_dicc);
        exit(1);
    }
    //Calculamos su tamaño y cantidad de líneas
    fseek(in, 0, SEEK_END);
    int sizeBytes = ftell(in);
    int lineas = sizeBytes / 81;
    //Vemos el índice preeliminar de la línea para la llave
    int i_llave = hash_string(llave) % lineas;
    //Variable que nos dirá si es que se recorrió el diccionario completo
    int vueltas = 0;
    //Creamos un buffer para poder almacenar una línea completa incluyendo \n
    char buf[81];

    while (1) {           
        //Revisamos si el archivo ya se leyó por completo
        if (i_llave == lineas) {
            i_llave = 0;
            vueltas++;
            //En caso de que se hayan dado dos vueltas es porque el diccionario ya está lleno
            if (vueltas == 2) {
                fprintf(stderr, "%s: el diccionario esta lleno\n",nom_dicc);
                fclose(in);
                exit(3);
                break;
            }
        }
    
        //Nos dirigimos hacia la línea preeliminar
        fseek(in, i_llave * 81, SEEK_SET);
        //Leemos la línea completa y la almacenamos en el buffer
        fread(buf, 1, sizeof(buf) , in);
        //Revisamos si el primer caracter es un espacio en blanco, pues por sintaxis del diccionario,
        //si ese espacio está vacío, la línea completa debería estarlo.
        if (buf[0] == ' ') {
            //Devolvemos el cursor a la posición inicial 
            fseek(in, i_llave * 81, SEEK_SET);
            break;
        }
        //Copiamos la llave para luego compararla
        char *llave1 = buf;
        while (*llave1 != ':') {
            llave1++;
        }
        //Como llegamos al caracter :, ya copiamos toda la llave así que debemos terminar el string.
        *llave1 = '\0';
        //Comparamos si son iguales
        if (strcmp(buf, llave) == 0) {
            fprintf(stderr, "La llave %s ya se encuentra en el diccionario\n", llave);
            fclose(in);
            exit(2);
        } 
        i_llave++;
    }

    int len = strlen(llave) + strlen(def);
    if (len + 1 < 80) {
        fprintf(in, "%s:%s", llave, def);
        
        //Calculamos cuántos espacios en blanco necesitamos para completar la línea
        int espacios = 80 - len - 1;
        
        //Rellenamos con los espacios en blanco
        for (int i = 0; i < espacios; i++) {
            fprintf(in, " ");
        }
        //Agregamos el salto de línea
        fprintf(in, "\n");
    } else {
        //En caso de que la línea fuese a sobrepasar el límite de caracteres se lanza un error
        fprintf(stderr, "La definición entregada es muy larga.\n");
        exit(3);
    }
    
    fclose(in);
}


