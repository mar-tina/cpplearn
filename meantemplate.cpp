#include <iostream>
#include <stdexcept>

template <typename T> T mean(T *values, size_t length) {
  T result{};
  for (size_t i{}; i < length; i++) {
    result += values[i];
  }

  return result / length;
}

int main() {
  double manythings[]{5.0, 6.0, 4.0};
  const auto res_double = mean(manythings, sizeof(manythings) / sizeof(double));
  std::cout << "RESULT " << res_double << "\n";

  int manyints[]{5, 6, 4};
  const auto res_int = mean<int>(manyints, sizeof(manyints) / sizeof(double));
  std::cout << "RESULT " << res_int << "\n";
}