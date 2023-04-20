// <Author - Kyndall Jones>
// Collaborated with: Zoe Carter and Julian Forbes

// Credit to Zoom Recorded Lectures by Dr. Burge

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  int pipefd[2], pipe2[2];
  int pid, pid_2;

  char *cat_args[] = {"cat", "scores", NULL};
  char *grep_args[] = {"grep", argv[1], NULL};
  char *sort_args[] = {"sort", NULL};

  if(argc < 1)
  {
    printf("Please enter the grep arg (e.g. \"Lakers or 28\")\n");
  }

  grep_args[1] = argv[1];
  
  pipe(pipefd);

  pid = fork();
  // Child
  if (pid == 0) 
    {
      pid_2 = fork();
      if (pid_2 == 0) {
        // reads from pipe 2
        dup2(pipe2[0], 0); 
        close(pipe2[3]);
        close(pipefd[1]);
        close(pipefd[0]);
        
        execvp("sort", sort_args);
      }
      else if (pid2 < 0) 
      {
        printf("error");
      }
      else 
      {
        dup2(pipefd[0], 0); 
        dup2(pipefd[3], 1); // read
      }
      // close unused half
      close(pipefd[1]);
      close(pipefd[2]);
      // execute grep
      execvp("grep", grep_args);
      }
    }
  else {
      dup2(pipefd[1], 1); // write 

      close(pipefd[0]);
      close(pipefd[3]);
      // execute cat
      execvp("cat", cat_args);
    }
}