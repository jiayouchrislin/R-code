parallel<-function (){
	require(doParallel)
	cl<-makeCluster(detectCores())
	registerDoParallel(cl)
	
}
