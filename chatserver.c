
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdbool.h>
void *do_chat(void *); //채팅 메세지를 보내는 함수
int pushClient(int); //새로운 클라이언트가 접속했을 때 클라이언트 정보 추가
int popClient(int); //클라이언트가 종료했을 때 클라이언트 정보 삭제
bool isempty();
bool isfull();
pthread_t thread;
pthread_mutex_t mutex;
//typedef enum {false, true} bool;
#define MAX_CLIENT 10
#define CHATDATA 1024
#define INVALID_SOCK -1
#define PORT 9000
int    list_c[MAX_CLIENT];  //클라이언트를 담는 배열
char    escape[ ] = "exit";   //클라이언트가 빠져나갈떄 보내는 메시지
char    greeting[ ] = "Welcome to chatting room\n"; // 클라이언트가 채팅서버 접속시 보내는 메시지
char    CODE200[ ] = "Sorry No More Connection\n";  // 서버 접속이 안될떄 보내는 메시지
int top = -1;  //스택의 가장 최상위
char user[10];

int main(int argc, char *argv[ ])
{
    int c_socket, s_socket;
    struct sockaddr_in s_addr, c_addr;
    int    len;
    int    i, j, n;
    int    res;
	char buf[100];
    if(pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Can not create mutex\n");
        return -1;
    }
    s_socket = socket(PF_INET, SOCK_STREAM, 0);
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    if(bind(s_socket, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {
        printf("Can not Bind\n");
        return -1;
    }
    if(listen(s_socket, MAX_CLIENT) == -1) {
        printf("listen Fail\n");
        return -1;
    }
    for(i = 0; i < MAX_CLIENT; i++)
        list_c[i] = INVALID_SOCK;
    while(1) {
        len = sizeof(c_addr);
        c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);
        res = pushClient(c_socket);
        if(res < 0) { //MAX_CLIENT만큼 이미 클라이언트가 접속해 있다면,
            write(c_socket, CODE200, strlen(CODE200));
            close(c_socket);
        } else {
            write(c_socket, greeting, strlen(greeting)); 
            pthread_create(&thread, NULL, do_chat, (void *)&c_socket);
            //pthread_create with do_chat function.
        }
    }
}
void *do_chat(void *arg)
{
    int c_socket = *((int *)arg);
    char chatData[CHATDATA];
    int i, n;
	
    while(1) {
        memset(chatData, 0, sizeof(chatData));
        if((n = read(c_socket, chatData, sizeof(chatData))) > 0) {

            for(i=0;i<list_c[top];i++){           
				
				
          		write(list_c[i], chatData,strlen(chatData));
			if(strncasecmp(chatData,"/w ",3)){
				char *id;
				char *token;
				char *b;
				b=strtok(chatData," "); // userid [a] , [b] , [c]...
				user[i]=b;
				token=strtok(chatData," ");   //    [/w]
				id = strtok(NULL,"\0");  //    /w [id]
				if(id==user[i]){
					write(list_c[i], chatData,strlen(chatData));
				}
			}
		     printf("%s",chatData);			
            		}
            if(strstr(chatData, escape) != NULL) {
                popClient(c_socket);
                break;
            }
        }
    }
}
int pushClient(int c_socket) {
	if(top>=MAX_CLIENT-1){
		return -1;
	}
	list_c[++top]=c_socket;
	return c_socket;


    //ADD c_socket to list_c array.
    //
    ///////////////////////////////
    //return -1, if list_c is full.
    //return the index of list_c which c_socket is added.
}
int popClient(int c_socket)
{
    close(c_socket);
	if(top<0){
		return -1;
	}
	return list_c[top--];
    //REMOVE c_socket from list_c array.
    //
    ///////////////////////////////////
}


