#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

//Alumnos y usuarios primeros en ser volcados

typedef struct usuarios {
	char id_usuario[4];
	char nomb_usuario[21];
	char perfil_usuario[14];
	char Usuario[21];
	char contraseña[9];
} usuarios;





typedef struct alumnos{
	char id_alum[7];
	char nombre_alum[21];
	char direc_alum[31];
	char local_alum[31];
	char curso[31];
	char grupo[11];
} alumnos;







typedef struct materias{
	char id_materia[5];
	char nombre_materia[51];
	char abrev_materia[4];
} materias;

//Depende de alumnos

typedef struct matriculas{
	char id_matriculas[5];
	alumnos id_alum;
} matriculas;

//Depende de alumnos y materias

typedef struct calificaciones{
	char fecha_calif[11];
	char descrip_calif[31];
	materias id_materia;
	alumnos id_alum;
	int valor_calif;
};

//Depende de alumnos

typedef struct faltas{
	char fecha_falta[11];
	int hora_falta;
	char descrip_falta[31];
	char estado_falta[14];
	alumnos id_alum;
} faltas;

//Depende de usuarios, alumnos y materias

typedef struct horarios{
	usuarios id_prof;
	int dia_clase;
	int hora_clase;
	materias id_materias;
	alumnos grupo;
};

#endif
