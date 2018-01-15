// This file is MACHINE GENERATED! Do not edit.

#ifndef E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SPECTRAL_OPS_H_
#define E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SPECTRAL_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup spectral_ops Spectral Ops
/// @{

/// Fast Fourier transform.
///
/// Computes the 1-dimensional discrete Fourier transform over the inner-most
/// dimension of `input`.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A complex64 tensor.
///
/// Returns:
/// * `Output`: A complex64 tensor of the same shape as `input`. The inner-most
///   dimension of `input` is replaced with its 1D Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.fft
/// @end_compatibility
class FFT {
 public:
  FFT(const ::tensorflow::Scope& scope, ::tensorflow::Input input);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// 2D fast Fourier transform.
///
/// Computes the 2-dimensional discrete Fourier transform over the inner-most
/// 2 dimensions of `input`.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A complex64 tensor.
///
/// Returns:
/// * `Output`: A complex64 tensor of the same shape as `input`. The inner-most 2
///   dimensions of `input` are replaced with their 2D Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.fft2
/// @end_compatibility
class FFT2D {
 public:
  FFT2D(const ::tensorflow::Scope& scope, ::tensorflow::Input input);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// 3D fast Fourier transform.
///
/// Computes the 3-dimensional discrete Fourier transform over the inner-most 3
/// dimensions of `input`.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A complex64 tensor.
///
/// Returns:
/// * `Output`: A complex64 tensor of the same shape as `input`. The inner-most 3
///   dimensions of `input` are replaced with their 3D Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.fftn with 3 dimensions.
/// @end_compatibility
class FFT3D {
 public:
  FFT3D(const ::tensorflow::Scope& scope, ::tensorflow::Input input);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// Inverse fast Fourier transform.
///
/// Computes the inverse 1-dimensional discrete Fourier transform over the
/// inner-most dimension of `input`.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A complex64 tensor.
///
/// Returns:
/// * `Output`: A complex64 tensor of the same shape as `input`. The inner-most
///   dimension of `input` is replaced with its inverse 1D Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.ifft
/// @end_compatibility
class IFFT {
 public:
  IFFT(const ::tensorflow::Scope& scope, ::tensorflow::Input input);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// Inverse 2D fast Fourier transform.
///
/// Computes the inverse 2-dimensional discrete Fourier transform over the
/// inner-most 2 dimensions of `input`.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A complex64 tensor.
///
/// Returns:
/// * `Output`: A complex64 tensor of the same shape as `input`. The inner-most 2
///   dimensions of `input` are replaced with their inverse 2D Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.ifft2
/// @end_compatibility
class IFFT2D {
 public:
  IFFT2D(const ::tensorflow::Scope& scope, ::tensorflow::Input input);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// Inverse 3D fast Fourier transform.
///
/// Computes the inverse 3-dimensional discrete Fourier transform over the
/// inner-most 3 dimensions of `input`.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A complex64 tensor.
///
/// Returns:
/// * `Output`: A complex64 tensor of the same shape as `input`. The inner-most 3
///   dimensions of `input` are replaced with their inverse 3D Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.ifftn with 3 dimensions.
/// @end_compatibility
class IFFT3D {
 public:
  IFFT3D(const ::tensorflow::Scope& scope, ::tensorflow::Input input);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// Inverse real-valued fast Fourier transform.
///
/// Computes the inverse 1-dimensional discrete Fourier transform of a real-valued
/// signal over the inner-most dimension of `input`.
///
/// The inner-most dimension of `input` is assumed to be the result of `RFFT`: the
/// `fft_length / 2 + 1` unique components of the DFT of a real-valued signal. If
/// `fft_length` is not provided, it is computed from the size of the inner-most
/// dimension of `input` (`fft_length = 2 * (inner - 1)`). If the FFT length used to
/// compute `input` is odd, it should be provided since it cannot be inferred
/// properly.
///
/// Along the axis `IRFFT` is computed on, if `fft_length / 2 + 1` is smaller
/// than the corresponding dimension of `input`, the dimension is cropped. If it is
/// larger, the dimension is padded with zeros.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A complex64 tensor.
/// * fft_length: An int32 tensor of shape [1]. The FFT length.
///
/// Returns:
/// * `Output`: A float32 tensor of the same rank as `input`. The inner-most
///   dimension of `input` is replaced with the `fft_length` samples of its inverse
///   1D Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.irfft
/// @end_compatibility
class IRFFT {
 public:
  IRFFT(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
      ::tensorflow::Input fft_length);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// Inverse 2D real-valued fast Fourier transform.
///
/// Computes the inverse 2-dimensional discrete Fourier transform of a real-valued
/// signal over the inner-most 2 dimensions of `input`.
///
/// The inner-most 2 dimensions of `input` are assumed to be the result of `RFFT2D`:
/// The inner-most dimension contains the `fft_length / 2 + 1` unique components of
/// the DFT of a real-valued signal. If `fft_length` is not provided, it is computed
/// from the size of the inner-most 2 dimensions of `input`. If the FFT length used
/// to compute `input` is odd, it should be provided since it cannot be inferred
/// properly.
///
/// Along each axis `IRFFT2D` is computed on, if `fft_length` (or
/// `fft_length / 2 + 1` for the inner-most dimension) is smaller than the
/// corresponding dimension of `input`, the dimension is cropped. If it is larger,
/// the dimension is padded with zeros.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A complex64 tensor.
/// * fft_length: An int32 tensor of shape [2]. The FFT length for each dimension.
///
/// Returns:
/// * `Output`: A float32 tensor of the same rank as `input`. The inner-most 2
///   dimensions of `input` are replaced with the `fft_length` samples of their
///   inverse 2D Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.irfft2
/// @end_compatibility
class IRFFT2D {
 public:
  IRFFT2D(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
        ::tensorflow::Input fft_length);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// Inverse 3D real-valued fast Fourier transform.
///
/// Computes the inverse 3-dimensional discrete Fourier transform of a real-valued
/// signal over the inner-most 3 dimensions of `input`.
///
/// The inner-most 3 dimensions of `input` are assumed to be the result of `RFFT3D`:
/// The inner-most dimension contains the `fft_length / 2 + 1` unique components of
/// the DFT of a real-valued signal. If `fft_length` is not provided, it is computed
/// from the size of the inner-most 3 dimensions of `input`. If the FFT length used
/// to compute `input` is odd, it should be provided since it cannot be inferred
/// properly.
///
/// Along each axis `IRFFT3D` is computed on, if `fft_length` (or
/// `fft_length / 2 + 1` for the inner-most dimension) is smaller than the
/// corresponding dimension of `input`, the dimension is cropped. If it is larger,
/// the dimension is padded with zeros.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A complex64 tensor.
/// * fft_length: An int32 tensor of shape [3]. The FFT length for each dimension.
///
/// Returns:
/// * `Output`: A float32 tensor of the same rank as `input`. The inner-most 3
///   dimensions of `input` are replaced with the `fft_length` samples of their
///   inverse 3D real Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.irfftn with 3 dimensions.
/// @end_compatibility
class IRFFT3D {
 public:
  IRFFT3D(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
        ::tensorflow::Input fft_length);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// Real-valued fast Fourier transform.
///
/// Computes the 1-dimensional discrete Fourier transform of a real-valued signal
/// over the inner-most dimension of `input`.
///
/// Since the DFT of a real signal is Hermitian-symmetric, `RFFT` only returns the
/// `fft_length / 2 + 1` unique components of the FFT: the zero-frequency term,
/// followed by the `fft_length / 2` positive-frequency terms.
///
/// Along the axis `RFFT` is computed on, if `fft_length` is smaller than the
/// corresponding dimension of `input`, the dimension is cropped. If it is larger,
/// the dimension is padded with zeros.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A float32 tensor.
/// * fft_length: An int32 tensor of shape [1]. The FFT length.
///
/// Returns:
/// * `Output`: A complex64 tensor of the same rank as `input`. The inner-most
///   dimension of `input` is replaced with the `fft_length / 2 + 1` unique
///   frequency components of its 1D Fourier transform.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.rfft
/// @end_compatibility
class RFFT {
 public:
  RFFT(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
     ::tensorflow::Input fft_length);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// 2D real-valued fast Fourier transform.
///
/// Computes the 2-dimensional discrete Fourier transform of a real-valued signal
/// over the inner-most 2 dimensions of `input`.
///
/// Since the DFT of a real signal is Hermitian-symmetric, `RFFT2D` only returns the
/// `fft_length / 2 + 1` unique components of the FFT for the inner-most dimension
/// of `output`: the zero-frequency term, followed by the `fft_length / 2`
/// positive-frequency terms.
///
/// Along each axis `RFFT2D` is computed on, if `fft_length` is smaller than the
/// corresponding dimension of `input`, the dimension is cropped. If it is larger,
/// the dimension is padded with zeros.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A float32 tensor.
/// * fft_length: An int32 tensor of shape [2]. The FFT length for each dimension.
///
/// Returns:
/// * `Output`: A complex64 tensor of the same rank as `input`. The inner-most 2
///   dimensions of `input` are replaced with their 2D Fourier transform. The
///   inner-most dimension contains `fft_length / 2 + 1` unique frequency
///   components.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.rfft2
/// @end_compatibility
class RFFT2D {
 public:
  RFFT2D(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
       ::tensorflow::Input fft_length);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// 3D real-valued fast Fourier transform.
///
/// Computes the 3-dimensional discrete Fourier transform of a real-valued signal
/// over the inner-most 3 dimensions of `input`.
///
/// Since the DFT of a real signal is Hermitian-symmetric, `RFFT3D` only returns the
/// `fft_length / 2 + 1` unique components of the FFT for the inner-most dimension
/// of `output`: the zero-frequency term, followed by the `fft_length / 2`
/// positive-frequency terms.
///
/// Along each axis `RFFT3D` is computed on, if `fft_length` is smaller than the
/// corresponding dimension of `input`, the dimension is cropped. If it is larger,
/// the dimension is padded with zeros.
///
/// Arguments:
/// * scope: A Scope object
/// * input: A float32 tensor.
/// * fft_length: An int32 tensor of shape [3]. The FFT length for each dimension.
///
/// Returns:
/// * `Output`: A complex64 tensor of the same rank as `input`. The inner-most 3
///   dimensions of `input` are replaced with the their 3D Fourier transform. The
///   inner-most dimension contains `fft_length / 2 + 1` unique frequency
///   components.
///
/// @compatibility(numpy)
/// Equivalent to np.fft.rfftn with 3 dimensions.
/// @end_compatibility
class RFFT3D {
 public:
  RFFT3D(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
       ::tensorflow::Input fft_length);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  ::tensorflow::Output output;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SPECTRAL_OPS_H_
