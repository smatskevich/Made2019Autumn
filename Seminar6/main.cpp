#include <iostream>

#include "puzzle8.hpp"

int main() {
  //position start{{1, 2, 3, 4, 0, 6, 7, 5, 8}, 4};
  position start{{2, 4, 3, 1, 0, 6, 7, 5, 8}, 4};
  const auto result = SolvePuzzle8(start);

  if (result.first) {
    for (const auto move : result.second) {
      std::cout << move;
    }
  } else {
    std::cout << "NO SOLUTION";
  }
  return 0;
}
