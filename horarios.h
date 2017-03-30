#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _HORARIOS
#define _HORARIOS
#define MAx_LINEA 36

/*
   Cabecera: char *, horario *
   Precondicion: vectores declarados e inicializados
   Postcondicion: lee una linea y guardo todos sus atributos en una
   estructura horario
*/
void leer_horario (char * linea, horario * h)

/*
	Cabecera: horario **
	Precondición: puntero a vector de estructura declarado e inicializado
	Postcondición: Lee todos los horarios que se encuetran en el fichero horarios.tt
	y los guarda en un vector de punteros a estructura tipo horario
*/ 
int leer_horarios (horarios ** arr)

/*
  Cabecera: horario ** arr, int n, usuarios id
  Precondición: vector que apunta a estructura inicializado
  Postcondición: lista todos los horarios de un profesor
*/
void listar_horarios (horarios ** arr, int n, usuarios id)

/*
  Cabecera: horario ** arr, int n
  Precondición: vector que apunta a estructura inicializado
  Postcondición: lista todos los horarios de todos los profesores
*/
void listar_horarios_admin (horarios ** arr, int n)

#endif