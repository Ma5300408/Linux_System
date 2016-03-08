#include<sys/types.h>
#include<sys/socket.h>

int sendall(int s,char *buf,int *len)
{
  int total = 0;
  int bytesleft = *len;
  int n;

  while(total<*len){
    n = send(s,buf+total,bytesleft,0);
    if(n == -1){break;}
    total += n;
    bytesleft -= n;
  }

  *len = total;
  return n == -1?-1:0;
}

char buf[10] = "Beej!";
int len;

len = strlen(buf);
if(sendall(s, buf, &len)==-1){
  perror("sendall");
  printf("We only sent %d bytes because of the error!\n",len);
}
