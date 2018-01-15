// This file is MACHINE GENERATED! Do not edit.

#ifndef E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_FUNCTIONAL_OPS_H_
#define E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_FUNCTIONAL_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup functional_ops Functional Ops
/// @{

/// Runs function `f` on a remote device indicated by `target`.
///
/// Arguments:
/// * scope: A Scope object
/// * target: A fully specified device name where we want to run the function.
/// * args: A list of arguments for the function.
/// * Tout: The type list for the return values.
/// * f: The function to run remotely.
///
/// Returns:
/// * `OutputList`: A list of return values.
class RemoteCall {
 public:
  RemoteCall(const ::tensorflow::Scope& scope, ::tensorflow::Input target,
           ::tensorflow::InputList args, const DataTypeSlice& Tout, const
           NameAttrList& f);
  ::tensorflow::Output operator[](size_t index) const { return output[index]; }


  ::tensorflow::OutputList output;
};

/// Computes the gradient function for function f via backpropagation.
///
/// Arguments:
/// * scope: A Scope object
/// * input: a list of input tensors of size N + M;
/// * Tout: the type list for the input list.
/// * f: The function we want to compute the gradient for.
///
/// The function 'f' must be a numerical function which takes N inputs and
/// produces M outputs. Its gradient function 'g', which is computed by
/// this SymbolicGradient op is a function taking N + M inputs and
/// produces N outputs.
///
/// I.e. if we have
///    (y1, y2, ..., y_M) = f(x1, x2, ..., x_N),
/// then, g is
///    (dL/dx1, dL/dx2, ..., dL/dx_N) = g(x1, x2, ..., x_N,
///                                      dL/dy1, dL/dy2, ..., dL/dy_M),
///
/// where L is a scalar-value function of (x1, x2, ..., xN) (e.g., the
/// loss function). dL/dx_i is the partial derivative of L with respect
/// to x_i.
///
/// (Needs some math expert to say the comment above better.)
///
/// Returns:
/// * `OutputList`: a list of output tensors of size N;
class SymbolicGradient {
 public:
  SymbolicGradient(const ::tensorflow::Scope& scope, ::tensorflow::InputList
                 input, const DataTypeSlice& Tout, const NameAttrList& f);
  ::tensorflow::Output operator[](size_t index) const { return output[index]; }


  ::tensorflow::OutputList output;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_FUNCTIONAL_OPS_H_
