<h1 align="center">Philosophers</h1>

## Index
- [Index](#index)
- [Description :clipboard:](#description-clipboard)
- [Operation :gear:](#operation-gear)
- [Usage](#usage)
- [Learnings :brain:](#learnings-brain)
- [Author](#author)

## Description :clipboard:
The project is designed to simulate a dining scenario where N philosophers sit around a table and alternate between eating, thinking, and sleeping. The challenge lies in coordinating their actions while avoiding deadlocks and ensuring that no philosopher starves. For more information about the project check the [subject here](https://github.com/pedromessetti/philosophers/blob/master/subject.pdf). The program was written following the rules described in the 42 Norme. To check the Norme [click here](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf)

## Usage
Clone the repository and navigate to the project directory.

Compile the program using `make` command.

Run the executable with the required arguments:
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- `number_of_philosophers`: The number of philosophers on the simulation.
- `time_to_die`: Time in milliseconds for a philosopher to die if not eating.
- `time_to_eat`: Time in milliseconds for a philosopher to eat.
- `time_to_sleep`: Time in milliseconds for a philosopher to sleep.
- `number_of_times_each_philosopher_must_eat` (optional): The number of times each philosopher must eat before the simulation stops.

## Operation :gear:
Each philosopher is represented as a thread, and they interact with forks using mutexes to ensure safe concurrent access. The program simulates philosophers engaging in 3 activities:

- **Eating**: Philosophers grab the forks on their left and right side, start eating and after finished, release the forks.

- **Sleeping**: After eating, philosophers enter a sleep state for a specified duration.

- **Thinking**: Philosophers think until it's time to eat again.

The challenge lies in managing the access to forks and ensuring that no two philosophers try to eat using the same fork simultaneously. Mutexes are used to synchronize access to shared resources and prevent race conditions. Here is the logic behind the program:

First, initializes the data structures and resources needed for the simulation, philosophers threads are created, each representing a philosopher and mutexes are set up to ensure synchronized access to shared resources like forks and output.

Then the simulation begins, each philosopher (thread) starts executing the routine function, which simulates their actions. When a philosopher eats, they acquire the forks (mutexes) on their left and right side, always checking if they have exclusive access to them. After eating and before sleeping, the philosopher release the forks allowing other philosophers that depends on that forks to start eating.

Mutexes prevent multiple philosophers from simultaneously grabbing the same fork, avoiding potential deadlock scenarios. Philosophers are given a limited time to eat, preventing starvation by ensuring they eat within a certain time frame.

The program generates output messages using printf to display philosophers' states (eating, sleeping, thinking).
Messages are formatted with timestamps and philosopher id.

The simulation continues until one of the following conditions is met:
 - All philosophers have completed the specified number of meals (number_of_times_each_philosopher_must_eat).
- A philosopher dies of starvation (reaches time_to_die without eating).

When the simulation ends, philosopher threads are joined, and resources are cleaned up.

## Learnings :brain:
Through this project, I've gained valuable insights into threads, synchronization, and concurrent programming. Some key takeaways include:

- **Threads** - Smallest units of execution within a program, representing independent paths of execution that share the same memory space and resources of their parent process. Threads enable concurrent execution, allowing multiple tasks to be carried out simultaneously within a single program. This concurrency enhances program performance and responsiveness, making threads an essential tool for multitasking and parallelism in programming.

- **mutex** - Short for "MUTual EXclusion", is a synchronization mechanism used in concurrent programming to control access to shared resources or critical sections by multiple threads. It ensures that only one thread can access the protected resource at a time, preventing race conditions and data corruption. When a thread acquires a mutex, it gains exclusive access to the associated resource, while other threads attempting to acquire the same mutex are blocked until it's released. Mutexes are crucial for maintaining data integrity and preventing conflicts in multithreaded environments.

- **POSIX threads** (pthreads) library - Set of C programming language threads (or lightweight processes) that provides a standardized interface for creating and manipulating threads, as well as synchronization and communication between threads. The library provides a number of functions for creating, managing, and synchronizing threads. It is a powerful and flexible way to write multithreaded programs that can take advantage of modern hardware with multiple cores and processors.

- `pthread_t` - data type used to represent a thread in the POSIX threads library. It's used to identify a thread and is created when a new thread is created using `pthread_create()` function. The `pthread_t` object is used as a parameter in other functions that operate on threads.

- `pthread_create()` - Function used to create a new thread from the current process. Takes 4 parameters:
  - A pointer to a `pthread_t` object that will hold the ID of the new thread.
  - A pointer to a `pthread_attr_t` object that specifies the attributes for the new thread being created. These attributes include things like the stack size, scheduling policy, and priority. If `NULL` is passed, the default attributes are used.
  - A pointer to the function that the new thread will execute.
  - A pointer to the argument that will be passed to the function. If no argument is needed, `NULL` can be passed.

    The function returns an integer value. If the function succeeds, it returns 0. If fails, returns an error code indicating the reason for the failure.

- `pthread_join()` function - Used to wait for a thread to terminate. Takes two parameters:

  - A `pthread_t` object that identifies the thread to wait for.
  - A pointer to a void pointer that will receive the exit status of the thread.

    When the function is called, the calling thread will block until the specified thread terminates. If the thread has already terminated, `pthread_join()` returns immediately. The exit status of the thread is stored in the location pointed to by the second parameter.

## Author
| [<img src="https://avatars.githubusercontent.com/u/105685220?v=4" width=115><br><sub>Pedro Vinicius Messetti</sub>](https://github.com/pedromessetti) |
| :---------------------------------------------------------------------------------------------------------------------------------------------------: |