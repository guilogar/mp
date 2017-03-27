#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Alumnos.h"

static int conta=0; //Marca el número de alumnos que hay

int main(){

Cad_Alumno *List_Alumno;
List_Alumno = Carga_Alumno();
Listar_Alumno(List_Alumno);

return 0;
}


//Cambia los caracteres de salto de linea por caracteres de final de vector
void quitar_saltosA(char *cadena){
    char *p;
    p = strchr(cadena,'\n');
    if(p) *p = '\0';
}

//Leer una cadena de caracteres del largo que se le pasa por parametro
char *leer_campo_A(int largo, char *titulo){
    char *campo;
    campo = (char*)calloc(largo+1,sizeof(char));
    printf("%s (%d):",titulo,largo);
    fflush(stdin);
    fgets(campo,largo+1,stdin);
    quitar_saltosA(campo);
    fflush(stdin);
    return campo;
}

Cad_Alumno* Carga_Alumno(){
    Cad_Alumno *List_Alumno;
    FILE *fichAlum;
    fichAlum=fopen("Alumnos.txt","r"); //Abre el fichero en modo lectura
    if(fichAlum==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(!feof(fichAlum)){
            if(conta==0){
              List_Alumno=(Cad_Alumno *)malloc(1*sizeof(Cad_Alumno));
            }
            else{
              List_Alumno=(Cad_Alumno *)realloc(List_Alumno,(conta+1)*sizeof(Cad_Alumno));
            }
            fscanf(fichAlum,"%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n",List_Alumno[conta].id,List_Alumno[conta].nombre,List_Alumno[conta].dir,List_Alumno[conta].localidad,List_Alumno[conta].curso,List_Alumno[conta].grupo);
            List_Alumno[conta].id[6]='\0';
            List_Alumno[conta].nombre[20]='\0';
            List_Alumno[conta].dir[30]='\0';
            List_Alumno[conta].localidad[30]='\0';
            List_Alumno[conta].curso[30]='\0';
            List_Alumno[conta].grupo[10]='\0';
            conta++;
        }
    }
    fclose(fichAlum);
    return List_Alumno;
}

void Anadir_Alumno(Cad_Alumno *List_Alumno){
    //HAY QUE ASIGNAR EL ID
    strcpy(List_Alumno[conta].id,leer_campo_A(6,"ID"));
    strcpy(List_Alumno[conta].nombre,leer_campo_A(20,"Nombre"));
    strcpy(List_Alumno[conta].dir,leer_campo_A(30,"Direccion"));
    strcpy(List_Alumno[conta].localidad,leer_campo_A(30,"Localidad"));
    strcpy(List_Alumno[conta].curso,leer_campo_A(30,"Curso"));
    strcpy(List_Alumno[conta].grupo,leer_campo_A(10,"Grupo"));
    conta++;
}

void Listar_Alumno(Cad_Alumno *List_Alumno){
    int i;
    for(i=0;i<conta;i++)
        printf("%s-%s-%s-%s-%s-%s\n",List_Alumno[i].id,List_Alumno[i].nombre,List_Alumno[i].dir,List_Alumno[i].localidad,List_Alumno[i].curso,List_Alumno[i].grupo);
}

void Modificar_Alumno(Cad_Alumno *List_Alumno){
    int i=0, pos_mod;
    char us[5];
    strcpy(us,leer_campo_A(5,"Introduce el codigo del alumno a modificar"));
    while(i<conta){
        if(!strcmp(List_Alumno[i].id,us)) pos_mod = i;
        i++;
    }
    if(i<conta){
    printf("\n%s-%s-%s-%s-%s-%s\n",List_Alumno[pos_mod].id,List_Alumno[pos_mod].nombre,List_Alumno[pos_mod].dir,List_Alumno[pos_mod].localidad,List_Alumno[pos_mod].curso,List_Alumno[pos_mod].grupo);
    printf("\n----INTRODUCIR NUEVOS VALORES----\n");
    strcpy(List_Alumno[pos_mod].nombre,leer_campo_A(20,"Nombre"));
    strcpy(List_Alumno[pos_mod].dir,leer_campo_A(30,"Direccion"));
    strcpy(List_Alumno[pos_mod].localidad,leer_campo_A(30,"Localidad"));
    strcpy(List_Alumno[pos_mod].curso,leer_campo_A(30,"Curso"));
    strcpy(List_Alumno[pos_mod].grupo,leer_campo_A(10,"Grupo"));
    } else { printf("\nEl ID introducido no se corresponde con ningun Alumno del sistema.\n"); }
}

void Baja_Alumno(Cad_Alumno *List_Alumno){
    int j = 0, posi, i;
    char cod[6], resp=' ';
    strcpy(cod,leer_campo_A(6,"Codigo del usuario a eliminar "));
    while(j<conta){
        if(!strcmp(List_Alumno[j].id,cod)) posi = j;
        j++;
    }
    if(j<conta){
        while(resp!='s' && resp!='n'){
            printf("\nSe va a eliminar el siguiente usuario:\n%s-%s-%s-%s-%s-%s\n",List_Alumno[posi].id,List_Alumno[posi].nombre,List_Alumno[posi].dir,List_Alumno[posi].localidad,List_Alumno[posi].curso,List_Alumno[posi].grupo);
            printf("Confirmar eliminar Alumno? (s/n)\n");
            fflush(stdin);
            scanf("%c",&resp);
        }

        if(resp=='s'){
            for(i=posi;i+1<conta;i++){
                strcpy(List_Alumno[i].id,List_Alumno[i+1].id);
                strcpy(List_Alumno[i].nombre,List_Alumno[i+1].nombre);
                strcpy(List_Alumno[i].dir,List_Alumno[i+1].dir);
                strcpy(List_Alumno[i].localidad,List_Alumno[i+1].localidad);
                strcpy(List_Alumno[i].curso,List_Alumno[i+1].curso);
                strcpy(List_Alumno[i].grupo,List_Alumno[i+1].grupo);
            }
            conta--;

            List_Alumno=(Cad_Alumno *)realloc(List_Alumno,(conta)*sizeof(Cad_Alumno));
        }else{ printf("\nSe ha cancelado la eliminacion del alumno\n"); }
    } else { printf("\nID introducido no se corresponde con ningun alumno del sistema.\n"); }
}


void Guardar_Alumno(Cad_Alumno *List_Alumno){
    int i=0;
    FILE *fichAlum;
    fichAlum=fopen("Alumnos.txt","w"); //Abre el fichero en modo escritura
    if(fichAlum==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(i<conta){
            fprintf(fichAlum,"%s-%s-%s-%s-%s-%s\n",List_Alumno[i].id,List_Alumno[i].nombre,List_Alumno[i].dir,List_Alumno[i].localidad,List_Alumno[i].curso,List_Alumno[i].grupo);
            i++;
        }
    }
    fclose(fichAlum);
}

