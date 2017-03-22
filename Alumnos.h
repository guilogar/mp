#include <stdlib.h>
#ifndef _ALUMNOS
#define _ALUMNOS
    typedef struct{
        char id[7];
        char nombre[21];
        char dir[31];
        char localidad[31];
        char curso[31];
        char grupo[11];
    }Cad_Alumno;
#endif

Cad_Alumno* Carga_Alumno();
void Guardar_Alumno(Cad_Alumno *);
void Anadir_Alumno(Cad_Alumno *);
void Listar_Alumno(Cad_Alumno *);
void Modificar_Alumno(Cad_Alumno *);
void Baja_Alumno(Cad_Alumno *);

