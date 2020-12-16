/*
* @author Ashlyn Davie
*/

// Counter will be a singleton class so we can get a consistent nummber on
// the customers.
class Counter {
  static final Counter _singleton = Counter._internal();

  int _maxCustomersAllowed;
  int _customerCount = 0;

  factory Counter() {
    return _singleton;
  }

  Counter._internal();

  void incrementCount() {
    _customerCount++;
  }

  void decrementCount() {
    _customerCount--;

    if (_customerCount < 0) _customerCount = 0;
  }

  bool checkMaxCount() {
    if (_customerCount >= _maxCustomersAllowed) return false;
    return true;
  }

  void setMaxCustomerCount(int customerCount) {
    this._maxCustomersAllowed = customerCount;
  }

  int getCustomerCount() {
    return _customerCount;
  }

  int getMaxCustomerCount() {
    return _maxCustomersAllowed;
  }

  void clear() {
    _customerCount = 0;
    _maxCustomersAllowed = 0;
  }
}
