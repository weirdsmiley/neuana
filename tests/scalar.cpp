#include "../include/Analysis.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <functional>
#include <iterator>
#include <type_traits>
#include <vector>
using namespace std;

double horriblesqrt(double n) {
  return sqrt(n + 1e-3);
}

void test_scalar() {
  cout << "Testing scalar types ...\n";

  double true_input = 2.0;
  double true_output = sqrt(true_input);

  double input = 2.0 + 1e-3;
  function<double(double)> f = horriblesqrt;

  auto e = new analysis::Error<double, double>(input, f);
  // auto aeb = e->absolute_backward(true_input);
  // auto reb = e->relative_backward(true_input);
  // auto aef = e->absolute_forward(true_output);
  // auto ref = e->relative_forward(true_output);

  // cout << "Absolute error: " << aeb << endl;
  // cout << "Relative error: " << ref << endl;

  // When input and output types are indistinguishable then
  // there is no way to infer which computation (forward/backward)
  // users want. So they explicitly have to provide it.
  auto aeb = e->absolute(true_input, analysis::Type::Backward);
  auto aef = e->absolute(true_output, analysis::Type::Forward);
  auto reb = e->relative(true_input, analysis::Type::Backward);
  auto ref = e->relative(true_output, analysis::Type::Forward);
  cout << "Absolute backward: " << aeb << endl;
  cout << "Absolute forward: " << aef << endl;
}

double horriblesqrtv(analysis::Vec v) {
  double res = 0.0;
  for (auto i : v) {
    res += horriblesqrt(i);
  }
  return res;
}
// void test_scalar_diff() {
//   cout << "Testing vector input and scalar output type ...\n";

//   analysis::Vec true_input({3.0, 4.0});
//   double true_output = 3.73205;

//   analysis::Vec input({3.00001, 4.00002});
//   function<double(analysis::Vec)> f = horriblesqrtv;
//   auto e = new analysis::Error<analysis::Vec, double>(input, f);
//   // auto ae = e->absolute_error(true_output);
//   // auto re = e->relative_error(true_output);
//   // auto aef = e->absolute_forward(true_output);
//   // auto aeb = e->absolute_backward(true_input);
//   auto aef = e->absolute(true_output, analysis::Type::Forward);
//   // auto aeb = e->absolute(true_input);

//   cout << aef << endl;
//   // cout << "backward : ";
//   // copy(aeb.begin(), aeb.end(),
//   //     ostream_iterator<analysis::Flatten<analysis::Vec>>(cout, " "));
//   // cout << "\n";
//   // cout << *e << endl;
// }

int main(int argc, char **argv) {
  test_scalar();
  // test_scalar_diff();
  return 0;
}
