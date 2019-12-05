#!/usr/bin/python3

from collections import Counter

with open('input.txt', 'r') as f:
  input = f.read().splitlines()

value = {
  2: 0,
  3: 0,
}

for line in input:
  c = Counter(line)
  if any(elm == 2 for elm in c.values()):
    value[2] += 1
  if any(elm == 3 for elm in c.values()):
    value[3] += 1

print('[Stage1] The "checksum" is %d.' % (value[2] * value[3]))


def check(s1, s2):
  diff = 0
  for idx in range(len(s1)):
    if s1[idx] != s2[idx]:
      diff += 1
      pos = idx
  return (diff, pos)

for i in range(len(input)):
  for j in range(len(input)):
    if  i == j:
      continue
    diff, pos = check(input[i], input[j])
    if diff == 1:
      print(input[i][:pos] + input[i][pos+1:])
      from sys import exit
      exit(0)
