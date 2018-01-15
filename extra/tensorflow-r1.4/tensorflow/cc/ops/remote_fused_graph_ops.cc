// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/remote_fused_graph_ops.h"

namespace tensorflow {
namespace ops {

RemoteFusedGraphExecute::RemoteFusedGraphExecute(const ::tensorflow::Scope&
                                                 scope, ::tensorflow::InputList
                                                 inputs, const DataTypeSlice&
                                                 Toutputs, StringPiece
                                                 serialized_remote_fused_graph_execute_info) {
  if (!scope.ok()) return;
  auto _inputs = ::tensorflow::ops::AsNodeOutList(scope, inputs);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("RemoteFusedGraphExecute");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "RemoteFusedGraphExecute")
                     .Input(_inputs)
                     .Attr("Toutputs", Toutputs)
                     .Attr("serialized_remote_fused_graph_execute_info", serialized_remote_fused_graph_execute_info)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  for (int32 i = 0; i < ret->num_outputs(); ++i)
    this->outputs.push_back(Output(ret, i));
}

/// @}

}  // namespace ops
}  // namespace tensorflow
