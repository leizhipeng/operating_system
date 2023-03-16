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
