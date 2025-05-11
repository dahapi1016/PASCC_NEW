// ���Ͷ���
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <variant>

namespace pascals {

	class TypeTemplate {  // ����ģ��(����)
	public:
		enum class TYPE { BASIC, ARRAY };  // �������͡���������
		TypeTemplate();  // �޲ι���
		TypeTemplate(TYPE type);  // ���ι���
		virtual ~TypeTemplate();  // ��������
		TYPE get_type();  // ��ȡ����
		virtual std::string get_pascal_name() = 0;  // ��ȡ��Ӧ��Pascal���������������
		bool is_basic_type(std::shared_ptr<TypeTemplate> type);  // ��t�Ƿ�Ϊ��������
		bool is_same(std::shared_ptr<TypeTemplate> type1, std::shared_ptr<TypeTemplate> type2);  // �����������Ƿ���ͬ
	protected:
		TYPE m_type;  // ����
	};

	class BasicType : public TypeTemplate, public std::enable_shared_from_this<BasicType> {  // �̳���TypeTemplate����ʾ��������
	public:
		enum class BASIC_TYPE { INTEGER, REAL, BOOLEAN, CHAR, STRING, NONE };  // NONE��ʾ�����ͻ�δ��ʼ������
		BasicType();  // �޲ι���
		BasicType(BASIC_TYPE basic_type);  // ���ι���
		~BasicType();  // ��������
		BASIC_TYPE get_basic_type();  // ��ȡ��������
		std::string get_pascal_name() override;  // ��ȡ��Ӧ��Pascal���������������
		std::string get_c_name();  // ��ȡ��Ӧ��c���������������
		std::shared_ptr<BasicType> get_computed_type(std::shared_ptr<BasicType> type1, std::shared_ptr<BasicType> type2, std::string op);  // �������ͽ���op������Ľ������
		std::shared_ptr<BasicType> get_computed_type(std::shared_ptr<BasicType> t1, std::string op);  // һ�����ͽ���op������Ľ������
	private:
		BASIC_TYPE m_basic_type;  // ��������
	};

	class ArrayType : public TypeTemplate, public std::enable_shared_from_this<ArrayType> {  // �̳���TypeTemplate����ʾ��������
	public:
		struct ArrayBound {  // һά�������½�
			int lower_bound;  // �����½�
			int upper_bound;  // �����Ͻ�
			ArrayBound();  // �޲ι���
			ArrayBound(const ArrayBound& other) = default;  // ǳ��������
			ArrayBound& operator=(const ArrayBound& other);  // ��ֵ�߼�
			bool operator==(const ArrayBound& other) const;  // �е��߼�
		};
		ArrayType();  // �޲ι���
		ArrayType(std::shared_ptr<BasicType> element_type);  // һ������(Ԫ������)����
		ArrayType(std::shared_ptr<BasicType> element_type, std::vector<ArrayBound> bounds);  // ��������(Ԫ�����͡��������½�)����
		ArrayType(const ArrayType& other);  // �������
		~ArrayType();  // ��������
		ArrayType& operator=(const ArrayType& other);  // ��ֵ�߼�
		bool operator==(const ArrayType& other) const;  // �е��߼�
		std::string get_pascal_name() override;  // ��ȡ��Ӧ��Pascal���������������
		std::shared_ptr<BasicType> get_element_type();  // ��ȡ����Ԫ������
		size_t get_dimention();  // ��ȡ����ά��
		std::vector<ArrayBound>& get_bounds();  // ��ȡ�����±귶Χ��
		ArrayBound get_certain_bound(size_t i);  // ��ȡ����ָ��ά�ȵ��±귶Χ(��0��ʼ)
		bool is_valid();  // �Ƿ��д�

		// �����û��
		// visitor by layer or by types
		ArrayType Visit(std::vector<TypeTemplate*> v_types);  // visit array
		ArrayType Visit(unsigned int v_layer);                 // visit array
	private:
		std::shared_ptr<BasicType> m_element_type;  // Ԫ������
		std::vector<ArrayBound> m_bounds;  // �����ά�����½�(��ά)
	};

