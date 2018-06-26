while
格式 (repeating action until condition is met)
  while condition:
    expression

for
格式(for each car in seq, execute expression)
  for var in seq:
    expression
enumerate
  for index, height in numerate(fam):
    print("index"+str(index)+":"+str(height))
  output: index 0:1.73......

loop in dictionary
  for key, value in world.items():
    print(key+"--"+str(value))
 
loop in 2D numpy arrays
  for val in means:
    print(val)   (結果是每一個array)
   for val in np.nditer(means):
    print(val)   (結果是每一個array中的每個元素)

loop in pandas
  brics=pd.read_csv("brics.csv",index_col=0)
  for val in brics:
    print(val)   (這裡印出來的是column名)
  for lab, row in brics.iterrows():
    print(lab)   (lab是row name ex.BU，row是BU這行的全部column內容)
    print(row)
  for lab, row in brics.iterrows():
    print(lab+": "+row["capital"])  (選出想印的column)
  增加column
  for lab, row in brics.iterrows():
    brics.loc[lab,"name_length"]=len(row["country"])  (row name也就是lab叫name_length，row的內容是country的字串長度len)
  = bircs["name_length"]=bircs["country"].apply(len)  (這種比較好懂)
  
    
