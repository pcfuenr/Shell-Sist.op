#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int segundos = atoi(argv[1]);
    char *mensaje = argv[2];

    sleep(segundos);

    printf("\n-------------------------\n* RECUERDE: %s\n-------------------------\nPRESIONE ENTER O NUEVO COMANDO PARA CONTINUAR: ",mensaje);

    return 0;
}
