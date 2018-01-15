// This file is MACHINE GENERATED! Do not edit.

#ifndef E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SET_OPS_H_
#define E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SET_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup set_ops Set Ops
/// @{

/// Applies set operation along last dimension of 2 `Tensor` inputs.
///
/// See SetOperationOp::SetOperationFromContext for values of `set_operation`.
///
/// Output `result` is a `SparseTensor` represented by `result_indices`,
/// `result_values`, and `result_shape`. For `set1` and `set2` ranked `n`, this
/// has rank `n` and the same 1st `n-1` dimensions as `set1` and `set2`. The `nth`
/// dimension contains the result of `set_operation` applied to the corresponding
/// `[0...n-1]` dimension of `set`.
///
/// Arguments:
/// * scope: A Scope object
/// * set1: `Tensor` with rank `n`. 1st `n-1` dimensions must be the same as `set2`.
/// Dimension `n` contains values in a set, duplicates are allowed but ignored.
/// * set2: `Tensor` with rank `n`. 1st `n-1` dimensions must be the same as `set1`.
/// Dimension `n` contains values in a set, duplicates are allowed but ignored.
///
/// Returns:
/// * `Output` result_indices: 2D indices of a `SparseTensor`.
/// * `Output` result_values: 1D values of a `SparseTensor`.
/// * `Output` result_shape: 1D `Tensor` shape of a `SparseTensor`. `result_shape[0...n-1]` is
/// the same as the 1st `n-1` dimensions of `set1` and `set2`, `result_shape[n]`
/// is the max result set size across all `0...n-1` dimensions.
class DenseToDenseSetOperation {
 public:
  /// Optional attribute setters for DenseToDenseSetOperation
  struct Attrs {
    /// Defaults to true
    Attrs ValidateIndices(bool x) {
      Attrs ret = *this;
      ret.validate_indices_ = x;
      return ret;
    }

    bool validate_indices_ = true;
  };
  DenseToDenseSetOperation(const ::tensorflow::Scope& scope, ::tensorflow::Input
                         set1, ::tensorflow::Input set2, StringPiece
                         set_operation);
  DenseToDenseSetOperation(const ::tensorflow::Scope& scope, ::tensorflow::Input
                         set1, ::tensorflow::Input set2, StringPiece
                         set_operation, const DenseToDenseSetOperation::Attrs&
                         attrs);

  static Attrs ValidateIndices(bool x) {
    return Attrs().ValidateIndices(x);
  }

  ::tensorflow::Output result_indices;
  ::tensorflow::Output result_values;
  ::tensorflow::Output result_shape;
};

/// Applies set operation along last dimension of `Tensor` and `SparseTensor`.
///
/// See SetOperationOp::SetOperationFromContext for values of `set_operation`.
///
/// Input `set2` is a `SparseTensor` represented by `set2_indices`, `set2_values`,
/// and `set2_shape`. For `set2` ranked `n`, 1st `n-1` dimensions must be the same
/// as `set1`. Dimension `n` contains values in a set, duplicates are allowed but
/// ignored.
///
/// If `validate_indices` is `True`, this op validates the order and range of `set2`
/// indices.
///
/// Output `result` is a `SparseTensor` represented by `result_indices`,
/// `result_values`, and `result_shape`. For `set1` and `set2` ranked `n`, this
/// has rank `n` and the same 1st `n-1` dimensions as `set1` and `set2`. The `nth`
/// dimension contains the result of `set_operation` applied to the corresponding
/// `[0...n-1]` dimension of `set`.
///
/// Arguments:
/// * scope: A Scope object
/// * set1: `Tensor` with rank `n`. 1st `n-1` dimensions must be the same as `set2`.
/// Dimension `n` contains values in a set, duplicates are allowed but ignored.
/// * set2_indices: 2D `Tensor`, indices of a `SparseTensor`. Must be in row-major
/// order.
/// * set2_values: 1D `Tensor`, values of a `SparseTensor`. Must be in row-major
/// order.
/// * set2_shape: 1D `Tensor`, shape of a `SparseTensor`. `set2_shape[0...n-1]` must
/// be the same as the 1st `n-1` dimensions of `set1`, `result_shape[n]` is the
/// max set size across `n-1` dimensions.
///
/// Returns:
/// * `Output` result_indices: 2D indices of a `SparseTensor`.
/// * `Output` result_values: 1D values of a `SparseTensor`.
/// * `Output` result_shape: 1D `Tensor` shape of a `SparseTensor`. `result_shape[0...n-1]` is
/// the same as the 1st `n-1` dimensions of `set1` and `set2`, `result_shape[n]`
/// is the max result set size across all `0...n-1` dimensions.
class DenseToSparseSetOperation {
 public:
  /// Optional attribute setters for DenseToSparseSetOperation
  struct Attrs {
    /// Defaults to true
    Attrs ValidateIndices(bool x) {
      Attrs ret = *this;
      ret.validate_indices_ = x;
      return ret;
    }

