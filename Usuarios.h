#include <stdio.h>
#include <stdlib.h>
#ifndef _USUARIOS
#define _USUARIOS
    typedef struct{
        char id[4];
        char nombre[21];
        char perfil[14];
        char usser[6];
        char pass[9];
    }Cad_Usuario;
#endif

Cad_Usuario* Carga_Usuario();
void Guardar_Usuario(Cad_Usuario *);
void Anadir_Usuario(Cad_Usuario *);
void Listar_Usuarios(Cad_Usuario *);
void Modificar_Usuario(Cad_Usuario *);
void Baja_Usuario(Cad_Usuario *);





