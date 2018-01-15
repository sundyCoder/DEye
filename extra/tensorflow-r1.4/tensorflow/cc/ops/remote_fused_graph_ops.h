// This file is MACHINE GENERATED! Do not edit.

#ifndef E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_REMOTE_FUSED_GRAPH_OPS_H_
#define E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_REMOTE_FUSED_GRAPH_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup remote_fused_graph_ops Remote Fused Graph Ops
/// @{

/// Execute a sub graph on a remote processor.
///
/// The graph specifications(such as graph itself, input tensors and output names)
/// are stored as a serialized protocol buffer of RemoteFusedGraphExecuteInfo
/// as serialized_remote_fused_graph_execute_info.
/// The specifications will be passed to a dedicated registered
/// remote fused graph executor.  The executor will send the graph specifications
/// to a remote processor and execute that graph.  The execution results
/// will be passed to consumer nodes as outputs of this node.
///
/// Arguments:
/// * scope: A Scope object
/// * inputs: Arbitrary number of tensors with arbitrary data types
/// * serialized_remote_fused_graph_execute_info: Serialized protocol buffer
/// of RemoteFusedGraphExecuteInfo which contains graph specifications.
///
/// Returns:
/// * `OutputList`: Arbitrary number of tensors with arbitrary data types
class RemoteFusedGraphExecute {
 public:
  RemoteFusedGraphExecute(const ::tensorflow::Scope& scope,
                        ::tensorflow::InputList inputs, const DataTypeSlice&
                        Toutputs, StringPiece
                        serialized_remote_fused_graph_execute_info);
  ::tensorflow::Output operator[](size_t index) const { return outputs[index]; }


  ::tensorflow::OutputList outputs;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_REMOTE_FUSED_GRAPH_OPS_H_
