# Philosophers (42 Project)

This project is a solution to the classic Dining Philosophers problem, implemented in C as part of the 42 curriculum. The goal is to manage concurrent access to shared resources (forks) using threads and mutexes, preventing deadlocks and starvation.

## Concept
The Dining Philosophers problem illustrates synchronization issues and resource sharing in concurrent programming. Philosophers alternately eat, think, and sleep, but need two forks to eat. The challenge is to coordinate their actions so that no philosopher starves or causes a deadlock.

## Usage
- Compile with `make` inside the `philo/` directory.
- Run with: `./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`

## Arguments
1. `number_of_philosophers` (int > 0)
2. `time_to_die` (ms)
3. `time_to_eat` (ms)
4. `time_to_sleep` (ms)
5. `[number_of_times_each_philosopher_must_eat]` (optional)

## Files
- `philo.c`: Main entry, argument parsing, initialization.
- `philosophers.h`: Header file.
- `errors_case/`: Error handling.
- `init/`: Initialization routines.
- `program_engine/`: Core logic and thread management.
- `utils/`: Utility functions.

## Note
This project is for educational purposes at 42. Keep it simple, follow the rules, and focus on understanding concurrency.
