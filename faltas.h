#include <stdlib.h>
#ifndef _FALTAS
#define _FALTAS

void cargar_faltas(FILE * f, faltas *list_faltas);
void volcado_faltas(FILE * f, faltas *list_faltas, char *nom_file, int longitud_array);

faltas * menu_faltas(faltas *list_faltas, int *array_datos, int longitud_array);

faltas * anadir_falta   (faltas ** list_faltas, char datos[][100], int *longitud_array);
void             modificar_falta(faltas *  list_faltas, char datos[][100], int  longitud_array);
faltas * borrar_falta   (faltas ** list_faltas, char datos[][100], int *longitud_array);

void print_faltas_por_alumno (faltas *list_faltas, int id_alumno,  int longitud_array);
void print_faltas_criba(faltas *list_faltas, int *array_datos, int longitud_array);

//void buscar_por_materia(faltas *list_faltas, int id_materia, faltas *new_list_faltas, int longitud_array);
//void buscar_por_alumno (faltas *list_faltas, int id_alumno,  faltas *new_list_faltas, int longitud_array);

int hora_valida(int hora, char *msg_error);
int get_longitud_array_faltas();

#endif
