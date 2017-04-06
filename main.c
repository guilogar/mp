#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Minusculas y mayusculas en tus .c y .h, revísalo, Guille
//Incompleta a falta de varios archivos.h, ¡¡REVISAR!!

#include "estructuras.h"
#include "ficheros.h"
#include "alumnos.h"
#include "matricula.h"
#include "usuarios.h"
#include "horarios.h"


//	Sección de importación (incompleta a falta de revisión)

void menu_principal();
void menu_admin();
void menu_prof();
void guardar();


void quitar_saltos(char *);
char *leer_campo(int, char *);

// Variables globales
//Contadores de lineas de .txt
//Si sobra o falta alguno añadir o eliminar

int n_horarios, n_alumnos, n_usuarios;
int n_materias, n_matriculas, n_faltas, n_calificaciones;


/*
	Proposición de hacer globales los vectores que
	apuntan a una estructura con los datos de cada
	archivo .txt. Ej:
*/

  horario **arr_horario
  usuarios *arr_usuarios;
  alumnos *arr_alumnos;



int main()
{
	printf("Cuaderno digital del profesor\n");
    //Calcula el numero de lineas de cada fichero de texto
    //Elminad los que os sobren

    n_horarios = cuenta_lineas("horarios.txt");
    n_alumnos = cuenta_lineas("alumnos.txt");
	n_usuarios = cuenta_lineas("usuarios.txt");
	n_materias = cuenta_lineas("materias.txt");
	n_matriculas = cuenta_lineas("materias.txt");
	n_faltas = cuenta_lineas("faltas.txt");
	n_calificaciones = cuenta_lineas("calificaciones.txt");

    arr_horario = malloc(n_horarios * sizeof(horario*));
    arr_usuarios = Carga_Usuario();
    arr_alumnos = Carga_Alumno();

    leer_horarios(arr_horario);

	menu_principal();

	return 0;
}


/*
	Cabecera: ninguna
	Precondición: ninguna
	Postcondición: permite el login de los usuarios del sistema
*/
void menu_principal(){
	int i = 0, sw = 1, op;
	char usser[21], pass[9];

    strcpy(usser,leer_campo(20,"Usuario"));

	while(sw)
    {
        if(i >= n_usuarios) sw = 0;
        else if(strcmp(usser,arr_usuarios[i].usuario) == 0) sw = 0;
        else i++;
    }
    if(i>=n_usuarios){
        printf("El usuario introducido no existe.");
        system("pause");
        i = 0;
        system("cls");
        strcpy(usser,leer_campo(20,"Usuario"));
    }else{
        do{
            strcpy(pass,leer_campo(8,"Contrasena"));
            if(strcmp(arr_usuarios[i].contrasena,pass)!=0){
                printf("Contrasena erronea");
            }
        }while(strcmp(arr_usuarios[i].contrasena,pass)!=0);

        if(strcmp(arr_usuarios[i].perfil_usuario,"Administrador")==0) op = 1;
        else op = 2;

        switch(op){
            case 1:
                menu_admin();
            break;
            case 2:
                menu_prof(i);
            break;
        }
    }
}

void menu_admin(){
    int op;

    system("cls");
    printf("1. Usuarios\n");
    printf("2. Alumnos\n");
    printf("3. Materias\n");
    printf("4. Horarios\n");
    printf("5. Salir\n\n");

    printf("Op: ");
    scanf("%d",&op);

    while(op!=5){
        switch(op){
            case 1:
                system("cls");
                menu_usuarios();
                op=5;
            break;
            case 2:
                system("cls");
                menu_alumnos();
                op=5;
            break;
            case 3:
                system("cls");
                menu_materias(); //Falta implementación
                op=5;
            break;
            case 4:
                system("cls");
                menu_horarios();
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


void menu_prof(int i){
    int op, al;
    char cod[7];
    system("cls");
    //Se necesita que esta función tambien permita seleccionar un grupo de la lista
    listar_horarios_prof(arr_horario,n_horarios,arr_usuarios[i].id_usuario);

    system("cls");
//id = posición del grupo seleccionado de la función anterior.
//pos = posición de la matería cuyo id coincide con el id de la materia del grupo seleccionado de la función anterior
    printf("GRUPO %s MATERIA %s",arr_horario[/*id*/].grupo,arr_materia[/*pos*/].nombre_materia);
    printf("  1.- Lista de alumnos\n");
    printf("  2.- Cambiar de grupo\n\n");

    printf("Op: ");
    scanf("%d",&op);

    switch(op){
        case 1:
            printf("\n\n");
            strcpy(cod,listar_alumnos_materia())
            //falta implementación de listar_alumnos_materia. Creo que debería ir en el módulo matrícula
            //En el módulo alumnos se ha implementado una función que dado el id de un alumno muestra su id y su nombre
            printf("ALUMNO:--------\n");
            printf("1.  Ficha del alumno\n");
            printf("2.  Calificaciones del alumno\n");
            printf("3.  Faltas de asistencia\n");
            printf("4.  Volver\n\n");

            printf("Op: ");
            scanf("%d",&al);

            switch(op){
                case 1:
                    ficha_alum(cod);
                break;
                case 2:
                    califica_alum(cod);
                break;
                case 3:
                    faltas_alum(cod);
                break;
                case 4:
                    //No tengo claro como conseguir esta parte tal y como está el código
                break;
                default:
                    printf("\nOpción incorrecta\n");
                break;
            }
        break;
        case 2:
            menu_prof(i);
        break;
        default:
            printf("\nOpción incorrecta\n");
        break;
    }
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
