#include <stdlib.h>
#include <stdio.h>

alumnos* Carga_Alumno();
void Guardar_Alumno(alumnos *);
void Anadir_Alumno(alumnos *);
void Listar_Alumno(alumnos *);
void Modificar_Alumno(alumnos *);
void Baja_Alumno(alumnos *);
void menu_alumnos();
void ficha_alum(char*);

/*
  Cabecera: char*
  Precondición: cadena que se le pasa debe coincidir con un alumno existente
  Postcondición: dado el identificador de un alumno imprime su nombre
*/
void listar_alumno_prof(char*)

