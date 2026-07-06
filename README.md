# philosophers

An implementation of the Dining Philosophers synchronization problem using POSIX threads and mutexes in C.

## Overview

This project simulates the classic Dining Philosophers problem: N philosophers sit around a circular table with N forks. Each philosopher alternates between thinking and eating. To eat, a philosopher must acquire both forks (left and right). The goal is to prevent deadlock and starvation using thread synchronization primitives.

### Problem Constraints

- N philosophers, N forks arranged in a circle
- Each philosopher needs exactly two forks to eat
- Philosophers alternate: eating → sleeping → thinking
- Monitor thread watches for philosopher starvation
- Simulation ends when a philosopher dies or all philosophers have eaten the required number of meals

## Building

```bash
cd philo
make              # Compile the program
make clean        # Remove object files
make fclean       # Remove all build artifacts
make re           # Clean and rebuild
make run ARGS="4 410 200 200"  # Compile and run
```

## Usage

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

### Arguments

| Parameter | Type | Unit | Description |
|-----------|------|------|-------------|
| `number_of_philosophers` | int | - | Number of philosophers (and forks) |
| `time_to_die` | int | ms | Time before philosopher dies without eating |
| `time_to_eat` | int | ms | Duration of eating |
| `time_to_sleep` | int | ms | Duration of sleeping |
| `number_of_meals` | int | - | (Optional) Meals required per philosopher; ends simulation if all philosophers reach this count |

### Examples

```bash
./philo 4 410 200 200         # 4 philosophers, simulation ends when someone dies
./philo 4 410 200 200 5        # 4 philosophers, ends when each eats 5 meals
./philo 1 800 200 200          # Edge case: 1 philosopher with 800ms to die
```

## Implementation Details

### Data Structures

**Philosopher** (`t_philo`):
- Unique ID
- Meal count and timestamp of last meal
- Individual fork (mutex) for left side
- Reference to global simulation data
- Associated thread

**Simulation** (`t_data`):
- Configuration parameters (timings, philosopher count)
- Shared mutex for global state
- Circular linked list of philosophers
- Simulation start time and stop flag

### Synchronization Strategy

**Fork Acquisition:**
- Each philosopher owns a left fork (mutex)
- Acquires forks in ID order to prevent circular wait
- Right fork belongs to next philosopher in circle

**Meal Tracking:**
- Each philosopher has `mtx_meal` protecting meal count and timestamp
- Monitor thread checks elapsed time since last meal

**Global State:**
- Single `mtx_info` protects `end_simulation` flag
- All threads check this flag before continuing

**Monitor Thread:**
- Independently iterates through philosophers
- Detects starvation: `current_time - time_last_meal > time_to_die`
- Prints death and terminates simulation

### File Structure

| File | Purpose |
|------|---------|
| `philo.c` | Main entry point, argument parsing |
| `philosophers.h` | Header with struct definitions and function declarations |
| `errors_case/errors.c` | Input validation and error messages |
| `init/init_data_philo.c` | Philosopher struct initialization |
| `init/init_data_routine.c` | Configuration parsing from arguments |
| `init/init_struct.c` | Table setup and circular linking |
| `program_engine/routine.c` | Eat, sleep, think state logic |
| `program_engine/engine.c` | Thread creation and monitor loop |
| `program_engine/philo_create.c` | Thread spawning |
| `utils/utils_nb_*.c` | Utility functions: time, string parsing, mutex operations |

### Key Functions

| Function | Purpose |
|----------|---------|
| `philo_routine()` | Main philosopher loop: acquire forks, eat, sleep, think |
| `monitor()` | Watches for starvation and meal completion |
| `fork_lock()` / `fork_unlock()` | Acquire/release both forks safely |
| `mtx_get_last_meal()` | Thread-safe access to last meal timestamp |
| `check_all_philosophers_meals()` | Verify all philosophers reached meal quota |
| `get_time_simulation()` | Get elapsed time since simulation start |

## Synchronization Guarantees

**No Deadlock:** 
- Forks acquired in consistent order (ID-based)
- Timeout mechanism prevents indefinite waiting

**Starvation Prevention:**
- Monitor thread enforces time-to-die constraint
- Simulation terminates if any philosopher exceeds this limit
- Optional meal count creates fairness goal

**Race Condition Prevention:**
- Separate mutexes for different concerns: forks, meals, global state
- All shared state access protected by appropriate mutex

## Output Format

```
<timestamp_ms> <philosopher_id> <action>
```

Actions: `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`

Colors: eating (green), thinking (bold yellow), other (neutral)

## Edge Cases Handled

- **Single philosopher:** Dies immediately (only one fork available)
- **No meal requirement:** Simulation runs until starvation
- **Large timing values:** Prevents integer overflow with `long` type
- **Minimal philosophers:** 2+ philosophers for meaningful synchronization

## Performance Notes

- Minimal synchronization overhead on small thread counts
- Scaling behavior depends on system load and context switch cost
- Monitor thread runs continuously; 100µs sleep between checks balances responsiveness and CPU usage

## License

Academic project for 42 School.
