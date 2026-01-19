#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define NAME_SIZE 32

char *out_file;

typedef struct {
    char name[NAME_SIZE];
    unsigned int delay;
    unsigned int maximum;
} thread_info;

/* ---------------- Thread function ---------------- */

void* thread_func(void *ptr)
{
    thread_info* info = (thread_info*)ptr;

    for (unsigned int i = 0; i < info->maximum; i++)
    {

        FILE* fp = fopen(out_file, "a");
        if (fp)
        {
            fprintf(fp, "thread: %s\n", info->name);
            fclose(fp);
        }
        else
        {
            fprintf(stderr, "Could not open file (thread %s)\n", info->name);
        }

        sleep(info->delay);
    }

    free(info);
    return NULL;
}

/* ---------------- Thread starter ---------------- */

bool start_thread(const char* name, unsigned int delay, unsigned int maximum)
{
    thread_info* info = malloc(sizeof(thread_info));
    if (!info)
        return false;

    pthread_t thrd;

    strncpy(info->name, name, NAME_SIZE - 1);
    info->name[NAME_SIZE - 1] = '\0';
    info->delay = delay;
    info->maximum = maximum;

    if (pthread_create(&thrd, NULL, thread_func, info) != 0)
    {
        free(info); //check if we have to free anyway
        return false;
    }

    pthread_detach(thrd);
    return true;
}

/* ---------------- User input loop ---------------- */

void process_userinput(void)
{
    char name[NAME_SIZE];
    unsigned int delay, maximum;
    bool running = true;

    while (running)
    {
        printf("Enter the name of the thread (or 'stop'): ");
        scanf("%31s", name);

        if (strcmp(name, "stop") == 0)
            running = false;
        else{
            printf("Enter the delay in seconds: ");
            scanf("%u", &delay);

            printf("Enter the maximum number of writes: ");
            scanf("%u", &maximum);

            start_thread(name, delay, maximum);

        }

        
    }
}

/* ---------------- main ---------------- */

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <output_file>\n", argv[0]);
        return 1;
    }

    out_file = argv[1];

    process_userinput();
    printf("Program ending...\n");

}
