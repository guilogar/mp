#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matricula.h"
#include "estructuras.h"
#include "materias.h"

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
        
            puts(mat[i].id_materias);
            puts(mat[i].id_alum);
        
            i++;
        }
    }
}

int contar_matriculas(matriculas *mat){

    int i;
    i=0;
    while(strcmp(mat[i].id_materias, NULL) != 0){
        i++;
    }
    return i;
}

void mostrar(char* idmatricula, matriculas *mat, alumnos *alu){
    
    int i, n, j;
    n = contar_matriculas(mat);
    for(i=0;i<n;i++){
        if(strcmp(idmatricula, mat[i].id_materias) == 0){
            while(strcmp(alu[j].id_alum, NULL) != 0){
                if(strcmp(mat[i].id_alum, alu[j].id_alum)){
                    printf(alu[j].nombre_alum);
                }
            }
            
        } 
    }
}

void matriculas_alum(char* idalu, matriculas *mat, alumnos *alu){

    int i, n, j;
    n = contar_matriculas(mat);
    for(i=0;i<n;i++){
        if(strcmp(idalu, mat[i].id_alum) == 0){
            while(strcmp(alu[j].id_alum, NULL) != 0){
                if(strcmp(mat[i].id_alum, alu[j].id_alum)){
                    sprintf("%s %s %s", alu[j].nombre_alum, alu[j].curso);
                }
            }
            
        } 
    }    
}

//Leer una cadena de caracteres del largo que se le pasa por parametro
char *leer_campo(int largo){
    char *campo;
    campo = (char*)calloc(largo+1,sizeof(char));
    fflush(stdin);
    fgets(campo,largo+1,stdin);
    fflush(stdin);
    return campo;
}

void Anadir_Matricula(matriculas *mat){

    int n;
    char aux;
    n = 1+contar_matriculas(mat);
    matriculas mat=(mat *)realloc(*sizeof(matriculas));
    printf("Introduzca el id de la materia en la que matriculara al alumno. \n");
    strcpy(mat[n].id_materias, leer_campo(5));
    printf("Introduzca el id del alumno. \n");
    strcpy(mat[n].id_alum, leer_campo(7));
}



void Modificar_matricula(matriculas *mat, char *id_alum, materias *mater){
    int i, n, op, j;
    n=contar_matriculas(mat);
    for(i=0;i<n;i++){
        if(strcmp(id_alum, mat[i].id_alum) == 0){
            for(j=0;j<contarmaterias(mater);j++){
                if(strcmp(mat[i].id_materias, mater[n].id_materia) == 0){
                    sprintf("%s-%s", mat[i].id_materias, mater[n].nombre_materia);
                }
            }
        }
    }
    printf("Introduzca el id de la materia que desea modificar");
    puts
    for(k=0;k<contarmaterias(mater);k++){
        printf
    }
}


void guardar_matriculas(matriculas *mat){
    int i=0;
    FILE *fich;
    fich=fopen("matriculas.txt","w"); //Abre el fichero en modo escritura
    if(fich==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(strcmp(mat[i].id_materias, NULL) != 0){
            fprintf(fich,"%s-%s\n",mat[i].id_materias,mat[i].id_alum);
            i++;
        }
    }
    fclose(fich);
}


int main(){
    
    char * id = malloc(sizeof(char));
    id="0001";
    
    matriculas mat[10];
    alumnos alu[20];
    mostrar(id, mat, alu);
    
    return 0;
    
    
    
}