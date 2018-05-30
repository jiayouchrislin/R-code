跟 2D Numpy array的差異
  1 2D Numpy array必須是同一種資料型態，Pandas不用(其實就是data frame)
  2 Pandas的基礎其實就是Numpy

Pandas使用的表格都有column labels跟row labels

如何創data frame
  從dictionary來，key會是column
  import pandas as pd
  brics=pd.DataFrame(dict)

加row name
  brics.index=["BR","RU","IN"]
  
直接讀csv檔
  brics=pd.read_csv("path/to/brics.csv")
  brics=pd.read_csv("path/to/brics.csv",index_col=o) (告知第一個col是row names)
  
如何選取column
  brics["country"]  這時候選出來的資料是series，也就是1D (用type()看)
  brics[["country"]]  這時候選出來的資料是dataframe
如何選取row
  bircs[1:4] 選出2到4行，因為第一個不被包含
  
[]的問題
  在2D Numpy中就直接是 array[rows,columns]
  Pandas 要靠loc(label-based) iloc(integer position-based)
  
如何選取row :loc版
  brics.loc["RU"] 以series方式出現
  brics.loc[["RU"]] 以dataframe方式出現
 
如何選取column :loc版
  brics.loc[:,["country","capital"]]

如何選取row和column :loc版
  brics.loc[["RU","IN","CH"],["country","capital"]]
  
如何選取row :iloc版
  brics.iloc[1] 以series方式出現
  brics.iloc[[1]] 以dataframe方式出現
 
如何選取column :iloc版
  brics.iloc[:,[0,1]]

如何選取row和column :iloc版
  brics.iloc[[1,2,3],[0,1]]  
