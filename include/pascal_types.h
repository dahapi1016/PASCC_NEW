// 类型定义
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <variant>

namespace pascals {

	class TypeTemplate {  // 类型模板(基类)
	public:
		enum class TYPE { BASIC, ARRAY };  // 基础类型、数组类型
		TypeTemplate();  // 无参构造
		TypeTemplate(TYPE type);  // 带参构造
		virtual ~TypeTemplate();  // 析构函数
		TYPE get_type();  // 获取类型
		virtual std::string get_pascal_name() = 0;  // 获取对应的Pascal风格数据类型名称
		static bool is_basic_type(std::shared_ptr<TypeTemplate> type);  // 判t是否为基础类型
		bool is_same(std::shared_ptr<TypeTemplate> type1, std::shared_ptr<TypeTemplate> type2);  // 判两个类型是否相同
	protected:
		TYPE m_type;  // 类型
	};

	class BasicType : public TypeTemplate, public std::enable_shared_from_this<BasicType> {  // 继承自TypeTemplate，表示基础类型
	public:
		enum class BASIC_TYPE { INTEGER, REAL, BOOLEAN, CHAR, STRING, NONE };  // NONE表示无类型或未初始化类型
		BasicType();  // 无参构造
		BasicType(BASIC_TYPE basic_type);  // 带参构造
		~BasicType();  // 析构函数
		BASIC_TYPE get_basic_type();  // 获取基础类型
		std::string get_pascal_name() override;  // 获取对应的Pascal风格数据类型名称
		std::string get_c_name();  // 获取对应的c风格数据类型名称
		std::shared_ptr<BasicType> get_computed_type(std::shared_ptr<BasicType> type1, std::shared_ptr<BasicType> type2, std::string op);  // 两种类型进行op操作后的结果类型
		std::shared_ptr<BasicType> get_computed_type(std::shared_ptr<BasicType> t1, std::string op);  // 一种类型进行op操作后的结果类型
	private:
		BASIC_TYPE m_basic_type;  // 基础类型
	};

	class ArrayType : public TypeTemplate, public std::enable_shared_from_this<ArrayType> {  // 继承自TypeTemplate，表示数组类型
	public:
		struct ArrayBound {  // 一维数组上下界
			int lower_bound;  // 数组下界
			int upper_bound;  // 数组上界
			ArrayBound();  // 无参构造
			ArrayBound(const ArrayBound& other) = default;  // 浅拷贝构造
			ArrayBound& operator=(const ArrayBound& other);  // 赋值逻辑
			bool operator==(const ArrayBound& other) const;  // 判等逻辑
		};
		ArrayType();  // 无参构造
		ArrayType(std::shared_ptr<BasicType> element_type);  // 一个参数(元素类型)构造
		ArrayType(std::shared_ptr<BasicType> element_type, std::vector<ArrayBound> bounds);  // 两个参数(元素类型、数组上下界)构造
		ArrayType(const ArrayType& other);  // 深拷贝构造
		~ArrayType();  // 析构函数
		ArrayType& operator=(const ArrayType& other);  // 赋值逻辑
		bool operator==(const ArrayType& other) const;  // 判等逻辑
		std::string get_pascal_name() override;  // 获取对应的Pascal风格数据类型名称
		std::shared_ptr<BasicType> get_element_type();  // 获取数组元素类型
		size_t get_dimention();  // 获取数组维度
		std::vector<ArrayBound>& get_bounds();  // 获取数组下标范围们
		ArrayBound get_certain_bound(size_t i);  // 获取数组指定维度的下标范围(从0开始)
		bool is_valid();  // 是否有错

		// 下面的没懂
		// visitor by layer or by types
		ArrayType Visit(std::vector<TypeTemplate*> v_types);  // visit array
		ArrayType Visit(unsigned int v_layer);                 // visit array
	private:
		std::shared_ptr<BasicType> m_element_type;  // 元素类型
		std::vector<ArrayBound> m_bounds;  // 数组各维数上下界(多维)
	};

	// 全局变量
	extern std::shared_ptr<BasicType> TYPE_INTEGER;
	extern std::shared_ptr<BasicType> TYPE_REAL;
	extern std::shared_ptr<BasicType> TYPE_BOOLEAN;
	extern std::shared_ptr<BasicType> TYPE_CHAR;
	extern std::shared_ptr<BasicType> TYPE_STRING;
	extern std::shared_ptr<BasicType> TYPE_NONE;

