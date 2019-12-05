#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <tuple>
#include <stdexcept>

enum class ParameterMode {
  UNKNOWN,
  POSITION,
  IMMEDIATE,
};

std::tuple<std::array<ParameterMode, 3>, int> parse_opcode(int instruction) {
  const auto opcode = instruction % 100;
  std::array<ParameterMode, 3> modes{};

  instruction /= 100;
  modes[0] = instruction % 10 == 0 ? ParameterMode::POSITION : ParameterMode::IMMEDIATE;
  instruction /= 10;
  modes[1] = instruction % 10 == 0 ? ParameterMode::POSITION : ParameterMode::IMMEDIATE;
  instruction /= 10;
  modes[2] = instruction % 10 == 0 ? ParameterMode::POSITION : ParameterMode::IMMEDIATE;

  if (std::any_of(modes.begin(), modes.end(),
    [](auto mode){ return mode == ParameterMode::UNKNOWN; })) {
    throw std::runtime_error{"Unknown parameter mode."};
  }

  return std::make_tuple(modes, opcode);
}

void run_program(std::vector<int> program) {
  std::size_t rip{};
  for (;;) {
    const auto [modes, opcode] = parse_opcode(program[rip]);
    switch (opcode) {
      case 1: {
        const auto value_1 = modes[0] == ParameterMode::POSITION ?
          program[program[rip + 1]] : program[rip + 1];
        const auto value_2 = modes[1] == ParameterMode::POSITION ?
            program[program[rip + 2]] : program[rip + 2];
        // ignore parameters mode for the output
        program[program[rip + 3]] = value_1 + value_2;
        rip += 4;
        break;
      }

      case 2: {
        const auto value_1 = modes[0] == ParameterMode::POSITION ?
          program[program[rip + 1]] : program[rip + 1];
        const auto value_2 = modes[1] == ParameterMode::POSITION ?
            program[program[rip + 2]] : program[rip + 2];
        // ignore parameters mode for the output
        program[program[rip + 3]] = value_1 * value_2;
        rip += 4;
        break;
      }


      case 3: {
        int value;
        std::cin >> value;
        // ignore the parameters mode for output address
        program[program[rip + 1]] = value;
        rip += 2;
        break;
      }

      case 4:
        if (modes[0] == ParameterMode::POSITION) {
          std::cout << program[program[rip + 1]] << std::endl;
        }
        if (modes[0] == ParameterMode::IMMEDIATE) {
          std::cout << program[rip + 1] << std::endl;
        }
        rip += 2;
        break;

      case 99:
        return;

      default:
        throw std::runtime_error{"Read unknown opcode."};
    }
  }
}

int main() {
  std::ifstream input_file{"./input.txt"};
  if (not input_file.good()) {
    std::cerr << "Could not open the input file.\n";
    return 1;
  }

  std::vector<int> program;
  int value;
  while(input_file >> value) {
    program.push_back(value);
    if (input_file.peek() == ',')
      input_file.get();
  }

  run_program(program);

  return 0;
}