#!/usr/bin/python3

with open('input.txt', 'r') as f:
  wire1, wire2 = f.read().splitlines()
wire1, wire2 = [x.split(',') for x in [wire1, wire2]]

dx = {
  'U': 0,
  'R': 1,
  'D': 0,
  'L': -1,
}
dy = {
  'U': 1,
  'R': 0,
  'D': -1,
  'L': 0,
}
def parse_wire(wire):
  res = {}
  x = 0
  y = 0
  length = 0
  for turn in wire:
    d = turn[0]
    n = int(turn[1:])
    for i in range(n):
      x += dx[d]
      y += dy[d]
      length += 1
      if (x, y) not in res:
        res[(x, y)] = length

  return res


wire1 = parse_wire(wire1)
wire2 = parse_wire(wire2)
in_both = set(wire1.keys()) & set(wire2.keys())

print("[Stage1] Closest intersection: %d" % min([abs(key[0]) + abs(key[1]) for key in in_both]))
print("[Stage2] Closest intersection: %d" % min([wire1[key] + wire2[key] for key in in_both]))