#!/usr/bin/python3

with open('input.txt', 'r') as f:
    lines = f.readlines()
    numbers = [int(line) for line in lines]

# Stage 1

for i in range(len(numbers)):
    for j in range(i, len(numbers)):
        if numbers[i] + numbers[j] == 2020:
            print(f'Stage 1 answer: {numbers[i]} * {numbers[j]} = {numbers[i] * numbers[j]}')

# Stage 2

for i in range(len(numbers)):
    for j in range(i, len(numbers)):
        for k in range(j, len(numbers)):
            if numbers[i] + numbers[j] + numbers[k] == 2020:
                print(f'Stage 2 answer: {numbers[i]} * {numbers[j]} * {numbers[k]} = {numbers[i] * numbers[j] * numbers[k]}')
