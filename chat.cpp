 #include <arpa/inet.h>
 #include <errno.h>
 #include <netinet/in.h>
 #include <signal.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/socket.h>
 #include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
 #include <string.h>
 #define PORT 3111 
 #define MAXLINE 1024

typedef struct {
	int socket;
	struct sockaddr_in addres;
	char* message;
	char buffer[MAXLINE];
} Peer;

#define коммуникация communication
#define Глав main
#define запуск run

class Communication{
	public:
    Communication(){
    //message = "Hello Server";
    //SetSocket(syscall(SYS_socket,AF_INET, SOCK_STREAM, 0));
    //memset(&servaddr, 0, sizeof(servaddr));
 if ( SetSocket(socket(AF_INET, SOCK_STREAM, 0)))  {//man socket
}else{
  printf("socket creation failed");
 // exit(0);
//return 0;
  }
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    }
    Peer peer;    
    fd_set read_fd;
    char* message;
    int  sd, sd2;
    struct sockaddr_in servaddr;
    virtual void run()=0;
    char buffer[MAXLINE];
int new_socket, client_socket[30], max_clients = 30, activity, i, valread; 
int max_sd;
	int GetSocket(){return name;}
	int SetSocket(int sock){name=sock;return name;}
	private:
    int name;
}* communication;

class Client: public Communication{
    public:
    Client(){
        servaddr.sin_addr.s_addr = inet_addr("192.168.1.177");
    //connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));    
}
    void run()
    {
    connect(GetSocket(), (struct sockaddr*)&servaddr, sizeof(servaddr));
	for(;;){
	memset(buffer, 0, sizeof(buffer));
	//man select
	FD_ZERO(&read_fd);
        FD_SET(0, &read_fd);
        FD_SET(GetSocket(), &read_fd);
        select(10, &read_fd, NULL, NULL, NULL);
	if (FD_ISSET(0, &read_fd)){read(0,buffer,sizeof(buffer));dprintf(GetSocket(),buffer);}  //write(sockfd,buffer,sizeof(buffer));}
        //write(sockfd, buffer, sizeof(buffer)); 
        //puts("test");
        if(FD_ISSET(GetSocket(), &read_fd)){read(GetSocket(), buffer, sizeof(buffer));
	//puts("reciving data from server: ");
	//write(0, (const char *)buffer, sizeof(buffer));
	//printf("reciving data from server: %s\n",buffer);
	dprintf(0, "server: "); 	
	dprintf(0,buffer);	
	}
	}        
	close(GetSocket());

    }
    

};



