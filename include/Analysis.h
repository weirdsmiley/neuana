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

enum class Type {
  None = 0, // Don't care, if Itype and Otype are different
  Forward,
  Backward,
};

inline std::ostream &operator<<(std::ostream &os, const Type &type) {
  switch (type) {
    case Type::None:
      os << "Undefined";
      break;
    case Type::Forward:
      os << "Forward error";
      break;
    case Type::Backward:
      os << "Backward error";
      break;
  }

  return os;
}

// This declaration will convert any aggregate type to its flattened form.
//    Flatten<vector<vector<double>> = vector<double>;
//    Flatten<vector<double>> = double;
// Cannot use this directive over already scalar types.
template <typename Aggregate> // FIXME: Private
using Flatten = typename std::decay<decltype(Aggregate()[0])>::type;
using Vec = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;

template <typename Aggregate> using Scalar = Flatten<Flatten<Aggregate>>;

template <typename Aggregate>
auto absolute_error(const Aggregate &true_val, const Aggregate &approx_val)
    -> Aggregate {
  static_assert(std::is_arithmetic<Aggregate>::value,
                "Partial specialization for non-arithmetic Aggregate type does "
                "not exist.");

  return std::abs(approx_val - true_val);
}

template <> auto absolute_error<Vec>(const Vec &, const Vec &) -> Vec;

template <>
auto absolute_error<Matrix>(const Matrix &, const Matrix &) -> Matrix;

template <typename Aggregate>
auto relative_error(const Aggregate &true_val, const Aggregate &approx_val)
    -> Aggregate {
  static_assert(std::is_arithmetic<Aggregate>::value,
                "Partial specialization for non-arithmetic Aggregate type does "
                "not exist.");
  // return absolute_error(approx_val, true_val) / std::abs(true_val);
  return std::abs(approx_val - true_val) / std::abs(true_val);
}

template <> auto relative_error<Vec>(const Vec &, const Vec &) -> Vec;

template <>
auto relative_error<Matrix>(const Matrix &, const Matrix &) -> Matrix;

// Main class to provide APIs for computing all kinds of errors.
template <typename Itype, typename Otype> class [[nodiscard]] Error final {
  bool dirty;
  Itype &input;
  std::function<Otype(Itype)> f;
  Otype output;

public:
  Error(Itype &i, std::function<Otype(Itype)> f) : dirty(true), input(i), f(f) {
    output = f(input);
  }

  // TODO: This family of methods is deprecated!
  // Use absolute() and relative() instead.
  template <typename T = Itype> T absolute_backward(T &true_val) {
    return analysis::absolute_error<T>(this->input, true_val);
  }

  template <typename T = Otype> T absolute_forward(T &true_val) {
    return analysis::absolute_error<T>(this->output, true_val);
  }

  template <typename T = Itype> T relative_backward(T &true_val) {
    return analysis::relative_error<T>(this->input, true_val);
  }

  template <typename T = Otype> T relative_forward(T &true_val) {
    return analysis::relative_error<T>(this->output, true_val);
  }

  template <typename T> T absolute(T &true_val, Type type = Type::None) {
    static_assert(std::is_same<T, Itype>() || std::is_same<T, Otype>(),
                  "Unknown type for computing absolute error");

    if (std::is_same<Itype, Otype>()) {
      switch (type) {
        case Type::Backward:
          return analysis::absolute_error<T>(this->input, true_val);

        case Type::Forward:
          return analysis::absolute_error<T>(this->output, true_val);

          [[unlikely]] case Type::None
              : throw std::runtime_error(
                    "Computing type must not be Type::None when "
                    "input and output types are indistinguishable");
      };
    }

    return std::is_same<T, Itype>()
               ? analysis::absolute_error<T>(this->input, true_val)
               : analysis::absolute_error<T>(this->output, true_val);
  }

  template <typename T> T relative(T &true_val, const Type type = Type::None) {
    static_assert(std::is_same<T, Itype>() || std::is_same<T, Otype>(),
                  "Unknown type for computing relative error");

    if (std::is_same<Itype, Otype>()) {
      switch (type) {
        case Type::Backward:
          return analysis::relative_error<T>(this->input, true_val);

        case Type::Forward:
          return analysis::relative_error<T>(this->output, true_val);

          [[unlikely]] case Type::None
              : throw std::runtime_error(
                    "Computing type must not be Type::None when "
                    "input and output types are indistinguishable");
      };
    }

    return std::is_same<T, Itype>()
               ? analysis::relative_error<Itype>(this->input, true_val)
               : analysis::relative_error<Otype>(this->output, true_val);
  }

  // FIXME: For vector types.
  friend std::ostream &operator<<(std::ostream &os, const Error &e) {
    os << "Error Analysis: \n"
       << "\tInput: " << e.input << "\n"
       << "\tOutput: " << e.output << "\n";
    return os;
  }
};

}; // namespace analysis

#endif /* __ERROR_ANALYSIS_H */
