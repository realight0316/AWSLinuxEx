#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

long int answer = 0;
void* addcal(void* dual_num);

struct dual_num {
    int ststst;
    int endend;
};

int main(){
    pthread_t threadcal[2];
    struct dual_num proc1, proc2;
    proc1.ststst = 1;
    proc1.endend = 1000000;
    proc2.ststst = 1000001;
    proc2.endend = 2000000;

    long int status ; // 상태확인
    int check_v;      // 에러확인

    check_v = pthread_create(&threadcal[0], NULL, addcal, (void*)&proc1);
    if(check_v!=0){
        perror("!!WARNING!! :: pthread_create(0) error \n // 본 컴퓨터는 3초뒤에 자동폭발 됩니다.(피해반경 약3m)");
        exit(1);
    }
    check_v = pthread_create(&threadcal[1], NULL, addcal, (void*)&proc2);
    if(check_v!=0){
        perror("!!WARNING!! :: pthread_create(1) error \n // 본 컴퓨터는 3초뒤에 자동폭발 됩니다.(피해반경 약3m)");
        exit(2);
    }

    pthread_join(threadcal[0], (void**)&status);
    printf("thread_join(0) : %ld\n", status);
    pthread_join(threadcal[1], (void**)&status);
    printf("thread_join(1) : %ld\n", status);

    printf("결과값 : %ld\n", answer);
    return (void*)answer;
}

void* addcal(void* nums){
    long int temp = 0;
    struct dual_num *dual_num;
    dual_num = ((struct dual_num*)nums);
    int i = dual_num->ststst;
    // printf("ststst: %d\n", i);
    // printf("endend: %d\n", dual_num->endend);

    for (; i<=dual_num->endend;i++){
        temp += i;
    }
    answer += temp;
}