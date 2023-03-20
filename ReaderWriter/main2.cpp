#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

constexpr int NUM_READERS = 5;
constexpr int NUM_WRITERS = 5;
constexpr int NUM_ITERATIONS = 10;

std::mutex resource_mtx;
std::mutex reader_count_mtx;
std::condition_variable writer_cv;
int reader_count = 0;
int shared_resource = 0;

void reader(int id) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        {
            std::unique_lock<std::mutex> lock(reader_count_mtx);
            ++reader_count;
            if (reader_count == 1) {
                resource_mtx.lock();
            }
        }

        std::cout << "Reader " << id << " read value " << shared_resource << std::endl;

        {
            std::unique_lock<std::mutex> lock(reader_count_mtx);
            --reader_count;
            if (reader_count == 0) {
                resource_mtx.unlock();
            }
            lock.unlock();
            writer_cv.notify_one();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void writer(int id) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::unique_lock<std::mutex> lock(resource_mtx);
        writer_cv.wait(lock, [&]() { return reader_count == 0; });

        ++shared_resource;
        std::cout << "Writer " << id << " wrote value " << shared_resource << std::endl;

        lock.unlock();
        writer_cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_READERS; ++i) {
        threads.emplace_back(reader, i);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        threads.emplace_back(writer, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
