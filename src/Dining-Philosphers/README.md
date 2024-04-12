# Dining Philosophers Problem

## Introduction
The Dining Philosophers problem is a classic example of a synchronization issue involving multiple processes (philosophers) that must share a limited number of resources (chopsticks). This implementation demonstrates a common solution to avoid deadlocks and ensure that each philosopher can eat without interfering with the others.

## Requirements
- C++17 compatible compiler
- Make (optional for building)

## Compilation and Execution
Navigate to the `Dining-Philosophers` directory in your terminal and execute the following commands to compile the program:

```
make clean
make
```

This creates an executable in the `bin` directory. To run the program, execute:

```
./bin/dining-philosophers
```

## Implementation Details
The solution uses a `Table` structure that holds a vector of mutexes representing chopsticks, and a `Philosopher` class for each philosopher. Each philosopher is given access to two chopsticks using a `std::unique_lock` with `std::defer_lock`, allowing them to lock both chopsticks simultaneously to eat and then release them. Philosophers alternate between thinking and eating to simulate the concurrency challenge.

- **Philosophers** must acquire two locks (chopsticks) to begin eating and release them when finished.
- The use of `std::defer_lock` combined with `std::lock` prevents deadlock by ensuring that both or neither of the chopsticks are locked simultaneously.

## License
This project is licensed under the MIT License - see the LICENSE file in the root directory of this repository for details.