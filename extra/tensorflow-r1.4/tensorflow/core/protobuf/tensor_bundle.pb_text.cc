// GENERATED FILE - DO NOT MODIFY
#include "tensorflow/core/protobuf/tensor_bundle.pb_text-impl.h"

using ::tensorflow::strings::Scanner;
using ::tensorflow::strings::StrCat;

namespace tensorflow {

const char* EnumName_BundleHeaderProto_Endianness(
    ::tensorflow::BundleHeaderProto_Endianness value) {
  switch (value) {
    case 0: return "LITTLE";
    case 1: return "BIG";
    default: return "";
  }
}

string ProtoDebugString(
    const ::tensorflow::BundleHeaderProto& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, false);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

string ProtoShortDebugString(
    const ::tensorflow::BundleHeaderProto& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, true);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

namespace internal {

void AppendProtoDebugString(
    ::tensorflow::strings::ProtoTextOutput* o,
    const ::tensorflow::BundleHeaderProto& msg) {
  o->AppendNumericIfNotZero("num_shards", msg.num_shards());
  if (msg.endianness() != 0) {
    o->AppendEnumName("endianness", ::tensorflow::EnumName_BundleHeaderProto_Endianness(msg.endianness()));
  }
  if (msg.has_version()) {
    o->OpenNestedMessage("version");
    ::tensorflow::internal::AppendProtoDebugString(o, msg.version());
    o->CloseNestedMessage();
  }
}

}  // namespace internal

bool ProtoParseFromString(
    const string& s,
    ::tensorflow::BundleHeaderProto* msg) {
  msg->Clear();
  Scanner scanner(s);
  if (!internal::ProtoParseFromScanner(&scanner, false, false, msg)) return false;
  scanner.Eos();
  return scanner.GetResult();
}

namespace internal {

bool ProtoParseFromScanner(
    ::tensorflow::strings::Scanner* scanner, bool nested, bool close_curly,
    ::tensorflow::BundleHeaderProto* msg) {
  std::vector<bool> has_seen(3, false);
  while(true) {
    ProtoSpaceAndComments(scanner);
    if (nested && (scanner->Peek() == (close_curly ? '}' : '>'))) {
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      return true;
    }
    if (!nested && scanner->empty()) { return true; }
    scanner->RestartCapture()
        .Many(Scanner::LETTER_DIGIT_UNDERSCORE)
        .StopCapture();
    StringPiece identifier;
    if (!scanner->GetResult(nullptr, &identifier)) return false;
    bool parsed_colon = false;
    (void)parsed_colon;
    ProtoSpaceAndComments(scanner);
    if (scanner->Peek() == ':') {
      parsed_colon = true;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
    }
    if (identifier == "num_shards") {
      if (has_seen[0]) return false;
      has_seen[0] = true;
      int32 value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseNumericFromScanner(scanner, &value)) return false;
      msg->set_num_shards(value);
    }
    else if (identifier == "endianness") {
      if (has_seen[1]) return false;
      has_seen[1] = true;
      StringPiece value;
      if (!parsed_colon || !scanner->RestartCapture().Many(Scanner::LETTER_DIGIT_DASH_UNDERSCORE).GetResult(nullptr, &value)) return false;
      if (value == "LITTLE" || value == "0" || value == "-0") {
        msg->set_endianness(::tensorflow::BundleHeaderProto_Endianness_LITTLE);
      } else if (value == "BIG" || value == "1") {
        msg->set_endianness(::tensorflow::BundleHeaderProto_Endianness_BIG);
      } else {
        return false;
      }
    }
    else if (identifier == "version") {
      if (has_seen[2]) return false;
      has_seen[2] = true;
      const char open_char = scanner->Peek();
      if (open_char != '{' && open_char != '<') return false;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      if (!::tensorflow::internal::ProtoParseFromScanner(
          scanner, true, open_char == '{', msg->mutable_version())) return false;
    }
  }
}

}  // namespace internal

string ProtoDebugString(
    const ::tensorflow::BundleEntryProto& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, false);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

string ProtoShortDebugString(
    const ::tensorflow::BundleEntryProto& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, true);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

namespace internal {

void AppendProtoDebugString(
    ::tensorflow::strings::ProtoTextOutput* o,
    const ::tensorflow::BundleEntryProto& msg) {
  if (msg.dtype() != 0) {
    o->AppendEnumName("dtype", ::tensorflow::EnumName_DataType(msg.dtype()));
  }
  if (msg.has_shape()) {
    o->OpenNestedMessage("shape");
    ::tensorflow::internal::AppendProtoDebugString(o, msg.shape());
    o->CloseNestedMessage();
  }
  o->AppendNumericIfNotZero("shard_id", msg.shard_id());
  o->AppendNumericIfNotZero("offset", msg.offset());
  o->AppendNumericIfNotZero("size", msg.size());
  o->AppendNumericIfNotZero("crc32c", msg.crc32c());
  for (int i = 0; i < msg.slices_size(); ++i) {
    o->OpenNestedMessage("slices");
    ::tensorflow::internal::AppendProtoDebugString(o, msg.slices(i));
    o->CloseNestedMessage();
  }
}

}  // namespace internal

