#pragma once
#ifndef PASCC_AST_H
#define PASCC_AST_H

#include <iostream>
#include <stack>
#include <vector>
#include "pascal_table.h"
#include "pascal_types.h"

namespace pascals {
    namespace ast {

        /* **************** standard output **************** */
#define PRINT(format, ...) fprintf(dst, format, ##__VA_ARGS__);

/* **************** basic class **************** */
/**
 * Abstract Syntax Tree Node
 */
        class Node { 
        protected:
            Node* parent_;
            std::vector<Node*> child_list_;

        public:
            // constructor and virtual destructor
            Node() : parent_(nullptr) {};
            virtual ~Node() {
                for (auto child : child_list_) {
                    delete child;
                }
            };

            // type cast
            template <typename T>
            T* StaticCast() {
                return dynamic_cast<T*>(this);
            }
            template <typename T>
            T* DynamicCast() {
                return dynamic_cast<T*>(this);
            }

            // getter and setter
            void set_parent(Node* parent) { parent_ = parent; }
            Node* parent() { return parent_; }
            void append_child(Node* child) { child_list_.emplace_back(child); }
            Node* get(int pos) {
                return child_list_[pos < 0 ? pos += child_list_.size() : pos];
            }

            
         
            //格式化输出某子节点及其后续节点
            void FormatFrom(int pos, std::unique_ptr<FILE> dst) {
                return child_list_[pos < 0 ? pos + child_list_.size() : pos]->Format(dst);
            }

            //递归输出所有子节点
            virtual void Format(std::unique_ptr<FILE>& dst) {
                for (auto& child : child_list_) {
                    child->Format(dst);
                }
            }
       
        };

        /**
         * Abstract Syntax Tree
         */
        class AST {
        private:
            bool valid_ = false;
            Node* root_ = nullptr;
   

        public:
            ~AST() {
                if (root_ != nullptr) delete root_;
            }
            bool Valid() { return valid_ && root_ != nullptr; }
            void set_valid(bool v) { valid_ = v; }
            // getter and setter
            Node* root() { return root_; }
            void set_root(Node* root) { root_ = root; }
            // static formater
            void Format(std::unique_ptr<FILE>& dst);


        };

        /* **************** inherit class **************** */
        /**
         * Terminal Node
         */
        class LeafNode : public Node {
        private:
            ConstValue value_;     // const values
            bool is_ref_ = false;

        public:
            LeafNode() {}
            LeafNode(ConstValue val) : value_(val) {}

            // getter and setter
            const std::string id_ref() {
                return is_ref_ ? "(*" + value_.get_value<std::string>() + ")"
                    : value_.get_value<std::string>();
            }
            void set_value(ConstValue value) { value_ = value; }
            void set_ref(bool ref) { is_ref_ = ref; }
            // template value getter
            template <typename T>
            T value() {
                return value_.get<T>();
            }
            std::shared_ptr<BasicType> type() { return value_.get_type(); }

            // Analyze reference
            bool AnalyzeReference(TableSet* ts, FunctionSymbol* fn);
            // override formater
            void Format(std::unique_ptr<FILE>& dst) override;

            // is referenced
        };

        class ProgramNode : public Node {
            // program → program_head  program_body
        };

        class ProgramHeadNode : public Node {
            // programhead → program_id (idlists)
            // programhead → program_id
        public:
            void Format(std::unique_ptr<FILE>& dst) override;
        };

        class ProgramBodyNode : public Node {
            // program_body → const_declarations

            //                var_declarations
            //                subprogram_declarations
            //                compound_statement
        public:
            void Format(std::unique_ptr<FILE>& dst) override;
        };

        class IdListNode : public Node {
        public:
            enum class GrammarType {
                SINGLE_ID,   // idlists → id
                MULTIPLE_ID  // idlists → idlist,id
            };
            IdListNode(GrammarType gt) : grammar_type_(gt) {}
            void Format(std::unique_ptr<FILE>& dst) override;
            std::vector<LeafNode*> Lists();

        private:
            GrammarType grammar_type_;
        };

        class ConstDeclarationsNode : public Node {
            //  enum class GrammarType {
            //    EPSILON,             //const_declarations → EPSILON
            //    CONST_DECLARATION    //const_declarations → const_declaration
            //  };
        };

        class ConstDeclarationNode : public Node {
        public:
            enum class GrammarType {
                VALUE,       // ConstDeclaration → id = const_var
                DECLARATION  // ConstDeclaration →ConstDeclaration; id = const_var
            };
            ConstDeclarationNode(GrammarType gt, BasicType* bt)
                : grammar_type_(gt), type_(bt) {}
            void print_type(std::unique_ptr<FILE>& dst);
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            GrammarType grammar_type_;
            BasicType* type_;
        };

