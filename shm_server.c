#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>

#define SHMSZ 27

int main(int argc, char * argv[])
{
   char c;
   int shmid;
   key_t key;
   char *shm, *s;
   int retval;

   key = 5678;

   if( (shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0){
      perror("shmget");
      exit(1);
   }

   if( (shm = shmat(shmid, NULL, 0)) == (char *) -1){
      perror("shmat");
      exit(1);
   }

   printf("Server create and attach the share memory.\n");

    shm = (char*)malloc(sizeof(char)*SHMSZ);
    s = shm;

    printf("Server write a ~ z to share memory.\n");
    for(c = 'a'; c <= 'z'; c++){*s= c; s++; }
   *s = '\0';

   printf("Waiting other process read the share memory\n");
   while(*shm !='*')
     sleep(1);
   printf("Server read from the share memory.\n");

   shmdt(shm);

   printf("Server destroy the share memory.\n");
   retval = shmctl(shmid, IPC_RMID,NULL);
   if(retval < 0)
   {
     fprintf(stderr,"Server remove share memory failed\n");
     exit(1);
   }

  return 0;
}
