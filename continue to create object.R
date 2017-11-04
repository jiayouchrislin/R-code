matri=read.csv("")
'ran'<-list()
#set ran is list
ml<-function(x){
        n = ncol(x)
	 for (i in 1:n) {
       ran[[i]]<-data.frame(matrix(1:n, ncol=3, nrow=n))
       ran[[i]]<-sort(marti[,i],decreasing = T)}
}
ml(marti)
