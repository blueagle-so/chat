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
 #define PORT 3111 
 #define MAXLINE 1024
 #include <string.h>
//#include "chat.h"
class Communication{
    public:
    //int PORT= 5000;
    //    //int MAXLINE= 1024;
    char* message;
    int sockfd;
    struct sockaddr_in servaddr,cliaddr;
    virtual void run(){}


};


class Client: public Communication{
    public:
    Client(){
    message = "Hello Server";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    }
    void run()
    {
    char buffer[MAXLINE];
    int n, len;

    if (connect(sockfd, (struct sockaddr*)&servaddr,
    sizeof(servaddr)) < 0) {
    printf("\n Error : Connect Failed \n");
    }
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "Hello Server");
    write(sockfd, buffer, sizeof(buffer));
    printf("Message from server: ");
    read(sockfd, buffer, sizeof(buffer));
    puts(buffer);
    //close(sockfd);
    }
};





#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/time.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <errno.h>

#include <unistd.h>

/* BufferLength is 100 bytes */

#define BufferLength 100

/* Server port number */

#define SERVPORT 3111

class Server : public Communication{
		public:

    /* Variable and structure definitions. */

    int sd, sd2, rc, length = sizeof(int);

    int totalcnt = 0, on = 1;

    char temp;

      char buffer[BufferLength];

       struct sockaddr_in serveraddr;

      struct sockaddr_in their_addr;

					         

									        fd_set read_fd;

										        struct timeval timeout;

									        /*timeout.tv_sec = 15;*/

									        /*timeout.tv_usec = 0;*/	
													
											Server()

											{
	 timeout.tv_sec = 15;

         timeout.tv_usec = 0;    


	/* The socket() function returns a socket descriptor */

	/* representing an endpoint. The statement also */

	/* identifies that the INET (Internet Protocol) */

 	/* address family with the TCP transport (SOCK_STREAM) */

	/* will be used for this socket. */

 	/************************************************/

 	/* Get a socket descriptor */

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)

	{

	perror("Server-socket() error");

	/* Just exit */

	exit (-1);

	}

	else

	printf("Server-socket() is OK\n");

																		 

	/* The setsockopt() function is used to allow */

	/* the local address to be reused when the server */

	/* is restarted before the required wait time */

	/* expires. */

	/***********************************************/

	/* Allow socket descriptor to be reusable */

