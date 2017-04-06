#include <stdlib.h>
#include <stdio.h>

alumnos* Carga_Alumno();
void Guardar_Alumno(alumnos *);
void Anadir_Alumno(alumnos *);
void Listar_Alumno(alumnos *);
void Modificar_Alumno(alumnos *);
void Baja_Alumno(alumnos *);
void menu_alumnos();
void ficha_alum(alumnos *,char*);

/*
  Cabecera: alumnos*, char*
  Precondición: existe estructura y contiene elementos, cadena debe coincidir con un alumno existente
  Postcondición: dado el identificador de un alumno devuelve su nombre
*/
char* listar_alumnos_prof(alumnos *,char*);

