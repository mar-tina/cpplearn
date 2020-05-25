// Implementing a named conversion. Wraps a static cast to check for narrowing
// and throws an error if there is any loss. FROM C++ crash course

#include <iostream>
#include <stdexcept>

using std::cout;

template <typename To, typename From> To narrow_cast(From value) {
  const auto converted = static_cast<To>(value);
  const auto reversed = static_cast<From>(converted);
  if (value != reversed)
    throw std::runtime_error { " NARROWED !" }
  return converted;
}

int main() {
  int perfect{89};
  const auto perfect_short = narrow_cast<short>(perfect);
  cout << "Perfect short: " << perfect_short << "\n";

  try {
    int narrows{142857};
    const auto narrows_short = narrow_cast<short>(narrows);
    cout << "Narrowing value " << perfect_short << "\n";
  } catch (const std::exception &e) {
    cout << "Execption: " << e.what() << '\n';
  }
}