/***
 * 	PROGRAMA: pipe_2.c
 * 		DESCRIPCION: Programa para ilustrar el envio de mensajes entre un proceso emisor y otro receptor a traves de dos tuberias sin nombre.
 * 			Estas tuberias van a permitir implementar una comunicacion didireccional.
 * 				El proceso emisor va a pedir el mensaje que le va a enviar al proceso receptor. Cuando el proceso receptor haya presentado el mensaje por pantalla, va a enviar al proceso emisor otro mensaje para indicarle que esta listo y que puede pedirle otro mesaje al usuario
 * 				***/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 256

main()
{
	int tuberia_em_re[2]; 
	int tuberia_re_em[2]; 
	int pid;
	char mensaje[MAX]; 
/* creacion de las tuberias de comunicacion */
	if (pipe (tuberia_em_re) == -1 || 
		pipe (tuberia_re_em) == -1)
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
		/* el proceso hijo (receptor) se va a encargar de leer un mensaje de la tuberia y presentarlo en pantalla. Al recibir el mensaje "FIN", termina el proceso */

		while (read(tuberia_em_re[0], mensaje, MAX) > 0 && 
		strcmp(mensaje, "FIN") != 0)
		{
			printf("PROCESO RECEPTOR. MENSAJE: %s \n", 					mensaje);
		/* enviamos al proceso emisor un mensaje para indicar que estamos listos para recibir otro mensaje */
		strcpy(mensaje, "LISTO");
		write(tuberia_re_em[1], mensaje, strlen(mensaje) +1);
		}

	close (tuberia_em_re[0]);
	close (tuberia_em_re[1]);
	close (tuberia_re_em[0]);
	close (tuberia_re_em[1]);
	exit(0);
	}
	
	else
	{
		/* Codigo del proceso padre */
		/* El proceso padre (emisor) se va a encargar de leer un mensaje de la entrada estandar y acto seguido escribirlo en la tuberia, para que lo reciba el proceso hijo. Al escribir el mensaje "FIN" acaban los dos procesos */
	while(printf("PROCESO EMISOR. MENSAJE: ") != 0 && 
	gets(mensaje) != NULL && 
	write(tuberia_em_re[1], mensaje, strlen(mensaje) +1) > 0 && 
		strcmp(mensaje, "FIN") != 0)
/* Nos ponemos a esperar el mensaje "LISTO" procedente del proceso receptor */
		do
		{
		read(tuberia_re_em[0], mensaje, MAX);
		}while(strcmp(mensaje, "LISTO") != 0);
	close (tuberia_em_re[0]);
	close (tuberia_em_re[1]);
	close (tuberia_re_em[0]);
	close (tuberia_re_em[1]);
	exit(0);
	}
}

