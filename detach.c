#include<errno.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void *threadfunc(void *param)
{
  printf("Inside secondary thread\n");
  sleep(3);
  printf("Exit secondary thread\n");
  pthread_exit(NULL);
}

int main(int argc,char ** argv)
{
   pthread_t thread;
   int rc = 0;
   printf("Create a thread using attributes that allow detach\n");
   rc = pthread_create(&thread,NULL,threadfunc,NULL);
   if(rc){
     printf("ERROR; return code from pthread create() is %d\n",rc);
     exit(-1);
   }   

   printf("Detach the thread after it terminates\n");
   rc = pthread_detach(thread);
   if(rc){
     printf("ERROR; return code from pthread detach() %d\n",rc);
     exit(-1);
   }

   printf("Detach the thread again\n");
   rc = pthread_detach(thread);

   if(rc != EINVAL){
     printf("Got an unexpected result! rc=%d\n",rc);
     exit(1);
   }

   printf("Second detach fails as expected.\n");

   sleep(6);
   printf("Main() completed.\n");
   return 0;
}
