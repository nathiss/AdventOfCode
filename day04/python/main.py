#!/usr/bin/python3

first = 158126
last = 624574

count = 0

def hasDouble(i):
  s = str(i)
  for idx in range(len(s) - 1):
    if s[idx] == s[idx+1]:
      return True
  return False


def hasDecreasing(i):
  current = i % 10
  while i > 0:
    i = i // 10
    if i % 10 > current:
      return True
    current = i % 10
  return False


for i in range(first, last):
  if not hasDouble(i):
    continue
  if hasDecreasing(i):
    continue
  count += 1

print('[Stage1] %d passwords meet this criteria.' % count)