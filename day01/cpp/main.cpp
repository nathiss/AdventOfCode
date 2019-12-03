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

  auto get_fuel = [](auto mass) {
    return (mass / 3) - 2;
  };

  while (input >> module_mass) {

    int fuel = module_mass;
    for (;;) {
      fuel = get_fuel(fuel);
      if (fuel <= 0)
        break;
      sum += fuel;
    }

  }

  std::cout << "Sum of the fuel requirements: " << sum << std::endl;
  return 0;
}
