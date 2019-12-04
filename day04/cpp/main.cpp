#include <cstdlib>

#include <iostream>

constexpr std::size_t first = 158126;
constexpr std::size_t last = 624574;

bool hasDouble(std::size_t number) {
  auto current = number % 10;
  while (number > 0) {
    number = number / 10;
    if (number % 10 == current)
      return true;
    current = number % 10;
  }
  return false;
}

bool hasDecreasing(std::size_t number) {
  auto current = number % 10;
  while (number > 0) {
    number = number / 10;
    if (number % 10 > current) {
      return true;
    }
    current = number % 10;
  }
  return false;
}

bool hasDoubleNotTriple(std::size_t number) {
  auto current = number % 10;
  auto count = 1;
  while (number > 0) {
    number = number / 10;
    if (number % 10 == current) {
      count++;
      continue;
    }
    if (count == 2) {
      return true;
    }
    current = number % 10;
    count = 1;
  }
  return false;
}

std::size_t stage1() {
  std::size_t count{};
  for (std::size_t number{first}; number < last; number++) {
    if (not hasDouble(number))
      continue;
    if (hasDecreasing(number))
      continue;
    count++;
  }
  return count;
}

std::size_t stage2() {
  std::size_t count{};
  for (std::size_t number{first}; number < last; number++) {
    if (not hasDoubleNotTriple(number))
      continue;
    if (hasDecreasing(number))
      continue;
    count++;
  }
  return count;
}

int main() {
  std::cout << "[Stage1] " << stage1() << " passwords meet this criteria.\n";
  std::cout << "[Stage1] " << stage2() << " passwords meet this criteria.\n";

  return 0;
}