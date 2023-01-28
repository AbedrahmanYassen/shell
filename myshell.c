#include "myshell.h"
int main(int argc, char* argv[])
{
	// if argv[1] contain the file, create or open it
	if(argv[1] != NULL)
		file = fopen(argv[1], "r");
	char buffer[MAX_LINE];
	char previousBuffer[MAX_LINE];
	int input;
	int output;
	// if one argument in the terminal, show welcomeShell
	if(argc == 1)
	    welcomeShell();

	while (1)
	{
		backgroundMode = 0; // the background in off mode
		deleteAllCommands(); // delete all commands from array of commands
		if (argc == 2)
		{
			// if an error occur in creating or open file, exit the program
			if (file == NULL)
			{
				break;
			}
			// gets the line from file, then put it in buffer
			fgets(buffer, MAX_LINE, file);
			stringCommands = buffer;
			// if arrive end of the file, exit the program
			if (strcmp(previousBuffer, buffer) == 0)
			{
				break;
			}
		}
		// if arguments less or greater than 2
		else
		{
			// print the line command prompt
			printf("\033[33m%s@myshell:%s/\033[36m~$ \033[37m", getenv("USER"), getcwd(currentWorkingDirectory, sizeof(currentWorkingDirectory)));
			// get the string from the user
			stringCommands = getStringFromUser();
		}
		// replace the enter character with '\0' character
		stringCommands = ReplaceEnterCharacter(stringCommands);
		// replace the tap character with ' ' character
		stringCommands = ReplaceTapCharacter(stringCommands);
		// split the string by using strtok system call
		char* piece = strtok(stringCommands, " ");
		int counter = 0;
		while (piece != NULL)
		{
			commands[counter] = piece;
			piece = strtok(NULL, " ");
			counter++;
		}
		int defInp = dup(STDIN_FILENO);
		int defOut = dup(STDOUT_FILENO);
		for (int i = 0; i < 100; i++)
		{
			if (commands[i] == NULL)
			{
				continue;
			}
			// here output redirection(trunc)
			if (strcmp(commands[i], ">") == 0)
			{
				output = open(commands[i + 1], O_CREAT | O_WRONLY | O_TRUNC);
				dup2(output, STDOUT_FILENO);
				close(output);
				commands[i] = NULL;
				commands[i + 1] = NULL;
			}
			// here input redirection
			else if (strcmp(commands[i], "<") == 0)
			{
				input = open(commands[i + 1], O_CREAT);
				dup2(input, STDIN_FILENO);
				commands[i] = NULL;
				commands[i + 1] = NULL;
			}
			// here output redirection (append)
			else if (strcmp(commands[i], ">>") == 0)
			{
				output = open(commands[i + 1], O_CREAT | O_WRONLY | O_APPEND);
				dup2(output, STDOUT_FILENO);
				close(output);
				commands[i] = NULL;
				commands[i + 1] = NULL;
			}
			// here background
			else if (strcmp(commands[i], "&") == 0)
			{
				backgroundMode = 1; // background in the on mode
				commands[i] = NULL;
			}
		}
		if (commands[0] == NULL) {
			continue;
		}
		// if command is dir
		else if (strcmp(commands[0], "dir") == 0) {
			commands[0] = "ls";
	    }
		// if command is quit
		if (strcmp(commands[0], "quit") == 0)
		{
			// print this statement, then exit program
			printf("\033[32m\n  Finished My Shell\n  Good Bye :(\n\n\n");
			break;
		}
		// if command is pause
		else if (strcmp(commands[0], "pause") == 0)
		{
		    pause_command();
		}
		// if command is cd
		else if (strcmp(commands[0], "cd") == 0)
		{
			changeDirctory();
		}
		// if command is clr
		else if (strcmp(commands[0], "clr") == 0)
		{
			// clears the screen
			system("clear"); // execute the clear command
		}
		// if command is environ
		else if (strcmp(commands[0], "environ") == 0)
		{
			system("env"); // execute the env command
		}
		// if command is echo
		else if (strcmp(commands[0], "echo") == 0)
		{
			echo_command(); // call the echo_command method
			
		}
		// if command is help
		else if (strcmp(commands[0], "help") == 0) {
			help_command(commands); // call the echo_command method
		}
		else
		{
			// create a child process
			int rc = fork();
			if (rc == 0)
			{
				// child process
				excuteCommandsByExec(); // call the excuteCommandsByExec method
			}
			else
			{
				// parent process
				if (backgroundMode == 0)
				{
					waitpid(rc,NULL,0); // wait the child process
				
				}
				else {
					printf("PID: %d\n", rc); // pid of the process
				}
			}
		}
		// close the standard input and output, and return it to the original state
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		dup2(defInp, STDIN_FILENO);
		dup2(defOut, STDOUT_FILENO);
		// copy the current line in buffer to the previousBuffer
		strcpy(previousBuffer, buffer);
    }
}

