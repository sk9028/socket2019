#include<stdio.h>

int main(){
	int a = 10;
	int b = 100;

	a=a+10;
	sleep(10);
	int pid = fork(); //fork함수는 현재 구동 중인 프로세스의 복제본을 생성
						//현재 프로세스 = 부모 프로세스
						//fork에 의해 생성된 프로세스 = 자식프로세스
						//리턴 값(pid)=0이면 자식 프로게스
						//리턴 값 = 자식 프로세스의  pid값  if 부모 프로세스
						//만약 fork함수 실패 시 -1값을 리턴

	if(pid>0){ //부모 프로세스
		printf("부모 프로세스\n");
		a=a+10;
		printf("[parent]a=%d, b=%d\n",a,b);
		sleep(20); //20초동안 프로그램을 종료시키지말고 기다리고 있어라
				
	}else if(pid==0){//자식 프로세스
		printf("자식 프로세스\n");
		b=b*10;
		printf("[child]a=%d, b=%d\n",a,b);
		sleep(20);

	}else{ //부모도 자식도 아닌경우 fork()함수 실패
		printf("fork함수가 실패했습니다.");

	}
	return 0;
}
