#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
//네트워크와 소켓통신을 위한 헤더파일

void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

// "./hello_client.c [서버IP주소값], [PORT]"
int main(int argc, char *argv[]){
    int sock;
    // 접속할 서버의 프로토콜, IP주소, 포트번호
    struct sockaddr_in serv_addr;
    // 메세지 받아 저장할 문자열 버퍼
    char message[30];
    // 수신 문자열
    int str_len;

    if(argc!=3){ // 인자값이 3개가 아닌 경우
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

    // STEP1. socker() : 소켓 생성
    sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

    // STEP2. connect() : 프로토콜, 서버 주소값, 포트를 설정해서
    // 연결 시도
    memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
		error_handling("connect() error!");
    // STEP3. read / write
    str_len=read(sock, message, sizeof(message)-1);
	if(str_len==-1)
		error_handling("read() error!");

    printf("Message from server: %s \n", message);  
	close(sock);
	return 0;
	
}