    bool validate_indices_ = true;
  };
  DenseToSparseSetOperation(const ::tensorflow::Scope& scope, ::tensorflow::Input
                          set1, ::tensorflow::Input set2_indices,
                          ::tensorflow::Input set2_values, ::tensorflow::Input
                          set2_shape, StringPiece set_operation);
  DenseToSparseSetOperation(const ::tensorflow::Scope& scope, ::tensorflow::Input
                          set1, ::tensorflow::Input set2_indices,
                          ::tensorflow::Input set2_values, ::tensorflow::Input
                          set2_shape, StringPiece set_operation, const
                          DenseToSparseSetOperation::Attrs& attrs);

  static Attrs ValidateIndices(bool x) {
    return Attrs().ValidateIndices(x);
  }

  ::tensorflow::Output result_indices;
  ::tensorflow::Output result_values;
  ::tensorflow::Output result_shape;
};

/// Number of unique elements along last dimension of input `set`.
///
/// Input `set` is a `SparseTensor` represented by `set_indices`, `set_values`,
/// and `set_shape`. The last dimension contains values in a set, duplicates are
/// allowed but ignored.
///
/// If `validate_indices` is `True`, this op validates the order and range of `set`
/// indices.
///
/// Arguments:
/// * scope: A Scope object
/// * set_indices: 2D `Tensor`, indices of a `SparseTensor`.
/// * set_values: 1D `Tensor`, values of a `SparseTensor`.
/// * set_shape: 1D `Tensor`, shape of a `SparseTensor`.
///
/// Returns:
/// * `Output`: For `set` ranked `n`, this is a `Tensor` with rank `n-1`, and the same 1st
/// `n-1` dimensions as `set`. Each value is the number of unique elements in
/// the corresponding `[0...n-1]` dimension of `set`.
class SetSize {
 public:
  /// Optional attribute setters for SetSize
  struct Attrs {
    /// Defaults to true
    Attrs ValidateIndices(bool x) {
      Attrs ret = *this;
      ret.validate_indices_ = x;
      return ret;
    }

    bool validate_indices_ = true;
  };
  SetSize(const ::tensorflow::Scope& scope, ::tensorflow::Input set_indices,
        ::tensorflow::Input set_values, ::tensorflow::Input set_shape);
  SetSize(const ::tensorflow::Scope& scope, ::tensorflow::Input set_indices,
        ::tensorflow::Input set_values, ::tensorflow::Input set_shape, const
        SetSize::Attrs& attrs);
  operator ::tensorflow::Output() const { return size; }
  operator ::tensorflow::Input() const { return size; }
  ::tensorflow::Node* node() const { return size.node(); }

  static Attrs ValidateIndices(bool x) {
    return Attrs().ValidateIndices(x);
  }

  ::tensorflow::Output size;
};

