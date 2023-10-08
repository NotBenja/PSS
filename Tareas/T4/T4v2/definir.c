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

void insertar(char *nom_dicc, char *llave, char *def) {
    // Abrimos el archivo en modo r+
    FILE *in = fopen(nom_dicc, "r+");
    
    // Comprobamos que el archivo es válido, sino retornamos error
    if (in == NULL) {
        perror("El archivo no puede abrirse");
        exit(1);
    }
    
    // Calculamos el tamaño del archivo en líneas
    fseek(in, 0, SEEK_END);
    int sizeBytes = ftell(in);
    int lineas = sizeBytes / 81;
    
    // Definimos el índice de la llave
    int i_llave = hash_string(llave) % lineas;
    int vueltas = 0;
    
    // Buscamos la línea de dicho índice
    fseek(in, i_llave * 81, SEEK_SET);
    
    // Vemos si ya existe la llave a insertar
    char buf[81];
    
    // Leemos toda la línea
    fread(buf, 1, sizeof(buf), in);
    
    // Si la línea está vacía, debería comenzar con un espacio en blanco
    if (buf[0] == ' ') {
        // Rebobinamos para escribir sobre la misma línea
        fseek(in, i_llave * 81, SEEK_SET);
    } else {
        while (1) {
            if (i_llave == lineas) {
                i_llave = 0;
                vueltas++;
                if (vueltas == 2) {
                    fprintf(stderr, "El diccionario está lleno\n");
                    fclose(in);
                    exit(3);
                    break;
                }
            }
            
            // Si la línea no está vacía, verificamos si es la misma llave
            char *llave1 = buf;
            while (*llave1 != ':') {
                llave1++;
            }
            *llave1 = '\0'; // Terminamos la cadena en ':' para comparar
            if (strcmp(buf, llave) == 0) {
                fprintf(stderr, "La llave %s ya se encuentra en el diccionario\n", llave);
                fclose(in);
                exit(2); // Cierra el archivo antes de retornar
            } else {
                break;
            }
            
            // Si no es la misma llave, avanzamos a la siguiente línea de manera circular
            i_llave++;
            fseek(in, i_llave * 81, SEEK_SET);
        }
    }
    
    // Rellenamos con espacios en blanco hasta llegar a 80 caracteres
    int len = strlen(llave) + strlen(def);
    if (len + 1 < 80) { // Añadimos 1 para el salto de línea
        fprintf(in, "%s:%s", llave, def);
        for (int i = 0; i < 80 - len - 1; i++) {
            fprintf(in, " ");
        }
        fprintf(in, "\n");
    } else {
        // Caso donde la definición es demasiado larga
        perror("La definición es demasiado larga");
        exit(3);
    }
    
    fclose(in);
}

