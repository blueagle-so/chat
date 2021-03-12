 #include <arpa/inet.h>
 #include <errno.h>
 #include <netinet/in.h>
 #include <signal.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <unistd.h>
 #define PORT 3111 
 #define MAXLINE 1024
 #include <string.h>

typedef struct {
	int socket;
	struct sockaddr_in addres;
	char* message;
	char buffer[MAXLINE];
} Peer;

class Communication{
    public:
    Communication(){
    message = "Hello Server";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    }
    Peer peer;    
    fd_set read_fd, write_fd;
    char* message;
    int sockfd;
    struct sockaddr_in servaddr,cliaddr;
    virtual void run(){}
    char buffer[MAXLINE];

};


class Client: public Communication{
    public:
    Client(){
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }
    void run()
    {
    //int n, len;

    if (connect(sockfd, (struct sockaddr*)&servaddr,
    sizeof(servaddr)) < 0) {
    printf("\n Error : Connect Failed \n");
    }
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "Hello Server");
    //write(0,"input message: ",15);
    //read(0,buffer,sizeof(buffer));
    write(sockfd, buffer, sizeof(buffer));
    printf("Message from server: ");
    read(sockfd, buffer, sizeof(buffer));
    puts(buffer);
    //close(sockfd);
/*
  fd_set rset;
for(;;){
          sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr)); //{
	FD_ZERO(&rset);	
     FD_SET(0, &rset);
     FD_SET(sockfd, &rset); 
       select(10, &rset, NULL, NULL, NULL);
 if (FD_ISSET(0, &rset)){
    //   connect(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr)); //{

	    read(0,buffer,sizeof(buffer));
       //printf("\n Error : Connect Failed \n");
    //}
    //memset(buffer, 0, sizeof(buffer));
    //strcpy(buffer, "Hello Server");
    write(sockfd, buffer, sizeof(buffer));
    //printf("Message from server: ");
    //read(sockfd, buffer, sizeof(buffer));
    //puts(buffer);
 //   close(sockfd);
    
 }
   //        sockfd = socket(AF_INET, SOCK_STREAM, 0);   
 //FD_SET(0, &rset);
   /// select(10, &rset, NULL, NULL, NULL);
 if (FD_ISSET(sockfd, &rset)){
     read(sockfd, buffer, sizeof(buffer)); 
printf("Message from server: ");
     puts(buffer);
 
 }
 }
*/
    }
    

};





/* BufferLength is 100 bytes */
#define BufferLength 100
/* Server port number */
#define SERVPORT 3111
class Server : public Communication{
		public:
    /* Variable and structure definitions. */
    int sd, sd2, rc, length = sizeof(int);
    int totalcnt = 0, on = 1;
	Server()
	{
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(sockfd, 10);
	}
	void run(){
//int sin_size = sizeof(struct sockaddr_in);
//sd2 = accept(sockfd, (struct sockaddr *)&cliaddr, &sin_size);    	
	sd2 = accept(sockfd, NULL, NULL);
	sd2 = accept(sockfd, NULL, NULL);           
	for(;;){
	FD_ZERO(&read_fd);
        FD_ZERO(&write_fd);
	FD_SET(0, &read_fd);
	FD_SET(sd2, &read_fd);
	FD_SET(sd2, &write_fd);
	select(sd2+1, &read_fd, &write_fd, NULL, NULL);
	if(FD_ISSET(sd2, &write_fd))
	read(sd2, &buffer[totalcnt], (BufferLength - totalcnt));
	printf("Received data from the f***ing client: %s\n", buffer);
	printf("Server-Echoing back to client...\n");
	if (FD_ISSET(sd2, &write_fd)){
        write(sd2, buffer, sizeof(buffer)); 
	break;}
	}
	close(sd2);
	close(sockfd);
	/*exit(0);*/
	/*return 0;*/
	}
/*
    }
 void run()
  {
  int listenfd, connfd, udpfd, nready, maxfdp1;
  char buffer[MAXLINE];
  pid_t childpid;
  fd_set rset;
  ssize_t n;
  socklen_t len;
  const int on = 1;
  void sig_chld(int);
//for(;;){
  //   sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// binding server addr structure to listenfd
   bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
   listen(sockfd, 10);

   // create UDP socket 
   //udpfd = socket(AF_INET, SOCK_DGRAM, 0);
   // binding server addr structure to udp sockfd
   //bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

   for(;;){
  // clear the descriptor set
  FD_ZERO(&rset);

  // get maxfd
  maxfdp1 = max(sockfd, udpfd) + 1;
  //for (;;) {

  // set listenfd and udpfd in readset
  FD_SET(sockfd, &rset);
  FD_SET(0, &rset);

   // select the ready descriptor
   nready = select(maxfdp1, &rset, NULL, NULL, NULL);

   // if tcp socket is readable then handle
   // it by accepting the connection
   if (FD_ISSET(sockfd, &rset)) {
   len = sizeof(cliaddr);
   connfd = accept(sockfd, NULL, NULL);
   if ((childpid = fork()) == 0) {
   //close(sockfd);
   bzero(buffer, sizeof(buffer));
   printf("Message From TCP client: ");
   read(connfd, buffer, sizeof(buffer));
   puts(buffer);
   write(connfd, buffer, sizeof(buffer));
   close(connfd);
   exit(0);
   }
   close(connfd);
   }
   // if udp socket is readable receive the message.
   if (FD_ISSET(0, &rset)) {
   connfd = accept(sockfd, NULL, NULL);
     if ((childpid = fork()) == 0) {
	   //    close(sockfd);
	         bzero(buffer, sizeof(buffer));
		   //printf("Message From TCP client: ");
		     read(0, buffer, sizeof(buffer));
		       puts(buffer);
		         write(connfd, (const char*)buffer, sizeof(buffer));
			   close(connfd);
			     exit(0);
			       }
       close(connfd);
         } 
   


 	  
   }
 }
*/
};









int main(){


Communication *comm;

 int sockfd;

  char buffer[MAXLINE];
  char* message = "Hello Server";
  struct sockaddr_in servaddr;

  int n, len;
  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
  printf("socket creation failed");
  exit(0);
  }
  memset(&servaddr, 0, sizeof(servaddr));
  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (connect(sockfd, (struct sockaddr*)&servaddr,
  sizeof(servaddr)) < 0) {
  comm=new Server();
  }else {comm=new Client();}
close (sockfd);
    comm->run();



}
