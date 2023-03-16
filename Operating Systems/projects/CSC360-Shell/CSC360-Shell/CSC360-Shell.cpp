#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

#define PRMTSIZ 255
#define MAXARGS 63
#define EXITCMD "exit"
#define SHOWPIDCMD "showpid"

void print_arg(char* arg);
void parent(void);

int main(void)
{
    int argc = 0;
    int pid_array[5] = { 0, 0, 0, 0, 0 };
    int index = 0;
    while (1)
    {
        char input[PRMTSIZ + 1] = { 0x0 };
        char* ptr = input;
        char* args[MAXARGS + 1] = { NULL };

        // prompt
        printf("myshell$ ");
        fgets(input, PRMTSIZ, stdin);

        // ignore empty input
        if (*ptr == '\n')
            continue;

        // convert input line to list of arguments
        for (int i = 0; i < sizeof(args) && *ptr; ptr++)
        {
            if (*ptr == ' ')
                continue;
            if (*ptr == '\n')
                break;
            for (args[i++] = ptr; *ptr && *ptr != ' ' && *ptr != '\n'; ptr++)
                ;
            *ptr = '\0';

            argc = i; //argc keeps track of how many arguments there are
        }

        printf("Received user commands: ");
        for (int i = 0; i < argc; i++)
        {
            print_arg(args[i]);
        }
        printf("\n");


        // built-in: exit
        if (strcmp(EXITCMD, args[0]) == 0)
        {
            printf("exit\n");
            exit(0);
        }
        else if (strcmp(SHOWPIDCMD, args[0]) == 0)
        {
            for (int i = 0; i < 5; i++)
                printf("%d\n", pid_array[i]);
            continue;
        }

        // fork child and execute program
        pid_array[index] = fork();
        int pid = pid_array[index];
        index++;
        if (index >= 5)
            index = 0;
        int status;

        if (pid < 0)
        {
            printf("Fork Failed\n");
            exit(-1);
        }
        else if (pid == 0)
        {
            int status = execvp(args[0], args);

            if (status == -1)
            {
                printf("ERROR: could not run command\n");
                continue;
            }
        }
        else //parent process
        {
            int cid = waitpid(-1, &status, 0);
            //printf("Child complete\n");
        }
    }
}

void print_arg(char* arg)
{
    int i = 0;
    while (arg[i] && arg[i] != '\0' && arg[i] != ' ' && arg[i] != '\n')
    {
        printf("%c", arg[i++]);
    }
    printf(" ");
}