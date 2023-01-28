// Call the libraries that we will use in the program
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdbool.h>
#define MAX_LINE 1000 // the maximum if line
// Define the variables and methods for using it in the program
FILE* file; 
char currentWorkingDirectory[300]; 
char* stringCommands;
char* commands[100];
int backgroundMode;
char* getStringFromUser();
void excuteCommandsByExec();
void changeDirctory();
char* ReplaceEnterCharacter(char* string);
char* ReplaceTapCharacter(char* string);
void deleteAllCommands();
void pause_command();
void echo_command();
void help_command();
void welcomeShell();