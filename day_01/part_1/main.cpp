#include "input.hpp"

#include <algorithm>
#include <cstdio>
#include <numeric>
#include <ranges>
#include <string_view>
#include <tuple>
#include <vector>

using namespace std::literals;

static constexpr auto lookup = {
    std::make_tuple("0"sv, 0),     std::make_tuple("1"sv, 1),
    std::make_tuple("2"sv, 2),     std::make_tuple("3"sv, 3),
    std::make_tuple("4"sv, 4),     std::make_tuple("5"sv, 5),
    std::make_tuple("6"sv, 6),     std::make_tuple("7"sv, 7),
    std::make_tuple("8"sv, 8),     std::make_tuple("9"sv, 9),

    std::make_tuple("zero"sv, 0),  std::make_tuple("one"sv, 1),
    std::make_tuple("two"sv, 2),   std::make_tuple("three"sv, 3),
    std::make_tuple("four"sv, 4),  std::make_tuple("five"sv, 5),
    std::make_tuple("six"sv, 6),   std::make_tuple("seven"sv, 7),
    std::make_tuple("eight"sv, 8), std::make_tuple("nine"sv, 9),

};

constexpr int extractCalibrationCode(const std::string_view s) {
  std::vector<int> parsedNumbers(1);

  for (const auto &[startIndex, _] : std::views::enumerate(s)) {
    for (const auto &[m, c] : lookup) {
      const auto substr = s.substr(startIndex, m.size());
      if (substr == m) {
        parsedNumbers.push_back(c);
      }
    }
  }
  return 10 * parsedNumbers[1] + parsedNumbers[parsedNumbers.size() - 1];
}

constexpr int accumulateCalibrationCodes(const std::string_view s) {
  auto calibrationCodes =
      std::views::split(s, "\n"sv) |
      std::views::transform([](const auto substring) {
        return extractCalibrationCode(std::string_view(substring));
      });

  return std::accumulate(calibrationCodes.begin(), calibrationCodes.end(), 0);
}

int main() {
  static constexpr auto result = accumulateCalibrationCodes(inputData);
  std::printf("%d", result);
}