	class ConstValue {  // 常量
	public:
		ConstValue();
		ConstValue(const ConstValue& other);
		template <typename T> ConstValue(T v) {
			set_type_and_value(v);
		}
		~ConstValue();
		ConstValue& operator=(const ConstValue& other);  // 赋值操作
		ConstValue operator+(const ConstValue& other);  // 当前对象与const_value作加法操作
		ConstValue operator-(const ConstValue& other);  // 当前对象与const_value作减法操作
		ConstValue operator*(const ConstValue& other);  // 当前对象与const_value作乘法操作
		ConstValue operator/(const ConstValue& other);  // 当前对象与const_value作除法操作
		template <typename T> void set_type_and_value(T v) {  // 设置常量类型&值
			if constexpr (std::is_same_v<T, int>) {  // 如果set的值是int类型
				m_const_type = TYPE_INTEGER;
			}
			else if constexpr (std::is_same_v<T, float>) {  // 如果set的值是float类型
				m_const_type = TYPE_REAL;
			}
			else if constexpr (std::is_same_v<T, bool>) {  // 如果set的值是bool类型
				m_const_type = TYPE_BOOLEAN;
			}
			else if constexpr (std::is_same_v<T, char>) {  // 如果set的值是char类型
				m_const_type = TYPE_CHAR;
			}
			else if constexpr (std::is_same_v<T, std::string>) {  // 如果set的值是string类型
				m_const_type = TYPE_STRING;
			}
			m_const_value = v;
		}
		void negate_value();  // 对常量值取反
		std::shared_ptr<BasicType> get_type();  // 获取常量对应的类型
		template <typename T> T get_value() {  // 获取常量对应的值
			if constexpr (std::is_same_v<T, int>) {
				return std::get<int>(m_const_value);  // 提取int类型的值
			}
			else if constexpr (std::is_same_v<T, char>) {
				return std::get<char>(m_const_value);  // 提取char类型的值
			}
			else if constexpr (std::is_same_v<T, float>) {
				return std::get<float>(m_const_value);  // 提取float类型的值
			}
			else if constexpr (std::is_same_v<T, bool>) {
				return std::get<bool>(m_const_value);  // 提取bool类型的值
			}
			else if constexpr (std::is_same_v<T, std::string>) {
				return std::get<std::string>(m_const_value);  // 提取std::string类型的值
			}
		}
	private:
		std::shared_ptr<BasicType> m_const_type = nullptr;  // 常量类型
		std::variant<int, float, bool, char, std::string> m_const_value;  // 常量值
	};

	class Operation {  // 运算类
	public:
		Operation(std::shared_ptr<BasicType> operand1_type, std::shared_ptr<BasicType> operand2_type, const std::string& op);
		~Operation();
		bool operator==(const Operation& other) const;  // 判等操作
		std::shared_ptr<BasicType> m_operand1_type;  // 操作数1类型
		std::shared_ptr<BasicType> m_operand2_type;  // 操作数2类型(若为一元运算符则为null)
		std::string m_op;  // 运算符
	};

	// 留待修改
	extern std::shared_ptr<std::vector<std::shared_ptr<TypeTemplate>>> g_ptr_collector;
	static void collect_ptr(std::shared_ptr<TypeTemplate> ptr) {
		if (ptr->get_type() == TypeTemplate::TYPE::BASIC)
			return;
		g_ptr_collector->push_back(std::move(ptr));
	}

	struct OperationHash {  // 哈希函数
		std::size_t operator()(const Operation& k) const {
			std::size_t seed = 0;
			std::hash<std::shared_ptr<BasicType>> type_hash;
			std::hash<std::string> op_hash;
			seed ^= type_hash(k.m_operand1_type) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			if (k.m_operand2_type) {
				seed ^= type_hash(k.m_operand2_type) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}
			seed ^= op_hash(k.m_op) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			return seed;
		}
	};
	extern std::unordered_map<Operation, std::shared_ptr<BasicType>, OperationHash> g_operation_map;  // 键为运算类，值为运算后结果类型

	void pascal_types_init();  // 全局变量初始化
}