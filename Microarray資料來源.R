Microarray資料來源

相對於Next Generation Sequence 資料動輒幾十gb，這次我們選擇用microarray的資料練習，
首先我們分別從GEO、EMBL和TCGA裡找尋用affymetrix 測expression的實驗資料，畢竟affymetrix是microarray年代裡最可靠的平台，另外我們也希望使用的chip 是一樣的，避免到probe annotation的問題，最後我們找到三組可行的資料來練習分析，都為使用Affymetrix Human Exon 1.0 ST array(GPL5175)：

第一組：口腔癌 GSE25099

這組資料來自於台灣長庚醫院頭頸癌團隊的研究論文，此組包含有79個樣本，其中22個為正常組織

第二組:胃癌 GSE33335 GSE13195

這組為來自中國大陸的研究團隊，其基因表現資料來自於27個paired胃癌組織樣本

第三組：大腸直腸癌 GSE29638

這組來自於挪威的研究團隊，主要有207組來自於挪威的大腸直腸癌病人檢體，其臨床分期有第一期到第五期，實驗主要是用來找尋第二期大腸直腸癌是否有可以用來預測預後的基因表現biomarker

匯入R並且簡易分析

參考此篇來做匯入

先安裝GEOquery R bioconductor package

source(“http://bioconductor.org/biocLite.R")
biocLite(“GEOquery“)

library(GEOquery)
接下來使用GEOquery來下載我們找到的檔案，先嘗試GSE25099

gse <- getGEO(“GSE25099“, GSEMatrix = TRUE)

screenshot.png
接下來我們只要這資料裡頭的gene expression matrix，於是我們把exprs subsetting出來，因為這是s4 class，先用＠在用$，交替尋出我們要的matrix

screenshot.png
接下來快速使用R內建函數來做簡單分析，可參考這篇，使用prcomp()

screenshot.pngscreenshot.png
 Rplot Rplot023
