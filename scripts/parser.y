%{
#include <memory>
#include"parser.h"
using namespace pascals;
using namespace pascals::ast;//在ast.h里定义
using std::string;//方便字符串操作
extern "C"			
{					
    void yyerror(const char *s);//错误处理函数
    extern int yylex(void);//获得token类型
    extern int line_count;//当前解析到的行号
    extern bool new_line_flag;/是否遇到换行符，辅助行计数
    extern int yyleng;//当前token长度
    extern int last_line_count;//上一个token行号，便于处理错误
}//方便c++调用词法语法分析程序

extern std::string cur_line_info;
extern std::string last_line_info;
extern int lex_error_flag;
int semantic_error_flag = 0;
std::stack<std::unique_ptr<SymbolTable>> symbol_table_queue;  // 符号表栈改用 unique_ptr
int _ = (log_set_level(LOG_INFO), 0);
auto top_table_set = std::make_shared<SymbolTable>("main", nullptr);  // 自动管理内存
int error_flag = 0;
char location_pointer[256];

void yyerror(std::unique_ptr<AST>& real_ast, const char *msg);
void yyerror_var(std::unique_ptr<AST>& real_ast, int line);
void yynote(std::string msg, int line);
void semantic_error(std::unique_ptr<AST>& real_ast, std::string msg, int line, int row) {
    semantic_error_flag = 1;
    real_ast->set_root(nullptr);  // 假设 set_root 能接受 nullptr
    if (row)
        fprintf(stderr, "%d,%d:\033[01;31m \terror\033[0m : %s\n", line, row, msg.c_str());
    else
        fprintf(stderr, "%d:\033[01;31m \terror\033[0m : %s\n", line, msg.c_str());
}
//错误处理部分

%}

%union
{}/*作用：定义 语义值（semantic value） 的联合类型（union），用于存储不同语法规则对应的值。
这里为空：说明语义值可能通过外部方式（如 %parse-param）传递，而不是通过 YYSTYPE（默认的 %union 类型）。*/

%parse-param {pascals::ast::AST *real_ast}//传递参数，生成语法树
%start programstruct//起始符号

%token PROGRAM FUNCTION PROCEDURE TO DOWNTO 
%token ARRAY TYPE CONST RECORD
%token IF THEN ELSE CASE OF WHILE DO FOR REPEAT UNTIL BEGIN_ END
%token ADDOP NOT PLUS UMINUS CONSTASSIGNOP  
%token<token_info> ID CHAR INT_NUM REAL_NUM BASIC_TYPE RELOP MULOP STRING_ VAR SUBCATALOG
%token<token_info> ASSIGNOP WRITE WRITELN SEP READ READLN TRUE FALSE ';'
//词法单元声明

%type<id_list_node_info> idlist
%type<value_node_info> const_value num
%type<periods_node_info> periods
%type<period_node_info> period
%type<type_node_info> type
%type<var_declaration_node_info> var_declaration  //
%type<basic_type_node_info> basic_type
%type<formal_parameter_node_info> formal_parameter
%type<parameter_lists_node_info> parameters
%type<parameter_list_node_info> parameter
%type<var_parameter_node_info> var_parameter
%type<value_parameter_node_info> value_parameter
%type<variable_node_info> variable
%type<variable_list_node_info> variable_list
%type<expression_node_info> expression
%type<simple_expression_node_info> simple_expression
%type<term_node_info> term
%type<factor_node_info> factor
%type<id_varpart_node_info> id_varpart
%type<expression_list_node_info> expression_list
%type<program_head_node> program_head
%type<program_body_node> program_body
%type<const_declarations_node> const_declarations
%type<const_declaration_node> const_declaration
%type<var_declarations_node> var_declarations //
%type<subprogram_declarations_node> subprogram_declarations
%type<subprogram_node> subprogram
%type<subprogram_head_node> subprogram_head
%type<subprogram_body_node> subprogram_body
%type<compound_statement_node> compound_statement
%type<statement_list_node> statement_list
%type<statement_node> statement
%type<else_node> else_part
%type<procedure_call_node> procedure_call
//语法规则的结点类型
%%

programstruct : 
   program_head  ';'program_body '.'
    {   
        // program -> program_head  ';'program_body '.'
        auto node = std::make_shared<ProgramNode>();
        node->append_child(std::move($1)); // head
        node->append_child(std::move($2)); // body

        if((!error_flag) && (!semantic_error_flag) && (!lex_error_flag)){
            real_ast->set_root(std::move(node));
            real_ast->set_valid(true);
        }
    };
program_head :
    PROGRAM ID '(' idlist ')' {
        if(error_flag) YYABORT;
        
        // 构建AST节点
        auto head_node = std::make_shared<ProgramHeadNode>();
        head_node->append_child(std::make_shared<LeafNode>($2.value));
        
        // 直接操作top_table_set
        auto& current_table = *top_table_set;
        
        // 注册标准I/O函数
        const std::vector<std::string> io_funcs = {"write", , "read"};
        for (const auto& name : io_funcs) {
            current_table.insert_element(name,
                std::make_shared<FunctionIdentifier>(name, TYPE_NONE, 0, {}));
        }
        
        // 转移所有权到栈
        symbol_table_queue.push(std::move(top_table_set));
        
        $$ = std::move(head_node);
    }
    | PROGRAM ID {
    // program_head -> PROGRAM ID 
    if(error_flag)
        YYABORT;
        
    auto head_node = std::make_shared<ProgramHeadNode>();
    auto leaf_node = std::make_shared<LeafNode>($2.value);
    head_node->append_child(std::move(leaf_node));
    
    // 直接操作top_table_set
    auto& current_table = *top_table_set;
    
    // 注册标准I/O函数
    const std::vector<std::string> io_funcs = {"write", "read"};
    for (const auto& name : io_funcs) {
        current_table.insert_element(name,
            std::make_shared<FunctionIdentifier>(name, TYPE_NONE, 0, {}));
    }
    
    // 转移所有权到栈
    symbol_table_queue.push(std::move(top_table_set));
    
    $$ = std::move(head_node);
};
program_body :
    const_declarations var_declarations subprogram_declarations compound_statement {
        // program_body -> const_declarations var_declarations subprogram_declarations compound_statement
        if(error_flag)
            YYABORT;
            
        auto body_node = std::make_shared<ProgramBodyNode>();
        body_node->append_child(std::move($1));//const_declarations
        body_node->append_child(std::move($2));//var_declarations
        body_node->append_child(std::move($3));//subprogram_declarations
        body_node->append_child(std::move($4));//compound_statement
        
        $$ = std::move(body_node);
    };
idlist :
    ID {
        // idlist -> ID
        $$.id_name_list = std::make_shared<std::vector<std::pair<std::string, int>>>();//创建
        $$.id_name_list->push_back(std::make_pair($1.value.get<string>(), $1.column_num));
        
        if(error_flag)
            YYABORT;
            
        $$.idlist_node = std::make_shared<IdListNode>(IdListNode::GrammarType::SINGLE_ID);
        auto leaf_node = std::make_shared<LeafNode>($1.value);
        $$.idlist_node->append_child(std::move(leaf_node));
    };
    | idlist ',' ID { 
        // idlist -> idlist ',' ID
        $1.id_name_list->push_back(std::make_pair($3.value.get<string>(), $3.column_num));//引用前一个标识符列表
        $$.id_name_list = std::move($1.id_name_list);//添加当前标识符
        $$.idlist_node = std::make_shared<IdListNode>(IdListNode::GrammarType::MULTIPLE_ID);
        
        if(error_flag)
            YYABORT;
            
        auto leaf_node = std::make_shared<LeafNode>($3.value);
        $$.idlist_node->append_child(std::move($1.idlist_node));
        $$.idlist_node->append_child(std::move(leaf_node));
    }; 

