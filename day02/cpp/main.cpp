#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

int run_stage1(std::vector<int> program) {
  program[1] = 12;
  program[2] = 2;
  std::size_t rip{0};

  for (;;) {
    const auto opcode = program[rip];
    switch (opcode) {
      case 1: {
        const auto value_1 = program[program[rip + 1]];
        const auto value_2 = program[program[rip + 2]];
        const auto result_idx = program[rip + 3];
        program[result_idx] = value_1 + value_2;
        rip += 4;
        break;
      }
      case 2: {
        const auto value_1 = program[program[rip + 1]];
        const auto value_2 = program[program[rip + 2]];
        const auto result_idx = program[rip + 3];
        program[result_idx] = value_1 * value_2;
        rip += 4;
        break;
      }
      case 99:
        return program[0];
      default:
        throw std::runtime_error{"Read unknown opcode."};
    }
  }

  throw std::runtime_error{"Didn't read the '99' opcode."};
}

int main() {
  std::ifstream input_file("./input.txt");
  if (not input_file.good()) {
    std::cerr << "Could not open the input file.\n";
    return 1;
  }

  std::vector<int> program;
  int value{};
  while(input_file >> value) {
    program.push_back(value);
    if (input_file.peek() == ',')
      input_file.get();
  }

  std::cout << "[Stage1] Position 0 value: " << run_stage1(program) << std::endl;

  return 0;
}
