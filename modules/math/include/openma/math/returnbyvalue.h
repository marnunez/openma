/* 
 * Open Source Movement Analysis Library
 * Copyright (C) 2016, Moveck Solution Inc., all rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __openma_math_returnbyvalue_h
#define __openma_math_returnbyvalue_h

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <type_traits>
#include <vector>
#include <array>

namespace Eigen
{
namespace internal
{ 
  // ----------------------------------------------------------------------- //
  //                            CrossOp return value
  // ----------------------------------------------------------------------- //

  template<typename V1, typename V2> struct CrossOpValues;

  template<typename V1, typename V2>
  struct traits<CrossOpValues<V1,V2>>
  {
    using ReturnType = typename ma::math::Traits<ma::math::Array<std::decay<V1>::type::ColsAtCompileTime>>::Values;
  };
  
  template<typename V1, typename V2>
  struct CrossOpValues : public Eigen::ReturnByValue<CrossOpValues<V1,V2>>
  {
    using InputType1 = typename std::decay<V1>::type;
    using InputType2 = typename std::decay<V2>::type;
    using Index = typename InputType1::Index;
    typename InputType1::Nested m_V1;
    typename InputType2::Nested m_V2;
  public:
    CrossOpValues(const V1& v1, const V2& v2) : m_V1(v1), m_V2(v2) {};
    template <typename R> inline void evalTo(R& result) const
    {
      // TODO: Is there a better way to implement the cross product?
      const auto& v1x = this->m_V1.col(0);
      const auto& v1y = this->m_V1.col(1);
      const auto& v1z = this->m_V1.col(2);
      const auto& v2x = this->m_V2.col(0);
      const auto& v2y = this->m_V2.col(1);
      const auto& v2z = this->m_V2.col(2);
      // result.resize(this->rows(),Eigen::NoChange);
      result.col(0) = (v1y * v2z) - (v1z * v2y);
      result.col(1) = (v1z * v2x) - (v1x * v2z);
      result.col(2) = (v1x * v2y) - (v1y * v2x);
    };
    Index rows() const {return this->m_V1.rows();};
    Index cols() const {return this->m_V1.cols();};
  };
  
  // ----------------------------------------------------------------------- //
  //                         TransformOp return value
  // ----------------------------------------------------------------------- //

  template<typename V1, typename V2> struct TransformOpValues;
  
  template<typename V1, typename V2>
  struct traits<TransformOpValues<V1,V2>>
  {
    using ReturnType = typename ma::math::Traits<ma::math::Array<std::decay<V2>::type::ColsAtCompileTime>>::Values;
  };
  
  // Motion against motion (12 vs 12)
  
  template<typename V1, typename V2>
  struct TransformOpValues : public Eigen::ReturnByValue<TransformOpValues<V1,V2>>
  {
    using InputType1 = typename std::decay<V1>::type;
    using InputType2 = typename std::decay<V2>::type;
    using Index = typename InputType1::Index;
    typename InputType1::Nested m_V1;
    typename InputType2::Nested m_V2;
    
    template <typename R, typename U1, typename U2> static inline void evaluate_12x12(R& result, const U1& v1, const U2& v2)
    {
      // lhs
      const auto& l11 = v1.col(0);
      const auto& l21 = v1.col(1);
      const auto& l31 = v1.col(2);
      const auto& l12 = v1.col(3);
      const auto& l22 = v1.col(4);
      const auto& l32 = v1.col(5);
      const auto& l13 = v1.col(6);
      const auto& l23 = v1.col(7);
      const auto& l33 = v1.col(8);
      const auto& l14 = v1.col(9);
      const auto& l24 = v1.col(10);
      const auto& l34 = v1.col(11);
      // rhs
      const auto& r11 = v2.col(0);
      const auto& r21 = v2.col(1);
      const auto& r31 = v2.col(2);
      const auto& r12 = v2.col(3);
      const auto& r22 = v2.col(4);
      const auto& r32 = v2.col(5);
      const auto& r13 = v2.col(6);
      const auto& r23 = v2.col(7);
      const auto& r33 = v2.col(8);
      const auto& r14 = v2.col(9);
      const auto& r24 = v2.col(10);
      const auto& r34 = v2.col(11);
      // Computation
      result.col(0)  = l11 * r11 + l12 * r21 + l13 * r31;
      result.col(1)  = l21 * r11 + l22 * r21 + l23 * r31;
      result.col(2)  = l31 * r11 + l32 * r21 + l33 * r31;
      result.col(3)  = l11 * r12 + l12 * r22 + l13 * r32;
      result.col(4)  = l21 * r12 + l22 * r22 + l23 * r32;
      result.col(5)  = l31 * r12 + l32 * r22 + l33 * r32;
      result.col(6)  = l11 * r13 + l12 * r23 + l13 * r33;
      result.col(7)  = l21 * r13 + l22 * r23 + l23 * r33;
      result.col(8)  = l31 * r13 + l32 * r23 + l33 * r33;
      result.col(9)  = l11 * r14 + l12 * r24 + l13 * r34 + l14;
      result.col(10) = l21 * r14 + l22 * r24 + l23 * r34 + l24;
      result.col(11) = l31 * r14 + l32 * r24 + l33 * r34 + l34;
    };
    
    template <typename R, typename U1, typename U2> static inline void evaluate_9x9(R& result, const U1& v1, const U2& v2)
    {
      // lhs
      const auto& l11 = v1.col(0);
      const auto& l21 = v1.col(1);
      const auto& l31 = v1.col(2);
      const auto& l12 = v1.col(3);
      const auto& l22 = v1.col(4);
      const auto& l32 = v1.col(5);
      const auto& l13 = v1.col(6);
      const auto& l23 = v1.col(7);
      const auto& l33 = v1.col(8);
      // rhs
      const auto& r11 = v2.col(0);
      const auto& r21 = v2.col(1);
      const auto& r31 = v2.col(2);
      const auto& r12 = v2.col(3);
      const auto& r22 = v2.col(4);
      const auto& r32 = v2.col(5);
      const auto& r13 = v2.col(6);
      const auto& r23 = v2.col(7);
      const auto& r33 = v2.col(8);
      // Computation
      result.col(0)  = l11 * r11 + l12 * r21 + l13 * r31;
      result.col(1)  = l21 * r11 + l22 * r21 + l23 * r31;
      result.col(2)  = l31 * r11 + l32 * r21 + l33 * r31;
      result.col(3)  = l11 * r12 + l12 * r22 + l13 * r32;
      result.col(4)  = l21 * r12 + l22 * r22 + l23 * r32;
      result.col(5)  = l31 * r12 + l32 * r22 + l33 * r32;
      result.col(6)  = l11 * r13 + l12 * r23 + l13 * r33;
      result.col(7)  = l21 * r13 + l22 * r23 + l23 * r33;
      result.col(8)  = l31 * r13 + l32 * r23 + l33 * r33;
    };
    
    template <typename R, typename U1, typename U2> static inline void evaluate_12x3(R& result, const U1& v1, const U2& v2)
    {
      // lhs
      const auto& l11 = v1.col(0);
      const auto& l21 = v1.col(1);
      const auto& l31 = v1.col(2);
      const auto& l12 = v1.col(3);
      const auto& l22 = v1.col(4);
      const auto& l32 = v1.col(5);
      const auto& l13 = v1.col(6);
      const auto& l23 = v1.col(7);
      const auto& l33 = v1.col(8);
      const auto& l14 = v1.col(9);
      const auto& l24 = v1.col(10);
      const auto& l34 = v1.col(11);
      // rhs
      const auto& px = v2.col(0);
      const auto& py = v2.col(1);
      const auto& pz = v2.col(2);
      // Computation
      result.col(0)  = l11 * px + l12 * py + l13 * pz + l14;
      result.col(1)  = l21 * px + l22 * py + l23 * pz + l24;
      result.col(2)  = l31 * px + l32 * py + l33 * pz + l34;
    };
    
    template <typename R, typename U1, typename U2> static inline void evaluate_9x3(R& result, const U1& v1, const U2& v2)
    {
      // lhs
      const auto& l11 = v1.col(0);
      const auto& l21 = v1.col(1);
      const auto& l31 = v1.col(2);
      const auto& l12 = v1.col(3);
      const auto& l22 = v1.col(4);
      const auto& l32 = v1.col(5);
      const auto& l13 = v1.col(6);
      const auto& l23 = v1.col(7);
      const auto& l33 = v1.col(8);
      // rhs
      const auto& px = v2.col(0);
      const auto& py = v2.col(1);
      const auto& pz = v2.col(2);
      // Computation
      result.col(0)  = l11 * px + l12 * py + l13 * pz;
      result.col(1)  = l21 * px + l22 * py + l23 * pz;
      result.col(2)  = l31 * px + l32 * py + l33 * pz;
    };
    
    template <typename R, typename U1, typename U2> static inline typename std::enable_if<std::decay<U1>::type::ColsAtCompileTime == 12 && std::decay<U2>::type::ColsAtCompileTime == 12>::type evaluate(R& result, const U1& v1, const U2& v2)
    {
      TransformOpValues::evaluate_12x12(result,v1,v2);
    };
    
    template <typename R, typename U1, typename U2> static inline typename std::enable_if<std::decay<U1>::type::ColsAtCompileTime == 9 && std::decay<U2>::type::ColsAtCompileTime == 9>::type evaluate(R& result, const U1& v1, const U2& v2)
    {
      TransformOpValues::evaluate_9x9(result,v1,v2);
    };
    
    template <typename R, typename U1, typename U2> static inline typename std::enable_if<std::decay<U1>::type::ColsAtCompileTime == 12 && std::decay<U2>::type::ColsAtCompileTime == 3>::type evaluate(R& result, const U1& v1, const U2& v2)
    {
      TransformOpValues::evaluate_12x3(result,v1,v2);
    };
    
    template <typename R, typename U1, typename U2> static inline typename std::enable_if<std::decay<U1>::type::ColsAtCompileTime == 9 && std::decay<U2>::type::ColsAtCompileTime == 3>::type evaluate(R& result, const U1& v1, const U2& v2)
    {
      TransformOpValues::evaluate_9x3(result,v1,v2);
    };
    
    template <typename R, typename U1, typename U2> static inline typename std::enable_if<std::decay<U1>::type::ColsAtCompileTime == 12 && std::decay<U2>::type::ColsAtCompileTime == Dynamic>::type evaluate(R& result, const U1& v1, const U2& v2)
    {
      if (v2.cols() == 12)
        TransformOpValues::evaluate_12x12(result,v1,v2);
      else if (v2.cols() == 3)
        TransformOpValues::evaluate_12x3(result,v1,v2);
      else
        result.setZero(); // Potentially crash the binary
    };
    
    template <typename R, typename U1, typename U2> static inline typename std::enable_if<std::decay<U1>::type::ColsAtCompileTime == 9 && std::decay<U2>::type::ColsAtCompileTime == Dynamic>::type evaluate(R& result, const U1& v1, const U2& v2)
    {
      if (v2.cols() == 9)
        TransformOpValues::evaluate_9x9(result,v1,v2);
      else if (v2.cols() == 3)
        TransformOpValues::evaluate_9x3(result,v1,v2);
      else
        result.setZero(); // Potentially crash the binary
    };
    
  public:
    TransformOpValues(const V1& v1, const V2& v2) : m_V1(v1), m_V2(v2) {};
    
    template <typename R> inline void evalTo(R& result) const
    {
      return TransformOpValues::evaluate(result, this->m_V1, this->m_V2);
    };
    
    Index rows() const {return this->m_V2.rows();};
    Index cols() const {return this->m_V2.cols();};
  };
  
  // ----------------------------------------------------------------------- //
  //                         TransposeOp return value
  // ----------------------------------------------------------------------- //
  
  template<typename V> struct TransposeOpValues;

  template<typename V>
  struct traits<TransposeOpValues<V>>
  {
    using ReturnType = typename ma::math::Traits<ma::math::Array<std::decay<V>::type::ColsAtCompileTime>>::Values;
  };
  
  template<typename V>
  struct TransposeOpValues : public Eigen::ReturnByValue<TransposeOpValues<V>>
  {
    using InputType = typename std::decay<V>::type;
    using Index = typename InputType::Index;
    typename InputType::Nested m_V;
  public:
    TransposeOpValues(const V& v) : m_V(v) {};
    template <typename R> inline void evalTo(R& result) const
    {
      result.col(0) = this->m_V.col(0);
      result.col(1) = this->m_V.col(3);
      result.col(2) = this->m_V.col(6);
      result.col(3) = this->m_V.col(1);
      result.col(4) = this->m_V.col(4);
      result.col(5) = this->m_V.col(7);
      result.col(6) = this->m_V.col(2);
      result.col(7) = this->m_V.col(5);
      result.col(8) = this->m_V.col(8);
    };
    Index rows() const {return this->m_V.rows();};
    Index cols() const {return this->m_V.cols();};
  };
 
  // ----------------------------------------------------------------------- //
  //                         InverseOp return value
  // ----------------------------------------------------------------------- //
  
  template<typename V> struct InverseOpValues;

  template<typename V>
  struct traits<InverseOpValues<V>>
  {
    using ReturnType = typename ma::math::Traits<ma::math::Array<std::decay<V>::type::ColsAtCompileTime>>::Values;
  };
  
  template<typename V>
  struct InverseOpValues : public Eigen::ReturnByValue<InverseOpValues<V>>
  {
    using InputType = typename std::decay<V>::type;
    using Index = typename InputType::Index;
    typename InputType::Nested m_V;
  public:
    InverseOpValues(const V& v) : m_V(v) {};
    template <typename R> inline void evalTo(R& result) const
    {
      const auto& v11 = this->m_V.col(0);
      const auto& v21 = this->m_V.col(1);
      const auto& v31 = this->m_V.col(2);
      const auto& v12 = this->m_V.col(3);
      const auto& v22 = this->m_V.col(4);
      const auto& v32 = this->m_V.col(5);
      const auto& v13 = this->m_V.col(6);
      const auto& v23 = this->m_V.col(7);
      const auto& v33 = this->m_V.col(8);
      const auto& v14 = this->m_V.col(9);
      const auto& v24 = this->m_V.col(10);
      const auto& v34 = this->m_V.col(11);
      // result.resize(this->rows(),Eigen::NoChange);
      // Rotation (v(1:3,1:3) transposed)
      result.col(0) = v11; // i11
      result.col(1) = v12; // i21
      result.col(2) = v13; // i31
      result.col(3) = v21; // i12
      result.col(4) = v22; // i22
      result.col(5) = v23; // i32
      result.col(6) = v31; // i13
      result.col(7) = v32; // i23
      result.col(8) = v33; // i33
      // Translation (-transpose(v(1:3,1:3))*v(1:3,4))
      result.col(9)  = -v11 * v14 - v21 * v24 - v31 * v34;
      result.col(10) = -v12 * v14 - v22 * v24 - v32 * v34;
      result.col(11) = -v13 * v14 - v23 * v24 - v33 * v34;
    };
    Index rows() const {return this->m_V.rows();};
    Index cols() const {return this->m_V.cols();};
  };
  
  // ----------------------------------------------------------------------- //
  //                          DownsampleOp return value
  // ----------------------------------------------------------------------- //
  
  template<typename V> struct DownsampleOpValues;

  template<typename V>
  struct traits<DownsampleOpValues<V>>
  {
    using ReturnType = typename ma::math::Traits<ma::math::Array<std::decay<V>::type::ColsAtCompileTime>>::Values;
  };

  template<typename V>
  struct DownsampleOpValues : public Eigen::ReturnByValue<DownsampleOpValues<V>>
  {
    using InputType = typename std::decay<V>::type;
    using Index = typename InputType::Index;
    typename InputType::Nested m_V;
    Index m_Factor;
  public:
    DownsampleOpValues(const V& v, Index ratio) : m_V(v), m_Factor(ratio) {};
    template <typename R> inline void evalTo(R& result) const
    {
      for (Index i = 0, len = this->rows() ; i < len ; ++i)
        result.row(i) = this->m_V.row(i * this->m_Factor);
    };
    Index rows() const {return static_cast<Index>(this->m_V.rows() / this->m_Factor);};
    Index cols() const {return this->m_V.cols();};
  };
  
  // ----------------------------------------------------------------------- //
  //                         EulerAnglesOp return value
  // ----------------------------------------------------------------------- //

  // Extract the coefficients index to use
  template <typename T>
  inline void rotation_matrix_to_euler_order(typename MatrixBase<T>::Index& i, typename MatrixBase<T>::Index& j, typename MatrixBase<T>::Index& k, typename MatrixBase<T>::Scalar& f, typename MatrixBase<T>::Index a0, typename MatrixBase<T>::Index a1)
  {
    const typename MatrixBase<T>::Index odd = ((a0 + 1) % 3 == a1) ? 0 : 1;
    i = a0;
    j = (a0 + 1 + odd) % 3;
    k = (a0 + 2 - odd) % 3;
    f = (!odd ? -1.0 : 1.0);
  }
  
  // ABA
  template <typename T>
  inline Matrix<typename MatrixBase<T>::Scalar,3,1> rotation_matrix_to_euler_sym(const T& rot, typename MatrixBase<T>::Index i, typename MatrixBase<T>::Index j, typename MatrixBase<T>::Index k, typename MatrixBase<T>::Scalar f)
  {
    using std::atan2;
    using Scalar = typename MatrixBase<T>::Scalar;
    Matrix<Scalar,3,1> res;
    Scalar s = Eigen::Matrix<Scalar,2,1>(rot.coeff(j,i), rot.coeff(k,i)).norm();
    res[1] = atan2(s, rot.coeff(i,i));
    if (s > NumTraits<Scalar>::dummy_precision())
    {
      res[0] = f * atan2(rot.coeff(j,i), rot.coeff(k,i));
      res[2] = f * atan2(rot.coeff(i,j),-rot.coeff(i,k));
    }
    else
    {
      res[0] = 0.0;
      res[2] = f * (rot.coeff(i,i) > 0 ? 1 : -1) * atan2(-rot.coeff(k,j), rot.coeff(j,j));
    }
    return res;
  }
  
  // ABC
  template <typename T>
  inline Matrix<typename MatrixBase<T>::Scalar,3,1> rotation_matrix_to_euler_unsym(const T& rot, typename MatrixBase<T>::Index i, typename MatrixBase<T>::Index j, typename MatrixBase<T>::Index k, typename MatrixBase<T>::Scalar f)
  {
    using std::atan2;
    using Scalar = typename MatrixBase<T>::Scalar;
    Matrix<Scalar,3,1> res;
    double c = Eigen::Matrix<Scalar,2,1>(rot.coeff(i,i), rot.coeff(i,j)).norm();
    res[1] = f * atan2(-rot.coeff(i,k), c);
    if (c > NumTraits<Scalar>::dummy_precision())
    {
      res[0] = f * atan2(rot.coeff(j,k), rot.coeff(k,k));
      res[2] = f * atan2(rot.coeff(i,j), rot.coeff(i,i));
    }
    else
    {
      res[0] = 0.0;
      res[2] = f * (rot.coeff(i,k) > 0 ? 1 : -1) * atan2(-rot.coeff(k,j), rot.coeff(j,j));
    }
    return res;
  }
  
  template<typename V> struct EulerAnglesOpValues;

  template<typename V>
  struct traits<EulerAnglesOpValues<V>>
  {
    using ReturnType = typename ma::math::Traits<ma::math::Array<3>>::Values;
  };
  
  template<typename V>
  struct EulerAnglesOpValues : public Eigen::ReturnByValue<EulerAnglesOpValues<V>>
  {
    using InputType = typename std::decay<V>::type;
    using Index = typename InputType::Index;
    using Scalar = typename InputType::Scalar;
    typename InputType::Nested m_V;
    const Index m_A0;
    const Index m_A1;
    const Index m_A2;
  public:
    EulerAnglesOpValues(const V& v, const unsigned& a0, const unsigned& a1, const unsigned& a2) : m_V(v), m_A0(a0), m_A1(a1), m_A2(a2) {};
    template <typename R> inline void evalTo(R& result) const
    {
      using MapStride = Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>;
      using MapMatrix33 = Eigen::Map<const Eigen::Matrix<double,3,3>, Eigen::Unaligned, MapStride>;
      const Index rows = this->m_V.rows();
      const Eigen::Array<double,Eigen::Dynamic,9> values = this->m_V.block(0,0,rows,9);
      // result.resize(rows, Eigen::NoChange);
      const MapStride stride(3*rows,rows);
      MapMatrix33 rot(nullptr,stride);
      Index i = 0, j = 0, k = 0;
      Scalar f = Scalar(0);
      rotation_matrix_to_euler_order<R>(i,j,k,f,this->m_A0,this->m_A1);
      // ABA
      if (this->m_A0 == this->m_A2)
      {
        for (Index idx = 0 ; idx < rows ; ++idx)
        {
          // See http://eigen.tuxfamily.org/dox/group__TutorialMapClass.html (section Changing the mapped array) for the syntax
          new (&rot) MapMatrix33(values.data()+idx,stride);
          result.row(idx) = rotation_matrix_to_euler_sym(rot, i, j, k, f);
        }
      }
      // ABC
      else
      {
        for (Index idx = 0 ; idx < rows ; ++idx)
        {
          // See http://eigen.tuxfamily.org/dox/group__TutorialMapClass.html (section Changing the mapped array) for the syntax
          new (&rot) MapMatrix33(values.data()+idx,stride);
          result.row(idx) = rotation_matrix_to_euler_unsym(rot, i, j, k, f);
        }
      }
    };
    Index rows() const {return this->m_V.rows();};
    Index cols() const {return 3;};
  };
  
  // ----------------------------------------------------------------------- //
  //                        SkewReduxOp return value
  // ----------------------------------------------------------------------- //
  
  template<typename V> struct SkewReduxOpValues;

  template<typename V>
  struct traits<SkewReduxOpValues<V>>
  {
    using ReturnType = typename ma::math::Traits<ma::math::Array<3>>::Values;
  };
  
  template<typename V>
  struct SkewReduxOpValues : public Eigen::ReturnByValue<SkewReduxOpValues<V>>
  {
    using InputType = typename std::decay<V>::type;
    using Index = typename InputType::Index;
    using Scalar = typename InputType::Scalar;
    typename InputType::Nested m_V;
  public:
    SkewReduxOpValues(const V& v) : m_V(v) {};
    template <typename R> inline void evalTo(R& result) const
    {
      result.col(0) = this->m_V.col(5);
      result.col(1) = this->m_V.col(2) * -1.0;
      result.col(2) = this->m_V.col(1);
    };
    Index rows() const {return this->m_V.rows();};
    Index cols() const {return 3;};
  };
  
  // ----------------------------------------------------------------------- //
  //                        DerivativeOp return value
  // ----------------------------------------------------------------------- //
  
  // NOTE: All finite difference coefficients came from Wikipedia: https://en.wikipedia.org/wiki/Finite_difference_coefficient
  
  template <unsigned Order>
  struct FiniteDifferenceCoefficents
  {};
  
  template <>
  struct FiniteDifferenceCoefficents<1>
  {
    static _OPENMA_CONSTEXPR unsigned minimum_window_length() {return 3;};
    static Eigen::Array<double,3,1> central_coefficients() {Eigen::Array<double,3,1> arr; arr << -1./2., 0., 1./2.; return arr;};
    static Eigen::Array<double,3,1> forward_coefficients() {Eigen::Array<double,3,1> arr; arr << -3./2., 2., -1./2.; return arr;};
    static Eigen::Array<double,3,1> backward_coefficients() {return -forward_coefficients().reverse();};
  };
  
  template <>
  struct FiniteDifferenceCoefficents<2>
  {
    static _OPENMA_CONSTEXPR unsigned minimum_window_length() {return 4;};
    static Eigen::Array<double,3,1> central_coefficients() {Eigen::Array<double,3,1> arr; arr << 1., -2., 1.; return arr;};
    static Eigen::Array<double,4,1> forward_coefficients() {Eigen::Array<double,4,1> arr; arr << 2., -5., 4., -1.; return arr;};
    static Eigen::Array<double,4,1> backward_coefficients() {return forward_coefficients().reverse();};
  };
  
  template<typename V, unsigned O> struct DerivativeOpValues;

  template<typename V, unsigned O>
  struct traits<DerivativeOpValues<V,O>>
  {
    using ReturnType = typename ma::math::Traits<ma::math::Array<std::decay<V>::type::ColsAtCompileTime>>::Values;
  };
  
  template<typename V, unsigned O>
  struct DerivativeOpValues : public Eigen::ReturnByValue<DerivativeOpValues<V,O>>
  {
    using InputType = typename std::decay<V>::type;
    using Index = typename InputType::Index;
    typename InputType::Nested m_V;
    const std::vector<std::array<unsigned,2>>& m_W;
    double m_H;
    
  public:
    DerivativeOpValues(const V& v, const std::vector<std::array<unsigned,2>>& w, double h) : m_V(v), m_W(w), m_H(h) {};
    template <typename R> inline void evalTo(R& result) const
    {
      const auto& cc = FiniteDifferenceCoefficents<O>::central_coefficients();
      const auto& fc = FiniteDifferenceCoefficents<O>::forward_coefficients();
      const auto& bc = FiniteDifferenceCoefficents<O>::backward_coefficients();
      using CC = typename std::decay<decltype(cc)>::type;
      using FC = typename std::decay<decltype(fc)>::type;
      using BC = typename std::decay<decltype(bc)>::type;
      _OPENMA_CONSTEXPR unsigned chs = CC::RowsAtCompileTime / 2;
      double ph = std::pow(this->m_H, O);
      result.setZero();
      for (const auto& window : this->m_W)
      {
        unsigned istart = window[0];
        unsigned ilen = window[1];
        
        // Begin (forward difference)
        for (unsigned i = istart, len = istart + chs; i < len ; ++i)
        {
          result.row(i) = (this->m_V.template middleRows<FC::RowsAtCompileTime>(i).colwise() * fc).colwise().sum() / ph;
        }
        
        // Middle (central difference)
        for (unsigned i = istart + chs, len = (istart + ilen - chs) ; i < len ; ++i)
        {
          result.row(i) = (this->m_V.template middleRows<CC::RowsAtCompileTime>(i-chs).colwise() * cc).colwise().sum() / ph;
        }
          
        // End (backward difference)
        for (unsigned i = (istart + ilen - chs), len = istart + ilen ; i < len ; ++i)
        {
          result.row(i) = (this->m_V.template middleRows<BC::RowsAtCompileTime>(i-BC::RowsAtCompileTime+1).colwise() * bc).colwise().sum() / ph;
        }
      }
    };
    Index rows() const {return this->m_V.rows();};
    Index cols() const {return this->m_V.cols();};
  };
};
};

#endif // DOXYGEN_SHOULD_SKIP_THIS

#endif // __openma_math_returnbyvalue_h