// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/checkpoint_ops.h"

namespace tensorflow {
namespace ops {

GenerateVocabRemapping::GenerateVocabRemapping(const ::tensorflow::Scope&
                                               scope, ::tensorflow::Input
                                               new_vocab_file,
                                               ::tensorflow::Input
                                               old_vocab_file, int64
                                               new_vocab_offset, int64
                                               num_new_vocab) {
  if (!scope.ok()) return;
  auto _new_vocab_file = ::tensorflow::ops::AsNodeOut(scope, new_vocab_file);
  if (!scope.ok()) return;
  auto _old_vocab_file = ::tensorflow::ops::AsNodeOut(scope, old_vocab_file);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("GenerateVocabRemapping");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "GenerateVocabRemapping")
                     .Input(_new_vocab_file)
                     .Input(_old_vocab_file)
                     .Attr("new_vocab_offset", new_vocab_offset)
                     .Attr("num_new_vocab", num_new_vocab)
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

  this->remapping = Output(ret, _outputs_range["remapping"].first);
  this->num_present = Output(ret, _outputs_range["num_present"].first);
}

LoadAndRemapMatrix::LoadAndRemapMatrix(const ::tensorflow::Scope& scope,
                                       ::tensorflow::Input ckpt_path,
                                       ::tensorflow::Input old_tensor_name,
                                       ::tensorflow::Input row_remapping,
                                       ::tensorflow::Input col_remapping,
                                       ::tensorflow::Input initializing_values,
                                       int64 num_rows, int64 num_cols, const
                                       LoadAndRemapMatrix::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _ckpt_path = ::tensorflow::ops::AsNodeOut(scope, ckpt_path);
  if (!scope.ok()) return;
  auto _old_tensor_name = ::tensorflow::ops::AsNodeOut(scope, old_tensor_name);
  if (!scope.ok()) return;
  auto _row_remapping = ::tensorflow::ops::AsNodeOut(scope, row_remapping);
  if (!scope.ok()) return;
  auto _col_remapping = ::tensorflow::ops::AsNodeOut(scope, col_remapping);
  if (!scope.ok()) return;
  auto _initializing_values = ::tensorflow::ops::AsNodeOut(scope, initializing_values);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("LoadAndRemapMatrix");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "LoadAndRemapMatrix")
                     .Input(_ckpt_path)
                     .Input(_old_tensor_name)
                     .Input(_row_remapping)
                     .Input(_col_remapping)
                     .Input(_initializing_values)
                     .Attr("num_rows", num_rows)
                     .Attr("num_cols", num_cols)
                     .Attr("max_rows_in_memory", attrs.max_rows_in_memory_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output_matrix = Output(ret, 0);
}

LoadAndRemapMatrix::LoadAndRemapMatrix(const ::tensorflow::Scope& scope,
                                       ::tensorflow::Input ckpt_path,
                                       ::tensorflow::Input old_tensor_name,
                                       ::tensorflow::Input row_remapping,
                                       ::tensorflow::Input col_remapping,
                                       ::tensorflow::Input initializing_values,
                                       int64 num_rows, int64 num_cols)
  : LoadAndRemapMatrix(scope, ckpt_path, old_tensor_name, row_remapping, col_remapping, initializing_values, num_rows, num_cols, LoadAndRemapMatrix::Attrs()) {}

/// @}

}  // namespace ops
}  // namespace tensorflow
