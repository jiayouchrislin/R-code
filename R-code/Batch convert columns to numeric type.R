#Batch convert columns to numeric type
#You can use sapply for this:

dat <- sapply( dat, as.numeric )
#If not every column needs converting:

library( taRifx )
dat <- japply( dat, which(sapply(dat, class)=="character"), as.numeric )