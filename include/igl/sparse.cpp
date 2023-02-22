// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "sparse.h"

#include <iostream>
#include <vector>

template <class IndexVector, class ValueVector, typename T>
IGL_INLINE void igl::sparse(
  const IndexVector & I,
  const IndexVector & J,
  const ValueVector & V,
  Eigen::SparseMatrix<T>& X)
{
  size_t m = (size_t)I.maxCoeff()+1;
  size_t n = (size_t)J.maxCoeff()+1;
  return igl::sparse(I,J,V,m,n,X);
}

#include "verbose.h"
template <
  class IndexVectorI,
  class IndexVectorJ,
  class ValueVector,
  typename T>
IGL_INLINE void igl::sparse(
  const IndexVectorI & I,
  const IndexVectorJ & J,
  const ValueVector & V,
  const size_t m,
  const size_t n,
  Eigen::SparseMatrix<T>& X)
{
  using namespace std;
  using namespace Eigen;
  assert((int)I.maxCoeff() < (int)m);
  assert((int)I.minCoeff() >= 0);
  assert((int)J.maxCoeff() < (int)n);
  assert((int)J.minCoeff() >= 0);
  assert(I.size() == J.size());
  assert(J.size() == V.size());
  // Really we just need .size() to be the same, but this is safer
  assert(I.rows() == J.rows());
  assert(J.rows() == V.rows());
  assert(I.cols() == J.cols());
  assert(J.cols() == V.cols());
  vector<Triplet<T> > IJV;
  IJV.reserve(I.size());
  for(int x = 0;x<I.size();x++)
  {
    IJV.push_back(Triplet<T >(I(x),J(x),V(x)));
  }
  X.resize(m,n);
  X.setFromTriplets(IJV.begin(),IJV.end());
}

template <typename DerivedD, typename T>
IGL_INLINE void igl::sparse(
  const Eigen::PlainObjectBase<DerivedD>& D,
  Eigen::SparseMatrix<T>& X)
{
  assert(false && "Obsolete. Just call D.sparseView() directly");
  using namespace std;
  using namespace Eigen;
  vector<Triplet<T> > DIJV;
  const int m = D.rows();
  const int n = D.cols();
  for(int i = 0;i<m;i++)
  {
    for(int j = 0;j<n;j++)
    {
      if(D(i,j)!=0)
      {
        DIJV.push_back(Triplet<T>(i,j,D(i,j)));
      }
    }
  }
  X.resize(m,n);
  X.setFromTriplets(DIJV.begin(),DIJV.end());
}

template <typename DerivedD>
IGL_INLINE Eigen::SparseMatrix<typename DerivedD::Scalar > igl::sparse(
  const Eigen::PlainObjectBase<DerivedD>& D)
{
  assert(false && "Obsolete. Just call D.sparseView() directly");
  Eigen::SparseMatrix<typename DerivedD::Scalar > X;
  igl::sparse(D,X);
  return X;
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template void igl::sparse<Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<int, -1, 1, 0, -1, 1>, int>(Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, unsigned long, unsigned long, Eigen::SparseMatrix<int, 0, int>&);
// generated by autoexplicit.sh
template void igl::sparse<Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true>, Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true>, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<int>, Eigen::Matrix<int, -1, 1, 0, -1, 1> >, int>(Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true> const&, Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true> const&, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<int>, Eigen::Matrix<int, -1, 1, 0, -1, 1> > const&, unsigned long, unsigned long, Eigen::SparseMatrix<int, 0, int>&);
// generated by autoexplicit.sh
template void igl::sparse<Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true>, Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true>, Eigen::CwiseBinaryOp<Eigen::internal::scalar_difference_op<int, int>, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<int>, Eigen::Array<int, -1, 1, 0, -1, 1> const> const, Eigen::CwiseBinaryOp<Eigen::internal::scalar_product_op<int, int>, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<int>, Eigen::Array<int, -1, 1, 0, -1, 1> const> const, Eigen::CwiseUnaryOp<Eigen::internal::scalar_cast_op<bool, int>, Eigen::CwiseBinaryOp<Eigen::internal::scalar_cmp_op<int, int, (Eigen::internal::ComparisonName)1>, Eigen::ArrayWrapper<Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true> > const, Eigen::ArrayWrapper<Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true> > const> const> const> const>, int>(Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true> const&, Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true> const&, Eigen::CwiseBinaryOp<Eigen::internal::scalar_difference_op<int, int>, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<int>, Eigen::Array<int, -1, 1, 0, -1, 1> const> const, Eigen::CwiseBinaryOp<Eigen::internal::scalar_product_op<int, int>, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<int>, Eigen::Array<int, -1, 1, 0, -1, 1> const> const, Eigen::CwiseUnaryOp<Eigen::internal::scalar_cast_op<bool, int>, Eigen::CwiseBinaryOp<Eigen::internal::scalar_cmp_op<int, int, (Eigen::internal::ComparisonName)1>, Eigen::ArrayWrapper<Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true> > const, Eigen::ArrayWrapper<Eigen::Block<Eigen::Matrix<int, -1, -1, 0, -1, -1>, -1, 1, true> > const> const> const> const> const&, unsigned long, unsigned long, Eigen::SparseMatrix<int, 0, int>&);
// generated by autoexplicit.sh
#ifndef WIN32
//template void igl::sparse<Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<bool>, Eigen::Array<bool, -1, 2, 0, -1, 2> >, bool>(Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::Matrix<int, -1, -1, 0, -1, -1> const&, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<bool>, Eigen::Array<bool, -1, 2, 0, -1, 2> > const&, unsigned long, unsigned long, Eigen::SparseMatrix<bool, 0, int>&);
//template void igl::sparse<Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<bool>, Eigen::Array<bool, -1, 3, 0, -1, 3> >, bool>(Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<bool>, Eigen::Array<bool, -1, 3, 0, -1, 3> > const&, unsigned long, unsigned long, Eigen::SparseMatrix<bool, 0, int>&);
#if EIGEN_VERSION_AT_LEAST(3,3,0)
#else
//template void igl::sparse<Eigen::CwiseNullaryOp<Eigen::internal::linspaced_op<int, true>, Eigen::Matrix<int, -1, 1, 0, -1, 1> >, Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<bool>, Eigen::Array<bool, -1, 1, 0, -1, 1> >, bool>(Eigen::CwiseNullaryOp<Eigen::internal::linspaced_op<int, true>, Eigen::Matrix<int, -1, 1, 0, -1, 1> > const&, Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<bool>, Eigen::Array<bool, -1, 1, 0, -1, 1> > const&, unsigned long, unsigned long, Eigen::SparseMatrix<bool, 0, int>&);
#endif
#endif

template void igl::sparse<Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<double, -1, 1, 0, -1, 1>, std::complex<double> >(Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, Eigen::Matrix<double, -1, 1, 0, -1, 1> const&, size_t, size_t, Eigen::SparseMatrix<std::complex<double>, 0, int>&);
template void igl::sparse<Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<double, -1, 1, 0, -1, 1>, double>(Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, Eigen::Matrix<double, -1, 1, 0, -1, 1> const&, Eigen::SparseMatrix<double, 0, int>&);
template void igl::sparse<Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<double, -1, 1, 0, -1, 1>, double>(Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, Eigen::Matrix<int, -1, 1, 0, -1, 1> const&, Eigen::Matrix<double, -1, 1, 0, -1, 1> const&, size_t, size_t, Eigen::SparseMatrix<double, 0, int>&);
#endif
