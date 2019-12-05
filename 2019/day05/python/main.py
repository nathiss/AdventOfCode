#!/usr/bin/python3

with open('input.txt', 'r') as f:
  input = f.read()

program = [int(ins) for ins in input.split(',')]

POSITION = 0
IMMEDIATE = 1

def decode_opcode(ins):
  modes = []
  opcode = ins % 100
  ins = ins // 100
  modes.append(ins % 10)
  ins = ins // 10
  modes.append(ins % 10)
  ins = ins // 10
  modes.append(ins % 10)

  return [modes, opcode]


def run_program(program, value):
  rip = 0
  while True:
    modes, opcode = decode_opcode(program[rip])
    if opcode == 1:
      value_1 = program[program[rip + 1]] if modes[0] == POSITION else program[rip + 1]
      value_2 = program[program[rip + 2]] if modes[1] == POSITION else program[rip + 2]
      # ignore parameter mode for the output
      program[program[rip + 3]] = value_1 + value_2
      rip += 4
    elif opcode == 2:
      value_1 = program[program[rip + 1]] if modes[0] == POSITION else program[rip + 1]
      value_2 = program[program[rip + 2]] if modes[1] == POSITION else program[rip + 2]
      # ignore parameter mode for the output
      program[program[rip + 3]] = value_1 * value_2
      rip += 4
    elif opcode == 3:
      # ignore parameter output for the output
      program[program[rip + 1]] = value
      rip += 2
    elif opcode == 4:
      value_1 = program[program[rip + 1]] if modes[0] == POSITION else program[rip + 1]
      print(value_1)
      rip += 2
    elif opcode == 5:
      value_1 = program[program[rip + 1]] if modes[0] == POSITION else program[rip + 1]
      value_2 = program[program[rip + 2]] if modes[1] == POSITION else program[rip + 2]
      if value_1 != 0:
        rip = value_2
      else:
        rip += 3
    elif opcode == 6:
      value_1 = program[program[rip + 1]] if modes[0] == POSITION else program[rip + 1]
      value_2 = program[program[rip + 2]] if modes[1] == POSITION else program[rip + 2]
      if value_1 == 0:
        rip = value_2
      else:
        rip += 3
    elif opcode == 7:
      value_1 = program[program[rip + 1]] if modes[0] == POSITION else program[rip + 1]
      value_2 = program[program[rip + 2]] if modes[1] == POSITION else program[rip + 2]
      # ignore parameter output for the output
      program[program[rip + 3]] = 1 if value_1 < value_2 else 0
      rip += 4
    elif opcode == 8:
      value_1 = program[program[rip + 1]] if modes[0] == POSITION else program[rip + 1]
      value_2 = program[program[rip + 2]] if modes[1] == POSITION else program[rip + 2]
      # ignore parameter output for the output
      program[program[rip + 3]] = 1 if value_1 == value_2 else 0
      rip += 4
    elif opcode == 99:
      return
    else:
      raise Exception("Unknown opcode %d." % opcode)


print("=============[Stage1]==============: \n\n")
run_program(program.copy(), 1)
print("\n=============[Stage2]==============: \n\n")
run_program(program.copy(), 5)