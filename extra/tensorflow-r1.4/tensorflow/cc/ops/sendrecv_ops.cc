// This file is MACHINE GENERATED! Do not edit.


#include "tensorflow/cc/ops/const_op.h"
#include "E:/jlchen/tensorflow/tensorflow/contrib/cmake/build/tensorflow/cc/ops/sendrecv_ops.h"

namespace tensorflow {
namespace ops {

_HostRecv::_HostRecv(const ::tensorflow::Scope& scope, DataType tensor_type,
                     StringPiece tensor_name, StringPiece send_device, int64
                     send_device_incarnation, StringPiece recv_device, const
                     _HostRecv::Attrs& attrs) {
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("_HostRecv");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "_HostRecv")
                     .Attr("tensor_type", tensor_type)
                     .Attr("tensor_name", tensor_name)
                     .Attr("send_device", send_device)
                     .Attr("send_device_incarnation", send_device_incarnation)
                     .Attr("recv_device", recv_device)
                     .Attr("client_terminated", attrs.client_terminated_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->tensor = Output(ret, 0);
}

_HostRecv::_HostRecv(const ::tensorflow::Scope& scope, DataType tensor_type,
                     StringPiece tensor_name, StringPiece send_device, int64
                     send_device_incarnation, StringPiece recv_device)
  : _HostRecv(scope, tensor_type, tensor_name, send_device, send_device_incarnation, recv_device, _HostRecv::Attrs()) {}

_HostSend::_HostSend(const ::tensorflow::Scope& scope, ::tensorflow::Input
                     tensor, StringPiece tensor_name, StringPiece send_device,
                     int64 send_device_incarnation, StringPiece recv_device,
                     const _HostSend::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _tensor = ::tensorflow::ops::AsNodeOut(scope, tensor);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("_HostSend");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "_HostSend")
                     .Input(_tensor)
                     .Attr("tensor_name", tensor_name)
                     .Attr("send_device", send_device)
                     .Attr("send_device_incarnation", send_device_incarnation)
                     .Attr("recv_device", recv_device)
                     .Attr("client_terminated", attrs.client_terminated_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

_HostSend::_HostSend(const ::tensorflow::Scope& scope, ::tensorflow::Input
                     tensor, StringPiece tensor_name, StringPiece send_device,
                     int64 send_device_incarnation, StringPiece recv_device)
  : _HostSend(scope, tensor, tensor_name, send_device, send_device_incarnation, recv_device, _HostSend::Attrs()) {}

_Recv::_Recv(const ::tensorflow::Scope& scope, DataType tensor_type,
             StringPiece tensor_name, StringPiece send_device, int64
             send_device_incarnation, StringPiece recv_device, const
             _Recv::Attrs& attrs) {
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("_Recv");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "_Recv")
                     .Attr("tensor_type", tensor_type)
                     .Attr("tensor_name", tensor_name)
                     .Attr("send_device", send_device)
                     .Attr("send_device_incarnation", send_device_incarnation)
                     .Attr("recv_device", recv_device)
                     .Attr("client_terminated", attrs.client_terminated_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->tensor = Output(ret, 0);
}

_Recv::_Recv(const ::tensorflow::Scope& scope, DataType tensor_type,
             StringPiece tensor_name, StringPiece send_device, int64
             send_device_incarnation, StringPiece recv_device)
  : _Recv(scope, tensor_type, tensor_name, send_device, send_device_incarnation, recv_device, _Recv::Attrs()) {}

_Send::_Send(const ::tensorflow::Scope& scope, ::tensorflow::Input tensor,
             StringPiece tensor_name, StringPiece send_device, int64
             send_device_incarnation, StringPiece recv_device, const
             _Send::Attrs& attrs) {
  if (!scope.ok()) return;
  auto _tensor = ::tensorflow::ops::AsNodeOut(scope, tensor);
  if (!scope.ok()) return;
  ::tensorflow::Node* ret;
  const auto unique_name = scope.GetUniqueNameForOp("_Send");
  auto builder = ::tensorflow::NodeBuilder(unique_name, "_Send")
                     .Input(_tensor)
                     .Attr("tensor_name", tensor_name)
                     .Attr("send_device", send_device)
                     .Attr("send_device_incarnation", send_device_incarnation)
                     .Attr("recv_device", recv_device)
                     .Attr("client_terminated", attrs.client_terminated_)
  ;
  scope.UpdateBuilder(&builder);
  scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));
  if (!scope.ok()) return;
  scope.UpdateStatus(scope.DoShapeInference(ret));
  this->operation = Operation(ret);
  return;
}

_Send::_Send(const ::tensorflow::Scope& scope, ::tensorflow::Input tensor,
             StringPiece tensor_name, StringPiece send_device, int64
             send_device_incarnation, StringPiece recv_device)
  : _Send(scope, tensor, tensor_name, send_device, send_device_incarnation, recv_device, _Send::Attrs()) {}

/// @}

}  // namespace ops
}  // namespace tensorflow
