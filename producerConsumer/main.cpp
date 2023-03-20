#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

const int buffer_size = 5;
std::queue<int> buffer;
std::mutex mtx;
std::condition_variable producer_cv, consumer_cv;

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        producer_cv.wait(lock, []{ return buffer.size() < buffer_size; });

        buffer.push(i);
        std::cout << "Producer " << id << " produced item " << i << std::endl;
        lock.unlock();

        consumer_cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        consumer_cv.wait(lock, []{ return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed item " << item << std::endl;
        lock.unlock();

        producer_cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
    }
}

int main() {
    srand(time(nullptr));
    std::thread p1(producer, 1);
    std::thread c1(consumer, 1);

    p1.join();
    c1.join();

    return 0;
}
