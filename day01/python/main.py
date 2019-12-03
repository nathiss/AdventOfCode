#!/usr/bin/python3

with open('input.txt', 'r') as f:
    input = [int(mass) for mass in f.read().splitlines()]

sum = sum([(mass // 3) - 2 for mass in input])

print('Sum of the fuel requirements: %d' % sum)
