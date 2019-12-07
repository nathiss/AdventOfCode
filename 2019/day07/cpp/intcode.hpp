#pragma once

#include <array>
#include <tuple>
#include <vector>

enum class ParameterMode {
  UNKNOWN,
  POSITION,
  IMMEDIATE,
};

std::tuple<std::array<ParameterMode, 3>, int> parse_opcode(int instruction);

std::vector<int> run_program(std::vector<int> program, std::vector<int> input);