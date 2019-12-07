#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "intcode.hpp"

template <typename T>
auto get_amplifiers(T&& program) {
  return std::make_tuple(
    Computer(std::forward<T>(program)),
    Computer(std::forward<T>(program)),
    Computer(std::forward<T>(program)),
    Computer(std::forward<T>(program)),
    Computer(std::forward<T>(program))
  );
}

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
    auto [A, B, C, D, E] = get_amplifiers(program);
    A.addInput(phase_setting[0]).addInput(0).run();
    B.addInput(phase_setting[1]).addInput(A.getOutput()).run();
    C.addInput(phase_setting[2]).addInput(B.getOutput()).run();
    D.addInput(phase_setting[3]).addInput(C.getOutput()).run();
    E.addInput(phase_setting[4]).addInput(D.getOutput()).run();
    results.push_back(E.getOutput());
  } while(std::next_permutation(phase_setting.begin(), phase_setting.end()));

  std::cout << "[Stage1] Highest signal that can be sent to the thrusters: "
    << *std::max_element(results.begin(), results.end()) << '\n';

  // ===================================================================

  phase_setting = {{5, 6, 7, 8, 9}};
  results.clear();

  do {
    auto [A, B, C, D, E] = get_amplifiers(program);
    A.addInput(phase_setting[0]);
    B.addInput(phase_setting[1]);
    C.addInput(phase_setting[2]);
    D.addInput(phase_setting[3]);
    E.addInput(phase_setting[4]).addOutput(0);  // initial input value for A
    for (;;) {
      A.addInput(E.getOutput()).run();
      B.addInput(A.getOutput()).run();
      C.addInput(B.getOutput()).run();
      D.addInput(C.getOutput()).run();
      E.addInput(D.getOutput());
      if (E.run()) {
        results.push_back(E.getOutput());
        break;
      }
    }
  } while(std::next_permutation(phase_setting.begin(), phase_setting.end()));

  std::cout << "[Stage2] Highest signal that can be sent to the thrusters: "
    << *std::max_element(results.begin(), results.end()) << '\n';

  return 0;
}