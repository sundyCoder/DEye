// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/ctc_ops.h"

namespace tensorflow {
namespace ops {

CTCBeamSearchDecoder::CTCBeamSearchDecoder(const ::tensorflow::Scope& scope,
                                           ::tensorflow::Input inputs,
                                           ::tensorflow::Input sequence_length,
                                           int64 beam_width, int64 top_paths,
                                           const CTCBeamSearchDecoder::Attrs&
                                           attrs) {
  if (!scope.ok()) return;
  auto _inputs = ::tensorflow::ops::AsNodeOut(scope, inputs);
  if (!scope.ok()) return;
  auto _sequence_length = ::tensorflow::ops::AsNodeOut(scope, sequence_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("CTCBeamSearchDecoder");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "CTCBeamSearchDecoder")
                     .Input(_inputs)
                     .Input(_sequence_length)
                     .Attr("beam_width", beam_width)
                     .Attr("top_paths", top_paths)
                     .Attr("merge_repeated", attrs.merge_repeated_)
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

  for (int32 i = _outputs_range["decoded_indices"].first; i < _outputs_range["decoded_indices"].second; ++i)
    this->decoded_indices.push_back(Output(ret, i));
  for (int32 i = _outputs_range["decoded_values"].first; i < _outputs_range["decoded_values"].second; ++i)
    this->decoded_values.push_back(Output(ret, i));
  for (int32 i = _outputs_range["decoded_shape"].first; i < _outputs_range["decoded_shape"].second; ++i)
    this->decoded_shape.push_back(Output(ret, i));
  this->log_probability = Output(ret, _outputs_range["log_probability"].first);
}

CTCBeamSearchDecoder::CTCBeamSearchDecoder(const ::tensorflow::Scope& scope,
                                           ::tensorflow::Input inputs,
                                           ::tensorflow::Input sequence_length,
                                           int64 beam_width, int64 top_paths)
  : CTCBeamSearchDecoder(scope, inputs, sequence_length, beam_width, top_paths, CTCBeamSearchDecoder::Attrs()) {}

CTCGreedyDecoder::CTCGreedyDecoder(const ::tensorflow::Scope& scope,
                                   ::tensorflow::Input inputs,
                                   ::tensorflow::Input sequence_length, const
                                   CTCGreedyDecoder::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _inputs = ::tensorflow::ops::AsNodeOut(scope, inputs);
  if (!scope.ok()) return;
  auto _sequence_length = ::tensorflow::ops::AsNodeOut(scope, sequence_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("CTCGreedyDecoder");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "CTCGreedyDecoder")
                     .Input(_inputs)
                     .Input(_sequence_length)
                     .Attr("merge_repeated", attrs.merge_repeated_)
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

  this->decoded_indices = Output(ret, _outputs_range["decoded_indices"].first);
  this->decoded_values = Output(ret, _outputs_range["decoded_values"].first);
  this->decoded_shape = Output(ret, _outputs_range["decoded_shape"].first);
  this->log_probability = Output(ret, _outputs_range["log_probability"].first);
}

CTCGreedyDecoder::CTCGreedyDecoder(const ::tensorflow::Scope& scope,
                                   ::tensorflow::Input inputs,
                                   ::tensorflow::Input sequence_length)
  : CTCGreedyDecoder(scope, inputs, sequence_length, CTCGreedyDecoder::Attrs()) {}

CTCLoss::CTCLoss(const ::tensorflow::Scope& scope, ::tensorflow::Input inputs,
                 ::tensorflow::Input labels_indices, ::tensorflow::Input
                 labels_values, ::tensorflow::Input sequence_length, const
                 CTCLoss::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _inputs = ::tensorflow::ops::AsNodeOut(scope, inputs);
  if (!scope.ok()) return;
  auto _labels_indices = ::tensorflow::ops::AsNodeOut(scope, labels_indices);
  if (!scope.ok()) return;
  auto _labels_values = ::tensorflow::ops::AsNodeOut(scope, labels_values);
  if (!scope.ok()) return;
  auto _sequence_length = ::tensorflow::ops::AsNodeOut(scope, sequence_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("CTCLoss");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "CTCLoss")
                     .Input(_inputs)
                     .Input(_labels_indices)
                     .Input(_labels_values)
                     .Input(_sequence_length)
                     .Attr("preprocess_collapse_repeated", attrs.preprocess_collapse_repeated_)
                     .Attr("ctc_merge_repeated", attrs.ctc_merge_repeated_)
                     .Attr("ignore_longer_outputs_than_inputs", attrs.ignore_longer_outputs_than_inputs_)
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

  this->loss = Output(ret, _outputs_range["loss"].first);
  this->gradient = Output(ret, _outputs_range["gradient"].first);
}

CTCLoss::CTCLoss(const ::tensorflow::Scope& scope, ::tensorflow::Input inputs,
                 ::tensorflow::Input labels_indices, ::tensorflow::Input
                 labels_values, ::tensorflow::Input sequence_length)
  : CTCLoss(scope, inputs, labels_indices, labels_values, sequence_length, CTCLoss::Attrs()) {}

/// @}

}  // namespace ops
}  // namespace tensorflow
