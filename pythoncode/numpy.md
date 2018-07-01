Numpy array 跟 list差別: list無法直接做數學運算`,Numpy array可。
  也就是說list的+是+元素，Numpy array是做加減
Numpy array　注意事項
  １　注意資料類型只能有一種，如果大於一種，會被轉換成其中一種　
  
Numpy array索引(跟list一樣)
  np_height=np.array(height)
  np_height[1]   會跳出第二個值如165
  np_height[100:111] 包含100不包含111
  
Numpy array真假值
  np_height>180  結果是array([True,False,False,False],dtype=bool)
  np_height(np_height>180)  跳出符合的項目值，如186
  或者也可以
  high=np_height>180 
  np_heigh[high] 

Numpy array的type
  type(np_height)
  numpy.ndarray  (就是n-dimentional array的意思)
  
2.D Numpy array
  np_2d=np.array([[1,2,3,2,1],
                  [4,5,6,5,4]])
  np_2d.shape  結果跑出(2.5)，代表2 row 5 column
  一樣只能是單一資料型態，例如同時有string跟數字，會被全部轉換成string

2.D Numpy array 索引
  np_2d[0] 跑出第一行資訊:array([1,2,3,2,1])
  np_2d[0][2] 跑出第一行第三欄數值:3
  np_2d[0,2] 跟上面一樣
  np_2d[:,1:3] 跑出array([[2,3],
                          [5,6]])
                          
取平均
np.mean(np_city[:,0])  結果為1.74
取中位數
np.median(np_city[:,0]) 結果為1.75
取相關係數
np.corrcoef(np_city[:,0],np_city[:,1])
取標準差
np.std(np_city[:,0])
產生資料
np.round(np.random.nomal(1.75,20,5000),2) (1.75,0.20,5000)分別為散佈的平均、標準差、產生的數目
變成2.D array
np_city=np.column.stack((height,weight))
看是否一樣
(a==b).all() a b完全一樣的話傳回True否則為False
(a==b).any() a b只要有一個一樣的話傳回True否則為False
跟上面比較
np.all: 如果所有的值都是真或者非零则返回 True, 否则返回 False.
np.any: ndarray 中有任何真值或者非零值则返回 True.
