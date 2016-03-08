#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

pid_t childpid;

void childfunc(void)
{
   int retval;
   
   printf("CHILD: I am the child process!\n");
   printf("CHILD: My PID: %d\n",getpid());
   printf("CHILD: My parent's PID is : %d\n",getppid());
   printf("CHILD: Sleeping for 1 second...\n");
   sleep(1);

   printf("CHILD: Enter an exit value (0 to 255):");
   scanf("%d",&retval);
   printf("CHILD: Goodbye!\n");
 
   exit(retval);
}



void parentfunc(void)
{
   int status;

   printf("PARENT: I am the parent process!\n");
   printf("PARENT: My PID: %d\n",getpid());
   printf("PARENT: My child's PID is %d\n", childpid);
   printf("PARENT: I will now wait for my child to exit.\n");


   wait(&status);
   printf("PARENT: Child's exit code is: %d\n",WEXITSTATUS(status));
   printf("PARENT: Goodbye!\n");

   exit(0);
}

int main(int argc, char *argv[])
{
  childpid = fork();

  if(childpid >= 0){
     if(childpid == 0){
       childfunc();
     }else {
      parentfunc();
     }

  } else {
      perror("fork");
      exit(0);
  }


  return 0;
}
