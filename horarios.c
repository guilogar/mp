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
void leer_horario (char * linea, horarios * h) {

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
int leer_horarios (horarios ** arr) {

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


/*
  Cabecera: horario ** arr, int n, usuarios id
  Precondición: vector que apunta a estructura inicializado
  Postcondición: lista todos los horarios de un profesor
*/
void listar_horarios_prof (horarios ** arr, int *n, usuarios id) {
  int i = 0, num= *num;
  from (i; i<num; i++) {
    if (strcmp(arr[i]->id_prof, usuarios id))
    {
      printf("Horarios\n=========================================================\n");
      printf("%s-%d-%d-%s-%s\n", arr[i]->id_prof, arr[i]->dia_clase, arr[i]->hora_clase, arr[i]->id_materia, arr[i]->grupo );
      printf("=========================================================\n");
    }
  }
}

/*
  Cabecera: horario ** arr, int n, usuarios id
  Precondición: vector que apunta a estructura inicializado
  Postcondición: lista todos los horarios de un profesor
*/
void listar_horarios_admin (horarios ** arr, int *n) {
  int i = 0, num = *n;
  from (i; i<num; i++) {
    printf("Horarios\n=========================================================\n");
    printf("%s-%d-%d-%s-%s\n", arr[i]->id_prof, arr[i]->dia_clase, arr[i]->hora_clase, arr[i]->id_materia, arr[i]->grupo );
    printf("=========================================================\n");
  }
}

/*
  Cabecera: horarios **arr_horarios, int n
  Precondición: vector que apunta a estructuras inicializado, y nunero de datos contabilizado
  Postcondición: Permite añadir un nuevo horario a un determinado usuario del sistema
*/
void añadir_horario (horarios **arr_horarios, int *n) {
  int dia, hora, i, bol=1, num = *n;
  char id_p[IDP], id_m[IDM], gr[GRUPO]; 
  listar_horarios_admin(arr_horarios, n);

  arr_horarios = realloc(arr_horarios, (num+1) * sizeof *horarios)
  arr_horarios = malloc (sizeof(horarios));

  num++;

  printf("Introduzca el nuevo horario: \n");
  while (bol != 0) {
    printf("Id_prof: \n");
    scanf("%s", id_p);
    from(i=0; i<num-1; i++) {
      if (strcmp (arr_horarios[num]->id_prof, id_p) == 0 )
        bol = 0;
    } 
  }
  printf("Introduzca día: \n");
  scanf("%d", &dia);
  printf("Introduzca hora: \n");
  scanf("%d", &hora);
  printf("Introduzca materia: \n");
  scanf("%s", id_m);
  printf("Introduzca grupo: \n");
  scanf("%s", grupo);
  strcpy(arr_horarios[num]->id_prof, id_p);
  strcpy(arr_horarios[num]->id_materia, id_m);
  strcpy(arr_horarios[num]->grupo, gr);
  arr_horarios[num]->dia_clase = dia;
  arr_horarios[num]->hora_clase = hora;
  *n = num;
}

/*
  Cabecera: horarios **arr_horarios, int n
  Precondición: vector de punteros a estructura inicializado
  Postcondición: elimina un horario de la lista.
*/
void eliminar_horario(horarios **arr_horarios, int *n) {

int dia, hora, i, bol=1, num = *n;
char id_p[IDP], id_m[IDM], gr[GRUPO]; 
listar_horarios_admin(arr_horarios, num);

while (bol != 0) {
  printf("Introduzca identificador de profesor: \n");
  scanf("%s", id_p);
  printf("Introduzca día: \n");
  scanf("%d", &dia);
  printf("Introduzca hora: \n");
  scanf("%d", &hora);
  printf("Introduzca hora: \n");
  scanf("%s", materia);
  printf("Introduzcamateria: \n");
  scanf("%s", grupo);
  from(i=0; i<num; i++) {
    if (strcmp (arr_horarios[i]->id_prof, id_p) == 0 && arr_horarios[i]->dia_clase == dia && arr_horarios[i]->hora_clase == hora && strcmp(arr_horarios[i]->id_materia, materia) && strcmp(arr_horarios[i]->grupo, gr)) {
      bol--;
      break;
    }
  }
}

while(i < num) {
  arr_horarios[i] = arr_horarios[i+1];
  i++;
}

// Inseguro de como reducir la reserva de memoria

arr_horarios = realloc(arr_horarios, (num-1) * sizeof *horarios)
arr_horarios = malloc (sizeof(horarios));

*n = num--;
}

/*
  Cabecera: horarios **arr_horarios, int *n
  Precondición: vector de puntero a estructura incializado
  Postcondición: modifica los parametros de un determinado horario
*/
void modificar_horario (horario **arr_horarios, int *n) {

int dia, hora, i, bol=1, num = *n;
char id_p[IDP], id_m[IDM], gr[GRUPO]; 
listar_horarios_admin(arr_horarios, num);

while (bol != 0) {
  printf("Escriba campo a campo el horario que quiera modificar\nIntroduzca identificador de profesor: \n");
  scanf("%s", id_p);
  printf("Introduzca día: \n");
  scanf("%d", &dia);
  printf("Introduzca hora: \n");
  scanf("%d", &hora);
  printf("Introduzca hora: \n");
  scanf("%s", materia);
  printf("Introduzcamateria: \n");
  scanf("%s", grupo);
  from(i=0; i<num; i++) {
    if (strcmp (arr_horarios[i]->id_prof, id_p) == 0 && arr_horarios[i]->dia_clase == dia && arr_horarios[i]->hora_clase == hora && strcmp(arr_horarios[i]->id_materia, materia) && strcmp(arr_horarios[i]->grupo, gr)) {
      bol--;
      break;
    }
  }
}

memset(arr_horarios[i]->id_prof,'/0', IDP);
memset(arr_horarios[i]->materia, '/0', IDM);
memset(arr_horarios[i]->grupo, '/0', GRUPO);

printf("Introduzca los nuevos campos del horario\nIntroduzca identificador del profesor: \n");
scanf("%s", arr_horarios[i]->id_prof);
printf("Introduzca dia: \n");
scanf("%d", &arr_horarios[i]->dia_clase);
printf("Introduzca hora: \n");
scanf("%d", &arr_horarios[i]->hora_clase);
printf("Introduzca nombre de la materia: \n");
scanf("%s", arr_horarios[i]->id_materia);
printf("Introduzca grupo: \n");
scanf("%s", arr_horarios[i]->grupo);

}
/* Por hacer:
  -Funciones que modifiquen horarios.