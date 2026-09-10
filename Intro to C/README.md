# Intro to C

Me following the C tutorial ayo. Each activity is its own little program w/ arrays, a calculator, and a heap-backed dynamic array. Build 'em with gcc and mess around in the terminal. Big blocker for me here was setting up the compiler and getting around with the Windows permission stuff.

## Tutorial

Follow along here: [Introduction to Git and C](https://confluence.analog.com/spaces/PHILSSG/pages/1299605203/3.+Introduction+to+Git+and+C)

## Activities

### Activity A — `Activity A/sort.c`
Sorts five integers into ascending order with bubble sort. Plays with the basic operators from the tutorial (relational, logical, arithmetic) and even swaps values in place using an XOR trick.

PR Link

### Activity B — `Activity B/calculator.c`
A looping calculator for two integers w/ add, subtract, multiply, divide. Keeps running until you pick Exit, validates input, guards against divide-by-zero, and only accepts operands from 0 to 100.

PR Link

### Activity C — `Activity C/dynamic_array.c`
A menu-driven growable array of ints on the heap:
- **Create** with `malloc()` (starts tiny w/ capacity 2)
- **Add** past the initial size — `realloc()` doubles the buffer when it fills up
- **Display** every element with its index, plus count/capacity
- **Modify** an element at a chosen index (range checked)
- **Free** the memory on exit so nothing leaks
- **Sort** ascending (bonus) — bubble sort merged in from Activity A

PR Link

## Build & run

Any activity builds the same way with the msys64 gcc:

```sh
gcc -g "Activity C/dynamic_array.c" -o "Activity C/dynamic_array.exe"
./"Activity C/dynamic_array.exe"
```

Or just open a `.c` file and hit **Run/Build** in VS Code. You setup your own gcc.
