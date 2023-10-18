/**
 *\file client.h
 *\author Денис Вергун
 *\brief  Файл содержит описание конкретного клиента
 *\version
 *\date 20-07-2023
 *
 *
 */

#ifndef cli
#define cli

#define MAXLINE 1024
#define PORT 8080 





class Client{
        public:
	Client();
	Client(const char* addr);
	void createSocket(); 
	void connectInit(const char* addr);
        void connectInit();
	void selinit(); 
	void sel();
	void conn();
	void sendmes();
	int sock;///<Переменная для хранения сокета
        struct sockaddr_in addres;///<Структура для хранения адреса и типа узла
        char buffer[MAXLINE]={0};///<Хранит сообщение
        fd_set read_fd={0};///<Массив дескрапторов для храненния сокета
};

#endif
