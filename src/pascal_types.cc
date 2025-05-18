#include "pascal_types.h"

namespace pascals {
	// TypeTemplate
	TypeTemplate::TypeTemplate() : m_type(TYPE::BASIC) {}  // 无参构造
	TypeTemplate::TypeTemplate(TYPE type) : m_type(type) {}  // 带参构造
	TypeTemplate::~TypeTemplate() {}  // 析构函数

	TypeTemplate::TYPE TypeTemplate::get_type() {  // 获取类型
		return m_type;
	}

	bool TypeTemplate::is_basic_type(TypeTemplate* type) {  // 判type是否为基础类型
		if (!type) return false;
		if (type->get_type() != TYPE::BASIC) return false;
		auto* basic_type = dynamic_cast<BasicType*>(type);
		return basic_type == TYPE_INTEGER || basic_type == TYPE_REAL || basic_type == TYPE_BOOLEAN || basic_type == TYPE_CHAR;
	}

	bool TypeTemplate::is_same(TypeTemplate* type1, TypeTemplate* type2) {  // 判type1和type2是否相等
		if (!type1 || !type2) return false;
		if (type1 == type2) return true;
		if (type1->get_type() != type2->get_type()) return false;

		if (type1->get_type() == TYPE::ARRAY) {
			auto* a1 = dynamic_cast<ArrayType*>(type1);
			auto* a2 = dynamic_cast<ArrayType*>(type2);
			return a1 && a2 && (*a1 == *a2);
		}
		else if (type1->get_type() == TYPE::BASIC) {
			auto* b1 = dynamic_cast<BasicType*>(type1);
			auto* b2 = dynamic_cast<BasicType*>(type2);
			return b1 && b2 && (b1->get_basic_type() == b2->get_basic_type());
		}
		return false;
	}

	// BasicType
	BasicType::BasicType() : TypeTemplate(TYPE::BASIC), m_basic_type(BASIC_TYPE::NONE) {}  // 无参构造
	BasicType::BasicType(BASIC_TYPE basic_type) : TypeTemplate(TYPE::BASIC), m_basic_type(basic_type) {}  // 带参构造
	BasicType::~BasicType() {}  // 析构函数

	std::string BasicType::get_pascal_name() {  // 获取基础类型对应的Pascal风格数据类型名称
		switch (m_basic_type) {
		case BASIC_TYPE::INTEGER:
			return "integer";
		case BASIC_TYPE::REAL:
			return "real";
		case BASIC_TYPE::BOOLEAN:
			return "boolean";
		case BASIC_TYPE::CHAR:
			return "char";
		default:
			return "none";
		}
	}

	std::string BasicType::get_c_name() {  // 获取基础类型对应的c风格数据类型名称
		switch (m_basic_type) {
		case BASIC_TYPE::INTEGER:
			return "int";
		case BASIC_TYPE::REAL:
			return "float";
		case BASIC_TYPE::BOOLEAN:
			return "int";
		case BASIC_TYPE::CHAR:
			return "char";
		default:
			return "void";
		}
	}

	BasicType::BASIC_TYPE BasicType::get_basic_type() {  // 获取基础类型
		return m_basic_type;
	}

	BasicType* BasicType::get_computed_type(BasicType* operand1_type, BasicType* operand2_type, std::string op) {
		if (!operand1_type || !operand2_type) return TYPE_NONE;
		auto res = g_operation_map.find(Operation(operand1_type, operand2_type, op));
		return res != g_operation_map.end() ? res->second : TYPE_NONE;
	}

	BasicType* BasicType::get_computed_type(BasicType* operand_type, std::string op) {
		if (!operand_type) return TYPE_NONE;
		auto res = g_operation_map.find(Operation(operand_type, nullptr, op));
		return res != g_operation_map.end() ? res->second : TYPE_NONE;
	}


	// ArrayType
	ArrayType::ArrayBound::ArrayBound() : lower_bound(0), upper_bound(0) {}  // ArrayBound无参构造

