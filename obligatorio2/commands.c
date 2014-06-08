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
#include <sys/types.h>
#include <dirent.h>

char previous_dir[512];
char tmp[512];

void command_cd(int argc, char args[512/2][512]){
    if (argc == 1)  // no args
    {
        char* home = getenv("HOME");
        strcpy(tmp, previous_dir);
        getcwd(previous_dir, sizeof(previous_dir));
        if (!chdir(home ? home : ".") == -1) {
            strcpy(previous_dir, tmp);
        }
        // in case HOME is not defined  :-)
    }
    else // arg given (could it be a path?)
    {
        if (strcmp(args[1],"-") == 0) {
            
            if (chdir(previous_dir) == -1){
                printf("cd: no previous dir\n");
            }
        }else{
            strcpy(tmp, previous_dir);
            getcwd(previous_dir, sizeof(previous_dir));
            if (chdir(args[1]) == -1){
                strcpy(previous_dir, tmp);
                
                printf("cd: %s: No such file or directory\n",args[1]);
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

void command_echo(int argc, char args[512/2][512]){
    for (int i=1; i<argc; i++) {
        printf("%s ",args[i]);
    }
    
    printf("\n");
}

void command_dir(int argc, char args[512/2][512]){
    if (argc == 1) {
        DIR *dp;
        struct dirent *ep;
        
        dp = opendir ("./");
        if (dp != NULL)
        {
            while ((ep = readdir (dp)))
                puts (ep->d_name);
            (void) closedir (dp);
        }
        else
            perror ("Error al abrir el directorio");
        
    }else{
        DIR *dp;
        struct dirent *ep;
        
        dp = opendir ("./");
        if (dp != NULL)
        {
            while ((ep = readdir (dp))){
                if (strstr(ep->d_name, args[1]) != NULL) {
                    puts (ep->d_name);
                }
            }
            
            (void) closedir (dp);
        }
        else
            perror ("Error al abrir el directorio");
    }
    
}

void command_extern(int argc, char args[512/2][512]){
    char command[512];
    for (int i=0; i<512; i++) {
        command[i] = '\0';
    }
    for (int i = 0; i<argc; i++) {
        sprintf(command, "%s %s", command, args[i]);
    }
    system(command);
    
}