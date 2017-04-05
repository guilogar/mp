#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estructuras.h"
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

void cargar_calificaciones(FILE * f, calificaciones *list_calificaciones);
void buscar_por_materia(calificaciones *list_calificaciones, int id_materia, calificaciones *new_list_calificaciones, int longitud_array);
void buscar_por_alumno(calificaciones *list_calificaciones, int id_alumno, calificaciones *new_list_calificaciones, int longitud_array);
void volcado_calificaciones(FILE * f, calificaciones *list_calificaciones, char *nom_file, int longitud_array);
void menu_calificaciones(calificaciones *list_calificaciones, int id_alumno, int longitud_array);
void print_calificaciones_por_alumno(calificaciones *list_calificaciones, int id_alumno, int longitud_array);
void print_calificaciones_por_materia(calificaciones *list_calificaciones, int id_materia, int longitud_array);
void modificar_calificacion(calificaciones * list_calificaciones, char datos[][100], int longitud_array);
int borrar_calificacion(calificaciones ** list_calificaciones, char datos[][100], int longitud_array);

int anadir_calificacion(calificaciones ** list_calificaciones, char datos[][100], int longitud_array);

int get_line (char *prmpt, char *buff, size_t sz);

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

void buscar_por_materia(calificaciones *list_calificaciones, int id_materia, calificaciones *new_list_calificaciones, int longitud_array) {
    int i, j = 0;
    
    for (i = 0; i <= longitud_array; i++) {
        //Asi se convierte una cadena a entero. Hay funciones parecidas para
        //hacer conversiones de cadena a otro tipos numericos.
        //atoi(list_calificaciones[i].id_materia);
        
        if (atoi(list_calificaciones[i].id_materia) == id_materia) {
            new_list_calificaciones[j++] = list_calificaciones[i];
        }
    }
}

void buscar_por_alumno(calificaciones *list_calificaciones, int id_alumno, calificaciones *new_list_calificaciones, int longitud_array) {
    int i, j = 0;
    
    for (i = 0; i <= longitud_array; i++) {
        //Asi se convierte una cadena a entero. Hay funciones parecidas para
        //hacer conversiones de cadena a otro tipos numericos.
        //atoi(list_calificaciones[i].id_materia);
        
        if (atoi(list_calificaciones[i].id_alum) == id_alumno) {
            new_list_calificaciones[j++] = list_calificaciones[i];
        }
    }
}

