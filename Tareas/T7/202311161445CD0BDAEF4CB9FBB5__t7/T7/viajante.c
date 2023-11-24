#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "viajante.h"

int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double viajante_par(int z[], int n, double **m, int nperm, int p) {
    int pipes[p][2];  // Cada hijo tendrá un pipe para comunicarse con el padre
    //Creamos los p pipes para los p forks 
    for (int i=0; i<p; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Error al crear el pipe");
            exit(1);
        }
    }
    //Declaramos la variable donde almacenaremos el pid del fork
    pid_t pid;
    for (int i=0; i<p; i++) {
        if ((pid = fork()) == 0) {
            //Cerramos la lectura pues no la usaremos
            close(pipes[i][0]); 
            //Renovamos la semilla para randomizar
            srandom(getUSecsOfDay()*getpid());
            //Definimos la cantidad de permutaciones a probar
            int sub_nperm = nperm/p;
            //Creamos un arreglo auxiliar que almacenará nuestra ruta candidata
            int sub_z[n+1];
            //Utilizamos el algoritmo del enunciado para ver una posible ruta
            double sub_min = viajante(sub_z, n, m, sub_nperm);

            //Enviamos nuestra candidata a través del pipe para que pueda ser leída por el padre
            write(pipes[i][1], sub_z, sizeof(sub_z));
            write(pipes[i][1], &sub_min, sizeof(sub_min));
            //Cerramos la escritura
            close(pipes[i][1]);
            //Matamos y enterramos al proceso hijo  
            exit(0);
            waitpid(pid,NULL,0);
        } else if (pid == -1) {
          //En caso de haber fallos en crear al hijo utilizamos la salida de errores
            perror("Error al crear el proceso hijo");
            exit(1);
        }
    }
    //Definimos la distancia mínima inicial al igual que en el algoritmo original
    double min = DBL_MAX;
    //Iteramos para leer el contenido de cada pipe
    for (int i=0; i<p; i++) {
        //Cerramos la escritura del pipe en el proceso padre
        close(pipes[i][1]);  
        //Declaramos las variables donde se almacenarán la ruta candidata con su distancia
        int sub_z[n + 1];
        double sub_min;

        //Leemos la ruta candidata y su distancia
        read(pipes[i][0], sub_z, sizeof(sub_z));
        read(pipes[i][0], &sub_min, sizeof(sub_min));
        //Si la distancia es menor a la considerada en iteraciones previas, sobreescribimos min
        if (sub_min < min) {
            min = sub_min;
            //Copiamos la ruta candidata en el arreglo z
            for (int j = 0; j <= n; j++)
                z[j] = sub_z[j];
        }
        //Cerramos la escritura para el padre
        close(pipes[i][0]);  
    }
    return min;
}
