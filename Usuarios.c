#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuarios.h"

static int cont=0; //Marca el número de usuarios que hay

int main(){

Cad_Usuario *List_Usuario;
List_Usuario = Carga_Usuario();
Listar_Usuarios(List_Usuario);

return 0;
}

//Cambia los caracteres de salto de linea por caracteres de final de vector
void quitar_saltos(char *cadena){
    char *p;
    p = strchr(cadena,'\n');
    if(p) *p = '\0';
}

//Leer una cadena de caracteres del largo que se le pasa por parametro
char *leer_campo(int largo, char *titulo){
    char *campo;
    campo = (char*)calloc(largo+1,sizeof(char));
    printf("%s (%d):",titulo,largo);
    fflush(stdin);
    fgets(campo,largo+1,stdin);
    quitar_saltos(campo);
    fflush(stdin);
    return campo;
}

Cad_Usuario* Carga_Usuario(){
    Cad_Usuario *List_Usuario;
    FILE *fich;
    fich=fopen("Usuarios.txt","r"); //Abre el fichero en modo lectura
    if(fich==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(!feof(fich)){
            if(cont==0){
              List_Usuario=(Cad_Usuario *)malloc(1*sizeof(Cad_Usuario));
            }
            else{
              List_Usuario=(Cad_Usuario *)realloc(List_Usuario,(cont+1)*sizeof(Cad_Usuario));
            }
            fscanf(fich,"%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n",List_Usuario[cont].id,List_Usuario[cont].nombre,List_Usuario[cont].perfil,List_Usuario[cont].usser,List_Usuario[cont].pass);
            List_Usuario[cont].id[3]='\0';
            List_Usuario[cont].nombre[20]='\0';
            List_Usuario[cont].perfil[13]='\0';
            List_Usuario[cont].usser[5]='\0';
            List_Usuario[cont].pass[8]='\0';
            cont++;
        }
    }
    fclose(fich);
    return List_Usuario;
}

void Anadir_Usuario(Cad_Usuario *List_Usuario){
    int op,id;
    char aux;
    List_Usuario=(Cad_Usuario *)realloc(List_Usuario,(cont+1)*sizeof(Cad_Usuario));
    id = atoi(List_Usuario[cont-1].id); //Transformar a entero el char referente al id
    id+=1;
    if(id>=100) itoa(id,List_Usuario[cont].id,10);
    else if(id>=10){
        strcat(itoa(id,List_Usuario[cont].id,10),"0");
        //Reordena el valor del indice para que el 0 que concatenamos aparezca delante
        aux = List_Usuario[cont].id[2];
        List_Usuario[cont].id[2] = List_Usuario[cont].id[1];
        List_Usuario[cont].id[1] = List_Usuario[cont].id[0];
        List_Usuario[cont].id[0] = aux;
    }
    else {
        strcat(itoa(id,List_Usuario[cont].id,10),"00");
        //Reordena el valor del indice para que 00 aparezca delante del número
        aux = List_Usuario[cont].id[0];
        List_Usuario[cont].id[0] = List_Usuario[cont].id[2];
        List_Usuario[cont].id[2] = aux;
    }
    strcpy(List_Usuario[cont].nombre,leer_campo(20,"Nombre"));
    do{
        printf("Perfil: 1.Administrador 2.Profesor ");
        scanf("%i",&op);
    }while(op<1 || op >3);
    switch(op){
        case 1:
            strcpy(List_Usuario[cont].perfil,"Administrador");
        break;
        case 2:
            strcpy(List_Usuario[cont].perfil,"Profesor");
        break;
    }
    strcpy(List_Usuario[cont].usser,leer_campo(5,"Usser"));
    strcpy(List_Usuario[cont].pass,leer_campo(8,"Password"));
    cont++;
}

void Listar_Usuarios(Cad_Usuario *List_Usuario){
    int i;
    for(i=0;i<cont;i++)
        printf("%s-%s-%s-%s-%s\n",List_Usuario[i].id,List_Usuario[i].nombre,List_Usuario[i].perfil,List_Usuario[i].usser,List_Usuario[i].pass);
}

void Modificar_Usuario(Cad_Usuario *List_Usuario){
    int i=0, pos_mod, op;
    char us[5];
    strcpy(us,leer_campo(5,"Introduce el Usser a modificar"));
    while(i<cont){
        if(!strcmp(List_Usuario[i].usser,us)) pos_mod = i;
        i++;
    }
    if(i<cont){
    printf("\n%s-%s-%s-%s-%s\n",List_Usuario[pos_mod].id,List_Usuario[pos_mod].nombre,List_Usuario[pos_mod].perfil,List_Usuario[pos_mod].usser,List_Usuario[pos_mod].pass);
    printf("\n----INTRODUCIR NUEVOS VALORES----\n");
    strcpy(List_Usuario[pos_mod].nombre,leer_campo(20,"Nombre"));
    do{
        printf("Perfil: 1.Administrador 2.Profesor ");
        scanf("%i",&op);
    }while(op<1 || op >3);
    switch(op){
        case 1:
            strcpy(List_Usuario[pos_mod].perfil,"Administrador");
        break;
        case 2:
            strcpy(List_Usuario[pos_mod].perfil,"Profesor");
        break;
    }
    strcpy(List_Usuario[pos_mod].usser,leer_campo(5,"Usser"));
    strcpy(List_Usuario[pos_mod].pass,leer_campo(8,"Password"));
    } else { printf("\nEl Usser introducido no se corresponde con ningun usuario del sistema.\n"); }
}

void Baja_Usuario(Cad_Usuario *List_Usuario){
    int j = 0, posi, i;
    char cod[3], resp=' ';
    strcpy(cod,leer_campo(3,"Codigo del usuario a eliminar "));
    while(j<cont){
        if(!strcmp(List_Usuario[j].id,cod)) posi = j;
        j++;
    }
    if(posi<cont){
        while(resp!='s' && resp!='n'){
            printf("\nSe va a eliminar el siguiente usuario:\n%s-%s-%s-%s-%s\n",List_Usuario[posi].id,List_Usuario[posi].nombre,List_Usuario[posi].perfil,List_Usuario[posi].usser,List_Usuario[posi].pass);
            printf("Confirmar eliminar usuario? (s/n)\n");
            fflush(stdin);
            scanf("%c",&resp);
        }

        if(resp=='s'){
            for(i=posi;i+1<cont;i++){
                strcpy(List_Usuario[i].id,List_Usuario[i+1].id);
                strcpy(List_Usuario[i].nombre,List_Usuario[i+1].nombre);
                strcpy(List_Usuario[i].perfil,List_Usuario[i+1].perfil);
                strcpy(List_Usuario[i].usser,List_Usuario[i+1].usser);
                strcpy(List_Usuario[i].pass,List_Usuario[i+1].pass);
            }
            cont--;

            List_Usuario=(Cad_Usuario *)realloc(List_Usuario,(cont)*sizeof(Cad_Usuario));
        }else{ printf("\nSe ha cancelado la eliminacion del usuario\n"); }
    } else { printf("\nID introducido no se corresponde con ningun usuario del sistema.\n"); }
}


void Guardar_Usuario(Cad_Usuario *List_Usuario){
    int i=0;
    FILE *fich;
    fich=fopen("Usuarios.txt","w"); //Abre el fichero en modo escritura
    if(fich==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(i<cont){
            fprintf(fich,"%s-%s-%s-%s-%s\n",List_Usuario[i].id,List_Usuario[i].nombre,List_Usuario[i].perfil,List_Usuario[i].usser,List_Usuario[i].pass);
            i++;
        }
    }
    fclose(fich);
}
