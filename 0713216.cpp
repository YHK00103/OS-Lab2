# include <iostream>
# include <thread>
# include <unistd.h>
#include <pthread.h>
using namespace std;

# define MAX 500
# define num1 250
#define num2 125

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication

void* Addition(void* arg) {
    // Addition -> matC

    int start = (long)(arg)*num1;
    int end = ((long)(arg)+1) * num1;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < MAX; j++) {
            matC[i][j] = matA[i][j] + matB[i][j];
        }
    }
    pthread_exit(0);
}

void* Multiplication(void* arg) {
    // Multiplication -> matD

    int start = (long)arg * num2;
    int end = ((long)arg + 1) * num2;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < MAX; j++) {
            matD[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    pthread_exit(0);
}

int main()
{
    //get input
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }

    pthread_t t1, t2, t3, t4, t5, t6;

    pthread_create(&t1, NULL, Addition, (void*)0);
    pthread_create(&t2, NULL, Addition, (void*)1);

    pthread_create(&t3, NULL, Multiplication, (void*)0);
    pthread_create(&t4, NULL, Multiplication, (void*)1);
    pthread_create(&t5, NULL, Multiplication, (void*)2);
    pthread_create(&t6, NULL, Multiplication, (void*)3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    
    // calculate SUM of matC
    long long sum_C = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_C += matC[i][j];
    }
    cout << sum_C << endl;

    // calculate SUM of matD
    long long sum_D = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            sum_D += matD[i][j];
        }
    }
    cout << sum_D << endl;

    return 0;
}