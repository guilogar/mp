#ifndef MATRICULA_H
#define MATRICULA_H
#include "estructuras.h"


//Cabecera: void mostrar(char idmateria, matriculas mat[], alumnos alum[])
//Precondición: Estructura matriculas y alumnos creada, con todos los datos cargados.
//Postcondición: Muestra todos los alumnos matriculados en una asignatura junto con sus datos.
void mostrar(char* idmateria, matriculas mat[], alumnos alum[]);

//Cabecera: void cargar_matriculas(FILE * f, matriculas mat[])
//Precondición: Estructura matriculas y alumnos creada, el fichero de matriculas.txt en la misma carpeta
//Postcondición: Vuelca todos los datos de las matriculas de los alumnos en la estructura.
void cargar_matriculas(matriculas mat[]);

//Cabecera: int contaralumnos(matriculas mat[])
//Precondición: Estructura matriculas y alumnos creada, con todos los datos cargados.
//Postcondición: Cuenta los alumnos matriculados en las asignaturas.
int contaralumnos(matriculas mat[]);
#endif /* MATRICULA_H */