void volcado_calificaciones(FILE * f, calificaciones *list_calificaciones, char *nom_file, int longitud_array) {
    
    f = fopen(nom_file, "w");
    
    char cadena[longitud_array][100];
    char aux_valor_calif[20];
    int i= 0;
    
    for (i = 0; i < longitud_array; i++) {
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

void print_calificaciones_por_materia(calificaciones *list_calificaciones, int id_materia, int longitud_array) {
    
    int i;
    for (i = 0; i <= longitud_array; i++) {
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
void print_calificaciones_por_alumno(calificaciones *list_calificaciones, int id_alumno, int longitud_array) {
    
    int i;
    for (i = 0; i < longitud_array; i++) {
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

void menu_calificaciones(calificaciones *list_calificaciones, int id_alumno, int longitud_array) {
    
    int rc;
    char buff[100];
    
    char datos_calif[5][100];
    char buff_fecha_calif[100];
    char buff_id_materia[100];
    char buff_id_alum[100];
    char buff_descrip_calif[100];
    char buff_valor_calif[100];
    
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
                    print_calificaciones_por_alumno(list_calificaciones, id_alumno, longitud_array);
                    puts("");
                    get_line ("Escriba una fecha de calificación para modificar (DD/MM/YYYY)> ", buff_fecha_calif, sizeof(buff_fecha_calif));
                    get_line ("Escriba el id de la materia de la calificación a modificar> ", buff_id_materia, sizeof(buff_id_materia));
                    get_line ("Escriba el id del alumno de la calificación a modificar> ", buff_id_alum, sizeof(buff_id_alum));
                    puts("");
                    strcpy(datos_calif[0], buff_fecha_calif);
                    strcpy(datos_calif[1], buff_id_materia);
                    strcpy(datos_calif[2], buff_id_alum);
                    
                    modificar_calificacion(list_calificaciones, datos_calif, longitud_array);
                }
              break;
            case 2:
                    puts("Se muestran a continuación todas las calificaciones del alumno.");
                    puts("===============================================================");
                    puts("");
                    print_calificaciones_por_alumno(list_calificaciones, id_alumno, longitud_array);
                    puts("");
                    get_line ("Escriba una fecha de calificación para borrar (DD/MM/YYYY)> ", buff_fecha_calif, sizeof(buff_fecha_calif));
                    get_line ("Escriba el id de la materia de la calificación a borrar> ", buff_id_materia, sizeof(buff_id_materia));
                    get_line ("Escriba el id del alumno de la calificación a borrar> ", buff_id_alum, sizeof(buff_id_alum));
                    puts("");
                    strcpy(datos_calif[0], buff_fecha_calif);
                    strcpy(datos_calif[1], buff_id_materia);
                    strcpy(datos_calif[2], buff_id_alum);
                    
                    longitud_array = borrar_calificacion(&list_calificaciones, datos_calif, longitud_array);
              break;
            case 3:
                    puts("");
                    get_line ("Escriba una fecha para añadir una calificación (DD/MM/YYYY)> ", buff_fecha_calif, sizeof(buff_fecha_calif));
                    get_line ("Escriba el id de la materia para añadir la calificación> ", buff_id_materia, sizeof(buff_id_materia));
                    get_line ("Escriba el id del alumno para añadir la calificación> ", buff_id_alum, sizeof(buff_id_alum));
                    get_line ("Escriba la descripción para añadir la calificación> ", buff_descrip_calif, sizeof(buff_descrip_calif));
                    get_line ("Escriba la nota para añadir la calificación> ", buff_valor_calif, sizeof(buff_valor_calif));
                    puts("");
                    strcpy(datos_calif[0], buff_fecha_calif);
                    strcpy(datos_calif[1], buff_id_materia);
                    strcpy(datos_calif[2], buff_id_alum);
                    strcpy(datos_calif[3], buff_descrip_calif);
                    strcpy(datos_calif[4], buff_valor_calif);
                    
                    longitud_array = anadir_calificacion(&list_calificaciones, datos_calif, longitud_array);
              break;
            case 4: break;
            default:
                puts("Error en la selección de la opción. Intentelo otra vez.");
        }
    } while (rc != OK || atoi(buff) != 4);
    
    return;
}

int anadir_calificacion(calificaciones **list_calificaciones, char datos[][100], int longitud_array) {
    
    puts("Información Calificación");
    puts("=========================");
    puts("");
    
    printf("Fecha de Calificación => %s.\n\n", datos[0]);
    printf("Descripción de la Calificación => %s.\n\n", datos[1]);
    printf("Id de la Materia => %s.\n\n", datos[2]);
    printf("Id Alumno => %s.\n\n", datos[3]);
    printf("Valor de la Calificación => %d.\n\n", atoi(datos[4]));
    puts("");
    char election[100];
    
    get_line ("¿Está seguro de que quiere añadir esta calificación al alumno?(y/n)> ", election, sizeof(election));
    if(strcmp("y", election) == 0 || strcmp("yes", election)) {
        printf("--------%d----------\n", --longitud_array);
        *list_calificaciones = (calificaciones *) realloc(*list_calificaciones, (++longitud_array));
        printf("--------%d----------\n", longitud_array);
        
        strcpy(list_calificaciones[longitud_array-1]->fecha_calif, datos[0]);
        strcpy(list_calificaciones[longitud_array-1]->id_materia, datos[1]);
        strcpy(list_calificaciones[longitud_array-1]->id_alum, datos[2]);
        strcpy(list_calificaciones[longitud_array-1]->descrip_calif, datos[3]);
        list_calificaciones[longitud_array-1]->valor_calif = atoi(datos[4]);
    }
    
    return longitud_array;
}

int borrar_calificacion(calificaciones **list_calificaciones, char datos[][100], int longitud_array) {
    int id_calificacion = -1, i;
    for (int i = 0; i < longitud_array; i++) {
        if(strcmp(datos[0], (*list_calificaciones + i)->fecha_calif) == 0 &&
           atoi(list_calificaciones[i]->id_materia) == atoi(datos[1]) &&
           atoi(list_calificaciones[i]->id_alum) == atoi(datos[2])      ) {
            
            id_calificacion = i;
            break;
        }
    }
    if(id_calificacion < 0) {
        puts("Calificación no encontrada. Vuelva a intentarlo.");
        puts("");
        return longitud_array;
    }
    char election[100];
    
    puts("Información Calificación");
    puts("=========================");
    puts("");
    
    printf("Fecha de Calificación => %s.\n\n", list_calificaciones[id_calificacion]->fecha_calif);
    printf("Descripción de la Calificación => %s.\n\n", list_calificaciones[id_calificacion]->descrip_calif);
    printf("Id de la Materia => %s.\n\n", list_calificaciones[id_calificacion]->id_materia);
    printf("Id Alumno => %s.\n\n", list_calificaciones[id_calificacion]->id_alum);
    printf("Valor de la Calificación => %d.\n\n", list_calificaciones[id_calificacion]->valor_calif);
    puts("");
    
    get_line ("¿Está seguro de que quiere borrar esta calificación del alumno?(y/n)> ", election, sizeof(election));
    if(strcmp("y", election) == 0 || strcmp("yes", election)) {
        for(i = id_calificacion; i < longitud_array; i++) {
            list_calificaciones[id_calificacion] = list_calificaciones[id_calificacion+1];
        }
    }
    
    *list_calificaciones = (calificaciones *) realloc(*list_calificaciones, (--longitud_array));
    return longitud_array;
}

void modificar_calificacion(calificaciones *list_calificaciones, char datos[][100], int longitud_array) {
    int id_calificacion = -1, i;
    for (int i= 0; i < longitud_array; i++) {
        
        if(strcmp(datos[0], list_calificaciones[i].fecha_calif) == 0 &&
           atoi(list_calificaciones[i].id_materia) == atoi(datos[1]) &&
           atoi(list_calificaciones[i].id_alum) == atoi(datos[2])      ) {
            
            id_calificacion = i;
            break;
        }
    }
    if(id_calificacion < 0) {
        puts("Calificación no encontrada. Vuelva a intentarlo.");
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
        modificar_calificacion(list_calificaciones, datos, longitud_array);
        return;
    }
    
    list_calificaciones[id_calificacion].valor_calif = atoi(new_value_calif);
}
int main(void) {
    FILE * f;
    
    // Se puede utilizar el operador -> para trabajar con estructuras y uniones.
    /*puts(new_list_calificaciones[0].descrip_calif);*/
    
    calificaciones list_calificaciones[9];
    
    cargar_calificaciones(f, list_calificaciones);
    
    /*buscar_por_alumno(list_calificaciones, 342312, new_list_calificaciones);*/
    /*buscar_por_materia(list_calificaciones, 2,  new_list_calificaciones);*/
    /*volcado_calificaciones(f, list_calificaciones, "calificaciones.txt");*/
    
    menu_calificaciones(list_calificaciones, 342312, (sizeof(list_calificaciones) / sizeof(calificaciones)));
    
    return 0;
}

