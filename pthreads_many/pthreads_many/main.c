//
//  main.c
//  pthreads_many
//
//  Created by Connor Jones on 07/12/2018.
//  Copyright © 2018 Connor Jones. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "threads.h"

struct data {
    int col_ind;
    int row_ind;
    int no_thrds;
    
};

//  Allocate global memory for all threads to access
//  Used 100x100
int sz;
int out[20000][20000] = {};
int A[20000][20000] = {
    {1,6,11},
    {2,7,12},
    {3,8,13},
};
int B[100][100] = {
    {1,2,3},
    {4,5,6},
    {3,3,5},
};

void* dot_prod(void* arg){
    struct data *data_ptr = (struct data*) arg;
    int i, prod;
    //  Collect the index of the matrix currenrlty calculating.
    int n = data_ptr->col_ind;
    int m = data_ptr->row_ind;
    //  Initalise the dot product vector output to 0
    for(i = 0; i<= sz - 1; i++){
        //  Calculate each product vector
        prod = (A[n][i] * B[i][m]);
        //  Add 9it to the overall dot product element
        out[n][m] += prod;
        
    }
    //  What to do with this answer?
    return 0;
}
void gen_rand_matrix(int limit, int mag){
    int i = 0, j = 0;
    for(i = 0; i < mag; i++){
        for(j = 0; j <= mag; j++){
            A[i][j] = rand() % limit;
            B[i][j] = A[j][i] * (rand() % (limit/3));
        }
    }
    
}
void print_A(){
    int i, j;
    // Print out the input matrix
    printf("Matrix A:\n");
    for(i=0; i<=4; i++){
        for(j=0; j <=  4; j++){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}
void print_B(){
    int i, j;
    printf("Matrix B:\n");
    for(i=0; i<=4; i++){
        for(j=0; j <= 4; j++){
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
}
void print_result(){
    int i, j;
    for(i=0; i<=sz-1 ; i++){
        for(j=0; j <= sz - 1; j++){
            printf("%d ", out[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int i=0,j=0,count;
    double long time;
    clock_t st,fn;
    
    // Generate a random matrix of sz x sz
    gen_rand_matrix(15, 1000);
    printf("Matrix dimensions: ");
    scanf("%d", &sz);

    struct data element[sz*sz];
    pthread_t tdid [sz*sz];
    
    st = clock();
    for(i=0,count = 0; i<=sz-1 ; i++){
    	for(j=0; j <= sz - 1; j++){
    		element[i+j].row_ind =i;
    		element[i+j].col_ind =j;
    		pthread_create(&tdid[i+j], NULL, dot_prod, &element[i+j]);
    		count++;
		}
	}
	for(i=0; i <= (sz*sz) - 1; i++){
		pthread_join(tdid[i+j], NULL);
	}
    fn = clock();
    time = ((long double)(fn-st))/CLOCKS_PER_SEC;
    printf("Execution time: %Lf\n", time);

    return 0;
    
}