	ArrayType::ArrayBound& ArrayType::ArrayBound::operator=(const ArrayBound& other) {  // ArrayBound赋值逻辑
		lower_bound = other.lower_bound;
		upper_bound = other.upper_bound;
		return *this;
	}

	bool ArrayType::ArrayBound::operator==(const ArrayBound& other) const {  // ArrayBound判等逻辑
		return lower_bound == other.lower_bound && upper_bound == other.upper_bound;
	}

	ArrayType::ArrayType() : TypeTemplate(TYPE::ARRAY), m_element_type(TYPE_NONE) {}  // ArrayType无参构造
	ArrayType::ArrayType(BasicType* element_type) : TypeTemplate(TYPE::ARRAY), m_element_type(element_type) {}  // 一个参数(元素类型)构造
	ArrayType::ArrayType(BasicType* element_type, std::vector<ArrayBound> bounds)  // 两个参数(元素类型、数组上下界)构造
		: TypeTemplate(TYPE::ARRAY), m_element_type(element_type), m_bounds(std::move(bounds)) {
	}
	ArrayType::ArrayType(const ArrayType& other) {  // ArrayType深拷贝构造
		m_element_type = other.m_element_type;
		for (auto& bound : other.m_bounds) {
			m_bounds.emplace_back(bound);  // 直接在容器末尾构造一个新元素，并避免了临时对象的创建和拷贝
		}
	}
	ArrayType::~ArrayType() {}

	ArrayType& ArrayType::operator=(const ArrayType& other) {  // ArrayType赋值逻辑
		if (this != &other) {
			m_element_type = other.m_element_type;
			m_bounds.clear();  // 清空原有内容
			for (auto& bound : other.m_bounds) {
				m_bounds.emplace_back(bound);
			}
		}
		return *this;
	}

	bool ArrayType::operator==(const ArrayType& other) const {  // ArrayType判等逻辑
		if (m_element_type != other.m_element_type) {  // 元素类型
			return false;
		}
		size_t dimention = m_bounds.size();
		if (dimention != other.m_bounds.size()) {  // 数组维度
			return false;
		}
		for (int i = 0; i < dimention; i++) {  // 上下界
			if (!(m_bounds[i] == other.m_bounds[i])) {
				return false;
			}
		}
		return true;
	}

	std::string ArrayType::get_pascal_name() {  // 获取数组类型对应的Pascal风格数据类型名称
		std::string res = "array";
		res += '[';
		size_t dimention = m_bounds.size();
		for (size_t i = 0; i < dimention; i++) {
			const auto& bound = m_bounds[i];
			res += std::to_string(bound.lower_bound) + ".." + std::to_string(bound.upper_bound);
			if (i != dimention - 1) {
				res += ",";  // 如果不是最后一个元素，添加逗号
			}
		}
		res += "] of " + m_element_type->get_pascal_name();
		return res;
	}

	BasicType* ArrayType::get_element_type() {  // 获取数组元素类型
		return m_element_type;
	}

	size_t ArrayType::get_dimention() {  // 获取数组维度
		return m_bounds.size();
	}

	std::vector<ArrayType::ArrayBound>& ArrayType::get_bounds() {  // 获取数组下标范围们
		return m_bounds;
	}

	ArrayType::ArrayBound ArrayType::get_certain_bound(size_t i) {   // 获取数组指定维度的下标范围(从0开始)
		if (i >= m_bounds.size()) {
			throw std::out_of_range("数组越界");
		}
		return m_bounds[i];
	}

	bool ArrayType::is_valid() {  // 是否有错
		return m_element_type != TYPE_NONE;
	}

	//ConstValue
	ConstValue::ConstValue() {}
	ConstValue::ConstValue(const ConstValue& other) {
		m_const_type = other.m_const_type;
		m_const_value = other.m_const_value;
	}
	ConstValue::~ConstValue() {}

