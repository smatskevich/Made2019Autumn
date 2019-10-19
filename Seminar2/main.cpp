#include <iostream>

struct Point {
  int x;
  int y;

  bool operator<(const Point& other) const;
};

bool Point::operator<(const Point& other) const {
  return y < other.y;
}

// Использует оператор <
void BubbleSort(Point* arr, int size) {
  for(int i = 0; i < size - 1; ++i) {
    for(int j = 0; j < size - i - 1; ++j) {
      if(arr[j + 1] < arr[j]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

// Функция сравнения по расстоянию до центра координат.
bool CompareByDistToZero(const Point& first, const Point& second) {
  return (first.x * first.x + first.y * first.y) <
      (second.x * second.x + second.y * second.y);
}

// Использует функцию сравнения
void BubbleSort(Point* arr, int size, bool (*compare)(const Point&, const Point&)) {
  for(int i = 0; i < size - 1; ++i) {
    for(int j = 0; j < size - i - 1; ++j) {
      if(compare(arr[j + 1], arr[j])) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

// Функтор, сравнивающий точки по расстоянию до center.
class ComparerByDistToCenter {
 public:
  explicit ComparerByDistToCenter(const Point& center) : center_(center) {}

  bool operator()(const Point& first, const Point& second) const;

 private:
  Point center_;
};

bool ComparerByDistToCenter::operator()(const Point& first, const Point& second) const {
  const int first_diff_x = first.x - center_.x;
  const int first_diff_y = first.y - center_.y;
  const int second_diff_x = second.x - center_.x;
  const int second_diff_y = second.y - center_.y;

  return (first_diff_x * first_diff_x + first_diff_y * first_diff_y) <
      (second_diff_x * second_diff_x + second_diff_y * second_diff_y);
}

// Использует шаблонное нечто, имеющее ()
template<typename TCompare>
void BubbleSortT(Point* arr, int size, const TCompare& compare) {
  for(int i = 0; i < size - 1; ++i) {
    for(int j = 0; j < size - i - 1; ++j) {
      if(compare(arr[j + 1], arr[j])) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}


int main() {
  Point arr[]{Point{3, 5}, Point{0, 0}, Point{1, 2}, Point{2, 8}, Point{4, 2}};
  // Сортировка с помощью оператора <
  // BubbleSort(arr, 5);

  // Сортировка с помощью функции сравнения
  // BubbleSort(arr, 5, CompareByDistToZero);

  // Сортировка с помощью функции сравнения шаблонной функцией
  // BubbleSortT(arr, 5, CompareByDistToZero);

  // Сортировка с помощью функтора шаблонной функцией
  // BubbleSortT(arr, 5, ComparerByDistToCenter(Point{3, 3}));

  const Point center{3, 3};
  BubbleSortT(arr, 5, [&center](const Point& first, const Point& second) {
    const int first_diff_x = first.x - center.x;
    const int first_diff_y = first.y - center.y;
    const int second_diff_x = second.x - center.x;
    const int second_diff_y = second.y - center.y;

    return (first_diff_x * first_diff_x + first_diff_y * first_diff_y) <
           (second_diff_x * second_diff_x + second_diff_y * second_diff_y);
  });

  for(int i = 0; i < 5; ++i) {
    std::cout << arr[i].x << " " << arr[i].y << std::endl;
  }
  return 0;
}