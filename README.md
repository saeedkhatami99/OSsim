# Operating System Simulation
A straightforward OS/terminal simulation with fundamental system capabilities (resembling Linux).

# Known Bug
- The `ls` command may lead to a program crash when attempting to list directories within a non-existent path.
`ls` will output blank directories/files if OS executable is not placed and ran in a folder named **OS**

- Currently only `BMP` files are being rendered in terminal, you will need to add `BMP` conversion functions to actually render other
file types.


# This project is part of a college assignment.
Running this code as is isn't recommended. This version is stable and covers essential functionalities,
but it should be further expanded. No external libraries were utilized, which results in some limitations
in the program's features. One notable omission in this codebase is the absence of multithreading capabilities
(easily implementable, see my [Multithread](https://github.com/saeedkhatami/MultiThread)).

# Which programming languages were used?
**C++**, with a bit of **C** thrown into the mix. It might not be fancy, but it gets the job done.

# Program's Capabilities
The program itself can perform a variety of fundamental tasks. When you run it, you can see a list of available functions by typing `help`. All functions are currently stored in the _User_cmd.hpp_ file and organized within a namespace. This structure makes it easy to declare and define new functions. A nifty feature you can add is having the program automatically recognize mathematical expressions and output the answers!
