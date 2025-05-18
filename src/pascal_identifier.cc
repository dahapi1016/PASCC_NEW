#include "pascal_identifier.h"

namespace pascals {
	// Identifier
	Identifier::Identifier() {}
	Identifier::Identifier(std::string name, TypeTemplate* value_type, bool is_reference, int declare_line) :
		m_name(name), m_value_type(value_type), m_is_reference(is_reference), m_declare_line(declare_line) {
		m_identifier_type = IDENTIFIER_TYPE::VAR;
	}
	Identifier::~Identifier() {}

	std::string Identifier::get_name() { 
		return m_name; 
	}
	TypeTemplate* Identifier::get_value_type() {
		return m_value_type; 
	}
	Identifier::IDENTIFIER_TYPE Identifier::get_identifier_type() { 
		return m_identifier_type; 
	}
	int Identifier::get_declare_line() { 
		return m_declare_line; 
	}
	bool Identifier::is_reference() { 
		return m_is_reference; 
	}
	void Identifier::set_reference(bool is_reference) { 
		m_is_reference = is_reference; 
	}

	// ConstIdentifier
	ConstIdentifier::ConstIdentifier() {}
	ConstIdentifier::ConstIdentifier(std::string name, ConstValue value, int declare_line) :
		Identifier(name, value.get_type(), declare_line), m_value(value) {
		m_identifier_type = IDENTIFIER_TYPE::CONST;
	}
	ConstIdentifier::~ConstIdentifier() {}

	ConstValue ConstIdentifier::get_value() {  // 获取常量值
		return m_value;
	}  
	bool ConstIdentifier::is_reference() {  // 是否引用类型，常量为非引用
		return false;
	}
	void ConstIdentifier::set_reference(bool r) {  // 设置是否为引用类型，常量为非引用
		m_is_reference = false; 
	}  

	// FunctionIdentifier
	FunctionIdentifier::FunctionIdentifier() {}
	FunctionIdentifier::FunctionIdentifier(const FunctionIdentifier& other) :
		Identifier(other.m_name, other.m_value_type, other.m_declare_line) {
		m_identifier_type = IDENTIFIER_TYPE::FUNCTION;
		m_params_list.assign(other.m_params_list.begin(), other.m_params_list.end());
		for (auto it = other.m_param_map.begin(); it != other.m_param_map.end(); it++) {
			m_param_map[it->first] = it->second;
		}
	}
	FunctionIdentifier::FunctionIdentifier(std::string name, BasicType* return_type, int declare_line, const std::vector<Parameter>& params_list) :
		Identifier(name, return_type, declare_line), m_params_list(params_list) {
		m_identifier_type = IDENTIFIER_TYPE::FUNCTION;
		for (int i = 0; i < params_list.size(); i++) {
			m_param_map[params_list[i].param_name] = i;
		}
	}
	FunctionIdentifier::FunctionIdentifier(std::string name, BasicType* return_type, int declare_line) :
		Identifier(name, return_type, declare_line) {
		m_identifier_type = IDENTIFIER_TYPE::FUNCTION;
	}

	int FunctionIdentifier::get_param_count() {  // 获取参数数量
		return m_params_list.size();
	}
	FunctionIdentifier::Parameter* FunctionIdentifier::get_param_at(int index) {  // 获取第index+1个参数指针
		// 原代码返回的是对象，需要返回对象的指针，因此取地址
		return &m_params_list[index];
	}
	bool FunctionIdentifier::is_certain_param_reference(std::string param_name) {  // 判指定参数是否为引用类型
		auto it = m_param_map.find(param_name);
		if (it == m_param_map.end()) {  // 若参数列表中没有该参数
			return false;
		}
		return m_params_list[it->second].is_reference;
	}
	bool FunctionIdentifier::is_reference() {  // 是否引用类型，函数名为非引用
		return false;
	}
	void FunctionIdentifier::set_reference(bool r) {  // 设置是否为引用类型，函数名为非引用
		m_is_reference = false;
	};
	bool FunctionIdentifier::add_param(const Parameter& param) {  // 向参数列表末尾添加参数
		auto it = m_param_map.find(param.param_name);
		if (it == m_param_map.end()) {  // 参数列表中无该参数，添加成功
			m_params_list.emplace_back(param);
			m_param_map[param.param_name] = m_params_list.size() - 1;
			return true;
		}
		else {  // 参数列表中已有该参数，添加失败
			return false;
		}
	}
	TypeTemplate* FunctionIdentifier::get_param_type_by_name(std::string name) {  // 根据参数名获取其类型
		auto ptr = m_param_map.find(name);
		return m_params_list[ptr->second].param_type;
	}
	bool FunctionIdentifier::get_param_is_reference_by_name(std::string name) {  // 根据参数名获取是否为引用
		auto ptr = m_param_map.find(name);
		return m_params_list[ptr->second].is_reference;
	}
}