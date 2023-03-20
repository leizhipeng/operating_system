#include <iostream>
#include <mutex>
#include <condition_variable>

class Buffer {
private:
    int data;
    bool available;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Buffer() : available(false) {}

    void produce(int value) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !available; });
        data = value;
        available = true;
        std::cout << "Produced: " << data << std::endl;
        lock.unlock();
        cv.notify_all();
    }

    int consume() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return available; });
        int value = data;
        available = false;
        std::cout << "Consumed: " << value << std::endl;
        lock.unlock();
        cv.notify_all();
        return value;
    }
};
