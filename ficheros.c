#include <stdio.h>
#include "ficheros.h"

// Devuelve el numero de lienas en un fichero de texto.
int cuenta_lineas(char * nombre_fichero) {
    FILE * fp = fopen(nombre_fichero, "r");
    char ch;

    int n_lineas = 0;
    while(!feof(fp)) {
      ch = fgetc(fp);
      if(ch == '\n')
        n_lineas++;
    }
    return n_lineas;
}
