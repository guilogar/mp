#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "materias.h"
#include "estructuras.h"

void cargar_materias(materias *mater) {
    
    char cadena[60];
    int i = 0;
    FILE *f;
    f = fopen("materias.txt", "r");
    if(f == NULL) {
        
        puts("Error fatal: El fichero con la información no existe.\n\n");     
        
    }else{
    
        while (fgets(cadena, 60, f) != NULL) {
        
            strcpy(mater[i].id_materia, strtok(cadena,"-"));
            strcpy(mater[i].nombre_materia, strtok(NULL,"-"));
            strcpy(mater[i].abrev_materia, strtok(NULL,"-"));
        
            puts(mater[i].id_materia);
            puts(mater[i].nombre_materia);
            puts(mater[i].abrev_materia);
        
            i++;
        }
    }
}

char* nombre_id(char* idmateria, materias *mater){
    
    int i, idm;
    
    while(mater[i].id_materia != NULL){
        
        if(strcmp(idmateria, mater[i].id_materia) != 0){
            return mater[i].nombre_materia;
        }
        i++;
    }
}

int contarmaterias(materias *mater){
    
    int i;
    while(strcmp(mater[i].id_materia, 0) != 0){
        i++;
    }
    return i;
}


void listar_materias(materias *mater){
    
    int i;
    for(i=0;i<contarmaterias(mater);i++){
        sprintf("%s", mater[i].nombre_materia);
    }
}
void guardar_materias(materias *mater){
    int i=0;
    FILE *fich;
    fich=fopen("materias.txt","w"); //Abre el fichero en modo escritura
    if(fich==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(strcmp(mater[i].id_materia, 0) != 0){
            fprintf(fich,"%s-%s-%s\n",mater[i].id_materia,mater[i].nombre_materia, mater[i].abrev_materia);
            i++;
        }
    }
    fclose(fich);
}