const_declarations :
    {
        // const_declarations -> empty
        if(error_flag)
            YYABORT;
        $$ = std::make_shared<ConstDeclarationsNode>();
    }
    | CONST const_declaration ';'
    {   
        // const_declarations -> CONST const_declaration ';'
        if(error_flag)
            YYABORT;
            
        $$ = std::make_shared<ConstDeclarationsNode>(); 
        $$->append_child(std::move($2));
    };

const_declaration :
    ID '=' const_value
    {
        // 错误检查（使用token_info访问行号）
        if(error_flag || !$3.const_variable_node) {
            YYABORT;
        }

        // 1. 获取符号表和常量名（通过token_info访问）
        auto current_table = symbol_table_queue.top();
        std::string const_name = $1.value.get<std::string>();

        // 2. 创建常量标识符
        auto const_identifier = std::make_shared<pascals::ConstIdentifier>(
            const_name,
            $3.value,  // 直接访问ValueInfo的value
            $1..line_num  // 必须通过token_info访问
        );

        // 3. 插入符号表
        if(!current_table->insert_element(const_name, const_identifier)) {
            semantic_error(real_ast, 
                "redefinition of '" + const_name + "'",
                $1.line_num,  // 必须通过token_info
                $1.column_num
            );
            YYABORT;
        }

        // 4. 构建AST节点（注意$$的类型是const_declaration_node）
        $$ = std::make_shared<pascals::ast::ConstDeclarationNode>(
            pascals::ast::ConstDeclarationNode::GrammarType::VALUE,
            $3.type  // 直接访问ValueInfo的type
        );

        // 5. 添加子节点
        $$->append_child(
            std::make_shared<pascals::ast::LeafNode>($1.value)
        );
        $$->append_child(
            $3.const_variable_node  // 直接访问ValueInfo的节点
        );
    }
    |
    const_declaration ';' ID '=' const_value
    {
        // 错误检查
        if(error_flag || !$5.const_variable_node) {
            YYABORT;
        }

        // 1. 获取当前符号表和常量名
        auto current_table = symbol_table_queue.top();
        std::string const_name = $3.value.get<std::string>();

        // 2. 创建常量标识符（使用shared_ptr）
        auto const_fier = std::make_shared<pascals::ConstIdentifier>(
            const_name,
            $5.value,  // 来自const_value的value
            $3.line_num
        );

        // 3. 尝试插入符号表
        if(!current_table->insert_element(const_name, const_identifier)) {
            semantic_error(real_ast, 
                "redefinition of '" + const_name + "'",
                $3.line_num,
                $3.column_num
            );
            YYABORT;
        }

        // 4. 构建AST节点
        $$ = std::make_shared<pascals::ast::ConstDeclarationNode>(
            pascals::ast::ConstDeclarationNode::GrammarType::DECLARATION,
            $5.type  // 使用shared_ptr<BasicType>
        );

        // 5. 添加子节点
        if ($1) {
            $$->append_child($1);
        }
        $$->append_child(
            std::make_shared<pascals::ast::LeafNode>($3.value)
        );
        $$->append_child($5.const_variable_node);
    }


const_value : 
    PLUS num
    {  
        // 处理正号数值
        $$.type = $2.type;  // 使用shared_ptr<BasicType>
        $$.value = $2.value;
        if(error_flag)
            YYABORT;
        $$.const_variable_node = std::make_shared<pascals::ast::LeafNode>($2.value);
    }
    | UMINUS num
    {  
        // 处理负号数值
        $$.type = $2.type;
        
        // 类型安全的取负操作
        if ($2.type == TYPE_INTEGER) {
            $$.value = ConstValue(-$2.value.get<int>());
        } else  ($2.type == TYPE_REAL) {
            $$.value = ConstValue(-$2.value.get<float>());
        } 
        if(error_flag)
            YYABORT;
        $$.const_variable_node = std::make_shared<pascals::ast::LeafNode>($$.value);
    }
    | num
    {   
        // 处理无符号数值
        $$.type = $1.type;
        $$.value = $1.value;
        if(error_flag)
            YYABORT;
        $$.const_variable_node = std::make_shared<pascals::ast::LeafNode>($1.value);
    }
    | CHAR
    {
        // 处理字符字面量
        $$.type = TYPE_CHAR;
        $$.value = $1.value;  // 通过token_info访问
        if(error_flag)
            YYABORT;
        $$.const_variable_node = std::make_shared<pascals::ast::LeafNode>($1.value);
    };

num :
    INT_NUM
    {
        // num -> INT_NUM
        $$.type = TYPE_INT;
        $$.value = $1.value;
    }
    | REAL_NUM
    {   
        // num -> REAL_NUM
        $$.type = TYPE_REAL;
        $$.value = $1.value;
    };

var_declarations : 
    {
        // var_declarations -> empty
        if(error_flag)
            YYABORT;
        $$ = std::make_shared<VarDeclarationsNode>();
    }
    | VAR var_declaration ';'
    {
        // var_declarations -> VAR var_declaration ';'
        if(error_flag)
            YYABORT;
            
        // 使用智能指针管理 Identifier
        for (auto& i : *($2.record_info)){
            int line = $2.pos_info->find(i.first)->second.first;
            int row = $2.pos_info->find(i.first)->second.second;
            
            // 创建新的变量标识符（保持原有变量名i）
            auto var_identifier = std::make_shared<Identifier>(
                i.first, 
                i.second,  
                line    // 声明行号
            );
            
            // 插入符号表
            if(!symbol_table_queue.top()->insert_element(i.first, var_identifier)){
                semantic_error(real_ast, "redefinition of '"+ i.first +"'", line, row);
                // 获取之前定义（保持原有SearchEntry调用方式）
                auto prev_def = symbol_table_queue.top()->get_identifier_by_name(i.first);
                yynote(i.first, prev_def->get_declare_line());
            }
        }
        
        $$ = std::make_shared<VarDeclarationsNode>();
        $$->append_child(std::move($2.variable_declaration_node));
    };

var_declaration :
    idlist ':' type 
    {
        // var_declaration -> idlist ':' type
        if(error_flag)
            YYABORT;
        
        // 保持原有record_info和pos_info声明方式
        $$.record_info = std::make_shared<std::unordered_map<std::string, std::shared_ptr<TypeTemplate>>>();
        $$.pos_info = std::make_shared<std::unordered_map<std::string, std::pair<int,int>>>();
        
        // 保持原有循环结构
        for (auto& i : *($1.id_name_list)){
            // 插入类型信息（使用shared_ptr）
            auto res = $$.record_info->insert({i.first, $3.type});
            $$.pos_info->insert({i.first, {line_count, i.second}});
            
            if (!res.second){
                semantic_error(real_ast, "redefinition of '"+ i.first +"'", line_count, i.second);
            }
        }
        
        // 保持原有节点创建方式
        $$.variable_declaration_node = std::make_shared<VariableDeclarationNode>(
            VariableDeclarationNode::GrammarType::SINGLE_DECL, 
            VariableDeclarationNode::ListType::TYPE
        );
        $$.variable_declaration_node->append_child(std::move($1.idlist_node));
        $$.variable_declaration_node->append_child(std::move($3.type_node));
    }
    | var_declaration ';' idlist ':' type 
    {
        // var_declaration -> var_declaration ';' idlist ':' type
        if(error_flag)
            YYABORT;
        
        // 保持原有信息转移方式
        $$.record_info = std::move($1.record_info);
        $$.pos_info = std::move($1.pos_info);
        
        // 保持原有循环结构
        for (auto& i : *($3.id_name_list)){
            auto res = $$.record_info->insert({i.first, $5.type});
            $$.pos_info->insert({i.first, {line_count, i.second}});
            
            if (!res.second){
                semantic_error(real_ast, "redefinition of '"+ i.first +"'", line_count, i.second);
            }
        }
        
        // 保持原有节点创建方式
        $$.variable_declaration_node = std::make_shared<VariableDeclarationNode>(
            VariableDeclarationNode::GrammarType::MULTIPLE_DECL, 
            VariableDeclarationNode::ListType::TYPE
        );
        $$.variable_declaration_node->append_child(std::move($1.variable_declaration_node));
        $$.variable_declaration_node->append_child(std::move($3.idlist_node));
        $$.variable_declaration_node->append_child(std::move($5.type_node));
    };
    


