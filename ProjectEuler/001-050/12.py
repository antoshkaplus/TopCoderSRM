"""
The sequence of triangle numbers is generated by adding the natural numbers. 
So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:
1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

Let us list the factors of the first seven triangle numbers:
 1: 1
 3: 1,3
 6: 1,2,3,6
10: 1,2,5,10
15: 1,3,5,15
21: 1,3,7,21
28: 1,2,4,7,14,28
We can see that 28 is the first triangle number to have over five divisors.
What is the value of the first triangle number to have over five hundred divisors?
"""
 
from math import sqrt

def add_divisors(d_1,d_2):
  result = d_1.copy()
  for key, value in d_2.iteritems():
    if key in result:
      result[key] += value
    else:
      result[key] = value
  return result

def possibilities(d):
  result = 1
  for i in d.values():
    result *= i+1
  return result       

def find_any_divisor(n):
  result = n
  for i in range(2,int(sqrt(n))+1):
    if n%i == 0:
      result = i
      break
  return result      

bound = 500
  
divisors = []
divisors.extend([{}]) # for '1' and '2'  
i = 1
while True:
  n_1 = i
  n_2 = i+1
  
  k = find_any_divisor(n_2)
  if k == n_2: divisors.append({n_2:1})
  else: divisors.append(add_divisors(divisors[k-1],divisors[n_2/k-1]))
  
  if n_1%2 == 0:
    n_1/=2
  else: n_2/=2
  
  if possibilities(add_divisors(divisors[n_1-1],divisors[n_2-1])) > bound: 
    print n_1*n_2
    break
  
  i += 1









  
  
  
  