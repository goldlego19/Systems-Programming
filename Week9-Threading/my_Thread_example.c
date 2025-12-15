#include <stdio.h>
#include <pthread.h>



void* counting_task(){
    int num = 30;
    printf("Counting to %d: \n",num);

    int count = 0;
    for (int i = 1; i <= num; i++)
    {
        printf("%d\n",i);
        count++;
    }
    
    printf("Counted to %d: Count = %d",num,count);
   
}

void* say_hello(){
    printf("beep\n");
}

int main(void) {
	pthread_t 	countThread;
	pthread_t 	helloThread;

	int			result1;
	int			result2;


	/*if (sysconf(_SC_THREADS) == -1) {
		fprintf(stderr, "Sorry, this program requires threads, which aren't supported here.\n");
		return -1;
	}*/

	result1 = pthread_create(&countThread, NULL, counting_task, NULL);
	result2 = pthread_create(&helloThread, NULL, say_hello, NULL);


	if (result1 != 0) {
		fprintf(stderr, "For some reason I couldn't create a thread! (errno = %d)\n", result1);
		return -2;
	}
    if (result2 != 0) {
		fprintf(stderr, "For some reason I couldn't create a thread! (errno = %d)\n", result2);
		return -2;
	}

	pthread_join(countThread, NULL);
	pthread_join(helloThread, NULL);

	return 0;
}