type :
    basic_type
    {
        // type -> basic_type (保持所有原始操作)
        $$.main_type = (TypeAttr::MainType)0;
        $$.type = $1.type;
        if(error_flag)
            break;
        $$.type_node = std::make_shared<TypeNode>(TypeNode::GrammarType::BASIC_TYPE);
        $$.base_type_node = $$.type_node;                        
        $$.type_node->set_base_type_node($$.type_node);         
        $$.type_node->append_child($1);
    }
    | ARRAY '[' periods ']' OF type
    {
        // type -> ARRAY [...] OF type (保持所有原始操作)
        $$.main_type = (TypeAttr::MainType)1;
        $$.base_type_node = $6.base_type_node;
        $$.bounds = $3.bounds;
        if ($3.bounds){
            auto merged_bounds = std::make_shared<std::vector<ArrayType::ArrayBound>>();
            for (auto i : *($3.bounds)){
                merged_bounds->push_back(i);
            }
            auto basic_type = $6.type;
            if($6.type->template_type() == TypeTemplate::TYPE::ARRAY) {
                for (auto i : *($6.bounds)){
                    merged_bounds->push_back(i);
                    $$.bounds->push_back(i);  
                }
                basic_type = std::dynamic_pointer_cast<ArrayType>($6.type)->base_type();
            }
            $$.type = std::make_shared<ArrayType>(basic_type, *merged_bounds);
        }
        if(error_flag)
            break; 
        $$.type_node = std::make_shared<TypeNode>(TypeNode::GrammarType::ARRAY);
        $$.type_node->set_base_type_node($6.base_type_node);  // 保持方法调用
        $$.type_node->append_child($3.periods_node);
        $$.type_node->append_child($6.type_node);
    };

basic_type :
    BASIC_TYPE
    {
        // basic_type -> BASIC_TYPE (保持所有原始操作)
        string typestr = $1.value.get<string>();
        if (typestr == "integer"){
            $$.type = TYPE_INT;
        } else if(typestr == "real"){
            $$.type = TYPE_REAL;
        } else if(typestr == "boolean"){
            $$.type = TYPE_BOOL;
        } else{
            $$.type = TYPE_CHAR;
        }
        if(error_flag)
            break;
        $$. = std::make_shared<BasicTypeNode>();
        $$->set_type(std::dynamic_pointer_cast<BasicType>($$.type));
    };

periods :
    periods ',' period
    {
        // periods -> periods ',' period
        $$.bounds = $1.bounds; // 共享指针
        $$.bounds->push_back(*($3.bound));
        
        if(error_flag) YYABORT;
        
        $$.periods_node = std::make_shared<PeriodsNode>();
        $$.periods_node->append_child($1.periods_node);
        $$.periods_node->append_child($3.period_node);
    }
    | period
    {
        // periods -> period
        $$.bounds = std::make_shared<std::vector<ArrayType::ArrayBound>>();
        $$.bounds->push_back(*($1.bound));
        
        if(error_flag) YYABORT;
        
        $$.periods_node = std::make_shared<PeriodsNode>();
        $$.periods_node->append_child($1.period_node);
    };

period :
    const_value SUBCATALOG const_value
    {     
        // period -> const_value SUBCATALOG const_value
        $$.bound = std::make_shared<ArrayType::ArrayBound>();
        int arr_len = 0;
        
        // 类型检查
        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
            arr_len = $3.value.get<int>() - $1.value.get<int>();
            $$.bound->type_ = TYPE_INT;
            $$.bound->lb_ = $1.value.get<int>();
            $$.bound->ub_ = $3.value.get<int>();
        } 
        else if ($1.type == TYPE_CHAR && $3.type == TYPE_CHAR) {
            arr_len = static_cast<int>($3.value.get<char>() - $1.value.get<char>());
            $$.bound->type_ = TYPE_CHAR;
            $$.bound->lb_ = static_cast<int>($1.value.get<char>());
            $$.bound->ub_ = static_cast<int>($3.value.get<char>());
        } 
        else {
            semantic_error(real_ast, "array bound should be integer or char", 
                          $2.line_num, $2.column_num);
            YYABORT;
        }

        // 边界检查
        if (arr_len < 0) {
            semantic_error(real_ast, "array upper bound must >= lower bound",
                          $2.line_num, $2.column_num);
            arr_len = 0; // 容错处理
        }

        $$.period_node = std::make_shared<PeriodNode>();
        $$.period_node->set_len(arr_len + 1);
        $$.period_node->append_child($1.const_variable_node);
        $$.period_node->append_child($3.const_variable_node);
    };






subprogram_declarations : 
    {
        // subprogram_declarations -> empty
        if(error_flag)
            YYABORT;
        $$.subprogram_declarations_node = std::make_shared<SubprogramDeclarationsNode>();
    }
    | subprogram_declarations subprogram ';'
    {
        // subprogram_declarations -> subprogram_declarations subprogram ';'
        if(error_flag)
            YYABORT;
        
        // 创建新节点（使用智能指针）
        $$.subprogram_declarations_node = std::make_shared<SubprogramDeclarationsNode>();
        $$.subprogram_declarations_node->append_child($1.subprogram_declarations_node);
        $$.subprogram_declarations_node->append_child($2);
        
        // 符号表处理（自动管理内存）
        symbol_table_queue.pop(); // shared_ptr会自动释放
    };
subprogram :
    subprogram_head ';' subprogram_body
    {
        // subprogram -> subprogram_head ';' subprogram_body
        if(error_flag)
            YYABORT;
        
        // 1. 创建子程序节点
        $$ = std::make_shared<SubprogramDeclarationNode>();
        $$->append_child($1);
        $$->append_child($3);
        
        // 2. 弹出当前子程序的符号表（退出作用域）
        if(!symbol_table_queue.empty()) {
            symbol_table_queue.pop(); // 自动释放shared_ptr
        } else {
            semantic_error(real_ast, "symbol table stack underflow", @1.first_line, @1.first_column);
        }
    };

subprogram_body :
    const_declarations var_declarations compound_statement
    {
        // subprogram_body -> const_declarations var_declarations compound_statement
        if(error_flag)
            YYABORT;
            
        // 创建子程序体节点
        $$ = std::make_shared<SubprogramBodyNode>();
        $$->append_child($1.const_declarations_node);
        $$->append_child($2);
        $$->append_child($3);
        
     
    };
