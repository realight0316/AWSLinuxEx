#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
//네트워크와 소켓통신을 위한 헤더파일

// 에러 발생시 메세지 출력하고 종료 처리
void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

// 서버 클라이언트 1대1 접속
int main(int argc, char *argv[]){
    int serv_sock;
    int clnt_sock;
    //서버, 클라이언트 소켓 변수 선언

    // 소켓의 주소값 저장하는 구조체, TCP_IP교재 p68 참조
    struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

    // 메세지: 서버 -> 클라이언트
    char message[]="Hello World!";
    if(argc!=2){
        // 실행시 ""./hello_server [port]" 포트번호 기입
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

    // STEP1. socket() : 소켓 생성
    // 0: stdin, 1: stdout, 2: stderr, 3: serv_sock
    serv_sock=socket(PF_INET, SOCK_STREAM, 0); // 프로토콜 IPv4체계, TCP사용
	if(serv_sock == -1)
		error_handling("socket() error");

    // STEP2. bind() : 서버의 IP주소, 포트번호, 주소체계 설정
    // bind()함수를 호출하기 전에 구조체에 세팅
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET; // 주소체계 IPv4로 설정
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); // IP주소 4byte(long), INADDR_ANY = 자신의 주소
	serv_addr.sin_port=htons(atoi(argv[1])); // Port 번호 2byte(short)
    // bind()함수를 호출
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
		error_handling("bind() error");

    // STEP3. listen() : 접속 대기열 버퍼의 크기를 설정
    if(listen(serv_sock, 5)==-1)    // 대기열 버퍼 크기 = 5
		error_handling("listen() error");

    // STEP4. accept() : 클라이언트의 접속 요청을 수신
    // 클라이언트 소켓 생성
    clnt_addr_size=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");

    // STEP5. 데이터 read / write
    write(clnt_sock, message, sizeof(message));
	close(clnt_sock);
	close(serv_sock);

	return 0;

}