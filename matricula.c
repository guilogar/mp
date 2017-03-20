#include <stdio.h>
#include <stdlib.h>
#include "matricula.h"
#include "estructuras.h"


int contaralumnos(matriculas mat[]){

    int i;
    i=0;
    while(mat[i] != NULL){
        i++;
    }
    return i;
}

void mostrar(char idmateria, matriculas mat[], alumnos alum[]){
    
    int i, n, j;
    n = contaralumnos(mat);
    for(i=0;i<n;i++){
        if(idmateria==mat[i].id_matriculas){
            while(alum[j] != 0){
                if(mat[i].id_alum=alum[j].id_alum){
                    printf(alum[j].nombre_alum);
                }
            }
            
        } 
    }
}
