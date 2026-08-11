// usage:
// g++-16 -std=c++26 -O1 repro.cpp && ./a.out
//
#ifdef MAGIC_ENUM_TEST_IMPORT_STD
import std;
#else
#include <optional>
#include <print>
#include <string_view>
#endif

namespace {
constexpr std::optional<int> parse(std::string_view value) {
  while (!value.empty()) {
    const auto pos = value.find('|');
    if (pos == std::string_view::npos || value.substr(0, pos) != "A") {
      return {};
    }
    // XXX std::println("{}", value);
    value.remove_prefix(pos + 1);
  }
  return 1;
}
}  // namespace

int main() { std::println("{}", parse("A|A|A|").has_value()); }
