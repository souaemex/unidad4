#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_STR 100
#define LEER		0
#define ESCRIBIR	1
void IniMsg(char *Msg);
int main (void){
    int descr[2];	/* Descriptores de E y S de la turberia */
    int  bytesleidos;
    char mensaje[100],
	*frase="Veremos si la transferecia es buena.";

   printf ("Ejemplo de tuberia entre padre e hijo.\n");
    IniMsg(mensaje);
    pipe (descr);
    if (fork () == 0) {
       close (descr[LEER]);
       write (descr[ESCRIBIR], frase, strlen(frase));
       close (descr[ESCRIBIR]);
    }
    else {
       close (descr[ESCRIBIR]);
       bytesleidos = read (descr[LEER], mensaje, 100);
       printf ("Bytes leidos: %d\n", bytesleidos);
	mensaje[strlen(mensaje)-1]='\0';
       printf ("Mensaje: %s %d\n",  mensaje, strlen(mensaje));
       close (descr[LEER]);
    }
}

void IniMsg(char *Msg)
{
	int iInd;
	for(iInd=0; iInd <MAX_STR; iInd++)
		Msg[iInd]='\0';
} /** fin del IniMsg **/
