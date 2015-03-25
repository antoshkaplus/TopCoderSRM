"""
The Fibonacci sequence is defined by the recurrence relation:

F_{n} = F_{n1} + F_{n2}, where F_{1} = 1 and F_{2} = 1.
Hence the first 12 terms will be:

F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F10 = 55
F11 = 89
F12 = 144
The 12th term, F12, is the first term to contain three digits.

What is the first term in the Fibonacci sequence to contain 1000 digits?
"""

bound = 10**999
f1, f2, i = 1, 2, 3
while f2 < bound: f1, f2, i = f2, f1+f2, i+1
print i
  




