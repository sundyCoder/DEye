// This file is MACHINE GENERATED! Do not edit.

#ifndef E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_CTC_OPS_H_
#define E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_CTC_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup ctc_ops Ctc Ops
/// @{

/// Performs beam search decoding on the logits given in input.
///
/// A note about the attribute merge_repeated: For the beam search decoder,
/// this means that if consecutive entries in a beam are the same, only
/// the first of these is emitted.  That is, when the top path is "A B B B B",
/// "A B" is returned if merge_repeated = True but "A B B B B" is
/// returned if merge_repeated = False.
///
/// Arguments:
/// * scope: A Scope object
/// * inputs: 3-D, shape: `(max_time x batch_size x num_classes)`, the logits.
/// * sequence_length: A vector containing sequence lengths, size `(batch)`.
/// * beam_width: A scalar >= 0 (beam search beam width).
/// * top_paths: A scalar >= 0, <= beam_width (controls output size).
///
/// Optional attributes (see `Attrs`):
/// * merge_repeated: If true, merge repeated classes in output.
///
/// Returns:
/// * `OutputList` decoded_indices: A list (length: top_paths) of indices matrices.  Matrix j,
/// size `(total_decoded_outputs[j] x 2)`, has indices of a
/// `SparseTensor<int64, 2>`.  The rows store: [batch, time].
/// * `OutputList` decoded_values: A list (length: top_paths) of values vectors.  Vector j,
/// size `(length total_decoded_outputs[j])`, has the values of a
/// `SparseTensor<int64, 2>`.  The vector stores the decoded classes for beam j.
/// * `OutputList` decoded_shape: A list (length: top_paths) of shape vector.  Vector j,
/// size `(2)`, stores the shape of the decoded `SparseTensor[j]`.
/// Its values are: `[batch_size, max_decoded_length[j]]`.
/// * `Output` log_probability: A matrix, shaped: `(batch_size x top_paths)`.  The
/// sequence log-probabilities.
class CTCBeamSearchDecoder {
 public:
  /// Optional attribute setters for CTCBeamSearchDecoder
  struct Attrs {
    /// If true, merge repeated classes in output.
    ///
    /// Defaults to true
    Attrs MergeRepeated(bool x) {
      Attrs ret = *this;
      ret.merge_repeated_ = x;
      return ret;
    }

    bool merge_repeated_ = true;
  };
  CTCBeamSearchDecoder(const ::tensorflow::Scope& scope, ::tensorflow::Input
                     inputs, ::tensorflow::Input sequence_length, int64
                     beam_width, int64 top_paths);
  CTCBeamSearchDecoder(const ::tensorflow::Scope& scope, ::tensorflow::Input
                     inputs, ::tensorflow::Input sequence_length, int64
                     beam_width, int64 top_paths, const
                     CTCBeamSearchDecoder::Attrs& attrs);

  static Attrs MergeRepeated(bool x) {
    return Attrs().MergeRepeated(x);
  }

  ::tensorflow::OutputList decoded_indices;
  ::tensorflow::OutputList decoded_values;
  ::tensorflow::OutputList decoded_shape;
  ::tensorflow::Output log_probability;
};

/// Performs greedy decoding on the logits given in inputs.
///
/// A note about the attribute merge_repeated: if enabled, when
/// consecutive logits' maximum indices are the same, only the first of
/// these is emitted.  Labeling the blank '*', the sequence "A B B * B B"
/// becomes "A B B" if merge_repeated = True and "A B B B B" if
/// merge_repeated = False.
///
/// Regardless of the value of merge_repeated, if the maximum index of a given
/// time and batch corresponds to the blank, index `(num_classes - 1)`, no new
/// element is emitted.
///
/// Arguments:
/// * scope: A Scope object
/// * inputs: 3-D, shape: `(max_time x batch_size x num_classes)`, the logits.
/// * sequence_length: A vector containing sequence lengths, size `(batch_size)`.
///
/// Optional attributes (see `Attrs`):
/// * merge_repeated: If True, merge repeated classes in output.
///
/// Returns:
/// * `Output` decoded_indices: Indices matrix, size `(total_decoded_outputs x 2)`,
/// of a `SparseTensor<int64, 2>`.  The rows store: [batch, time].
/// * `Output` decoded_values: Values vector, size: `(total_decoded_outputs)`,
/// of a `SparseTensor<int64, 2>`.  The vector stores the decoded classes.
/// * `Output` decoded_shape: Shape vector, size `(2)`, of the decoded SparseTensor.
/// Values are: `[batch_size, max_decoded_length]`.
/// * `Output` log_probability: Matrix, size `(batch_size x 1)`, containing sequence
/// log-probabilities.
class CTCGreedyDecoder {
 public:
  /// Optional attribute setters for CTCGreedyDecoder
  struct Attrs {
    /// If True, merge repeated classes in output.
    ///
    /// Defaults to false
    Attrs MergeRepeated(bool x) {
      Attrs ret = *this;
      ret.merge_repeated_ = x;
      return ret;
    }