subprogram_head :
    FUNCTION ID formal_parameter ':' basic_type 
    {
        // subprogram_head -> FUNCTION ID formal_parameter ':' basic_type
        std::shared_ptr<FunctionIdentifier> tmp;
        const std::string func_name = $2.value.get<std::string>();
        const int decl_line = $2.line_num;

        // 创建函数符号
        if($3.parameters){
            tmp = std::make_shared<FunctionIdentifier>(
                func_name, 
                $5.type,
                decl_line,
                *($3.parameters)
            );
        } else {
            tmp = std::make_shared<FunctionIdentifier>(
                func_name,
                $5.type,
                decl_line
            );
        }

        // 检查重复定义
        if (auto existing = symbol_table_queue.top()->get_identifier_by_name(func_name)) {
            semantic_error(real_ast,"redefinition of function '"+func_name+"'",
                         $2.line_num,$2.column_num);
            yynote(func_name, existing->get_declare_line());
            YYABORT;
        }

        // 创建新符号表
        auto now_table_set = std::make_shared<SymbolTable>(
            func_name, 
            symbol_table_queue.top()
        );
        symbol_table_queue.push(now_table_set);

        // 注册函数和返回标识符
        auto tmp2 = std::make_shared<FunctionIdentifier>(*tmp);
        std::string tag = func_name;
        auto tmp3 = std::make_shared<Identifier>(
            "__"+tag+"__", 
            $5.type,
            decl_line
        );
        
        symbol_table_queue.top()->insert_element(tag, tmp2);
        symbol_table_queue.top()->insert_element("__"+tag+"__", tmp3);

        // 处理参数
        if ($3.parameters){
            int cnt = 0;
            for (auto& param : *($3.parameters)){
                auto param_symbol = std::make_shared<Identifier>(
                    param.param_name,
                    param.param_type,
                    param.is_reference,
                    decl_line
                );
                
                if(!symbol_table_queue.top()->insert_element(param.param_name, param_symbol)){
                    const auto& pos = $3.pos_info->at(cnt);
                    semantic_error(real_ast,"redefinition of '"+param.param_name+"'",
                                  pos.first, pos.second);
                    yynote(param.param_name, 
                          symbol_table_queue.top()->get_identifier_by_name(param.param_name)->get_declare_line());
                }
                cnt++;
            }
        }

        if(error_flag) YYABORT;

        // 构建AST节点
        $$ = std::make_shared<SubprogramHeadNode>(
            SubprogramHeadNode::GrammarType::FUNCTION
        );
        $$->append_child(
            std::make_shared<LeafNode>($2.value)
        );
        $$->append_child($3.formal_parameter_node);
        $$->append_child($5);
    }
    |
    PROCEDURE ID formal_parameter 
    {
        // subprogram_head -> PROCEDURE ID formal_parameter 
        if(error_flag)
            YYABORT;

        std::shared_ptr<FunctionIdentifier> tmp;
        const std::string proc_name = $2.value.get<std::string>();
        const int decl_line = $2.line_num;

        // 创建过程符号（适配新Parameter结构）
        if($3.parameters){
            tmp = std::make_shared<FunctionIdentifier>(
                proc_name, 
                nullptr,  // 过程无返回值类型
                decl_line,
                *($3.parameters)  // 直接传递参数列表
            );
        } else {
            tmp = std::make_shared<FunctionIdentifier>(
                proc_name,
                nullptr,
                decl_line
            );
        }

        // 检查重复定义（保持原错误处理逻辑）
        if (auto existing = symbol_table_queue.top()->get_identifier_by_name(proc_name)) {
            semantic_error(real_ast, "redefinition of procedure '" + proc_name + "'",
                         $2.line_num, $2.column_num);
            yynote(proc_name, existing->get_declare_line());
            YYABORT;
        }

        // 创建新作用域符号表
        auto now_table_set = std::make_shared<SymbolTable>(
            proc_name,
            symbol_table_queue.top()
        );
        symbol_table_queue.push(now_table_set);

        // 注册过程符号到当前符号表
        symbol_table_queue.top()->insert_element(proc_name, tmp);

        // 处理参数（适配新Parameter结构）
        if ($3.parameters){
            int cnt = 0;
            for (const auto& param : *($3.parameters)){  // 使用新结构体字段
                auto param_symbol = std::make_shared<Identifier>(
                    param.param_name,       // 使用结构体字段
                    param.param_type,       // 直接获取类型指针
                    decl_line,
                    param.is_reference      // 直接获取引用标志
                );
                
                // 插入参数符号
                if(!symbol_table_queue.top()->insert_element(param.param_name, param_symbol)){
                    const auto& pos = $3.pos_info->at(cnt);  // 保持位置信息获取方式
                    semantic_error(real_ast, "redefinition of parameter '" + param.param_name + "'",
                                  pos.first, pos.second);
                    yynote(param.param_name, 
                          symbol_table_queue.top()->get_identifier_by_name(param.param_name)->get_declare_line());
                }
                cnt++;
            }
        }

        // 构建AST节点（保持原结构）
        $$ = std::make_shared<SubprogramHeadNode>(
            SubprogramHeadNode::GrammarType::PROCEDURE
        );
        $$->append_child(
            std::make_shared<LeafNode>($2.value)
        );
        $$->append_child($3.formal_parameter_node);
    };

formal_parameter :
    {   
        // formal_parameter -> empty
        $$.parameters = std::make_shared<std::vector<FunctionSymbol::Parameter>>();
        $$.pos_info = std::make_shared<std::vector<std::pair<int,int>>>();
        if(error_flag)
            YYABORT;
        $$.formal_parameter_node = std::make_shared<FormalParamNode>();
    }
    | '(' parameters')'
    {
        // formal_parameter -> '(' parameter ')'
        $$.parameters = $2.parameters;
        $$.pos_info = $2.pos_info;
        if(error_flag)
            YYABORT;
        $$.formal_parameter_node = std::make_shared<FormalParamNode>();
        $$.formal_parameter_node->append_child($2.param_lists_node);
    };


parameters :
    parameters ';' parameter
    {   
        // parameters -> parameters ';' parameter
        $$.parameters = std::move($1.parameters);
        $$.pos_info = std::move($1.pos_info);
        $$.parameters->insert($$.parameters->end(), $3.parameters->begin(), $3.parameters->end());
        $$.pos_info->insert($$.pos_info->end(),$3.pos_info->begin(), $3.pos_info->end());
        if(error_flag)
            YYABORT;
        $$.param_lists_node = std::make_shared<ParamListsNode>(ParamListsNode::GrammarType::MULTIPLE_PARAM_LIST);
        $$.param_lists_node->append_child(std::move($1.param_lists_node));
        $$.param_lists_node->append_child(std::move($3.param_list_node));
    }
    | parameter
    {  
        // parameters -> parameter
        $$.parameters = std::move($1.parameters);
        $$.pos_info = std::move($1.pos_info);
        if(error_flag)
            YYABORT;
        $$.param_lists_node = std::make_shared<ParamListsNode>(ParamListsNode::GrammarType::SINGLE_PARAM_LIST);
        $$.param_lists_node->append_child(std::move($1.param_list_node));
    };

parameter :
    var_parameter
    {   
        // parameters -> var_parameter
        $$.parameters = std::move($1.parameters);
        $$.pos_info = std::move($1.pos_info);
        if(error_flag)
            YYABORT;
        $$.param_list_node = std::make_shared<ParamListNode>();
        $$.param_list_node->append_child(std::move($1.var_parameter_node));
    }
    | value_parameter
    {   
        // parameters -> value_parameter
        $$.parameters = std::move($1.parameters);
        $$.pos_info = std::move($1.pos_info);
        if(error_flag)
            YYABORT;
        $$.param_list_node = std::make_shared<ParamListNode>();
        $$.param_list_node->append_child(std::move($1.value_parameter_node));
    };
