// 符号表定义
#pragma once
#include "pascal_identifier.h"

namespace pascals {
    class SymbolTable {  // 符号表
    public:
        SymbolTable(std::string tag = "", std::unordered_map<std::string, Identifier*> map = {}, SymbolTable* prev_table = nullptr) :
            m_tag(tag), m_map(map), m_prev_table(prev_table) {
        }
        ~SymbolTable() {}
        std::string get_tag() {  // 获取当前符号表标识
            return m_tag; 
        }
        std::unordered_map<std::string, Identifier*>* get_map() {  // 获取当前符号表
            return new std::unordered_map<std::string, Identifier*>(m_map);
        }
        SymbolTable* get_prev_table() {  // 获取上一层符号表
            return m_prev_table; 
        }
        bool insert_element(std::string name, Identifier* identifier_ptr) {  // 向表中添加新的键值对
            if (m_map.find(name) != m_map.end()) {  // 表中已有对应标识符名，插入失败
                return false;
            }
            m_map.insert(std::make_pair(name, identifier_ptr));
            return true;
        }
        Identifier* get_identifier_by_name(std::string name) {  // 根据标识符名返回对应标识符的指针
            auto it = m_map.find(name);
            if (it != m_map.end()) {
                return it->second;
            }
            if (m_prev_table != nullptr) {  // 当前层符号表找不到，递归查找上一层
                return m_prev_table->get_identifier_by_name(name);
            }
            return nullptr;
        }
    protected:
        std::string m_tag;  // 用于标识本层符号表(函数/过程名)
        std::unordered_map<std::string, Identifier*> m_map;  // 键为标识符名，值为对应该标识符的指针
        SymbolTable* m_prev_table;  // 指向外层符号表的指针
    };
}
