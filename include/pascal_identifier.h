// 标识符定义
#pragma once
#include "pascal_types.h"

namespace pascals {

	class Identifier {  // 标识符，默认为变量名
	public:
		enum class IDENTIFIER_TYPE { VAR, CONST, FUNCTION };  // 标识符类型(变量名/常量名/函数名)
		Identifier();
		Identifier(std::string name, std::shared_ptr<TypeTemplate> value_type, bool is_reference = false, int declare_line = 0);  // 默认构造为变量名
		virtual ~Identifier();
		std::string get_name();  // 获取标识符名
		std::shared_ptr<TypeTemplate> get_value_type();  // 获取标识符值的类型
		IDENTIFIER_TYPE get_identifier_type();  // 获取标识符类型
		virtual bool is_reference();  // 是否引用类型
		int get_declare_line();  // 获取标识符声明行
		virtual void set_reference(bool is_reference);  // 设置是否为引用类型
	protected:
		std::string m_name;  // 标识符名
		std::shared_ptr<TypeTemplate> m_value_type;  // 标识符值的类型
		IDENTIFIER_TYPE m_identifier_type;  // 标识符类型
		bool m_is_reference;  // 是否引用类型
		int m_declare_line;  // 声明行
	};

	class ConstIdentifier : public Identifier {  // 继承自Identifier，表示常量名
	public:
		ConstIdentifier();
		ConstIdentifier(std::string name, ConstValue value, int declare_line);  // 默认构造为常量名
		~ConstIdentifier();
		ConstValue get_value();  // 获取常量值
		bool is_reference() override;  // 是否引用类型，常量名为非引用
		void set_reference(bool r) override;  // 设置是否为引用类型，常量名为非引用
	private:
		ConstValue m_value;  // 常量值
	};

	class FunctionIdentifier : public Identifier {  // 继承自Identifier，表示函数名
	public:
		struct Parameter {  // 函数参数
			std::string param_name;  // 参数名
			std::shared_ptr<TypeTemplate> param_type;  // 参数类型
			bool is_reference;   // 是否引用类型
		};

		FunctionIdentifier();
		FunctionIdentifier(const FunctionIdentifier& other);  // 深拷贝构造
		FunctionIdentifier(std::string name, std::shared_ptr<BasicType> return_type, int decl_line, const std::vector<Parameter>& params_list);
		FunctionIdentifier(std::string name, std::shared_ptr<BasicType> return_type, int decl_line);

		int get_param_count();  // 获取参数数量
		std::shared_ptr<Parameter> get_param_at(int index);  // 获取第index+1个参数指针
		bool add_param(const Parameter& param);  // 向参数列表末尾添加参数
        bool is_certain_param_reference(std::string param_name);  // 判指定参数是否引用类型
		bool is_reference() override;  // 是否引用类型，函数名为非引用
		void set_reference(bool r) override;  // 设置是否为引用类型，函数名为非引用


		// 等待实现
		bool AssertParams(const std::vector<TypeTemplate*>& params,
			const std::vector<bool> value_type_in);
		bool AssertParams();
		std::string ParamName();
		std::vector<bool> ParamRefVec();

	private:
		std::vector<Parameter> m_params_list;  // 函数参数列表
		std::unordered_map<std::string, int> m_param_map;  // 键为参数名，值为参数在m_params_list中下标
	};
}