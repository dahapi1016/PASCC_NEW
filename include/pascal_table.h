// ���ű���
#pragma once
#include "pascal_identifier.h"

namespace pascals {
    class SymbolTable {  // ���ű�
    public:
        SymbolTable(std::string tag = "", std::unordered_map<std::string, std::shared_ptr<Identifier>> map = {}, std::shared_ptr<SymbolTable> prev_table = nullptr) :
            m_tag(tag), m_map(map), m_prev_table(prev_table) {
        }
        ~SymbolTable() {}
        std::string get_tag() {  // ��ȡ��ǰ���ű��ʶ
            return m_tag; 
        }
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Identifier>>> get_map() {  // ��ȡ��ǰ���ű�
            return std::make_shared<std::unordered_map<std::string, std::shared_ptr<Identifier>>>(m_map); 
        }
        std::shared_ptr<SymbolTable> get_prev_table() {  // ��ȡ��һ����ű�
            return m_prev_table; 
        }
        bool insert_element(std::string name, std::shared_ptr<Identifier> identifier_ptr) {  // ���������µļ�ֵ��
            if (m_map.find(name) != m_map.end()) {  // �������ж�Ӧ��ʶ����������ʧ��
                return false;
            }
            m_map.insert(std::make_pair(name, identifier_ptr));
            return true;
        }
        std::shared_ptr<Identifier> get_identifier_by_name(std::string name) {  // ���ݱ�ʶ�������ض�Ӧ��ʶ����ָ��
            auto it = m_map.find(name);
            if (it != m_map.end()) {
                return it->second;
            }
            if (m_prev_table != nullptr) {  // ��ǰ����ű��Ҳ������ݹ������һ��
                return m_prev_table->get_identifier_by_name(name);
            }
            return nullptr;
        }
    protected:
        std::string m_tag;  // ���ڱ�ʶ������ű�(����/������)
        std::unordered_map<std::string, std::shared_ptr<Identifier>> m_map;  // ��Ϊ��ʶ������ֵΪ��Ӧ�ñ�ʶ����ָ��
        std::shared_ptr<SymbolTable> m_prev_table;  // ָ�������ű��ָ��
    };
}
