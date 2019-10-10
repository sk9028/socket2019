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
	char *ptr;
	char *ptrr;
	char *ptr1;
	char *ptr2;
	char *ptr3;


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
		ptr=str;   						//서버로 부터 메시지를 주고 받아와서 ptr에 저장
		ptr1=strtok(ptr," ");  			//[strcmp] hello hello 
		ptr=str+7;							//strcmp 자르기
		ptr2=strtok(ptr," ");			//strcmp [hello] hello
		ptr3=strtok(NULL," ");			//strcmp hello [hello]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//./client 후 strcmp hello hello를 입력할 때 마지막에 공백을 해주셔야 정확한 값이 출력됩니다!
		//./client -> "strcmp[공백]hello[공백]hello[공백]"		
		// 이 점 참고해서 실행 해주시면 감사하겠습니다.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//서버에서 보내준 메세지를 rcvBuffer에 저장하고, 메세지의 길이를 리턴
		//만약 read에 실패하면, -1을 리턴
		if (n < 0){ //read() 함수 실패 
			printf("Read Failed\n");
			return -1;
		}
		rcvBuffer[n] = '\0'; //문자열 뒷부분 깨짐 방지
		
		
		printf("first 길이 : %d \n",strlen(ptr1));  //strcmp 자른 후 길이 출력
		printf("second 길이 : %d \n",strlen(ptr2)); //첫번째 문자열 길이 출력
		printf("third 길이 : %d \n",strlen(ptr3));  //두번째 물자열 길이 출력

		
		printf("first 문자열 출력 : %s \n",ptr2);   //첫번째 문자열 출력
		printf("second 문자열 출력 : %s \n",ptr3);   //두번째 문자열 출력
		if(strcmp(ptr2,ptr3)){
		
			printf("두 문자열은 같지 않습니다. == 1 \n");  
		}
		else{
			printf("두 문자열은 같습니다. == 0 \n");
		}
		
		close(c_socket);

	return 0;	
}
