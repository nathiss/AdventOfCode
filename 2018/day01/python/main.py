#!/usr/bin/python3

def to_number(sign):
  return 1 if sign is '+' else -1

with open('input.txt', 'r') as f:
  input = f.read().splitlines()

input = [to_number(line[0]) * int(line[1:]) for line in input]

def stage2():
  s = set()
  last = 0

  while True:
    for frequency in input:
      last += frequency
      if last in s:
        return last
      s.add(last)

print('[Stage1] Sum of frequencies: %d' % sum(input))
print('[Stage2] Sum of frequencies: %d' % stage2())