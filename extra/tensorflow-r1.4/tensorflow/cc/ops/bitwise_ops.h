// This file is MACHINE GENERATED! Do not edit.

#ifndef E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_BITWISE_OPS_H_
#define E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_BITWISE_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup bitwise_ops Bitwise Ops
/// @{

/// Elementwise computes the bitwise AND of `x` and `y`.
///
/// The result will have those bits set, that are set in both `x` and `y`. The
/// computation is performed on the underlying representations of `x` and `y`.
///
/// Arguments:
/// * scope: A Scope object
///
/// Returns:
/// * `Output`: The z tensor.
class BitwiseAnd {
 public:
  BitwiseAnd(const ::tensorflow::Scope& scope, ::tensorflow::Input x,
           ::tensorflow::Input y);
  operator ::tensorflow::Output() const { return z; }
  operator ::tensorflow::Input() const { return z; }
  ::tensorflow::Node* node() const { return z.node(); }

  ::tensorflow::Output z;
};

/// Elementwise computes the bitwise OR of `x` and `y`.
///
/// The result will have those bits set, that are set in `x`, `y` or both. The
/// computation is performed on the underlying representations of `x` and `y`.
///
/// Arguments:
/// * scope: A Scope object
///
/// Returns:
/// * `Output`: The z tensor.
class BitwiseOr {
 public:
  BitwiseOr(const ::tensorflow::Scope& scope, ::tensorflow::Input x,
          ::tensorflow::Input y);
  operator ::tensorflow::Output() const { return z; }
  operator ::tensorflow::Input() const { return z; }
  ::tensorflow::Node* node() const { return z.node(); }

  ::tensorflow::Output z;
};

/// Elementwise computes the bitwise XOR of `x` and `y`.
///
/// The result will have those bits set, that are different in `x` and `y`. The
/// computation is performed on the underlying representations of `x` and `y`.
///
/// Arguments:
/// * scope: A Scope object
///
/// Returns:
/// * `Output`: The z tensor.
class BitwiseXor {
 public:
  BitwiseXor(const ::tensorflow::Scope& scope, ::tensorflow::Input x,
           ::tensorflow::Input y);
  operator ::tensorflow::Output() const { return z; }
  operator ::tensorflow::Input() const { return z; }
  ::tensorflow::Node* node() const { return z.node(); }

  ::tensorflow::Output z;
};

/// Flips all bits elementwise.
///
/// The result will have exactly those bits set, that are not set in `x`. The
/// computation is performed on the underlying representation of x.
///
/// Arguments:
/// * scope: A Scope object
///
/// Returns:
/// * `Output`: The y tensor.
class Invert {
 public:
  Invert(const ::tensorflow::Scope& scope, ::tensorflow::Input x);
  operator ::tensorflow::Output() const { return y; }
  operator ::tensorflow::Input() const { return y; }
  ::tensorflow::Node* node() const { return y.node(); }

  ::tensorflow::Output y;
};

/// Computes element-wise population count (a.k.a. popcount, bitsum, bitcount).
///
/// For each entry in `x`, calculates the number of `1` (on) bits in the binary
/// representation of that entry.
///
/// **NOTE**: It is more efficient to first `tf.bitcast` your tensors into
/// `int32` or `int64` and perform the bitcount on the result, than to feed in
/// 8- or 16-bit inputs and then aggregate the resulting counts.
///
/// Arguments:
/// * scope: A Scope object
///
/// Returns:
/// * `Output`: The y tensor.
class PopulationCount {
 public:
  PopulationCount(const ::tensorflow::Scope& scope, ::tensorflow::Input x);
  operator ::tensorflow::Output() const { return y; }
  operator ::tensorflow::Input() const { return y; }
  ::tensorflow::Node* node() const { return y.node(); }

  ::tensorflow::Output y;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_BITWISE_OPS_H_
