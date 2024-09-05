#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024  // Tamaño máximo de la línea de comando
#define MAX_ARGS 64    // Número máximo de argumentos

void cd(char *ruta){
    if (path == NULL) {
        fprintf(stderr, "Error: No se proporcionó directorio\n");
    } else {
        if (chdir(path) != 0) {
            perror("Error al cambiar de directorio");
        }
    }
}

void parseCommand(char *cmd, char **args) {
    for (int i = 0; i < MAX_ARGS; i++) {
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
    char cmd[MAX_LINE];
    char *args[MAX_ARGS];
    
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
        }
        else{
            executeCommand(args);
        }
        
    }
    return 0;
}