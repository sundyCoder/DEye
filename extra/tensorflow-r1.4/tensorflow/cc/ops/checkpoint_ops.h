// This file is MACHINE GENERATED! Do not edit.

#ifndef E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_CHECKPOINT_OPS_H_
#define E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_CHECKPOINT_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup checkpoint_ops Checkpoint Ops
/// @{

/// Given a path to new and old vocabulary files, returns a remapping Tensor of
///
/// length `num_new_vocab`, where `remapping[i]` contains the row number in the old
/// vocabulary that corresponds to row `i` in the new vocabulary (starting at line
/// `new_vocab_offset` and up to `num_new_vocab` entities), or `-1` if entry `i`
/// in the new vocabulary is not in the old vocabulary.  `num_vocab_offset` enables
/// use in the partitioned variable case, and should generally be set through
/// examining partitioning info.  The format of the files should be a text file,
/// with each line containing a single entity within the vocabulary.
///
/// For example, with `new_vocab_file` a text file containing each of the following
/// elements on a single line: `[f0, f1, f2, f3]`, old_vocab_file = [f1, f0, f3],
/// `num_new_vocab = 3, new_vocab_offset = 1`, the returned remapping would be
/// `[0, -1, 2]`.
///
/// The op also returns a count of how many entries in the new vocabulary
/// were present in the old vocabulary, which is used to calculate the number of
/// values to initialize in a weight matrix remapping
///
/// This functionality can be used to remap both row vocabularies (typically,
/// features) and column vocabularies (typically, classes) from TensorFlow
/// checkpoints.  Note that the partitioning logic relies on contiguous vocabularies
/// corresponding to div-partitioned variables.  Moreover, the underlying remapping
/// uses an IndexTable (as opposed to an inexact CuckooTable), so client code should
/// use the corresponding index_table_from_file() as the FeatureColumn framework
/// does (as opposed to tf.feature_to_id(), which uses a CuckooTable).
///
/// Arguments:
/// * scope: A Scope object
/// * new_vocab_file: Path to the new vocab file.
/// * old_vocab_file: Path to the old vocab file.
/// * new_vocab_offset: How many entries into the new vocab file to start reading.
/// * num_new_vocab: Number of entries in the new vocab file to remap.
///
/// Returns:
/// * `Output` remapping: A Tensor of length num_new_vocab where the element at index i
/// is equal to the old ID that maps to the new ID i.  This element is -1 for any
/// new ID that is not found in the old vocabulary.
/// * `Output` num_present: Number of new vocab entries found in old vocab.
class GenerateVocabRemapping {
 public:
  GenerateVocabRemapping(const ::tensorflow::Scope& scope, ::tensorflow::Input
                       new_vocab_file, ::tensorflow::Input old_vocab_file,
                       int64 new_vocab_offset, int64 num_new_vocab);

  ::tensorflow::Output remapping;
  ::tensorflow::Output num_present;
};

