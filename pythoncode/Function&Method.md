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

Function內變數的尋找順序:local(inner->outer)->golbal->built-in
Function外的變數要能夠在Function內被改變: 變數前面+golbal
def square():
  golbal new_val
  new_val=new_val**2
  return new_val
square(10) 結果會是100
new_val結果也會是100

Nested Function

def raise_val(n):
  def inner(x):
    raised=x**n
    return raised
  return inner
square=raise_val(2)
cube=raise_val(3)
print(square(2),cube(4)) 結果會是4 64

Nonlocal 可以改變enclosing scope中的數值 
def outer()
  n=1
  def inner():
    nonlocal n
    n=2
    print(n)
  inner()
  print(n)  
outer()  結果跑出2 2

Default argument
def power(number, pow=1):
  new_value=number**pow
  return new_value
power(9,2)  結果是81
power(9,1)  結果是9
power(9)    結果是9

flexible arguments:*args    
def add_all(*args):
  sum_all=0
  for num in args:
    sum_all+=num
  return sum_all
  
有用於dictionary
flexible arguments:**kwargs
def print_all(**kwargs):
  for key, value in kwargs.item():
    print(key+": "+value)


