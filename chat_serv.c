#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

// 서버에서 사용할 버퍼의 크기
#define BUF_SIZE 100
// 서버에 최대로 접속 가능한 클라이언트의 수
#define MAX_CLNT 256

// 클라이언트 접속시 해당 데이터 송수신 담당 스레드함수
void * handle_clnt(void * arg);
// 메세지 전송
void send_msg(char * msg, int len);
// 에러 처리
void error_handling(char * msg);

// 스레드간 공유메모리 변수 선언
// (전역변수이므로 모든 스레드에서 접근가능)
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
// mutex 변수 : critical section 관리 (lock / unlock)
pthread_mutex_t mutx;

// ./chat_serv 5000 (실행 시)
// argv[0] = "./chat_serve"
// argv[1] = "5000"
int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int clnt_adr_sz;

    // 스레드 아이디값 저장
	pthread_t t_id;
    // 인자값이 두개가 아닌 경우
    if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
    // mutex 변수 초기화
    pthread_mutex_init(&mutx, NULL);

    // STEP1. socket()
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);

    // STEP2. bind() - 프로토콜(IPv4, IPv6), IP주소, 포트번호
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET; 
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");

	// STEP3. listen() -서버소켓의 대기열 버퍼 크기 설정
    if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

    
    while(1)
	{
        // STEP4. accept()
		clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);
		
        // clnt_socks값을 증가
		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt++]=clnt_sock;
		pthread_mutex_unlock(&mutx);

        // STEP5. read() / write() - handle_clnt에서 read, write동작
        // 방금 접속한 클라이언트의 데이터처리를 위한 스레드 생성
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		// 스레드 생성후 메인 스레드가 관리하지않고 해당스레드가 끝나면 알아서 종료되도록 방치
        pthread_detach(t_id);
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));

	}
    // STEP6-2. server close()
	close(serv_sock);
	return 0;
    
    
}

void * handle_clnt(void * arg){
    int clnt_sock=*((int*)arg);
    int str_len=0, i;
    // 메세지를 위한 문자열 버퍼
	char msg[BUF_SIZE];

    while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
        // 모든 클라이언트에게 메세지 전송
		send_msg(msg, str_len);

    pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)   // remove disconnected client
	{
		if(clnt_sock==clnt_socks[i])
		{
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);
    // 리턴 void* - 스레드함수는 리눅스내 지정된 형식이 있어서 필요함
	return NULL;
}

void send_msg(char * msg, int len)   // send to all
{
	int i;
	pthread_mutex_lock(&mutx);
    // clnt_socks 전인원에게 메세지 전송
	for(i=0; i<clnt_cnt; i++)
		write(clnt_socks[i], msg, len);
	pthread_mutex_unlock(&mutx);
}

void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}