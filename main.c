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


//	Sección de importación (incompleta a falta de revisión)

void menu_principal();
void menu_admin();
void menu_prof();
void guardar();

// Variables globales
//Contadores de lineas de .txt
//Si sobra o falta alguno añadir o eliminar

int *n_horarios, n_alumnos, n_usuarios;
int n_materias, n_matriculas, n_faltas, n_calificaciones; 

/* 
	Proposición de hacer globales los vectores que
	apuntan a una estructura con los datos de cada 
	archivo .txt. Ej: 
*/

horario **arr_horario


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

/*  
	Reserva de memoria para los vectores que contendrán la
	la base de datos del sistema
*/ 
//Así con todos haría yo...

	arr_horario = malloc(n_horarios * sizeof(horario*));

//Carga de ficheros en memoria
// Así con todos

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

	
}