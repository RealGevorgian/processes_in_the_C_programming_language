# Processes in C Programming Language

This repository contains a set of assignments that explore process creation, synchronization, cleanup, exit handling, and zombie process management in the C programming language. All tasks are implemented in separate source files and include explanations and sample outputs for clarity.

Repository link: [Processes in the C Programming Language](https://github.com/RealGevorgian/processes_in_the_C_programming_language.git)

## Folder Structure

```
processes_assignment/
├── src/
│   ├── assignment1.c  # Basic process creation with fork()
│   ├── assignment2.c  # Using wait() and waitpid() for synchronization
│   ├── assignment3.c  # Understanding atexit() for process cleanup
│   ├── assignment4.c  # Fork and exit status handling
│   └── assignment5.c  # Handling zombie processes
├── Report.md          # Detailed analysis of all assignments
└── README.md          # Project overview and instructions
```

## Assignments Overview

**Assignment 1: Basic Process Creation with fork()**
The first task demonstrates how a child process is created using the `fork()` system call. The child prints its PID and exits, while the parent prints its own PID without waiting. This shows how processes run independently.

**Assignment 2: Using wait() and waitpid()**
Here the focus is on synchronization. The parent waits for the child process to complete using `wait()`, and also demonstrates `waitpid()` to target a specific child. Exit statuses are retrieved and printed to show how parents monitor their children.

**Assignment 3: Understanding atexit()**
This program registers two functions with `atexit()`, which automatically run when the process terminates. Testing with different `exit()` placements highlights the order of cleanup execution and its usefulness in real-world scenarios, like releasing resources or logging.

**Assignment 4: Fork and Exit Status**
Two child processes are created, each returning a distinct exit code. The parent waits for both and reports whether each terminated normally or with an error. This assignment deepens understanding of exit statuses.

**Assignment 5: Handling Zombie Processes**
A demonstration of what happens when the parent does not call `wait()`: the child becomes a zombie. Using tools like `ps` or `htop`, one can observe the zombie process. The program is then modified to use `wait()`, resolving the zombie issue.

## How to Run

To try out the programs, clone the repository and compile the desired source file:

```bash
git clone https://github.com/RealGevorgian/processes_in_the_C_programming_language.git
cd processes_in_the_C_programming_language/src
gcc assignmentN.c -o assignmentN   # Replace N with 1, 2, 3, 4, or 5
./assignmentN
```

For Assignment 5, open another terminal and use `ps` or `htop` to observe zombie processes before and after applying `wait()`.

## Prerequisites

You need a GCC compiler, a Linux environment such as Ubuntu, and Git for cloning the repository.

## Notes

To visualize process relationships, the `pstree -p $(pidof assignmentN)` command can be very helpful, especially when experimenting with fork() and exit behavior.

---

This project serves as a foundation for understanding how processes work in C, giving practical experience with system calls that are crucial in operating systems and systems programming.
