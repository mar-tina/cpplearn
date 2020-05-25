#include <chrono>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <thread>

using std::cout;
using namespace std::chrono_literals;

struct TimerClass {

  TimerClass() { gettimeofday(&timestamp, NULL); }
  ~TimerClass() {

    gettimeofday(&endtime, NULL);
    cout << "COPY DESTRUCTOR: " << endtime.tv_sec << "\n";
  }
  // copy constructor
  TimerClass(const TimerClass &other)
      : timestamp(other.timestamp), endtime(other.endtime) {
    cout << "COPY CONSTRUCTOR: " << other.timestamp.tv_sec << "  "
         << other.endtime.tv_sec << "\n";
  }

  //   // move constructor
  //   TimerClass(TimerClass &&other) noexcept
  //       : timestamp(other.timestamp), endtime{0, 0} {
  //     // assign the member values in other to their ZERO values.
  //     other.timestamp = {0, 0};
  //     other.endtime = {0, 0};
  //   }

  //   // copy assignment
  //   TimerClass &operator=(const TimerClass &other) {
  //     // self-reference check
  //     if (this == &other)
  //       return *this;

  //     timestamp = other.timestamp;
  //     endtime = {0, 0};
  //     return *this;
  //   }

  // move assignment
  TimerClass &operator=(TimerClass &&other) noexcept {
    cout << "MOVE ASSIGNMENT: " << other.timestamp.tv_sec << "  ";

    if (this == &other)
      return *this;

    timestamp = other.timestamp;
    endtime = {0, 0};

    other.timestamp = {0, 0};
    other.endtime = {0, 0};

    return *this;
  }

  void print_elapsed() {
    gettimeofday(&endtime, NULL);
    cout << "ELAPSED: " << endtime.tv_sec - timestamp.tv_sec << "\n";
  }

private:
  timeval timestamp;
  timeval endtime;
};

int main() {
  cout << "Running the object lifecycle demo"
       << " \n";

  TimerClass tclass1;
  TimerClass tclass2;
  tclass2 = std::move(tclass1);
  tclass1.print_elapsed();

  std::this_thread::sleep_for(10s);
  tclass2.print_elapsed();
}
