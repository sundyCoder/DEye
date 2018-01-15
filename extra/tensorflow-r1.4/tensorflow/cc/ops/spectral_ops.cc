// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/spectral_ops.h"

namespace tensorflow {
namespace ops {

FFT::FFT(const ::tensorflow::Scope& scope, ::tensorflow::Input input) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("FFT");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "FFT")
                     .Input(_input)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

FFT2D::FFT2D(const ::tensorflow::Scope& scope, ::tensorflow::Input input) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("FFT2D");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "FFT2D")
                     .Input(_input)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

FFT3D::FFT3D(const ::tensorflow::Scope& scope, ::tensorflow::Input input) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("FFT3D");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "FFT3D")
                     .Input(_input)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

IFFT::IFFT(const ::tensorflow::Scope& scope, ::tensorflow::Input input) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IFFT");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IFFT")
                     .Input(_input)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

IFFT2D::IFFT2D(const ::tensorflow::Scope& scope, ::tensorflow::Input input) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IFFT2D");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IFFT2D")
                     .Input(_input)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

IFFT3D::IFFT3D(const ::tensorflow::Scope& scope, ::tensorflow::Input input) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IFFT3D");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IFFT3D")
                     .Input(_input)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

IRFFT::IRFFT(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
             ::tensorflow::Input fft_length) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  auto _fft_length = ::tensorflow::ops::AsNodeOut(scope, fft_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IRFFT");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IRFFT")
                     .Input(_input)
                     .Input(_fft_length)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

IRFFT2D::IRFFT2D(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
                 ::tensorflow::Input fft_length) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  auto _fft_length = ::tensorflow::ops::AsNodeOut(scope, fft_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IRFFT2D");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IRFFT2D")
                     .Input(_input)
                     .Input(_fft_length)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

IRFFT3D::IRFFT3D(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
                 ::tensorflow::Input fft_length) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  auto _fft_length = ::tensorflow::ops::AsNodeOut(scope, fft_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("IRFFT3D");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "IRFFT3D")
                     .Input(_input)
                     .Input(_fft_length)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

RFFT::RFFT(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
           ::tensorflow::Input fft_length) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  auto _fft_length = ::tensorflow::ops::AsNodeOut(scope, fft_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("RFFT");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "RFFT")
                     .Input(_input)
                     .Input(_fft_length)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

RFFT2D::RFFT2D(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
               ::tensorflow::Input fft_length) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  auto _fft_length = ::tensorflow::ops::AsNodeOut(scope, fft_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("RFFT2D");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "RFFT2D")
                     .Input(_input)
                     .Input(_fft_length)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

RFFT3D::RFFT3D(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
               ::tensorflow::Input fft_length) {
  if (!scope.ok()) return;
  auto _input = ::tensorflow::ops::AsNodeOut(scope, input);
  if (!scope.ok()) return;
  auto _fft_length = ::tensorflow::ops::AsNodeOut(scope, fft_length);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("RFFT3D");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "RFFT3D")
                     .Input(_input)
                     .Input(_fft_length)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->output = Output(ret, 0);
}

/// @}

}  // namespace ops
}  // namespace tensorflow