var_parameter :
    VAR value_parameter
    {   
        // var_parameter → VAR value_parameter
        auto& params = $2.parameters;  // 直接使用 $2.parameters 访问参数列表
        for (auto& param : *params) {
            param.is_reference = true;  // 标记所有参数为引用传递
        }

        // 传递参数列表和位置信息
        $$.parameters = std::move(params);
        $$.pos_info = std::move($2.pos_info);  // 假设位置信息字段名为 pos_info

        // 构建 AST 节点
        $$.var_parameter_node = std::make_shared<pascals::ast::VarParameterNode>();
        $$.var_parameter_node->append_child($2.value_parameter_node);  // 直接添加子节点

        if (error_flag) YYABORT;
    };

value_parameter :
    idlist ':' basic_type
    {   
        // value_parameter → idlist ':' basic_type
        $$.parameters = std::make_shared<std::vector<FunctionIdentifier::Parameter>>();
        $$.pos_info = std::make_shared<std::vector<std::pair<int, int>>>();
        
        // 遍历标识符列表，构造参数对象
        for (const auto& id_pair : *($1.id_name_list)) {
            FunctionIdentifier::Parameter param;
            param.param_name = id_pair.first;                   // 参数名
            param.param_type = $3.type;                     // 参数类型（来自 basic_type）
            param.is_reference = false;                         // 值参数，标记为非引用
            $$.parameters->push_back(param);
            
            // 记录位置信息
            $$.pos_info->push_back(std::make_pair(yylineno, id_pair.second));
        }
        
        // 构建AST节点
        $$.value_parameter_node = std::make_shared<pascals::ast::ValueParameterNode>();
        $$.value_parameter_node->append_child($1.id_list_node);  // 添加 idlist 节点
        $$.value_parameter_node->append_child($3); // 添加 basic_type 节点
        
        if (error_flag) YYABORT;
    };



compound_statement :
    BEGIN_ statement_list END 
    {
        // compound_statement -> BEGIN_ statement_list END
        if(error_flag)
            YYABORT;
        $$ = std::make_shared<CompoundStatementNode>();
        $$->append_child(std::move($2));
    };

statement_list :
    statement_list ';' statement
    {
        // statement_list -> statement_list ';' statement
        if(error_flag)
            YYABORT;
        $$ = std::make_shared<StatementListNode>();
        $$->append_child(std::move($1));
        $$->append_child(std::move($3));
    } 
    | statement
    {
        // statement_list -> statement
        if(error_flag)
            YYABORT;
        $$ = std::make_shared<StatementListNode>();
        $$->append_child(std::move($1));
    };

statement:
    variable ASSIGNOP expression
    {   
        // statement → variable ASSIGNOP expression
        if (error_flag) YYABORT;

        // 获取变量和表达式的类型指针
        auto var_type = $1.type;
        auto expr_type = $3.type;
        bool type_compatible = false;
        bool string_compatible = false;

        // 基础类型兼容性检查（如 real ← int）
        if (auto var_basic = std::dynamic_pointer_cast<BasicType>(var_type)) {
            if (auto expr_basic = std::dynamic_pointer_cast<BasicType>(expr_type)) {
                // 允许 real ← int，其他类型需严格匹配
                if (var_basic->get_basic_type() == BasicType::BASIC_TYPE::REAL &&
                    expr_basic->get_basic_type() == BasicType::BASIC_TYPE::INTEGER) {
                    type_compatible = true;
                } else if (var_basic->get_basic_type() == expr_basic->get_basic_type()) {
                    type_compatible = true;
                }
            }
        }

        // 字符串兼容性检查（如 char[] ← string）
        if (!type_compatible) {
            if (auto var_array = std::dynamic_pointer_cast<ArrayType>(var_type)) {
                if (var_array->get_element_type()->get_basic_type() == BasicType::BASIC_TYPE::CHAR &&
                    expr_type == TYPE_STRING) {
                    string_compatible = true;
                }
            }
        }

        // 类型不兼容报错
        if (!type_compatible && !string_compatible) {
            std::string tn1 = var_type->get_pascal_name();
            std::string tn2 = expr_type->get_pascal_name();
            semantic_error(@$, "Incompatible types: cannot assign '" + tn2 + "' to '" + tn1 + "'");
            YYABORT;
        }


        // 构建AST节点
        $$ = std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::VAR_ASSIGN_OP_EXP
        );
        $$->append_child($1.variable_node);
        $$->append_child($3.expression_node);
    }
    | procedure_call
    {
        $$ = std::move($1);
    }
    | compound_statement
    {
        $$ = std::move($1);
    }
    | 
    IF expression THEN statement else_part
    {   
        // IF expression THEN statement else_part
        if (error_flag) YYABORT;

        // 类型检查：表达式必须为布尔类型
        auto expr_type = std::dynamic_pointer_cast<BasicType>($2.type);
        if (!expr_type || expr_type->get_basic_type() != BasicType::BASIC_TYPE::BOOLEAN) {
            std::string tn = $2.type->get_pascal_name();
            semantic_error(@$, "IF condition cannot be of type '" + tn + "', expected boolean");
            YYABORT;
        }

        // 构建AST节点
        $$ = std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::IF_STATEMENT
        );
        $$->append_child($2.expression_node);  // 条件表达式
        $$->append_child($4);   // THEN语句
        $$->append_child($5);        // ELSE部分
    }
    | FOR ID ASSIGNOP expression TO expression DO statement
    {
        // FOR ID ASSIGNOP expression updown expression DO statement
        if (error_flag) YYABORT;

        // 符号表查找：检查循环变量是否声明
        std::string var_name = $2.value.get<std::string>();
        auto identifier = symbol_table_queue.top()->SearchEntry<Identifier>(var_name);
        if (!identifier) {
            semantic_error(@2, "'" + var_name + "' is undeclared");
            YYABORT;
        }

        // 类型检查1：循环变量必须是基本类型
        auto var_type = std::dynamic_pointer_cast<BasicType>(identifier->get_value_type());
        if (!var_type) {
            semantic_error(@2, "Loop variable must be of basic type");
            YYABORT;
        }

        // 类型检查2：初始值和终止值必须与变量类型兼容
        auto init_type = std::dynamic_pointer_cast<BasicType>($4.type);
        auto end_type = std::dynamic_pointer_cast<BasicType>($6.type);
        if (!init_type || !end_type || 
            var_type->get_basic_type() != init_type->get_basic_type() || 
            init_type->get_basic_type() != end_type->get_basic_type()) {
            std::string tn_var = var_type->get_pascal_name();
            std::string tn_init = init_type ? init_type->get_pascal_name() : "unknown";
            std::string tn_end = end_type ? end_type->get_pascal_name() : "unknown";
            semantic_error(@4, "Incompatible types in FOR loop: variable '" + tn_var + 
                              "', initial '" + tn_init + "', end '" + tn_end + "'");
            YYABORT;
        }

        // 类型检查3：禁止实数类型循环变量
        if (var_type->get_basic_type() == BasicType::BASIC_TYPE::REAL) {
            semantic_error(@2, "FOR loop variable cannot be of type 'real'");
            YYABORT;
        }

        // 构建AST节点
        $$ = std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::FOR_STATEMENT
        );
        $$->append_child(std::make_shared<pascals::ast::LeafNode>($2.value));  // 循环变量
        $$->append_child($4.expression_node);   // 初始值
        $$->append_child($6.expression_node);   // 终止值
        $$->append_child($8);    // 循环体
    }  
    | 
    {
        // EPSILON产生式
        if (error_flag) YYABORT;
        $$ = std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::EPSILON
        );
    };
    |
    READ '(' variable_list ')'
    { 
        // READ '(' variable_list ')'
        if (error_flag) YYABORT;

        // 类型检查：变量列表中的每个变量必须是基础类型或字符数组
        for (const auto& type : *$3.type_list) {
            bool valid = false;
            if (auto basic_type = std::dynamic_pointer_cast<BasicType>(type)) {
                valid = true;  // 基础类型合法
            } else if (auto array_type = std::dynamic_pointer_cast<ArrayType>(type)) {
                // 检查是否为字符数组（字符串）
                if (auto elem_type = std::dynamic_pointer_cast<BasicType>(array_type->get_element_type())) {
                    valid = (elem_type->get_basic_type() == BasicType::BASIC_TYPE::CHAR);
                }
            }

            if (!valid) {
                std::string tn = type->get_pascal_name();
                semantic_error(@3, "READ statement requires basic type or char array, got '" + tn + "'");
                YYABORT;
            }
        }
        // 构建AST节点
        $$= std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::READ_STATEMENT
        );
        $$->append_child($3.variable_list_node);
    }
    | WRITE '(' expression_list ')'
    { 
        // WRITE '(' expression_list ')'
        if (error_flag) YYABORT;

        // 类型检查：表达式必须是基础类型或字符串
        for (const auto& type : *$3.type_list) {
            bool valid = false;
            if (auto basic_type = std::dynamic_pointer_cast<BasicType>(type)) {
                valid = true;  // 基础类型合法
            } else if (type == TYPE_STRING) {
                valid = true;  // 字符串类型合法
            }

            if (!valid) {
                std::string tn = type->get_pascal_name();
                semantic_error(@3, "WRITE statement requires basic type or string, got '" + tn + "'");
                YYABORT;
            }
        }
        // 构建AST节点
        $$= std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::WRITE_STATEMENT
        );
        $$->append_child($3.expression_list_node);
    };

