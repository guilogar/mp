#ifndef AUXILIAR_H
#define AUXILIAR_H

//===================================

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

//===================================

int cuenta_lineas(char * nombre_fichero);
int fecha_correcta(char * fecha);
void str_replace(char *target, const char *needle, const char *replacement);
void convertir_digito_cadena(char * target, char * longitud_cadena, int numero);
int get_line(char *prmpt, char *buff, size_t sz);
char *leer_campo_m(int largo);
#endif
