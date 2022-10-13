#include "../include/Analysis.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <type_traits>
#include <cmath>
using namespace std;

double mysqrt(double n) {
  return sqrt(n) + 1e-3;
}
void test_scalar() {
  cout << "Testing scalar types...\n";
  double input = 2.3;
  double true_input = 2.3 + 1e-2;
  double true_output = 1.517999;
  function<double(double)> f = mysqrt;
  auto e = new analysis::Error<double, double>(input, f);
  // auto ae = e->absolute_error(true_input);
  // cout << "Absolute error: " << ae << endl;
  // auto re = e->relative_error(true_output);
  // cout << result << endl;
  // cout << *e << endl;
}

template <typename Vec>
Vec mysqrtv(Vec v) {
  Vec res;
  for (auto i: v)
    res.push_back(mysqrt(i));
  return res;
}
void test_vector() {
  cout << "Testing vector types...\n";
  using vec_d = vector<double>;
  vec_d input = {1.2, 2.3};
  vec_d true_input = {1.2 + 1e-2, 2.34};
  function<vec_d(vec_d)> f = mysqrtv<vec_d>;

  auto e = new analysis::Error<vec_d, vec_d>(input, f);
  // auto result = e->absolute_error(true_input);
  // cout << *e << endl;
}

template<typename Matrix>
using Flat = typename decay<decltype(Matrix()[0])>::type;
template <typename Matrix>
auto mysqrtm(Matrix m) -> Matrix {
  Matrix res;
  for (auto i=m.begin(); i!=m.end(); ++i) {
    Flat<Matrix> row;
    for (auto j=i->begin(); j!=i->end(); ++j) {
      row.push_back(mysqrt(*j));
    }
    res.push_back(row);
  }
  return res;
}
void test_matrix() {
  cout << "Testing matrix types...\n";
  using mat_d = vector<vector<double>>;
  mat_d input = {{1.2,2.3},{3.4,4.5}};
  mat_d true_input = {{1.2+1e-2,2.30002},{3.4034,4.5+1e-2}};
  function<mat_d(mat_d)> f = mysqrtm<mat_d>;

  auto e = new analysis::Error<mat_d, mat_d>(input, f);
  // auto result = e->absolute_error(true_input);
}

void test_flattening() {
  using Matrix = vector<vector<double>>;
  cout << typeid(Matrix).name() << endl;
  cout << typeid(analysis::Flatten<Matrix>).name() << endl;
  cout << typeid(analysis::Flatten<analysis::Flatten<Matrix>>).name() << endl;

  cout << is_arithmetic<Matrix>::value << endl;
  cout << is_arithmetic<analysis::Flatten<Matrix>>::value << endl;
  cout << is_arithmetic<analysis::Flatten<analysis::Flatten<Matrix>>>::value << endl;

  using Aggregate = Matrix;


  cout << "Aggregate type: " << typeid(Aggregate).name() << endl;
  cout << "Flatten-1 type: " << typeid(analysis::Flatten<Aggregate>).name() << endl;
  cout << "Flatten-2 type: " << typeid(analysis::Scalar<Aggregate>).name() << endl;
}

// void new_test() {
//   // FIXME: Add initilizations and compute function.
//   using Matrix = double **;
//   // Matrix m = {{1,2},{3,4}}, t = {{1.1,2.1},{3.0,4.0}};
//   Matrix m, t;
//   function<Matrix(Matrix)> f;
//   auto e = new analysis::Error<Matrix, Matrix>(m, f);
//   e->absolute_error(t);
// }

int main(int argc, char **argv) {
  test_scalar();
  test_vector();
  test_matrix();
  test_flattening();
  // new_test();
  return 0;
}
