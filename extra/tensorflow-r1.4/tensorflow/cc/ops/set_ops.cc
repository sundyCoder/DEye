// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/set_ops.h"

namespace tensorflow {
namespace ops {

DenseToDenseSetOperation::DenseToDenseSetOperation(const ::tensorflow::Scope&
                                                   scope, ::tensorflow::Input
                                                   set1, ::tensorflow::Input
                                                   set2, StringPiece
                                                   set_operation, const
                                                   DenseToDenseSetOperation::Attrs&
                                                   attrs) {
  if (!scope.ok()) return;
  auto _set1 = ::tensorflow::ops::AsNodeOut(scope, set1);
  if (!scope.ok()) return;
  auto _set2 = ::tensorflow::ops::AsNodeOut(scope, set2);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("DenseToDenseSetOperation");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "DenseToDenseSetOperation")
                     .Input(_set1)
                     .Input(_set2)
                     .Attr("set_operation", set_operation)
                     .Attr("validate_indices", attrs.validate_indices_)
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

  this->result_indices = Output(ret, _outputs_range["result_indices"].first);
  this->result_values = Output(ret, _outputs_range["result_values"].first);
  this->result_shape = Output(ret, _outputs_range["result_shape"].first);
}

DenseToDenseSetOperation::DenseToDenseSetOperation(const ::tensorflow::Scope&
                                                   scope, ::tensorflow::Input
                                                   set1, ::tensorflow::Input
                                                   set2, StringPiece
                                                   set_operation)
  : DenseToDenseSetOperation(scope, set1, set2, set_operation, DenseToDenseSetOperation::Attrs()) {}

DenseToSparseSetOperation::DenseToSparseSetOperation(const ::tensorflow::Scope&
                                                     scope, ::tensorflow::Input
                                                     set1, ::tensorflow::Input
                                                     set2_indices,
                                                     ::tensorflow::Input
                                                     set2_values,
                                                     ::tensorflow::Input
                                                     set2_shape, StringPiece
                                                     set_operation, const
                                                     DenseToSparseSetOperation::Attrs&
                                                     attrs) {
  if (!scope.ok()) return;
  auto _set1 = ::tensorflow::ops::AsNodeOut(scope, set1);
  if (!scope.ok()) return;
  auto _set2_indices = ::tensorflow::ops::AsNodeOut(scope, set2_indices);
  if (!scope.ok()) return;
  auto _set2_values = ::tensorflow::ops::AsNodeOut(scope, set2_values);
  if (!scope.ok()) return;
  auto _set2_shape = ::tensorflow::ops::AsNodeOut(scope, set2_shape);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("DenseToSparseSetOperation");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "DenseToSparseSetOperation")
                     .Input(_set1)
                     .Input(_set2_indices)
                     .Input(_set2_values)
                     .Input(_set2_shape)
                     .Attr("set_operation", set_operation)
                     .Attr("validate_indices", attrs.validate_indices_)
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

  this->result_indices = Output(ret, _outputs_range["result_indices"].first);
  this->result_values = Output(ret, _outputs_range["result_values"].first);
  this->result_shape = Output(ret, _outputs_range["result_shape"].first);
}

DenseToSparseSetOperation::DenseToSparseSetOperation(const ::tensorflow::Scope&
                                                     scope, ::tensorflow::Input
                                                     set1, ::tensorflow::Input
                                                     set2_indices,
                                                     ::tensorflow::Input
                                                     set2_values,
                                                     ::tensorflow::Input
                                                     set2_shape, StringPiece
                                                     set_operation)
  : DenseToSparseSetOperation(scope, set1, set2_indices, set2_values, set2_shape, set_operation, DenseToSparseSetOperation::Attrs()) {}

SetSize::SetSize(const ::tensorflow::Scope& scope, ::tensorflow::Input
                 set_indices, ::tensorflow::Input set_values,
                 ::tensorflow::Input set_shape, const SetSize::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _set_indices = ::tensorflow::ops::AsNodeOut(scope, set_indices);
  if (!scope.ok()) return;
  auto _set_values = ::tensorflow::ops::AsNodeOut(scope, set_values);
  if (!scope.ok()) return;
  auto _set_shape = ::tensorflow::ops::AsNodeOut(scope, set_shape);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SetSize");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SetSize")
                     .Input(_set_indices)
                     .Input(_set_values)
                     .Input(_set_shape)
                     .Attr("validate_indices", attrs.validate_indices_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->size = Output(ret, 0);
}

SetSize::SetSize(const ::tensorflow::Scope& scope, ::tensorflow::Input
                 set_indices, ::tensorflow::Input set_values,
                 ::tensorflow::Input set_shape)
  : SetSize(scope, set_indices, set_values, set_shape, SetSize::Attrs()) {}

SparseToSparseSetOperation::SparseToSparseSetOperation(const
                                                       ::tensorflow::Scope&
                                                       scope,
                                                       ::tensorflow::Input
                                                       set1_indices,
                                                       ::tensorflow::Input
                                                       set1_values,
                                                       ::tensorflow::Input
                                                       set1_shape,
                                                       ::tensorflow::Input
                                                       set2_indices,
                                                       ::tensorflow::Input
                                                       set2_values,
                                                       ::tensorflow::Input
                                                       set2_shape, StringPiece
                                                       set_operation, const
                                                       SparseToSparseSetOperation::Attrs&
                                                       attrs) {
  if (!scope.ok()) return;
  auto _set1_indices = ::tensorflow::ops::AsNodeOut(scope, set1_indices);
  if (!scope.ok()) return;
  auto _set1_values = ::tensorflow::ops::AsNodeOut(scope, set1_values);
  if (!scope.ok()) return;
  auto _set1_shape = ::tensorflow::ops::AsNodeOut(scope, set1_shape);
  if (!scope.ok()) return;
  auto _set2_indices = ::tensorflow::ops::AsNodeOut(scope, set2_indices);
  if (!scope.ok()) return;
  auto _set2_values = ::tensorflow::ops::AsNodeOut(scope, set2_values);
  if (!scope.ok()) return;
  auto _set2_shape = ::tensorflow::ops::AsNodeOut(scope, set2_shape);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SparseToSparseSetOperation");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SparseToSparseSetOperation")
                     .Input(_set1_indices)
                     .Input(_set1_values)
                     .Input(_set1_shape)
                     .Input(_set2_indices)
                     .Input(_set2_values)
                     .Input(_set2_shape)
                     .Attr("set_operation", set_operation)
                     .Attr("validate_indices", attrs.validate_indices_)
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

  this->result_indices = Output(ret, _outputs_range["result_indices"].first);
  this->result_values = Output(ret, _outputs_range["result_values"].first);
  this->result_shape = Output(ret, _outputs_range["result_shape"].first);
}

SparseToSparseSetOperation::SparseToSparseSetOperation(const
                                                       ::tensorflow::Scope&
                                                       scope,
                                                       ::tensorflow::Input
                                                       set1_indices,
                                                       ::tensorflow::Input
                                                       set1_values,
                                                       ::tensorflow::Input
                                                       set1_shape,
                                                       ::tensorflow::Input
                                                       set2_indices,
                                                       ::tensorflow::Input
                                                       set2_values,
                                                       ::tensorflow::Input
                                                       set2_shape, StringPiece
                                                       set_operation)
  : SparseToSparseSetOperation(scope, set1_indices, set1_values, set1_shape, set2_indices, set2_values, set2_shape, set_operation, SparseToSparseSetOperation::Attrs()) {}

/// @}

}  // namespace ops
}  // namespace tensorflow
