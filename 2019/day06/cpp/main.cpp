#include <algorithm>
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
    return std::any_of(childs.begin(), childs.end(), [&n](auto child) {
      return child->name == n;
    });
  }

  bool insert(const std::string& orbitee, const std::string& orbiter) {
    if (orbitee == this->name) {
      if (not this->has_child(orbiter)) {
        childs.emplace(new Object{orbiter});
      }
      return true;
    }
    return std::any_of(childs.begin(), childs.end(), [&orbitee, &orbiter](auto ch) {
      return ch->insert(orbitee, orbiter);
    });
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
    std::int64_t indirects{depth - 1};  // do not count direct to the parent
    if (this->childs.empty())
      return indirects;
    for (auto child : childs) {
      indirects += child->indirect_orbits(depth + 1);
    }
    if (this->name == "COM")
      indirects++;  // the COM has no parent
    return indirects;
  }

  std::vector<std::string> orbital_transfers_to(const std::string& n, std::vector<std::string> path = {}) {
    if (this->childs.empty()) {
      return {};
    }

    path.push_back(this->name);
    if (this->has_child(n))
      return path;
    for (auto child : childs) {
      if (auto ret = child->orbital_transfers_to(n, path); ret != decltype(ret){})
        return ret;
    }

    return {};
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
    // symtax: "XXX)YYY"
    std::string orbitee{line.c_str(), 3};
    std::string orbiter{line.c_str() + 4, 3};
    list.emplace_back(std::move(orbitee), std::move(orbiter));
  }

  std::cout << "Building the space up....\n";
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

  const auto d = com->direct_orbits();
  const auto i = com->indirect_orbits();
  std::cout << "[Stage1] Direct orbits: " << d << '\n'
    << "[Stage1] Indirect orbits: " << i << '\n'
    << "[Stage1] The Directs + The Indirects: " << d + i << std::endl;


  const auto you = com->orbital_transfers_to("YOU");
  const auto santa = com->orbital_transfers_to("SAN");

  auto [mis1, mis2] = std::mismatch(you.begin(), you.end(), santa.begin(), santa.end());

  // do not count YOU, but the object that YOU's orbiting.
  const auto me_to_junction = std::abs(std::distance(mis1, you.end())) - 1;
  const auto santa_to_junction = std::abs(std::distance(mis2, santa.end()));
  // The '1' represents the junction connecting the two paths.
  const auto dis = me_to_junction + santa_to_junction + 1;
  std::cout << "[Stage2] Distance from me to Santa: " << dis << std::endl;

  return 0;
}