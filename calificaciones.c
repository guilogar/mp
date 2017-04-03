#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

void cargar_calificaciones(FILE * f, calificaciones *list_calificaciones);
void buscar_por_materia(calificaciones *list_calificaciones, int id_materia, calificaciones *new_list_calificaciones);
void buscar_por_alumno(calificaciones *list_calificaciones, int id_alumno, calificaciones *new_list_calificaciones);
void volcado_calificaciones(FILE * f, calificaciones *list_calificaciones, char *nom_file);
void menu_calificaciones(calificaciones *list_calificaciones, int id_alumno);
int get_line (char *prmpt, char *buff, size_t sz);
void print_calificaciones_por_alumno(calificaciones *list_calificaciones, int id_alumno);
void print_calificaciones_por_materia(calificaciones *list_calificaciones, int id_materia);

void modificar_calificacion(calificaciones *list_calificaciones, int id_calificacion);
void borrar_calificacion(calificaciones *list_calificaciones, int id_calificacion);


int get_line (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    buff[strlen(buff)-1] = '\0';
    return OK;
}


void cargar_calificaciones(FILE * f, calificaciones *list_calificaciones) {
    char cadena[100];
    int i = 0;
    
    if((f = fopen("calificaciones.txt", "r")) == NULL) {
        puts(ANSI_COLOR_RED);
        puts("Error fatal: El fichero con la información no existe.\n");
        puts("Puede que parte del programa no funcione correctamente sin esta información.\n\n");
        puts(ANSI_COLOR_RESET);
        return;
    }
    
    while (fgets(cadena, 100, f) != NULL) {
        strcpy(list_calificaciones[i].fecha_calif, strtok(cadena,"-"));
        strcpy(list_calificaciones[i].descrip_calif, strtok(NULL,"-"));
        strcpy(list_calificaciones[i].id_materia, strtok(NULL,"-"));
        strcpy(list_calificaciones[i].id_alum, strtok(NULL,"-"));
        list_calificaciones[i].valor_calif = atoi(strtok(NULL,"-"));
        
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
    
    f = fopen(nom_file, "w");
    
    char cadena[2][100];
    char aux_valor_calif[20];
    int i= 0;
    
    for (i = 0; i < 2; i++) {
        memset(cadena, 0, strlen(cadena[i]));
        
        strcat(cadena[i], list_calificaciones[i].fecha_calif);
        strcat(cadena[i], "-");
        
        strcat(cadena[i], list_calificaciones[i].descrip_calif);
        strcat(cadena[i], "-");
        
        strcat(cadena[i], list_calificaciones[i].id_materia);
        strcat(cadena[i], "-");
        
        strcat(cadena[i], list_calificaciones[i].id_alum);
        strcat(cadena[i], "-");
        
        sprintf(aux_valor_calif, "%d", list_calificaciones[i].valor_calif);
        
        strcat(cadena[i], aux_valor_calif);
        strcat(cadena[i], "\n");
        
        /*puts(cadena[i]);*/
        fprintf(f, "%s", cadena[i]);
    }
    fclose(f);
}

void print_calificaciones_por_materia(calificaciones *list_calificaciones, int id_materia) {
    
    int i;
    for (i = 0; i <= (sizeof(*list_calificaciones) / sizeof(calificaciones)); i++) {
        
        if (atoi(list_calificaciones[i].id_materia) == id_materia) {
            printf("%dº) ", i+1);
            printf("%s-", list_calificaciones[i].fecha_calif);
            printf("%s-", list_calificaciones[i].descrip_calif);
            printf("%s-", list_calificaciones[i].id_materia);
            printf("%s-", list_calificaciones[i].id_alum);
            printf("%d", list_calificaciones[i].valor_calif);
            puts("");
        }
    }
}
void print_calificaciones_por_alumno(calificaciones *list_calificaciones, int id_alumno) {
    
    int i;
    for (i = 0; i <= (sizeof(*list_calificaciones) / sizeof(calificaciones)); i++) {
        
        if (atoi(list_calificaciones[i].id_alum) == id_alumno) {
            printf("%dº) ", i+1);
            printf("%s-", list_calificaciones[i].fecha_calif);
            printf("%s-", list_calificaciones[i].descrip_calif);
            printf("%s-", list_calificaciones[i].id_materia);
            printf("%s-", list_calificaciones[i].id_alum);
            printf("%d", list_calificaciones[i].valor_calif);
            puts("");
        }
    }
}

void menu_calificaciones(calificaciones *list_calificaciones, int id_alumno) {
    
    int rc;
    char buff[100];
    char buff_num_calif[100];
    
    puts("Bienvenido al menu de modificar calificaciones.");
    puts("===============================================");
    puts("");
    
    do {
        puts("Opciones.");
        puts("1º) Modificar Calificación existente.");
        puts("2º) Borrar una Calificación.");
        puts("3º) Añadir una nueva Calificación.");
        puts("4º) Salir de este menú.");
        puts("");
        
        rc = get_line ("Eliga una opción> ", buff, sizeof(buff));
        puts("");
        /*
         *switch (rc) {
         *    case OK: break;
         *    case NO_INPUT:
         *        printf ("\nNo input\n");
         *      break;
         *    case TOO_LONG:
         *        printf ("Input too long [%s]\n", buff);
         *      break;
         *    default:
         *        puts("Error desconocido.");
         *}
         */
        switch (atoi(buff)) {
            case 1: {
                    puts("Se muestran a continuación todas las calificaciones del alumno.");
                    puts("===============================================================");
                    puts("");
                    print_calificaciones_por_alumno(list_calificaciones, id_alumno);
                    puts("");
                    get_line ("Eliga una calificación para modificar (0 para no modificar ninguna)> ", buff_num_calif, sizeof(buff_num_calif));
                    puts("");
                    modificar_calificacion(list_calificaciones, atoi(buff_num_calif)-1);
                }
              break;
            case 2:
                    puts("Se muestran a continuación todas las calificaciones del alumno.");
                    puts("===============================================================");
                    puts("");
                    print_calificaciones_por_alumno(list_calificaciones, id_alumno);
                    puts("");
                    get_line ("Eliga una calificación para borrar (0 para no borrar ninguna)> ", buff_num_calif, sizeof(buff_num_calif));
                    puts("");
                    /*borrar_calificacion(list_calificaciones, atoi(buff_num_calif)-1);*/
              break;
            case 3:
                printf ("Input too long [%s]\n", buff);
              break;
            case 4: break;
            default:
                puts("Error en la selección de la opción. Intentelo otra vez.");
        }
    } while (rc != OK || atoi(buff) != 4);
    
    return;
}

void modificar_calificacion(calificaciones *list_calificaciones, int id_calificacion) {
    
    if(id_calificacion < 0) {
        return;
    }
    if(id_calificacion > (sizeof(*list_calificaciones) / sizeof(calificaciones))) {
        puts("El alumno no tiene tantas calificaciones. Escoje un número que este entre 1 y el número maximo de calificaciones que posea.");
        puts("");
        return;
    }
    char new_value_calif[100];
    
    puts("Información Calificación");
    puts("=========================");
    puts("");
    
    printf("Fecha de Calificación => %s.\n\n", list_calificaciones[id_calificacion].fecha_calif);
    printf("Descripción de la Calificación => %s.\n\n", list_calificaciones[id_calificacion].descrip_calif);
    printf("Id de la Materia => %s.\n\n", list_calificaciones[id_calificacion].id_materia);
    printf("Id Alumno => %s.\n\n", list_calificaciones[id_calificacion].id_alum);
    printf("Valor de la Calificación => %d.\n\n", list_calificaciones[id_calificacion].valor_calif);
    puts("");
    
    get_line ("Inserte el nuevo valor de la calificación> ", new_value_calif, sizeof(new_value_calif));
    puts("");
    if(atoi(new_value_calif) < 0 || atoi(new_value_calif) > 10) {
        puts("No se admite como nota un valor inferior a 0 o superior a 10. Vuelva a intentarlo.");
        puts("");
        modificar_calificacion(list_calificaciones, id_calificacion);
        return;
    }
    
    list_calificaciones[id_calificacion].valor_calif = atoi(new_value_calif);
    return;
}
int main(void) {
    FILE * f;
    
    // Se puede utilizar el operador -> para trabajar con estructuras y uniones.
    /*puts(new_list_calificaciones[0].descrip_calif);*/
    
    calificaciones list_calificaciones[2];
    calificaciones new_list_calificaciones[2];
    calificaciones new_list_calificaciones2[2];
    
    cargar_calificaciones(f, list_calificaciones);
    buscar_por_alumno(list_calificaciones, 342312, new_list_calificaciones);
    
    /*buscar_por_materia(list_calificaciones, 2,  new_list_calificaciones);*/
    /*volcado_calificaciones(f, list_calificaciones, "calificaciones.txt");*/
    
    menu_calificaciones(new_list_calificaciones, 342312);
    
    
    return 0;
}

