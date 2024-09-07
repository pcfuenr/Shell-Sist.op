#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define Max_Caracteres 1024  // Tamaño máximo de la línea de comando
#define Max_Argumentos 64    // Número máximo de argumentos
#define Max_pipes 10         // Número maximo de argumentos concatenados con pipes

char DirectorioAnterior[Max_Caracteres];

void cd(char *ruta){
    char DirectorioActual[Max_Caracteres];

    getcwd(DirectorioActual, sizeof(DirectorioActual));

    if (ruta == NULL) {
        if(strlen(DirectorioAnterior)>0){
            if(chdir(DirectorioAnterior)!=0){
                perror("Error al cambiar al directorio anterior");
            }
        }
    } else {
        if (chdir(ruta) != 0) {
            perror("Error al cambiar de directorio");
        }
    }
    strcpy(DirectorioAnterior,DirectorioActual);
}

void parseCommand(char *cmd, char **args) {
    for (int i = 0; i < Max_Argumentos; i++) {
        args[i] = strsep(&cmd, " ");
        if (args[i] == NULL) break;
    }
}

void executeCommand(char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error en fork");
    } else if (pid == 0) {
        // Proceso hijo
        if (execvp(args[0], args) < 0) {
            perror("Error en exec");
        }
        exit(EXIT_FAILURE);
    } else {
        // Proceso padre
        wait(NULL);
    }
}

int main() {
    char cmd[Max_Caracteres];
    char *args[Max_Argumentos];
    DirectorioAnterior[0] = '\0';
    while (1) {
        printf("mishell:$ ");
        fgets(cmd, MAX_LINE, stdin);

        // Eliminar el salto de línea al final de la entrada
        cmd[strcspn(cmd, "\n")] = 0;

        // Si la línea está vacía, continuar
        if (strlen(cmd) == 0) continue;
        
        // Comprobar si el comando es "exit"
        if (strcmp(cmd, "exit") == 0) break;

        // Parsear la entrada
        parseCommand(cmd, args);

        // Ejecutar el comando
        if(strcmp(cmd,"cd") == 0) {
            cd(args[1]);
        }
        else{
            executeCommand(args);
        }
        
    }
    return 0;
}