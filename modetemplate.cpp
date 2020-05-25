#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

using std::cout;
using std::string;
using std::vector;

// Brute force implementation for a mode checker algorithm.
template <typename T> T mode(T *values, size_t length) {
  T result{};
  int count{0};
  int maxCount{0};
  vector<T> checked;

  static_assert(std::is_arithmetic<T>(),
                "Type must support addition and division");

  for (size_t i{}; i < length; i++) {

    if (std::find(checked.begin(), checked.end(), values[i]) != checked.end()) {
      cout << "Already exists in checked"
           << "\n";
    } else {
      for (size_t j{}; j < length; j++) {
        if (values[i] == values[j]) {
          count++;
        }
      }
    }

    cout << "Current value " << values[i] << " The count: " << count << "\n";
    if (count > maxCount) {
      maxCount = count;
      result = values[i];
    }

    count = 0;
    checked.push_back(values[i]);
  }

  return result;
}

int main() {
  int manymodes[]{1, 2, 2, 3, 1, 2};
  const auto res_mode = mode<int>(manymodes, sizeof(manymodes) / sizeof(int));

  // Commented out code block should fail to compile.
  //   string failinitializer[]{"a", "b", "c", "c"};
  //   const auto fail_res =
  //       mode<string>(failinitializer, sizeof(failinitializer) /
  //       sizeof(char));

  cout << "The mode " << res_mode << " \n";
}