/// Applies set operation along last dimension of 2 `SparseTensor` inputs.
///
/// See SetOperationOp::SetOperationFromContext for values of `set_operation`.
///
/// If `validate_indices` is `True`, `SparseToSparseSetOperation` validates the
/// order and range of `set1` and `set2` indices.
///
/// Input `set1` is a `SparseTensor` represented by `set1_indices`, `set1_values`,
/// and `set1_shape`. For `set1` ranked `n`, 1st `n-1` dimensions must be the same
/// as `set2`. Dimension `n` contains values in a set, duplicates are allowed but
/// ignored.
///
/// Input `set2` is a `SparseTensor` represented by `set2_indices`, `set2_values`,
/// and `set2_shape`. For `set2` ranked `n`, 1st `n-1` dimensions must be the same
/// as `set1`. Dimension `n` contains values in a set, duplicates are allowed but
/// ignored.
///
/// If `validate_indices` is `True`, this op validates the order and range of `set1`
/// and `set2` indices.
///
/// Output `result` is a `SparseTensor` represented by `result_indices`,
/// `result_values`, and `result_shape`. For `set1` and `set2` ranked `n`, this
/// has rank `n` and the same 1st `n-1` dimensions as `set1` and `set2`. The `nth`
/// dimension contains the result of `set_operation` applied to the corresponding
/// `[0...n-1]` dimension of `set`.
///
/// Arguments:
/// * scope: A Scope object
/// * set1_indices: 2D `Tensor`, indices of a `SparseTensor`. Must be in row-major
/// order.
/// * set1_values: 1D `Tensor`, values of a `SparseTensor`. Must be in row-major
/// order.
/// * set1_shape: 1D `Tensor`, shape of a `SparseTensor`. `set1_shape[0...n-1]` must
/// be the same as `set2_shape[0...n-1]`, `set1_shape[n]` is the
/// max set size across `0...n-1` dimensions.
/// * set2_indices: 2D `Tensor`, indices of a `SparseTensor`. Must be in row-major
/// order.
/// * set2_values: 1D `Tensor`, values of a `SparseTensor`. Must be in row-major
/// order.
/// * set2_shape: 1D `Tensor`, shape of a `SparseTensor`. `set2_shape[0...n-1]` must
/// be the same as `set1_shape[0...n-1]`, `set2_shape[n]` is the
/// max set size across `0...n-1` dimensions.
///
/// Returns:
/// * `Output` result_indices: 2D indices of a `SparseTensor`.
/// * `Output` result_values: 1D values of a `SparseTensor`.
/// * `Output` result_shape: 1D `Tensor` shape of a `SparseTensor`. `result_shape[0...n-1]` is
/// the same as the 1st `n-1` dimensions of `set1` and `set2`, `result_shape[n]`
/// is the max result set size across all `0...n-1` dimensions.
class SparseToSparseSetOperation {
 public:
  /// Optional attribute setters for SparseToSparseSetOperation
  struct Attrs {
    /// Defaults to true
    Attrs ValidateIndices(bool x) {
      Attrs ret = *this;
      ret.validate_indices_ = x;
      return ret;
    }

    bool validate_indices_ = true;
  };
  SparseToSparseSetOperation(const ::tensorflow::Scope& scope,
                           ::tensorflow::Input set1_indices,
                           ::tensorflow::Input set1_values, ::tensorflow::Input
                           set1_shape, ::tensorflow::Input set2_indices,
                           ::tensorflow::Input set2_values, ::tensorflow::Input
                           set2_shape, StringPiece set_operation);
  SparseToSparseSetOperation(const ::tensorflow::Scope& scope,
                           ::tensorflow::Input set1_indices,
                           ::tensorflow::Input set1_values, ::tensorflow::Input
                           set1_shape, ::tensorflow::Input set2_indices,
                           ::tensorflow::Input set2_values, ::tensorflow::Input
                           set2_shape, StringPiece set_operation, const
                           SparseToSparseSetOperation::Attrs& attrs);

  static Attrs ValidateIndices(bool x) {
    return Attrs().ValidateIndices(x);
  }

  ::tensorflow::Output result_indices;
  ::tensorflow::Output result_values;
  ::tensorflow::Output result_shape;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SET_OPS_H_
