// <Author - Kyndall Jones>
// Collaborated with: Zoe Carter and Julian Forbes

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

bool signaled = true;

void handler(int signum)
{ 
  printf("Hello World!\n");
  signaled = false;
}

int main(int argc, char * argv[])
{
  signal(SIGALRM, handler); 
  alarm(1); 
  
  while (1) 
  {
    while(signaled);
    printf("Turing was right!\n");
    
    exit(1);
  }
  
  //busy wait for signal to be delivered
  return 0; //never reached
}