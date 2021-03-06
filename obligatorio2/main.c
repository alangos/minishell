//
//  main.c
//  obligatorio2
//
//  Created by Alan Gostanian on 02/06/14.
//  Copyright (c) 2014 Alan Gostanian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include "commands.h"

#define CommandNumber 6

int separaPorEspacios(char *s, char out[W_SIZE/2][W_SIZE]);

void eval_command(char command[W_SIZE/2][W_SIZE], int argc){
    if (strcmp(command[0], "cd") == 0) {
        command_cd(argc,command);
        return;
    }
    
    if (strcmp(command[0], "exit") == 0) {
        command_exit(command[1]);
        return;
    }
    
    if (strcmp(command[0], "pid") == 0) {
        command_pid();
        return;
    }
    
    if (strcmp(command[0], "uid") == 0) {
        command_uid();
        return;
    }
    
    if (strcmp(command[0], "getenv") == 0) {
        command_getenv(command[1]);
        return;
    }
    
    if (strcmp(command[0], "echo") == 0) {
        command_echo(argc, command);
        return;
    }
    
    if (strcmp(command[0], "dir") == 0) {
        command_dir(argc, command);
        return;
    }
    
    if (strcmp(command[0], "ver") == 0) {
        command_cat(argc, command[1]);
        return;
    }
    
    if (strcmp(command[0], "copiar") == 0) {
        command_copy(argc, command);
        return;
    }
    
    if (strcmp(command[0], "setenv") == 0) {
        command_setenv(argc, command);
        return;
    }
    
    command_extern(argc, command);
}

int checkVariables(char command[W_SIZE/2][W_SIZE], int argc){
    int i;
    for (i=1; i<argc; i++) {
        char* c = command[i];
        
        if (*c == '$') {
            char* var = getenv(++c);
            
            if (var == NULL) {
                printf("Variable %s does not exist\n", command[i]);
                return 1;
            }else{
                strcpy(command[i], var);
            }
        }
    }
    return 0;
}

void printPrompt(){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        fprintf(stdout, "minishell %s > ", cwd);
    else
        perror("getcwd() error");
}

int main(int argc, const char * argv[])
{

    // insert code here...
    int i,j;
    char str[W_SIZE];
    char pval[W_SIZE/2][W_SIZE];
    while (1) {
        printPrompt();
        if( fgets (str, W_SIZE, stdin)!=NULL ) {
            /* writing content to stdout */
            int words_count = separaPorEspacios(str, pval);
            
            
            if (checkVariables(pval, words_count) == 0) {
                eval_command(pval,words_count);
            }
            //eval command here

            
            
        }
        
        for (i=0; i<W_SIZE; i++) {
            str[i] = '\0';
        }
        for (i=0; i<W_SIZE/2; i++) {
            for (j=0; j<W_SIZE; j++) {
                pval[i][j] = '\0';
                
            }
        }

        
    }
    

    
    
    return 0;
}




int separaPorEspacios(char *s, char out[W_SIZE/2][W_SIZE])
{
    int i=0, j=0, k=0;
    
    while (s[i] != '\0' && s[i] != '\n') {
        while( s[i] == ' '  || s[i] == '\t')
            i++;
        
        
        for (j=0; s[i] != ' ' && s[i] != '\t' && j<W_SIZE-1; j++, i++) {
            if (s[i]=='\0' || s[i] == '\n') {
                break;
            }
            
            out[k][j] = s[i];
        }
        
        out[k][j+1] = '\0';
        i++;
        k++;
    }
    
    return k;
    
}
