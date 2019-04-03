//
//  main.c
//  pthread_test
//
//  Created by Connor Jones on 12/12/2018.
//  Copyright © 2018 Connor Jones. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct data {
    int col_ind;
    int row_ind;
    int no_thrds;
};

struct thread {
    int start;
    int end;
    long double time;
    //int A_thrd[2000][2000];
    //int B_thrd[2000][2000];
};
//  Allocate global memory for all threads to access
//  Used 100x100
int sz, N;
int out[2000][2000] = {};
int A[2000][2000] = {
    {1,6,11,4},
    {2,7,12,3},
    {3,8,13,1},
};
int B[2000][2000 ] = {
    {1,2,3,1},
    {4,5,6,5},
    {3,3,5,7},
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void dot_prod(int n, int m){
    int i, prod;
    //  Collect the index of the matrix currenrlty calculating.
    //  Initalise the dot product vector output to 0
    for(i = 0; i<= sz - 1; i++){
        //pthread_mutex_lock(&mutex);
        //  Calculate each product vector
        prod = (A[n][i] * B[i][m]);
        //  Add to the overall dot product element
        out[n][m] += prod;
        //pthread_mutex_unlock(&mutex);
        
    }
    //  What to do with this answer?
}
void gen_rand_matrix(int limit, int mag){
    int i = 0, j = 0;
    for(i = 0; i <= mag-1; i++){
        for(j = 0; j <= mag-1; j++){
            A[i][j] = rand() % limit;
            B[i][j] = rand() % limit;
        }
    }
}
void* Thread_func(void* thrd_ptr){
    clock_t st,fn;
    st = clock();
    struct thread* data = (struct thread*) thrd_ptr;
    int i,j;
    //printf("Start inside thread %d\n", data->start);
    //printf("End inside threas %d\n", data->end);
    for(i=0;i <= sz -1; i++){
        //  Compute the rows
        for(j = data->start; j <= data->end; j++){
            //  Compute columns
            //pthread_mutex_lock(&mutex);
            dot_prod(i, j);
            //pthread_mutex_unlock(&mutex);
        }
    }
    fn = clock();
    data->time = ((long double)(fn-st))/CLOCKS_PER_SEC;
    return 0;
}
int main(int argv, char ** argc) {
    int i=0,count = 0;
    long double time;
    /*
    int sz = (int) argc[1];
    int N = (int) argc[2];
    sz = 20000;
    N = 1;
     */
    printf("Matrix dimensions: ");
    scanf("%d", &sz);
    printf("Number of threads used: ");
    scanf("%d", &N);
    // Generate a random matrix of sz x sz
    gen_rand_matrix(7, 2000);
    /*
    // Print out the input matrix
    printf("Matrix A:\n");
    for(i=0,count = 0; i<4; i++){
        for(j=0; j <  4; j++){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("Matrix B:\n");
    for(i=0,count = 0; i<4; i++){
        for(j=0; j < 4; j++){
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
     */
    // Initalise Clock data type to measure execution time
    clock_t st, fn;
    // Start the clock
    st = clock();
    struct thread stk[N];
    pthread_t thrd_id[N];
    int col_per_thrd = sz/N;
    for(i=0; i <= N - 1; i++){
        if(i==0){
            // Initialise thread start point
            stk[i].start = 0;
            stk[i].end = col_per_thrd - 1;
        }
        //printf("Start = %d\n", stk[i].start);
        //printf("End = %d\n", stk[i].end);
        pthread_create(&thrd_id[i], NULL, Thread_func, &stk[i]);
        count++;
        stk[count].end = (stk[count-1].end + (sz/N));
        stk[count].start = stk[count-1].end + 1;
        
    }
    for(i=0; i <= N - 1; i++){
        pthread_join(thrd_id[i], NULL);
    }
    /*
    for(i=0,count = 0; i<=sz-1 ; i++){
        for(j=0; j <= sz - 1; j++){
            printf("%d ", out[i][j]);
        }
        printf("\n");
    }
    */
    // stop the clock
    fn = clock();
    time = ((long double) (fn- st))/CLOCKS_PER_SEC;
    printf("Execution time: %Lf secs\n", time);
    
    for(i = 0; i<=N-1;i++){
        printf("Thread %d took %Lf\n", i+1,stk[i].time);
    }
    
    return 0;
    
}
