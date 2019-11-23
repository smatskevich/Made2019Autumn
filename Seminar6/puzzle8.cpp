//
// Created by Stepan Matskevich on 2019-11-23.
//

#include "puzzle8.hpp"

#include <algorithm>
#include <queue>
#include <unordered_map>

bool BFS(const position& start, std::unordered_map<position, position>& parents) {
  std::queue<position> positions_queue;
  positions_queue.push(start);
  while (!positions_queue.empty()) {
    position current = positions_queue.front();
    positions_queue.pop();
    for (auto sibling : current.Siblings()) {
      if (parents.count(sibling)) {
        continue;
      }
      parents[sibling] = current;
      if (sibling.IsFinish()) {
        return true;
      }
      positions_queue.push(sibling);
    }
  }
  return false;
}

std::vector<char> GetPath(const position& start,
    const std::unordered_map<position, position>& parents) {
  std::vector<char> result;

  position current = FinishPosition;
  while (current != start) {
    const position parent = parents.at(current);
    result.push_back(GetMoveSymbol(parent, current));
    current = parent;
  }
  // Развернем result, так как собирали его с конца.
  std::reverse(result.begin(), result.end());
  return result;
}

std::pair<bool, std::vector<char>> SolvePuzzle8(const position& start) {
  // Запустим BFS, запоминая предков всех пройденных позиций.
  std::unordered_map<position, position> parents;
  if (!BFS(start, parents)) {
    return std::make_pair(false, std::vector<char>());
  }
  return std::make_pair(true, GetPath(start, parents));
}
