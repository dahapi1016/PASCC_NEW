// ��ʶ������
#pragma once
#include "pascal_types.h"

namespace pascals {

	class Identifier {  // ��ʶ����Ĭ��Ϊ������
	public:
		enum class IDENTIFIER_TYPE { VAR, CONST, FUNCTION };  // ��ʶ������(������/������/������)
		Identifier();
		Identifier(std::string name, std::shared_ptr<TypeTemplate> value_type, bool is_reference = false, int declare_line = 0);  // Ĭ�Ϲ���Ϊ������
		virtual ~Identifier();
		std::string get_name();  // ��ȡ��ʶ����
		std::shared_ptr<TypeTemplate> get_value_type();  // ��ȡ��ʶ��ֵ������
		IDENTIFIER_TYPE get_identifier_type();  // ��ȡ��ʶ������
		virtual bool is_reference();  // �Ƿ���������
		int get_declare_line();  // ��ȡ��ʶ��������
		virtual void set_reference(bool is_reference);  // �����Ƿ�Ϊ��������
	protected:
		std::string m_name;  // ��ʶ����
		std::shared_ptr<TypeTemplate> m_value_type;  // ��ʶ��ֵ������
		IDENTIFIER_TYPE m_identifier_type;  // ��ʶ������
		bool m_is_reference;  // �Ƿ���������
		int m_declare_line;  // ������
	};

	class ConstIdentifier : public Identifier {  // �̳���Identifier����ʾ������
	public:
		ConstIdentifier();
		ConstIdentifier(std::string name, ConstValue value, int declare_line);  // Ĭ�Ϲ���Ϊ������
		~ConstIdentifier();
		ConstValue get_value();  // ��ȡ����ֵ
		bool is_reference() override;  // �Ƿ��������ͣ�������Ϊ������
		void set_reference(bool r) override;  // �����Ƿ�Ϊ�������ͣ�������Ϊ������
	private:
		ConstValue m_value;  // ����ֵ
	};

	class FunctionIdentifier : public Identifier {  // �̳���Identifier����ʾ������
	public:
		struct Parameter {  // ��������
			std::string param_name;  // ������
			std::shared_ptr<TypeTemplate> param_type;  // ��������
			bool is_reference;   // �Ƿ���������
		};

		FunctionIdentifier();
		FunctionIdentifier(const FunctionIdentifier& other);  // �������
		FunctionIdentifier(std::string name, std::shared_ptr<BasicType> return_type, int decl_line, const std::vector<Parameter>& params_list);
		FunctionIdentifier(std::string name, std::shared_ptr<BasicType> return_type, int decl_line);

		int get_param_count();  // ��ȡ��������
		std::shared_ptr<Parameter> get_param_at(int index);  // ��ȡ��index+1������ָ��
		bool add_param(const Parameter& param);  // ������б�ĩβ��Ӳ���
        bool is_certain_param_reference(std::string param_name);  // ��ָ�������Ƿ���������
		bool is_reference() override;  // �Ƿ��������ͣ�������Ϊ������
		void set_reference(bool r) override;  // �����Ƿ�Ϊ�������ͣ�������Ϊ������
		std::shared_ptr<TypeTemplate> get_param_type_by_name(std::string name);  // ���ݲ�������ȡ������
		bool get_param_is_reference_by_name(std::string name);  // ���ݲ�������ȡ�Ƿ�Ϊ����

		// �ȴ�ʵ��
		bool AssertParams(const std::vector<TypeTemplate*>& params,
			const std::vector<bool> value_type_in);
		bool AssertParams();
		std::string ParamName();
		std::vector<bool> ParamRefVec();

	private:
		std::vector<Parameter> m_params_list;  // ���������б�
		std::unordered_map<std::string, int> m_param_map;  // ��Ϊ��������ֵΪ������m_params_list���±�
	};
}