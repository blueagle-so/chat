module;
#include <arpa/inet.h>  //inet_addr define
#include <sys/socket.h> //socket(), connect(), bind(), listen(), accept(), select(); 
#include <unistd.h>  //close(), fread()
#include <cstring>
#include <ext/stdio_filebuf.h>
import client;
export module server;
import <iostream>;
import <typeinfo>;
import <vector>;
//import client;
#define MAXLINE 1024
#define PORT 8080 
#if 0	
		<сервер>									
		  |
	инициализация соединения функции bind(), listen()
		  |
		цикл (бесконечный)
	     	  |
     ________\	 \|/ 
    |	     / установка сокетов для прослушивания. /______________________________________|
    |		поток вывода, свой и клиентские     \                                      |
    |		  |                                                                        |
    |		 \|/                                                                       |
    |	<select() возврыщает массив дескрипторов     режим ожидания>  		           |
    |	  |	при записи вних		   	   	|                                  |
    |	  |				    		|                                  |
    |	 \|/			                       \|/                                 |
    |	если select возвращает 	     			|				   |	
    |	сокет сервера:  				|                                  |
    |	accept() нового соединения			|                                  |
    |		|		       		       \|/                                 |
    |		|		если select() возвращает дескрипторы  read() из них        |
    |___________|			|			|                          |
					|			|                          |
				       \|/	      	       \|/                         |
				сообшение отсутствует: 	 сообшение присутствует:           |
				send Host Disconnect	 send message to                   |
				erase from socket	 other sockets                     |
				from sockets massive		|			   |
					|_______________________|__________________________|


(stdin (поток ввода) на дескрипторе 0) 



#endif

export class Server : public Client{
	public:
	Server(){};
	Server(int _sock, struct sockaddr_in _addres):Client(_sock, _addres){}
	int sd,new_socket, client_socket[30], max_clients=30, activity, i, max_sd, valread;
	std::vector<std::pair<int, char*>> nicknames;
};

//Синглетон Майерса
export class Singleton:public Server
{
public:
   static Singleton* Instance();
   //Client* instance = new Server(); 
   int data;
protected:
   Singleton(){};
   Singleton(int _sock, struct sockaddr_in _addres):Server(_sock, _addres){};
private:
   static Singleton* _instance;
};

Singleton* Singleton::_instance = 0;
Singleton* Singleton::Instance() {
  if(_instance == 0)_instance = new Singleton(socket(AF_INET, SOCK_STREAM, 0),(struct sockaddr_in)0);
  return _instance;
}




Singleton* s(new Singleton);
Singleton* singleton0(Singleton::Instance());
Singleton* singleton1(Singleton::Instance()->data = 20);

//export singleton0;
//export singleton1;



template<> Server *Client::init1(Server* peer)
        {
        //char * ser = "Server fd ";
	std::cout << "server start" << std::endl;
	peer->addres.sin_family = AF_INET;
        peer->addres.sin_port = htons(PORT);
        peer->addres.sin_addr.s_addr = htonl(INADDR_ANY);

        bind(peer->sock, (struct sockaddr*)&peer->addres, sizeof(peer->addres));
        //waiting for connection
        listen(peer->sock, 300);
        //std::cout <<"test" <<std::endl;
        peer->nicknames.push_back({0,"test"});
        return peer;

	}






template<> Server *Client::sel(Server *peer){
for (auto itr = peer->nicknames.begin(); itr != peer->nicknames.end(); ++itr)
FD_SET(itr->first, &peer->read_fd);
//                select(300, &peer->read_fd, NULL, NULL, NULL);

return this;
}

template<> Server *Client::sendmes(Server *peer){
//#if 0
	for (auto itr2 = peer->nicknames.begin(); itr2 != peer->nicknames.end(); ++itr2)
                { 
			peer->sd = itr2->first; 
			if (FD_ISSET(peer->sd , &peer->read_fd)) 
                        { 
				if ((peer->valread = read(peer->sd, peer->buffer, 1024))) 
				/*{ 
                                        printf("Host disconnected %s \n" ,itr2->second); 
                                        close(peer->sd); 
					peer->nicknames.erase(itr2); 
                                	break;				
				} 
                                else
					*/
				{ 
	  				peer->buffer[peer->valread] = '\0';
					for (auto itr1 = peer->nicknames.begin(); itr1 != peer->nicknames.end(); ++itr1)
					dprintf(itr1->first,"%s says: %s\n",itr2->second, peer->buffer);
					
                                 }  
                        } 
             
        	}
//#endif
return this;
}

template<> Server *Client::conn(Server *peer){
			//peer->new_socket = accept(peer->sock,NULL,NULL);
			//accepting connection
			peer->new_socket = accept(peer->sock,NULL,NULL);
			//char g[80]={"sos"};
			//g="sos";
			//read(peer->new_socket,g,1024);
			peer->nicknames.push_back({peer->new_socket,"test"});
			std::cout<< "New connection "<<peer->new_socket<<std::endl;
			//printf("New connection %s\n", peer->new_socket);
			dprintf(peer->new_socket,"welcome %d\n", peer->new_socket);  

return this;
}

