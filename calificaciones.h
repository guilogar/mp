#include <stdlib.h>
#ifndef _CALIFICACIONES
#define _CALIFICACIONES

void cargar_calificaciones(FILE * f, calificaciones *list_calificaciones);
void buscar_por_materia(calificaciones *list_calificaciones, int id_materia, calificaciones *new_list_calificaciones);
void buscar_por_alumno(calificaciones *list_calificaciones, int id_alumno, calificaciones *new_list_calificaciones);
void volcado_calificaciones(FILE * f, calificaciones *list_calificaciones, char nom_file);

#endif
