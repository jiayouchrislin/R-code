Function&Method差異
  Method受object屬性影響，Function沒有
  method用法可以是 fam.append()  functiob則須為:max(fam)


Docstring:讓人家知道這個function在幹嘛用
"""......"""

沒parameter Function
def square():
  new_value=4**2
  print(new_value)

有
def square(value):
  new_value=value**2
  print(new_value)
square(4)

多個
def square(value1,value2):
  new_value=value1**value2
  print(new_value)

要傳回數值，以儲存
def square():
  new_value=value**2
  return new_value
num=square(4)
print(num)

傳回多個數值
def raise_both(value1,value2):
  new_value1=value1**value2
  new_value2=value2**value1
  new_tuple=(new_value1,new_value2)
  return new_tuple



