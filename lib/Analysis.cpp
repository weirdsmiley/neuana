#include "../include/Analysis.h"
#include <iterator>

namespace analysis {

template <>
auto absolute_error<Vec>(const Vec &true_val, const Vec &approx_val) -> Vec {
  assert(true_val.size() == approx_val.size());

  Vec err;
  typedef Vec::const_iterator VIter;
  for (std::pair<VIter, VIter> I(approx_val.begin(), true_val.begin());
       I.first != approx_val.end(); ++I.first, ++I.second) {
    err.push_back(absolute_error(*I.first, *I.second));
  }

  return err;
}

// template <int M, int N> for a Matrix of size MxN
template <>
auto absolute_error<Matrix>(const Matrix &true_val, const Matrix &approx_val)
    -> Matrix {
  assert(true_val.size() == approx_val.size() &&
         true_val.begin()->size() == approx_val.begin()->size());

  Matrix err;
  typedef Matrix::const_iterator MIter;
  return err;
}

template <>
auto relative_error<Vec>(const Vec &true_val, const Vec &approx_val) -> Vec {
  assert(true_val.size() == approx_val.size());

  Vec err;
  typedef Vec::const_iterator VIter;
  for (std::pair<VIter, VIter> I(approx_val.begin(), true_val.begin());
       I.first != approx_val.end(); ++I.first, ++I.second) {
    err.push_back(relative_error(*I.first, *I.second));
  }

  return err;
}

template <>
auto relative_error<Matrix>(const Matrix &true_val, const Matrix &approx_val)
    -> Matrix {
  assert(true_val.size() == approx_val.size() &&
         true_val.begin()->size() == approx_val.begin()->size());

  Matrix err;
  typedef Matrix::const_iterator MIter;
  return err;
}

}; // namespace analysis
