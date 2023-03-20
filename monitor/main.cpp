#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Counter {
private:
    int count;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Counter() : count(0) {}

    void increment() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        std::cout << "Incremented count: " << count << std::endl;
        lock.unlock();
        cv.notify_all();
    }

    void decrement() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return count > 0; });
        --count;
        std::cout << "Decremented count: " << count << std::endl;
        lock.unlock();
    }
};

void incrementer(Counter& counter) {
    for (int i = 0; i < 10; ++i) {
        counter.increment();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void decrementer(Counter& counter) {
    for (int i = 0; i < 10; ++i) {
        counter.decrement();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    Counter counter;
    std::thread inc_thread(incrementer, std::ref(counter));
    std::thread dec_thread(decrementer, std::ref(counter));

    inc_thread.join();
    dec_thread.join();

    return 0;
}