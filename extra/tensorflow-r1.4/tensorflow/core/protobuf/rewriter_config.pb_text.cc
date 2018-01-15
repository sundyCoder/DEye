// GENERATED FILE - DO NOT MODIFY
#include "tensorflow/core/protobuf/rewriter_config.pb_text-impl.h"

using ::tensorflow::strings::Scanner;
using ::tensorflow::strings::StrCat;

namespace tensorflow {

string ProtoDebugString(
    const ::tensorflow::AutoParallelOptions& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, false);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

string ProtoShortDebugString(
    const ::tensorflow::AutoParallelOptions& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, true);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

namespace internal {

void AppendProtoDebugString(
    ::tensorflow::strings::ProtoTextOutput* o,
    const ::tensorflow::AutoParallelOptions& msg) {
  o->AppendBoolIfTrue("enable", msg.enable());
  o->AppendNumericIfNotZero("num_replicas", msg.num_replicas());
}

}  // namespace internal

bool ProtoParseFromString(
    const string& s,
    ::tensorflow::AutoParallelOptions* msg) {
  msg->Clear();
  Scanner scanner(s);
  if (!internal::ProtoParseFromScanner(&scanner, false, false, msg)) return false;
  scanner.Eos();
  return scanner.GetResult();
}

namespace internal {

bool ProtoParseFromScanner(
    ::tensorflow::strings::Scanner* scanner, bool nested, bool close_curly,
    ::tensorflow::AutoParallelOptions* msg) {
  std::vector<bool> has_seen(2, false);
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
    if (identifier == "enable") {
      if (has_seen[0]) return false;
      has_seen[0] = true;
      bool value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseBoolFromScanner(scanner, &value)) return false;
      msg->set_enable(value);
    }
    else if (identifier == "num_replicas") {
      if (has_seen[1]) return false;
      has_seen[1] = true;
      int32 value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseNumericFromScanner(scanner, &value)) return false;
      msg->set_num_replicas(value);
    }
  }
}

}  // namespace internal

const char* EnumName_RewriterConfig_Toggle(
    ::tensorflow::RewriterConfig_Toggle value) {
  switch (value) {
    case 0: return "DEFAULT";
    case 1: return "ON";
    case 2: return "OFF";
    default: return "";
  }
}

const char* EnumName_RewriterConfig_MemOptType(
    ::tensorflow::RewriterConfig_MemOptType value) {
  switch (value) {
    case 0: return "DEFAULT_MEM_OPT";
    case 1: return "NO_MEM_OPT";
    case 2: return "MANUAL";
    case 3: return "HEURISTICS";
    default: return "";
  }
}

string ProtoDebugString(
    const ::tensorflow::RewriterConfig& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, false);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

string ProtoShortDebugString(
    const ::tensorflow::RewriterConfig& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, true);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

namespace internal {

void AppendProtoDebugString(
    ::tensorflow::strings::ProtoTextOutput* o,
    const ::tensorflow::RewriterConfig& msg) {
  o->AppendBoolIfTrue("optimize_tensor_layout", msg.optimize_tensor_layout());
  o->AppendBoolIfTrue("disable_model_pruning", msg.disable_model_pruning());
  if (msg.constant_folding() != 0) {
    o->AppendEnumName("constant_folding", ::tensorflow::EnumName_RewriterConfig_Toggle(msg.constant_folding()));
  }
  if (msg.memory_optimization() != 0) {
    o->AppendEnumName("memory_optimization", ::tensorflow::EnumName_RewriterConfig_MemOptType(msg.memory_optimization()));
  }
  if (msg.has_auto_parallel()) {
    o->OpenNestedMessage("auto_parallel");
    ::tensorflow::internal::AppendProtoDebugString(o, msg.auto_parallel());
    o->CloseNestedMessage();
  }
  o->AppendStringIfNotEmpty("memory_optimizer_target_node_name_prefix", ProtobufStringToString(msg.memory_optimizer_target_node_name_prefix()));
  if (msg.arithmetic_optimization() != 0) {
    o->AppendEnumName("arithmetic_optimization", ::tensorflow::EnumName_RewriterConfig_Toggle(msg.arithmetic_optimization()));
  }
  for (int i = 0; i < msg.optimizers_size(); ++i) {
    o->AppendString("optimizers", ProtobufStringToString(msg.optimizers(i)));
  }
}

}  // namespace internal

bool ProtoParseFromString(
    const string& s,
    ::tensorflow::RewriterConfig* msg) {
  msg->Clear();
  Scanner scanner(s);
  if (!internal::ProtoParseFromScanner(&scanner, false, false, msg)) return false;
  scanner.Eos();
  return scanner.GetResult();
}

