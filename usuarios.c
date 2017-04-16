#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "usuarios.h"

int cont=0; //Marca el número de usuarios que hay

void quitar_saltosU(char *);
char *leer_campo(int largo, char *titulo);

//Cambia los caracteres de salto de linea por caracteres de final de vector
void quitar_saltosU(char *cadena){
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
    quitar_saltosU(campo);
    fflush(stdin);
    return campo;
}

usuarios* Carga_Usuario(){
    usuarios *List_Usuario;
    FILE *fich;
    fich=fopen("Usuarios.txt","r"); //Abre el fichero en modo lectura
    if(fich==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(!feof(fich)){
            if(cont==0){
              List_Usuario=(usuarios *)malloc(1*sizeof(usuarios));
            }
            else{
               List_Usuario=(usuarios *)realloc(List_Usuario,(cont+1)*sizeof(usuarios));
            }
            fscanf(fich,"%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n",List_Usuario[cont].id_usuario,List_Usuario[cont].nomb_usuario,List_Usuario[cont].perfil_usuario,List_Usuario[cont].usuario,List_Usuario[cont].contrasena);
            List_Usuario[cont].id_usuario[3]='\0';
            List_Usuario[cont].nomb_usuario[20]='\0';
            List_Usuario[cont].perfil_usuario[13]='\0';
            List_Usuario[cont].usuario[20]='\0';
            List_Usuario[cont].contrasena[8]='\0';
            cont++;
        }
    }
    fclose(fich);
    return List_Usuario;
}

void menu_usuarios(usuarios * arr_usuarios){
    int op;
    
    system("cls");
    printf("1. Alta usuario\n");
    printf("2. Baja usuario\n");
    printf("3. Modificar usuario\n");
    printf("4. Listar usuarios\n");
    printf("5. Salir\n\n");

    printf("Op: ");
    scanf("%d",&op);

    while(op!=5){
        switch(op){
            case 1:
                system("cls");
                Anadir_Usuario(arr_usuarios);
                op=5;
            break;
            case 2:
                system("cls");
                Baja_Usuario(arr_usuarios);
                op=5;
            break;
            case 3:
                system("cls");
                Modificar_Usuario(arr_usuarios);
                op=5;
            break;
            case 4:
                system("cls");
                Listar_Usuarios(arr_usuarios);
                op=5;
            break;
            default:
                printf("\nOpción incorrecta\n");
            break;
        }

        if(op!=5){
            printf("Op: ");
            scanf("%d",&op);
        }
    }
}

void Anadir_Usuario(usuarios *List_Usuario){
    int op,id;
    char aux;
    List_Usuario=(usuarios *)realloc(List_Usuario,(cont+1)*sizeof(usuarios));
    id = atoi(List_Usuario[cont-1].id_usuario); //Transformar a entero el char referente al id
    id+=1;
    if(id>=100) sprintf(List_Usuario[cont].id_usuario,"%d",id);
    else if(id>=10){
        sprintf(List_Usuario[cont].id_usuario,"%d",id);
        strcat(List_Usuario[cont].id_usuario,"0");
        //Reordena el valor del indice para que el 0 que concatenamos aparezca delante
        aux = List_Usuario[cont].id_usuario[2];
        List_Usuario[cont].id_usuario[2] = List_Usuario[cont].id_usuario[1];
        List_Usuario[cont].id_usuario[1] = List_Usuario[cont].id_usuario[0];
        List_Usuario[cont].id_usuario[0] = aux;
    }
    else {
        sprintf(List_Usuario[cont].id_usuario,"%d",id);
        strcat(List_Usuario[cont].id_usuario,"00");
        //Reordena el valor del indice para que 00 aparezca delante del número
        aux = List_Usuario[cont].id_usuario[0];
        List_Usuario[cont].id_usuario[0] = List_Usuario[cont].id_usuario[2];
        List_Usuario[cont].id_usuario[2] = aux;
    }
    strcpy(List_Usuario[cont].nomb_usuario,leer_campo(20,"Nombre"));
    do{
        printf("Perfil: 1.Administrador 2.Profesor ");
        scanf("%i",&op);
    }while(op<1 || op >3);
    switch(op){
        case 1:
            strcpy(List_Usuario[cont].perfil_usuario,"Administrador");
        break;
        case 2:
            strcpy(List_Usuario[cont].perfil_usuario,"Profesor");
        break;
    }
    strcpy(List_Usuario[cont].usuario,leer_campo(20,"Usser"));
    strcpy(List_Usuario[cont].contrasena,leer_campo(8,"Password"));
    cont++;
}

