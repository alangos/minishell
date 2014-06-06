//
//  commands.c
//  minishell
//
//  Created by Alan Gostanian on 05/06/14.
//  Copyright (c) 2014 Alan Gostanian. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

char previous_dir[512];
char tmp[512];

void command_cd(char* args){
    if (strcmp(args,"\0") == 0)  // no args
    {
        char* home = getenv("HOME");
        chdir(home ? home : ".");   // in case HOME is not defined  :-)
    }
    else // arg given (could it be a path?)
    {
        if (strcmp(args,"-") == 0) {
            printf("bien");
        }else{
            if (chdir(args) == -1){
                printf("cd: %s: No such file or directory\n",args);
                //printf("%s",getenv("HOME"));
        
            }
        }
        
    }
}

void command_exit(char* args){
    exit(atoi(args));
}

void command_pid(){
    printf("Process ID : %d\n", getpid());
}

void command_uid(){
    printf("User ID : %d\n", getuid());
}

void command_getenv(char* args){
    printf("%s=%s\n",args, getenv(args));
}

void command_echo(char* args){
    printf("%s\n",args);
}