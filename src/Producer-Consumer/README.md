# Producer-Consumer Problem

## Introduction
The Producer-Consumer problem is a classic synchronization challenge where two processes, the producer and the consumer, share a common, fixed-size buffer. The producer's job is to generate data, put it into the buffer, and start again. At the same time, the consumer consumes the data from the buffer. This implementation uses modern C++ features such as threads, mutexes, and condition variables to solve the problem efficiently.

## Requirements
- C++17 compatible compiler
- Make (optional for building)

## Compilation and Execution
To compile the Producer-Consumer program, navigate to the `Producer-Consumer` directory in your terminal and run the following commands:

```
make clean
make
```

This will produce an executable in the `bin` directory. To run the program, execute:

```
./bin/producer-consumer
```

## Implementation Details
The `BoundedBuffer` class is at the core of the solution, implementing a circular buffer with thread-safe methods for producing and consuming items. The `produce` and `consume` methods use mutexes and condition variables to ensure that the producer waits when the buffer is full and the consumer waits when the buffer is empty. The main function initializes a `BoundedBuffer` of size 10 and creates one producer and one consumer thread, each processing 10 items.

## License
This project is licensed under the MIT License - see the LICENSE file in the root directory of this repository for details.