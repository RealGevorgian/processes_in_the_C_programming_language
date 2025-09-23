# Report on Process Management Assignments

This report documents the solutions and explanations for five assignments focused on process management in the C programming language. Each assignment demonstrates a core concept such as process creation, synchronization, cleanup, exit statuses, and handling zombies.

All assignments and this report are hosted in the GitHub repository: https://github.com/RealGevorgian/processes_in_the_C_programming_language.git


## Folder Structure

```
processes_in_the_C_programming_language/
├── src/
│   ├── assignment1.c  # Basic process creation with fork()
│   ├── assignment2.c  # Using wait() and waitpid() for synchronization
│   ├── assignment3.c  # Understanding atexit() for process cleanup
│   ├── assignment4.c  # Fork and exit status handling
│   └── assignment5.c  # Handling zombie processes
├── Report.md          # Detailed analysis of all assignments
└── README.md          # Project overview and instructions
```


---

## Assignment 1: Basic Process Creation with fork()

**Objective:** Understand how a process can create a child using `fork()`.

**Program Summary:**

* The parent process calls `fork()`, which creates a child process.
* In the child branch (`pid == 0`), the child prints its PID using `getpid()` and terminates.
* In the parent branch, the parent prints its own PID without waiting for the child to complete.
* If `fork()` fails, an error is printed.

**Key Takeaways:**

* `fork()` duplicates the process, returning `0` in the child and the child’s PID in the parent.
* Parent and child execute independently after the fork.
* This program demonstrates asynchronous execution.

**Expected Output Example:**

```
PID of the Child  12345
PID of the Parent 12344
```

---

## Assignment 2: Using wait() and waitpid()

**Objective:** Learn process synchronization with `wait()` and `waitpid()`.

**Program Summary:**

* First child: Created with `fork()`. The parent waits with `wait()` until it finishes and prints its exit status.
* Second child: Created with another `fork()`. The parent uses `waitpid()` to wait for this specific child and prints its exit status.
* Each child exits with different codes (0 and 42).
* The parent confirms both children’s completion.

**Key Takeaways:**

* `wait()` waits for any child process, while `waitpid()` can target a specific child.
* The `status` code from `wait()`/`waitpid()` can be decoded with `WEXITSTATUS`.

**Expected Output Example:**

```
1-st Child process PID -> 12345
Parent: 1-st Child (PID 12345) completed with status 0
2-nd Child process PID -> 12346
Parent: 2-nd Child (PID 12346) completed with status 42
Parent process PID is 12344 completed
```

---

## Assignment 3: Understanding atexit()

**Objective:** Learn how to use `atexit()` for cleanup functions.

**Program Summary:**

* The program registers two cleanup functions (`first_cleanup` and `second_cleanup`).
* When `exit()` is called, these functions run in reverse order of registration.
* Demonstrates that registered cleanup handlers will always be executed before termination.

**Key Takeaways:**

* `atexit()` is useful for resource cleanup (closing files, releasing memory, saving logs).
* Functions are executed LIFO (last-in, first-out).

**Expected Output Example:**

```
Main program is started -> PID: 12344
Registering the 1-st cleanup function...
Registering the 2-nd cleanup function...
Both cleanup functions registered successfully
About to call exit(0) - cleanup functions should execute now
2-nd Cleanup function is executed B
1-st Cleanup function is executed A
```

---

## Assignment 4: Fork and Exit Status

**Objective:** Manage multiple child processes and report their exit statuses.

**Program Summary:**

* The parent creates two child processes.
* The first child exits with code `0` (success).
* The second child exits with code `13` (custom exit code).
* The parent uses `waitpid()` to wait for both children and checks whether they exited normally.

**Key Takeaways:**

* `WIFEXITED(status)` checks if a process terminated normally.
* `WEXITSTATUS(status)` retrieves the actual exit code.
* Parents can differentiate between normal and abnormal termination.

**Expected Output Example:**

```
Parent (PID 12340) created the first Child (PID 12341)
The first child (PID 12341) is executing
Parent (PID 12340) created the second Child (PID 12342)
The second Child (PID 12342) executing
Parent waiting for Child 1 (PID 12341)...
The first Child (PID 12341) exited normally with status 0
Parent waiting for the second Child (PID 12342)...
The second Child (PID 12342) exited normally with status 13
Parent (PID 12340) completed all child processing
```

---

## Assignment 5: Handling Zombie Processes

**Objective:** Demonstrate zombie processes and their prevention.

**Program Summary:**

* **First version:** Creates a child, but the parent does not call `wait()`. The child terminates but remains in the process table as a zombie until the parent exits.
* **Second version:** The parent calls `wait()` after the child exits, properly reaping the child and preventing it from becoming a zombie.

**Key Takeaways:**

* A zombie process occurs when a child has terminated but its parent hasn’t collected its exit status.
* Using `wait()` or `waitpid()` ensures child processes are cleaned up.
* Tools like `htop`, `top`, or `ps` can be used to observe zombies.

**Expected Output Example:**

```
Starting the illustration -> PID: 12340
1-st version of the solution: Creating the zombie process.........
(PID 12341) Child created, and is now active
(PID 12340) Parent created child (PID 12341)
2-nd version of the solution: Trying to deny the zombie process..........
(PID 12342) Child created, and is active
(PID 12340) Parent created Child (PID 12342) and will wait
Parent (PID 12340) reaped Child (PID 12342) with status 0
(PID 12340) Parent completed all illustrations
```

---

## Finally

These assignments demonstrate key aspects of Unix process management:

* **Assignment 1** introduced basic `fork()`.
* **Assignment 2** showed synchronization with `wait()` and `waitpid()`.
* **Assignment 3** explored cleanup with `atexit()`.
* **Assignment 4** highlighted exit codes and monitoring child termination.
* **Assignment 5** illustrated zombie processes and their prevention.

Together, they provide a strong foundation for understanding process creation, lifecycle management, and synchronization in C.