	ConstValue& ConstValue::operator=(const ConstValue& other) {  // 两个常量的赋值操作
		m_const_type = other.m_const_type;
		m_const_value = other.m_const_value;
		return *this;
	}

	ConstValue ConstValue::operator+(const ConstValue& other) {  // 两个常量的加法操作
		if (m_const_type != other.m_const_type) {  // 类型不匹配，出错
			throw std::runtime_error("加法操作：两个常量的类型不匹配");
		}
		if (m_const_type == TYPE_INTEGER) {
			return ConstValue(std::get<int>(m_const_value) + std::get<int>(other.m_const_value));
		}
		if (m_const_type == TYPE_REAL) {
			return ConstValue(std::get<float>(m_const_value) + std::get<float>(other.m_const_value));
		}
		if (m_const_type == TYPE_CHAR) {
			return ConstValue(std::get<char>(m_const_value) + std::get<char>(other.m_const_value));
		}
		throw std::runtime_error("常量类型(boolean)不支持加法运算");
	}

	ConstValue ConstValue::operator-(const ConstValue& other) {  // 两个常量的减法操作
		if (m_const_type != other.m_const_type) {  // 类型不匹配，出错
			throw std::runtime_error("减法操作：两个常量的类型不匹配");
		}
		if (m_const_type == TYPE_INTEGER) {
			return ConstValue(std::get<int>(m_const_value) - std::get<int>(other.m_const_value));
		}
		if (m_const_type == TYPE_REAL) {
			return ConstValue(std::get<float>(m_const_value) - std::get<float>(other.m_const_value));
		}
		if (m_const_type == TYPE_CHAR) {
			return ConstValue(static_cast<char>(std::get<char>(m_const_value) - std::get<char>(other.m_const_value)));
		}
		throw std::runtime_error("常量类型(boolean)不支持减法运算");
	}

	ConstValue ConstValue::operator*(const ConstValue& other) {  // 两个常量的乘法操作
		if (m_const_type != other.m_const_type) {  // 类型不匹配，出错
			throw std::runtime_error("乘法操作：两个常量的类型不匹配");
		}
		if (m_const_type == TYPE_INTEGER) {
			return ConstValue(std::get<int>(m_const_value) * std::get<int>(other.m_const_value));
		}
		if (m_const_type == TYPE_REAL) {
			return ConstValue(std::get<float>(m_const_value) * std::get<float>(other.m_const_value));
		}
		throw std::runtime_error("常量类型(char,boolean)不支持乘法运算");
	}

	ConstValue ConstValue::operator/(const ConstValue& other) {  // 两个常量的除法操作
		if (m_const_type != other.m_const_type) {  // 类型不匹配，出错
			throw std::runtime_error("除法操作：两个常量的类型不匹配");
		}
		if (m_const_type == TYPE_INTEGER) {
			if (std::get<int>(other.m_const_value) == 0) {  // 除数为0，出错
				throw std::runtime_error("除法操作：除数不能为零");
			}
			return ConstValue(std::get<int>(m_const_value) / std::get<int>(other.m_const_value));
		}
		if (m_const_type == TYPE_REAL) {
			if (std::get<float>(other.m_const_value) == 0) {  // 除数为0，出错
				throw std::runtime_error("除法操作：除数不能为零");
			}
			return ConstValue(std::get<float>(m_const_value) / std::get<float>(other.m_const_value));
		}
		throw std::runtime_error("常量类型(char,boolean)不支持除法运算");
	}

	void ConstValue::negate_value() {  // 对常量值取相反数
		if (m_const_type == TYPE_REAL) {
			m_const_value = -std::get<float>(m_const_value);
		}
		else if (m_const_type == TYPE_INTEGER) {
			m_const_value = -std::get<int>(m_const_value);
		}
		else if (m_const_type == TYPE_CHAR) {
			m_const_value = -std::get<char>(m_const_value);
		}
		else
			throw std::runtime_error("常量类型(boolean)不支持取相反数");
	}

