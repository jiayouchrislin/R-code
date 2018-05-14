#R supports parallel computations with the core parallel package. What the doParallel package does is provide a backend while utilizing the core parallel package. The caret package is used for developing and testing machine learning models in R. This package as well as others like plyr support multicore CPU speedups if a parallel backend is registered before the supported instructions are called.

#The train instruction of the caret package has built-in support for parallel backends, but you have to call and set it up. If you don¡¦t register a backend, train will resort to single-core computations. With a registered parallel backend, any caret model training will use multi-cores of the CPU, since by default the trainControl argument is already set as allowParallel=TRUE.

#You can also parallelize other instructions that don¡¦t support it by default, but you have to add additional code. For example, you can parallel process in loops using the foreach instruction after registering a parallel backend. In our case for caret, we don¡¦t have to. Whether you have a Windows or Unix-based (MacOS, Linux) machine, you can download the doParallel package (other similar packages are OS-dependent). Add the following lines in your program and leave everything else the same:


library(doParallel)
cl <- makeCluster(detectCores())
registerDoParallel(cl)
# machine learning code goes in here
stopCluster(cl)


#I have verified that it works while looking at the real-time CPU core utilization. Running a train instruction with method="rf" only used 1 core at 100% while running processes in parallel showed all cores being used ¡V each at 100% with significant speedups. If you do not wish to use all of the CPU cores, you can manually enter the value, such as cl <- makeCluster(4). Also, keep in mind that parallel processing in R will utilize almost all of your system memory while training models and will only free the memory after the instructions have completed.

