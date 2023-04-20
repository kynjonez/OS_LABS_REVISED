// <Author - Kyndall Jones>
// Collaborated with: Zoe Carter and Julian Forbes
// Resources: stackoverflow and geeksforgeeks

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[256] = "> ";
char delimiters[] = " \t\r\n";
extern char **environ;
int time = 0;
int numAlarm = 0;
int kill_pidt;
int child_proc_pid;

time_t start, stop;

void handlesAlarm(int signum)
{
  kill (child_proc_pid, SIGKILL);
}

void handleSigint(int signum)
{
  signal(SIGINT, handleSigint);
  fflush(stdout);
}

// pid_t pid;
// int status;

int main() {
    int i = 0;
    int echoint = 1;
    int envint = 1;
    bool is_background = false;
    char *text;
    
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
  
    // Stores the tokenized command line input.
    char *tokens[MAX_COMMAND_LINE_ARGS];
    size_t n = sizeof(tokens) / sizeof(tokens[0]);

    signal(SIGINT, handleSigint);
    signal(SIGALRM, handlesAlarm);

    while (true) {
      
        do{ 
            int bufsize = 256;

            getcwd(prompt, bufsize);
            // Print the shell prompt.
            printf("%s> ", prompt);
            fflush(stdout);

            if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) 
            {
                // error, exit immediately. (If you want to learn more about this line,
                // you can Google "man fgets")
                fprintf(stderr, "fgets error");
                exit(0);
            }           
        } while(command_line[0] == 0x0A);  // while just ENTER pressed

      
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // TODO:
        // 
        
			  // 0. Modify the prompt to print the current working directory
        if (getcwd(prompt, sizeof(prompt)) == NULL) 
        {
          perror("getcwd() error");
          exit(1);
        }
			
        // 1. Tokenize the command line input (split it on whitespace)
        tokens[0] = strtok(command_line, delimiters);
        
        i = 0;
        while(tokens[i] != NULL)
        {
          i++;
          tokens[i] = strtok(NULL, delimiters);
        }
        if(strcmp(tokens[i-1], "&") == 0)
        {
          is_background = true;
          tokens[i-1] = '\0';
        }
      
        // 2. Implement Built-In Commands
        if (strcmp(tokens[0], "exit") == 0) 
        {
          exit(1);
        } else if (strcmp(tokens[0], "pwd") == 0) {
          printf("%s\n", prompt);
        }
        else if (strcmp(tokens[0], "cd") == 0) {
          if (chdir(tokens[1]) != 0) {
            printf("change directory to %s failed", tokens[1]);
          } else {
            if (tokens[1] == NULL) {
              chdir(getenv("HOME"));
            } else {
              chdir(tokens[1]);
            }
          }
        } else if (strcmp(tokens[0], "env") == 0) {
          envint = 1;

          printf("PATH : %s\n", getenv("PATH"));
          printf("HOME : %s\n", getenv("HOME"));
          printf("ROOT : %s\n", getenv("ROOT"));

          while(tokens[envint] != NULL) {
            text = tokens[envint];
            if (strstr(text, "$") != NULL) {
              text += 1;
            }
            printf("%s : ", text);
            printf("%s\n", getenv(text));
            envint++;
          }
        } else if (strcmp(tokens[0], "echo") == 0) {
          echoint = 1;
          while (tokens[echoint] != NULL) {
            text = tokens[echoint];
            if (strstr(text, "$")!= NULL) {
              text +=1;
              text = getenv(text);
              printf("%s \n", text);
            }
            else {
              printf("%s ", tokens[echoint]);
            }
            echoint++;
          }
          printf("\n");
        } else if (strcmp(tokens[0], "setenv") == 0) {
          if (tokens[1] != NULL && tokens[2] != NULL) {
            setenv(tokens[1], tokens[2], 1);
          }
          else {
            printf("SETENV Error: no parameters specified\n");
          }
        } else {
          // 3. Create a child process which will execute the command line input
          pid_t pid;
          int status;
          pid = fork();

          if(pid < 0) {
            printf("Error: Could not execute the requested process\n");
          }
          else if(pid == 0) {
            if (execvp(tokens[0], tokens) == -1) {
              perror("execvp() fail: ");
              printf("An error occured\n");
            }
            exit(0);
          }
          else {
            child_proc_pid = pid;
            alarm(10);
            if (!is_background) {
              wait(NULL);
            }
          }
        }
  
        // 4. The parent process should wait for the child to complete unless its a background process
      
        // Hints (put these into Google):
        // man fork
        // man execvp
        // man wait
        // man strtok
        // man environ
        // man signals
        
        // Extra Credit
        // man dup2
        // man open
        // man pipes
    }
    // This should never be reached.
    return -1;
}