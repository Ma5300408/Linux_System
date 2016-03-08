#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>
#include<unistd.h>

pid_t childpid;

void childfunc(void)
{
  int randtime;
  int exitstatus;

  printf("CHILD: I am the child process!\n");
  printf("CHILD: My PID: %d\n",getpid());
  
  srand(time(NULL));
  randtime = rand() % 5;
  printf("CHILD: Sleeping for %d second...\n", randtime);
  sleep(randtime);

  exitstatus = rand() % 2;
  printf("CHILD: Exit status is %d\n",exitstatus);


  printf("CHILD: Goodbye!\n");
  exit(exitstatus);
}

void parentfunc(void)
{
   int status;
   pid_t pid;

   printf("PARENT: I am the parent process!\n");
   printf("PARENT: My PID: %d\n",getpid());

   printf("PARENT: I will now wait for my child to exit.\n");

    do
    {
      pid = waitpid(childpid, &status, WNOHANG);
      printf("PARENT: Waiting child exit...\n");
      sleep(1);
    }while(pid != childpid);

    if(WIFEXITED(status)){
      printf("PARENT: Child's exit code is: %d\n",WEXITSTATUS(status));

    }else{
      printf("PARENT: Child process executed but exited failed.\n");
    }

  printf("PARENT: Goodbye!\n");    
  exit(0);
}

int main(int argc , char * argv[])
{
   childpid = fork();
   
   if(childpid >= 0){
      if(childpid == 0){
         childfunc();
       } else {
          parentfunc();
      }
   } else {
      perror("fork");
      exit(0);
    }
   
  return 0;
}
