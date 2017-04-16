#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "horarios.h"
#include "auxiliar.h"

/*
	Cabecera: ninguna
	Precondición: ninguna
	Postcondición: permite el manejo de la información de horarios
*/
void menu_horarios(horarios **arr_horarios, int* n_horarios) {
    int op;

    system("cls");
    printf("1. Aniadir horas\n");
    printf("2. Eliminar horas\n");
    printf("3. Modificar horas\n");
    printf("4. Listar horario\n");
    printf("5. Salir\n\n");

    printf("Op: ");
    scanf("%d",&op);

    while(op!=5){
        switch(op){
            case 1:
                system("cls");
                aniadir_horario(arr_horarios,n_horarios);
                op=5;
            break;
            case 2:
                system("cls");
                eliminar_horario(arr_horarios,n_horarios);
                op=5;
            break;
            case 3:
                system("cls");
                modificar_horario(arr_horarios,n_horarios);
                op=5;
            break;
            case 4:
                system("cls");
                listar_horarios_admin(arr_horarios,n_horarios);
                op=5;
            break;
            default:
                printf("\nOpcion incorrecta\n");
            break;
        }

        if(op!=5){
            printf("Op: ");
            scanf("%d",&op);
        }
    }
}

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

      h->dia_clase = atoi( strtok (NULL,"-"));

      h->hora_clase = atoi( strtok (NULL,"-"));

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
        puts("Error fatal: El fichero con la informacion no existe.\n\n");
        puts(ANSI_COLOR_RESET);
        return 0;
      }

	//Reserva progresiva de memoria para almacenar cada
	//horario en el vector
  while (fgets (linea, sizeof linea, fichero)) {
    arr[i] = malloc (sizeof (horarios));
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
void listar_horarios_prof (horarios **arr, int *n, char id_p) {
  int i = 0, num= *n;
  for (i; i<num; i++) {
    if (strcmp(arr[i]->id_prof, &id_p))
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
  for (i; i<num; i++) {
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
void aniadir_horario (horarios **arr_horarios, int *n) {
  int dia, hora, i, bol=1, num = *n;
  char id_p[IDP], id_m[IDM], gr[GRUPO];
  listar_horarios_admin(arr_horarios, n);

  arr_horarios = realloc(arr_horarios, (num+1) * sizeof (horarios*));
  arr_horarios = malloc (sizeof(horarios));

  num++;

  printf("Introduzca el nuevo horario: \n");
  while (bol != 0) {
    printf("Id_prof: \n");
    scanf("%s", id_p);
    for(i=0; i<num-1; i++) {
      if (strcmp (arr_horarios[num]->id_prof, id_p) == 0 )
        bol = 0;
    }
  }
  printf("Introduzca dia: \n");
  scanf("%d", &dia);
  printf("Introduzca hora: \n");
  scanf("%d", &hora);
  printf("Introduzca materia: \n");
  scanf("%s", id_m);
  printf("Introduzca grupo: \n");
  scanf("%s", gr);
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
listar_horarios_admin(arr_horarios, n);

while (bol != 0) {
  printf("Introduzca identificador de profesor: \n");
  scanf("%s", id_p);
  printf("Introduzca dia: \n");
  scanf("%d", &dia);
  printf("Introduzca hora: \n");
  scanf("%d", &hora);
  printf("Introduzca hora: \n");
  scanf("%s", id_m);
  printf("Introduzcamateria: \n");
  scanf("%s", gr);
  for(i=0; i<num; i++) {
    if (strcmp (arr_horarios[i]->id_prof, id_p) == 0 && arr_horarios[i]->dia_clase == dia && arr_horarios[i]->hora_clase == hora && strcmp(arr_horarios[i]->id_materia, id_m) && strcmp(arr_horarios[i]->grupo, gr)) {
      bol--;
      break;
    }
  }
}

while(i < num) {
  arr_horarios[i] = arr_horarios[i+1];
  i++;
}

arr_horarios = realloc(arr_horarios, (num-1) * sizeof (horarios*));
arr_horarios = malloc (sizeof(horarios));

*n = num--;
}

/*
  Cabecera: horarios **arr_horarios, int *n
  Precondición: vector de puntero a estructura incializado
  Postcondición: modifica los parametros de un determinado horario
*/
void modificar_horario (horarios **arr_horarios, int *n) {

int dia, hora, i, bol=1, num = *n;
char id_p[IDP], id_m[IDM], gr[GRUPO];
listar_horarios_admin(arr_horarios, n);

while (bol != 0) {
  printf("Escriba campo a campo el horario que quiera modificar\nIntroduzca identificador de profesor: \n");
  scanf("%s", id_p);
  printf("Introduzca dia: \n");
  scanf("%d", &dia);
  printf("Introduzca hora: \n");
  scanf("%d", &hora);
  printf("Introduzca hora: \n");
  scanf("%s", id_m);
  printf("Introduzcamateria: \n");
  scanf("%s", gr);
  for(i=0; i<num; i++) {
    if (strcmp (arr_horarios[i]->id_prof, id_p) == 0 && arr_horarios[i]->dia_clase == dia && arr_horarios[i]->hora_clase == hora && strcmp(arr_horarios[i]->id_materia, id_m) && strcmp(arr_horarios[i]->grupo, gr)) {
      bol--;
      break;
    }
  }
}

memset(arr_horarios[i]->id_prof,'\0', IDP);
memset(arr_horarios[i]->id_materia, '\0', IDM);
memset(arr_horarios[i]->grupo, '\0', GRUPO);

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

/*
  Cabecera: horarios **arr_horarios, int *n
  Precondición: vector de puntero a estructura inicializado
  Postcondición: escribe toda la información del vector rn un fichero de texto
*/
void volcado_horarios(horarios **arr_horarios, int *n) {

int i, n_horarios= *n;
FILE * fichero = fopen("horarios.txt", "w");

if (fichero == NULL){
  puts(ANSI_COLOR_RED);
  puts("Error fatal: El fichero con la informacion no existe.\n\n");
  puts(ANSI_COLOR_RESET);
  return;
}

for (i = 0; i < n_horarios; i++) {
  fprintf(fichero, "%s-%d-%d-%s-%s\n", arr_horarios[i]->id_prof, arr_horarios[i]->dia_clase, arr_horarios[i]->hora_clase, arr_horarios[i]->id_materia, arr_horarios[i]->grupo);
}
fclose(fichero);

}

/*
  Cabecera: horarios **arr_horarios, int *n, materias **arr_materias, int n_materias, int arr_horas_mat
  Precondición: arr_horarios, arr_materias y n inicializados
  Postcondición: devuelve un vector con las horas en las que se imparta una determinada materia
*/
void horas_materia (horarios **arr_horarios, int *n, materias **arr_materias, int n_materias, int arr_horas_mat[]) {

    int i, j= 0, k;

    for(i=0; i < *n; i++) {
        if (strcmp (arr_materias[n_materias]->id_materia, arr_horarios[i]->id_materia) == 0){
          arr_horas_mat[j] = arr_horarios[i]->hora_clase;
          j++;
        }
    }
    for (i = 1; i < j; ++i) {
      for (k = 0; k < i; ++k) {
        if (arr_horas_mat[k] == arr_horas_mat[i] && arr_horas_mat[k] != 0) {
          arr_horas_mat[k] = 0;
        }
      }
    }
    for (i = 0; i < j-1; ++i) {
      if (arr_horas_mat[i] == 0 && arr_horas_mat[i+1] != 0) {
        arr_horas_mat[i] = arr_horas_mat[i+1];
        arr_horas_mat[i+1] = 0;
      }
      else {
        k = i;
        while(arr_horas_mat[i] == 0 && i < j-1)
          i++;
        arr_horas_mat[k] = arr_horas_mat[i];
        arr_horas_mat[i] = 0;
      }
    }

    i=0;

    while(arr_horas_mat[i] != 0)
      i++;

    arr_horas_mat = realloc(arr_horas_mat, (j-i) * sizeof (int*));
    arr_horas_mat = malloc (sizeof(int));
}


/*
 *int main(){
 *
 *    int size = cuenta_lineas("horarios.txt");
 *    horarios * array_horarios[size];
 *
 *    menu_horarios(array_horarios, &size);
 *    return 0;
 *}
 */
