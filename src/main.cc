// 程序入口
#include "pascal_types.h"
#include "pascal_table.h"
#include "pascal_ast.h"
#include "parser.tab.h"

extern FILE* yyin;  // Flex的输入

int main(int argc, char** argv) {
	pascals::pascal_types_init();  // 全局变量初始化
	std::string pascal_file_name = argv[2];  // 读取pascal文件名
	size_t dot_pos = pascal_file_name.find_last_of('.');
	std::string c_file_name = pascal_file_name.substr(0, dot_pos) + ".c";  // 对应的c文件名

	yyin = std::fopen(pascal_file_name.c_str(), "r");  // 打开pascal文件，并作为Flex输入
	FILE* output_file = std::fopen(c_file_name.c_str(), "w");  // 创建.c文件

	
	pascals::ast::AST ast;  // 创建语法树
	// yyparse(&ast);  // 调用Bison语法分析接口，生成ast
	ast.Format(output_file);  // ast格式化输出到.c文件

	std::fclose(yyin);  // 关闭.pas文件
	std::fclose(output_file);  // 关闭.c文件
	return 0;
}
