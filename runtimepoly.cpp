#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

struct Logger {
  virtual ~Logger() = default;
  virtual void log_transfer(long from, long to, double amount) = 0;
};

struct AccountDatabase {
  virtual ~AccountDatabase() = default;
  virtual double get_balance(long id) = 0;
  virtual void increase_balance(long id, int amount) = 0;
  virtual void decrease_balance(long id, int amount) = 0;
  virtual void complete_transfer(long from, long to, int amount) = 0;
};

struct Account {

  ~Account() { cout << "ACCOUNT DESTRUCTOR: " << id << "\n"; }
  Account(string name, double balance, int id)
      : balance{balance}, name{name}, id{id} {
    cout << "ACCOUNT CREATED: " << name << " " << balance << " \n";
  }

  int getID() { return id; }
  double getBalance() { return balance; }
  void reduceBalance(double amount) {
    if (balance > amount) {
      balance -= amount;
    } else {
      throw std::runtime_error{"Transaction failed, not enough funds"};
    }
  }

  bool increaseBalance(double amount) {
    balance += amount;
    cout << id << " RECEIVED " << amount << " New balance " << balance << "\n";
    return true;
  }

private:
  string name;
  long id;
  double balance;
};

struct InmemoryDatabase : AccountDatabase {
  InmemoryDatabase(vector<Account *> &accounts) : accounts{accounts} {}

  double get_balance(long id) override {
    auto account = getAccount(id);
    return account->getBalance();
  }

  void increase_balance(long id, int amount) override {
    try {
      Account *account = getAccount(id);
      account->increaseBalance(amount);
    } catch (const std::runtime_error &e) {
      cout << "Exception caught with message " << e.what() << "\n";
    }
  }

  void decrease_balance(long id, int amount) override {
    try {
      Account *account = getAccount(id);
      account->reduceBalance(amount);
    } catch (const std::runtime_error &e) {
      cout << "Exception caught with message " << e.what() << "\n";
    }
  }

  void complete_transfer(long from, long to, int amount) override {
    decrease_balance(from, amount);
    increase_balance(to, amount);
  }

  Account *getAccount(long id) {
    for (auto account : accounts) {
      if (account->getID() == id) {
        return account;
      }
    }
    throw std::runtime_error{"Account with the given ID does not exist"};
  }

private:
  vector<Account *> &accounts;
};

struct FileLogger : Logger {
  void log_transfer(long from, long to, double amount) override {
    cout << "[file] TRANSFERRING: " << amount << " FROM: " << from
         << " TO: " << to << "\n";
  }
};

struct ConsoleLogger : Logger {
  void log_transfer(long from, long to, double amount) override {
    cout << "[console] TRANSFERRING: " << amount << " FROM: " << from
         << " TO: " << to << "\n";
  }
};

enum class LoggerType { Console, File };

struct Bank {
  Bank(Logger *logger, AccountDatabase *database)
      : logger{logger}, database{database} {
    cout << "Bank Constructor "
         << "\n";
  }

  // Constructor injection
  //     Bank(Logger &logger) : logger{logger} {
  //     cout << "Bank Constructor "
  //          << "\n";
  //   }

  void set_logger(Logger *new_logger) { logger = new_logger; }

  void make_transfer(long from, long to, double amount) {
    if (database) {
      database->complete_transfer(from, to, amount);
      if (logger)
        logger->log_transfer(from, to, amount);
    }
  }

  // Constructor injection
  //   void make_transfer(long from, long to, double amount) {
  //     logger.log_transfer(from, to, amount);
  //   }

private:
  // constructor injection
  //   Logger &logger;

  // Property Injection
  Logger *logger{};
  AccountDatabase *database{};
};

int main() {
  vector<Account *> accounts;

  Account martina = Account{"mar-tina", 60.00, 1425672};
  Account mar = Account{"tina", 90.00, 32783841};
  Account tina = Account{"mar", 100.00, 16363};

  accounts.push_back(&martina);
  accounts.push_back(&mar);
  accounts.push_back(&tina);

  InmemoryDatabase db{accounts};
  ConsoleLogger clogger;
  FileLogger logger;
  Bank bank{&logger, &db};

  bank.make_transfer(1425672, 32783841, 8.00);
  bank.make_transfer(16363, 32783841, 9.00);
  bank.set_logger(&clogger);
  bank.make_transfer(16363, 32783841, 7.60);
}