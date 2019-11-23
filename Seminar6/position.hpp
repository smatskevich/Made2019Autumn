//
// Created by Stepan Matskevich on 2019-11-23.
//
#pragma once

#include <vector>

const size_t HashParameter = 37;

struct position {
  std::vector<char> chips;
  char zero_place;

  bool IsFinish() const;
  std::vector<position> Siblings() const;

  bool operator==(const position& other) const;
  bool operator!=(const position& other) const { return !operator==(other); }
};

namespace std {
  template <>
  struct hash<position> {
    size_t operator()(const position& key) const {
      size_t value = 0;
      for (auto chip : key.chips) {
        value = HashParameter * value + static_cast<size_t>(chip);
      }
      return value;
    }
  };
}

const position FinishPosition{{1, 2, 3, 4, 5, 6, 7, 8, 0}, 8};

char GetMoveSymbol(const position& from, const position& to);
