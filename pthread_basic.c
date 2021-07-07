#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int glob_var = 3; 
// 전역변수 3생성

// 스레드 함수 생성시, 리턴값과 인수는 void*타입
void* t_function(void *data){
    int val;
    int i=0;
    pthread_t t_id;
    // 스레드 아이디값 확인
    glob_var++;
    t_id = pthread_self();
    printf("pid= %d, t_id= %ld, glob_var= %d\n", getpid(), t_id, glob_var);
    val = *((int*)data);
    // void*이지만 원래 인자가 int형이라서 데이터 접근을 위해 (*int)로 지정해서 접근
    printf("value=%d\n", val);
    return (void*)(val*val);
}

int main(void){
    pthread_t p_thread[2];
    int a= 1;
    int b= 2;
    int err;    // 에러 감별
    int status; // 상태 확인

    printf("현재 PID = %d, glob_var = %d\n", getpid(), glob_var);
    // 스레드 2개 추가 생성

    // 1st :thread변수 주소값
    // 2nd :thread attribute(NULL) - 스레드 특성값 지정, 기본값은 NULL삽입
    // 3rd :스레드 생성시 실행할 스레드 함수 주소
    // 4th :스레드 생성시 전달할 인자값
    err = pthread_create(&p_thread[0], NULL, t_function, (void*)&a);
    // 에러 발생 경우
    if(err!=0){
        perror("!!WARNING!! :: pthread_create(0) error ");
        exit(1);
    }


    err = pthread_create(&p_thread[1], NULL, t_function, (void*)&b);
    // 에러 발생 경우
    if(err!=0){
        perror("!!WARNING!! :: pthread_create(1) error ");
        exit(2);
    }

    pthread_join(p_thread[0], (void**)&status);
    printf("thread_join(0) : %d\n", status);
    pthread_join(p_thread[1], (void**)&status);
    printf("thread_join(1) : %d\n", status);
}