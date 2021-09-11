#!/usr/bin/bash

gcc ex2.c -o ex2.out && ./ex2.out & sleep 0.1; pstree | grep ex2

# Output of the above command:
#        |         |-alacritty-+-zsh-+-ex2.out-+-ex2.out-+-ex2.out---ex2.out
#        |         |           |     |         |         `-ex2.out
#        |         |           |     |         |-ex2.out---ex2.out
#        |         |           |     |         `-ex2.out
#
# As we can see, 8 processes are created.
# This can be explained by the fact that each of the children
# of the initial process creates a child process.
# Therefore, amount of processes is equal to 2^n
# Where n is the amount of loops.
# 
# So, if we run the loop 5 times, we get 32 processes. 