procedure_call:
    ID '(' expression_list ')'
    {
        // procedure_call → ID '(' expression_list ')'
        if (error_flag) YYABORT;

        // 1. 符号表查找
        std::string proc_name = $1.value.get<std::string>();
        auto identifier = symbol_table_queue.top()->get_identifier_by_name(proc_name);

        // 检查是否为函数/过程标识符
        auto procedure = std::dynamic_pointer_cast<FunctionIdentifier>(identifier);
        if (!procedure) {
            semantic_error(@1, "Undefined procedure '" + proc_name + "'");
            YYABORT;
        }

        // 2. 参数个数检查
        if (procedure->get_param_count() != $3.type_list->size()) {
            semantic_error(@3, "Argument count mismatch for procedure '" + proc_name + 
                              "', expected " + std::to_string(procedure->get_param_count()) + 
                              ", got " + std::to_string($3.type_list->size()));
            YYABORT;
        }

        // 3. 参数类型和引用模式检查
        bool params_valid = true;
        std::string expected_params, actual_params;
        for (size_t i = 0; i < $3.type_list->size(); ++i) {
            auto param_info = procedure->get_param_at(i);
            
            // 类型检查
            if (!is_same(param_info->param_type, (*$3.type_list)[i])) {
                params_valid = false;
            }
            
            // 引用模式检查
            if (param_info->is_reference && !(*$3.is_lvalue_list)[i]) {
                semantic_error(@3, "Non-lvalue passed to reference parameter " + 
                                  std::to_string(i+1) + " of procedure '" + proc_name + "'");
                params_valid = false;
            }
            
            // 收集类型信息用于错误报告
            expected_params += (i > 0 ? ", " : "") + param_info->param_type->get_pascal_name();
            actual_params += (i > 0 ? ", " : "") + (*$3.type_list)[i]->get_pascal_name();
        }

        if (!params_valid) {
            semantic_error(@3, "Parameter type mismatch for procedure '" + proc_name + 
                              "', expected (" + expected_params + "), got (" + actual_params + ")");
            YYABORT;
        }

        // 构建AST节点
        $$ = std::make_shared<pascals::ast::ProcedureCallNode>(
            pascals::ast::ProcedureCallNode::GrammarType::ID_EXP_LIST
        );
        $$->append_child(std::make_shared<pascals::ast::LeafNode>($1.value));
        $$->append_child($3.expression_list_node);
    }
    | ID
    {   
        // procedure_call → ID
        if (error_flag) YYABORT;

        std::string proc_name = $1.value.get<std::string>();
        auto identifier = symbol_table_queue.top()->get_identifier_by_name(proc_name);

        // 1. 检查是否为函数/过程标识符
        auto procedure = std::dynamic_pointer_cast<FunctionIdentifier>(identifier);
        if (!procedure) {
            semantic_error(@1, "Undefined procedure '" + proc_name + "'");
            YYABORT;
        }

        // 2. 检查参数个数是否为0
        if (procedure->get_param_count() != 0) {
            semantic_error(@1, "Procedure '" + proc_name + "' expects " + 
                              std::to_string(procedure->get_param_count()) + " arguments, but none given");
            YYABORT;
        }

        // 构建AST节点
        $$ = std::make_shared<pascals::ast::ProcedureCallNode>(
            pascals::ast::ProcedureCallNode::GrammarType::ID
        );
        $$->append_child(std::make_shared<pascals::ast::LeafNode>($1.value));
    };


variable_list :
    variable
    { 
        // variable_list -> variable
        $$.type_list = std::make_shared<std::vector<TypeTemplate*>>();
        $$.type_list->push_back($1.type);
        if(error_flag)
            YYABORT;
        $$.variable_list_node = std::make_shared<VariableListNode>(VariableListNode::GrammarType::VARIABLE);
        $$.variable_list_node->append_child(std::move($1.variable_node));
    } 
    | variable_list ',' variable
    {
        // variable_list -> variable_list ',' variable
        $$.type_list = std::move($1.type_list);
        $$.type_list->push_back($3.type);
        if(error_flag)
            YYABORT;
        $$.variable_list_node = std::make_shared<VariableListNode>(VariableListNode::GrammarType::VARIABLE_LIST_VARIABLE);
        $$.variable_list_node->append_child(std::move($1.variable_list_node));
        $$.variable_list_node->append_child(std::move($3.variable_node));
    };

variable:
    ID id_varpart
    {
        // variable → ID id_varpart
        if (error_flag) YYABORT;

        // 符号表查找
        std::string var_name = $1.value.get<std::string>();
        auto identifier = symbol_table_queue.top()->get_identifier_by_name(var_name);
        $$.type = TYPE_ERROR;  // 全局错误类型
        $$.is_lvalue = true;

        // 1. 检查标识符是否存在
        if (!identifier) {
            semantic_error(@1, "'" + var_name + "' is undeclared");
            YYABORT;
        }

        // 2. 检查标识符类型
        if (auto const_identifier = std::dynamic_pointer_cast<ConstIdentifier>(identifier)) {
            // 常量不可修改
            $$.is_lvalue = false;
            $$.type = const_identifier->get_value_type();
        } 
        else if (auto func_identifier = std::dynamic_pointer_cast<FunctionIdentifier>(identifier)) {
            // 函数名作为右值处理
            $$.is_lvalue = false;
            semantic_error(@1, "Function name '" + var_name + "' cannot be used as variable");
            YYABORT;
        } 
        else {
            // 变量或参数
            auto var_identifier = std::dynamic_pointer_cast<VarIdentifier>(identifier);
            $$.type = var_identifier->get_value_type();

            // 处理数组/记录的访问部分
            if (auto array_type = std::dynamic_pointer_cast<ArrayType>($$.type)) {
                // 传递数组边界信息到 id_varpart 节点
                auto bounds = array_type->get_bounds();
                $2.id_varpart_node->set_bounds(bounds);
            }

            // 执行访问检查（例如数组下标或记录字段）
            $$.type = $2.access_check($$.type);
            if (!$$.type) {
                std::string tn = $$.type->get_pascal_name();
                semantic_error(@2, "Invalid access on type '" + tn + "'");
                YYABORT;
            }

            // 处理引用类型
            if (var_identifier->is_reference()) {
                $$.is_ref = true;  // 标记为引用类型
            }
        }

        // 构建AST节点
        $$.variable_node = std::make_shared<pascals::ast::VariableNode>();
        $$.variable_node->append_child(std::make_shared<pascals::ast::LeafNode>(var_name));
        $$.variable_node->append_child($2.id_varpart_node);
    };


