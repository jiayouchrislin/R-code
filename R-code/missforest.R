install.packages("missForest", dependencies = TRUE)
library(missForest)
a.namiss<-prodNA(a,0.0)
summary(a.namiss)
a.imp <- missForest(a,maxiter=10,ntree=900,verbose = TRUE,
parallelize = c('no', 'variables', 'forests'))
err.imp <- mixError(a.imp$ximp, a.namiss, a)
 