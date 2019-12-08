#include <cstdint>
#include <cstdlib>

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

constexpr int kWidth = 25;
constexpr int kHeight = 6;

struct Layer {
  template <typename It>
  It add(It first, It last) {
    for (auto& row : data) {
      for (auto& pixel : row) {
        if (first == last)
          throw std::runtime_error{"Not enought data."};
        pixel = *first - '0';
        first++;
      }
    }
    return first;
  }  // add

  std::size_t count(std::uint8_t value) const {
    std::size_t c{};
    for (const auto& row : data)
      for (const auto& pixel : row)
        if (pixel == value)
          c++;
    return c;
  }

  std::array<std::array<std::uint8_t, kWidth>, kHeight> data;
};

int main() {
  std::ifstream input_file{"./input.txt"};
  if (not input_file.good()) {
    std::cerr << "Cloud not open the input file.\n";
    return 1;
  }

  std::string data;
  std::getline(input_file, data);

  std::vector<Layer> image;
  for (auto begin = data.begin(); begin != data.end();) {
    auto layer = Layer();
    begin = layer.add(begin, data.end());
    image.push_back(std::move(layer));
  }

  std::map<decltype(image)::iterator, std::size_t> zeros;
  for (auto it = image.begin(); it != image.end(); it++) {
    zeros[it] = it->count(0);
  }

  auto lowest = std::min_element(zeros.begin(), zeros.end(),
    [](auto& lhs, auto& rhs) { return lhs.second < rhs.second; });

  std::cout << "[Stage1] Number of `1` digits multiplied by number of `2`: "
    << lowest->first->count(1) * lowest->first->count(2) << std::endl;

  return 0;
}