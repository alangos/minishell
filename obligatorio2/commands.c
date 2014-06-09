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
#include <pwd.h>
#include "commands.h"

char previous_dir[W_SIZE];
char tmp[W_SIZE];

void command_cd(int argc, char args[W_SIZE/2][W_SIZE]){
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
    struct passwd *pwd = getpwuid(getuid());
    printf("Username : %s\n", pwd->pw_name);
    
}

void command_getenv(char* args){
    printf("%s=%s\n",args, getenv(args));
}

void command_echo(int argc, char args[W_SIZE/2][W_SIZE]){
    for (int i=1; i<argc; i++) {
        printf("%s ",args[i]);
    }
    
    printf("\n");
}

void command_dir(int argc, char args[W_SIZE/2][W_SIZE]){
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

void command_extern(int argc, char args[W_SIZE/2][W_SIZE]){
    char command[W_SIZE];
    for (int i=0; i<W_SIZE; i++) {
        command[i] = '\0';
    }
    for (int i = 0; i<argc; i++) {
        sprintf(command, "%s %s", command, args[i]);
    }
    system(command);
    
}

void command_cat(int argc, char *argv){
    FILE* fp;
    char c;
    if (argc == 1){
        printf("Error al usar ver, faltan argumentos.\n");
        return;
    }
    fp = fopen(argv, "r");
    if ( fp == NULL ){
        printf("Error al abrir el archivo.\n");
        return;
    }
    while ( (c = getc(fp)) != EOF ) {
        putchar(c);
    }
    printf("\n");
    fclose(fp);
}

void command_setenv (int argc, char args[W_SIZE/2][W_SIZE])

{
    if (argc != 3) {
        printf("Error: missing or too many parameters\n");
        
        return;
    }
    
    char*name = args[1];
    char*value = args [2];
    
    if (! value) {
        
        printf ("'%s' is not set.\n", name);
        
    }
    
    else {
        
        setenv(name,value,1); //If the environment already contains an entry with key name the replace parameter controls the action. If replace is zero, nothing happens. Otherwise the old entry is replaced by the new one.
        
        printf ("%s = %s\n", name, value);
        
    }
    
}

int command_copy(int argc, char args[W_SIZE/2][W_SIZE]){
    char ch;
    
    if (argc != 3) {
        printf("Error: missing or too many parameters\n");
        
        return 1;
    }
    
    FILE* source = fopen(args[1], "r");
    
    if( source == NULL )
        
    {
        
        printf("Error: Source file %s does not exist\n",args[1]);
        
        return 1;
        
    }
    
    FILE* target;
    target = fopen(args[2], "r");


    if( target != NULL )
        
    {
        
        fclose(source);
        
        printf("Error: File %s already exists\n", args[2]);
        
        return 1;
        
    }else{
        target = fopen(args[2], "ab+");
    }
    
    
    while( ( ch = fgetc(source) ) != EOF )
        
        fputc(ch, target);
    
    
    printf("File copied successfully.\n");
    
    
    fclose(source);
    
    fclose(target);
    
    
    
    return 0;
    
}