id_varpart:
    {
        // id_varpart -> empty.
        if(error_flag)
            YYABORT;
        $$.var_parts = std::make_shared<std::vector<VarParts>>();
        $$.id_varparts_node = std::make_shared<IDVarPartsNode>();
    }
    | '[' expression_list ']'
    {   
        // id_varpart -> [expression_list].
        $$.var_part = std::make_shared<VarParts>();
        $$.var_part->flag = 0;//数组
        $$.var_part->subscript = std::move($2.type_list);
        if(error_flag)
            YYABORT;
        $$.id_varpart_node = std::make_shared<IDVarPartNode>(IDVarPartNode::GrammarType::EXP_LIST);
        $$.id_varpart_node->append_child(std::move($2.expression_list_node));
    };

else_part:
    {
        // else_part -> empty.
        if(error_flag)
            YYABORT;
        $$ = std::make_shared<ElseNode>(ElseNode::GrammarType::EPSILON);
    }
    | ELSE statement
    {
        // else_part -> ELSE statement.
        if(error_flag)
            YYABORT;
        $$ = std::make_shared<ElseNode>(ElseNode::GrammarType::ELSE_STATEMENT);
        $$->append_child(std::move($2));
    } ;



   
expression_list:
    expression_list ',' expression
    {
        // expression_list -> expression_list ',' expression
        $$.type_list = std::move($1.type_list);
        $$.type_list->push_back($3.type);
        $$.is_lvalue_list = std::move($1.is_lvalue_list);
        $$.is_lvalue_list->push_back($3.is_lvalue);
        if(error_flag)
            YYABORT;
        $$.expression_list_node = std::make_shared<ExpressionListNode>((ExpressionListNode::GrammarType)1);
        $$.expression_list_node->append_child(std::move($1.expression_list_node));
        $$.expression_list_node->append_child(std::move($3.expression_node));
    }
    | expression
    {
        // expression_list -> expression
        $$.type_list = std::make_shared<std::vector<TypeTemplate*>>();
        $$.type_list->push_back($1.type);
        $$.is_lvalue_list = std::make_shared<std::vector<bool>>();
        $$.is_lvalue_list->push_back($1.is_lvalue);
        if(error_flag)
            YYABORT;
        $$.expression_list_node = std::make_shared<ExpressionListNode>((ExpressionListNode::GrammarType)0);
        $$.expression_list_node->append_child(std::move($1.expression_node));
    };

expression:
    simple_expression RELOP simple_expression
    {
        // expression → simple_expression RELOP simple_expression
        if (error_flag) YYABORT;

        // 类型检查：操作数必须为基础类型
        auto type1 = std::dynamic_pointer_cast<BasicType>($1.type);
        auto type2 = std::dynamic_pointer_cast<BasicType>($3.type);
        if (!type1 || !type2) {
            std::string tn1 = $1.type->get_pascal_name();
            std::string tn2 = $3.type->get_pascal_name();
            std::string op = $2.value.get<std::string>();
            semantic_error(@$, "Invalid operands to binary operator '" + op + 
                              "', types '" + tn1 + "' and '" + tn2 + "' are not basic types");
            YYABORT;
        }

        // 计算运算结果类型
        auto result_type = compute(type1, type2, $2.value.get<std::string>());
        if (result_type == TYPE_ERROR) {
            std::string tn1 = type1->get_pascal_name();
            std::string tn2 = type2->get_pascal_name();
            std::string op = $2.value.get<std::string>();
            semantic_error(@$, "Invalid operands to binary operator '" + op + 
                              "' (have '" + tn1 + "' and '" + tn2 + "')");
            YYABORT;
        }

        // 构建AST节点
        $$.expression_node = std::make_shared<pascals::ast::ExpressionNode>();
        $$.type = result_type;
        $$.is_lvalue = false;

        // 处理运算符符号（例如将 '<>' 转换为 '!='）
        std::string relop = $2.value.get<std::string>();
        if (relop == "<>") relop = "!=";

        auto relop_node = std::make_shared<pascals::ast::LeafNode>(ConstValue(relop));
        $$.expression_node->append_child($1.simple_expression_node);
        $$.expression_node->append_child(relop_node);
        $$.expression_node->append_child($3.simple_expression_node);
    }
    | simple_expression
    {
        // expression → simple_expression
        $$.type = $1.type;
        $$.is_lvalue = $1.is_lvalue;

        if (error_flag) YYABORT;

        // 处理数组类型标记
        if (auto array_type = std::dynamic_pointer_cast<ArrayType>($$.type)) {
            $$.expression_node = std::make_shared<pascals::ast::ExpressionNode>(
                pascals::ast::ExpressionNode::TargetType::VAR_ARRAY
            );
        } else {
            $$.expression_node = std::make_shared<pascals::ast::ExpressionNode>();
        }

        $$.expression_node->append_child($1.simple_expression_node);
    };

