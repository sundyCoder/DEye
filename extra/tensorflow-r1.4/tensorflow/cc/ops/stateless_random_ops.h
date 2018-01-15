// This file is MACHINE GENERATED! Do not edit.

#ifndef E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_STATELESS_RANDOM_OPS_H_
#define E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_STATELESS_RANDOM_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup stateless_random_ops Stateless Random Ops
/// @{

/// Outputs deterministic pseudorandom values from a normal distribution.
///
/// The generated values will have mean 0 and standard deviation 1.
///
/// The outputs are a deterministic function of `shape` and `seed`.
///
/// Arguments:
/// * scope: A Scope object
/// * shape: The shape of the output tensor.
/// * seed: 2 seeds (shape [2]).
///
/// Optional attributes (see `Attrs`):
/// * dtype: The type of the output.
///
/// Returns:
/// * `Output`: Random values with specified shape.
class StatelessRandomNormal {
 public:
  /// Optional attribute setters for StatelessRandomNormal
  struct Attrs {
    /// The type of the output.
    ///
    /// Defaults to DT_FLOAT
    Attrs Dtype(DataType x) {
      Attrs ret = *this;
      ret.dtype_ = x;
      return ret;
    }

    DataType dtype_ = DT_FLOAT;
  };
  StatelessRandomNormal(const ::tensorflow::Scope& scope, ::tensorflow::Input
                      shape, ::tensorflow::Input seed);
  StatelessRandomNormal(const ::tensorflow::Scope& scope, ::tensorflow::Input
                      shape, ::tensorflow::Input seed, const
                      StatelessRandomNormal::Attrs& attrs);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  static Attrs Dtype(DataType x) {
    return Attrs().Dtype(x);
  }

  ::tensorflow::Output output;
};

/// Outputs deterministic pseudorandom random values from a uniform distribution.
///
/// The generated values follow a uniform distribution in the range `[0, 1)`. The
/// lower bound 0 is included in the range, while the upper bound 1 is excluded.
///
/// The outputs are a deterministic function of `shape` and `seed`.
///
/// Arguments:
/// * scope: A Scope object
/// * shape: The shape of the output tensor.
/// * seed: 2 seeds (shape [2]).
///
/// Optional attributes (see `Attrs`):
/// * dtype: The type of the output.
///
/// Returns:
/// * `Output`: Random values with specified shape.
class StatelessRandomUniform {
 public:
  /// Optional attribute setters for StatelessRandomUniform
  struct Attrs {
    /// The type of the output.
    ///
    /// Defaults to DT_FLOAT
    Attrs Dtype(DataType x) {
      Attrs ret = *this;
      ret.dtype_ = x;
      return ret;
    }

    DataType dtype_ = DT_FLOAT;
  };
  StatelessRandomUniform(const ::tensorflow::Scope& scope, ::tensorflow::Input
                       shape, ::tensorflow::Input seed);
  StatelessRandomUniform(const ::tensorflow::Scope& scope, ::tensorflow::Input
                       shape, ::tensorflow::Input seed, const
                       StatelessRandomUniform::Attrs& attrs);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  static Attrs Dtype(DataType x) {
    return Attrs().Dtype(x);
  }

  ::tensorflow::Output output;
};

/// Outputs deterministic pseudorandom values from a truncated normal distribution.
///
/// The generated values follow a normal distribution with mean 0 and standard
/// deviation 1, except that values whose magnitude is more than 2 standard
/// deviations from the mean are dropped and re-picked.
///
/// The outputs are a deterministic function of `shape` and `seed`.
///
/// Arguments:
/// * scope: A Scope object
/// * shape: The shape of the output tensor.
/// * seed: 2 seeds (shape [2]).
///
/// Optional attributes (see `Attrs`):
/// * dtype: The type of the output.
///
/// Returns:
/// * `Output`: Random values with specified shape.
class StatelessTruncatedNormal {
 public:
  /// Optional attribute setters for StatelessTruncatedNormal
  struct Attrs {
    /// The type of the output.
    ///
    /// Defaults to DT_FLOAT
    Attrs Dtype(DataType x) {
      Attrs ret = *this;
      ret.dtype_ = x;
      return ret;
    }

    DataType dtype_ = DT_FLOAT;
  };
  StatelessTruncatedNormal(const ::tensorflow::Scope& scope, ::tensorflow::Input
                         shape, ::tensorflow::Input seed);
  StatelessTruncatedNormal(const ::tensorflow::Scope& scope, ::tensorflow::Input
                         shape, ::tensorflow::Input seed, const
                         StatelessTruncatedNormal::Attrs& attrs);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  static Attrs Dtype(DataType x) {
    return Attrs().Dtype(x);
  }

  ::tensorflow::Output output;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_STATELESS_RANDOM_OPS_H_
