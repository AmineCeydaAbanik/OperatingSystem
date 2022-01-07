#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef struct queue {
    int arr[50];
    int rear;
} q_t;

void push(int n, q_t *q) {
    if (q->rear == 50) {
        printf("Queue Overflow!");
        return;
    }
    q->arr[q->rear++] = n;
}

void clear(q_t *q) {
    q->rear = 0;
}

typedef struct num {
    int n;
} num_t;

int running_threads_table[10] = {0};
int table_receipt[10] = {0};
int eaten[80] = {0};
int rice[10] = {0};
int table_counter[10];
int last_phl = 0;
q_t queues[10];

void print_receipt(int grp_index) {
    printf("****** Table %d Receipt ******\n", table_counter[grp_index] + 1);
    for(int i = 0; i < 8; i++)
        printf("<philosopher: %d  eat:%d>\n", table_counter[grp_index] * 8 + i + 1, eaten[8 * grp_index + i] * 100);
    printf("Eaten Rice: %d kg\n", rice[grp_index]/10);
    printf("Eaten Rice: %d g\n", rice[grp_index]*100);
    printf("reOrder Count: %d\n", table_receipt[grp_index] - 1);
    printf("Total cost: %lf\n", 99.9 + (table_receipt[grp_index] - 1) * 19.9 + table_receipt[grp_index] * 40);
    printf("****** End Receipt ******\n");
}

void *eat(void *vargp) {
    int phl = ((num_t *)vargp)->n;
    int grp_index = phl/8;
    int goal = rice[grp_index] + 20;
    while (rice[grp_index] < goal) {
        float eat_time = rand()%5000 + 1000;
        usleep(eat_time);
        if (rice[grp_index] < goal) {
            rice[grp_index]++;
            push(phl, &queues[grp_index]);
        }
    }
    pthread_exit(NULL);
}

void *table(void *vargp) {
    int grp_index = *(int *)vargp;
    pthread_t phls[8];
    for (int i = 0; i < 8; i++) {
        eaten[grp_index * 8 + i] = 0;
        rice[grp_index] = 0;
        table_receipt[grp_index] = 0;
    }
    while (true) {
        int eaten_rice = rice[grp_index];
        bool end = true;
        for (int i = 0; i < 8; i++) {
            num_t *tmp = (num_t *)malloc(sizeof(num_t));
            tmp->n = grp_index * 8 + i;
            pthread_create(&phls[i], NULL, eat, tmp);
        }
        for (int i = 0; i < 8; i++) pthread_join(phls[i], NULL);
        for (int i = 0; i < 20; i++) eaten[queues[grp_index].arr[i]]++;
        rice[grp_index] = eaten_rice + 20;
        clear(&queues[grp_index]);
        for (int i = 0; i < 8; i++)
            if (eaten[grp_index * 8 + i] == 0)
                end = false;
        table_receipt[grp_index]++;
        if (end) break;
    }
    running_threads_table[grp_index] = -1;
    pthread_exit(NULL);
}

int main() {
    int nums[10] = {0,1,2,3,4,5,6,7,8,9};
    int grp_count;
    srand(time(NULL));
    pthread_t thread_ids[10];
    scanf("%d", &grp_count);
    for (int i = 0; i < 10 && grp_count > 0; i++, grp_count--) {
        queues[i].rear = 0;
        running_threads_table[i] = 1;
        table_counter[i] = last_phl++;
        pthread_create(&thread_ids[i], NULL, table, &nums[i]);
    }
    while (grp_count > 0) {
        for (int i = 0; i < 10 && grp_count > 0; i++) {
            if (running_threads_table[i] == -1) {
                pthread_join(thread_ids[i], NULL);
                print_receipt(i);
                running_threads_table[i] = 1;
                table_counter[i] = last_phl++;
                pthread_create(&thread_ids[i], NULL, table, &nums[i]);
                grp_count--;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        if (running_threads_table[i] == 0)
            continue;
        pthread_join(thread_ids[i], NULL);
        print_receipt(i);
    }
    return 0;
}
