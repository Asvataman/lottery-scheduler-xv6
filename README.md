# Lottery Scheduler Implementation in xv6

This project implements a lottery scheduler in the xv6 operating system, replacing the default round-robin scheduler. The lottery scheduler assigns CPU time to processes based on the number of tickets they hold, providing a probabilistic approach to process scheduling.

## Features

1. **Lottery Scheduler**: Replaces the round-robin scheduler in xv6 with a lottery-based scheduling algorithm.

2. **New System Calls**:
   - `settickets(int)`: Sets the number of tickets for the calling process.
   - `getpinfo(struct pstat *)`: Retrieves information about all running processes.

3. **Ticket Inheritance**: Child processes inherit the same number of tickets as their parent upon creation.

4. **Random Number Generator**: Implements a pseudo-random number generator in the kernel for lottery selection.

5. **Process Statistics**: Tracks and provides information about process execution, including ticket count and CPU time slices received.

## Implementation Details

### settickets(int)

- **Prototype**: `int settickets(int)`
- **Description**: Sets the number of tickets for the calling process.
- **Return Value**: 0 if successful, -1 otherwise.
- **Default**: Each process starts with one ticket.

### getpinfo(struct pstat *)

- **Prototype**: `int getpinfo(struct pstat *)`
- **Description**: Returns information about all running processes.
- **Return Value**: 0 if successful, -1 if an invalid pointer is passed.
- **Data Structure**: Uses the `pstat` structure defined in `pstat.h`.

### Scheduler Implementation

- Located primarily in `proc.c` and `proc.h`.
- Replaces the round-robin implementation with lottery scheduling logic.
- Assigns and manages tickets for processes.
- Implements a pseudo-random number generator for ticket selection.

## Building and Running

1. Clone the repo
2. Compile the modified xv6 kernel
   ```console
   bash> make
   ```
3. Run xv6 with one CPU. The makefile has been updated to run with one CPU. If the original makefile is used use the following command
   ```console
   make qemu CPUS=1
   ```

## Testing

Test programs are available to verify the correct implementation of the lottery scheduler. These tests check various aspects of the scheduler, including ticket assignment, process creation, and CPU time distribution.

## Performance Analysis

A graph demonstrating the CPU time distribution among processes with different ticket allocations (3:2:1 ratio) is included in the project documentation. This graph visually confirms the proportional allocation of CPU time based on ticket count.

## Notes

- This project is based on the xv6 operating system, a reimplementation of Unix V6.
- The implementation focuses on maintaining the existing xv6 code structure while introducing the new scheduling algorithm.
- Careful consideration has been given to kernel security, especially when handling user-space pointers.

## Contributors

1. Asvataman Venkatesan
2. Sriman Satish
