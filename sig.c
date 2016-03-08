#include<signal.h>
#include<stdio.h>
#include<unistd.h>


void IGotSignal (int sig)
{
   printf("I got a signal %d\n\r", sig);
   (void)signal(SIGINT, SIG_DFL);
}

int main(int argc, char ** argv)
{
   printf("You See See You\n");
 (void) signal(SIGINT, IGotSignal);

  for(;;)
  {
    printf("Waiting!!\n\r");
    sleep(5);
  }

return 1;
}
