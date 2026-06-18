*This project has been created as part of the 42 curriculum by zaalrafa.*

# Dining Philosophers - Multitasking & Concurrency

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="C Language" />
  <img src="https://img.shields.io/badge/OS-Linux%20%2F%20macOS-lightgrey.svg" alt="OS Support" />
  <img src="https://img.shields.io/badge/School-42-black.svg" alt="42 School" />
</p>

## Description

The **Dining Philosophers** project is a classic computer science problem that illustrates the challenges of synchronization, multitasking, and resource sharing in concurrent programming. 

### The Scenario
A number of philosophers sit around a circular table doing one of three things: **eating**, **sleeping**, or **thinking**.
- While eating, they cannot think or sleep.
- While sleeping, they cannot eat or think.
- While thinking, they cannot eat or sleep.

There is a single fork placed between each adjacent pair of philosophers. To eat, a philosopher must acquire both their left and right forks. Once they finish eating, they return both forks to the table and begin sleeping. When they wake up, they start thinking again. The cycle repeats until a philosopher dies of starvation.

### Goal
The goal of this project is to implement a simulation of this scenario in **C**, using **threads** and **mutexes** to ensure that:
1. No two philosophers can hold the same fork simultaneously (Mutual Exclusion).
2. Philosophers do not get stuck in a state where no progress is made (Deadlock avoidance).
3. The simulation is highly precise and correctly reports state changes (no overlapping logs, no logs printed after death).

---

## Technical Features & Choices

- **Multithreading**: Each philosopher is represented by a separate thread (`pthread_t`), allowing them to act concurrently.
- **Mutex Protection**: Forks are represented by individual mutexes (`pthread_mutex_t`), ensuring safe sharing and preventing race conditions.
- **Deadlock Avoidance (Asymmetric Lock Acquisition)**:
  - **Even-numbered** philosophers pick up their **right** fork first, then their **left** fork.
  - **Odd-numbered** philosophers pick up their **left** fork first, then their **right** fork.
  This breaks the circular wait condition, guaranteeing deadlock-free simulation.
- **Starvation Monitoring**: The main thread runs a dedicated monitoring loop to check if any philosopher has exceeded the `time_to_die` since their last meal.
- **Precise Timing (`ft_usleep`)**: Instead of relying on a single `usleep()` call which can be imprecise, this implementation uses a custom polling sleep that wakes up in 1ms steps to check the global death flag, improving responsiveness and stopping accuracy.
- **Log Thread Safety**: A dedicated `print_mutex` protects console outputs to ensure logs do not overlap, and immediately blocks further prints after a death is recorded.

---

## Instructions

### Compilation
The project comes with a `Makefile` that compiles the sources using standard flags (`-Wall -Wextra -Werror -g -pthread`).

To build the executable, run the following command in the `philo/` directory:
```bash
make
```

This compiles the code and produces the `philo` executable.

Other Makefile targets:
- `make clean`: Removes all compiled object (`.o`) files.
- `make fclean`: Removes all object files and the `philo` binary.
- `make re`: Performs a clean build (`fclean` followed by `all`).

### Execution
Run the executable with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Arguments Detail:
1. **`number_of_philosophers`**: The number of philosophers (and forks) at the table.
2. **`time_to_die`** (in milliseconds): The time a philosopher can survive without eating. If this time passes since their last meal (or the start of the simulation), they die.
3. **`time_to_eat`** (in milliseconds): The duration a philosopher takes to eat (holding two forks).
4. **`time_to_sleep`** (in milliseconds): The duration a philosopher spends sleeping.
5. **`[number_of_times_each_philosopher_must_eat]`** (Optional): If specified, the simulation stops when all philosophers have eaten at least this many times. If not specified, the simulation runs until a philosopher dies.

#### Examples:
* **Starvation case** (one philosopher should die):
  ```bash
  ./philo 1 800 200 200
  ```
  *(Philosopher 1 has only one fork and will die at 800ms)*

* **Starvation case** (another death scenario):
  ```bash
  ./philo 4 310 200 100
  ```
  *(A philosopher should die of starvation)*

* **Infinite survival case** (no one should die):
  ```bash
  ./philo 5 800 200 200
  ```

* **Meal limit case** (simulation stops after everyone eats at least 7 times):
  ```bash
  ./philo 4 410 200 200 7
  ```

---

## Resources

### Classic References
- [Dining Philosophers Visualizer](https://rom98759.github.io/Philosophers-visualizer/) - Useful tool to visualize philosophers state changes and timing.
- [Code Vault - Unix Threads Playlist](https://youtube.com/playlist?list=PLGU1kcPKHMKi41Py2kqxdvqYE3M9VhCHe&si=ZJGbztb9Ejzekap1) - Excellent video playlist detailing concurrency, threads, and mutexes in Unix.
- [Introduction to Threads (Video)](https://www.youtube.com/watch?v=zOpzGHwJ3MU) - A quick introduction to multitasking and multithreading.
- [Philosophers 42 Guide by Ruinadd](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2) - A comprehensive guide on structuring the 42 project.
- [The Dining Philosophers by m4nnb3ll](https://m4nnb3ll.medium.com/the-dining-philoshophers-an-introduction-to-multitasking-a-42-the-network-project-34e4141dbc49) - Concept and implementation walkthrough.

### AI Usage Description
In accordance with the 42 curriculum requirements, here is the description of how Artificial Intelligence was used during the development of this project:
- **Scaffolding and Design Patterns**: AI was used to research standard concurrency architectures (such as asymmetric locking and monitor threads) to design an efficient solution for avoiding deadlocks.
- **Documentation and Code Review**: AI was utilized to draft this `README.md` document, conduct code analysis to ensure adherence to 42 Norminette requirements, and suggest micro-optimizations for time precision in simulation threads.
- **Explaining Concepts**: AI assisted in verifying concepts like race conditions, thread synchronization, data races, and debugging potential data-sharing issues during development.