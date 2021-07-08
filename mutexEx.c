// mutex -> 멀티스레드 환경
// 뮤텍스를 사용하여 공유변수(메모리) 동시접근을 방지한다.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

// mutex 사용할 공유 변수
static int count = 10;
// mutex 초기화
static pthread_mutex_t countlock = PTHREAD_MUTEX_INITIALIZER;

// count값 증감시킬 스레드 함수
void* increment(void* data){
    int err;
    while(1){
        err = pthread_mutex_lock(&countlock);
        if(err)
            printf("ERROR !! increment lock\n");
        count++;
        // mutex lock과 unlock 사이를 크리티컬존이라고 하며 보호되는 구역, 최대한 간결한 코드로 구성할 것.
        err = pthread_mutex_unlock(&countlock);
        if(err)
            printf("ERROR !! increment unlock\n");

        // mutex동작을 원하는 다른 스레드에게 우선 순위 양보
        err = sched_yield();
        //usleep(100);
    }   
}
void* decrement(void* data){
    int err;
    while(1){
        err = pthread_mutex_lock(&countlock);
        if(err)
            printf("ERROR !! decrement lock\n");
        count--;
        // mutex lock과 unlock 사이를 크리티컬존이라고 하며 보호되는 구역, 최대한 간결한 코드로 구성할 것.
        err = pthread_mutex_unlock(&countlock);
        if(err)
            printf("ERROR !! decrement unlock\n");

        // mutex동작을 원하는 다른 스레드에게 우선 순위 양보
        err = sched_yield();
        //usleep(100);
    }  
}
void* reader(void* data){
    int err;
    int value;
    while(1){
        err = pthread_mutex_lock(&countlock);
        if(err)
            printf("ERROR !! reader lock\n");
        value = count;
        // mutex lock과 unlock 사이를 크리티컬존이라고 하며 보호되는 구역, 최대한 간결한 코드로 구성할 것.
        err = pthread_mutex_unlock(&countlock);
        if(err)
            printf("ERROR !! reader unlock\n");

        // mutex동작을 원하는 다른 스레드에게 우선 순위 양보
        err = sched_yield();
        sleep(1); // 1초 슬립
        printf("count = %d\n",value);
    }   

}

int main(){
    // thread id값 저장할 변수 생성
    pthread_t p_thread[3];
    int err;

    pthread_mutex_init(&countlock, NULL);

    err = pthread_create(&p_thread[0], NULL, increment, NULL);
    if(err<0){
        perror("increment thread error : ");
        exit(1);
    }
    err = pthread_create(&p_thread[0], NULL, decrement, NULL);
    if(err<0){
        perror("decrement thread error : ");
        exit(1);
    }
    err = pthread_create(&p_thread[0], NULL, reader, NULL);
    if(err<0){
        perror("reader thread error : ");
        exit(1);
    }

    pthread_detach(p_thread[0]);
    pthread_detach(p_thread[1]);
    pthread_detach(p_thread[2]);

    while (1);
    return 0;
}