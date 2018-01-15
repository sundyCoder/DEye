// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/stateless_random_ops.h"

namespace tensorflow {
namespace ops {

StatelessRandomNormal::StatelessRandomNormal(const ::tensorflow::Scope& scope,
                                             ::tensorflow::Input shape,
                                             ::tensorflow::Input seed, const
                                             StatelessRandomNormal::Attrs&
                                             attrs) {
  if (!scope.ok()) return;
  auto _shape = ::tensorflow::ops::AsNodeOut(scope, shape);
  if (!scope.ok()) return;
  auto _seed = ::tensorflow::ops::AsNodeOut(scope, seed);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("StatelessRandomNormal");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "StatelessRandomNormal")
                     .Input(_shape)
                     .Input(_seed)
                     .Attr("dtype", attrs.dtype_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

StatelessRandomNormal::StatelessRandomNormal(const ::tensorflow::Scope& scope,
                                             ::tensorflow::Input shape,
                                             ::tensorflow::Input seed)
  : StatelessRandomNormal(scope, shape, seed, StatelessRandomNormal::Attrs()) {}

StatelessRandomUniform::StatelessRandomUniform(const ::tensorflow::Scope&
                                               scope, ::tensorflow::Input
                                               shape, ::tensorflow::Input seed,
                                               const
                                               StatelessRandomUniform::Attrs&
                                               attrs) {
  if (!scope.ok()) return;
  auto _shape = ::tensorflow::ops::AsNodeOut(scope, shape);
  if (!scope.ok()) return;
  auto _seed = ::tensorflow::ops::AsNodeOut(scope, seed);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("StatelessRandomUniform");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "StatelessRandomUniform")
                     .Input(_shape)
                     .Input(_seed)
                     .Attr("dtype", attrs.dtype_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

StatelessRandomUniform::StatelessRandomUniform(const ::tensorflow::Scope&
                                               scope, ::tensorflow::Input
                                               shape, ::tensorflow::Input seed)
  : StatelessRandomUniform(scope, shape, seed, StatelessRandomUniform::Attrs()) {}

StatelessTruncatedNormal::StatelessTruncatedNormal(const ::tensorflow::Scope&
                                                   scope, ::tensorflow::Input
                                                   shape, ::tensorflow::Input
                                                   seed, const
                                                   StatelessTruncatedNormal::Attrs&
                                                   attrs) {
  if (!scope.ok()) return;
  auto _shape = ::tensorflow::ops::AsNodeOut(scope, shape);
  if (!scope.ok()) return;
  auto _seed = ::tensorflow::ops::AsNodeOut(scope, seed);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("StatelessTruncatedNormal");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "StatelessTruncatedNormal")
                     .Input(_shape)
                     .Input(_seed)
                     .Attr("dtype", attrs.dtype_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

StatelessTruncatedNormal::StatelessTruncatedNormal(const ::tensorflow::Scope&
                                                   scope, ::tensorflow::Input
                                                   shape, ::tensorflow::Input
                                                   seed)
  : StatelessTruncatedNormal(scope, shape, seed, StatelessTruncatedNormal::Attrs()) {}

/// @}

}  // namespace ops
}  // namespace tensorflow
