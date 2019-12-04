#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <charconv>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <algorithm>


using Wire = std::map<std::pair<std::int64_t, std::int64_t>, std::size_t>;

std::vector<std::string> split(const std::string& s, char delimeter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream{s};
  while (std::getline(tokenStream, token, delimeter)) {
    tokens.push_back(token);
  }

  return tokens;
}

Wire parse_wire(const std::vector<std::string>& path) {
  static std::map<char, std::pair<std::int64_t, std::int64_t>> directions{
    {'U', {0, 1}},
    {'R', {1, 0}},
    {'D', {0, -1}},
    {'L', {-1, 0}},
  };

  Wire wire;
  std::size_t length{};
  std::int64_t x{}, y{};
  for (const auto& move : path) {
    const auto d = move[0];
    std::size_t value;
    if (auto [p, ec] = std::from_chars(move.data() + 1, move.data() + move.size(), value);
      ec != std::errc{}) {
      std::cerr << "Error: " << std::make_error_condition(ec).message() << std::endl;
    }

    for (std::size_t i{}; i < value; i++) {
      length++;
      x += directions[d].first;
      y += directions[d].second;
      if (auto it = wire.find({x, y}); it == wire.end()) {
        wire[{x, y}] = length;
      }
    }
  }

  return wire;
}

std::vector<std::pair<std::int64_t, std::int64_t>> getIntersections(const Wire& w1, const Wire& w2) {
  std::vector<std::pair<std::int64_t, std::int64_t>> intersections;

  for (const auto& [key, _] : w1) {
    if (auto it = w2.find(key); it != w2.end()) {
      intersections.push_back(key);
    }
  }

  return intersections;
}

template <typename T>
std::size_t stage1(const T& intersections) {
  std::vector<std::size_t> distances;
  for (const auto& intersection : intersections) {
    distances.push_back(std::abs(intersection.first) + std::abs(intersection.second));
  }
  return *std::min_element(distances.begin(), distances.end());
}

template <typename T>
std::size_t stage2(const Wire& w1, const Wire& w2, const T& intersections) {
  std::vector<std::size_t> distances;
  for (const auto& intersection : intersections) {
    distances.push_back(w1.at(intersection) + w2.at(intersection));
  }
  return *std::min_element(distances.begin(), distances.end());
}

int main() {
  std::ifstream input_file("./input.txt");

  std::string line1, line2;
  std::getline(input_file, line1);
  std::getline(input_file, line2);

  auto wire1 = parse_wire(split(line1, ','));
  auto wire2 = parse_wire(split(line2, ','));

  auto intersections = getIntersections(wire1, wire2);

  std::cout << "[Stage1] Distance to the closest intersection: "
    << stage1(intersections) << std::endl;

  std::cout << "[Stage2] Sum of wires' distances to the closest intersection: "
    << stage2(wire1, wire2, intersections) << std::endl;


  return 0;
}
