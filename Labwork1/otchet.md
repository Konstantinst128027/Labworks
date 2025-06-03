#Plan
- creating a structure for flow control
- creating a function that will take a function for one line and the number of lines.
- it will create as many threads as the processor has, and each thread will perform a function for a specific line. This will all be controlled by the atomic variable.

#Time in different cases
- without parallelism, it will execute the entire process in about 600 milliseconds.
- with parallelism, it will run for about 150-200 milliseconds, which is 3-4 times faster.

#Conclusion
- The code will run much faster with parallelism than without it.
