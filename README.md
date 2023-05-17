# Philosophers

This project was completed as part of the curriculum at École 42. The goal of the project is to simulate the behavior of philosophers who eat spaghetti and reflect between bites. The project is written in C and implements a solution to the dining philosophers problem using threads and semaphores. 

## Installation

To install and run the program, follow these steps:

1. Clone the repository to your local machine.
2. Open a terminal window and navigate to the root directory of the project.
3. Run the command `make` to compile the program.
4. Run the program using the command `./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]`.

## Usage

The program takes five command-line arguments:

1. `number_of_philosophers`: the number of philosophers at the table (must be at least 2).
2. `time_to_die`: the time in milliseconds after which a philosopher dies if they have not started eating.
3. `time_to_eat`: the time in milliseconds that a philosopher takes to eat.
4. `time_to_sleep`: the time in milliseconds that a philosopher takes to sleep.
5. `number_of_times_each_philosopher_must_eat`: the number of times each philosopher must eat before the program ends (optional).

If the `number_of_times_each_philosopher_must_eat` argument is not provided, the program will run indefinitely until a philosopher dies or the program is manually stopped.

## Example

Here's an example of how to run the program with three philosophers:

```
./philo 3 600 200 200
```

In this example, there are three philosophers at the table, each with a time to die of 600 milliseconds, a time to eat of 200 milliseconds, and a time to sleep of 200 milliseconds.

## Credits

This project was completed by Léon Pupier (lpupier) as part of the curriculum at École 42.
