// This file is MACHINE GENERATED! Do not edit.

#ifndef E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SENDRECV_OPS_H_
#define E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SENDRECV_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup sendrecv_ops Sendrecv Ops
/// @{

/// Receives the named tensor from send_device on recv_device.
///
/// _HostRecv requires its input on host memory whereas _Recv requires its
/// input on device memory.
///
/// Arguments:
/// * scope: A Scope object
/// * tensor_name: The name of the tensor to receive.
/// * send_device: The name of the device sending the tensor.
/// * send_device_incarnation: The current incarnation of send_device.
/// * recv_device: The name of the device receiving the tensor.
///
/// Optional attributes (see `Attrs`):
/// * client_terminated: If set to true, this indicates that the node was added
/// to the graph as a result of a client-side feed or fetch of Tensor data,
/// in which case the corresponding send or recv is expected to be managed
/// locally by the caller.
///
/// Returns:
/// * `Output`: The tensor to receive.
class _HostRecv {
 public:
  /// Optional attribute setters for _HostRecv
  struct Attrs {
    /// If set to true, this indicates that the node was added
    /// to the graph as a result of a client-side feed or fetch of Tensor data,
    /// in which case the corresponding send or recv is expected to be managed
    /// locally by the caller.
    ///
    /// Defaults to false
    Attrs ClientTerminated(bool x) {
      Attrs ret = *this;
      ret.client_terminated_ = x;
      return ret;
    }

    bool client_terminated_ = false;
  };
  _HostRecv(const ::tensorflow::Scope& scope, DataType tensor_type, StringPiece
          tensor_name, StringPiece send_device, int64 send_device_incarnation,
          StringPiece recv_device);
  _HostRecv(const ::tensorflow::Scope& scope, DataType tensor_type, StringPiece
          tensor_name, StringPiece send_device, int64 send_device_incarnation,
          StringPiece recv_device, const _HostRecv::Attrs& attrs);
  operator ::tensorflow::Output() const { return tensor; }
  operator ::tensorflow::Input() const { return tensor; }
  ::tensorflow::Node* node() const { return tensor.node(); }

  static Attrs ClientTerminated(bool x) {
    return Attrs().ClientTerminated(x);
  }

  ::tensorflow::Output tensor;
};

/// Sends the named tensor from send_device to recv_device.
///
/// _HostSend requires its input on host memory whereas _Send requires its
/// input on device memory.
///
/// Arguments:
/// * scope: A Scope object
/// * tensor: The tensor to send.
/// * tensor_name: The name of the tensor to send.
/// * send_device: The name of the device sending the tensor.
/// * send_device_incarnation: The current incarnation of send_device.
/// * recv_device: The name of the device receiving the tensor.
///
/// Optional attributes (see `Attrs`):
/// * client_terminated: If set to true, this indicates that the node was added
/// to the graph as a result of a client-side feed or fetch of Tensor data,
/// in which case the corresponding send or recv is expected to be managed
/// locally by the caller.
///
/// Returns:
/// * the created `Operation`
class _HostSend {
 public:
  /// Optional attribute setters for _HostSend
  struct Attrs {
    /// If set to true, this indicates that the node was added
    /// to the graph as a result of a client-side feed or fetch of Tensor data,
    /// in which case the corresponding send or recv is expected to be managed
    /// locally by the caller.
    ///
    /// Defaults to false
    Attrs ClientTerminated(bool x) {
      Attrs ret = *this;
      ret.client_terminated_ = x;
      return ret;
    }

    bool client_terminated_ = false;
  };
  _HostSend(const ::tensorflow::Scope& scope, ::tensorflow::Input tensor,
          StringPiece tensor_name, StringPiece send_device, int64
          send_device_incarnation, StringPiece recv_device);
  _HostSend(const ::tensorflow::Scope& scope, ::tensorflow::Input tensor,
          StringPiece tensor_name, StringPiece send_device, int64
          send_device_incarnation, StringPiece recv_device, const
          _HostSend::Attrs& attrs);
  operator ::tensorflow::Operation() const { return operation; }

