#include <cstdlib>

#include <fstream>
#include <iostream>

int main() {
  std::ifstream input("./input.txt");
  if (not input.good()) {
    std::cerr << "Could not open the input file.\n";
    return 1;
  }

  std::size_t sum{};
  int module_mass{};

  while (input >> module_mass) {
    sum += (module_mass / 3) - 2;
  }

  std::cout << "Sum of the fuel requirements: " << sum << std::endl;
  return 0;
}