/// Loads a 2-D (matrix) `Tensor` with name `old_tensor_name` from the checkpoint
///
/// at `ckpt_path` and potentially reorders its rows and columns using the
/// specified remappings.
///
/// Most users should use one of the wrapper initializers (such as
/// `tf.contrib.framework.load_and_remap_matrix_initializer`) instead of this
/// function directly.
///
/// The remappings are 1-D tensors with the following properties:
///
/// * `row_remapping` must have exactly `num_rows` entries. Row `i` of the output
///   matrix will be initialized from the row corresponding to index
///   `row_remapping[i]` in the old `Tensor` from the checkpoint.
/// * `col_remapping` must have either 0 entries (indicating that no column
///   reordering is needed) or `num_cols` entries. If specified, column `j` of the
///   output matrix will be initialized from the column corresponding to index
///   `col_remapping[j]` in the old `Tensor` from the checkpoint.
/// * A value of -1 in either of the remappings signifies a "missing" entry. In that
///   case, values from the `initializing_values` tensor will be used to fill that
///   missing row or column. If `row_remapping` has `r` missing entries and
///   `col_remapping` has `c` missing entries, then the following condition must be
///   true:
///
/// `(r * num_cols) + (c * num_rows) - (r * c) == len(initializing_values)`
///
/// The remapping tensors can be generated using the GenerateVocabRemapping op.
///
/// As an example, with row_remapping = [1, 0, -1], col_remapping = [0, 2, -1],
/// initializing_values = [0.5, -0.5, 0.25, -0.25, 42], and w(i, j) representing
/// the value from row i, column j of the old tensor in the checkpoint, the output
/// matrix will look like the following:
///
/// [[w(1, 0),  w(1, 2),  0.5],
///  [w(0, 0),  w(0, 2), -0.5],
///  [0.25,    -0.25,      42]]
///
/// Arguments:
/// * scope: A Scope object
/// * ckpt_path: Path to the TensorFlow checkpoint (version 2, `TensorBundle`) from
/// which the old matrix `Tensor` will be loaded.
/// * old_tensor_name: Name of the 2-D `Tensor` to load from checkpoint.
/// * row_remapping: An int `Tensor` of row remappings (generally created by
/// `generate_vocab_remapping`).  Even if no row remapping is needed, this must
/// still be an index-valued Tensor (e.g. [0, 1, 2, ...]), or a shifted
/// index-valued `Tensor` (e.g. [8, 9, 10, ...], for partitioned `Variables`).
/// * col_remapping: An int `Tensor` of column remappings (generally created by
/// `generate_vocab_remapping`).  May be a size-0 `Tensor` if only row remapping
/// is to be done (e.g. column ordering is the same).
/// * initializing_values: A float `Tensor` containing  values to fill in for cells
/// in the output matrix that are not loaded from the checkpoint. Length must be
/// exactly the same as the number of missing / new cells.
/// * num_rows: Number of rows (length of the 1st dimension) in the output matrix.
/// * num_cols: Number of columns (length of the 2nd dimension) in the output matrix.
///
/// Optional attributes (see `Attrs`):
/// * max_rows_in_memory: The maximum number of rows to load from the checkpoint at
/// once. If less than or equal to 0, the entire matrix will be loaded into
/// memory. Setting this arg trades increased disk reads for lower memory usage.
///
/// Returns:
/// * `Output`: Output matrix containing existing values loaded from the
/// checkpoint, and with any missing values filled in from initializing_values.
class LoadAndRemapMatrix {
 public:
  /// Optional attribute setters for LoadAndRemapMatrix
  struct Attrs {
    /// The maximum number of rows to load from the checkpoint at
    /// once. If less than or equal to 0, the entire matrix will be loaded into
    /// memory. Setting this arg trades increased disk reads for lower memory usage.
    ///
    /// Defaults to -1
    Attrs MaxRowsInMemory(int64 x) {
      Attrs ret = *this;
      ret.max_rows_in_memory_ = x;
      return ret;
    }

    int64 max_rows_in_memory_ = -1;
  };
  LoadAndRemapMatrix(const ::tensorflow::Scope& scope, ::tensorflow::Input
                   ckpt_path, ::tensorflow::Input old_tensor_name,
                   ::tensorflow::Input row_remapping, ::tensorflow::Input
                   col_remapping, ::tensorflow::Input initializing_values,
                   int64 num_rows, int64 num_cols);
  LoadAndRemapMatrix(const ::tensorflow::Scope& scope, ::tensorflow::Input
                   ckpt_path, ::tensorflow::Input old_tensor_name,
                   ::tensorflow::Input row_remapping, ::tensorflow::Input
                   col_remapping, ::tensorflow::Input initializing_values,
                   int64 num_rows, int64 num_cols, const
                   LoadAndRemapMatrix::Attrs& attrs);
  operator ::tensorflow::Output() const { return output_matrix; }
  operator ::tensorflow::Input() const { return output_matrix; }
  ::tensorflow::Node* node() const { return output_matrix.node(); }

  static Attrs MaxRowsInMemory(int64 x) {
    return Attrs().MaxRowsInMemory(x);
  }

  ::tensorflow::Output output_matrix;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // E__JLCHEN_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_CHECKPOINT_OPS_H_
