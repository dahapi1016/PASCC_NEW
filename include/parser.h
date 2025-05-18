// 用于.l和.y文件的数据结构
#pragma once
#include <stack>
#include <algorithm>
#include "pascal_types.h"
#include "pascal_identifier.h"
#include "pascal_ast.h"

struct Token {  // 词法单元
	pascals::ConstValue value;
	int length;
	int line_num;
	int column_num;
};


// 语法树节点信息
struct ValueInfo {  // 值(对应文法中的const_value和num)
	std::shared_ptr<pascals::BasicType> type;  // 类型
	pascals::ConstValue value;  // 值
	std::shared_ptr<pascals::ast::LeafNode> const_variable_node;  // 对应语法树节点
};

struct IdListInfo {  // 标识符列表(对应文法中的id_list)
	std::shared_ptr<std::pair<std::string, int>> id_name_list;  // 标识符名们
	std::shared_ptr<pascals::ast::IdListNode> id_list_node;  // 对应语法树节点
};

struct BasicTypeInfo {  // 基本类型(对应文法中的basic_type)
	std::shared_ptr<pascals::BasicType> type;  // 类型
	std::shared_ptr<pascals::ast::BasicTypeNode> basic_type_node;  // 对应语法树节点
};

struct TypeInfo {  // 类型(对应文法中的type)
	enum MainType { BASIC, ARRAY } main_type;
	pascals::TypeTemplate::TYPE type_n;  // 类型(基本/数组)
	std::shared_ptr<pascals::TypeTemplate> type;  // 指向类型的指针
	std::shared_ptr<std::vector<pascals::ArrayType::ArrayBound>> bounds;  // 数组各维数上下界
	std::shared_ptr<pascals::ast::TypeNode> base_type_node;  // 基类型(基本类型本身/数组元素的类型)对应语法树节点
	std::shared_ptr<pascals::ast::TypeNode> type_node;  // 对应语法树节点
};

struct PeriodInfo {  // 数组上下界(一维)(对应文法中的period);
	std::shared_ptr<pascals::ArrayType::ArrayBound> bound;  // 下界&上界
	std::shared_ptr<pascals::ast::PeriodNode> period_node;  // 对应语法树节点
};

struct PeriodsInfo {  // 数组上下界(多维)(对应文法中的periods);
	std::shared_ptr<std::vector<pascals::ArrayType::ArrayBound>> bounds;  // 多个下界&上界
	std::shared_ptr<pascals::ast::PeriodsNode> periods_node;  // 对应语法树节点
};

struct FormalParameterInfo {  // 函数/过程参数(对应文法中的formal_parameter)
	std::shared_ptr<std::vector<pascals::FunctionIdentifier::Parameter>> parameters;  // 参数列表
	std::shared_ptr<pascals::ast::FormalParameterNode> formal_parameter_node;  // 对应语法树节点
	std::shared_ptr<std::unordered_map<std::string, std::pair<int, int>>> pos_info;
};

struct ParameterListInfo {  // 一个参数列表(对应文法中的parameter_list)
	std::shared_ptr<std::vector<pascals::FunctionIdentifier::Parameter>> parameters;  // 参数列表
	std::shared_ptr<pascals::ast::ParameterListNode> parameter_list_node;  // 对应语法树节点
	std::shared_ptr<std::unordered_map<std::string, std::pair<int, int>>> pos_info;
};

struct ParameterListsInfo {  // 多个参数列表(对应文法中的parameter_lists)
	std::shared_ptr<std::vector<pascals::FunctionIdentifier::Parameter>> parameters;  // 参数列表
	std::shared_ptr<pascals::ast::ParameterListsNode> parameter_lists_node;  // 对应语法树节点
	std::shared_ptr<std::unordered_map<std::string, std::pair<int, int>>> pos_info;
};

struct VarDeclarationInfo {
	std::shared_ptr<std::unordered_map<std::string, pascals::TypeTemplate*>> record_info;
	std::shared_ptr<pascals::ast::VarDeclarationNode> variable_declaration_node;
	std::shared_ptr<std::unordered_map<std::string, std::pair<int, int>>> pos_info;
};

struct VarParameterInfo {  // 参数列表(引用传递)(对应文法中的var_parameter)
	std::shared_ptr<std::vector<pascals::FunctionIdentifier::Parameter>> parameters;  // 参数列表
	std::shared_ptr<pascals::ast::VarParameterNode> var_parameter_node;  // 对应语法树节点
	std::shared_ptr<std::unordered_map<std::string, std::pair<int, int>>> pos_info;
};

struct ValueParameterInfo {  // 参数列表(值传递)(对应文法中的value_parameter)
	std::shared_ptr<std::vector<pascals::FunctionIdentifier::Parameter>> parameters;  // 参数列表
	std::shared_ptr<pascals::ast::ValueParameterNode> value_parameter_node;  // 对应语法树节点
	std::shared_ptr<std::unordered_map<std::string, std::pair<int, int>>> pos_info;
};

struct VariableInfo {  // read函数的一个参数(对应文法中的variable)
	std::shared_ptr<pascals::TypeTemplate> type;  // 类型
	std::shared_ptr<std::string> name;  // 名
	std::shared_ptr<pascals::ast::VariableNode> variable_node;  // 对应语法树节点
	bool is_lvalue;
};

