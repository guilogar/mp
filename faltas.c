#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include "estructuras.h"*/
#include "auxiliar.c"
#include "faltas.h"

#define MSG_ERROR_TRAMO_HORARIO "No se admite un tramo horario inferior a 1 o superior a 6. Vuelva a intentarlo."
int LONGITUD_ARRAY_FALTAS;

int get_longitud_array_faltas() {
    return LONGITUD_ARRAY_FALTAS;
}

int hora_valida(int hora, char *msg_error) {
    if(hora < 1 || hora > 6) {
        printf("%s", msg_error);
        puts("");
        return 0;
    }
    return 1;
}

void print_faltas_por_alumno(faltas *list_faltas, int id_alumno, int longitud_array) {
    int i, j = 0;
    for (i = 0; i < longitud_array; i++) {
        if (atoi(list_faltas[i].id_alum) == id_alumno) {
            printf("%dº) ", ++j);
            printf("%s-", list_faltas[i].fecha_falta);
            printf("%d-", list_faltas[i].hora_falta);
            printf("%s-", list_faltas[i].descrip_falta);
            printf("%s-", list_faltas[i].estado_falta);
            printf("%s", list_faltas[i].id_alum);
            puts("");
        }
    }
}

void print_faltas_criba(faltas *list_faltas, int *array_datos, int longitud_array) {
    int i, j = 0;
    for (i = 0; i < longitud_array; i++) {
        if (atoi(list_faltas[i].id_alum) == array_datos[0]) {
            printf("%dº) ", ++j);
            printf("%s-", list_faltas[i].fecha_falta);
            printf("%d-", list_faltas[i].hora_falta);
            printf("%s-", list_faltas[i].descrip_falta);
            printf("%s-", list_faltas[i].estado_falta);
            printf("%s", list_faltas[i].id_alum);
            puts("");
        }
    }
}

faltas * anadir_falta(faltas **list_faltas, char datos[][100], int *longitud_array) {
    
    puts("Información Falta");
    puts("=========================");
    puts("");
    
    printf("Fecha de falta => %s.\n\n", datos[0]);
    printf("Id Alumno => %s.\n\n", datos[1]);
    printf("Estado de la Falta => %s.\n\n", datos[2]);
    printf("Descripción de la Falta => %s.\n\n", datos[3]);
    printf("Hora de la falta => %d.\n\n", atoi(datos[4]));
    puts("");
    char election[100];
    int i;
    
    get_line ("¿Está seguro de que quiere añadir esta calificación al alumno?(y/n)> ", election, sizeof(election));
    if(strcmp("y", election) == 0 || strcmp("yes", election) == 0) {
        
        *(longitud_array) += 1;
        faltas *new_list = (faltas *) calloc(*(longitud_array), sizeof(faltas));
        for(i = 0; i < *longitud_array - 1; i++) {
            if(fecha_correcta((*list_faltas + i)->fecha_falta)) {
                strcpy(new_list[i].fecha_falta, (*list_faltas + i)->fecha_falta);
                
                new_list[i].hora_falta = (*list_faltas + i)->hora_falta;
                
                strcpy(new_list[i].estado_falta, (*list_faltas + i)->estado_falta);
                strcpy(new_list[i].id_alum, (*list_faltas + i)->id_alum);
                strcpy(new_list[i].descrip_falta, (*list_faltas + i)->descrip_falta);
            }
        }
        str_replace(datos[0], "-", "/");
        
        strcpy(new_list[*longitud_array - 1].fecha_falta, datos[0]);
        strcpy(new_list[*longitud_array - 1].id_alum, datos[1]);
        strcpy(new_list[*longitud_array - 1].estado_falta, datos[2]);
        strcpy(new_list[*longitud_array - 1].descrip_falta, datos[3]);
        
        new_list[*longitud_array - 1].hora_falta = atoi(datos[4]);
        
        return new_list;
    }
    return *list_faltas;
}