        class ConstValueNode : public Node {
            // const_variable →+num | -num | num | 'letter'
        };

        class VarDeclarationsNode : public Node {
            //  variable_declarations → EPSILON
            //                        | var var_declaration
        };

        class VarDeclarationNode : public Node {
        public:
            enum class GrammarType {
                SINGLE_DECL,   // variable_declaration → idlist : type
                MULTIPLE_DECL  // variable_declaration → variable_declaration ; idlist : type
            };
            enum class ListType { TYPE, ID };
            VarDeclarationNode(GrammarType gt, ListType lt)
                : grammar_type_(gt), list_type_(lt) {}
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            GrammarType grammar_type_;
            ListType list_type_;
        };


        class TypeNode : public Node {
        public:
            enum class GrammarType { BASIC_TYPE, ARRAY };
            //type  basic_type    |    array [  period  ]  of  basic_type
            TypeNode(GrammarType gt) : grammar_type_(gt) {}

            GrammarType grammar_type() { return grammar_type_; }
            void set_base_type_node(TypeNode* node) { base_type_node_ = node; }
            TypeNode* base_type() { return base_type_node_; }

            void PeriodsFormat(FILE* dst);
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            GrammarType grammar_type_;
            TypeNode* base_type_node_;
        };

        class BasicTypeNode : public Node {
            // BasicType →integer|real|boolean|char
        public:
            BasicTypeNode() {}
            BasicTypeNode(BasicType* type) : type_(type) {}

            std::string TypeName(bool ref = false) {
                std::string type_name = type_->get_c_name() + (ref ? "*" : "");
                return type_name;
            }
            void set_type(BasicType* type) { type_ = type; }
            BasicType* type() { return type_; }
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            BasicType* type_;
        };

        class PeriodsNode : public Node {
            // periods → period
            //         | periods, period
        };

        class PeriodNode : public Node {
            // Period → const_var ... const var
        public:
            void Format(std::unique_ptr<FILE>& dst) override;
            int len() { return len_; }
            void set_len(int len) { len_ = len; }

        private:
            int len_;
        };

        class SubprogramDeclarationsNode : public Node {
            // subprogram_declarations → EPSILON
            //                         | subprogram_declarations subprogram
        };

        class SubprogramNode : public Node {
            // subprogram -> subprogram_head ; subprogram_body
        public:
            void Format(std::unique_ptr<FILE>& dst) override;
        };

        class SubprogramBodyNode : public Node {
            // subprogram_body → const_declarations
            //                var_declarations
            //                compound_statement
        public:
        };

        class SubprogramHeadNode : public Node {
        public:
            enum class GrammarType {
                PROCEDURE,  // subprogram_head → procedure id formal_parameter
                FUNCTION    // subprogram_head → function id formal_parameter : basic_type
            };

            SubprogramHeadNode(GrammarType gt) : grammar_type_(gt) {}
            void Format(std::unique_ptr<FILE>& dst) override;
            GrammarType grammar_type() { return grammar_type_; }
            void set_id(std::string id) { id_ = id; }
            std::string id() { return id_; }

        private:
            std::string id_;

            GrammarType grammar_type_;
        };

        class FormalParameterNode : public Node {
        public:
            // formal_parameter → EPSILON
            //                  | ( parameter_lists )
            void Format(std::unique_ptr<FILE>& dst) override;
        };

        class ParameterListsNode : public Node {
        public:
            enum class GrammarType {
                SINGLE_PARAM_LIST,    // param_lists→ param
                MULTIPLE_PARAM_LIST,  // param_lists→ param_list ; parameter
            };

            ParameterListsNode(GrammarType gt) : grammar_type_(gt) {}
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            GrammarType grammar_type_;
        };

        class ParameterListNode : public Node {
            //  parameter → var_parameter | value_parameter
        };

        class VarParameterNode : public Node {
            // var_param → var value_param
        public:
            void Format(std::unique_ptr<FILE>& dst) override;
        };

        class ValueParameterNode : public Node {
            // ValueParam → idlist : basic_type
        public:
            void Format(std::unique_ptr<FILE>& dst) override;
            void Format(bool ref, FILE* dst);
        };

        class CompoundStatementNode : public Node {
            // CompoundStatement → begin StatementList end
        };

        class StatementListNode : public Node {
            // statement_list → statement | statement_list ; statement
        };

        class StatementNode : public Node {
        public:
            enum class GrammarType {
                EPSILON,             // statement → EPSILON
                VAR_ASSIGN_OP_EXP,   // statement → variable assignop expression
                FUNC_ASSIGN_OP_EXP,  // statement → func_id assignop expression
                PROCEDURE_CALL,      // statement → procedure_call
                COMPOUND_STATEMENT,  // statement → compound_statement
                IF_STATEMENT,        // statement → if expression then statement else_part
                FOR_STATEMENT,  // statement → for id assignop expression downto expression
                // do statement
                READ_STATEMENT,     // statement → read ( variable_list )
                WRITE_STATEMENT,    // statement → write ( expression_list )
            };