	// ȫ�ֱ���
	extern std::shared_ptr<BasicType> TYPE_INTEGER;
	extern std::shared_ptr<BasicType> TYPE_REAL;
	extern std::shared_ptr<BasicType> TYPE_BOOLEAN;
	extern std::shared_ptr<BasicType> TYPE_CHAR;
	extern std::shared_ptr<BasicType> TYPE_STRING;
	extern std::shared_ptr<BasicType> TYPE_NONE;

	class ConstValue {  // ����
	public:
		ConstValue();
		ConstValue(const ConstValue& other);
		template <typename T> ConstValue(T v) {
			set_type_and_value(v);
		}
		~ConstValue();
		ConstValue& operator=(const ConstValue& other);  // ��ֵ����
		ConstValue operator+(const ConstValue& other);  // ��ǰ������const_value���ӷ�����
		ConstValue operator-(const ConstValue& other);  // ��ǰ������const_value����������
		ConstValue operator*(const ConstValue& other);  // ��ǰ������const_value���˷�����
		ConstValue operator/(const ConstValue& other);  // ��ǰ������const_value����������
		template <typename T> void set_type_and_value(T v) {  // ���ó�������&ֵ
			if constexpr (std::is_same_v<T, int>) {  // ���set��ֵ��int����
				m_const_type = TYPE_INTEGER;
			}
			else if constexpr (std::is_same_v<T, float>) {  // ���set��ֵ��float����
				m_const_type = TYPE_REAL;
			}
			else if constexpr (std::is_same_v<T, bool>) {  // ���set��ֵ��bool����
				m_const_type = TYPE_BOOLEAN;
			}
			else if constexpr (std::is_same_v<T, char>) {  // ���set��ֵ��char����
				m_const_type = TYPE_CHAR;
			}
			else if constexpr (std::is_same_v<T, std::string>) {  // ���set��ֵ��string����
				m_const_type = TYPE_STRING;
			}
			m_const_value = v;
		}
		void negate_value();  // �Գ���ֵȡ��
		std::shared_ptr<BasicType> get_type();  // ��ȡ������Ӧ������
		template <typename T> T get_value() {  // ��ȡ������Ӧ��ֵ
			if constexpr (std::is_same_v<T, int>) {
				return std::get<int>(m_const_value);  // ��ȡint���͵�ֵ
			}
			else if constexpr (std::is_same_v<T, char>) {
				return std::get<char>(m_const_value);  // ��ȡchar���͵�ֵ
			}
			else if constexpr (std::is_same_v<T, float>) {
				return std::get<float>(m_const_value);  // ��ȡfloat���͵�ֵ
			}
			else if constexpr (std::is_same_v<T, bool>) {
				return std::get<bool>(m_const_value);  // ��ȡbool���͵�ֵ
			}
			else if constexpr (std::is_same_v<T, std::string>) {
				return std::get<std::string>(m_const_value);  // ��ȡstd::string���͵�ֵ
			}
		}
	private:
		std::shared_ptr<BasicType> m_const_type = nullptr;  // ��������
		std::variant<int, float, bool, char, std::string> m_const_value;  // ����ֵ
	};

	class Operation {  // ������
	public:
		Operation(std::shared_ptr<BasicType> operand1_type, std::shared_ptr<BasicType> operand2_type, const std::string& op);
		~Operation();
		bool operator==(const Operation& other) const;  // �еȲ���
		std::shared_ptr<BasicType> m_operand1_type;  // ������1����
		std::shared_ptr<BasicType> m_operand2_type;  // ������2����(��ΪһԪ�������Ϊnull)
		std::string m_op;  // �����
	};

	// �����޸�
	extern std::shared_ptr<std::vector<std::shared_ptr<TypeTemplate>>> g_ptr_collector;
	static void collect_ptr(std::shared_ptr<TypeTemplate> ptr) {
		if (ptr->get_type() == TypeTemplate::TYPE::BASIC)
			return;
		g_ptr_collector->push_back(std::move(ptr));
	}

	struct OperationHash {  // ��ϣ����
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
	extern std::unordered_map<Operation, std::shared_ptr<BasicType>, OperationHash> g_operation_map;  // ��Ϊ�����ֵ࣬Ϊ�����������

	void pascal_types_init();  // ȫ�ֱ�����ʼ��
}