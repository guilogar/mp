#include <stdio.h>
#include <stdlib.h>
#include "matricula.h"
#include "estructuras.h"

void cargar_matriculas(FILE * f, matriculas mat[]) {
    
    char cadena[100];
    int i = 0;
    
    if((f = fopen("matriculas.txt", "r")) == NULL) {
        
        puts("Error fatal: El fichero con la información no existe.\n\n");     
        return;
    }
    
    while (fgets(cadena, 100, f) != NULL) {
        strcpy(mat[i].id_matriculas, strtok(cadena,"-"));
        strcpy(mat[i].id_alum, strtok(NULL,"-"));
        
        puts(mat[i].id_matriculas);
        puts(mat[i].id_alum);
        
        i++;
    }
}

int contaralumnos(matriculas mat[]){

    int i;
    i=0;
    while(strcmp(mat[i].id_matriculas) != NULL){
        i++;
    }
    return i;
}

void mostrar(char idmateria, matriculas mat[], alumnos alu[]){
    
    int i, n, j;
    n = contaralumnos(mat);
    for(i=0;i<n;i++){
        if(strcmp(idmateria, mat[i].id_matriculas)){
            while(strcmp(alu[j].id_alum) != NULL){
                if(strcmp(mat[i].id_alum, alu[j].id_alum)){
                    printf(alu[j].nombre_alum);
                }
            }
            
        } 
    }
}