struct VariableListInfo {  // read函数的参数列表(对应文法中的variable_list) 
	std::shared_ptr<std::vector<std::shared_ptr<pascals::TypeTemplate>>> type_list;  // 类型列表
	std::shared_ptr<pascals::ast::VariableListNode> variable_list_node;  // 对应语法树节点
};

struct ExpressionInfo {  // 表达式(对应文法中的expression) 
	std::shared_ptr<pascals::TypeTemplate> type;  // 类型
	std::shared_ptr<pascals::ast::ExpressionNode> expression_node;  // 对应语法树节点
	bool is_lvalue;
};

struct SimpleExpressionInfo {  // 简单表达式(对应文法中的simple_expression)
	std::shared_ptr<pascals::TypeTemplate> type;  // 类型
	std::shared_ptr<pascals::ast::SimpleExpressionNode> simple_expression_node;  // 对应语法树节点
	bool is_lvalue;
};

struct TermInfo {  // (对应文法中的term)
	std::shared_ptr<pascals::TypeTemplate> type;  // 类型
	std::shared_ptr<pascals::ast::TermNode> term_node;  // 对应语法树节点
	bool is_lvalue;
};

struct FactorInfo {  // (对应文法中的factor)
	std::shared_ptr<pascals::TypeTemplate> type;  // 类型
	std::shared_ptr<pascals::ast::FactorNode> factor_node;  // 对应语法树节点
	bool is_lvalue;
};


struct VarParts {
	bool flag;
	std::vector<pascals::TypeTemplate*>* subscript;
	std::string name;
};

struct IdVarpartInfo {  // (对应文法中的id_varpart)
	VarParts* var_part;
	std::shared_ptr<pascals::ast::IDVarPartNode> id_varpart_node;  // 对应语法树节点
};

struct ExpressionListInfo {  // (对应文法中的expression_list)  
	std::shared_ptr<std::vector<std::shared_ptr<pascals::TypeTemplate>>> type_list;  // 类型列表
	std::shared_ptr<pascals::ast::ExpressionListNode> expression_list_node;  // 对应语法树节点
	std::vector<bool>* is_lvalue_list;
};


#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
struct YYSTYPE {  // Bison .y文件中YYSTYPE的定义 这里定义了，.y文件中就无需再次定义
	Token token_info;
	ValueInfo value_node_info;
	union {
		IdListInfo id_list_node_info;
		TypeInfo type_node_info;
		BasicTypeInfo basic_type_node_info;
		PeriodsInfo periods_node_info;
		PeriodInfo period_node_info;
		FormalParameterInfo formal_parameter_node_info;
		ParameterListsInfo parameter_lists_node_info;
		ParameterListInfo parameter_list_node_info;
		VarParameterInfo var_parameter_node_info;
		ValueParameterInfo value_parameter_node_info;

		VarDeclarationInfo var_declaration_node_info;// 对应文法中var_declaration
		VariableInfo variable_node_info;
		VariableListInfo variable_list_node_info;
		ExpressionInfo expression_node_info;
		SimpleExpressionInfo simple_expression_node_info;
		TermInfo term_node_info;
		FactorInfo factor_node_info;
		IdVarpartInfo id_varpart_node_info;
		ExpressionListInfo expression_list_node_info;

		std::shared_ptr<pascals::ast::ProgramNode> program_node;
		std::shared_ptr<pascals::ast::ProgramHeadNode> program_head_node;  // 对应文法中program_head
		std::shared_ptr<pascals::ast::ProgramBodyNode> program_body_node;  // 对应文法中program_body
		std::shared_ptr<pascals::ast::ConstDeclarationsNode> const_declarations_node;  // 对应文法中const_declarations
		std::shared_ptr<pascals::ast::ConstDeclarationNode> const_declaration_node;  // 对应文法中const_declaration
		std::shared_ptr<pascals::ast::BasicTypeNode> basic_type_node;  // 对应文法中basic_type  
		std::shared_ptr<pascals::ast::VarDeclarationsNode> var_declarations_node;  // 对应文法中var_declarations
		std::shared_ptr<pascals::ast::SubprogramDeclarationsNode> subprogram_declarations_node;  // 对应文法中subprogram_declarations
		std::shared_ptr<pascals::ast::SubprogramNode> subprogram_node;  // 对应文法中subprogram
		std::shared_ptr<pascals::ast::SubprogramHeadNode> subprogram_head_node;  // 对应文法中subprogram_head
		std::shared_ptr<pascals::ast::SubprogramBodyNode> subprogram_body_node;  // 对应文法中subprogram_body
		std::shared_ptr<pascals::ast::CompoundStatementNode> compound_statement_node;  // 对应文法中compound_statement
		std::shared_ptr<pascals::ast::StatementListNode> statement_list_node;  // 对应文法中statement_list
		std::shared_ptr<pascals::ast::StatementNode> statement_node;  // 对应文法中statement
		std::shared_ptr<pascals::ast::ElsePartNode> else_node;  // 对应文法中else_part
		std::shared_ptr<pascals::ast::ProcedureCallNode> procedure_call_node;  // 对应文法中procedure_call
	};
	YYSTYPE() = default;
    ~YYSTYPE() = default;
};
typedef struct YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

