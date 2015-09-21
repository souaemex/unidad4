/***
 * 	PROGRAMA: pipe_1.c
 * 	DESCRIPCION: Programa para ilustrar el envio 
 * 	de mensajes entre un proceso emisor y otro 
 * 	receptor a  traves de una tuberia sin nombre
 * 		***/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 256

main()
{
	int tuberia[2]; 
	int pid;
	char mensaje[MAX]; 

/* creacion de la tuberia sin nombre */

	if (pipe (tuberia) == -1)
	{
		perror("pipe");
		exit (-1);
	}

/* creacion del proceso hijo */

	if((pid = fork()) == -1)
	{
		perror("fork");
		exit (-1);
	}
	else if (pid == 0)
	{
		/* codigo del proceso hijo */
		/* el proceso hijo (receptor) se va a encargar de 
 * 		leer un mensaje de la tuberia y presentarlo 
 * 		en pantalla. El ciclo de lectura y 
 * 		presentacion termina al leer el mensaje "FIN" */

		while (read(tuberia[0], mensaje, MAX) > 0 
		&& strcmp(mensaje, "FIN") != 0)
			printf("PROCESO RECEPTOR. MENSAJE: %s \n", mensaje);
	close (tuberia[0]);
	close (tuberia[1]);
	exit(0);
	}
	else
	{
		/* Codigo del proceso padre */
		/* Codigo del proceso padre (emisor) se va a 
 * 		encargar de leer un mensaje de la entrada 
 * 		esrtandar y, acto seguido, escribirlo en 
 * 		la tuberia para que lo reciba el proceso hijo 
 * 	El ciclo de la lectura de la entrada estandar y 
 * 	escrita en la tuberia terminarà cuando se 
 * 	introduzca el mensaje "FIN"  */
	while( strcmp(mensaje, "FIN") !=0){
		printf("PROCESO EMISOR, MENSAJE: ")   ;
		gets(mensaje) ;
		write(tuberia[1], mensaje, strlen(mensaje) +1 ) ;
	}

	close(tuberia[0]);
	close(tuberia[1]);
	exit(0);
	}
}/** fin del main**/

