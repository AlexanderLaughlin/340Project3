#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

volatile int strLen = 0;  //length of string to append
char final[0] = "";     //final string
volatile int counter;   //global counter
volatile int numThreads;
pthread_mutex_t lock;


void* threadWork(void *arg){

	printf("Argument is : %p", arg);
}
	

void main(int argc, char *argv[]){

	FILE *f;
	char str[25];
	int numThreads = atoi(argv[1]);	     //threads= number of threads
	printf("Number of threads to create = %d\n", numThreads);


	f = fopen("shakespeare.txt", "r");
	if (f == NULL){
		printf("Error opening file\n");
	}
	for (int i = 0; i<numThreads; i++){
		//read lines from shakespeare.txt and store in array
		//threads will remove elements from array to add to final string
	
	
		if (fgets (str, 25, f)!=NULL) {
			printf("String = %s\n", str);
		}
	}

		
	strLen = 10;  
	pthread_t thread_id[numThreads+1];      //extra space for null character

	assert(pthread_mutex_lock(&lock)==0); //LOCK

	for (int i = 0; i < numThreads; i++){

		if(pthread_create(&thread_id[i], NULL, threadWork, (void*)str)){
			printf("Thread Creation Failure\n");
		}
	}
	assert(pthread_mutex_unlock(&lock)==0); //UNLOCK
			
}


