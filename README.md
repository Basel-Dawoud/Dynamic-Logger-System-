# Dynamic Logger System with Signal-Based Log Level Control

This project implements a dynamic logger system that allows you to set the logging level of a logger process in real-time using signals. You can control the log level between `ERROR`, `WARNING`, `INFO`, and `DEBUG`. The log level can be changed by sending a signal to the logger process using a separate control program.

## Project Overview

This project consists of two main components:

1. **Logger Process**: The main process that logs messages based on the current log level.
2. **Set Log Level Process**: A control program that allows the user to change the log level of the logger process in real-time by sending specific signals.

### Log Levels:
- **ERROR**: Only error messages are logged.
- **WARNING**: Both error and warning messages are logged.
- **INFO**: Error, warning, and informational messages are logged.
- **DEBUG**: All messages (error, warning, info, and debug messages) are logged.

## Files

- `logger.c`: The main logger program that logs messages based on the current log level.
- `setLoggerLevel.c`: A control program that allows the user to change the log level of the logger process using signals.
  
## Setup

### 1. Clone the Repository
Clone the repository to your local machine.

```bash
git clone <repo_url>
cd <repo_folder>
```

### 2. Compile the Programs

Use `gcc` to compile both programs:

```bash
gcc -o logger logger.c
gcc -o setLoggerLevel setLoggerLevel.c
```

### 3. Run the Logger Program

First, start the logger process. This program will run continuously and print logs based on the log level set.

```bash
./logger
```

### 4. Change Log Levels Using Signals

Once the `logger` process is running, you can change its log level by using the `setLoggerLevel` program. This program sends a signal to the `logger` process to change its log level.

Usage:

```bash
./setLoggerLevel <log_level> <pid>
```

Where `<log_level>` can be one of:
- `error`
- `warning`
- `info`
- `debug`

And `<pid>` is the process ID of the running logger process.

For example, to set the log level to `debug`:

```bash
./setLoggerLevel debug <pid_of_logger>
```

### 5. Example

- Start the `logger` program in one terminal:

  ```bash
  ./logger
  ```

- In another terminal, change the log level by sending a signal:

  ```bash
  ./setLoggerLevel error <pid_of_logger>   # Logs only error messages
  ./setLoggerLevel warning <pid_of_logger> # Logs error and warning messages
  ./setLoggerLevel info <pid_of_logger>    # Logs error, warning, and info messages
  ./setLoggerLevel debug <pid_of_logger>   # Logs all messages (error, warning, info, and debug)
  ```

## Signal Handling

The `setLoggerLevel` program sends different signals to the `logger` process to change the log level:
- `SIGUSR1` for `ERROR`
- `SIGUSR2` for `WARNING`
- `SIGRTMIN` for `INFO`
- `SIGRTMAX` for `DEBUG`

The logger process listens for these signals and adjusts its log level accordingly. The log level changes in real-time without the need for restarting the logger process.

## Error Handling

If the user provides an invalid log level (e.g., "5" or "invalidLevel"), the `setLoggerLevel` program will print an error message and not send any signal to the logger process.

Example of an invalid input:
```bash
Invalid log level: 5
```

## Notes

- The `setLoggerLevel` program requires the process ID (PID) of the running logger process. You can obtain this by using `ps` or `pgrep` commands.
- The logger process will run indefinitely, so to stop it, use `Ctrl+C` to terminate it manually.

## Example Output

1. **Logger output (with `DEBUG` level):**

   ```bash
   Log level changed to DEBUG
   Debug message logged
   Info message logged
   Warning message logged
   Error message logged
   ```

2. **Set Log Level Output:**

   ```bash
   ./setLoggerLevel warning 12345
   Log level changed to WARNING
   ```

3. **Invalid Log Level:**

   ```bash
   ./setLoggerLevel invalidLevel 12345
   Invalid log level: invalidLevel
   ```

## Dependencies

- `gcc` (GNU Compiler Collection) for compiling the programs.
- Standard C libraries like `stdio.h`, `stdlib.h`, `unistd.h`, and `signal.h`.

## Contact
Email: baselinux2024@gmail.com
