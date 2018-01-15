// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/dataset_ops.h"

namespace tensorflow {
namespace ops {

BatchDataset::BatchDataset(const ::tensorflow::Scope& scope,
                           ::tensorflow::Input input_dataset,
                           ::tensorflow::Input batch_size, const DataTypeSlice&
                           output_types, const
                           gtl::ArraySlice<PartialTensorShape>& output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _batch_size = ::tensorflow::ops::AsNodeOut(scope, batch_size);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("BatchDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "BatchDataset")
                     .Input(_input_dataset)
                     .Input(_batch_size)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

CacheDataset::CacheDataset(const ::tensorflow::Scope& scope,
                           ::tensorflow::Input input_dataset,
                           ::tensorflow::Input filename, const DataTypeSlice&
                           output_types, const
                           gtl::ArraySlice<PartialTensorShape>& output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _filename = ::tensorflow::ops::AsNodeOut(scope, filename);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("CacheDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "CacheDataset")
                     .Input(_input_dataset)
                     .Input(_filename)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

ConcatenateDataset::ConcatenateDataset(const ::tensorflow::Scope& scope,
                                       ::tensorflow::Input input_dataset,
                                       ::tensorflow::Input another_dataset,
                                       const DataTypeSlice& output_types, const
                                       gtl::ArraySlice<PartialTensorShape>&
                                       output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _another_dataset = ::tensorflow::ops::AsNodeOut(scope, another_dataset);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("ConcatenateDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "ConcatenateDataset")
                     .Input(_input_dataset)
                     .Input(_another_dataset)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

DenseToSparseBatchDataset::DenseToSparseBatchDataset(const ::tensorflow::Scope&
                                                     scope, ::tensorflow::Input
                                                     input_dataset,
                                                     ::tensorflow::Input
                                                     batch_size,
                                                     ::tensorflow::Input
                                                     row_shape, const
                                                     DataTypeSlice&
                                                     output_types, const
                                                     gtl::ArraySlice<PartialTensorShape>&
                                                     output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _batch_size = ::tensorflow::ops::AsNodeOut(scope, batch_size);
  if (!scope.ok()) return;
  auto _row_shape = ::tensorflow::ops::AsNodeOut(scope, row_shape);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("DenseToSparseBatchDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "DenseToSparseBatchDataset")
                     .Input(_input_dataset)
                     .Input(_batch_size)
                     .Input(_row_shape)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

FilterDataset::FilterDataset(const ::tensorflow::Scope& scope,
                             ::tensorflow::Input input_dataset,
                             ::tensorflow::InputList other_arguments, const
                             NameAttrList& predicate, const DataTypeSlice&
                             output_types, const
                             gtl::ArraySlice<PartialTensorShape>&
                             output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _other_arguments = ::tensorflow::ops::AsNodeOutList(scope, other_arguments);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("FilterDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "FilterDataset")
                     .Input(_input_dataset)
                     .Input(_other_arguments)
                     .Attr("predicate", predicate)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

FixedLengthRecordDataset::FixedLengthRecordDataset(const ::tensorflow::Scope&
                                                   scope, ::tensorflow::Input
                                                   filenames,
                                                   ::tensorflow::Input
                                                   header_bytes,
                                                   ::tensorflow::Input
                                                   record_bytes,
                                                   ::tensorflow::Input
                                                   footer_bytes,
                                                   ::tensorflow::Input
                                                   buffer_size) {
  if (!scope.ok()) return;
  auto _filenames = ::tensorflow::ops::AsNodeOut(scope, filenames);
  if (!scope.ok()) return;
  auto _header_bytes = ::tensorflow::ops::AsNodeOut(scope, header_bytes);
  if (!scope.ok()) return;
  auto _record_bytes = ::tensorflow::ops::AsNodeOut(scope, record_bytes);
  if (!scope.ok()) return;
  auto _footer_bytes = ::tensorflow::ops::AsNodeOut(scope, footer_bytes);
  if (!scope.ok()) return;
  auto _buffer_size = ::tensorflow::ops::AsNodeOut(scope, buffer_size);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("FixedLengthRecordDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "FixedLengthRecordDataset")
                     .Input(_filenames)
                     .Input(_header_bytes)
                     .Input(_record_bytes)
                     .Input(_footer_bytes)
                     .Input(_buffer_size)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

FlatMapDataset::FlatMapDataset(const ::tensorflow::Scope& scope,
                               ::tensorflow::Input input_dataset,
                               ::tensorflow::InputList other_arguments, const
                               NameAttrList& f, const DataTypeSlice&
                               output_types, const
                               gtl::ArraySlice<PartialTensorShape>&
                               output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _other_arguments = ::tensorflow::ops::AsNodeOutList(scope, other_arguments);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("FlatMapDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "FlatMapDataset")
                     .Input(_input_dataset)
                     .Input(_other_arguments)
                     .Attr("f", f)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

GroupByWindowDataset::GroupByWindowDataset(const ::tensorflow::Scope& scope,
                                           ::tensorflow::Input input_dataset,
                                           ::tensorflow::InputList
                                           key_func_other_arguments,
                                           ::tensorflow::InputList
                                           reduce_func_other_arguments,
                                           ::tensorflow::InputList
                                           window_size_func_other_arguments,
                                           const NameAttrList& key_func, const
                                           NameAttrList& reduce_func, const
                                           NameAttrList& window_size_func,
                                           const DataTypeSlice& output_types,
                                           const
                                           gtl::ArraySlice<PartialTensorShape>&
                                           output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _key_func_other_arguments = ::tensorflow::ops::AsNodeOutList(scope, key_func_other_arguments);
  if (!scope.ok()) return;
  auto _reduce_func_other_arguments = ::tensorflow::ops::AsNodeOutList(scope, reduce_func_other_arguments);
  if (!scope.ok()) return;
  auto _window_size_func_other_arguments = ::tensorflow::ops::AsNodeOutList(scope, window_size_func_other_arguments);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("GroupByWindowDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "GroupByWindowDataset")
                     .Input(_input_dataset)
                     .Input(_key_func_other_arguments)
                     .Input(_reduce_func_other_arguments)
                     .Input(_window_size_func_other_arguments)
                     .Attr("key_func", key_func)
                     .Attr("reduce_func", reduce_func)
                     .Attr("window_size_func", window_size_func)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

IgnoreErrorsDataset::IgnoreErrorsDataset(const ::tensorflow::Scope& scope,
                                         ::tensorflow::Input input_dataset,
                                         const DataTypeSlice& output_types,
                                         const
                                         gtl::ArraySlice<PartialTensorShape>&
                                         output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IgnoreErrorsDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IgnoreErrorsDataset")
                     .Input(_input_dataset)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

InterleaveDataset::InterleaveDataset(const ::tensorflow::Scope& scope,
                                     ::tensorflow::Input input_dataset,
                                     ::tensorflow::InputList other_arguments,
                                     ::tensorflow::Input cycle_length,
                                     ::tensorflow::Input block_length, const
                                     NameAttrList& f, const DataTypeSlice&
                                     output_types, const
                                     gtl::ArraySlice<PartialTensorShape>&
                                     output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _other_arguments = ::tensorflow::ops::AsNodeOutList(scope, other_arguments);
  if (!scope.ok()) return;
  auto _cycle_length = ::tensorflow::ops::AsNodeOut(scope, cycle_length);
  if (!scope.ok()) return;
  auto _block_length = ::tensorflow::ops::AsNodeOut(scope, block_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("InterleaveDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "InterleaveDataset")
                     .Input(_input_dataset)
                     .Input(_other_arguments)
                     .Input(_cycle_length)
                     .Input(_block_length)
                     .Attr("f", f)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

Iterator::Iterator(const ::tensorflow::Scope& scope, StringPiece shared_name,
                   StringPiece container, const DataTypeSlice& output_types,
                   const gtl::ArraySlice<PartialTensorShape>& output_shapes) {
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("Iterator");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "Iterator")
                     .Attr("shared_name", shared_name)
                     .Attr("container", container)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

IteratorFromStringHandle::IteratorFromStringHandle(const ::tensorflow::Scope&
                                                   scope, ::tensorflow::Input
                                                   string_handle, const
                                                   IteratorFromStringHandle::Attrs&
                                                   attrs) {
  if (!scope.ok()) return;
  auto _string_handle = ::tensorflow::ops::AsNodeOut(scope, string_handle);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IteratorFromStringHandle");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IteratorFromStringHandle")
                     .Input(_string_handle)
                     .Attr("output_types", attrs.output_types_)
                     .Attr("output_shapes", attrs.output_shapes_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->resource_handle = Output(ret, 0);
}

IteratorFromStringHandle::IteratorFromStringHandle(const ::tensorflow::Scope&
                                                   scope, ::tensorflow::Input
                                                   string_handle)
  : IteratorFromStringHandle(scope, string_handle, IteratorFromStringHandle::Attrs()) {}

IteratorGetNext::IteratorGetNext(const ::tensorflow::Scope& scope,
                                 ::tensorflow::Input iterator, const
                                 DataTypeSlice& output_types, const
                                 gtl::ArraySlice<PartialTensorShape>&
                                 output_shapes) {
  if (!scope.ok()) return;
  auto _iterator = ::tensorflow::ops::AsNodeOut(scope, iterator);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IteratorGetNext");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IteratorGetNext")
                     .Input(_iterator)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  for (int32 i = 0; i < ret->num_outputs(); ++i)
    this->components.push_back(Output(ret, i));
}

IteratorToStringHandle::IteratorToStringHandle(const ::tensorflow::Scope&
                                               scope, ::tensorflow::Input
                                               resource_handle) {
  if (!scope.ok()) return;
  auto _resource_handle = ::tensorflow::ops::AsNodeOut(scope, resource_handle);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IteratorToStringHandle");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IteratorToStringHandle")
                     .Input(_resource_handle)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->string_handle = Output(ret, 0);
}

MakeIterator::MakeIterator(const ::tensorflow::Scope& scope,
                           ::tensorflow::Input dataset, ::tensorflow::Input
                           iterator) {
  if (!scope.ok()) return;
  auto _dataset = ::tensorflow::ops::AsNodeOut(scope, dataset);
  if (!scope.ok()) return;
  auto _iterator = ::tensorflow::ops::AsNodeOut(scope, iterator);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("MakeIterator");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "MakeIterator")
                     .Input(_dataset)
                     .Input(_iterator)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

MapDataset::MapDataset(const ::tensorflow::Scope& scope, ::tensorflow::Input
                       input_dataset, ::tensorflow::InputList other_arguments,
                       const NameAttrList& f, const DataTypeSlice&
                       output_types, const gtl::ArraySlice<PartialTensorShape>&
                       output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _other_arguments = ::tensorflow::ops::AsNodeOutList(scope, other_arguments);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("MapDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "MapDataset")
                     .Input(_input_dataset)
                     .Input(_other_arguments)
                     .Attr("f", f)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

OneShotIterator::OneShotIterator(const ::tensorflow::Scope& scope, const
                                 NameAttrList& dataset_factory, const
                                 DataTypeSlice& output_types, const
                                 gtl::ArraySlice<PartialTensorShape>&
                                 output_shapes, const OneShotIterator::Attrs&
                                 attrs) {
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("OneShotIterator");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "OneShotIterator")
                     .Attr("dataset_factory", dataset_factory)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
                     .Attr("container", attrs.container_)
                     .Attr("shared_name", attrs.shared_name_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

OneShotIterator::OneShotIterator(const ::tensorflow::Scope& scope, const
                                 NameAttrList& dataset_factory, const
                                 DataTypeSlice& output_types, const
                                 gtl::ArraySlice<PartialTensorShape>&
                                 output_shapes)
  : OneShotIterator(scope, dataset_factory, output_types, output_shapes, OneShotIterator::Attrs()) {}

PaddedBatchDataset::PaddedBatchDataset(const ::tensorflow::Scope& scope,
                                       ::tensorflow::Input input_dataset,
                                       ::tensorflow::Input batch_size,
                                       ::tensorflow::InputList padded_shapes,
                                       ::tensorflow::InputList padding_values,
                                       const
                                       gtl::ArraySlice<PartialTensorShape>&
                                       output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _batch_size = ::tensorflow::ops::AsNodeOut(scope, batch_size);
  if (!scope.ok()) return;
  auto _padded_shapes = ::tensorflow::ops::AsNodeOutList(scope, padded_shapes);
  if (!scope.ok()) return;
  auto _padding_values = ::tensorflow::ops::AsNodeOutList(scope, padding_values);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("PaddedBatchDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "PaddedBatchDataset")
                     .Input(_input_dataset)
                     .Input(_batch_size)
                     .Input(_padded_shapes)
                     .Input(_padding_values)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

ParallelMapDataset::ParallelMapDataset(const ::tensorflow::Scope& scope,
                                       ::tensorflow::Input input_dataset,
                                       ::tensorflow::InputList other_arguments,
                                       ::tensorflow::Input num_parallel_calls,
                                       const NameAttrList& f, const
                                       DataTypeSlice& output_types, const
                                       gtl::ArraySlice<PartialTensorShape>&
                                       output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _other_arguments = ::tensorflow::ops::AsNodeOutList(scope, other_arguments);
  if (!scope.ok()) return;
  auto _num_parallel_calls = ::tensorflow::ops::AsNodeOut(scope, num_parallel_calls);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("ParallelMapDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "ParallelMapDataset")
                     .Input(_input_dataset)
                     .Input(_other_arguments)
                     .Input(_num_parallel_calls)
                     .Attr("f", f)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

PrefetchDataset::PrefetchDataset(const ::tensorflow::Scope& scope,
                                 ::tensorflow::Input input_dataset,
                                 ::tensorflow::Input buffer_size, const
                                 DataTypeSlice& output_types, const
                                 gtl::ArraySlice<PartialTensorShape>&
                                 output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _buffer_size = ::tensorflow::ops::AsNodeOut(scope, buffer_size);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("PrefetchDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "PrefetchDataset")
                     .Input(_input_dataset)
                     .Input(_buffer_size)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

RangeDataset::RangeDataset(const ::tensorflow::Scope& scope,
                           ::tensorflow::Input start, ::tensorflow::Input stop,
                           ::tensorflow::Input step, const DataTypeSlice&
                           output_types, const
                           gtl::ArraySlice<PartialTensorShape>& output_shapes) {
  if (!scope.ok()) return;
  auto _start = ::tensorflow::ops::AsNodeOut(scope, start);
  if (!scope.ok()) return;
  auto _stop = ::tensorflow::ops::AsNodeOut(scope, stop);
  if (!scope.ok()) return;
  auto _step = ::tensorflow::ops::AsNodeOut(scope, step);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("RangeDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "RangeDataset")
                     .Input(_start)
                     .Input(_stop)
                     .Input(_step)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

RepeatDataset::RepeatDataset(const ::tensorflow::Scope& scope,
                             ::tensorflow::Input input_dataset,
                             ::tensorflow::Input count, const DataTypeSlice&
                             output_types, const
                             gtl::ArraySlice<PartialTensorShape>&
                             output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _count = ::tensorflow::ops::AsNodeOut(scope, count);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("RepeatDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "RepeatDataset")
                     .Input(_input_dataset)
                     .Input(_count)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

RestoreIterator::RestoreIterator(const ::tensorflow::Scope& scope,
                                 ::tensorflow::Input iterator,
                                 ::tensorflow::Input path) {
  if (!scope.ok()) return;
  auto _iterator = ::tensorflow::ops::AsNodeOut(scope, iterator);
  if (!scope.ok()) return;
  auto _path = ::tensorflow::ops::AsNodeOut(scope, path);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("RestoreIterator");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "RestoreIterator")
                     .Input(_iterator)
                     .Input(_path)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

SaveIterator::SaveIterator(const ::tensorflow::Scope& scope,
                           ::tensorflow::Input iterator, ::tensorflow::Input
                           path) {
  if (!scope.ok()) return;
  auto _iterator = ::tensorflow::ops::AsNodeOut(scope, iterator);
  if (!scope.ok()) return;
  auto _path = ::tensorflow::ops::AsNodeOut(scope, path);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SaveIterator");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SaveIterator")
                     .Input(_iterator)
                     .Input(_path)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

ShuffleDataset::ShuffleDataset(const ::tensorflow::Scope& scope,
                               ::tensorflow::Input input_dataset,
                               ::tensorflow::Input buffer_size,
                               ::tensorflow::Input seed, ::tensorflow::Input
                               seed2, const DataTypeSlice& output_types, const
                               gtl::ArraySlice<PartialTensorShape>&
                               output_shapes, const ShuffleDataset::Attrs&
                               attrs) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _buffer_size = ::tensorflow::ops::AsNodeOut(scope, buffer_size);
  if (!scope.ok()) return;
  auto _seed = ::tensorflow::ops::AsNodeOut(scope, seed);
  if (!scope.ok()) return;
  auto _seed2 = ::tensorflow::ops::AsNodeOut(scope, seed2);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("ShuffleDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "ShuffleDataset")
                     .Input(_input_dataset)
                     .Input(_buffer_size)
                     .Input(_seed)
                     .Input(_seed2)
                     .Attr("reshuffle_each_iteration", attrs.reshuffle_each_iteration_)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

ShuffleDataset::ShuffleDataset(const ::tensorflow::Scope& scope,
                               ::tensorflow::Input input_dataset,
                               ::tensorflow::Input buffer_size,
                               ::tensorflow::Input seed, ::tensorflow::Input
                               seed2, const DataTypeSlice& output_types, const
                               gtl::ArraySlice<PartialTensorShape>&
                               output_shapes)
  : ShuffleDataset(scope, input_dataset, buffer_size, seed, seed2, output_types, output_shapes, ShuffleDataset::Attrs()) {}

SkipDataset::SkipDataset(const ::tensorflow::Scope& scope, ::tensorflow::Input
                         input_dataset, ::tensorflow::Input count, const
                         DataTypeSlice& output_types, const
                         gtl::ArraySlice<PartialTensorShape>& output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _count = ::tensorflow::ops::AsNodeOut(scope, count);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SkipDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SkipDataset")
                     .Input(_input_dataset)
                     .Input(_count)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

SloppyInterleaveDataset::SloppyInterleaveDataset(const ::tensorflow::Scope&
                                                 scope, ::tensorflow::Input
                                                 input_dataset,
                                                 ::tensorflow::InputList
                                                 other_arguments,
                                                 ::tensorflow::Input
                                                 cycle_length,
                                                 ::tensorflow::Input
                                                 block_length, const
                                                 NameAttrList& f, const
                                                 DataTypeSlice& output_types,
                                                 const
                                                 gtl::ArraySlice<PartialTensorShape>&
                                                 output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _other_arguments = ::tensorflow::ops::AsNodeOutList(scope, other_arguments);
  if (!scope.ok()) return;
  auto _cycle_length = ::tensorflow::ops::AsNodeOut(scope, cycle_length);
  if (!scope.ok()) return;
  auto _block_length = ::tensorflow::ops::AsNodeOut(scope, block_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SloppyInterleaveDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SloppyInterleaveDataset")
                     .Input(_input_dataset)
                     .Input(_other_arguments)
                     .Input(_cycle_length)
                     .Input(_block_length)
                     .Attr("f", f)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

SparseTensorSliceDataset::SparseTensorSliceDataset(const ::tensorflow::Scope&
                                                   scope, ::tensorflow::Input
                                                   indices, ::tensorflow::Input
                                                   values, ::tensorflow::Input
                                                   dense_shape) {
  if (!scope.ok()) return;
  auto _indices = ::tensorflow::ops::AsNodeOut(scope, indices);
  if (!scope.ok()) return;
  auto _values = ::tensorflow::ops::AsNodeOut(scope, values);
  if (!scope.ok()) return;
  auto _dense_shape = ::tensorflow::ops::AsNodeOut(scope, dense_shape);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SparseTensorSliceDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SparseTensorSliceDataset")
                     .Input(_indices)
                     .Input(_values)
                     .Input(_dense_shape)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

SqlDataset::SqlDataset(const ::tensorflow::Scope& scope, ::tensorflow::Input
                       driver_name, ::tensorflow::Input data_source_name,
                       ::tensorflow::Input query, const DataTypeSlice&
                       output_types, const gtl::ArraySlice<PartialTensorShape>&
                       output_shapes) {
  if (!scope.ok()) return;
  auto _driver_name = ::tensorflow::ops::AsNodeOut(scope, driver_name);
  if (!scope.ok()) return;
  auto _data_source_name = ::tensorflow::ops::AsNodeOut(scope, data_source_name);
  if (!scope.ok()) return;
  auto _query = ::tensorflow::ops::AsNodeOut(scope, query);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("SqlDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "SqlDataset")
                     .Input(_driver_name)
                     .Input(_data_source_name)
                     .Input(_query)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

TFRecordDataset::TFRecordDataset(const ::tensorflow::Scope& scope,
                                 ::tensorflow::Input filenames,
                                 ::tensorflow::Input compression_type,
                                 ::tensorflow::Input buffer_size) {
  if (!scope.ok()) return;
  auto _filenames = ::tensorflow::ops::AsNodeOut(scope, filenames);
  if (!scope.ok()) return;
  auto _compression_type = ::tensorflow::ops::AsNodeOut(scope, compression_type);
  if (!scope.ok()) return;
  auto _buffer_size = ::tensorflow::ops::AsNodeOut(scope, buffer_size);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("TFRecordDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "TFRecordDataset")
                     .Input(_filenames)
                     .Input(_compression_type)
                     .Input(_buffer_size)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

TakeDataset::TakeDataset(const ::tensorflow::Scope& scope, ::tensorflow::Input
                         input_dataset, ::tensorflow::Input count, const
                         DataTypeSlice& output_types, const
                         gtl::ArraySlice<PartialTensorShape>& output_shapes) {
  if (!scope.ok()) return;
  auto _input_dataset = ::tensorflow::ops::AsNodeOut(scope, input_dataset);
  if (!scope.ok()) return;
  auto _count = ::tensorflow::ops::AsNodeOut(scope, count);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("TakeDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "TakeDataset")
                     .Input(_input_dataset)
                     .Input(_count)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

TensorDataset::TensorDataset(const ::tensorflow::Scope& scope,
                             ::tensorflow::InputList components, const
                             gtl::ArraySlice<PartialTensorShape>&
                             output_shapes) {
  if (!scope.ok()) return;
  auto _components = ::tensorflow::ops::AsNodeOutList(scope, components);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("TensorDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "TensorDataset")
                     .Input(_components)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

TensorSliceDataset::TensorSliceDataset(const ::tensorflow::Scope& scope,
                                       ::tensorflow::InputList components,
                                       const
                                       gtl::ArraySlice<PartialTensorShape>&
                                       output_shapes) {
  if (!scope.ok()) return;
  auto _components = ::tensorflow::ops::AsNodeOutList(scope, components);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("TensorSliceDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "TensorSliceDataset")
                     .Input(_components)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

TextLineDataset::TextLineDataset(const ::tensorflow::Scope& scope,
                                 ::tensorflow::Input filenames,
                                 ::tensorflow::Input compression_type,
                                 ::tensorflow::Input buffer_size) {
  if (!scope.ok()) return;
  auto _filenames = ::tensorflow::ops::AsNodeOut(scope, filenames);
  if (!scope.ok()) return;
  auto _compression_type = ::tensorflow::ops::AsNodeOut(scope, compression_type);
  if (!scope.ok()) return;
  auto _buffer_size = ::tensorflow::ops::AsNodeOut(scope, buffer_size);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("TextLineDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "TextLineDataset")
                     .Input(_filenames)
                     .Input(_compression_type)
                     .Input(_buffer_size)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

ZipDataset::ZipDataset(const ::tensorflow::Scope& scope,
                       ::tensorflow::InputList input_datasets, const
                       DataTypeSlice& output_types, const
                       gtl::ArraySlice<PartialTensorShape>& output_shapes) {
  if (!scope.ok()) return;
  auto _input_datasets = ::tensorflow::ops::AsNodeOutList(scope, input_datasets);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("ZipDataset");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "ZipDataset")
                     .Input(_input_datasets)
                     .Attr("output_types", output_types)
                     .Attr("output_shapes", output_shapes)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->handle = Output(ret, 0);
}

/// @}

}  // namespace ops
}  // namespace tensorflow
