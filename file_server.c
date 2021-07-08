#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

// 인자로 Port번호 받음
int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    // 이 예제는 파일을 전송하고 다루기위해 파일 포인터를 선언
    FILE* fp;
    char buf[BUF_SIZE]; //1024
	int read_cnt;

    struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

    // 인자값으로 Port를 넣어주지 않았을때 에러
    if(argc!=2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

    // STEP1. socket() : 서버의 소켓을 생성
    serv_sock=socket(PF_INET, SOCK_STREAM, 0); // IPv4, TCP


    // STEP2. bind()   : 서버의 프로토콜, 주소, 포트번호 설정
    memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

    bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

    // STEP3. listen() : 대기열 버퍼 크기 설정
    listen(serv_sock, 5);

    // STEP4. accept() : 클라이언트 접속 요청 허용
    clnt_adr_sz=sizeof(clnt_adr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

    // STEP5. read()/write() : 데이터 송수신
    fp=fopen("cat.jpg", "rb");
    while(1)
	{
		read_cnt=fread((void*)buf, 1, BUF_SIZE, fp); 
        // 버퍼사이즈만큼 데이터가 많이 차지 않은 경유, 1024만큼 읽어낸다
		if(read_cnt<BUF_SIZE){                       
            // 1024보다 read_cnt가 더 작으면
			write(clnt_sock, buf, read_cnt);
			break;
            // 마지막으로 전송하고 반복문 종료
		}
        // BUF_SIZE(1024)만큼 데이터를 전송
		write(clnt_sock, buf, BUF_SIZE);
	}
    shutdown(clnt_sock, SHUT_WR);
    // clnt_sock의 쓰기(WR)부분을 닫음
    read(clnt_sock, buf, BUF_SIZE);
	printf("Message from client: %s \n", buf);
	
	fclose(fp);
	close(clnt_sock); close(serv_sock);
    // 위에서 쓰기부분만 닫았으므로 나머지 부분도 종료
	return 0;


    // STEP6. close() : 클라이언트 접속종료



}