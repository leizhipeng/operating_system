#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

const int NUM_READERS = 5;
const int NUM_WRITERS = 5;
const int X = 5;

pthread_mutex_t mutex;
pthread_cond_t reader_cond, writer_cond;

int shared_var = 0;
int readers_count = 0;
int writers_count = 0;

void* reader(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < X; i++) {
        usleep(rand() % 1000);

        pthread_mutex_lock(&mutex);
        readers_count++;
        while (writers_count > 0) {
            pthread_cond_wait(&reader_cond, &mutex);
        }

        std::cout << "Reader " << id << " reads " << shared_var << ", readers present: " << readers_count << std::endl;

        readers_count--;
        if (readers_count == 0) {
            pthread_cond_signal(&writer_cond);
        }
        pthread_mutex_unlock(&mutex);
    }

    return nullptr;
}

void* writer(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < X; i++) {
        usleep(rand() % 1000);

        pthread_mutex_lock(&mutex);
        writers_count++;
        while (readers_count > 0) {
            pthread_cond_wait(&writer_cond, &mutex);
        }

        shared_var = rand() % 100;
        std::cout << "Writer " << id << " writes " << shared_var << ", readers present: " << readers_count << std::endl;

        writers_count--;
        if (writers_count == 0) {
            pthread_cond_broadcast(&reader_cond);
        } else {
            pthread_cond_signal(&writer_cond);
        }
        pthread_mutex_unlock(&mutex);
    }

    return nullptr;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&reader_cond, nullptr);
    pthread_cond_init(&writer_cond, nullptr);

    int ids[NUM_READERS + NUM_WRITERS];
    for (int i = 0; i < NUM_READERS + NUM_WRITERS; i++) {
        ids[i] = i + 1;
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], nullptr, reader, (void*)&ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], nullptr, writer, (void*)&ids[NUM_READERS + i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], nullptr);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&reader_cond);
    pthread_cond_destroy(&writer_cond);

    return 0;
}
