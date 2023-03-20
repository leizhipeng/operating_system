# ​Priority Readers and Writers

## Problem Statement

Develop a multi-threaded C++ program that prioritizes reader threads over writer threads when accessing a shared global variable. Specifically, reader threads should be granted priority when waiting, while writer threads can only write when no readers are present.

## Constraints

* The program must support multiple readers and writers (up to 5 of each).
* Each reader must read the shared variable X times.
* Each writer must write to the shared variable X times.
* When reading, readers must print:
  * The value read from the shared variable.
  * The number of readers present during the read operation.
* When writing, writers must print:
  * The value written to the shared variable.
  * The number of readers present during the write operation (which should be 0).
* Prior to accessing the shared variable, both readers and writers should wait for a random duration to prevent simultaneous reads and writes.
* Utilize pthreads, mutexes, and condition variables to synchronize access to the shared variable.

## Introduction

The reader-writer problem, also known as the readers-writers problem, is a classic concurrency problem that deals with the synchronization of multiple threads accessing a shared resource. The shared resource can be a data structure, a file, or any other piece of data that can be read or modified.

The problem consists of two types of threads: reader threads and writer threads. Reader threads only read the shared resource, while writer threads can modify it. The challenge is to synchronize access to the shared resource in a way that ensures data consistency, prevents race conditions, and maximizes concurrency.

There are several variations of the reader-writer problem, but the main requirements are generally as follows:

* Multiple reader threads can read the shared resource simultaneously, as long as no writer thread is modifying it.
* Only one writer thread can modify the shared resource at a time, and no reader thread can read the resource while a writer is modifying it.
Avoid starvation: Ensure that neither reader threads nor writer threads are indefinitely waiting to access the shared resource.
* To solve the reader-writer problem, various synchronization primitives, such as mutexes, semaphores, and condition variables, can be used. The solution needs to ensure that reader threads can access the shared resource concurrently (when there are no writers), while writers have exclusive access to the shared resource when they are modifying it.

Here's an outline of a possible solution using mutexes and condition variables:

* Use a mutex to protect access to the shared resource, ensuring that only one thread can access it at a time.
* Use a reader count variable to keep track of the number of reader threads currently reading the shared resource.
* Use a condition variable to make writer threads wait when there are reader threads reading the shared resource or another writer thread modifying the shared resource.
* When a reader thread wants to read the shared resource, it must first lock the mutex, increment the reader count, and then release the mutex. If this is the first reader, it should also make any waiting writer threads wait using the condition variable.
* When a reader thread is done reading, it must lock the mutex again, decrement the reader count, and release the mutex. If this is the last reader, it should notify any waiting writer threads using the condition variable.
* When a writer thread wants to modify the shared resource, it should lock the mutex and wait on the condition variable if there are any reader threads reading or another writer thread modifying the shared resource. Once it gets access to the shared resource, it can make the modifications and release the mutex.

This solution ensures that multiple reader threads can read the shared resource concurrently while ensuring that writer threads have exclusive access to the shared resource when they are modifying it. It also helps prevent starvation by using a condition variable to manage waiting threads.

## Compile the code
```
mkdir build
cd build
cmake ..
```

If CMake has used the Ninja build system as the default generator.

```c++
ninja
```

Otherwise.

```c++
make
```
