#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "alumnos.h"

int conta=0; //Marca el número de alumnos que hay

void quitar_saltosA(char *);
char *leer_campo_A(int, char*);
void Modificar_Alumno_ficha(alumnos *,int);

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

alumnos* Carga_Alumno(){
    conta = 0;
    alumnos *List_Alumno;
    FILE *fichAlum;
    fichAlum=fopen("alumnos.txt","r"); //Abre el fichero en modo lectura
    if(fichAlum==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(!feof(fichAlum)){
            if(conta==0){
              List_Alumno=(alumnos *)malloc(1*sizeof(alumnos));
            }
            else{
              List_Alumno=(alumnos *)realloc(List_Alumno,(conta+1)*sizeof(alumnos));
            }
            fscanf(fichAlum,"%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n",List_Alumno[conta].id_alum,List_Alumno[conta].nombre_alum,List_Alumno[conta].direc_alum,List_Alumno[conta].local_alum,List_Alumno[conta].curso,List_Alumno[conta].grupo);
            List_Alumno[conta].id_alum[6]='\0';
            List_Alumno[conta].nombre_alum[20]='\0';
            List_Alumno[conta].direc_alum[30]='\0';
            List_Alumno[conta].local_alum[30]='\0';
            List_Alumno[conta].curso[30]='\0';
            List_Alumno[conta].grupo[10]='\0';
            conta++;
        }
    }
    fclose(fichAlum);
    return List_Alumno;
}

void menu_alumnos(alumnos *arr_alumnos){
    int op;

    system("cls");
    printf("1. Alta alumno\n");
    printf("2. Baja alumno\n");
    printf("3. Modificar alumno\n");
    printf("4. Listar alumnos\n");
    printf("5. Revisar matricula\n");
    printf("6. Salir\n\n");

    printf("Op: ");
    scanf("%d",&op);

    while(op!=6){
        switch(op){
            case 1:
                system("cls");
                Anadir_Alumno(arr_alumnos);
                op=6;
            break;
            case 2:
                system("cls");
                Baja_Alumno(arr_alumnos);
                op=6;
            break;
            case 3:
                system("cls");
                Modificar_Alumno(arr_alumnos);
                op=6;
            break;
            case 4:
                system("cls");
                Listar_Alumno(arr_alumnos);
                op=6;
            break;
            case 5:
                system("cls");
//                ver_matricula(); //Falta implementación
                op=6;
            break;
            default:
                printf("\nOpción incorrecta\n");
            break;
        }

        if(op!=6){
            printf("Op: ");
            scanf("%d",&op);
        }
    }
}

char* listar_alumnos_prof(alumnos* List_Alumno, char* id){
    int i=0;

    while(strcmp(List_Alumno[i].id_alum,id)!=0){ i++; }
    return List_Alumno[i].nombre_alum;
}

void ficha_alum(alumnos *List_Alumno, char* cod){
    int i=0, op;
    char car;

    while(strcmp(List_Alumno[i].id_alum,cod)!=0){ i++; }
    printf("%s-%s-%s-%s-%s-%s\n",List_Alumno[i].id_alum,List_Alumno[i].nombre_alum,List_Alumno[i].direc_alum,List_Alumno[i].local_alum,List_Alumno[i].curso,List_Alumno[i].grupo);

    printf("\n\nEditar datos[s/n]: ");
    scanf("%c",&car);
    while(car!='s' && car!='n'){
        printf("\n\nEditar datos[s/n]: ");
        scanf("%c",&car);
    }
    if(car=='s') Modificar_Alumno_ficha(List_Alumno,i);
    else if(car=='n') printf("Donde fue el comentario?");
}

void Modificar_Alumno_ficha(alumnos *List_Alumno,int i){
    printf("\n----INTRODUCIR NUEVOS VALORES----\n");
    strcpy(List_Alumno[i].nombre_alum,leer_campo_A(20,"Nombre"));
    strcpy(List_Alumno[i].direc_alum,leer_campo_A(30,"Direccion"));
    strcpy(List_Alumno[i].local_alum,leer_campo_A(30,"Localidad"));
    strcpy(List_Alumno[i].curso,leer_campo_A(30,"Curso"));
    strcpy(List_Alumno[i].grupo,leer_campo_A(10,"Grupo"));
}

