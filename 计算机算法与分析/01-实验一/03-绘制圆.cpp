#include <cmath>
#include <iostream>
using namespace std;
int main() {
  for (double y = 10; y >= -10; y -= 1) {
    for (int i = 0; i < 10; i++)
      cout << " ";
    double x = 2.5 * (10 - sqrt(100 - y * y)), t;
    for (t = 0; t < x; t += 1)
      cout << " ";
    cout << "*";
    for (; t < 20 * 2.5 - x; t += 1)
      cout << " ";
    cout << "*" << endl;
  }
  return 0;
}
