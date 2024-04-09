# Readers-Writers Problem

## Introduction
The Readers-Writers problem addresses a scenario where a data structure, database, or resource can be read by multiple threads simultaneously but only written to by one at a time to prevent race conditions. This implementation showcases a classic solution using modern C++ features, including `std::shared_mutex` for managing concurrent reads while ensuring exclusive write access.

## Requirements
- C++17 compatible compiler
- Make (optional for building)

## Compilation and Execution
Navigate to the `Readers-Writers` directory in your terminal and execute the following commands to compile the program:

```
make clean
make
```

This generates an executable in the `bin` directory. To run the program, use:

```
./bin/readers-writers
```

## Implementation Details
The solution uses a `SharedResource` class protected by a `std::shared_mutex`. This mutex allows multiple threads to hold a shared lock for reading while ensuring an exclusive lock is required for writing. The program dynamically creates threads for readers and writers, demonstrating the concurrency control mechanism in action.

- **Readers** acquire a shared lock to read the resource without blocking other readers.
- **Writers** require an exclusive lock, preventing any other reader or writer from accessing the resource during a write operation.

This example creates 3 reader threads and 2 writer threads, each performing a series of read or write operations on the shared resource.

## License
This project is licensed under the MIT License - see the LICENSE file in the root directory of this repository for details.