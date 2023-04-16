# Debugger

The memory debugger shall wrap malloc, calloc, realloc, and free. It shall provide a simple debugging interface for tracking memory allocations and leaks.
Do accomplish this, the debugger shall provide the following functions:

* A hash table to store the memory allocations
* A function to add a memory allocation to the hash table
* A function to remove a memory allocation from the hash table
* A function to print the memory allocations in the hash table