            StatementNode(GrammarType gt) : grammar_type_(gt) {}
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            GrammarType grammar_type_;
        };

        class VariableListNode : public Node {
        public:
            enum class GrammarType {
                VARIABLE,                // variable_list → variable
                VARIABLE_LIST_VARIABLE,  // variable_list → variable_list , variable
            };

            VariableListNode(GrammarType gt) : grammar_type_(gt) {}
            std::string FormatString();
            void Format(std::unique_ptr<FILE>& dst) override;
            void Format(bool ref, FILE* dst);
            bool set_types(std::vector<TypeTemplate*>* type_list);

        private:
            std::vector<BasicType*> basic_types;
            GrammarType grammar_type_;
        };

        class VariableNode : public Node {
            // variable → id id_varparts
        public:
            void Format(bool ref, FILE* dst);
        };

        class IDVarPartNode : public Node {
        public:
            enum class GrammarType {
                EPSILON,       // id_varpart → .id
                EXP_LIST,  // id_varpart → [ expression_list ]
            };

            IDVarPartNode(GrammarType gt) : grammar_type_(gt) {}
            GrammarType grammar_type() { return grammar_type_; }
            void Format(std::unique_ptr<FILE>& dst) override;
            void set_array_lb(int lb) { array_lb_ = lb; }

        private:
            int array_lb_ = 0;
            GrammarType grammar_type_;
        };

        class ProcedureCallNode : public Node {
        public:
            enum class GrammarType {
                ID,           // procedure_call → id
                ID_EXP_LIST,  // procedure_call → id ( expression_list )
            };

            ProcedureCallNode(GrammarType gt) : grammar_type_(gt) {}
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            GrammarType grammar_type_;
        };

        class ElsePartNode : public Node {
        public:
            enum class GrammarType {
                EPSILON,         // else_part → EPSILON
                ELSE_STATEMENT,  // else_part → else statement
            };

            ElsePartNode(GrammarType gt) : grammar_type_(gt) {}
            void Format(std::unique_ptr<FILE>& dst) override;
            StatementNode* GetStatement() {
                return child_list_[0]->DynamicCast<StatementNode>();
            }

        private:
            GrammarType grammar_type_;
        };

        class ExpressionListNode : public Node {
        public:
            enum class GrammarType {
                EXP,           // expression_list → expression
                EXP_LIST_EXP,  // expression_list → expression_list , expression
            };

            ExpressionListNode(GrammarType gt) : grammar_type_(gt) {}
            std::string FormatString();
            void Format(std::unique_ptr<FILE>& dst) override;
            bool set_types(std::vector<TypeTemplate*>* type_list);
            void set_ref(std::stack<bool>* ref);

        private:
            std::vector<BasicType*> basic_types;
            GrammarType grammar_type_;
        };

        class ExpressionNode : public Node {
            //            | simple_expression
            //            | simple_expression relop simple_expression
        public:
            enum class TargetType {
                EXPRESSION,
                VAR_ARRAY,
                CONST_STRING,
            };
            ExpressionNode() : target_type_(TargetType::EXPRESSION) {}
            ExpressionNode(TargetType tg) : target_type_(tg) {}
            void set_is_ref() { is_ref_ = 1; }
            void set_expression_type(TargetType tg) { target_type_ = tg; }
            TargetType target_type() { return target_type_; }
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            TargetType target_type_;
            bool is_ref_ = 0;
        };

        class SimpleExpressionNode : public Node {
            // simple_expression → term | simple_expression addop term
        };

        class TermNode : public Node {
        public:
            // term → factor | term mulop factor
            void set_op_div(bool op) { op_div = op; }
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            bool op_div = false;
        };

        class FactorNode : public Node {
        public:
            enum class GrammarType {
                UCONST_VAR,   // factor → unsigned_const_variable
                VARIABLE,     // factor → variable
                EXP,          // factor → ( expression )
                ID_EXP_LIST,  // factor → id ( expression_list )
                NOT,          // factor → not factor
                UMINUS,       // factor → uminus  factor
            };

            FactorNode(GrammarType gt) : grammar_type_(gt) {}
            void Format(std::unique_ptr<FILE>& dst) override;

        private:
            GrammarType grammar_type_;
        };

        class UnsignConstVarNode : public Node {
            // unsigned_const_variable → num | 'letter'
        };

    }  // namespace ast

}  // namespace pascals

#endif