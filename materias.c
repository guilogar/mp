#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "materias.h"
#include "matricula.h"
#include "estructuras.h"
#include "auxiliar.h"

int tam_array;

int get_tam_array_materias(){
    return tam_array;
}

void cargar_materias(materias *mater) {
    
    char cadena[100];
    int i = 0;
    FILE *f;
    f = fopen("materias.txt", "r");
    if(f == NULL) {
        puts("Error fatal: El fichero con la información no existe.\n\n");     
    } else{
        while (fgets(cadena, 100, f) != NULL) {
        
            strcpy(mater[i].id_materia, strtok(cadena,"-"));
            strcpy(mater[i].nombre_materia, strtok(NULL,"-"));
            strcpy(mater[i].abrev_materia, strtok(NULL,"-"));

            i++;
        }
    }
    tam_array = i;
    printf("%d", tam_array);
    fclose(f);
}

char* nombre_id(char *idmateria, materias *mater){
    
    int i;
    
    for(i=0;i<tam_array;i++){
        
        if(strcmp(idmateria, mater[i].id_materia) != 0){
            return mater[i].nombre_materia;
        }
        
    }
}


void listar_materias(materias *mater){
    
    int i;
    
    for(i=0;i<tam_array;i++){
        printf("%s-%s-%s\n", mater[i].id_materia, mater[i].nombre_materia, mater[i].abrev_materia);
        
    }
}

void Anadir_materia(materias *mater){
    
    int i, n;
    
    n = 1+tam_array;
    mater = realloc(mater, n*sizeof(materias));
    printf("Introduzca el id de la nueva materia: ");
    strcpy(mater[n].id_materia, leer_campo_m(5));
    printf("Introduzca el nombre de la materia: ");
    strcpy(mater[n].nombre_materia, leer_campo_m(51));
    printf("Introduzca la abreviatura de la materia: ");
    strcpy(mater[n].abrev_materia, leer_campo_m(4));
    printf("%s-%s-%s\n", mater[n].id_materia, mater[n].nombre_materia, mater[n].abrev_materia);
    tam_array = tam_array + 1;
}

void Modificar_materia(materias *mater){
    
    int i, op;
    char id_mater[4];
    listar_materias(mater);
    printf("Introduzca el id de la materia que desea modificar: ");
    strcpy(id_mater, leer_campo_m(4));
    for(i=0;i<tam_array;i++){
        if(strcmp(id_mater, mater[i].id_materia) == 0){
            
            printf("1. Modificar el id de la materia.\n");
            printf("2. Modificar el nombre de la materia.\n");
            printf("3. Modificar la abreviatura de la materia.\n");
            printf("4. Salir\n\n");
            
            printf("Op: ");
            scanf("%d", &op);
            
            while(op !=4){

                switch(op){
                    case 1: 
                        printf("Introduzca el nuevo id de la materia: ");
                        strcpy(mater[i].id_materia, leer_campo_m(4));
                        break;
                    case 2: 
                        printf("Introduzca el nuevo nombre de la materia: ");
                        strcpy(mater[i].nombre_materia, leer_campo_m(50));
                        break;
                    case 3: 
                        printf("Introduzca la nueva abreviatura de la materia: ");
                        strcpy(mater[i].abrev_materia, leer_campo_m(3));
                        break;
                    default: 
                        printf("ERROR");
                        break;
                }
                if(op!=4){
                    printf("Op: ");
                    scanf("%d", &op);
                }
            }
            printf("La materia modificada: %s-%s-%s", mater[i].id_materia, mater[i].nombre_materia, mater[i].abrev_materia);
            
        }
    } 
}

void Eliminar_materia(materias *mater){
    
    int i, j;
    char id_mater[4];
    printf("Introduzca el id de la materia que quiere eliminar");
    strcpy(id_mater, leer_campo_m(4));
    for(i=0;i<tam_array;i++){
        if(strcmp(id_mater, mater[i].id_materia) == 0){
            strcpy(mater[i].id_materia, "NULL");
            strcpy(mater[i].nombre_materia, "NULL");
            strcpy(mater[i].abrev_materia, "NULL");
            for(j=i+1;tam_array;j++){
                strcpy(mater[j].id_materia, mater[j-1].id_materia);
                strcpy(mater[j].nombre_materia, mater[j-1].nombre_materia);
                strcpy(mater[j].abrev_materia, mater[j-1].abrev_materia);
            }
            mater =(materias *)realloc(mater,(tam_array-1)*sizeof(materias));
            printf("Matricula eliminada.");
            tam_array = tam_array-1;
        }
    }   
}

void menu_materias(materias *mater){
    
    int op;
    
    printf("1. Listar materias\n");
    printf("2. Añadir materia\n");
    printf("3. Eliminar materia\n");
    printf("4. Modificar materia\n");
    printf("5. Salir\n\n");

    printf("Op: ");
    scanf("%d", &op);

    while(op !=5){

        switch(op){
            case 1: 
                listar_materias(mater);
                break;
            case 2: 
                Anadir_materia(mater);
                break;
            case 3: 
                Eliminar_materia(mater);
                break;
            case 4: 
                Modificar_materia(mater);
                break;
            default: 
                printf("ERROR");
                break;
        }
        if(op!=5){
            printf("1. Listar materias\n");
            printf("2. Añadir materia\n");
            printf("3. Eliminar materia\n");
            printf("4. Modificar materia\n");
            printf("5. Salir\n\n");
            printf("Op: ");
            scanf("%d", &op);
        }
    }
}

void guardar_materias(materias *mater){
    int i=0;
    FILE *fich;
    fich=fopen("materias.txt","w"); //Abre el fichero en modo escritura
    if(fich==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(strcmp(mater[i].id_materia, "0") != 0){
            fprintf(fich,"%s-%s-%s\n",mater[i].id_materia,mater[i].nombre_materia, mater[i].abrev_materia);
            i++;
        }
    }
    fclose(fich);
}
