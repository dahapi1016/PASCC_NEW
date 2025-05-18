#include "pascal_ast.h"
using std::stack;
using std::string;
using std::vector;

namespace pascals {
namespace ast {
/* **************** standard output **************** */

/* **************** ast output **************** */
void AST::Format(FILE *dst) {
  if(!Valid()) return;
  if (root_ != nullptr) {
    fprintf(dst, "#include <stdio.h>\n");
    root_->Format(dst);
  }
  // log_info("ast format success");
  fclose(dst);
}

//////////////////////////////

void LeafNode::Format(FILE *dst) {
    std::shared_ptr<pascals::BasicType> tp = value_.get_type();
  if (tp == TYPE_INTEGER) {
    PRINT("%d", value_.get_value<int>())
  } else if (tp == TYPE_REAL) {
    PRINT("%.2f", value_.get_value<float>())
  } else if (tp == TYPE_BOOLEAN) {
    PRINT("%d", value_.get_value<bool>())
  } else if (tp == TYPE_CHAR) {
    PRINT("'%c'", value_.get_value<char>())
  }
}

bool LeafNode::AnalyzeReference(SymbolTable *ts, FunctionIdentifier *fn) {
  if (fn == nullptr) return false;
  // search table and judge if is current layer
  bool local = false;
  string id = value_.get_value<string>();
  // std::shared_ptr<Identifier> entry = ts->get_identifier_by_name(id);
  // if (entry != nullptr && local) {
  //   //TODO : 等待刁仲阳修改
  //   FunctionIdentifier::Parameter.param_type pt = (*fn)[id];
  //   if (pt != nullptr && pt->second == FunctionSymbol::PARAM_MODE::REFERENCE) {
  //     is_ref_ = true;
  //   }
  // }
  return fn->get_param_is_reference_by_name(id);
}
/////////////////////////////////////////////

void ProgramHeadNode::Format(FILE *dst) {
  time_t now = time(nullptr);
  tm *local = localtime(&now);
  // PRINT("/// [")
  FormatFrom(0, dst);
  // PRINT("] created on %d/%d/%d\n", 1900 + local->tm_year, 1 + local->tm_mon,
  //       local->tm_mday)
}

void ProgramBodyNode::Format(FILE *dst) {
  FormatFrom(0, dst);  // const decl
  FormatFrom(1, dst);  // type decl
  FormatFrom(2, dst);  // var decl
  FormatFrom(3, dst);  // sub prog decl
  PRINT("int main() {\n")
  FormatFrom(4, dst);  // comp stat
  PRINT("return 0;\n")
  PRINT("}\n")
}

void IdListNode::Format(FILE *dst) {
  FormatFrom(0, dst);
  if (grammar_type_ == GrammarType::MULTIPLE_ID) {
    PRINT(", ")
    FormatFrom(1, dst);
  }
}

vector<LeafNode *> IdListNode::Lists() {
  vector<LeafNode *> lists;
  IdListNode *cur_node = this;
  GrammarType gtype = grammar_type_;

  while (gtype == GrammarType::MULTIPLE_ID) {
    LeafNode *ln = cur_node->child_list_[1]->DynamicCast<LeafNode>();
    lists.insert(lists.begin(), ln);
    // switch to next layer
    cur_node = cur_node->child_list_[0]->DynamicCast<IdListNode>();
    gtype = cur_node->grammar_type_;
  }

  // insert last
  LeafNode *ln = (*cur_node->child_list_.rbegin())->DynamicCast<LeafNode>();
  lists.insert(lists.begin(), ln);
  return lists;
}


void ConstDeclarationNode::print_type(FILE *dst) {
  if (type_ == TYPE_INTEGER) {
    PRINT("int ")
  } else if (type_ == TYPE_REAL) {
    PRINT("float ")
  } else if (type_ == TYPE_CHAR) {
    PRINT("char ")
  }
}
void ConstDeclarationNode::Format(FILE *dst) {
  if (grammar_type_ == GrammarType::DECLARATION) {
    FormatFrom(0, dst);
    PRINT("const ")
    print_type(dst);
    FormatFrom(1, dst);
    PRINT(" = ")
    FormatFrom(2, dst);
    PRINT(";\n");
  } else if (grammar_type_ == GrammarType::VALUE) {
    PRINT("const ")
    print_type(dst);
    FormatFrom(0, dst);
    PRINT(" = ")
    FormatFrom(1, dst);
    PRINT(";\n");
  }
}

void VarDeclarationNode::Format(FILE *dst) {
  if (grammar_type_ == GrammarType::MULTIPLE_DECL) {
    FormatFrom(0, dst);
  }
  // analyze current layer
  size_t last = child_list_.size() - 1;
  std::shared_ptr<pascals::ast::Node> tnode = child_list_[last];
  vector<LeafNode *> idlist =
      child_list_[last - 1]->DynamicCast<IdListNode>()->Lists();

  if (list_type_ == ListType::ID) {
    tnode->Format(dst);
    PRINT(" ");
    // idlist
    for (int i = 0; i < idlist.size(); i++) {
      idlist[i]->Format(dst);
      if (i < idlist.size() - 1) {
        PRINT(", ")
      }
    }
  } else {
    // TypeNode* tn = tnode->DynamicCast<TypeNode>()->base_type();
    TypeNode *tn = tnode->DynamicCast<TypeNode>();
    tn->base_type()->Format(dst);
    PRINT(" ");
    // idlist
    bool array_flag = (tn->grammar_type() == TypeNode::GrammarType::ARRAY);
    for (int i = 0; i < idlist.size(); i++) {
      idlist[i]->Format(dst);
      if (array_flag) tn->PeriodsFormat(dst);
      if (i < idlist.size() - 1) {
        PRINT(", ")
      }
    }
  }
  PRINT(";\n")
}



void TypeNode::Format(FILE *dst) {
  switch (grammar_type_) {
    case GrammarType::BASIC_TYPE:
      FormatFrom(0, dst);
      break;
    case GrammarType::ARRAY:  // upper funciton will solve this
      break;
    // case GrammarType::RECORD_TYPE:  删了？
    //   PRINT("struct {\n")
    //   FormatFrom(0, dst);
    //   PRINT("}")
    //   break;
  }
}

void TypeNode::PeriodsFormat(FILE *dst) {
  if (grammar_type_ == GrammarType::ARRAY) {
    child_list_[0]->Format(dst);
    child_list_[1]->DynamicCast<TypeNode>()->PeriodsFormat(dst);
  }
}

void BasicTypeNode::Format(FILE *dst) {
  PRINT("%s", type_->get_c_name().c_str())
}

void PeriodNode::Format(FILE *dst) { PRINT("[%d]", len_) }

//TODO: 改为递归，加一个SubprogramDeclarationsNode
void SubprogramNode::Format(FILE *dst) {
  auto headnode = child_list_[0]->DynamicCast<SubprogramHeadNode>();
  bool func_flag =
      (headnode->grammar_type() == SubprogramHeadNode::GrammarType::FUNCTION);
  string id;
  BasicType *type = nullptr;
  if (func_flag) {
    id = headnode->id();
    id = "__" + id + "__";
    type = headnode->get(2)->DynamicCast<BasicTypeNode>()->type();
  }

  FormatFrom(0, dst);
  PRINT("{\n")
  if (func_flag) PRINT("%s %s;\n", type->get_c_name().c_str(), id.c_str())
  FormatFrom(1, dst);
  if (func_flag) PRINT("return %s;\n", id.c_str())
  PRINT("}\n")
}

void SubprogramHeadNode::Format(FILE *dst) {
  if (grammar_type_ == GrammarType::PROCEDURE) {
    PRINT("void ")
  } else {
    FormatFrom(2, dst);  // basic_type
    PRINT(" ")
  }
  FormatFrom(0, dst);
  FormatFrom(1, dst);
}

void FormalParameterNode::Format(FILE *dst) {
  PRINT("(")
  for (auto child : child_list_) {
    child->Format(dst);
  }
  PRINT(")")
}

void ParameterListsNode::Format(FILE *dst) {
  for (int i = 0; i < child_list_.size(); i++) {
    child_list_[i]->Format(dst);
    if (i < child_list_.size() - 1) {
      PRINT(",")
    }
  }
}


void VarParameterNode::Format(FILE *dst) {
  ValueParameterNode *vp = child_list_[0]->DynamicCast<ValueParameterNode>();
  vp->Format(true, dst);
}

void ValueParameterNode::Format(FILE *dst) { this->Format(false, dst); }

void ValueParameterNode::Format(bool ref, FILE *dst) {
  // get idlists
  IdListNode *idnode = child_list_[0]->DynamicCast<IdListNode>();
  // get type
  BasicTypeNode *tnode = child_list_[1]->DynamicCast<BasicTypeNode>();
  vector<LeafNode *> idlist = idnode->Lists();
  string tname = tnode->TypeName(ref);

  for (int i = 0; i < idlist.size(); i++) {
    PRINT("%s %s", tname.c_str(), idlist[i]->id_ref().c_str());
    if (i < idlist.size() - 1) {
      PRINT(", ")
    }
  }
}

void StatementNode::Format(FILE *dst) {
  switch (grammar_type_) {
    case GrammarType::EPSILON:
      return;
    case GrammarType::VAR_ASSIGN_OP_EXP:
    case GrammarType::FUNC_ASSIGN_OP_EXP: {
      auto exp = child_list_[1]->DynamicCast<ExpressionNode>();
      switch (exp->target_type()) {
        case ExpressionNode::TargetType::EXPRESSION: {  // other expression
          FormatFrom(0, dst);
          PRINT(" = ");
          FormatFrom(1, dst);
          break;
        }
        case ExpressionNode::TargetType::VAR_ARRAY: {  // array-list
          PRINT("memcpy(");
          FormatFrom(0, dst);
          PRINT(", ");
          FormatFrom(1, dst);
          PRINT(", sizeof(");
          FormatFrom(0, dst);
          PRINT("))")
          break;
        }
        case ExpressionNode::TargetType::CONST_STRING: {  // const-string
          PRINT("strcpy(");
          FormatFrom(0, dst);
          PRINT(", ");
          FormatFrom(1, dst);
          PRINT(")")
          break;
        }
      }
      PRINT(";\n")
      break;
    }
    case GrammarType::PROCEDURE_CALL:
    case GrammarType::COMPOUND_STATEMENT: {
      FormatFrom(0, dst);
      break;
    }
    case GrammarType::IF_STATEMENT: {
      PRINT("if (")
      FormatFrom(0, dst);
      PRINT(") {\n")
      FormatFrom(1, dst);
      PRINT("}\n")
      FormatFrom(2, dst);
      break;
    }
    case GrammarType::FOR_STATEMENT: {
      PRINT("for (")
      FormatFrom(0, dst);
      PRINT("=")
      FormatFrom(1, dst);
      PRINT(";")
      FormatFrom(0, dst);
      PRINT("<=")
      FormatFrom(3, dst);
      PRINT(";")
      FormatFrom(0, dst);
      PRINT("++")
      PRINT(") {\n")
      for (int i = 4; i < child_list_.size(); i++) FormatFrom(i, dst);
      PRINT("}\n")
      break;
    }
    //TODO :改为Read，去掉Readln
    case GrammarType::READ_STATEMENT:{
      if(child_list_.size() > 0){
          auto *vlnodes = child_list_[0]->DynamicCast<VariableListNode>();
          PRINT("scanf(\"%s\", ", vlnodes->FormatString().c_str());
          vlnodes->Format(true, dst);
          PRINT(");\n")
      }
      break;
    }
    case GrammarType::WRITE_STATEMENT: {
      if (child_list_.size() == 0) {
        PRINT("printf(\"\\n\");\n")
        break;
      }
      auto *elnode = child_list_[0]->DynamicCast<ExpressionListNode>();
      PRINT("printf(\"%s\", ", elnode->FormatString().c_str())
      // PRINT(", ")
      elnode->Format(dst);
      PRINT(");\n")
      break;
    }
  }
}

string VariableListNode::FormatString() {
  string format = "";
  for (int i = 0; i < basic_types.size(); i++) {
    std::shared_ptr<BasicType> type = basic_types[i];
    string chfmt = (type == TYPE_INTEGER || type == TYPE_BOOLEAN) ? "%d "
                   : type == TYPE_REAL                     ? "%f "
                   : type == TYPE_CHAR
                       ? "%c "
                       : throw std::runtime_error(
                             "ExpressionListNode: FormatString() : error type");
    format += chfmt;
  }
  return format;
}

void VariableListNode::Format(FILE *dst) { Format(false, dst); }

void VariableListNode::Format(bool ref, FILE *dst) {
  if (grammar_type_ == GrammarType::VARIABLE) {
    child_list_[0]->DynamicCast<VariableNode>()->Format(ref, dst);
  }
  if (grammar_type_ == GrammarType::VARIABLE_LIST_VARIABLE) {
    child_list_[0]->DynamicCast<VariableListNode>()->Format(ref, dst);
    PRINT(",")
    child_list_[1]->DynamicCast<VariableNode>()->Format(ref, dst);
  }
}

bool VariableListNode::set_types(std::vector<TypeTemplate *> *type_list) {
  if (!type_list) return true;
  for (auto i : *type_list) {
    //TODO 
    if (TypeTemplate::is_basic_type(std::shared_ptr<TypeTemplate>(i))) {
// 原代码使用 dynamic_cast 转换为 std::shared_ptr<BasicType> 有误，需要先将 TypeTemplate* 转换为 BasicType*，再用 std::shared_ptr 包装
      basic_types.push_back(std::shared_ptr<BasicType>(dynamic_cast<BasicType*>(i)));
    } 
    // else if (i != TYPE_ERROR && i->StringLike()) {
    //   basic_types.push_back(TYPE_STRINGLIKE);
    // } 
    else {
      return false;
    }
  }
  return true;
}

void VariableNode::Format(bool ref, FILE *dst) {
  if (ref) PRINT("&")
  Node::Format(dst);
}

void IDVarPartNode::Format(FILE *dst) {
  if (grammar_type_ == GrammarType::EPSILON) {
    PRINT(".")
    FormatFrom(0, dst);
  } else if (grammar_type_ == GrammarType::EXP_LIST) {
    PRINT("[")
    FormatFrom(0, dst);
    if (array_lb_ > 0)
      PRINT(" - %d", array_lb_)
    else if (array_lb_ < 0)
      PRINT(" + %d", -array_lb_)
    PRINT("]")
  }
}


void ProcedureCallNode::Format(FILE *dst) {
  FormatFrom(0, dst);
  if (grammar_type_ == GrammarType::ID) {
    PRINT("();")
  } else if (grammar_type_ == GrammarType::ID_EXP_LIST) {
    PRINT("(")
    FormatFrom(1, dst);
    PRINT(");")
  }
}

void ElsePartNode::Format(FILE *dst) {
  switch (grammar_type_) {
    case GrammarType::EPSILON:
      return;
    case GrammarType::ELSE_STATEMENT:
      PRINT("else {\n")
      GetStatement()->Format(dst);
      PRINT("}\n")
  }
}

string ExpressionListNode::FormatString() {
  string format = "";
  for (int i = 0; i < basic_types.size(); i++) {
    std::shared_ptr<pascals::BasicType> type = basic_types[i];
    string chfmt = (type == TYPE_INTEGER || type == TYPE_BOOLEAN) ? "%d"
                   : type == TYPE_REAL                     ? "%.2f"
                   : type == TYPE_CHAR
                       ? "%c"
                       : throw std::runtime_error(
                             "ExpressionListNode: FormatString() : error type");
    format += chfmt;
  }
  return format;
}

void ExpressionListNode::Format(FILE *dst) {
  for (int i = 0; i < child_list_.size(); i++) {
    child_list_[i]->Format(dst);
    if (i < child_list_.size() - 1) {
      PRINT(", ")
    }
  }
}

bool ExpressionListNode::set_types(std::vector<TypeTemplate *> *type_list) {
  if (!type_list) return true;
  for (auto i : *type_list) {
    // if (is_basic(i) || i == TYPE_STRINGLIKE) {
    //   basic_types.push_back(dynamic_cast<BasicType *>(i));
    // } else if (i != TYPE_ERROR && i->StringLike()) {
    //   basic_types.push_back(TYPE_STRINGLIKE);
    // } else {
    //   return false;
    // }
    return false;
  }
  return true;
}

void ExpressionListNode::set_ref(std::stack<bool> *ref) {
  if(child_list_.size() == 0 || ref == nullptr || ref->size() == 0) return;
  if (grammar_type_ == GrammarType::EXP) {
    if (ref->top()) child_list_[0]->DynamicCast<ExpressionNode>()->set_is_ref();
  } else {
    if (ref->top()) child_list_[1]->DynamicCast<ExpressionNode>()->set_is_ref();
    ref->pop();
    child_list_[0]->DynamicCast<ExpressionListNode>()->set_ref(ref);
  }
}
//TODO: 改一下，加入simple expression
void ExpressionNode::Format(FILE *dst) {
  if (is_ref_) PRINT("&")
  Node::Format(dst);
}


void TermNode::Format(FILE *dst) {
  if (op_div) PRINT("(float)")
  for (auto child : child_list_) {
    child->Format(dst);
  }
}

void FactorNode::Format(FILE *dst) {
  switch (grammar_type_) {
    case GrammarType::NUM:
    case GrammarType::VARIABLE:
      FormatFrom(0, dst);
      break;

    case GrammarType::EXP:
      PRINT("(")
      FormatFrom(0, dst);
      PRINT(")")
      break;

    case GrammarType::ID_EXP_LIST:
      FormatFrom(0, dst);
      PRINT("(")
      FormatFrom(1, dst);
      PRINT(")")
      break;

    case GrammarType::NOT:
      PRINT("!")
      FormatFrom(0, dst);
      break;

    default:
      break;
  }
}

/////////////////////////////

}  // namespace ast
}  // namespace pascals