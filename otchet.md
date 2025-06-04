#Plan
- creating a structure for flow control
- creating a function that will take a function for one line and the number of lines.
- it will create as many threads as the processor has, and each thread will perform a function for a specific line. This will all be controlled by the atomic variable.

#Example of program execution

|Process            | without paralellism | with paralellism |    
|:---------------:|:---------------------|:------------------|
| Rotate90Clockwise |      65     |      54       |                
| Rotate90CoClockwise |     51     |      34       |           
| GaussianBlur |      573        |      159      |           
| All |      689      |        247        |    
            
#Time in different cases
- after measuring 10 times, I calculated the average running time without and with parallelism. The table shows the results.

|Process            | without paralellism | with paralellism |    
|:---------------:|:---------------------|:------------------|
| Rotate90Clockwise |      57     |      52       |                
| Rotate90CoClockwise |     54     |      41       |           
| GaussianBlur |      534        |      159      |           
| All |      689      |        174        | 

#Experiment
- with a single thread

|Process            | without paralellism | with paralellism |    
|:---------------:|:---------------------|:------------------|
| Rotate90Clockwise |      53     |      77       |                
| Rotate90CoClockwise |     55     |      49       |           
| GaussianBlur |      571        |      438      |           
| All |      679      |        564        |

- with two thread

|Process            | without paralellism | with paralellism |    
|:---------------:|:---------------------|:------------------|
| Rotate90Clockwise |      83     |      70       |                
| Rotate90CoClockwise |     77     |      59       |           
| GaussianBlur |      489        |      354      |           
| All |      649      |        483        |

- with three thread

|Process            | without paralellism | with paralellism |    
|:---------------:|:---------------------|:------------------|
| Rotate90Clockwise |      83     |      53       |                
| Rotate90CoClockwise |     55     |      51       |           
| GaussianBlur |      469        |      205      |           
| All |      607      |        309        |

- with four thread (like a sd::thread::hartdware_concurrency())

|Process            | without paralellism | with paralellism |    
|:---------------:|:---------------------|:------------------|
| Rotate90Clockwise |      53     |      49       |                
| Rotate90CoClockwise |     92     |      56       |           
| GaussianBlur |      555        |      170      |           
| All |      696      |        279        |

#Conclusion
- The code will run much faster with parallelism than without it.
