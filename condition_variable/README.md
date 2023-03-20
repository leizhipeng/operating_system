# Condition variable

`std::condition_variable` is a synchronization primitive used in conjunction with a mutex, such as `std::mutex` or `std::recursive_mutex`, to allow one or more threads to wait for some condition to become true. It is often used to coordinate the activities of multiple threads that access shared data.

Here's an example of how to use `std::condition_variable` with a mutex and `std::unique_lock`.

In this example, we have two threads: one thread (t1) prepares the data, and another thread (t2) processes the data. The process_data function should wait for the prepare_data function to complete before starting its work.

We use a `std::condition_variable` (cv) to make the process_data function wait for the data to be ready. When the data is ready, the prepare_data function sets the ready variable to true and calls `cv.notify_one()` to wake up the waiting thread.

In the process_data function, we use `cv.wait()` to wait for the condition to be met. The first argument to `cv.wait()` is a `std::unique_lock` object that locks the mutex, ensuring that only one thread can access the shared data at a time. The second argument is a lambda function that returns true when the condition is met (in this case, when ready is true). The `cv.wait()` function will atomically release the lock and block the thread until the condition is met or another thread calls `cv.notify_one()` or `cv.notify_all()`.

Using `std::condition_variable`, you can efficiently coordinate the activities of multiple threads and ensure that they wait for specific conditions to be met before proceeding with their tasks.
