#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "intcode.hpp"

int main() {
  std::ifstream input_file{"./input.txt"};
  if (not input_file.good()) {
    std::cerr << "Could not open the input file.";
    return 1;
  }

  std::vector<int> program;
  int value;
  while(input_file >> value) {
    program.push_back(value);
    if (input_file.peek() == ',')
      input_file.get();
  }

  std::vector<int> phase_setting{{0, 1, 2, 3, 4}};
  std::vector<int> results;

  do {
    const auto A = run_program(program, {phase_setting[0], 0});
    const auto B = run_program(program, {phase_setting[1], A.front()});
    const auto C = run_program(program, {phase_setting[2], B.front()});
    const auto D = run_program(program, {phase_setting[3], C.front()});
    const auto E = run_program(program, {phase_setting[4], D.front()});
    results.push_back(E.front());
  } while(std::next_permutation(phase_setting.begin(), phase_setting.end()));

  std::cout << "[Stage1] Highest signal that can be sent to the thrusters: "
    << *std::max_element(results.begin(), results.end()) << '\n';

  return 0;
}