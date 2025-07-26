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

int Resource[NUM];
int Claim[NUM][NUM];
int Allocation[NUM][NUM];
int C_sub_A[NUM][NUM];

pthread_mutex_t m;
pthread_cond_t c;

int isSafe() {
    int Work[NUM];
    int Finish[NUM] = { 0 };
    for (int i = 0; i < NUM; i++) {
        Work[i] = Resource[i];
    }

    int cnt = 0;
    while (cnt < NUM) {
        int i;
        for (i = 0; i < NUM; i++) {
            if (!Finish[i]) {
                int j;
                for (j = 0; j < NUM; j++) {
                    if (C_sub_A[i][j] > Work[j]) break;
                }
                if (j == NUM) {
                    for (int k = 0; k < NUM; k++) Work[k] += Allocation[i][k];
                    Finish[i] = 1;
                    cnt++;
                    break;
                }
            }
        }
        if (i == NUM) break;
    }
    return (cnt == NUM);
}

int Pick(int PhilNum) {
    int Req[NUM] = { 0 };
    Req[PhilNum] = 1;
    Req[(PhilNum + 1) % NUM] = 1;
    
    for (int i = 0; i < NUM; i++) {
        if (Req[i] > C_sub_A[PhilNum][i] || Req[i] > Resource[i])
            return 0;
    }

    for (int i = 0; i < NUM; i++) {
        Resource[i] -= Req[i];
        Allocation[PhilNum][i] += Req[i];
        C_sub_A[PhilNum][i] -= Req[i];
    }

    if (isSafe()) {
        return 1;
    }
    else {
        for (int i = 0; i < NUM; i++) {
            Resource[i] += Req[i];
            Allocation[PhilNum][i] -= Req[i];
            C_sub_A[PhilNum][i] += Req[i];
        }
        return 0;
    }
}

void Put(int PhilNum) {
    for (int i = 0; i < NUM; i++) {
        if (Allocation[PhilNum][i] > 0) {
            Resource[i] += Allocation[PhilNum][i];
            C_sub_A[PhilNum][i] += Allocation[PhilNum][i];
            Allocation[PhilNum][i] = 0;
            printf("philosopher %d puts down fork %d.\n", PhilNum, i);
        }
    }
    pthread_cond_broadcast(&c);
}

void Think(int PhilNum) {
    printf("philosopher %d is Thinking\n", PhilNum);
    return;
}

void Eat(int PhilNum) {
    printf("philosopher %d is Eating\n", PhilNum);
    return;
}

void* Phil(void* num) {
    int PhilNum = (int)(long)num;
    while (1) {
        Think(PhilNum);

        pthread_mutex_lock(&m);
        while (!Pick(PhilNum)) {
            pthread_cond_wait(&c, &m);
        }
        printf("philosopher %d picks up forks %d and %d.\n", PhilNum, PhilNum, (PhilNum + 1) % NUM);
        pthread_mutex_unlock(&m);

        Eat(PhilNum);

        pthread_mutex_lock(&m);
        Put(PhilNum);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
    pthread_t Thrds[NUM];

    for (int i = 0; i < NUM; i++) {
        Resource[i] = 1;
        for (int j = 0; j < NUM; j++) {
            Allocation[i][j] = 0;
            Claim[i][j] = 0;
        }
    }

    for (int i = 0; i < NUM; i++) {
        Claim[i][i] = 1;
        Claim[i][(i + 1) % NUM] = 1;
        for (int j = 0; j < NUM; j++) {
            C_sub_A[i][j] = Claim[i][j] - Allocation[i][j];
        }
    }

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);

    for (long i = 0; i < NUM; i++) {
        pthread_create(&Thrds[i], NULL, Phil, (void*)i);
    }
    for (int i = 0; i < NUM; i++) {
        pthread_join(Thrds[i], NULL);
    }

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);

    return 0;
}
