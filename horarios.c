#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "horarios.h"
#include "estructuras.h"

/*
   Cabecera: char *, horario *
   Precondicion: vectores declarados e inicializados
   Postcondicion: lee una linea y guardo todos sus atributos en una
   estructura horario
*/
void leer_horario (char * linea, horario * h) {

    if (linea == NULL) {
      perror("Error: linea vacia.\n");
    }

    else {
      strcpy(h->id_prof, strtok (linea,"-"));

      strcpy(h->dia_clase, strtok (NULL,"-"));

      strcpy(h->hora_clase, strtok (NULL,"-"));

      strcpy(h->id_materia, strtok (NULL,"-"));

      strcpy(h->grupo, strtok (NULL,"\n"));
    }
}

/*
	Cabecera: horario **
	Precondición: puntero a vector de estructura declarado e inicializado
	Postcondición: Lee todos los horarios que se encuetran en el fichero horarios.tt
	y los guarda en un vector de punteros a estructura tipo horario
*/ 
int leer_horarios (horario ** arr) {

int i = 0;
char linea[MAX_LINEA];
  FILE * fichero = fopen("horarios.txt", "r");

  if (fichero == NULL){
   /* exit(EXIT_FAILURE); Dejar para mas tarde y poner un mensaje de error simplemente */
	   puts(ANSI_COLOR_RED);
        puts("Error fatal: El fichero con la información no existe.\n\n");
        puts(ANSI_COLOR_RESET);
        return;
      }

	//Reserva progresiva de memoria para almacenar cada
	//horario en el vector
  while (fgets (linea, sizeof linea, fichero)) {
    arr[i] = malloc (sizeof (horario));
    leer_horario(linea, arr[i]);
    i++;
  }

  fclose(fichero);

  return i;
}


/* Por hacer:
  -Función listar horarios por id de profesor en menu admin.
  -Funciones que añadan, eliminen, modifiquen, o eliminen horarios.