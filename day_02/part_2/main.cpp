
#include "input.hpp"
#include <algorithm>
#include <bits/ranges_algo.h>
#include <cstddef>
#include <functional>
#include <numeric>
#include <ranges>
#include <string_view>

struct BagData {
  std::size_t red;
  std::size_t green;
  std::size_t blue;

  constexpr auto operator+(const BagData rhs) const {
    return BagData{.red = red + rhs.red,
                   .green = green + rhs.green,
                   .blue = blue + rhs.blue};
  }

  constexpr auto operator<=(const BagData rhs) const {
    return red <= rhs.red && blue <= rhs.blue && green <= rhs.green;
  }
};

constexpr auto bagMax(const BagData rhs, const BagData lhs) {
  return BagData{.red = std::max(lhs.red, rhs.red),
                 .green = std::max(lhs.green, rhs.green),
                 .blue = std::max(lhs.blue, rhs.blue)};
}

constexpr auto bagMin(const BagData rhs, const BagData lhs) {
  return BagData{.red = std::min(lhs.red, rhs.red),
                 .green = std::min(lhs.green, rhs.green),
                 .blue = std::min(lhs.blue, rhs.blue)};
}

struct GameData {
  std::size_t index;
  BagData bag;
};

namespace constexprutils {
constexpr unsigned int atoi_digit(const char c) { return c - '0'; }

constexpr unsigned int atoi(const std::string_view line) {
  unsigned int accumulator = 0;
  for (std::size_t i = 0; i < line.size(); i++) {
    accumulator *= 10;
    accumulator += atoi_digit(line[i]);
  }
  return accumulator;
}
}; // namespace constexprutils

constexpr auto parseColorCount(const std::string_view color,
                               const std::string_view line) {
  using namespace std::literals;
  const auto colorDelimiterIndex = line.find(color);

  if (colorDelimiterIndex == std::string_view::npos) {
    return 0u;
  }

  const auto countEndIndex = colorDelimiterIndex - 1;

  const auto countBeginIndex = line.rfind(" ", countEndIndex - 1) + 1;

  const auto countStr =
      line.substr(countBeginIndex, countEndIndex - countBeginIndex);
  return constexprutils::atoi(countStr);
}

constexpr auto parseBag(const std::string_view bagLine) -> BagData {
  using namespace std::literals;
  const auto redCount = parseColorCount("red"sv, bagLine);
  const auto blueCount = parseColorCount("blue"sv, bagLine);
  const auto greenCount = parseColorCount("green"sv, bagLine);

  return BagData{.red = redCount, .green = greenCount, .blue = blueCount};
}

constexpr auto parseBags(const std::string_view bagLine) -> BagData {
  using namespace std::literals;
  auto bags = std::views::split(bagLine, ";"sv) |
              std::views::transform(
                  [](const auto input) { return std::string_view(input); }) |
              std::views::transform(parseBag);

  auto max_bag = std::reduce(bags.begin(), bags.end(), BagData{}, bagMax);
  return max_bag;
}

constexpr auto parseGame(const std::string_view gameLine) -> GameData {

  static constexpr std::size_t GAME_HEADER_BOILERPLATE_LENGTH =
      std::string_view("Game ").size();
  const auto gameIndexLength =
      gameLine.find(':') - GAME_HEADER_BOILERPLATE_LENGTH;
  const auto gameIndexString =
      gameLine.substr(GAME_HEADER_BOILERPLATE_LENGTH, gameIndexLength);
  const auto index = constexprutils::atoi(gameIndexString);

  const auto gameBag = parseBags(
      gameLine.substr(GAME_HEADER_BOILERPLATE_LENGTH + gameIndexLength));
  return GameData{.index = index, .bag = gameBag};
}

constexpr auto bagPower(const GameData gameData) {
  return gameData.bag.red * gameData.bag.blue * gameData.bag.green;
}

constexpr auto getSolution(const std::string_view s) {
  using namespace std::literals;
  auto gameIndices = std::views::split(s, "\n"sv) |
                     std::views::transform([](const auto input) {
                       return std::string_view(input);
                     }) |
                     std::views::transform(parseGame) |
                     std::views::transform(bagPower);
  return std::accumulate(gameIndices.begin(), gameIndices.end(), 0);
}

int main() {
  using namespace std::literals;
  static constexpr auto solution = getSolution(inputData);

  std::printf("%d\n", solution);
  return 0;
}