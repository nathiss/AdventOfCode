#pragma once

#include <array>
#include <tuple>
#include <vector>
#include <queue>

class Computer {
 public:
  enum class ParameterMode {
    UNKNOWN,
    POSITION,
    IMMEDIATE,
  };

  Computer(std::vector<int> p) : program{p}, original{std::move(p)} {}

  void reset() {
    program = original;
    rip = {};
    input = {};
    output = {};
  }

  Computer& addInput(int value) {
    input.push(value);
    return *this;
  }

  Computer& addOutput(int value) {
    output.push(value);
    return *this;
  }

  int getOutput() {
    if (output.empty()) {
      throw std::runtime_error{"No element in the output stream."};
    }
    const auto value = output.front();
    output.pop();
    return value;
  }

  bool run();

 private:
  std::tuple<std::array<ParameterMode, 3>, int> parse_opcode(int instruction);

  std::vector<int> program;
  decltype(program)::size_type rip{};
  std::queue<int> input;
  std::queue<int> output;

  const std::vector<int> original;
};