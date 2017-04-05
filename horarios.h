#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _HORARIOS
#define _HORARIOS
#define GRUPO 11
#define IDP 4
#define IDM 5
#define MAx_LINEA 30

void menu_horarios();

/*
   Cabecera: char *, horario *
   Precondicion: vectores declarados e inicializados
   Postcondicion: lee una linea y guardo todos sus atributos en una
   estructura horario
*/
void leer_horario (char * linea, horarios * h);

/*
	Cabecera: horario **
	Precondición: puntero a vector de estructura declarado e inicializado
	Postcondición: Lee todos los horarios que se encuetran en el fichero horarios.tt
	y los guarda en un vector de punteros a estructura tipo horario
*/
int leer_horarios (horarios ** arr);

/*
  Cabecera: horario ** arr, int n, usuarios id
  Precondición: vector que apunta a estructura inicializado
  Postcondición: lista todos los horarios de un profesor
*/
void listar_horarios_prof (horarios ** arr, int n, usuarios id);

/*
  Cabecera: horario ** arr, int n
  Precondición: vector que apunta a estructura inicializado
  Postcondición: lista todos los horarios de todos los profesores
*/
void listar_horarios_admin (horarios ** arr, int n);

/*
  Cabecera: horarios **arr_horarios, int n
  Precondición: vector que apunta a estructuras inicializado, y nunero de datos contabilizado
  Postcondición: Permite añadir un nuevo horario a un determinado usuario del sistema
*/
void añadir_horario (horarios **arr_horarios, int n);

/*
  Cabecera: horarios **arr_horarios, int n
  Precondición: vector de punteros a estructura inicializado
  Postcondición: elimina un horario de la lista.
*/
void eliminar_horario (horarios **arr_horarios, int n);

/*
  Cabecera: horarios **arr_horarios, int *n
  Precondición: vector de puntero a estructura incializado
  Postcondición: modifica los parametros de un determinado horario
*/
void modificar_horario (horarios **arr_horarios, int *n);

/*
  Cabecera: horarios **arr_horarios, int *n
  Precondición: vector de puntero a estructura inicializado
  Postcondición: escribe toda la información del vector rn un fichero de texto
*/
void volcado_horarios(horarios **arr_horarios, int *n);

#endif