	BasicType* ConstValue::get_type() {  // 获取常量对应的类型
		return m_const_type;
	}

	// Operation
	Operation::Operation(BasicType* operand1_type, BasicType* operand2_type, const std::string& op) :
		m_operand1_type(operand1_type), m_operand2_type(operand2_type), m_op(op) {
	}
	Operation::~Operation() {}

	bool Operation::operator==(const Operation& other) const {  // 判等操作
		return m_operand1_type == other.m_operand1_type && m_operand2_type == other.m_operand2_type && m_op == other.m_op;
	}

	// 全局变量
	BasicType* TYPE_INTEGER;
	BasicType* TYPE_REAL;
	BasicType* TYPE_BOOLEAN;
	BasicType* TYPE_CHAR;
	BasicType* TYPE_STRING;
	BasicType* TYPE_NONE;
	// std::shared_ptr<std::vector<std::shared_ptr<TypeTemplate>>> g_ptr_collector;
	std::unordered_map<Operation, BasicType*, OperationHash> g_operation_map;

	void pascal_types_init() {  // 全局变量初始化
		TYPE_INTEGER = new BasicType(BasicType::BASIC_TYPE::INTEGER);
		TYPE_REAL = new BasicType(BasicType::BASIC_TYPE::REAL);
		TYPE_BOOLEAN = new BasicType(BasicType::BASIC_TYPE::BOOLEAN);
		TYPE_CHAR = new BasicType(BasicType::BASIC_TYPE::CHAR);
		TYPE_STRING = new BasicType(BasicType::BASIC_TYPE::STRING);
		TYPE_NONE = new BasicType(BasicType::BASIC_TYPE::NONE);
		// g_ptr_collector = std::make_shared<std::vector<std::shared_ptr<TypeTemplate>>>();

		// int
		g_operation_map[Operation(TYPE_INTEGER, nullptr, "-")] = TYPE_INTEGER;
		g_operation_map[Operation(TYPE_INTEGER, nullptr, "+")] = TYPE_INTEGER;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "+")] = TYPE_INTEGER;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "-")] = TYPE_INTEGER;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "*")] = TYPE_INTEGER;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "/")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "mod")] = TYPE_INTEGER;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "div")] = TYPE_INTEGER;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "<>")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "<")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, ">")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, "<=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_INTEGER, ">=")] = TYPE_BOOLEAN;

		// real
		g_operation_map[Operation(TYPE_REAL, nullptr, "-")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, nullptr, "+")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, "+")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, "-")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, "*")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, "/")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, "=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, "<>")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, ">")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, "<")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, ">=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_REAL, "<=")] = TYPE_BOOLEAN;

		// int & real
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, "+")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, "-")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, "*")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, "/")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, "=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, "<>")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, ">")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, ">=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, "<=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_REAL, TYPE_INTEGER, "<")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, "+")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, "-")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, "*")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, "/")] = TYPE_REAL;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, "=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, "<>")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, ">")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, ">=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, "<=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_INTEGER, TYPE_REAL, "<")] = TYPE_BOOLEAN;

		// boolean
		g_operation_map[Operation(TYPE_BOOLEAN, TYPE_BOOLEAN, "and")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_BOOLEAN, TYPE_BOOLEAN, "or")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_BOOLEAN, nullptr, "not")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_BOOLEAN, TYPE_BOOLEAN, "=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_BOOLEAN, TYPE_BOOLEAN, "<>")] = TYPE_BOOLEAN;

		// char
		g_operation_map[Operation(TYPE_CHAR, TYPE_CHAR, "=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_CHAR, TYPE_CHAR, "<>")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_CHAR, TYPE_CHAR, "<")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_CHAR, TYPE_CHAR, "<=")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_CHAR, TYPE_CHAR, ">")] = TYPE_BOOLEAN;
		g_operation_map[Operation(TYPE_CHAR, TYPE_CHAR, ">=")] = TYPE_BOOLEAN;
	}
}