namespace internal {

bool ProtoParseFromScanner(
    ::tensorflow::strings::Scanner* scanner, bool nested, bool close_curly,
    ::tensorflow::RewriterConfig* msg) {
  std::vector<bool> has_seen(8, false);
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
    if (identifier == "optimize_tensor_layout") {
      if (has_seen[0]) return false;
      has_seen[0] = true;
      bool value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseBoolFromScanner(scanner, &value)) return false;
      msg->set_optimize_tensor_layout(value);
    }
    else if (identifier == "constant_folding") {
      if (has_seen[1]) return false;
      has_seen[1] = true;
      StringPiece value;
      if (!parsed_colon || !scanner->RestartCapture().Many(Scanner::LETTER_DIGIT_DASH_UNDERSCORE).GetResult(nullptr, &value)) return false;
      if (value == "DEFAULT" || value == "0" || value == "-0") {
        msg->set_constant_folding(::tensorflow::RewriterConfig_Toggle_DEFAULT);
      } else if (value == "ON" || value == "1") {
        msg->set_constant_folding(::tensorflow::RewriterConfig_Toggle_ON);
      } else if (value == "OFF" || value == "2") {
        msg->set_constant_folding(::tensorflow::RewriterConfig_Toggle_OFF);
      } else {
        return false;
      }
    }
    else if (identifier == "arithmetic_optimization") {
      if (has_seen[2]) return false;
      has_seen[2] = true;
      StringPiece value;
      if (!parsed_colon || !scanner->RestartCapture().Many(Scanner::LETTER_DIGIT_DASH_UNDERSCORE).GetResult(nullptr, &value)) return false;
      if (value == "DEFAULT" || value == "0" || value == "-0") {
        msg->set_arithmetic_optimization(::tensorflow::RewriterConfig_Toggle_DEFAULT);
      } else if (value == "ON" || value == "1") {
        msg->set_arithmetic_optimization(::tensorflow::RewriterConfig_Toggle_ON);
      } else if (value == "OFF" || value == "2") {
        msg->set_arithmetic_optimization(::tensorflow::RewriterConfig_Toggle_OFF);
      } else {
        return false;
      }
    }
    else if (identifier == "disable_model_pruning") {
      if (has_seen[3]) return false;
      has_seen[3] = true;
      bool value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseBoolFromScanner(scanner, &value)) return false;
      msg->set_disable_model_pruning(value);
    }
    else if (identifier == "memory_optimization") {
      if (has_seen[4]) return false;
      has_seen[4] = true;
      StringPiece value;
      if (!parsed_colon || !scanner->RestartCapture().Many(Scanner::LETTER_DIGIT_DASH_UNDERSCORE).GetResult(nullptr, &value)) return false;
      if (value == "DEFAULT_MEM_OPT" || value == "0" || value == "-0") {
        msg->set_memory_optimization(::tensorflow::RewriterConfig_MemOptType_DEFAULT_MEM_OPT);
      } else if (value == "NO_MEM_OPT" || value == "1") {
        msg->set_memory_optimization(::tensorflow::RewriterConfig_MemOptType_NO_MEM_OPT);
      } else if (value == "MANUAL" || value == "2") {
        msg->set_memory_optimization(::tensorflow::RewriterConfig_MemOptType_MANUAL);
      } else if (value == "HEURISTICS" || value == "3") {
        msg->set_memory_optimization(::tensorflow::RewriterConfig_MemOptType_HEURISTICS);
      } else {
        return false;
      }
    }
    else if (identifier == "memory_optimizer_target_node_name_prefix") {
      if (has_seen[5]) return false;
      has_seen[5] = true;
      string str_value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
          scanner, &str_value)) return false;
      SetProtobufStringSwapAllowed(&str_value, msg->mutable_memory_optimizer_target_node_name_prefix());
    }
    else if (identifier == "auto_parallel") {
      if (has_seen[6]) return false;
      has_seen[6] = true;
      const char open_char = scanner->Peek();
      if (open_char != '{' && open_char != '<') return false;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      if (!::tensorflow::internal::ProtoParseFromScanner(
          scanner, true, open_char == '{', msg->mutable_auto_parallel())) return false;
    }
    else if (identifier == "optimizers") {
      const bool is_list = (scanner->Peek() == '[');
      do {
        if (is_list) {
          scanner->One(Scanner::ALL);
          ProtoSpaceAndComments(scanner);
        }
        string str_value;
        if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
            scanner, &str_value)) return false;
        SetProtobufStringSwapAllowed(&str_value, msg->add_optimizers());
      } while (is_list && scanner->Peek() == ',');
      if (is_list && !scanner->OneLiteral("]").GetResult()) return false;
    }
  }
}

}  // namespace internal

}  // namespace tensorflow