    bool merge_repeated_ = false;
  };
  CTCGreedyDecoder(const ::tensorflow::Scope& scope, ::tensorflow::Input inputs,
                 ::tensorflow::Input sequence_length);
  CTCGreedyDecoder(const ::tensorflow::Scope& scope, ::tensorflow::Input inputs,
                 ::tensorflow::Input sequence_length, const
                 CTCGreedyDecoder::Attrs& attrs);

  static Attrs MergeRepeated(bool x) {
    return Attrs().MergeRepeated(x);
  }

  ::tensorflow::Output decoded_indices;
  ::tensorflow::Output decoded_values;
  ::tensorflow::Output decoded_shape;
  ::tensorflow::Output log_probability;
};

/// Calculates the CTC Loss (log probability) for each batch entry.  Also calculates
///
/// the gradient.  This class performs the softmax operation for you, so inputs
/// should be e.g. linear projections of outputs by an LSTM.
///
/// Arguments:
/// * scope: A Scope object
/// * inputs: 3-D, shape: `(max_time x batch_size x num_classes)`, the logits.
/// * labels_indices: The indices of a `SparseTensor<int32, 2>`.
/// `labels_indices(i, :) == [b, t]` means `labels_values(i)` stores the id for
/// `(batch b, time t)`.
/// * labels_values: The values (labels) associated with the given batch and time.
/// * sequence_length: A vector containing sequence lengths (batch).
///
/// Optional attributes (see `Attrs`):
/// * preprocess_collapse_repeated: Scalar, if true then repeated labels are
/// collapsed prior to the CTC calculation.
/// * ctc_merge_repeated: Scalar.  If set to false, *during* CTC calculation
/// repeated non-blank labels will not be merged and are interpreted as
/// individual labels.  This is a simplified version of CTC.
/// * ignore_longer_outputs_than_inputs: Scalar. If set to true, during CTC
/// calculation, items that have longer output sequences than input sequences
/// are skipped: they don't contribute to the loss term and have zero-gradient.
///
/// Returns:
/// * `Output` loss: A vector (batch) containing log-probabilities.
/// * `Output` gradient: The gradient of `loss`.  3-D, shape:
/// `(max_time x batch_size x num_classes)`.
class CTCLoss {
 public:
  /// Optional attribute setters for CTCLoss
  struct Attrs {
    /// Scalar, if true then repeated labels are
    /// collapsed prior to the CTC calculation.
    ///
    /// Defaults to false
    Attrs PreprocessCollapseRepeated(bool x) {
      Attrs ret = *this;
      ret.preprocess_collapse_repeated_ = x;
      return ret;
    }

    /// Scalar.  If set to false, *during* CTC calculation
    /// repeated non-blank labels will not be merged and are interpreted as
    /// individual labels.  This is a simplified version of CTC.
    ///
    /// Defaults to true
    Attrs CtcMergeRepeated(bool x) {
      Attrs ret = *this;
      ret.ctc_merge_repeated_ = x;
      return ret;
    }

    /// Scalar. If set to true, during CTC
    /// calculation, items that have longer output sequences than input sequences
    /// are skipped: they don't contribute to the loss term and have zero-gradient.
    ///
    /// Defaults to false
    Attrs IgnoreLongerOutputsThanInputs(bool x) {
      Attrs ret = *this;
      ret.ignore_longer_outputs_than_inputs_ = x;
      return ret;
    }

    bool preprocess_collapse_repeated_ = false;
    bool ctc_merge_repeated_ = true;
    bool ignore_longer_outputs_than_inputs_ = false;
  };
  CTCLoss(const ::tensorflow::Scope& scope, ::tensorflow::Input inputs,
        ::tensorflow::Input labels_indices, ::tensorflow::Input labels_values,
        ::tensorflow::Input sequence_length);
  CTCLoss(const ::tensorflow::Scope& scope, ::tensorflow::Input inputs,
        ::tensorflow::Input labels_indices, ::tensorflow::Input labels_values,
        ::tensorflow::Input sequence_length, const CTCLoss::Attrs& attrs);

  static Attrs PreprocessCollapseRepeated(bool x) {
    return Attrs().PreprocessCollapseRepeated(x);
  }
  static Attrs CtcMergeRepeated(bool x) {
    return Attrs().CtcMergeRepeated(x);
  }
  static Attrs IgnoreLongerOutputsThanInputs(bool x) {
    return Attrs().IgnoreLongerOutputsThanInputs(x);
  }

  ::tensorflow::Output loss;
  ::tensorflow::Output gradient;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_CTC_OPS_H_
