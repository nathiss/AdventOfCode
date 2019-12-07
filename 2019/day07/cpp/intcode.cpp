#include "intcode.hpp"

#include <algorithm>
#include <sstream>

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

std::vector<int> run_program(std::vector<int> program, std::vector<int> input) {
  std::vector<int> output;
  std::size_t rip{};
  for (;;) {
    const auto [modes, opcode] = parse_opcode(program[rip]);
    switch (opcode) {
      // add
      case 1: {
        const int value_1 = modes[0] == ParameterMode::POSITION ?
          program[program[rip + 1]] : program[rip + 1];
        const int value_2 = modes[1] == ParameterMode::POSITION ?
            program[program[rip + 2]] : program[rip + 2];
        // ignore parameter mode for the output
        program[program[rip + 3]] = value_1 + value_2;
        rip += 4;
        break;
      }

      // multiply
      case 2: {
        const int value_1 = modes[0] == ParameterMode::POSITION ?
          program[program[rip + 1]] : program[rip + 1];
        const int value_2 = modes[1] == ParameterMode::POSITION ?
            program[program[rip + 2]] : program[rip + 2];
        // ignore parameter mode for the output
        program[program[rip + 3]] = value_1 * value_2;
        rip += 4;
        break;
      }

      // input
      case 3: {
        // ignore the parameter mode for output address
        if (input.empty()) {
          throw std::runtime_error{"Not enough input values."};
        }
        program[program[rip + 1]] = input.front();
        input.erase(input.begin());
        rip += 2;
        break;
      }

      // output
      case 4:
        if (modes[0] == ParameterMode::POSITION) {
          output.push_back(program[program[rip + 1]]);
        }
        if (modes[0] == ParameterMode::IMMEDIATE) {
          output.push_back(program[rip + 1]);
        }
        rip += 2;
        break;

      // jump-if-true
      case 5: {
        const int value_1 = modes[0] == ParameterMode::POSITION ?
          program[program[rip + 1]] : program[rip + 1];
        const int value_2 = modes[1] == ParameterMode::POSITION ?
          program[program[rip + 2]] : program[rip + 2];
        if (value_1 != 0) {
          rip = value_2;
        } else {
          rip += 3;
        }
        break;
      }

      // jump-if-false
      case 6: {
        const int value_1 = modes[0] == ParameterMode::POSITION ?
          program[program[rip + 1]] : program[rip + 1];
        const int value_2 = modes[1] == ParameterMode::POSITION ?
          program[program[rip + 2]] : program[rip + 2];
        if (value_1 == 0) {
          rip = value_2;
        } else {
          rip += 3;
        }
        break;
      }

      // less than
      case 7: {
        const int value_1 = modes[0] == ParameterMode::POSITION ?
          program[program[rip + 1]] : program[rip + 1];
        const int value_2 = modes[1] == ParameterMode::POSITION ?
          program[program[rip + 2]] : program[rip + 2];
        // ignore parameter mode for the output parameter.
        program[program[rip + 3]] = value_1 < value_2 ? 1 : 0;
        rip += 4;
        break;
      }

      // equals
      case 8: {
        const int value_1 = modes[0] == ParameterMode::POSITION ?
          program[program[rip + 1]] : program[rip + 1];
        const int value_2 = modes[1] == ParameterMode::POSITION ?
          program[program[rip + 2]] : program[rip + 2];
        // ignore parameter mode for the output parameter.
        program[program[rip + 3]] = value_1 == value_2 ? 1 : 0;
        rip += 4;
        break;
      }

      // return
      case 99:
        return output;

      default: {
        std::stringstream ss{"Readm unknown opcode: "};
        ss << opcode << '.';
        throw std::runtime_error{ss.str()};
      }
    }
  }
}