simple_expression:
    term
    {   
        // simple_expression -> term.
        $$.type = $1.type;
        $$.is_lvalue = $1.is_lvalue;
        if(error_flag)
            YYABORT;
        $$.simple_expression_node = std::make_shared<SimpleExpressionNode>();
        $$.simple_expression_node->append_child(std::move($1.term_node));
    }
    | simple_expression ADDOP term
    {
        // simple_expression -> simple_expression or term.、
        //类型检查
        if($1.type!=$3.type){
            string tn1 = type_name($1.type);
            string tn2 = type_name($3.type);
            semantic_error(real_ast,"invalid operands to binary or (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        $$.is_lvalue = false;
        $$.type = $1.type;

        if(error_flag)
            YYABORT;
        $$.simple_expression_node = std::make_shared<SimpleExpressionNode>();
        auto addop_node = std::make_shared<LeafNode>(ConstValue("||"));
        $$.simple_expression_node->append_child(std::move($1.simple_expression_node));
        $$.simple_expression_node->append_child(std::move(addop_node));
        $$.simple_expression_node->append_child(std::move($3.term_node));
    };

term:
    factor
    {   
        // term → factor
        $$.type = $1.type;
        $$.is_lvalue = $1.is_lvalue;
        if (error_flag) YYABORT;
        
        $$.term_node = std::make_shared<pascals::ast::TermNode>();
        $$.term_node->append_child($1.factor_node);
    }
    | term MULOP factor
    {  
        // term → term MULOP factor
        if (error_flag) YYABORT;

        // 类型检查：操作数必须为基础类型
        auto type1 = std::dynamic_pointer_cast<BasicType>($1.type);
        auto type2 = std::dynamic_pointer_cast<BasicType>($3.type);
        if (!type1 || !type2) {
            std::string tn1 = $1.type->get_pascal_name();
            std::string tn2 = $3.type->get_pascal_name();
            std::string op = $2.value.get<std::string>();
            semantic_error(@$, "Invalid operands to binary operator '" + op + 
                              "', types '" + tn1 + "' and '" + tn2 + "' are not basic types");
            YYABORT;
        }

        // 计算运算结果类型
        auto result_type = compute(type1, type2, $2.value.get<std::string>());
        if (result_type == TYPE_ERROR) {
            std::string tn1 = type1->get_pascal_name();
            std::string tn2 = type2->get_pascal_name();
            std::string op = $2.value.get<std::string>();
            semantic_error(@$, "Invalid operands to binary operator '" + op + 
                              "' (have '" + tn1 + "' and '" + tn2 + "')");
            YYABORT;
        }

        // 运算符转换逻辑
        std::string mulop = $2.value.get<std::string>();
        if (mulop == "div") {
            mulop = "/";  // 整数除法
            
        } else if (mulop == "mod") {
            mulop = "%";  // 取模运算
            
        }
         else if (mulop == "and") {
            mulop = "&&"; // 逻辑与
        }

        // 设置除法标记（用于代码生成阶段区分浮点/整数除法）
        if (mulop == "/" && type1->get_basic_type() == BasicType::BASIC_TYPE::REAL) {
            $1.term_node->set_op_div(true);
        }

        // 构建AST节点
        $$.term_node = std::make_shared<pascals::ast::TermNode>();
        auto mulop_node = std::make_shared<pascals::ast::LeafNode>(ConstValue(mulop));
        $$.term_node->append_child($1.term_node);
        $$.term_node->append_child(mulop_node);
        $$.term_node->append_child($3.factor_node);
        $$.type = result_type;
        $$.is_lvalue = false;
    };

factor:
    num
    {
        $$.type = $1.type;
        if(error_flag)
            YYABORT;
        auto num_node = std::make_shared<LeafNode>($1.value);
        $$.factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::NUM);
        $$.factor_node->append_child(std::move(num_node));
    }
    | variable
    {   
        // factor -> variable.
        $$.type = $1.type;
        $$.is_lvalue = $1.is_lvalue;
        if(error_flag)
            YYABORT;
        $$.factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::VARIABLE);
        $$.factor_node->append_child(std::move($1.variable_node));
    }
    |ID '(' expression_list ')'
    {
        if(error_flag)
            YYABORT;

        // 1. 符号表查找
        std::string func_name = $1.value.get<std::string>();
        auto symbol_table = symbol_table_queue.top();
        auto identifier = symbol_table->get_identifier_by_name(func_name);

        // 检查是否为函数标识符
        auto func = std::dynamic_pointer_cast<pascals::FunctionIdentifier>(identifier);
        if (!func) {
            std::string error_msg = "undefined function '" + func_name + "'";
            semantic_error(real_ast, error_msg, $1.line_num, $1.column_num);
            YYABORT;
        }

        // 2. 参数个数检查
        if (func->get_param_count() != $3.type_ptr_list->size()) {
            std::string error_msg = "Argument count mismatch for function '" + func_name + 
                                    "', expected " + std::to_string(func->get_param_count()) + 
                                    ", got " + std::to_string($3.type_ptr_list->size());
            semantic_error(real_ast, error_msg, line_count, 0);
            YYABORT;
        }

        // 3. 参数类型和引用模式检查
        bool params_valid = true;
        std::string expected_params, actual_params;
        for (size_t i = 0; i < $3.type_ptr_list->size(); ++i) {
            auto param_info = func->get_param_at(i);
            
            // 类型检查
            if (!is_same(param_info->param_type.get(), (*$3.type_ptr_list)[i])) {
                params_valid = false;
            }
            
            // 引用模式检查
            if (param_info->is_reference && !(*$3.is_lvalue_list)[i]) {
                std::string error_msg = "Non-lvalue passed to reference parameter " + 
                                        std::to_string(i+1) + " of function '" + func_name + "'";
                semantic_error(real_ast, error_msg, line_count, 0);
                params_valid = false;
            }
            
            // 收集类型信息用于错误报告
            expected_params += (i > 0 ? ", " : "") + param_info->param_type->name();
            actual_params += (i > 0 ? ", " : "") + (*$3.type_ptr_list)[i]->name();
        }

        if (!params_valid) {
            std::string error_msg = "Parameter type mismatch for function '" + func_name + 
                                    "', expected (" + expected_params + "), got (" + actual_params + ")";
            semantic_error(real_ast, error_msg, line_count, 0);
            YYABORT;
        }

        // 构建AST节点
        $$.is_lvalue = false;
        $$.type = func->get_value_type().get();
        $$.factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::ID_EXP_LIST);
        auto id_node = std::make_shared<pascals::ast::LeafNode>($1.value);
        $$.factor_node->append_child(std::move(id_node));
        $$.factor_node->append_child($3.expression_list_node);

        // 设置引用信息
        auto ref_vec = func->ParamRefVec();
        auto ref_stack = std::make_shared<std::stack<bool>>();
        for (auto i : ref_vec){
            ref_stack->push(i);
        }
        $3.expression_list_node->set_ref(ref_stack.get());

    }
    | '(' expression ')'
    {
        // factor -> (expression).
        $$.type = $2.type;
        $$.is_lvalue = false;
        if(error_flag)
            YYABORT;
        $$.factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::EXP);
        $$.factor_node->append_child(std::move($2.expression_node));
    }
    | NOT factor
    {   
        // factor -> not factor.
        // 类型检查
        if(!is_basic($2.type)){
            semantic_error(real_ast,"wrong type argument to unary not",line_count,0);
            YYABORT;
        }
        auto result=compute((BasicType*)$2.type, "not");
        
        if(result==TYPE_ERROR){
            semantic_error(real_ast,"wrong type argument to unary not",line_count,0);
            YYABORT;
        }
        $$.is_lvalue = false;
        $$.type = result;

        if(error_flag)
            YYABORT;
        $$.factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::NOT);
        $$.factor_node->append_child(std::move($2.factor_node));
    }
    |UMINUS factor
    {   
        
        $$.type = $2.type;
        $$.is_lvalue = false;
        if(error_flag)
            YYABORT;
        $$.factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::UMINUS);
        $$.factor_node->append_child(std::move($2.factor_node));
    };
%%
 

void yyerror(ast::AST* real_ast,const char *msg){
    if(yydebug || strcmp(msg,"syntax error")!=0)   // 当非debug模式且传入的是默认报错时不输出 
        fprintf(stderr,"%d,%ld:\033[01;31m \terror\033[0m : %s\n", line_count,cur_line_info.size(),msg);   
    error_flag = 1;
    real_ast->set_root(nullptr);
}

void yynote(std::string msg ,int line){
    fprintf(stderr,"%d:\033[01;32m \tnote\033[0m : previous definition of \"%s\" was here\n", line, msg.c_str());
}

void yyerror_var(AST* real_ast,int line){
    fprintf(stderr,"%d:\033[01;31m \terror\033[0m : %s\n", line, "redifinition of variable");
    error_flag = 1;
    real_ast->set_root(nullptr);
}

void location_pointer_refresh(){
    int length = cur_line_info.size()-yyleng;
    if(length<0)
        length=0;
    memset(location_pointer,' ',length);
    memcpy(location_pointer+length,"^\n\0",3);
}
int yywrap(){
    return 1;
}