  static Attrs ClientTerminated(bool x) {
    return Attrs().ClientTerminated(x);
  }

  Operation operation;
};

/// Receives the named tensor from send_device on recv_device.
///
/// Arguments:
/// * scope: A Scope object
/// * tensor_name: The name of the tensor to receive.
/// * send_device: The name of the device sending the tensor.
/// * send_device_incarnation: The current incarnation of send_device.
/// * recv_device: The name of the device receiving the tensor.
///
/// Optional attributes (see `Attrs`):
/// * client_terminated: If set to true, this indicates that the node was added
/// to the graph as a result of a client-side feed or fetch of Tensor data,
/// in which case the corresponding send or recv is expected to be managed
/// locally by the caller.
///
/// Returns:
/// * `Output`: The tensor to receive.
class _Recv {
 public:
  /// Optional attribute setters for _Recv
  struct Attrs {
    /// If set to true, this indicates that the node was added
    /// to the graph as a result of a client-side feed or fetch of Tensor data,
    /// in which case the corresponding send or recv is expected to be managed
    /// locally by the caller.
    ///
    /// Defaults to false
    Attrs ClientTerminated(bool x) {
      Attrs ret = *this;
      ret.client_terminated_ = x;
      return ret;
    }

    bool client_terminated_ = false;
  };
  _Recv(const ::tensorflow::Scope& scope, DataType tensor_type, StringPiece
      tensor_name, StringPiece send_device, int64 send_device_incarnation,
      StringPiece recv_device);
  _Recv(const ::tensorflow::Scope& scope, DataType tensor_type, StringPiece
      tensor_name, StringPiece send_device, int64 send_device_incarnation,
      StringPiece recv_device, const _Recv::Attrs& attrs);
  operator ::tensorflow::Output() const { return tensor; }
  operator ::tensorflow::Input() const { return tensor; }
  ::tensorflow::Node* node() const { return tensor.node(); }

  static Attrs ClientTerminated(bool x) {
    return Attrs().ClientTerminated(x);
  }

  ::tensorflow::Output tensor;
};

/// Sends the named tensor from send_device to recv_device.
///
/// Arguments:
/// * scope: A Scope object
/// * tensor: The tensor to send.
/// * tensor_name: The name of the tensor to send.
/// * send_device: The name of the device sending the tensor.
/// * send_device_incarnation: The current incarnation of send_device.
/// * recv_device: The name of the device receiving the tensor.
///
/// Optional attributes (see `Attrs`):
/// * client_terminated: If set to true, this indicates that the node was added
/// to the graph as a result of a client-side feed or fetch of Tensor data,
/// in which case the corresponding send or recv is expected to be managed
/// locally by the caller.
///
/// Returns:
/// * the created `Operation`
class _Send {
 public:
  /// Optional attribute setters for _Send
  struct Attrs {
    /// If set to true, this indicates that the node was added
    /// to the graph as a result of a client-side feed or fetch of Tensor data,
    /// in which case the corresponding send or recv is expected to be managed
    /// locally by the caller.
    ///
    /// Defaults to false
    Attrs ClientTerminated(bool x) {
      Attrs ret = *this;
      ret.client_terminated_ = x;
      return ret;
    }

    bool client_terminated_ = false;
  };
  _Send(const ::tensorflow::Scope& scope, ::tensorflow::Input tensor, StringPiece
      tensor_name, StringPiece send_device, int64 send_device_incarnation,
      StringPiece recv_device);
  _Send(const ::tensorflow::Scope& scope, ::tensorflow::Input tensor, StringPiece
      tensor_name, StringPiece send_device, int64 send_device_incarnation,
      StringPiece recv_device, const _Send::Attrs& attrs);
  operator ::tensorflow::Operation() const { return operation; }

  static Attrs ClientTerminated(bool x) {
    return Attrs().ClientTerminated(x);
  }

  Operation operation;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SENDRECV_OPS_H_
