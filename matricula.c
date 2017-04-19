#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matricula.h"
#include "estructuras.h"
#include "materias.h"
#include "auxiliar.h"

int tam_array;

int get_tam_array_matriculas(){
    return tam_array;
}

void cargar_matriculas(matriculas *mat) {
    
    char cadena[60];
    int i = 0;
    FILE *f;
    f = fopen("matriculas.txt", "r");
    if(f == NULL) {
        
        puts("Error fatal: El fichero con la información no existe.\n\n");     
        
    }else{
    
        while (fgets(cadena, 60, f) != NULL) {
        
            strcpy(mat[i].id_materias, strtok(cadena,"-"));
            strcpy(mat[i].id_alum, strtok(NULL,"-"));
        
            i++;
        }
    }
    tam_array = i;
}


void mostrar(char *idmatricula, matriculas *mat, alumnos *alu){
    
    int i, j;

    for(i=0;i<tam_array;i++){
        if(strcmp(idmatricula, mat[i].id_materias) == 0){
            while(strcmp(alu[j].id_alum, "NULL") != 0){
                if(strcmp(mat[i].id_alum, alu[j].id_alum)){
                    puts(alu[j].nombre_alum);
                }
            }
        } 
    }
}

void matriculas_alum(char *idalu, matriculas *mat, alumnos *alu){

    int i, j=0;
    
    for(i=0;i<tam_array;i++){
        if(strcmp(idalu, mat[i].id_alum) == 0){
            while(strcmp(alu[j].id_alum, NULL) != 0){
                if(strcmp(mat[i].id_alum, alu[j].id_alum)){
                    printf("%s %s \n", alu[j].nombre_alum, alu[j].curso);
                }
            }   
        } 
    }    
}

void lista_matricula(char *id_alum, matriculas *mat, materias *mater){
    
    int i, j;
 
    for(i=0;i<tam_array;i++){
        if(strcmp(id_alum, mat[i].id_alum) == 0){
            for(j=0;j < get_tam_array_materias();j++){
                if(strcmp(mat[i].id_materias, mater[j].id_materia) == 0){
                    printf("%s-%s\n", mat[i].id_materias, mater[j].nombre_materia);
                }
            }
        }
    }
}


void Anadir_Matricula(matriculas *mat, char *id_alum){

    int n;
    n = 1+tam_array;
    mat =(matriculas *)realloc(mat,(n)*sizeof(matriculas));
    strcpy(mat[n].id_alum, id_alum);
    printf("Introduzca el id de la materia en la que matriculara al alumno. \n");
    strcpy(mat[n].id_materias, leer_campo_m(4));
    tam_array = tam_array+1;
}



void Modificar_matricula(matriculas *mat, char *id_alum, materias *mater){
    
    int i, n, k, j;
    char id_materia[6];
    n=tam_array;
    printf("Lista de asignaturas matriculadas: \n");
    for(i=0;i<n;i++){
        if(strcmp(id_alum, mat[i].id_alum) == 0){
            for(j=0;j<get_tam_array_materias();j++){
                if(strcmp(mat[i].id_materias, mater[j].id_materia) == 0){
                    sprintf("%s-%s\n", mat[i].id_materias, mater[j].nombre_materia);
                   
                }
            }
        }
    }
    printf("Introduzca el id de la materia que quiere modificar");
    strcpy(id_materia,leer_campo_m(4));
    for(k=0;k<get_tam_array_materias();k++){
        if((strcmp(id_materia, mat[k].id_materias) == 0) && (strcmp(id_alum, mat[k].id_alum) == 0)){
            printf("Introduzca el id de la materia que desea matricular");
            strcpy(mat[k].id_materias, leer_campo_m(4));
            printf("%s-%s\n", mat[k].id_alum, mat[k].id_materias);
        }
    }
}

void Eliminar_matricula(matriculas *mat, char *id_alum, materias *mater){
    
    int i, j, k, l;
    char mensaje[50], id_materia[6];
    
    printf("Lista de asignaturas matriculadas: \n");
    for(i=0;i<tam_array;i++){
        if(strcmp(id_alum, mat[i].id_alum) == 0){
            for(j=0;j<get_tam_array_materias();j++){
                if(strcmp(mat[i].id_materias, mater[j].id_materia) == 0){
                    printf("%s-%s\n", mat[i].id_materias, mater[j].nombre_materia);
                }
            }
        }
    }
    printf("Introduzca el id de la materia que quiere eliminar");
    strcpy(id_materia, leer_campo_m(4));
    for(k=0;k<tam_array;k++){
        if((strcmp(id_materia, mat[k].id_materias) == 0) && (strcmp(id_alum, mat[k].id_alum) == 0)){
            strcpy(mat[k].id_alum, "NULL");
            strcpy(mat[k].id_materias, "NULL");
            for(l=k+1;l<tam_array;l++){
                strcpy(mat[l].id_alum, mat[l-1].id_alum);
                strcpy(mat[l].id_materias, mat[l-1].id_materias);
            }
            printf("Matricula eliminada.");
            tam_array = tam_array - 1;
        }
    }
}


void menu_matriculas(char *id_alum, matriculas *mat, materias *mater){
    
    int op;
    
    system("cls");
    printf("1. Listar asignaturas matriculadas\n");
    printf("2. Modificar matricula\n");
    printf("3. Eliminar matricula\n");
    printf("4. Anadir matricula\n");
    printf("5. Salir\n\n");

    printf("Op: ");
    scanf("%d", &op);

    while(op !=5){

        switch(op){
            case 1: 
                lista_matricula(id_alum, mat, mater);
                break;
            case 2: 
                Modificar_matricula(mat, id_alum, mater);
                break;
            case 3: 
                Eliminar_matricula(mat, id_alum, mater);
                break;
            case 4: 
                Anadir_Matricula(mat, id_alum);
                break;
            default: 
                printf("ERROR");
                break;
        }
        if(op!=5){
            printf("Op: ");
            scanf("%d", &op);
        }
    }
}

void guardar_matriculas(matriculas *mat){
    int i=0;
    FILE *fich;
    fich=fopen("matriculas.txt","w"); //Abre el fichero en modo escritura
    if(fich==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(strcmp(mat[i].id_materias, "NULL") != 0){
            fprintf(fich,"%s-%s\n",mat[i].id_materias,mat[i].id_alum);
            i++;
        }
    }
    fclose(fich);
}

