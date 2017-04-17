#ifndef MATRICULA_H
#define MATRICULA_H
#include "estructuras.h"

//Cabecera: void mostrar(char idmateria, matriculas mat[], alumnos alum[])
//Precondición: Estructura matriculas y alumnos creada, con todos los datos cargados.
//Postcondición: Muestra todos los alumnos matriculados en una asignatura junto con sus datos.
void mostrar(char* idmateria, matriculas *mat, alumnos *alum);

//Cabecera: char *leer_campo(int largo)
//Precondición: Pasar por parametro el tamaño de la caden a leer.
//Postcondición: Devuelve una cadena introducida por teclado.
char *leer_campo_m(int largo);

//Cabecera: void matriculas_alum(char *idalu, matriculas *mat, alumnos *alu)
//Precondición: Estructura matriculas y alumnos creada, con todos los datos cargados, y un id de un alumno por parametro.
//Postcondición: Muestra por pantalla las materias matriculas de un alumno en concreto.
void matriculas_alum(char *idalu, matriculas *mat, alumnos *alu);

//Cabecera: void menu_matriculas(char *id_alum, matriculas *mat, materias *mater)
//Precondición: Estructura matriculas y materias creada, con todos los datos cargados y un id de un alumno por parametro
//Postcondición: Menu con todas las funciones pedidas para este modulo.
void menu_matriculas(char *id_alum, matriculas *mat, materias *mater);
void cargar_matriculas(matriculas *mat);
int contar_matriculas(matriculas *mat);
void lista_matricula(char *id_alum, matriculas *mat, materias *mater);
void Anadir_Matricula(matriculas *mat, char *id_alum);
void Modificar_matricula(matriculas *mat, char *id_alum, materias *mater);
void Eliminar_matricula(matriculas *mat, char *id_alum, materias *mater);
void guardar_matriculas(matriculas *mat);

#endif /* MATRICULA_H */

