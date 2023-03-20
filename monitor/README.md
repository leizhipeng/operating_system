# Monitor Demo in Concurrent Programming

This project demonstrates the use of a monitor to synchronize access to a shared resource in concurrent programming. A monitor is an object-oriented approach to synchronization, providing mutual exclusion and condition synchronization for threads that access shared resources.

## Introduction

In concurrency, a monitor is a synchronization construct that allows threads to have mutually exclusive access to a shared resource, along with providing a mechanism to wait for certain conditions to be met before proceeding with an operation.

A monitor is an object-oriented approach to synchronization, which typically combines a mutex (or other lock mechanism) and one or more condition variables to provide both mutual exclusion and condition synchronization.

A monitor has the following characteristics:

* Encapsulation: A monitor encapsulates the shared resource, along with its associated synchronization mechanisms (mutex and condition variables). This ensures that the resource is accessed only within the monitor, which helps maintain data consistency and integrity.

* Mutual Exclusion: A monitor ensures that only one thread can execute the monitor's methods at a time. This is typically achieved by acquiring a lock (such as a mutex) at the beginning of each method and releasing it at the end.

* Condition Synchronization: A monitor provides a way for threads to wait for specific conditions to be met before proceeding. This is done using condition variables, which allow threads to block until they receive a signal that the desired condition has been met. Condition synchronization helps prevent race conditions and ensures proper sequencing of operations.

## C++ Example

The example uses a simple `Counter` class as the shared resource, with two methods: `increment()` and `decrement()`. The `Counter` class is protected by a monitor, ensuring that only one thread can access it at a time. We use `std::mutex` and `std::unique_lock` to enforce mutual exclusion and `std::condition_variable` to handle condition synchronization.

### Usage

To compile and run the example, use the following commands:

```sh
g++ -std=c++11 main.cpp -o monitor_demo
./monitor_demo
```
