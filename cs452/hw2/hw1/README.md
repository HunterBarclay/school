# Homework 1: Queue\<Anon\> (lmao)
- Hunter Barclay
- CS 452

### Deliverables
These files are mostly copied and pasted from the given files from the assignment. I'll be listing
the files I modified only:
- `deq.c` -> Queue (dequeue?) source file. Added implementations with supporting code docs
    for method stubs.
- `main.c` -> Main executable file. Includes unit tests for the queue and a sample queue that prints
    it's contents to the console for verification.
- `README.md` -> This file.

### Design Notes

#### Errors and Warnings
I opted to use the fatal error exclusively for a failed malloc invocation. That, plus a
warning for when you try to index out of bounds, are the only situations the user will be
notified via the console, or termination of the program, that they did something wrong.

In all other error/warning scenarios, I opted to return the null pointer. Mostly out of the
philosophy that a library should be a lot more considerate when reporting an issue. I'd love
to change the interface to account for that, but that's explicitly not allowed for this assignment.

#### NULL queue insertions
I opted to disallow NULL insertions. This library makes the assumption that you are giving a pointer, not the data,
and NULL is intentionally reserved to indicate an issue of state of the queue to the user. The issue of how
the `deq_str` method treats the elements by default is a little inconsistent with this, but strings are
just weird in general, considering they are still technically a location of where the data is.
