import re
from dataclasses import dataclass

from parser import Parser

@dataclass
class MoveInstruction:
    amount: int
    source: int
    destination: int

def parse_instructions(lines: list[str]) -> list[MoveInstruction]:
    instructions = []

    for line in lines:
        raw_instruction = [int(d) for d in re.findall("(\d+)", line)]
        instructions.append(MoveInstruction(raw_instruction[0], raw_instruction[1] - 1, raw_instruction[2] - 1))

    return instructions

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        d = [line.rstrip("\n") for line in f.readlines()]

    separation_idx = d.index("")
    stacks, raw_instructions = d[:separation_idx], d[separation_idx+1:]

    instructions = parse_instructions(raw_instructions)

    parser = Parser(stacks)
    stacks = parser.parse()

    for instruction in instructions:
        for _ in range(instruction.amount):
            element = stacks[instruction.source].pop()
            stacks[instruction.destination].push(element)

    top_elements = [stack.peek() for stack in stacks]

    print(f"Stage 1: {''.join(top_elements)}")

    stacks = parser.parse()

    for instruction in instructions:
        elements = stacks[instruction.source].pop_many(instruction.amount)
        stacks[instruction.destination].push_many(elements)

    top_elements = [stack.peek() for stack in stacks]

    print(f"Stage 2: {''.join(top_elements)}")



