#!/usr/bin/python3

first = 158126
last = 624574

def hasDouble(i):
  s = str(i)
  for idx in range(len(s) - 1):
    if s[idx] == s[idx+1]:
      return True
  return False


def hasDoubleNotTriple(i):
  s = str(i)
  current = s[0]
  c = [[current, 1]]
  for idx in range(1, len(s)):
    if s[idx] == current:
      c[-1][1] += 1
    else:
      c.append([s[idx], 1])
      current = s[idx]

  for set in c:
    if set[1] == 2:
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


def stage1():
  count = 0
  for i in range(first, last):
    if not hasDouble(i):
      continue
    if hasDecreasing(i):
      continue
    count += 1
  return count


def stage2():
  count = 0
  for i in range(first, last):
    if not hasDoubleNotTriple(i):
      continue
    if hasDecreasing(i):
      continue
    count += 1
  return count


print('[Stage1] %d passwords meet this criteria.' % stage1())
print('[Stage2] %d passwords meet this criteria.' % stage2())