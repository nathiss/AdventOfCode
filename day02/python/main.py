#!/usr/bin/python3

def stage1(program):
    program[1] = 12
    program[2] = 2
    rip = 0

    while True:
        opcode = program[rip]
        if opcode == 1:
            value_1 = program[program[rip + 1]]
            value_2 = program[program[rip + 2]]
            result_idx = program[rip + 3]
            program[result_idx] = value_1 + value_2
            rip += 4
        elif opcode == 2:
            value_1 = program[program[rip + 1]]
            value_2 = program[program[rip + 2]]
            result_idx = program[rip + 3]
            program[result_idx] = value_1 * value_2
            rip += 4
        elif opcode == 99:
            return program[0]
        else:
            raise ValueError("Unknown opcode %d" % opcode)

    raise Exception("Didn't read the '99' opcode.")


with open('input.txt', 'r') as f:
    program = [int(number) for number in f.read().split(',')]


print('[Stage1] Position 0 value: %d' % stage1(program.copy()))
