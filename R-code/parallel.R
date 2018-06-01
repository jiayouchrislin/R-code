眾所周知，在大數據時代R語言有兩個弱項，其中一個就是只能使用單線程計算。但是在2.14版本之後，R就內置了parallel包，強化了R的並行計算能力。 parallel包實際上整合了之前已經比較成熟的snow包和multicore包。前者已經在之前的文章中介紹過了，而後者無法在windows下運行，所以也就先不管了。 parallel包可以很容易的在計算集群上實施並行計算，在多個CPU核心的單機上，也能發揮並行計算的功能。我們今天就來探索一下parallel包在多核心單機上的使用。

parallel包的思路和lapply函數很相似，都是將輸入數據分割、計算、整合結果。只不過並行計算是用到了不同的cpu來運算。下面的例子是解決歐拉問題的第14個問題。

# 並行計算euler14問題
# 自定義函數以返回原始數值和步數
func <- function(x) {
????n = 1
????raw <- x
????while (x > 1) {
????????x <- ifelse(x%%2==0,x/2,3*x+1)
????????n = n + 1
????}
????return(c(raw,n))
}
?
library(parallel)
# 用system.time來返回計算所需時間
system.time({
????x <- 1:1e6
????cl <- makeCluster(4) # 初始化四核心集群
????results <- parLapply(cl,x,func) # lapply的並行版本
????res.df <- do.call('rbind',results) # 整合結果
????stopCluster(cl) # 關閉集群
})
# 找到最大的步數對應的數字
res.df[which.max(res.df[,2]),1]
?
上例中關鍵的函數就是parLapply，其中三個參數分別是集群對象、輸入參數和運算函數名。我們最後算出的結果是837799。

foreach包是revolutionanalytics公司貢獻給R開源社區的一個包。它能使R中的並行計算更為方便。與sapply函數類似，foreach函數中的第一個參數是輸入參數，%do%後面的對象表示運算函數，而.combine則表示運算結果的整合方式。下面的例子即是用foreach來完成前面的同一個任務。如果要啟用並行，則需要加載doParallel包，並將%do%改為%dopar%。這樣一行代碼就能方便的完成並行計算了。

library(foreach)
# 非並行計算方式，類似於sapply函數的功能
x <- foreach(x=1:1000,.combine='rbind') %do% func(x)
?
# 啟用parallel作為foreach並行計算的後端
library(doParallel)
cl <- makeCluster(4)
registerDoParallel(cl)
# 並行計算方式
x <- foreach(x=1:1000,.combine='rbind') %dopar% func(x)
stopCluster(cl)

下面的例子是用foreach函數來進行隨機森林的並行計算。我們一共要生成十萬個樹來組合成一個隨機森林，每個核心負責生成兩萬五千個樹。最後用combine進行組合。

# 隨機森林的並行計算
library(randomForest)
?cl <- makeCluster(4)
?registerDoParallel(cl)
?rf <- foreach(ntree=rep(25000, 4),
??????????????????.combine=combine,
??????????????????.packages='randomForest') %dopar%
??????????randomForest(Species~., data=iris, ntree=ntree)
stopCluster(cl)

並行不僅可以在建模時進行，也可以在數據整理階段進行。之前我們提到過的plyr包也可以進行並行，前提是加載了foreach包，並且參數.parallel設置為TURE。當然不是所有的任務都能並行計算，而且並行計算前你需要改寫你的代碼。

參考資料：
http://stat.ethz.ch/R-manual/R-devel/library/parallel/doc/parallel.pdf
http://cran.r-project.org/web/packages/foreach/vignettes/foreach.pdf
http://cran.r-project.org/web/packages/doParallel/vignettes/gettingstartedParallel.pdf