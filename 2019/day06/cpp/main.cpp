#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <set>
#include <vector>

struct Object {
  using Object_ptr = std::shared_ptr<Object>;

  Object(std::string n) : name{std::move(n)} {}

  std::string name{};
  std::set<Object_ptr> childs;

  // =====================================================================

  bool has_child(const std::string& n) const noexcept {
    for (auto ch : childs) {
      if (ch->name == n)
        return true;
    }
    return false;
  }

  bool insert(const std::string& orbitee, const std::string& orbiter) {
    if (orbitee == this->name) {
      if (not this->has_child(orbiter)) {
        childs.emplace(new Object{orbiter});
      }
      return true;
    }
    for (auto ch : childs) {
      if (ch->insert(orbitee, orbiter))
        return true;
    }
    return false;
  }

  std::size_t direct_orbits() const noexcept {
    std::size_t ret{0};
    for (auto& child : childs) {
      ret += child->direct_orbits();
    }
    ret += this->childs.size();
    return ret;
  }

  std::int64_t indirect_orbits(std::int64_t depth = 0) const noexcept {
    std::int64_t indirects{depth - 1};
    if (this->childs.empty())
      return indirects;
    for (auto child : childs) {
      indirects += child->indirect_orbits(depth + 1);
    }
    if (this->name == "COM")
      indirects++;
    return indirects;
  }
};

int main() {
  std::ifstream input_file{"./input.txt"};
  if (not input_file.good()) {
    std::cerr << "Could not open the input file.\n";
    return 1;
  }

  std::vector<std::pair<std::string, std::string>> list;
  std::string line;
  while (input_file >> line) {
    std::string orbitee{line.c_str(), 3};
    std::string orbiter{line.c_str() + 4, 3};
    list.emplace_back(std::move(orbitee), std::move(orbiter));
  }

  std::cout << "Building the space....\n";
  auto com = std::make_shared<Object>("COM");
  for (auto it = list.begin(); !list.empty();) {
    if (it == list.end())
      it = list.begin();
    if (com->insert(it->first, it->second)) {
      it = list.erase(it);
    } else {
      it++;
    }

  }

  auto d = com->direct_orbits();
  auto i = com->indirect_orbits();
  std::cout << "[Stage1] Direct orbits: " << d << '\n'
    << "[Stage1] Indirect orbits: " << i << '\n'
    << "[Stage1] The Directs + The Indirects: " << d + i << std::endl;

  return 0;
}