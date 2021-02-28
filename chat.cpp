// Server program
 #include <arpa/inet.h>
 #include <errno.h>
 #include <netinet/in.h>
 #include <signal.h>
 #include <stdio.h>
 #include <stdlib.h>
// #include <strings.h>
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <unistd.h>
 #define PORT 5000
 #define MAXLINE 1024
 #include <string.h>
//#include "chat.h"
class Communication{
    public:
    Communication(){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    bzero(&servaddr, sizeof(servaddr));
    }
    virtual int run(){}
    char* message;
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in cliaddr, servaddr;
    int max(int x, int y)
       {
           if (x > y)
                return x;
              else
                   return y;
                }
};


class Client: public Communication{
    public:
    //int n, len;

    Client(){
    message = "Hello Server";

        // Filling server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    }
    int run()
    {
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {return 0;}
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "Hello Server");
    write(sockfd, buffer, sizeof(buffer));
    printf("Message from server: ");
    read(sockfd, buffer, sizeof(buffer));
    puts(buffer);
    //close(sockfd);
    //exit(0);

}
};


class Server : public  Communication{
  public:
    Server(){
    message = "Hello Client";
        // Filling server information
         servaddr.sin_family = AF_INET;
         servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
         servaddr.sin_port = htons(PORT);

         // binding server addr structure to listenfd
         bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
         listen(sockfd, 10);
         // clear the descriptor set
        // FD_ZERO(&rset);
         // get maxfd
        // maxfdp1 = max(sockfd, udpfd) + 1;
    }

      int listenfd, connfd, udpfd, nready, maxfdp1;
   pid_t childpid;
    fd_set rset;
      ssize_t n;
       socklen_t len;
        const int on = 1;
       void sig_chld(int);


    int run()
  {

  for (;;) {
 // clear the descriptor set
      FD_ZERO(&rset);
   // get maxfd
   maxfdp1 = max(sockfd, udpfd) + 1;
  FD_SET(sockfd, &rset);
   // select the ready descriptor
   nready = select(maxfdp1, &rset, NULL, NULL, NULL);

   // if tcp socket is readable then handle
   // it by accepting the connection
   if (FD_ISSET(sockfd, &rset)) {
    len = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if ((childpid = fork()) == 0) {
      close(sockfd);
      bzero(buffer, sizeof(buffer));
      //printf("Message From TCP client: ");
      if(read(connfd, buffer, sizeof(buffer)))
      printf("Message From TCP client: ");
      puts(buffer);
      write(connfd, (const char*)message, sizeof(buffer));
      close(connfd);
      exit(0);
    }
   close(connfd);
   }
  }
 }
};


int main(){



Communication *comm;
Client *client=new Client();
if(client->run()==0){comm=new Server();delete(client);}
else comm = new Client();
comm->run();



}
