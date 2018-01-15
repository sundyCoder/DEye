// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/resource_variable_ops.h"

namespace tensorflow {
namespace ops {

AssignAddVariableOp::AssignAddVariableOp(const ::tensorflow::Scope& scope,
                                         ::tensorflow::Input resource,
                                         ::tensorflow::Input value) {
  if (!scope.ok()) return;
  auto _resource = ::tensorflow::ops::AsNodeOut(scope, resource);
  if (!scope.ok()) return;
  auto _value = ::tensorflow::ops::AsNodeOut(scope, value);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("AssignAddVariableOp");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "AssignAddVariableOp")
                     .Input(_resource)
                     .Input(_value)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

AssignSubVariableOp::AssignSubVariableOp(const ::tensorflow::Scope& scope,
                                         ::tensorflow::Input resource,
                                         ::tensorflow::Input value) {
  if (!scope.ok()) return;
  auto _resource = ::tensorflow::ops::AsNodeOut(scope, resource);
  if (!scope.ok()) return;
  auto _value = ::tensorflow::ops::AsNodeOut(scope, value);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("AssignSubVariableOp");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "AssignSubVariableOp")
                     .Input(_resource)
                     .Input(_value)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

AssignVariableOp::AssignVariableOp(const ::tensorflow::Scope& scope,
                                   ::tensorflow::Input resource,
                                   ::tensorflow::Input value) {
  if (!scope.ok()) return;
  auto _resource = ::tensorflow::ops::AsNodeOut(scope, resource);
  if (!scope.ok()) return;
  auto _value = ::tensorflow::ops::AsNodeOut(scope, value);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("AssignVariableOp");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "AssignVariableOp")
                     .Input(_resource)
                     .Input(_value)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

DestroyResourceOp::DestroyResourceOp(const ::tensorflow::Scope& scope,
                                     ::tensorflow::Input resource, const
                                     DestroyResourceOp::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _resource = ::tensorflow::ops::AsNodeOut(scope, resource);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("DestroyResourceOp");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "DestroyResourceOp")
                     .Input(_resource)
                     .Attr("ignore_lookup_error", attrs.ignore_lookup_error_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

DestroyResourceOp::DestroyResourceOp(const ::tensorflow::Scope& scope,
                                     ::tensorflow::Input resource)
  : DestroyResourceOp(scope, resource, DestroyResourceOp::Attrs()) {}

ReadVariableOp::ReadVariableOp(const ::tensorflow::Scope& scope,
                               ::tensorflow::Input resource, DataType dtype) {
  if (!scope.ok()) return;
  auto _resource = ::tensorflow::ops::AsNodeOut(scope, resource);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("ReadVariableOp");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "ReadVariableOp")
                     .Input(_resource)
                     .Attr("dtype", dtype)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->value = Output(ret, 0);
}

ResourceGather::ResourceGather(const ::tensorflow::Scope& scope,
                               ::tensorflow::Input resource,
                               ::tensorflow::Input indices, DataType dtype,
                               const ResourceGather::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _resource = ::tensorflow::ops::AsNodeOut(scope, resource);
  if (!scope.ok()) return;
  auto _indices = ::tensorflow::ops::AsNodeOut(scope, indices);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("ResourceGather");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "ResourceGather")
                     .Input(_resource)
                     .Input(_indices)
                     .Attr("validate_indices", attrs.validate_indices_)
                     .Attr("dtype", dtype)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

ResourceGather::ResourceGather(const ::tensorflow::Scope& scope,
                               ::tensorflow::Input resource,
                               ::tensorflow::Input indices, DataType dtype)
  : ResourceGather(scope, resource, indices, dtype, ResourceGather::Attrs()) {}

ResourceScatterAdd::ResourceScatterAdd(const ::tensorflow::Scope& scope,
                                       ::tensorflow::Input resource,
                                       ::tensorflow::Input indices,
                                       ::tensorflow::Input updates) {
  if (!scope.ok()) return;
  auto _resource = ::tensorflow::ops::AsNodeOut(scope, resource);
  if (!scope.ok()) return;
  auto _indices = ::tensorflow::ops::AsNodeOut(scope, indices);
  if (!scope.ok()) return;
  auto _updates = ::tensorflow::ops::AsNodeOut(scope, updates);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("ResourceScatterAdd");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "ResourceScatterAdd")
                     .Input(_resource)
                     .Input(_indices)
                     .Input(_updates)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

VarHandleOp::VarHandleOp(const ::tensorflow::Scope& scope, DataType dtype,
                         PartialTensorShape shape, const VarHandleOp::Attrs&
                         attrs) {
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("VarHandleOp");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "VarHandleOp")
                     .Attr("container", attrs.container_)
                     .Attr("shared_name", attrs.shared_name_)
                     .Attr("dtype", dtype)
                     .Attr("shape", shape)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->resource = Output(ret, 0);
}

VarHandleOp::VarHandleOp(const ::tensorflow::Scope& scope, DataType dtype,
                         PartialTensorShape shape)
  : VarHandleOp(scope, dtype, shape, VarHandleOp::Attrs()) {}

VarIsInitializedOp::VarIsInitializedOp(const ::tensorflow::Scope& scope,
                                       ::tensorflow::Input resource) {
  if (!scope.ok()) return;
  auto _resource = ::tensorflow::ops::AsNodeOut(scope, resource);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("VarIsInitializedOp");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "VarIsInitializedOp")
                     .Input(_resource)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->is_initialized = Output(ret, 0);
}

VariableShape::VariableShape(const ::tensorflow::Scope& scope,
                             ::tensorflow::Input input, const
                             VariableShape::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("VariableShape");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "VariableShape")
                     .Input(_input)
                     .Attr("out_type", attrs.out_type_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

VariableShape::VariableShape(const ::tensorflow::Scope& scope,
                             ::tensorflow::Input input)
  : VariableShape(scope, input, VariableShape::Attrs()) {}

/// @}

}  // namespace ops
}  // namespace tensorflow
