#!/usr/bin/python3

with open('input.txt', 'r') as f:
    input = [int(mass) for mass in f.read().splitlines()]


stage1_sum = sum([(mass // 3) - 2 for mass in input], 0)
print('[Stage1] Sum of the fuel requirements: %d' % stage1_sum)


stage2_sum = 0
for fuel in input:
    while True:
        fuel = (fuel // 3) - 2
        if fuel <- 0:
            break
        stage2_sum += fuel

print('[Stage2] Sum of the fuel requirements: %d' % stage2_sum)