void modificar_falta(faltas *list_faltas, char datos[][100], int longitud_array) {
    int id_falta = -1, i;
    for (int i= 0; i < longitud_array; i++) {
        if(strcmp(datos[0], list_faltas[i].fecha_falta) == 0 &&
           atoi(list_faltas[i].id_alum) == atoi(datos[1])      ) {
            
            id_falta = i;
            break;
        }
    }
    if(id_falta < 0) {
        puts("Calificación no encontrada. Vuelva a intentarlo.");
        puts("");
        return;
    }
    char new_value_estado_falta[100];
    
    puts("Información Falta");
    puts("=========================");
    puts("");
    
    printf("Fecha de la Falta => %s.\n\n", list_faltas[id_falta].fecha_falta);
    printf("Descripción de la Falta => %s.\n\n", list_faltas[id_falta].descrip_falta);
    printf("Estado de la Falta => %s.\n\n", list_faltas[id_falta].estado_falta);
    printf("Tramo horario => %d.\n\n", list_faltas[id_falta].hora_falta);
    printf("Id Alumno => %s.\n\n", list_faltas[id_falta].id_alum);
    puts("");
    
    get_line ("Inserte el nuevo estado para la falta> ", new_value_estado_falta, sizeof(new_value_estado_falta));
    puts("");
    /*
     *if(!hora_valida(atoi(new_value_calif), MSG_ERROR_NOTA)) {
     *    modificar_calificacion(list_faltas, datos, longitud_array);
     *    return;
     *}
     */
    strcpy(list_faltas[id_falta].estado_falta, new_value_estado_falta);
}

faltas * borrar_falta(faltas **list_faltas, char datos[][100], int *longitud_array) {
    int id_falta = -1, i, j;
    for (int i = 0; i < *(longitud_array); i++) {
        if(strcmp(datos[0], (*list_faltas + i)->fecha_falta) == 0 &&
           atoi((*list_faltas + i)->id_alum) == atoi(datos[1])      ) {
            
            id_falta = i;
            break;
        }
    }
    if(id_falta < 0) {
        puts("Calificación no encontrada. Vuelva a intentarlo.");
        puts("");
        return *list_faltas;
    }
    char election[100];
    
    puts("Información Falta");
    puts("=========================");
    puts("");
    
    printf("Fecha de Falta => %s.\n\n", (*list_faltas +id_falta)->fecha_falta);
    printf("Descripción de la Falta => %s.\n\n", (*list_faltas + id_falta)->descrip_falta);
    printf("Id Alumno => %s.\n\n", (*list_faltas + id_falta)->id_alum);
    printf("Estado falta => %s.\n\n", (*list_faltas + id_falta)->estado_falta);
    printf("Tramo Horario => %d.\n\n", (*list_faltas + id_falta)->hora_falta);
    puts("");
    
    get_line ("¿Está seguro de que quiere borrar esta falta del alumno?(y/n)> ", election, sizeof(election));
    if(strcmp("y", election) == 0 || strcmp("yes", election) == 0) {
        
        *(longitud_array) -= 1;
        faltas *new_list = (faltas *) calloc(*(longitud_array), sizeof(faltas));
        for(i = 0, j = 0; j < *longitud_array; i++, j++) {
            if(i == id_falta) {
                --j;
                continue;
            }
            if(fecha_correcta((*list_faltas + i)->fecha_falta)) {
                strcpy(new_list[j].fecha_falta, (*list_faltas + i)->fecha_falta);
                strcpy(new_list[j].id_alum, (*list_faltas + i)->id_alum);
                strcpy(new_list[j].descrip_falta, (*list_faltas + i)->descrip_falta);
                strcpy(new_list[j].estado_falta, (*list_faltas + i)->estado_falta);
                new_list[j].hora_falta = (*list_faltas + i)->hora_falta;
            }
        }
        
        return new_list;
    }
    
    return *list_faltas;
}

