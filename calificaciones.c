#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
//===================================
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//===================================

void cargar_calificaciones(FILE * f, calificaciones *list_calificaciones);
calificaciones * buscar_por_materia(calificaciones *list_calificaciones, int id_materia);
calificaciones * buscar_por_alumno(calificaciones *list_calificaciones, int id_alumno);
void volcado_calificaciones(FILE * f, calificaciones *list_calificaciones);

void cargar_calificaciones(FILE * f, calificaciones *list_calificaciones) {
    
    char cadena[100];
    int i = 0;
    
    if((f = fopen("calificaciones.txt", "r")) == NULL) {
        puts(ANSI_COLOR_RED);
        puts("Error fatal: El fichero con la información no existe.\n\n");
        puts(ANSI_COLOR_RESET);
        return;
    }
    
    while (fgets(cadena, 100, f) != NULL) {
        strcpy(list_calificaciones[i].fecha_calif, strtok(cadena,"-"));
        strcpy(list_calificaciones[i].descrip_calif, strtok(NULL,"-"));
        strcpy(list_calificaciones[i].id_materia, strtok(NULL,"-"));
        strcpy(list_calificaciones[i].id_alum, strtok(NULL,"-"));
        list_calificaciones[i].valor_calif = atoi(strtok(NULL,"-"));
        
        puts(list_calificaciones[i].fecha_calif);
        puts(list_calificaciones[i].descrip_calif);
        puts(list_calificaciones[i].id_materia);
        puts(list_calificaciones[i].id_alum);
        printf("%i\n", list_calificaciones[i].valor_calif);
        
        i++;
    }
}

calificaciones * buscar_por_materia(calificaciones *list_calificaciones, int id_materia) {
    int i, j = 0;
    static calificaciones new_list_calificaciones[2];
    printf("%li\n", (sizeof(*list_calificaciones) / sizeof(calificaciones)));
    
    for (i = 0; i <= (sizeof(*list_calificaciones) / sizeof(calificaciones)); i++) {
        //Asi se convierte una cadena a entero. Hay funciones parecidas para
        //hacer conversiones de cadena a otro tipos numericos.
        //atoi(list_calificaciones[i].id_materia);
        
        if (atoi(list_calificaciones[i].id_materia) == id_materia) {
            new_list_calificaciones[j++] = list_calificaciones[i];
        }
    }

    return new_list_calificaciones;
}

calificaciones * buscar_por_alumno(calificaciones *list_calificaciones, int id_alumno) {
    int i, j = 0;
    static calificaciones new_list_calificaciones[2];
    printf("%li\n", (sizeof(*list_calificaciones) / sizeof(calificaciones)));
    
    for (i = 0; i <= (sizeof(*list_calificaciones) / sizeof(calificaciones)); i++) {
        //Asi se convierte una cadena a entero. Hay funciones parecidas para
        //hacer conversiones de cadena a otro tipos numericos.
        //atoi(list_calificaciones[i].id_materia);
        
        if (atoi(list_calificaciones[i].id_alum) == id_alumno) {
            new_list_calificaciones[j++] = list_calificaciones[i];
        }
    }

    return new_list_calificaciones;
}


int main(void) {
    FILE * f;
    
    calificaciones list_calificaciones[2];
    calificaciones *new_list_calificaciones[2];
    
    cargar_calificaciones(f, list_calificaciones);
    
    *new_list_calificaciones = buscar_por_materia(list_calificaciones, 2);
    
    // Se puede utilizar el operador -> para trabajar con estructuras y uniones.
    /*puts(new_list_calificaciones[0] -> descrip_calif);*/
    return 0;
}