class Server : public Communication{
		public:
	Server()
	{
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(GetSocket(), (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(GetSocket(), 10);
 	for (i = 0; i < max_clients; i++) client_socket[i] = 0;  
	}
	void run(){
//int sin_size = sizeof(struct sockaddr_in);
//sd2 = accept(sockfd, (struct sockaddr *)&cliaddr, &sin_size);    	
	//sd2 = accept(sockfd, NULL, NULL);
	//sd2 = accept(sockfd, NULL, NULL);           
	//addrlen = sizeof(cliaddr); 
	for(;;){
	FD_ZERO(&read_fd);	
        max_sd = GetSocket(); 
	for ( i = 0 ; i < max_clients ; i++) 
		{ 
			//socket descriptor 
			sd = client_socket[i]; 
			//if valid socket descriptor then add to read list 
			if(sd > 0) 
				FD_SET( sd , &read_fd); 
			//highest file descriptor number, need it for the select function 
			if(sd > max_sd) 
				max_sd = sd; 
		} 	
	//FD_ZERO(&read_fd);
        //FD_ZERO(&write_fd);
	FD_SET(0, &read_fd);
	//FD_SET(sd2, &read_fd);
	FD_SET(GetSocket(), &read_fd);	
	//FD_SET(sd2, &write_fd);
	select(max_sd+1, &read_fd, NULL, NULL, NULL);//man select
	//if(FD_ISSET(sd2, &read_fd)){
	//read(sd2, buffer, sizeof(buffer));
	//printf("Received data from the f***ing client: %s\n", buffer);
	//printf("Server-Echoing back to client...\n");
	//}
	//if (FD_ISSET(sd2, &write_fd)){
        //write(sd2, buffer, sizeof(buffer)); 
	//break;
	//}
	//if(FD_ISSET(0, &read_fd)){
        //read(0, buffer, sizeof(buffer));
        
	  //for ( i = 0 ; i < max_clients ; i++) 
            //    { 
                        //socket descriptor 
              //          sd = client_socket[i]; 
                                
                        //if valid socket descriptor then add to read list 
                //      if(sd > 0) 
	//write(sd, (const char *)buffer, sizeof(buffer)); 
	//}	




	//printf("Received data from the f***ing client: %s\n", buffer);
        //printf("Server-Echoing back to client...\n");
        //}
if (FD_ISSET(GetSocket(), &read_fd)) 
		{
 	 //sd2=accept(sockfd, NULL, NULL);    
	//close(sd2);      
	while ((new_socket = accept(GetSocket(),NULL,NULL))<=0)//man accept
//accept(sockfd,(struct sockaddr *)&cliaddr, (socklen_t*)&addrlen))<=0) 
			{ 
			//close(new_socket);
			}
			
while ((new_socket = accept(GetSocket(),NULL,NULL))<=0)//accept(sockfd,(struct sockaddr *)&cliaddr, (socklen_t*)&addrlen))<=0) 
				{}

//inform user of socket number - used in send and receive commands 
//printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(cliaddr.sin_addr) , ntohs	(cliaddr.sin_port)); 
printf("New connection %d\n",new_socket);	
//write(new_socket, "welcome ", 20);
//write (new_socket,"new_socket",10); 

dprintf(new_socket,"welcome %d\n",new_socket);	
			//send new connection greeting message 
		//if( send(new_socket, message, strlen(message), 0) != strlen(message) ) 
		//	{ 
		//		perror("send"); 
		//	} 
				
			puts("Welcome message sent successfully"); 
			//add new socket to array of sockets 
			for (i = 0; i < max_clients; i++) 
			{ 
				//if position is empty 
				if( client_socket[i] == 0) 
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
				if ((valread = read( sd , buffer, 1024)) == 0)//man read 
				{ 
					//Somebody disconnected , get his details and print 
					//getpeername(sd , (struct sockaddr*)&cliaddr , (socklen_t*)&addrlen); 
					//printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(cliaddr.sin_addr) , ntohs(cliaddr.sin_port)); 
					//Close the socket and mark as 0 in list for reuse 
				
					printf("Host disconnected %d \n" , i); 
					close( sd ); 
					client_socket[i] = 0; 
				} 
				//Echo back the message that came in 
				else
				{ 
       //valread = read(sd, buffer, sizeof(buffer));
       buffer[valread] = '\0';  
          for ( i = 0 ; i < max_clients ; i++) 
                { 
                        //socket descriptor 
                        sd = client_socket[i]; 
                        //if valid socket descriptor then add to read list 
                      if(sd > 0)
dprintf(sd,buffer); 
       // write(sd, (const char *)buffer, sizeof(buffer)); 
       if (i==max_clients-1)printf("%s\n",buffer);//write(0, (const char *)buffer, 20);
}       






					//set the string terminating NULL byte on the end 
					//of the data read 
					//buffer[valread] = '\0'; 
					//write(sd , buffer , strlen(buffer) ); 
				} 
			} 
		} 
//printfv("Received data from the econd client: %s\n", buffer);
	}
	close(sd2);
	close(GetSocket());
	/*exit(0);*/
	/*return 0;*/
	}
};









int Глав(){


//Communication *comm;

 int sockfd;

  char buffer[MAXLINE];
  //char* message = "Hello Server";
  struct sockaddr_in servaddr;

  int n, len;
  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
  printf("socket creation failed");
  //exit(0);
return 0;
  }
  //memset(&servaddr, 0, sizeof(servaddr));
  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = inet_addr("192.168.1.177");
  if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
close (sockfd);
 communication=new Server();
}else {close (sockfd);
communication=new Client();
}
    коммуникация->запуск();

}
