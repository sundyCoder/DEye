// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/bitwise_ops.h"

namespace tensorflow {
namespace ops {

BitwiseAnd::BitwiseAnd(const ::tensorflow::Scope& scope, ::tensorflow::Input x,
                       ::tensorflow::Input y) {
  if (!scope.ok()) return;
  auto _x = ::tensorflow::ops::AsNodeOut(scope, x);
  if (!scope.ok()) return;
  auto _y = ::tensorflow::ops::AsNodeOut(scope, y);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("BitwiseAnd");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "BitwiseAnd")
                     .Input(_x)
                     .Input(_y)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->z = Output(ret, 0);
}

BitwiseOr::BitwiseOr(const ::tensorflow::Scope& scope, ::tensorflow::Input x,
                     ::tensorflow::Input y) {
  if (!scope.ok()) return;
  auto _x = ::tensorflow::ops::AsNodeOut(scope, x);
  if (!scope.ok()) return;
  auto _y = ::tensorflow::ops::AsNodeOut(scope, y);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("BitwiseOr");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "BitwiseOr")
                     .Input(_x)
                     .Input(_y)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->z = Output(ret, 0);
}

BitwiseXor::BitwiseXor(const ::tensorflow::Scope& scope, ::tensorflow::Input x,
                       ::tensorflow::Input y) {
  if (!scope.ok()) return;
  auto _x = ::tensorflow::ops::AsNodeOut(scope, x);
  if (!scope.ok()) return;
  auto _y = ::tensorflow::ops::AsNodeOut(scope, y);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("BitwiseXor");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "BitwiseXor")
                     .Input(_x)
                     .Input(_y)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->z = Output(ret, 0);
}

Invert::Invert(const ::tensorflow::Scope& scope, ::tensorflow::Input x) {
  if (!scope.ok()) return;
  auto _x = ::tensorflow::ops::AsNodeOut(scope, x);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("Invert");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "Invert")
                     .Input(_x)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->y = Output(ret, 0);
}

PopulationCount::PopulationCount(const ::tensorflow::Scope& scope,
                                 ::tensorflow::Input x) {
  if (!scope.ok()) return;
  auto _x = ::tensorflow::ops::AsNodeOut(scope, x);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("PopulationCount");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "PopulationCount")
                     .Input(_x)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->y = Output(ret, 0);
}

/// @}

}  // namespace ops
}  // namespace tensorflow
