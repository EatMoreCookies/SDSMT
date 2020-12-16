/*
* Tim Adcock
*/
class Stats {
  int _customersEntered = 0;
  int _customersExited = 0;

  void customerEntered() {
    _customersEntered++;
  }

  void customererExited() {
    _customersExited++;
  }

  int getCustomersEntered() {
    return _customersEntered;
  }

  int getCustomersExited() {
    return _customersExited;
  }
}
