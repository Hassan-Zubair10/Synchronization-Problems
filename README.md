# Synchronization Problems

## Introduction
This repository is dedicated to exploring classic synchronization problems in computer science using modern C++. Each problem is implemented with a focus on thread safety and efficient communication between threads.

## Problems Covered
- **Producer-Consumer:** Demonstrates how to handle the classic scenario where producers generate data and consumers process it, with a fixed-size buffer in between.
- **Dining Philosophers:** Illustrates solutions to avoid deadlocks when multiple processes require the same resources.
- **Readers-Writers:** Focuses on allowing multiple readers or a single writer to access a shared resource without conflicts.
- **Cigarette Smokers:** A synchronization problem that involves coordinating multiple agents with access to ingredients to make cigarettes.
- **No-Starve Mutex:** Implements a mutex that ensures fairness, preventing starvation of any thread.

## Getting Started
Each problem in the repository is contained in its own directory within the `src` folder and includes its own README.md for detailed instructions. Generally, you can compile and run each problem's solution by navigating to its directory and using the following commands:

```bash
make clean
make
./bin/<executable-name>
```

Replace `<executable-name>` with the specific executable for the problem you're running.

## Requirements
- A C++17 compatible compiler is required to build the solutions.
- GNU Make for compiling the projects (optional but recommended).

## License
This project is open-sourced under the MIT License. See the LICENSE file in the root directory for more information.

## Contributions
Contributions are welcome! If you'd like to add a solution to a new synchronization problem or improve an existing one, please feel free to open a pull request.