#!/usr/bin/bash

for i in $(seq 10); do ./ex1.out; done

# The parent's PID increments by 2 each time I call the program,
# because during it's execution 2 processes are started.
# In my case, the parent process fully finishes,
# then the child process starts.
