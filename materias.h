#ifndef MATERIAS_H
#define MATERIAS_H
#include "estructuras.h"

//Cabecera: int contarmaterias(materias *mater)
//Precondición: Estructura materias creada, con todos los datos cargados.
//Postcondición: Devuelve el numero de materias de la estructura.
int contarmaterias(materias *mater);


//Cabecera: char* nombre_id(char *idmateria, materias *mater)
//Precondición: Estructura materias creada, con todos los datos cargados y el id de una materia pasada por parametro.
//Postcondición: Devuelve el nombre de una materia que le pasamos por parametro.
char* nombre_id(char *idmateria, materias *mater);

//Cabecera: void menu_materias(materias *mater)
//Precondición: Estructura materias creada, con todos los datos cargados.
//Postcondición: Menu con todas las funciones pedias para este modulo.
void menu_materias(materias *mater);

#endif /* MATERIAS_H */

