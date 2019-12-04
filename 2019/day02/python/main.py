#!/usr/bin/python3

def run_program(program):
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

def stage1(program):
  program[1] = 12
  program[2] = 2
  return run_program(program)

def stage2(program):
  for noun in range(0, 100):
    for verb in range(0, 100):
      p = program.copy()
      p[1] = noun
      p[2] = verb
      try:
        result = run_program(p)
        if result == 19690720:
          return 100 * noun + verb
      except:
        continue
  raise Exception("No combination produced '19690720'.")



with open('input.txt', 'r') as f:
  program = [int(number) for number in f.read().split(',')]


print('[Stage1] Position 0 value: %d' % stage1(program.copy()))
print('[Stage2] Position 0 value: %d' % stage2(program.copy()))