void Anadir_Alumno(alumnos *List_Alumno){
    //HAY QUE ASIGNAR EL ID
    strcpy(List_Alumno[conta].id_alum,leer_campo_A(6,"ID"));
    strcpy(List_Alumno[conta].nombre_alum,leer_campo_A(20,"Nombre"));
    strcpy(List_Alumno[conta].direc_alum,leer_campo_A(30,"Direccion"));
    strcpy(List_Alumno[conta].local_alum,leer_campo_A(30,"Localidad"));
    strcpy(List_Alumno[conta].curso,leer_campo_A(30,"Curso"));
    strcpy(List_Alumno[conta].grupo,leer_campo_A(10,"Grupo"));
    conta++;
}

void Listar_Alumno(alumnos *List_Alumno){
    int i;
    for(i=0;i<conta;i++)
        printf("%s-%s-%s-%s-%s-%s\n",List_Alumno[i].id_alum,List_Alumno[i].nombre_alum,List_Alumno[i].direc_alum,List_Alumno[i].local_alum,List_Alumno[i].curso,List_Alumno[i].grupo);
}

void Modificar_Alumno(alumnos *List_Alumno){
    int i=0, pos_mod;
    char us[6];
    strcpy(us,leer_campo_A(5,"Introduce el codigo del alumno a modificar"));
    while(i<conta){
        if(!strcmp(List_Alumno[i].id_alum,us)) pos_mod = i;
        i++;
    }
    if(i<conta){
    printf("\n%s-%s-%s-%s-%s-%s\n",List_Alumno[pos_mod].id_alum,List_Alumno[pos_mod].nombre_alum,List_Alumno[pos_mod].direc_alum,List_Alumno[pos_mod].local_alum,List_Alumno[pos_mod].curso,List_Alumno[pos_mod].grupo);
    printf("\n----INTRODUCIR NUEVOS VALORES----\n");
    strcpy(List_Alumno[pos_mod].nombre_alum,leer_campo_A(20,"Nombre"));
    strcpy(List_Alumno[pos_mod].direc_alum,leer_campo_A(30,"Direccion"));
    strcpy(List_Alumno[pos_mod].local_alum,leer_campo_A(30,"Localidad"));
    strcpy(List_Alumno[pos_mod].curso,leer_campo_A(30,"Curso"));
    strcpy(List_Alumno[pos_mod].grupo,leer_campo_A(10,"Grupo"));
    } else { printf("\nEl ID introducido no se corresponde con ningun Alumno del sistema.\n"); }
}

void Baja_Alumno(alumnos *List_Alumno){
    int j = 0, posi = -1, i;
    char cod[6], resp=' ';
    strcpy(cod,leer_campo_A(6,"Codigo del usuario a eliminar "));
    while(j<conta && posi==-1){
        if(!strcmp(List_Alumno[j].id_alum,cod)) posi = j;
        j++;
    }
    if(j<=conta){
        while(resp!='s' && resp!='n'){
            printf("\nSe va a eliminar el siguiente usuario:\n%s-%s-%s-%s-%s-%s\n",List_Alumno[posi].id_alum,List_Alumno[posi].nombre_alum,List_Alumno[posi].direc_alum,List_Alumno[posi].local_alum,List_Alumno[posi].curso,List_Alumno[posi].grupo);
            printf("Confirmar eliminar Alumno? (s/n)\n");
            fflush(stdin);
            scanf("%c",&resp);
        }

        if(resp=='s'){
            for(i=posi;i+1<conta;i++){
                strcpy(List_Alumno[i].id_alum,List_Alumno[i+1].id_alum);
                strcpy(List_Alumno[i].nombre_alum,List_Alumno[i+1].nombre_alum);
                strcpy(List_Alumno[i].direc_alum,List_Alumno[i+1].direc_alum);
                strcpy(List_Alumno[i].local_alum,List_Alumno[i+1].local_alum);
                strcpy(List_Alumno[i].curso,List_Alumno[i+1].curso);
                strcpy(List_Alumno[i].grupo,List_Alumno[i+1].grupo);
            }
            conta--;

            List_Alumno=(alumnos *)realloc(List_Alumno,(conta)*sizeof(alumnos));
        }else{ printf("\nSe ha cancelado la eliminacion del alumno\n"); }
    } else { printf("\nID introducido no se corresponde con ningun alumno del sistema.\n"); }
}


void Guardar_Alumno(alumnos *List_Alumno){
    int i=0;
    FILE *fichAlum;
    fichAlum=fopen("alumnos.txt","w"); //Abre el fichero en modo escritura
    if(fichAlum==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(i<conta){
            fprintf(fichAlum,"%s-%s-%s-%s-%s-%s\n",List_Alumno[i].id_alum,List_Alumno[i].nombre_alum,List_Alumno[i].direc_alum,List_Alumno[i].local_alum,List_Alumno[i].curso,List_Alumno[i].grupo);
            i++;
        }
    }
    fclose(fichAlum);
}

