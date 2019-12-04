#include <cstdlib>

#include <fstream>
#include <iostream>
#include <vector>

std::size_t stage1(const std::vector<int>& input) {
  std::size_t sum{};
  for (auto el : input) {
    sum += (el / 3) - 2;
  }
  return sum;
}

std::size_t stage2(const std::vector<int>& input) {
  std::size_t sum{};
  auto get_fuel = [](auto mass) {
    return (mass / 3) - 2;
  };
  for (auto el : input) {
    for (;;) {
      el = get_fuel(el);
      if (el <= 0)
        break;
      sum += el;
    }
  }
  return sum;
}

int main() {
  std::ifstream input_file("./input.txt");
  if (not input_file.good()) {
    std::cerr << "Could not open the input file.\n";
    return 1;
  }

  std::vector<int> input;
  int module_mass{};
  while(input_file >> module_mass) {
    input.push_back(module_mass);
  }

  std::cout << "[Stage1] Sum of the fuel requirements: " << stage1(input) << std::endl;
  std::cout << "[Stage2] Sum of the fuel requirements: " << stage2(input) << std::endl;

  return 0;
}
