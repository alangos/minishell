//
//  commands.h
//  minishell
//
//  Created by Alan Gostanian on 05/06/14.
//  Copyright (c) 2014 Alan Gostanian. All rights reserved.
//


#define W_SIZE 512

void command_cd(int argc, char args[W_SIZE/2][W_SIZE]);
void command_exit(char* args);
void command_pid();
void command_uid();
void command_getenv(char* args);
void command_echo(int argc, char args[W_SIZE/2][W_SIZE]);
void command_dir(int argc, char args[W_SIZE/2][W_SIZE]);
void command_extern(int argc, char args[W_SIZE/2][W_SIZE]);
void command_cat(int argc, char *argv);
int command_copy(int argc, char args[W_SIZE/2][W_SIZE]);
void command_setenv (int argc, char args[W_SIZE/2][W_SIZE]);