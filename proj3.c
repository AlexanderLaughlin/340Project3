#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>



volatile int counter;   //global counter
volatile int numThreads;
pthread_mutex_t lock;


void* threadWork(void *arg){

	assert(pthread_mutex_lock(&lock)==0); //LOCK

	char * lineToAdd = (char *) arg;
	printf("Argument is : %p\n", lineToAdd);


	assert(pthread_mutex_unlock(&lock)==0); //UNLOCK
}
	

void main(int argc, char *argv[]){

	assert(pthread_mutex_init(&lock, NULL) == 0);  //Initialize lock
	FILE *f;
	int maxLen = 70;
	char str[maxLen]; 
	int numThreads = atoi(argv[1]);	     //threads= number of threads
	printf("Number of threads to create = %d\n", numThreads);
	

	//TODO change this to queue
	char threadLines[numThreads][maxLen+1];  //2D array to store strings
					   
	//OPEN FILE
	f = fopen("shakespeare.txt", "r");
	if (f == NULL){
		printf("Error opening file\n");
	}

	for (int i = 0; i<numThreads; i++){
	
		fgets (str, maxLen, f); 	//this is reading lines from the file
		strcpy(threadLines[i], str); 	//this is writing lines to threadLines array

		//TODO add code to push these onto queue instead of array

		//printf("String = %s\n", str); //print to check if working
		
	}

		
	
	pthread_t thread_id[numThreads+1];      //extra space for null character

	//assert(pthread_mutex_lock(&lock)==0); //LOCK


	for (int i = 0; i < numThreads; i++){
		assert(pthread_mutex_lock(&lock)==0);

		if(pthread_create(&thread_id[i], NULL, threadWork, (void *)threadLines[i])){ //create thread and pass it the line to be added
			printf("Thread Creation Failure\n");
			assert(pthread_mutex_unlock(&lock)==0); //UNLOCK
		}
		assert(pthread_mutex_unlock(&lock)==0);
	}		
}


