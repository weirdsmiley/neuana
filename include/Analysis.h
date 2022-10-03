#ifndef __ERROR_ANALYSIS_H
#define __ERROR_ANALYSIS_H

#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <utility>
#include <vector>

namespace analysis {

// This declaration will convert any aggregate type to its flattened form.
//    Flatten<vector<vector<double>> = vector<double>;
//    Flatten<vector<double>> = double;
// Cannot use this directive over already scalar types.
template <typename Aggregate> // FIXME: Private
using Flatten = typename std::decay<decltype(Aggregate()[0])>::type;

template <typename Aggregate> using Scalar = Flatten<Flatten<Aggregate>>;

template <typename Aggregate>
auto absolute_error(const Aggregate &true_val, const Aggregate &approx_val)
    -> Aggregate {
  static_assert(std::is_arithmetic<Aggregate>::value,
                "Partial specialization for non-arithmetic Aggregate type does "
                "not exist.");
  return std::abs(approx_val - true_val);
}

using Vec = std::vector<double>;
template <> auto absolute_error<Vec>(const Vec &, const Vec &) -> Vec;

using Matrix = std::vector<std::vector<double>>;
template <>
auto absolute_error<Matrix>(const Matrix &, const Matrix &) -> Matrix;

template <typename Aggregate>
auto relative_error(Aggregate &true_val, Aggregate &approx_val) -> Aggregate {
  Aggregate err(0);
  std::cout << "Reached relative_error function ...\n";
  return err;
}

// Main class to provide APIs for computing all kinds of errors.
template <typename Itype, typename Otype> class Error {
  bool dirty;
  Itype &input;
  std::function<Otype(Itype)> f;
  Otype output;

public:
  Error(Itype &i, std::function<Otype(Itype)> f) : dirty(true), input(i), f(f) {
    output = f(input);
  }

  Itype absolute_error(Itype &true_input) {
    return analysis::absolute_error<Itype>(this->input, true_input);
  }

  Otype relative_error(Otype &true_output) {
    return analysis::relative_error<Otype>(this->output, true_output);
  }

  // FIXME:
  friend std::ostream &operator<<(std::ostream &os, const Error &e) {
    os << "Error Analysis: \n";
    // << "\tInput: " << e.input << "\n"
    // << "\tOutput: " << e.output << "\n";
    return os;
  }
};

}; // namespace analysis

#endif /* __ERROR_ANALYSIS_H */
