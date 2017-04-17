#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar.h"

#ifdef __unix__
    #include <regex.h>
#elif defined(_WIN32) || defined(WIN32)
    // Estoy triste porque utilizas windows, en linux esto iria re-bien :(
#endif

int get_line (char *prmpt, char *buff, size_t sz) {
    int ch, extra;
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }
    
    buff[strlen(buff)-1] = '\0';
    return OK;
}

void convertir_digito_cadena(char * target, char * longitud_cadena, int numero) {
    char aux[100];
    strcpy(aux, "%0");
    strcat(aux, longitud_cadena);
    strcat(aux, "d");
    sprintf(target, aux, numero);
}

void str_replace(char *target, const char *needle, const char *replacement){
    char buffer[1024] = { 0 };
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);
    
    while (1) {
        const char *p = strstr(tmp, needle);
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;
        tmp = p + needle_len;
    }
    strcpy(target, buffer);
}

int fecha_correcta(char * fecha) {
    
    #ifdef __unix__
        regex_t regex;
        
        int reti;
        char msgbuf[100];
        
        reti = regcomp(&regex, "[0-9][0-9][/-][0-9][0-9][/-][0-9][0-9][0-9][0-9]", 0);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
        }
        reti = regexec(&regex, fecha, 0, NULL, 0);
        if (!reti) { return 1; }
        else if (reti == REG_NOMATCH) {
            puts("Esta fecha no puede ser valida, intentelo de nuevo.");
        }
        else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        }
        return 0;
    #elif defined(_WIN32) || defined(WIN32)
        // Sorry, pero pa el windows yo no me complico.
        return 1;
    #endif
}

// Devuelve el numero de lienas en un fichero de texto.
int cuenta_lineas(char * nombre_fichero) {
    FILE * fp = fopen(nombre_fichero, "r");
    
    char ch;
    int n_lineas = 0;
    
    while(! feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n')
            n_lineas++;
    }
    
    return n_lineas;
}