void Listar_Usuarios(usuarios *List_Usuario){
    int i;
    for(i=0;i<cont;i++)
        printf("%s-%s-%s-%s-%s\n",List_Usuario[i].id_usuario,List_Usuario[i].nomb_usuario,List_Usuario[i].perfil_usuario,List_Usuario[i].usuario,List_Usuario[i].contrasena);
}

void Modificar_Usuario(usuarios *List_Usuario){
    int i=0, pos_mod, op;
    char us[20];
    strcpy(us,leer_campo(20,"Introduce el Usser a modificar"));
    while(i<cont){
        if(!strcmp(List_Usuario[i].usuario,us)) pos_mod = i;
        i++;
    }
    if(i<cont){
    printf("\n%s-%s-%s-%s-%s\n",List_Usuario[pos_mod].id_usuario,List_Usuario[pos_mod].nomb_usuario,List_Usuario[pos_mod].perfil_usuario,List_Usuario[pos_mod].usuario,List_Usuario[pos_mod].contrasena);
    printf("\n----INTRODUCIR NUEVOS VALORES----\n");
    strcpy(List_Usuario[pos_mod].nomb_usuario,leer_campo(20,"Nombre"));
    do{
        printf("Perfil: 1.Administrador 2.Profesor ");
        scanf("%i",&op);
    }while(op<1 || op >3);
    switch(op){
        case 1:
            strcpy(List_Usuario[pos_mod].perfil_usuario,"Administrador");
        break;
        case 2:
            strcpy(List_Usuario[pos_mod].perfil_usuario,"Profesor");
        break;
    }
    strcpy(List_Usuario[pos_mod].usuario,leer_campo(20,"Usser"));
    strcpy(List_Usuario[pos_mod].contrasena,leer_campo(8,"Password"));
    } else { printf("\nEl Usser introducido no se corresponde con ningun usuario del sistema.\n"); }
}

void Baja_Usuario(usuarios *List_Usuario){
    int j = 0, posi = -1, i;
    char cod[3], resp=' ';
    strcpy(cod,leer_campo(3,"Codigo del usuario a eliminar "));
    while(j<cont && posi == -1){
        if(!strcmp(List_Usuario[j].id_usuario,cod)) posi = j;
        j++;
    }
    if(j<=cont){
        while(resp!='s' && resp!='n'){
            printf("\nSe va a eliminar el siguiente usuario:\n%s-%s-%s-%s-%s\n",List_Usuario[posi].id_usuario,List_Usuario[posi].nomb_usuario,List_Usuario[posi].perfil_usuario,List_Usuario[posi].usuario,List_Usuario[posi].contrasena);
            printf("Confirmar eliminar usuario? (s/n)\n");
            fflush(stdin);
            scanf("%c",&resp);
        }

        if(resp=='s'){
            for(i=posi;i+1<cont;i++){
                strcpy(List_Usuario[i].id_usuario,List_Usuario[i+1].id_usuario);
                strcpy(List_Usuario[i].nomb_usuario,List_Usuario[i+1].nomb_usuario);
                strcpy(List_Usuario[i].perfil_usuario,List_Usuario[i+1].perfil_usuario);
                strcpy(List_Usuario[i].usuario,List_Usuario[i+1].usuario);
                strcpy(List_Usuario[i].contrasena,List_Usuario[i+1].contrasena);
            }
            cont--;

            List_Usuario=(usuarios *)realloc(List_Usuario,(cont)*sizeof(usuarios));
        }else{ printf("\nSe ha cancelado la eliminacion del usuario\n"); }
    } else { printf("\nID introducido no se corresponde con ningun usuario del sistema.\n"); }
}


void Guardar_Usuario(usuarios *List_Usuario){
    int i=0;
    FILE *fich;
    fich=fopen("Usuarios.txt","w"); //Abre el fichero en modo escritura
    if(fich==NULL) printf("\nError al cargar el fichero\n");
    else{
        while(i<cont){
            fprintf(fich,"%s-%s-%s-%s-%s\n",List_Usuario[i].id_usuario,List_Usuario[i].nomb_usuario,List_Usuario[i].perfil_usuario,List_Usuario[i].usuario,List_Usuario[i].contrasena);
            i++;
        }
    }
    fclose(fich);
}
