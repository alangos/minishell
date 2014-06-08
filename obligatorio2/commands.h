//
//  commands.h
//  minishell
//
//  Created by Alan Gostanian on 05/06/14.
//  Copyright (c) 2014 Alan Gostanian. All rights reserved.
//

#ifndef minishell_commands_h
#define minishell_commands_h



#endif
void command_cd(int argc, char args[512/2][512]);
void command_exit(char* args);
void command_pid();
void command_uid();
void command_getenv(char* args);
void command_echo(int argc, char args[512/2][512]);
void command_dir(int argc, char args[512/2][512]);
void command_extern(int argc, char args[512/2][512]);
void command_cat(int argc, char *argv);
int command_copy(int argc, char args[512/2][512]);