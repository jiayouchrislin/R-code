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
