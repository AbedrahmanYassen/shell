#include "myshell.h"
//This mehod gets the string from user
// return pointer of character(string)
char* getStringFromUser()
{
	char* line = NULL; 
	size_t len = 0; 
    getline(&line, &len, stdin); 
	return line;
}
// This method execute the command by using exec system call
// if exec didnt execution, will print error message
// didnt return anything
void excuteCommandsByExec()
{
	execvp(commands[0], commands); 
	printf("\033[31mThis is a wrong command\n");
	exit(0);
}
// This method change directory to the new directory
// if the user enter just cd, will print error message
// if the user enter the wrong directory, will print error message
// didnt return anything
void changeDirctory()
{
	if (commands[1] == NULL)
	{
		printf("\033[31mThis is a wrong command\n");
	}
	else
	{
		if ((chdir(commands[1])) == -1)
		{
			printf("\033[31m%s: no such directory \n", commands[1]);
		}
	}
}
// This method replace the enter character '\n' with '\0' character
// '\0' means terminate the string
// This method take a string parameter
// return pointer of character (string)
char* ReplaceEnterCharacter(char* string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == '\n')
		{
			string[i] = '\0';
		}
	}
	return string;
}
// This method replace the enter character '\t' with ' ' character
// This method take a string parameter
// return pointer of character (string)
char* ReplaceTapCharacter(char* string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == '\t')
		{
			string[i] = ' ';
		}
	}
	return string;
}
// This method removes all commands from array of commands
// didnt return anything
void deleteAllCommands()
{
	for (int i = 0; i < 100; i++)
	{
		commands[i] = NULL;
	}
}
// This method print the statement below
// if user press enter character, then method finish
// didnt return anything
void pause_command() {
	char useless;
	printf("Press Enter Key to Continue\n");
	scanf("%c", &useless);
}
// this method print all words after the echo command
// didnt return anything
void echo_command() {
	int count;
	for (count = 1; commands[count] != NULL; count++)
		printf("%s ", commands[count]);
	printf("\n");
}
// This method print the help of each command
// This method read from the readme file
// didnt return anything
void help_command(char* commands[]) {
	if (strcmp(commands[0], "help") == 0) {
		bool keep_read = true;
		char message[1000];
		char heep[100] = "<help ";
		if (commands[1] == NULL) {
			strcat(heep, ">");
		} 
		else if (commands[1] != NULL) {
			strcat(commands[1], ">");
			strcat(heep, commands[1]);
		}
		FILE* fd = fopen("readme", "r");
		while (fgets(message, MAX_LINE, fd) != NULL) {
			if (strstr(message, heep) != NULL) {
				while (keep_read) {
					printf("%s", message);
					fgets(message, MAX_LINE, fd);
					
					if (strstr(message, "#") != NULL) {
						keep_read = false;
					}
				}
			}
		}
	}
}
// This method show in the start of program
// This method print statement in below
// then from 5 to 1, then go to the my shell
// didnt return anything
void welcomeShell() {
    printf("\n\n\n\n");
	printf("\033[36m\t\t\t\t\t       Welcome to My Shell \n\n ");
	sleep(1);
	printf("\t\t\t\t\t\t  Developed By:\n\n ");
	sleep(1);
	printf("\t\t\t\t\t\t Abdelrhman Yaseen\n\n");
	sleep(1);
	int i = 5;
	while (1) {
		if (i == 0) {
			printf("  \033[32m\t\t\t\t\t\t   Let's Goooo\n");
			break;
		}
		printf("  \033[32m\t\t\t\t\t\t\t%d\n",i);
		sleep(1);
		i--;
	}
	sleep(1);
	system("clear");
}
