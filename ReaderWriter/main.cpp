#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <chrono>
#include <random>

constexpr int num_readers = 5;
constexpr int num_writers = 5;
constexpr int X = 5;

std::mutex mtx;
std::condition_variable cv;
int shared_variable = 0;
int active_readers = 0;
int waiting_readers = 0;

void reader(int id) {
    for (int i = 0; i < X; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100 + 1));
        std::unique_lock<std::mutex> lock(mtx);
        waiting_readers++;
        cv.wait(lock, []{ return waiting_readers == 1; });
        waiting_readers--;
        active_readers++;

        lock.unlock();
        int value = shared_variable;
        std::cout << "Reader " << id << " read value: " << value << ", active readers: " << active_readers << std::endl;

        lock.lock();
        active_readers--;
        if (active_readers == 0) {
            cv.notify_all();
        }
        lock.unlock();
    }
}

void writer(int id) {
    for (int i = 0; i < X; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100 + 1));
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return active_readers == 0 && waiting_readers == 0; });

        shared_variable = id;
        std::cout << "Writer " << id << " wrote value: " << shared_variable << ", active readers: " << active_readers << std::endl;

        cv.notify_all();
    }
}

int main() {
    srand(time(nullptr));
    std::vector<std::thread> threads;

    for (int i = 0; i < num_readers; i++) {
        threads.push_back(std::thread(reader, i));
    }

    for (int i = 0; i < num_writers; i++) {
        threads.push_back(std::thread(writer, i));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
