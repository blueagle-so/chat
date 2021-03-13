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
    //message = "Hello Server";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    }
    Peer peer;    
    fd_set read_fd, write_fd;
    char* message;
    int sockfd, sd2;
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
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	for(;;){
	memset(buffer, 0, sizeof(buffer));
	FD_ZERO(&read_fd);
        FD_ZERO(&write_fd);
        FD_SET(0, &read_fd);
        FD_SET(sockfd, &read_fd);
        //FD_SET(sockfd, &write_fd);
        select(10, &read_fd, &write_fd, NULL, NULL);
	if (FD_ISSET(0, &read_fd)){read(0,buffer,sizeof(buffer));write(sockfd,buffer,sizeof(buffer));}
        //write(sockfd, buffer, sizeof(buffer)); 
        //puts("test");
        if(FD_ISSET(sockfd, &read_fd)){read(sockfd, buffer, sizeof(buffer));
	//puts("reciving data from server: ");
	//write(0, (const char *)buffer, sizeof(buffer));
	printf("reciving data from server: %s\n",buffer);
	}
        //printf("Server-Echoing back to client...\n");}
        //if(FD_ISSET(sockfd, &write_fd)) write(sockfd, buffer, sizeof(buffer)); 
	}
        close(sockfd);

    }
    

};





/* BufferLength is 100 bytes */
#define BufferLength 100
/* Server port number */
#define SERVPORT 3111
class Server : public Communication{
		public:
    /* Variable and structure definitions. */
    //int sd, sd2, rc, length = sizeof(int);
    //int totalcnt = 0, on = 1;
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
	//sd2 = accept(sockfd, NULL, NULL);           
	for(;;){
        sd2 = accept(sockfd, NULL, NULL);           
	memset(buffer, 0, sizeof(buffer));
	FD_ZERO(&read_fd);
        FD_ZERO(&write_fd);
	FD_SET(0, &read_fd);
	FD_SET(sd2, &read_fd);
	//FD_SET(sd2, &write_fd);
	select(sd2+1, &read_fd, &write_fd, NULL, NULL);
	if(FD_ISSET(sd2, &read_fd)){
	read(sd2, buffer, sizeof(buffer));
	printf("Received data from the f***ing client: %s\n", buffer);
	//printf("Server-Echoing back to client...\n");
	}
	//if (FD_ISSET(sd2, &write_fd)){
        //write(sd2, buffer, sizeof(buffer)); 
	//break;
	//}
	if(FD_ISSET(0, &read_fd)){
        read(0, buffer, sizeof(buffer));
        write(sd2, (const char *)buffer, sizeof(buffer)); 
	//printf("Received data from the f***ing client: %s\n", buffer);
        //printf("Server-Echoing back to client...\n");
        }
	}
	close(sd2);
	close(sockfd);
	/*exit(0);*/
	/*return 0;*/
	}
};









int main(){


Communication *comm;

 int sockfd;

  char buffer[MAXLINE];
  //char* message = "Hello Server";
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
