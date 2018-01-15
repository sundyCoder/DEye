// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/functional_ops.h"

namespace tensorflow {
namespace ops {

RemoteCall::RemoteCall(const ::tensorflow::Scope& scope, ::tensorflow::Input
                       target, ::tensorflow::InputList args, const
                       DataTypeSlice& Tout, const NameAttrList& f) {
  if (!scope.ok()) return;
  auto _target = ::tensorflow::ops::AsNodeOut(scope, target);
  if (!scope.ok()) return;
  auto _args = ::tensorflow::ops::AsNodeOutList(scope, args);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("RemoteCall");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "RemoteCall")
                     .Input(_target)
                     .Input(_args)
                     .Attr("Tout", Tout)
                     .Attr("f", f)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  for (int32 i = 0; i < ret->num_outputs(); ++i)
    this->output.push_back(Output(ret, i));
}

SymbolicGradient::SymbolicGradient(const ::tensorflow::Scope& scope,
                                   ::tensorflow::InputList input, const
                                   DataTypeSlice& Tout, const NameAttrList& f) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOutList(scope, input);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SymbolicGradient");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SymbolicGradient")
                     .Input(_input)
                     .Attr("Tout", Tout)
                     .Attr("f", f)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  for (int32 i = 0; i < ret->num_outputs(); ++i)
    this->output.push_back(Output(ret, i));
}

/// @}

}  // namespace ops
}  // namespace tensorflow
