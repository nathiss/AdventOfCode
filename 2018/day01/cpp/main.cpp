#include <cstdint>

#include <stdexcept>
#include <numeric>
#include <iostream>
#include <charconv>
#include <fstream>
#include <string>
#include <set>
#include <vector>

std::int64_t stage1(const std::vector<int>& changes) {
  return std::accumulate(changes.begin(), changes.end(), 0);
}

std::int64_t stage2(const std::vector<int>& changes) {
  std::set<std::int64_t> frequencies;
  std::int64_t last{};
  for (;;) {
    for (auto change : changes) {
      last += change;
      if (auto it = frequencies.find(last); it != frequencies.end()) {
        return last;
      }
      frequencies.insert(last);
    }
  }
  throw std::runtime_error{"No chance that this line of code would be ever executed."};
}

int main() {
  std::ifstream input_file{"./input.txt"};
  if (not input_file.good()) {
    std::cerr << "Could not open the input file.\n";
    return 1;
  }

  std::vector<int> changes;
  std::string line;
  while (std::getline(input_file, line)) {
    int sign = line[0] == '+' ? 1 : -1;
    int value;
    if (auto [p, ec] = std::from_chars(line.data() + 1, line.data() + line.size(), value);
      ec != std::errc{}) {
      std::cerr << std::make_error_condition(ec).message() << std::endl;
      return 2;
    }
    changes.push_back(sign * value);
  }

  std::cout << "[Stage1] Sum of frequencies: " << stage1(changes) << std::endl;
  std::cout << "[Stage2] First double frequency: " << stage2(changes) << std::endl;

  return 0;
}
