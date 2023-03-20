#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx; // Mutex to protect shared data
std::condition_variable cv; // Condition variable to coordinate threads
bool ready = false; // Shared variable to indicate when the data is ready

void prepare_data() {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate data preparation

    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    ready = true; // Update the shared variable
    cv.notify_one(); // Notify waiting threads that the condition is met
}

void process_data() {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    cv.wait(lock, []{ return ready; }); // Wait for the condition to be met
    std::cout << "Processing data..." << std::endl;
}

int main() {
    std::thread t1(prepare_data);
    std::thread t2(process_data);

    t1.join();
    t2.join();

    return 0;
}