	if((rc = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on))) < 0)

	{

	perror("Server-setsockopt() error");

	close(sd);

	exit (-1);

	}

	else

	printf("Server-setsockopt() is OK\n");

																				 

	/* bind to an address */

	memset(&serveraddr, 0, sizeof(struct sockaddr_in));

	serveraddr.sin_family = AF_INET;

	serveraddr.sin_port = htons(SERVPORT);

	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

																								/*printf("Using %s, listening at %d\n", inet_ntoa(serveraddr.sin_addr), SERVPORT);*/


	/* After the socket descriptor is created, a bind() */

	/* function gets a unique name for the socket. */

	/* In this example, the user sets the */

	/* s_addr to zero, which allows the system to */

	/* connect to any client that used port 3005. */

	if((rc = bind(sd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0)

	{

	perror("Server-bind() error");

											/* Close the socket descriptor */
																															close(sd);

	/* and just exit */

											exit(-1);

	}

	else

	printf("Server-bind() is OK\n");

																 
	/* The listen() function allows the server to accept */

	/* incoming client connections. In this example, */

	/* the backlog is set to 10. This means that the */

	/* system can queue up to 10 connection requests before */

	/* the system starts rejecting incoming requests.*/

	/*************************************************/

	/* Up to 10 clients can be queued */

	if((rc = listen(sd, 10)) < 0)

	{

        perror("Server-listen() error");

        close(sd);

        exit (-1);

    	}

	else

	printf("Server-Ready for client connection...\n");

	}
											void run(){

											/* The server will accept a connection request */

	/* with this accept() function, provided the */

	/* connection request does the following: */
											/* - Is part of the same address family */

	/* - Uses streams sockets (TCP) */
											/* - Attempts to connect to the specified port */
											/***********************************************/
											/* accept() the incoming connection request. */

	int sin_size = sizeof(struct sockaddr_in);

	if((sd2 = accept(sd, (struct sockaddr *)&their_addr, &sin_size)) < 0)

	{

	perror("Server-accept() error");

	close(sd);

	exit (-1);

	}

	else

	printf("Server-accept() is OK\n");

	/*client IP*/

	printf("Server-new socket, sd2 is OK...\n");

	/*printf("Got connection from the f***ing client: %s\n", inet_ntoa(their_addr.sin_addr));*/

												 
	/* The select() function allows the process to */
	/* wait for an event to occur and to wake up */
	/* the process when the event occurs. In this */
	/* example, the system notifies the process */
	/* only when data is available to read. */

	/***********************************************/

	/* Wait for up to 15 seconds on */

	/* select() for data to be read. */

	FD_ZERO(&read_fd);

	FD_SET(sd2, &read_fd);

	rc = select(sd2+1, &read_fd, NULL, NULL, NULL);

	if((rc == 1) && (FD_ISSET(sd2, &read_fd)))

	{

	/* Read data from the client. */

	totalcnt = 0;

																							 

	while(totalcnt < BufferLength)

	{

	/* When select() indicates that there is data */

	/* available, use the read() function to read */

	/* 100 bytes of the string that the */

	/* client sent. */

	/***********************************************/

	/* read() from client */

	rc = read(sd2, &buffer[totalcnt], (BufferLength - totalcnt));

	if(rc < 0)

	{

	perror("Server-read() error");

	close(sd);

	close(sd2);

	exit (-1);

	}

	else if (rc == 0)

	{

	printf("Client program has issued a close()\n");

	close(sd);

	close(sd2);

	exit(-1);

	}

	else

	{

	totalcnt += rc;

	printf("Server-read() is OK\n");

	}

	}

	}

																					else if (rc < 0)

	{

	perror("Server-select() error");

	close(sd);

	close(sd2);

	exit(-1);

	}

	/* rc == 0 */

	else

	{

	printf("Server-select() timed out.\n");

	close(sd);

	close(sd2);

	exit(-1);

	}

	/* Shows the data */

	printf("Received data from the f***ing client: %s\n", buffer);

	/* Echo some bytes of string, back */

	/* to the client by using the write() */

	/* function. */

	/************************************/

	/* write() some bytes of string, */

	/* back to the client. */

	printf("Server-Echoing back to client...\n");

	rc = write(sd2, buffer, totalcnt);

	if(rc != totalcnt)

	{

	perror("Server-write() error");

	/* Get the error number. */

	rc = getsockopt(sd2, SOL_SOCKET, SO_ERROR, &temp, &length);

	if(rc == 0)

	{

	/* Print out the asynchronously */

	/* received error. */

	errno = temp;

	perror("SO_ERROR was: ");

	}

	else

	printf("Server-write() is OK\n");

	close(sd);

	close(sd2);

	exit(-1);

	}

	/* When the data has been sent, close() */

	/* the socket descriptor that was returned */

	/* from the accept() verb and close() the */

	/* original socket descriptor. */

	/*****************************************/

	/* Close the connection to the client and */

	/* close the server listening socket. */

	/******************************************/

	close(sd2);

	close(sd);

	/*exit(0);*/

	/*return 0;*/

	}
};











class Server1 : public  Communication{
  public:
int max(int x, int y)
 {
  if (x > y)
   return x;
   else
   return y;
  }
    Server1(){
    message = "Hello Client";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
bzero(&servaddr, sizeof(servaddr));
        // Filling server information
         servaddr.sin_family = AF_INET;
         servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
         servaddr.sin_port = htons(PORT);


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

  // binding server addr structure to listenfd
   bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
   listen(sockfd, 10);

   /* create UDP socket */
   udpfd = socket(AF_INET, SOCK_DGRAM, 0);
   // binding server addr structure to udp sockfd
   bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

  // clear the descriptor set
  FD_ZERO(&rset);

  // get maxfd
  maxfdp1 = max(sockfd, udpfd) + 1;
  for (;;) {

  // set listenfd and udpfd in readset
  FD_SET(sockfd, &rset);
  FD_SET(udpfd, &rset);

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
   printf("Message From TCP client: ");
   read(connfd, buffer, sizeof(buffer));
   puts(buffer);
   write(connfd, (const char*)message, sizeof(buffer));
   close(connfd);
   exit(0);
   }
   close(connfd);
   }
   // if udp socket is readable receive the message.
   if (FD_ISSET(udpfd, &rset)) {
   len = sizeof(cliaddr);
   bzero(buffer, sizeof(buffer));
   printf("\nMessage from UDP client: ");
   n = recvfrom(udpfd, buffer, sizeof(buffer), 0,
   (struct sockaddr*)&cliaddr, &len);
   puts(buffer);
   sendto(udpfd, (const char*)message, sizeof(buffer), 0,
   (struct sockaddr*)&cliaddr, sizeof(cliaddr));
   }
  }
 }
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
//puts(getsockname(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) ;





	                          //  comm=new Server();
	                            //  }else {comm=new Client();}
	                            //  close (sockfd);
	                             //     comm->run();
	   

//  Server server;
//  server.run();
  Client client;
  client.run();




}