faltas * menu_faltas(faltas *list_faltas, int *array_datos, int longitud_array) {
    
    int rc;
    char buff[100];
    
    char datos_falta[5][100];
    char buff_fecha_falta[100];
    char buff_descrip_falta[100];
    char buff_estado_falta[100];
    char buff_hora_falta[100];
    
    puts("Bienvenido al menu de modificar faltas.");
    puts("===============================================");
    
    do {
        puts("");
        puts("Opciones.");
        puts("1º) Listar faltas.");
        puts("2º) Modificar falta existente.");
        puts("3º) Borrar una falta.");
        puts("4º) Añadir una nueva falta.");
        puts("5º) Salir de este menú.");
        puts("");
        
        rc = get_line ("Eliga una opción> ", buff, sizeof(buff));
        puts("");
        switch (atoi(buff)) {
            case 1: {
                    puts("Se muestran a continuación todas las faltas del alumno.");
                    puts("===============================================================");
                    puts("");
                    print_faltas_criba(list_faltas, array_datos, longitud_array);
                }
              break;
            case 2: {
                    puts("Se muestran a continuación todas las faltas del alumno.");
                    puts("===============================================================");
                    puts("");
                    print_faltas_criba(list_faltas, array_datos, longitud_array);
                    puts("");
                    get_line ("Escriba una fecha de falta para modificar (DD/MM/YYYY)> ", buff_fecha_falta, sizeof(buff_fecha_falta));
                    puts("");
                    str_replace(buff_fecha_falta, "-", "/");
                    strcpy(datos_falta[0], buff_fecha_falta);
                    sprintf(datos_falta[1], "%d", array_datos[0]);
                    sprintf(datos_falta[2], "%d", array_datos[1]);
                    
                    modificar_falta(list_faltas, datos_falta, longitud_array);
                }
              break;
            case 3: {
                    puts("Se muestran a continuación todas las faltas del alumno.");
                    puts("===============================================================");
                    puts("");
                    print_faltas_criba(list_faltas, array_datos, longitud_array);
                    puts("");
                    get_line ("Escriba una fecha de falta para borrar (DD/MM/YYYY)> ", buff_fecha_falta, sizeof(buff_fecha_falta));
                    puts("");
                    str_replace(buff_fecha_falta, "-", "/");
                    strcpy(datos_falta[0], buff_fecha_falta);
                    sprintf(datos_falta[1], "%d", array_datos[0]);
                    sprintf(datos_falta[2], "%d", array_datos[1]);
                    
                    list_faltas= borrar_falta(&list_faltas, datos_falta, &longitud_array);
                }
              break;
            case 4: {
                    puts("");
                    get_line ("Escriba una fecha para añadir una falta (DD/MM/YYYY)> ", buff_fecha_falta, sizeof(buff_fecha_falta));
                    if(!fecha_correcta(buff_fecha_falta)) {
                        continue;
                    }
                    get_line ("Escriba la descripción para añadir la falta> ", buff_descrip_falta, sizeof(buff_descrip_falta));
                    get_line ("Escriba el estado añadir la falta> ", buff_estado_falta, sizeof(buff_estado_falta));
                    get_line ("Escriba la hora para añadir la falta> ", buff_hora_falta, sizeof(buff_hora_falta));
                    if(!hora_valida(atoi(buff_hora_falta), MSG_ERROR_TRAMO_HORARIO)) {
                        continue;
                    }
                    puts("");
                    str_replace(buff_fecha_falta, "-", "/");
                    strcpy(datos_falta[0], buff_fecha_falta);
                    
                    sprintf(datos_falta[1], "%d", array_datos[0]);
                    
                    strcpy(datos_falta[2], buff_estado_falta);
                    strcpy(datos_falta[3], buff_descrip_falta);
                    strcpy(datos_falta[4], buff_hora_falta);
                    
                    list_faltas = anadir_falta(&list_faltas, datos_falta, &longitud_array);
                }
              break;
            case 5: break;
            default:
                puts("Error en la selección de la opción. Intentelo otra vez.");
        }
    } while (rc != OK || atoi(buff) != 5);
    
    int i = 0;
    faltas *new_list = (faltas *) calloc((longitud_array), sizeof(faltas));
    for(i = 0; i < longitud_array; i++) {
        strcpy(new_list[i].fecha_falta, (list_faltas + i)->fecha_falta);
        strcpy(new_list[i].id_alum, (list_faltas + i)->id_alum);
        strcpy(new_list[i].estado_falta, (list_faltas + i)->estado_falta);
        strcpy(new_list[i].descrip_falta, (list_faltas + i)->descrip_falta);
        new_list[i].hora_falta = (list_faltas + i)->hora_falta;
    }
    /*print_faltas_criba(new_list, array_datos, longitud_array);*/
    
    LONGITUD_ARRAY_FALTAS = longitud_array;
    return new_list;
}

