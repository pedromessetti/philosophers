<h1 align="center">Philosophers</h1>

## Index
- [Index](#index)
- [Description :clipboard:](#description-clipboard)
- [Operation :gear:](#operation-gear)
- [Learnings :brain:](#learnings-brain)

## Description :clipboard:
The dinning philosophers problem

## Operation :gear:

## Learnings :brain:

- **POSIX threads** (pthreads) library - Set of C programming language threads (or lightweight processes) that provides a standardized interface for creating and manipulating threads, as well as synchronization and communication between threads. The library provides a number of functions for creating, managing, and synchronizing threads. It is a powerful and flexible way to write multithreaded programs that can take advantage of modern hardware with multiple cores and processors.

- `pthread_t` object - data type used to represent a thread in the POSIX threads library. It's used to identify a thread and is created when a new thread is created using `pthread_create()` function. The `pthread_t` object is used as a parameter in other functions that operate on threads.

- `pthread_create()` function - Used to create a new thread from the current process. Takes 4 parameters:

  - A pointer to a `pthread_t` object that will hold the ID of the new thread.
  - A pointer to a `pthread_attr_t` object that specifies the attributes for the new thread being created. These attributes include things like the stack size, scheduling policy, and priority. If `NULL` is passed, the default attributes are used.
  - A pointer to the function that the new thread will execute.
  - A pointer to the argument that will be passed to the function. If no argument is needed, `NULL` can be passed.

    The function returns an integer value. If the function succeeds, it returns 0. If fails, returns an error code indicating the reason for the failure.

- `pthread_join()` function - Used to wait for a thread to terminate. Takes two parameters:

  - A `pthread_t` object that identifies the thread to wait for.
  - A pointer to a void pointer that will receive the exit status of the thread.

    When the function is called, the calling thread will block until the specified thread terminates. If the thread has already terminated, `pthread_join()` returns immediately. The exit status of the thread is stored in the location pointed to by the second parameter.