#include "unp.hpp"
using namespace std;

int main(int argc, char* argv[])
{
   int listenfd, connfd;
   struct sockaddr_in serverAddr;
   char buff[MAXLINE];
   time_t ticks;

   listenfd = Socket(AF_INET, SOCK_STREAM, 0);
   memset(&serverAddr, 0, sizeof(serverAddr));

   serverAddr.sin_family = AF_INET;
   serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   serverAddr.sin_port = htons(12585);

   Bind(listenfd, (SA *)&serverAddr, sizeof(serverAddr));

   Listen(listenfd, LISTENQ);

   while(true)
   {
      connfd = Accept(listenfd, (SA*)NULL, NULL);

      ticks = time(0);
      snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
      Write(connfd, buff, strlen(buff));

      Close(connfd);
   }

   return 0;
}

