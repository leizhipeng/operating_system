#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>

constexpr int num_threads = 10;
constexpr int max_concurrent_threads = 3;

std::counting_semaphore<max_concurrent_threads> sem((max_concurrent_threads));


void access_resource(int id) {
    sem.acquire();
    std::cout << "Thread " << id << " is accessing the resource." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " is done accessing the resource." << std::endl;
    sem.release();
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(access_resource, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
