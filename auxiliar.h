#ifndef AUXILIAR_H
#define AUXILIAR_H

int cuenta_lineas(char * nombre_fichero);
int fecha_correcta(char * fecha);
void str_replace(char *target, const char *needle, const char *replacement);
void convertir_digito_cadena(char * target, char * longitud_cadena, int numero);
int get_line(char *prmpt, char *buff, size_t sz);

#endif
