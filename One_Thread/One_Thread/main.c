//
//  main.c
//  One_Thread
//
//  Created by Connor Jones on 13/12/2018.
//  Copyright © 2018 Connor Jones. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int out[2000][2000];
int A[2000][2000];
int B[2000][2000];

int sz, N;

void gen_rand_matrix(int limit, int mag){
    int i = 0, j = 0;
    for(i = 0; i <= mag-1; i++){
        for(j = 0; j <= mag-1; j++){
            A[i][j] = rand() % limit;
            B[i][j] = rand() % limit;
        }
    }
}

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
int main(int argc, const char * argv[]) {
    clock_t st,fn;
    long double time;
    printf("Matrix dimensions: ");
    scanf("%d", &sz);
    gen_rand_matrix(10, sz);
    st = clock();
    for(int i=0;i<=sz-1;i++){
        for(int j=0; j<=sz-1;j++){
            dot_prod(i,j);
        }
    }
    fn = clock();
    time = ((long double) (fn-st))/CLOCKS_PER_SEC;
    printf("Overall Execution Time: %Lf",time);
}
