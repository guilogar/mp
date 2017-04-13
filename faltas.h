#include <stdlib.h>
#ifndef _CALIFICACIONES
#define _CALIFICACIONES

void cargar_calificaciones (FILE * f, calificaciones *list_calificaciones);
void volcado_calificaciones(FILE * f, calificaciones *list_calificaciones, char *nom_file, int longitud_array);

calificaciones * menu_calificaciones(calificaciones *list_calificaciones, int *array_datos, int longitud_array);

calificaciones * anadir_calificacion   (calificaciones ** list_calificaciones, char datos[][100], int *longitud_array);
void             modificar_calificacion(calificaciones *  list_calificaciones, char datos[][100], int  longitud_array);
calificaciones * borrar_calificacion   (calificaciones ** list_calificaciones, char datos[][100], int *longitud_array);

void print_calificaciones_por_alumno (calificaciones *list_calificaciones, int id_alumno,  int longitud_array);
void print_calificaciones_por_materia(calificaciones *list_calificaciones, int id_materia, int longitud_array);
void print_calificaciones_criba(calificaciones *list_calificaciones, int *array_datos, int longitud_array);

void buscar_por_materia(calificaciones *list_calificaciones, int id_materia, calificaciones *new_list_calificaciones, int longitud_array);
void buscar_por_alumno (calificaciones *list_calificaciones, int id_alumno,  calificaciones *new_list_calificaciones, int longitud_array);

int nota_valida(int nota, char *msg_error);
int get_longitud_array_calificaciones();

#endif
