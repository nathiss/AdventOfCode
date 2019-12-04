#!/usr/bin/python3

first = 158126
last = 624574

def hasDouble(i):
  current = i % 10
  while i > 0:
    i = i // 10
    if i % 10 == current:
      return True
    current = i % 10
  return False


def hasDoubleNotTriple(i):
  current = i % 10
  count = 1
  while i > 0:
    i = i // 10
    if i % 10 == current:
      count += 1
      continue
    if count == 2:
      return True
    current = i % 10
    count = 1
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