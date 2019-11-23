//
// Created by Stepan Matskevich on 2019-11-23.
//

#include "position.hpp"

#include <assert.h>

bool position::IsFinish() const {
  return operator==(FinishPosition);
}

std::vector<position> position::Siblings() const {
  std::vector<position> result;
  if (zero_place < 6) {
    position sibling = *this;
    std::swap(sibling.chips[zero_place], sibling.chips[zero_place + 3]);
    sibling.zero_place += 3;
    result.emplace_back(sibling);
  }
  if (zero_place >= 3) {
    position sibling = *this;
    std::swap(sibling.chips[zero_place], sibling.chips[zero_place - 3]);
    sibling.zero_place -= 3;
    result.emplace_back(sibling);
  }
  if (zero_place % 3 != 0) {
    position sibling = *this;
    std::swap(sibling.chips[zero_place], sibling.chips[zero_place - 1]);
    sibling.zero_place -= 1;
    result.emplace_back(sibling);
  }
  if (zero_place % 3 != 2) {
    position sibling = *this;
    std::swap(sibling.chips[zero_place], sibling.chips[zero_place + 1]);
    sibling.zero_place += 1;
    result.emplace_back(sibling);
  }
  return result;
}

bool position::operator==(const position& other) const {
  for (size_t i = 0; i < chips.size(); ++i ) {
    if (chips[i] != other.chips[i]) return false;
  }
  return true;
}

char GetMoveSymbol(const position& from, const position& to) {
  char zero_diff = to.zero_place - from.zero_place;
  switch (zero_diff) {
    case 1:
      return 'L'; // Ноль вправо -> фишка влево
    case -1:
      return 'R';
    case 3:
      return 'U';
    case -3:
      return 'D';
    default:
      assert(false);
  }
  return 0;
}
