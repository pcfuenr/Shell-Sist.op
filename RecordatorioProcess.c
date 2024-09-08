#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int segundos = atoi(argv[1]);
    char *mensaje = argv[2];

    sleep(segundos);

    printf("\n\nRECUERDA: %s\n\n",mensaje);

    return 0;
}
