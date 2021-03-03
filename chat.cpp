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
typedef struct {
int socket;
struct sockaddr_in addres;
char* message;
char buffer[MAXLINE];
} Peer;


class Communication{
    public:
    Communication(){
    peer.socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&peer.addres, 0, sizeof(peer.addres));
    bzero(&peer.addres, sizeof(peer.addres));
    }
    virtual int run(){}
    Peer peer;
    //char* message;
    //int sockfd;
    //char buffer[MAXLINE];
    //struct sockaddr_in cliaddr, servaddr;
};


class Client: public Communication{
    public:
    //int n, len;

    Client(){
    peer.message = "Hello Server";

        // Filling server information
        peer.addres.sin_family = AF_INET;
        peer.addres.sin_port = htons(PORT);
        peer.addres.sin_addr.s_addr = inet_addr("127.0.0.1");

    }
    int run()
    {
      for (;;){
       fd_set rfds;
       struct timeval tv;
       int retval;
       // Watch stdin (fd 0) to see when it has input.
        FD_ZERO(&rfds);
       FD_SET(0, &rfds);
       FD_SET(peer.socket,&rfds);
       // Wait up to five seconds.
       retval = select(1, &rfds, NULL, NULL, NULL);
       // Don't rely on the value of tv now!
       ///if (retval == -1)
      //perror("select()");
      //else if (retval)
      //printf("Data is available now.\n");
    if(FD_ISSET(0, &rfds)){
     //else
   // printf("No data within five seconds.\n");


        peer.socket = socket(AF_INET, SOCK_STREAM, 0);
      if (connect(peer.socket, (struct sockaddr*)&peer.addres, sizeof(peer.addres)) < 0) {return 0;}
    memset(peer.buffer, 0, sizeof(peer.buffer));
    //strcpy(buffer, "Hello Server");
    read(0, peer.buffer, sizeof(peer.buffer));
    write(peer.socket, peer.buffer, sizeof(peer.buffer));
    printf("Message from server: ");
    read(peer.socket, peer.buffer, sizeof(peer.buffer));
    puts(peer.buffer);
    close(peer.socket);
    }
   
    if(FD_ISSET(peer.socket, &rfds)){

    
  peer.socket = socket(AF_INET, SOCK_STREAM, 0);
  if (connect(peer.socket, (struct sockaddr*)&peer.addres, sizeof(peer.addres)) < 0) {return 0;}
          memset(peer.buffer, 0, sizeof(peer.buffer));
	    // strcpy(buffer, "Hello Server");
	        read(peer.socket, peer.buffer, sizeof(peer.buffer));
	      //     write(sockfd, buffer, sizeof(buffer));
	       printf("Message from server: ");
        read(peer.socket, peer.buffer, sizeof(peer.buffer));
    puts(peer.buffer);
    close(peer.socket);    
    
    }
      }
    exit(0);

}
};


class Server : public  Communication{
  public:
    Server(){
    peer.message = "Hello Client";
        // Filling server information
         peer.addres.sin_family = AF_INET;
         peer.addres.sin_addr.s_addr = htonl(INADDR_ANY);
         peer.addres.sin_port = htons(PORT);

         // binding server addr structure to listenfd
         bind(peer.socket, (struct sockaddr*)&peer.addres, sizeof(peer.addres));
         listen(peer.socket, 10);
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
   maxfdp1 =  10;
  FD_SET(peer.socket, &rset);
    FD_SET(0, &rset); 
  // select the ready descriptor
   nready = select(maxfdp1, &rset, NULL, NULL, NULL);

   // if tcp socket is readable then handle
   // it by accepting the connection
   if (FD_ISSET(peer.socket, &rset)) {
    len = sizeof(peer.addres);
    connfd = accept(peer.socket, (struct sockaddr*)&peer.addres, &len);
    if ((childpid = fork()) == 0) {
      close(peer.socket);
      bzero(peer.buffer, sizeof(peer.buffer));
      //printf("Message From TCP client: ");
      if(read(connfd, peer.buffer, sizeof(peer.buffer)))
      printf("Message From TCP client: ");
      puts(peer.buffer);
      write(connfd, (const char*)peer.message, sizeof(peer.buffer));
      close(connfd);
      exit(0);
    }
   close(connfd);
   }
    if (FD_ISSET(0, &rset)) {
    len = sizeof(peer.addres);
    connfd = accept(peer.socket, (struct sockaddr*)&peer.addres, &len);
    if ((childpid = fork()) == 0) {
   close(peer.socket);
    bzero(peer.buffer, sizeof(peer.buffer));
    //printf("Message From TCP client: ");
    read(0, peer.buffer, sizeof(peer.buffer));
     //printf("Message From stdin: ");
     //puts(buffer);
      write(connfd, (const char*)peer.buffer, sizeof(peer.buffer));
     close(connfd);
      exit(0);
      }
 	}
   close(connfd); 
  
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
