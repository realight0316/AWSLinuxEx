#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sock;
	FILE *fp;
	
	char buf[BUF_SIZE];
	int read_cnt;
    struct  sockaddr_in serv_adr;

    if(argc!=3){
        printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
    }

    // STEP1. socket() : 소켓 생성
    sock = socket(PF_INET, SOCK_STREAM, 0);

    // STEP2. connect() : 프로토콜, 서버주소, 포트번호 설정
    memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

    // 서버 접속 요청
    connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
    
    fp=fopen("receive.jpg", "wb");

    // STEP3. read(), write()
    while((read_cnt=read(sock, buf, BUF_SIZE ))!=0)
		fwrite((void*)buf, 1, read_cnt, fp);

    // STEP4. shutdown(), close()
    puts("Received file data");
    // 상태확인을 위해 터미널에 출력
	write(sock, "I'll find u and I'll kill u", 27);
    // 파일데이터 수신이 끝나면 서버로 전달되는 메세지
	fclose(fp);
	close(sock);
	return 0;
}