bool ProtoParseFromString(
    const string& s,
    ::tensorflow::BundleEntryProto* msg) {
  msg->Clear();
  Scanner scanner(s);
  if (!internal::ProtoParseFromScanner(&scanner, false, false, msg)) return false;
  scanner.Eos();
  return scanner.GetResult();
}

namespace internal {

bool ProtoParseFromScanner(
    ::tensorflow::strings::Scanner* scanner, bool nested, bool close_curly,
    ::tensorflow::BundleEntryProto* msg) {
  std::vector<bool> has_seen(7, false);
  while(true) {
    ProtoSpaceAndComments(scanner);
    if (nested && (scanner->Peek() == (close_curly ? '}' : '>'))) {
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      return true;
    }
    if (!nested && scanner->empty()) { return true; }
    scanner->RestartCapture()
        .Many(Scanner::LETTER_DIGIT_UNDERSCORE)
        .StopCapture();
    StringPiece identifier;
    if (!scanner->GetResult(nullptr, &identifier)) return false;
    bool parsed_colon = false;
    (void)parsed_colon;
    ProtoSpaceAndComments(scanner);
    if (scanner->Peek() == ':') {
      parsed_colon = true;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
    }
    if (identifier == "dtype") {
      if (has_seen[0]) return false;
      has_seen[0] = true;
      StringPiece value;
      if (!parsed_colon || !scanner->RestartCapture().Many(Scanner::LETTER_DIGIT_DASH_UNDERSCORE).GetResult(nullptr, &value)) return false;
      if (value == "DT_INVALID" || value == "0" || value == "-0") {
        msg->set_dtype(::tensorflow::DT_INVALID);
      } else if (value == "DT_FLOAT" || value == "1") {
        msg->set_dtype(::tensorflow::DT_FLOAT);
      } else if (value == "DT_DOUBLE" || value == "2") {
        msg->set_dtype(::tensorflow::DT_DOUBLE);
      } else if (value == "DT_INT32" || value == "3") {
        msg->set_dtype(::tensorflow::DT_INT32);
      } else if (value == "DT_UINT8" || value == "4") {
        msg->set_dtype(::tensorflow::DT_UINT8);
      } else if (value == "DT_INT16" || value == "5") {
        msg->set_dtype(::tensorflow::DT_INT16);
      } else if (value == "DT_INT8" || value == "6") {
        msg->set_dtype(::tensorflow::DT_INT8);
      } else if (value == "DT_STRING" || value == "7") {
        msg->set_dtype(::tensorflow::DT_STRING);
      } else if (value == "DT_COMPLEX64" || value == "8") {
        msg->set_dtype(::tensorflow::DT_COMPLEX64);
      } else if (value == "DT_INT64" || value == "9") {
        msg->set_dtype(::tensorflow::DT_INT64);
      } else if (value == "DT_BOOL" || value == "10") {
        msg->set_dtype(::tensorflow::DT_BOOL);
      } else if (value == "DT_QINT8" || value == "11") {
        msg->set_dtype(::tensorflow::DT_QINT8);
      } else if (value == "DT_QUINT8" || value == "12") {
        msg->set_dtype(::tensorflow::DT_QUINT8);
      } else if (value == "DT_QINT32" || value == "13") {
        msg->set_dtype(::tensorflow::DT_QINT32);
      } else if (value == "DT_BFLOAT16" || value == "14") {
        msg->set_dtype(::tensorflow::DT_BFLOAT16);
      } else if (value == "DT_QINT16" || value == "15") {
        msg->set_dtype(::tensorflow::DT_QINT16);
      } else if (value == "DT_QUINT16" || value == "16") {
        msg->set_dtype(::tensorflow::DT_QUINT16);
      } else if (value == "DT_UINT16" || value == "17") {
        msg->set_dtype(::tensorflow::DT_UINT16);
      } else if (value == "DT_COMPLEX128" || value == "18") {
        msg->set_dtype(::tensorflow::DT_COMPLEX128);
      } else if (value == "DT_HALF" || value == "19") {
        msg->set_dtype(::tensorflow::DT_HALF);
      } else if (value == "DT_RESOURCE" || value == "20") {
        msg->set_dtype(::tensorflow::DT_RESOURCE);
      } else if (value == "DT_VARIANT" || value == "21") {
        msg->set_dtype(::tensorflow::DT_VARIANT);
      } else if (value == "DT_FLOAT_REF" || value == "101") {
        msg->set_dtype(::tensorflow::DT_FLOAT_REF);
      } else if (value == "DT_DOUBLE_REF" || value == "102") {
        msg->set_dtype(::tensorflow::DT_DOUBLE_REF);
      } else if (value == "DT_INT32_REF" || value == "103") {
        msg->set_dtype(::tensorflow::DT_INT32_REF);
      } else if (value == "DT_UINT8_REF" || value == "104") {
        msg->set_dtype(::tensorflow::DT_UINT8_REF);
      } else if (value == "DT_INT16_REF" || value == "105") {
        msg->set_dtype(::tensorflow::DT_INT16_REF);
      } else if (value == "DT_INT8_REF" || value == "106") {
        msg->set_dtype(::tensorflow::DT_INT8_REF);
      } else if (value == "DT_STRING_REF" || value == "107") {
        msg->set_dtype(::tensorflow::DT_STRING_REF);
      } else if (value == "DT_COMPLEX64_REF" || value == "108") {
        msg->set_dtype(::tensorflow::DT_COMPLEX64_REF);
      } else if (value == "DT_INT64_REF" || value == "109") {
        msg->set_dtype(::tensorflow::DT_INT64_REF);
      } else if (value == "DT_BOOL_REF" || value == "110") {
        msg->set_dtype(::tensorflow::DT_BOOL_REF);
      } else if (value == "DT_QINT8_REF" || value == "111") {
        msg->set_dtype(::tensorflow::DT_QINT8_REF);
      } else if (value == "DT_QUINT8_REF" || value == "112") {
        msg->set_dtype(::tensorflow::DT_QUINT8_REF);
      } else if (value == "DT_QINT32_REF" || value == "113") {
        msg->set_dtype(::tensorflow::DT_QINT32_REF);
      } else if (value == "DT_BFLOAT16_REF" || value == "114") {
        msg->set_dtype(::tensorflow::DT_BFLOAT16_REF);
      } else if (value == "DT_QINT16_REF" || value == "115") {
        msg->set_dtype(::tensorflow::DT_QINT16_REF);
      } else if (value == "DT_QUINT16_REF" || value == "116") {
        msg->set_dtype(::tensorflow::DT_QUINT16_REF);
      } else if (value == "DT_UINT16_REF" || value == "117") {
        msg->set_dtype(::tensorflow::DT_UINT16_REF);
      } else if (value == "DT_COMPLEX128_REF" || value == "118") {
        msg->set_dtype(::tensorflow::DT_COMPLEX128_REF);
      } else if (value == "DT_HALF_REF" || value == "119") {
        msg->set_dtype(::tensorflow::DT_HALF_REF);
      } else if (value == "DT_RESOURCE_REF" || value == "120") {
        msg->set_dtype(::tensorflow::DT_RESOURCE_REF);
      } else if (value == "DT_VARIANT_REF" || value == "121") {
        msg->set_dtype(::tensorflow::DT_VARIANT_REF);
      } else {
        return false;
      }
    }
    else if (identifier == "shape") {
      if (has_seen[1]) return false;
      has_seen[1] = true;
      const char open_char = scanner->Peek();
      if (open_char != '{' && open_char != '<') return false;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      if (!::tensorflow::internal::ProtoParseFromScanner(
          scanner, true, open_char == '{', msg->mutable_shape())) return false;
    }
    else if (identifier == "shard_id") {
      if (has_seen[2]) return false;
      has_seen[2] = true;
      int32 value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseNumericFromScanner(scanner, &value)) return false;
      msg->set_shard_id(value);
    }
    else if (identifier == "offset") {
      if (has_seen[3]) return false;
      has_seen[3] = true;
      int64 value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseNumericFromScanner(scanner, &value)) return false;
      msg->set_offset(value);
    }
    else if (identifier == "size") {
      if (has_seen[4]) return false;
      has_seen[4] = true;
      int64 value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseNumericFromScanner(scanner, &value)) return false;
      msg->set_size(value);
    }
    else if (identifier == "crc32c") {
      if (has_seen[5]) return false;
      has_seen[5] = true;
      uint32 value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseNumericFromScanner(scanner, &value)) return false;
      msg->set_crc32c(value);
    }
    else if (identifier == "slices") {
      const bool is_list = (scanner->Peek() == '[');
      do {
        if (is_list) {
          scanner->One(Scanner::ALL);
          ProtoSpaceAndComments(scanner);
        }
        const char open_char = scanner->Peek();
        if (open_char != '{' && open_char != '<') return false;
        scanner->One(Scanner::ALL);
        ProtoSpaceAndComments(scanner);
        if (!::tensorflow::internal::ProtoParseFromScanner(
            scanner, true, open_char == '{', msg->add_slices())) return false;
      } while (is_list && scanner->Peek() == ',');
      if (is_list && !scanner->OneLiteral("]").GetResult()) return false;
    }
  }
}

}  // namespace internal

}  // namespace tensorflow
