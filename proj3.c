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

	assert(pthread_mutex_lock(&lock)==0); //LOCK

	char * lineToAdd = (char *) arg;
	printf("Argument is : %p\n", arg);
	strncat(final, lineToAdd, 1);

	assert(pthread_mutex_unlock(&lock)==0); //UNLOCK
}
	

void main(int argc, char *argv[]){

	FILE *f;
	char str[70];
	int numThreads = atoi(argv[1]);	     //threads= number of threads
	printf("Number of threads to create = %d\n", numThreads);

	char threadLines[numThreads][71];  //2D array to store strings
					   //hardcoded to strLength+1 = 71

	f = fopen("shakespeare.txt", "r");
	if (f == NULL){
		printf("Error opening file\n");
	}
	for (int i = 0; i<numThreads; i++){
		//read lines from shakespeare.txt and store in array
		//threads will remove elements from array to add to final string
	
	
		fgets (str, 70, f); //this is reading lines from the file
		strcpy(threadLines[i], str);
		//printf("String = %s\n", str); //print to check if working
		
	}

		
	
	pthread_t thread_id[numThreads+1];      //extra space for null character

	assert(pthread_mutex_lock(&lock)==0); //LOCK

	for(int i = 0; i < numThreads; i++){     //Trying to print threadLines
		printf("I am thread %d\n", i);
		printf("I added the following line: %s\n", threadLines[i]);
	}

	for (int i = 0; i < numThreads; i++){

		if(pthread_create(&thread_id[i], NULL, threadWork, (void*)threadLines[i])){ //create thread and pass it the line to be added
			printf("Thread Creation Failure\n");
		}
	}
	assert(pthread_mutex_unlock(&lock)==0); //UNLOCK
			
}