void volcado_faltas(FILE * f, faltas *list_faltas, char *nom_file, int longitud_array) {
    puts("");
    f = fopen(nom_file, "w");
    
    char cadena[longitud_array][100];
    char aux_hora_falta[20];
    int i;
    
    for (i = 0; i < longitud_array; i++) {
        memset(cadena[i], 0, strlen(cadena[i]));
        
        if(!fecha_correcta(list_faltas[i].fecha_falta)) {
            continue;
        }
        
        strcat(cadena[i], list_faltas[i].fecha_falta);
        strcat(cadena[i], "-");
        
        sprintf(aux_hora_falta, "%d", list_faltas[i].hora_falta);
        strcat(cadena[i], aux_hora_falta);
        strcat(cadena[i], "-");
        
        strcat(cadena[i], list_faltas[i].descrip_falta);
        strcat(cadena[i], "-");
        
        strcat(cadena[i], list_faltas[i].estado_falta);
        strcat(cadena[i], "-");
        
        strcat(cadena[i], list_faltas[i].id_alum);
        strcat(cadena[i], "\n");
        
        fprintf(f, "%s", cadena[i]);
    }
    fclose(f);
}

void cargar_faltas(FILE * f, faltas *list_faltas) {
    char cadena[100];
    int i = 0;
    if((f = fopen("faltas.txt", "r")) == NULL) {
        puts(ANSI_COLOR_RED);
        puts("Error fatal: El fichero con la información no existe.\n");
        puts("Puede que parte del programa no funcione correctamente sin esta información.\n\n");
        puts(ANSI_COLOR_RESET);
        return;
    }
    
    while (fgets(cadena, 100, f) != NULL) {
        strcpy(list_faltas[i].fecha_falta, strtok(cadena,"-"));
        list_faltas[i].hora_falta = atoi(strtok(NULL,"-"));
        strcpy(list_faltas[i].descrip_falta, strtok(NULL,"-"));
        strcpy(list_faltas[i].estado_falta, strtok(NULL,"-"));
        strcpy(list_faltas[i].id_alum, strtok(NULL,"\n"));
        
        i++;
    }
    LONGITUD_ARRAY_FALTAS = i;
    fclose(f);
}

/*
 *int main(void) {
 *    
 *    FILE * f;
 *    int array_datos[2];
 *    array_datos[0] = 123456;
 *    array_datos[1] = 3;
 *    
 *    faltas list_faltas[cuenta_lineas("faltas.txt")];
 *    faltas *new_list;
 *    
 *    cargar_faltas(f, list_faltas);
 *    new_list = menu_faltas(list_faltas, array_datos, get_longitud_array_faltas());
 *    
 *    volcado_faltas(f, new_list, "faltas.txt", get_longitud_array_faltas());
 *    return 0;
 *}
 *
 */
