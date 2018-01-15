// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/math_ops_internal.h"

namespace tensorflow {
namespace ops {
namespace internal {
// NOTE: This namespace has internal TensorFlow details that
// are not part of TensorFlow's public API.

ReciprocalGrad::ReciprocalGrad(const ::tensorflow::Scope& scope,
                               ::tensorflow::Input y, ::tensorflow::Input dy) {
  if (!scope.ok()) return;
  auto _y = ::tensorflow::ops::AsNodeOut(scope, y);
  if (!scope.ok()) return;
  auto _dy = ::tensorflow::ops::AsNodeOut(scope, dy);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("ReciprocalGrad");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "ReciprocalGrad")
                     .Input(_y)
                     .Input(_dy)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->z = Output(ret, 0);
}

RsqrtGrad::RsqrtGrad(const ::tensorflow::Scope& scope, ::tensorflow::Input y,
                     ::tensorflow::Input dy) {
  if (!scope.ok()) return;
  auto _y = ::tensorflow::ops::AsNodeOut(scope, y);
  if (!scope.ok()) return;
  auto _dy = ::tensorflow::ops::AsNodeOut(scope, dy);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("RsqrtGrad");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "RsqrtGrad")
                     .Input(_y)
                     .Input(_dy)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->z = Output(ret, 0);
}

SigmoidGrad::SigmoidGrad(const ::tensorflow::Scope& scope, ::tensorflow::Input
                         y, ::tensorflow::Input dy) {
  if (!scope.ok()) return;
  auto _y = ::tensorflow::ops::AsNodeOut(scope, y);
  if (!scope.ok()) return;
  auto _dy = ::tensorflow::ops::AsNodeOut(scope, dy);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SigmoidGrad");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SigmoidGrad")
                     .Input(_y)
                     .Input(_dy)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->z = Output(ret, 0);
}

SqrtGrad::SqrtGrad(const ::tensorflow::Scope& scope, ::tensorflow::Input y,
                   ::tensorflow::Input dy) {
  if (!scope.ok()) return;
  auto _y = ::tensorflow::ops::AsNodeOut(scope, y);
  if (!scope.ok()) return;
  auto _dy = ::tensorflow::ops::AsNodeOut(scope, dy);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SqrtGrad");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SqrtGrad")
                     .Input(_y)
                     .Input(_dy)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->z = Output(ret, 0);
}

TanhGrad::TanhGrad(const ::tensorflow::Scope& scope, ::tensorflow::Input y,
                   ::tensorflow::Input dy) {
  if (!scope.ok()) return;
  auto _y = ::tensorflow::ops::AsNodeOut(scope, y);
  if (!scope.ok()) return;
  auto _dy = ::tensorflow::ops::AsNodeOut(scope, dy);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("TanhGrad");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "TanhGrad")
                     .Input(_y)
                     .Input(_dy)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->z = Output(ret, 0);
}

}  // namespace internal
}  // namespace ops
}  // namespace tensorflow
