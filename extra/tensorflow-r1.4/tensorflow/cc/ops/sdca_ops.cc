// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/sdca_ops.h"

namespace tensorflow {
namespace ops {

SdcaFprint::SdcaFprint(const ::tensorflow::Scope& scope, ::tensorflow::Input
                       input) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SdcaFprint");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SdcaFprint")
                     .Input(_input)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

SdcaOptimizer::SdcaOptimizer(const ::tensorflow::Scope& scope,
                             ::tensorflow::InputList sparse_example_indices,
                             ::tensorflow::InputList sparse_feature_indices,
                             ::tensorflow::InputList sparse_feature_values,
                             ::tensorflow::InputList dense_features,
                             ::tensorflow::Input example_weights,
                             ::tensorflow::Input example_labels,
                             ::tensorflow::InputList sparse_indices,
                             ::tensorflow::InputList sparse_weights,
                             ::tensorflow::InputList dense_weights,
                             ::tensorflow::Input example_state_data,
                             StringPiece loss_type, float l1, float l2, int64
                             num_loss_partitions, int64 num_inner_iterations,
                             const SdcaOptimizer::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _sparse_example_indices = ::tensorflow::ops::AsNodeOutList(scope, sparse_example_indices);
  if (!scope.ok()) return;
  auto _sparse_feature_indices = ::tensorflow::ops::AsNodeOutList(scope, sparse_feature_indices);
  if (!scope.ok()) return;
  auto _sparse_feature_values = ::tensorflow::ops::AsNodeOutList(scope, sparse_feature_values);
  if (!scope.ok()) return;
  auto _dense_features = ::tensorflow::ops::AsNodeOutList(scope, dense_features);
  if (!scope.ok()) return;
  auto _example_weights = ::tensorflow::ops::AsNodeOut(scope, example_weights);
  if (!scope.ok()) return;
  auto _example_labels = ::tensorflow::ops::AsNodeOut(scope, example_labels);
  if (!scope.ok()) return;
  auto _sparse_indices = ::tensorflow::ops::AsNodeOutList(scope, sparse_indices);
  if (!scope.ok()) return;
  auto _sparse_weights = ::tensorflow::ops::AsNodeOutList(scope, sparse_weights);
  if (!scope.ok()) return;
  auto _dense_weights = ::tensorflow::ops::AsNodeOutList(scope, dense_weights);
  if (!scope.ok()) return;
  auto _example_state_data = ::tensorflow::ops::AsNodeOut(scope, example_state_data);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SdcaOptimizer");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SdcaOptimizer")
                     .Input(_sparse_example_indices)
                     .Input(_sparse_feature_indices)
                     .Input(_sparse_feature_values)
                     .Input(_dense_features)
                     .Input(_example_weights)
                     .Input(_example_labels)
                     .Input(_sparse_indices)
                     .Input(_sparse_weights)
                     .Input(_dense_weights)
                     .Input(_example_state_data)
                     .Attr("loss_type", loss_type)
                     .Attr("adaptative", attrs.adaptative_)
                     .Attr("l1", l1)
                     .Attr("l2", l2)
                     .Attr("num_loss_partitions", num_loss_partitions)
                     .Attr("num_inner_iterations", num_inner_iterations)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  ::tensorflow::NameRangeMap _outputs_range;
  ::tensorflow::Status _status_ = ::tensorflow::NameRangesForNode(*ret, ret->op_def(), nullptr, &_outputs_range);
  if (!_status_.ok()) {
    scope.UpdateStatus(_status_);
    return;
  }

  this->out_example_state_data = Output(ret, _outputs_range["out_example_state_data"].first);
  for (int32 i = _outputs_range["out_delta_sparse_weights"].first; i < _outputs_range["out_delta_sparse_weights"].second; ++i)
    this->out_delta_sparse_weights.push_back(Output(ret, i));
  for (int32 i = _outputs_range["out_delta_dense_weights"].first; i < _outputs_range["out_delta_dense_weights"].second; ++i)
    this->out_delta_dense_weights.push_back(Output(ret, i));
}

SdcaOptimizer::SdcaOptimizer(const ::tensorflow::Scope& scope,
                             ::tensorflow::InputList sparse_example_indices,
                             ::tensorflow::InputList sparse_feature_indices,
                             ::tensorflow::InputList sparse_feature_values,
                             ::tensorflow::InputList dense_features,
                             ::tensorflow::Input example_weights,
                             ::tensorflow::Input example_labels,
                             ::tensorflow::InputList sparse_indices,
                             ::tensorflow::InputList sparse_weights,
                             ::tensorflow::InputList dense_weights,
                             ::tensorflow::Input example_state_data,
                             StringPiece loss_type, float l1, float l2, int64
                             num_loss_partitions, int64 num_inner_iterations)
  : SdcaOptimizer(scope, sparse_example_indices, sparse_feature_indices, sparse_feature_values, dense_features, example_weights, example_labels, sparse_indices, sparse_weights, dense_weights, example_state_data, loss_type, l1, l2, num_loss_partitions, num_inner_iterations, SdcaOptimizer::Attrs()) {}

SdcaShrinkL1::SdcaShrinkL1(const ::tensorflow::Scope& scope,
                           ::tensorflow::InputList weights, float l1, float l2) {
  if (!scope.ok()) return;
  auto _weights = ::tensorflow::ops::AsNodeOutList(scope, weights);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SdcaShrinkL1");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SdcaShrinkL1")
                     .Input(_weights)
                     .Attr("l1", l1)
                     .Attr("l2", l2)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

/// @}

}  // namespace ops
}  // namespace tensorflow
