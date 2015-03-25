"""
Each new term in the Fibonacci sequence is generated by adding the previous two terms. 
By starting with 1 and 2, the first 10 terms will be:
1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
By considering the terms in the Fibonacci sequence whose values do not exceed four million, 
find the sum of the even-valued terms.
"""
"""
n = 4000000
sum = 0
p, p1, p2 = 0, 1, 1
while p2 <= n:
  if not (p2%2): sum += p2
  p = p1 + p2 
  p1 = p2; p2 = p 

print sum  
"""
This uses the idea mentioned above of only calculating every third number. The nth even number is 4*(n-1)th + (n-2)th. 
Assuming the n0 and n1 are 0 and 2 respectively. I do cheat a little by knowing ahead of time when to stop but so did most people. 
a, b = b, a+b

n = 4000000
sum = 0

