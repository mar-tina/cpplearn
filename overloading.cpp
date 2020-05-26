#include <iostream>
#include <stdexcept>

using std::cerr;
using std::cout;

// Won't compile . Find fix
struct SpecialInteger {
  SpecialInteger(unsigned int value) : value{value} {}

  SpecialInteger operator+(unsigned int other) const {
    SpecialInteger result{value + other};
    cout << "Other " << other << " new value " << result.value << " old value "
         << value << "\n";
    if (result.value < value)
      throw std::runtime_error{" Overflow ! "};
    return result;
  }

  const unsigned int value;
};

int main() {
  SpecialInteger shortOne{62};
  auto modShort = shortOne + 30;
  cout << "New short " << modShort.value << "\n";

  try {
    auto bigShort = shortOne + std::numeric_limits<unsigned int>::max();
  } catch (const std::exception &e) {
    cerr << "Something went wrong " << e.what() << '\n';
  }
}