#include <iostream>
#include <stdexcept>
#include <vector>

using std::cout;
using std::vector;

// Brute force implementation for a mode checker algorithm.
template <typename T> T mode(T *values, size_t length) {
  T result{};
  int count{0};
  int maxCount{0};
  vector<T> checked;

  for (size_t i{}; i < length; i++) {

    if (std::find(checked.begin(), checked.end(), values[i]) != checked.end()) {
      cout << "Already exists in checked"
           << "\n";
    } else {
      for (size_t j{}; j < length; j++) {
        cout << "Inner loop " << values[j] << "\n";
        if (values[i] == values[j]) {
          count++;
        }
      }
    }

    cout << "Logging the mode " << values[i] << " The count: " << count << "\n";
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

  cout << "The mode " << res_mode << " \n";
}