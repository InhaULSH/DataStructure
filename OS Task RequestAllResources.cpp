#define PTW32_NO_TIMESPEC
#define _TIMESPEC_DEFINED

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <windows.h>
#include <thread>
using namespace std;

#define NUM 5
sem_t Forks[NUM];
sem_t Once;

void Pick(int PhilNum) {
    sem_wait(&Forks[PhilNum % NUM]);
}

void Put(int PhilNum) {
    sem_post(&Forks[PhilNum % NUM]);
}

void Think(int PhilNum) {
    printf("philosopher %d is Think\n", PhilNum);
    return;
}

void Eat(int PhilNum) {
    printf("philosopher %d is Eat\n", PhilNum);
    return;
}

void* Phil(void* arg) {
    int PhilNum;
    PhilNum = (unsigned long int) arg;
    while (1) {
        sem_wait(&Once);
        Pick(PhilNum);
        printf("philosopher %d picks up the fork %d.\n", PhilNum, PhilNum);
        Pick(PhilNum + 1);
        printf("philosopher %d picks up the fork %d.\n", PhilNum, (PhilNum + 1) % NUM);
        sem_post(&Once);
        Eat(PhilNum);
        Put(PhilNum + 1);
        printf("philosopher %d puts down the fork %d.\n", PhilNum, (PhilNum + 1) % NUM);
        Put(PhilNum);
        printf("philosopher %d puts down the fork %d.\n", PhilNum, PhilNum);
        Think(PhilNum);
    }
    return NULL;
}

int main() {
    pthread_t Thrds[NUM];
    sem_init(&Once, 0, 1);
    for (int i = 0; i < NUM; i++) {
        sem_init(&Forks[i], 0, 1);
    }    
    for (unsigned long int i = 0; i < NUM; i++) {
        pthread_create(&Thrds[i], NULL, Phil, (void*)i);
    }
    for (int i = 0; i < NUM; i++) {
        pthread_join(Thrds[i], NULL);
    }
    return 0;
}