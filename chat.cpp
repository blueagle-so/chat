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
	//char *p;
        //int n;

        //errno = 0;
        ///scanf("%m[a-z]", &buffer);
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
    int sd;
    //int totalcnt = 0, on = 1;
int master_socket , addrlen , new_socket , client_socket[30], max_clients = 30 , activity, i , valread ; 
	int max_sd; 

	Server()
	{
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(sockfd, 10);
 	for (i = 0; i < max_clients; i++) 
        { 
                client_socket[i] = 0; 
        } 	


}
	void run(){
//int sin_size = sizeof(struct sockaddr_in);
//sd2 = accept(sockfd, (struct sockaddr *)&cliaddr, &sin_size);    	
	//sd2 = accept(sockfd, NULL, NULL);
	//sd2 = accept(sockfd, NULL, NULL);           
	addrlen = sizeof(cliaddr); 
	for(;;){
	FD_ZERO(&read_fd);	
        max_sd = sockfd; 
	for ( i = 0 ; i < max_clients ; i++) 
        { 
        //socket descriptor 
        sd = client_socket[i]; 
        //if valid socket descriptor then add to read list 
        if(sd > 0) 
        FD_SET( sd , &read_fd); 
	}
	//FD_ZERO(&read_fd);
        //FD_ZERO(&write_fd);
	FD_SET(0, &read_fd);
	//FD_SET(sd2, &read_fd);
	FD_SET(sockfd, &read_fd);	
	//FD_SET(sd2, &write_fd);
	select(max_sd+1, &read_fd, &write_fd, NULL, NULL);
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


if (FD_ISSET(sockfd, &read_fd)) 
		{ 
			if ((new_socket = accept(sockfd,(struct sockaddr *)&cliaddr, (socklen_t*)&addrlen))<0) 
			{ 
				perror("accept"); 
				exit(EXIT_FAILURE); 
			} 
			
			//inform user of socket number - used in send and receive commands 
			printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(cliaddr.sin_addr) , ntohs	(cliaddr.sin_port)); 
		
			//send new connection greeting message 
			if( send(new_socket, message, strlen(message), 0) != strlen(message) ) 
			{ 
				perror("send"); 
			} 
				
			puts("Welcome message sent successfully"); 
				
			//add new socket to array of sockets 
			for (i = 0; i < max_clients; i++) 
			{ 
				//if position is empty 
				if( client_socket[i] == 0 ) 
				{ 
					client_socket[i] = new_socket; 
					printf("Adding to list of sockets as %d\n" , i); 
						
					break; 
				} 
			} 
		} 
			
		//else its some IO operation on some other socket 
		for (i = 0; i < max_clients; i++) 
		{ 
			sd = client_socket[i]; 
				
			if (FD_ISSET( sd , &read_fd )) 
			{ 
				//Check if it was for closing , and also read the 
				//incoming message 
				if ((valread = read( sd , buffer, 1024)) == 0) 
				{ 
					//Somebody disconnected , get his details and print 
					getpeername(sd , (struct sockaddr*)&cliaddr , (socklen_t*)&addrlen); 
					printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(cliaddr.sin_addr) , ntohs(cliaddr.sin_port)); 
						
					//Close the socket and mark as 0 in list for reuse 
					close( sd ); 
					client_socket[i] = 0; 
				} 
					
				//Echo back the message that came in 
				else
				{ 
					//set the string terminating NULL byte on the end 
					//of the data read 
					buffer[valread] = '\0'; 
					send(sd , buffer , strlen(buffer) , 0 ); 
				} 
			} 
		} 











//printfv("Received data from the econd client: %s\n", buffer);
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
