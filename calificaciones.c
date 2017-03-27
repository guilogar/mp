#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

void cargar_calificaciones(FILE * f, calificaciones *list_calificaciones);
void buscar_por_materia(calificaciones *list_calificaciones, int id_materia, calificaciones *new_list_calificaciones);
void buscar_por_alumno(calificaciones *list_calificaciones, int id_alumno, calificaciones *new_list_calificaciones);
void volcado_calificaciones(FILE * f, calificaciones *list_calificaciones, char *nom_file);

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
        
        /*
         *puts(list_calificaciones[i].fecha_calif);
         *puts(list_calificaciones[i].descrip_calif);
         *puts(list_calificaciones[i].id_materia);
         *puts(list_calificaciones[i].id_alum);
         *printf("%i\n", list_calificaciones[i].valor_calif);
         */
        
        i++;
    }
}

void buscar_por_materia(calificaciones *list_calificaciones, int id_materia, calificaciones *new_list_calificaciones) {
    int i, j = 0;
    
    for (i = 0; i <= (sizeof(*list_calificaciones) / sizeof(calificaciones)); i++) {
        //Asi se convierte una cadena a entero. Hay funciones parecidas para
        //hacer conversiones de cadena a otro tipos numericos.
        //atoi(list_calificaciones[i].id_materia);
        
        if (atoi(list_calificaciones[i].id_materia) == id_materia) {
            new_list_calificaciones[j++] = list_calificaciones[i];
        }
    }
}

void buscar_por_alumno(calificaciones *list_calificaciones, int id_alumno, calificaciones *new_list_calificaciones) {
    int i, j = 0;
    
    for (i = 0; i <= (sizeof(*list_calificaciones) / sizeof(calificaciones)); i++) {
        //Asi se convierte una cadena a entero. Hay funciones parecidas para
        //hacer conversiones de cadena a otro tipos numericos.
        //atoi(list_calificaciones[i].id_materia);
        
        if (atoi(list_calificaciones[i].id_alum) == id_alumno) {
            new_list_calificaciones[j++] = list_calificaciones[i];
        }
    }
}

void volcado_calificaciones(FILE * f, calificaciones *list_calificaciones, char *nom_file) {
    
    f = fopen(nom_file, "a+");
    
    char cadena[100];
    int i= 0;
    
    for (i = 0; i < 2; i++) {
        strcat(cadena, list_calificaciones[i].fecha_calif);
        strcat(cadena, list_calificaciones[i].descrip_calif);
        strcat(cadena, list_calificaciones[i].id_materia);
        strcat(cadena, list_calificaciones[i].id_alum);
        strcat(cadena, list_calificaciones[i].valor_calif);
    }

}

int main(void) {
    FILE * f;
    
    calificaciones list_calificaciones[2];
    calificaciones new_list_calificaciones[2];
    calificaciones new_list_calificaciones2[2];
    
    cargar_calificaciones(f, list_calificaciones);
    
    buscar_por_materia(list_calificaciones, 2,  new_list_calificaciones);
    buscar_por_alumno(list_calificaciones, 2,  new_list_calificaciones2);
    
    // Se puede utilizar el operador -> para trabajar con estructuras y uniones.
    /*puts(new_list_calificaciones[0].descrip_calif);*/
    return 0;
}

