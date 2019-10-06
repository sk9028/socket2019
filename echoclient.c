#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 10000
#define IPADDR "127.0.0.1"
#define BUFSIZE 100

int main(){
	int c_socket; 
	struct sockaddr_in c_addr;
	int n;
	char rcvBuffer[BUFSIZE];//서버에서 보내준 메세지를 저장하는 변수
	char sendbuffer[BUFSIZE]="안녕하세요";
	char *str;
	char strr[BUFSIZE]="the little prince";
	char *ptr;
	char *ptrr;
	char *ptr1;
	char *ptr2;
	char *ptr3;
	char *ptr4;
	//1. 클라이언트 소켓 생성
	c_socket = socket(PF_INET, SOCK_STREAM, 0); //서버와 동일한 설정으로 생성
	//2.소켓 정보 초기화
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR); //접속할 IP 설정 (127.0.0.1)
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	//3. 서버에 접속
	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) == -1){
		//서버 접속에 실패하면 
		printf("Cannot Connect\n"); //Cannot connect 메세지 출력
		close(c_socket); //자원 회수
		return -1;  //프로세스 종료
	}
	//4. 서버에 메시지 보낼때 키보드로부터 메세지 입력 받기
		fgets(sendbuffer, sizeof(sendbuffer),stdin);
		//5. 서버에 메시지 주기
		write(c_socket,sendbuffer,strlen(sendbuffer));
		//5. 서버에서 보낸 메시지 읽기 
		n = read(c_socket, rcvBuffer, sizeof(rcvBuffer));
		strcpy(str,rcvBuffer);
		ptr=str+7;   //strcmp delete
//		ptrr=str+13;
		//ptrr=strtok(ptr,"  ");
		ptr1=strtok(ptr," ");  			//strcmp [hello] hello
		ptr2=strtok(ptr," ");
		           //strcmp hello [hello]
		
		
		
		//서버에서 보내준 메세지를 rcvBuffer에 저장하고, 메세지의 길이를 리턴
		//만약 read에 실패하면, -1을 리턴
		if (n < 0){ //read() 함수 실패 
			printf("Read Failed\n");
			return -1;
		}
		rcvBuffer[n] = '\0'; //문자열 뒷부분 깨짐 방지
		//printf("길이 : %s \n",ptr);   //str+8=ello hello  ,, str+13=hello
		printf("first value : %s \n",ptr1);   //str+8=ello hello  ,, str+13=hello
		printf("second value : %s \n",ptr2);   //str+8=ello hello  ,, str+13=hello
		if(ptr1==ptr2){
			printf("two value == %d\n",strcmp(ptr1,ptr2));
		}
		else{
			printf("two value == 1 n");
		}
		
		close(c_socket);

	return 0;	
}
