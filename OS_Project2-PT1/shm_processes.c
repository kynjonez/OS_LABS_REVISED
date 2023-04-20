// <Author - Kyndall Jones>
// Collaborated with: Zoe Carter and Abigial Thomas
// Resources: stackoverflow and geeksforgeeks

#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
sem_t *mutex;

void  ChildProcess(int *SharedMem) 
{
  int i, acc_ID, rand_num;
  srand(getpid());

  for(i=0; i<25; i++) {
    sleep(rand() % 6);
    sem_wait(mutex);
    acc_ID = *SharedMem;
    rand_num = rand() % 51;
    printf("Poor student needs $%d\n", rand_num);

    if (rand_num <= acc_ID)
    {
      acc_ID -= rand_num;
      printf("Poor Student: Withdraws $%d / Balance = $%d\n", rand_num, acc_ID);
      *SharedMem = acc_ID;
    }
    else {
      printf("Poor Student: Not Enough Cash ($%d)\n", acc_ID);
    }
    sem_post(mutex);
  }
}

void ParentProcess(int *SharedMem)
{
  int i, acc_ID, rand_num;
  srand(getpid());

  for (i=0; i<25; i++) {
    sleep(rand() % 6);
    sem_wait(mutex);
    acc_ID = *SharedMem;
    if (acc_ID <= 100) {
      rand_num = rand() % 101;
      if (rand_num % 2 == 0) {
        acc_ID += rand_num;
        printf("Dear old Dad: Deposits $%d / Balance = $%d\n", rand_num, acc_ID);
      }
      else {
        printf("Dear old Dad: Doesn't have any money to give\n");
      }
      *SharedMem = acc_ID;
    }
    else {
      printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", acc_ID);
    }
    sem_post(mutex);
  }
}

int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;

     if((mutex = sem_open("examplesemaphore", O_CREAT, 0644, 1)) == SEM_FAILED)
     {
       perror("semaphore initilization");
       exit(1);
     }

     // one
     ShmID = shmget(IPC_PRIVATE, 4*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     printf("Server has received a shared memory of four integers...\n");

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     printf("Server has attached the shared memory...\n");

     *ShmPTR = 0;

     printf("Main is about to fork a child process...\n");
     pid = fork();
     if (pid < 0) {
       printf("*** fork error (Main) ***\n");
       exit(1);
     }
     else if (pid == 0) {
       ChildProcess(ShmPTR);
     }
     else {
       ParentProcess(ShmPTR);
    }

     wait(&status);
     printf("Server has detected the completion of its child...\n");
     shmdt((void *) ShmPTR);
     printf("Server has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Server has removed its shared memory...\n");
     printf("Server exits...\n");
     exit(0);
}