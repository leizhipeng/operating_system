/*
In this example, we use a std::queue as a shared buffer between a producer and consumer thread. The producer generates items (integer values) and puts them into the buffer, while the consumer reads items from the buffer and consumes them.

To synchronize access to the buffer, we use two semaphores:

empty_slots: This semaphore represents the number of empty slots in the buffer, initialized with the maximum buffer size (BUFFER_SIZE). The producer thread acquires an empty slot before inserting an item into the buffer, and the consumer thread releases an empty slot after consuming an item.

filled_slots: This semaphore represents the number of filled slots in the buffer, initialized with 0. The consumer thread acquires a filled slot before consuming an item from the buffer, and the producer thread releases a filled slot after inserting an item into the buffer.

Additionally, we use a std::mutex (mtx) to protect the shared buffer and ensure that only one thread can access it at a time.

To compile and run this example, make sure to use a C++20-compatible compiler, such as GCC 10 or later:

```sh
g++ -std=c++20 main.cpp -o semaphore_example
./semaphore_example
```
*/



#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <semaphore>
#include <queue>
#include <chrono>

const int BUFFER_SIZE = 5;
const int NUM_ITEMS = 20;

std::queue<int> buffer;
std::mutex mtx;
std::counting_semaphore<BUFFER_SIZE> empty_slots(BUFFER_SIZE);
std::counting_semaphore<BUFFER_SIZE> filled_slots(0);

void producer() {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        empty_slots.acquire();
        {
            std::unique_lock<std::mutex> lock(mtx);
            buffer.push(i);
            std::cout << "Produced: " << i << std::endl;
        }
        filled_slots.release();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void consumer() {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        filled_slots.acquire();
        int item;
        {
            std::unique_lock<std::mutex> lock(mtx);
            item = buffer.front();
            buffer.pop();
            std::cout << "Consumed: " << item << std::endl;
        }
        empty_slots.release();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}

