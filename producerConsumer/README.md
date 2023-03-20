# Producer-Consumer Problem

The producer-consumer problem, also known as the bounded-buffer problem, is a classic concurrency problem that illustrates the challenges of synchronizing multiple threads that access shared data. The problem involves two types of threads: producers and consumers. Producers generate data and store it in a shared buffer, while consumers read and remove data from the buffer. The buffer has a fixed size, and both producers and consumers operate independently and concurrently.

The main challenges in the producer-consumer problem are:

* Ensuring mutual exclusion: Only one thread should access the buffer at a time to avoid race conditions and data corruption. This can be achieved using synchronization primitives such as mutexes, locks, or semaphores.

* Handling buffer full and buffer empty conditions: Producers must wait when the buffer is full, and consumers must wait when the buffer is empty. Condition variables or semaphores can be used to coordinate the activities of producers and consumers, ensuring they wait and signal each other when data is available or buffer space is free.

## Example

Here's a simple example of the producer-consumer problem using C++11, `std::mutex`, `std::condition_variable`, and a bounded buffer implemented with `std::queue`.

In this example, producers and consumers use a `std::mutex` and `std::unique_lock` to ensure mutual exclusion when accessing the shared buffer. Producers wait on a `std::condition_variable` (`producer_cv`) until there's space in the buffer to produce a new item, while consumers wait on another `std::condition_variable` (`consumer_cv`) until there's an item available in the buffer to consume. Producers and consumers signal each other using notify_one() when they've produced or consumed an item, allowing the other party to proceed with their tasks.
