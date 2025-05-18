
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

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



/* Line 189 of yacc.c  */
#line 115 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     FUNCTION = 259,
     PROCEDURE = 260,
     TO = 261,
     DOWNTO = 262,
     ARRAY = 263,
     TYPE = 264,
     CONST = 265,
     RECORD = 266,
     IF = 267,
     THEN = 268,
     ELSE = 269,
     CASE = 270,
     OF = 271,
     WHILE = 272,
     DO = 273,
     FOR = 274,
     REPEAT = 275,
     UNTIL = 276,
     BEGIN_ = 277,
     END = 278,
     ADDOP = 279,
     NOT = 280,
     PLUS = 281,
     UMINUS = 282,
     CONSTASSIGNOP = 283,
     ID = 284,
     CHAR = 285,
     INT_NUM = 286,
     REAL_NUM = 287,
     BASIC_TYPE = 288,
     RELOP = 289,
     MULOP = 290,
     STRING_ = 291,
     VAR = 292,
     SUBCATALOG = 293,
     ASSIGNOP = 294,
     WRITE = 295,
     WRITELN = 296,
     SEP = 297,
     READ = 298,
     READLN = 299,
     TRUE = 300,
     FALSE = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 43 "parser.y"



/* Line 214 of yacc.c  */
#line 201 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 226 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   148

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNRULES -- Number of states.  */
#define YYNSTATES  159

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      49,    50,     2,     2,    51,     2,    48,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    47,
       2,    52,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     8,    14,    17,    22,    24,    28,    29,
      33,    37,    43,    46,    49,    51,    53,    55,    57,    58,
      62,    66,    72,    74,    81,    83,    87,    89,    93,    94,
      98,   102,   106,   112,   116,   117,   121,   125,   127,   129,
     131,   134,   138,   142,   146,   148,   152,   154,   156,   162,
     171,   172,   177,   182,   187,   189,   191,   195,   198,   199,
     203,   204,   207,   211,   213,   217,   219,   221,   225,   227,
     231,   233,   235,   240,   244,   247
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    47,    59,    48,    -1,     3,    29,
      49,    60,    50,    -1,     3,    29,    -1,    61,    65,    71,
      80,    -1,    29,    -1,    60,    51,    29,    -1,    -1,    10,
      62,    47,    -1,    29,    52,    63,    -1,    62,    47,    29,
      52,    63,    -1,    26,    64,    -1,    27,    64,    -1,    64,
      -1,    30,    -1,    31,    -1,    32,    -1,    -1,    37,    66,
      47,    -1,    60,    53,    67,    -1,    66,    47,    60,    53,
      67,    -1,    68,    -1,     8,    54,    69,    55,    16,    67,
      -1,    33,    -1,    69,    51,    70,    -1,    70,    -1,    63,
      38,    63,    -1,    -1,    71,    72,    47,    -1,    74,    47,
      73,    -1,    61,    65,    80,    -1,     4,    29,    75,    53,
      68,    -1,     5,    29,    75,    -1,    -1,    49,    76,    50,
      -1,    76,    47,    77,    -1,    77,    -1,    78,    -1,    79,
      -1,    37,    79,    -1,    60,    53,    68,    -1,    22,    81,
      23,    -1,    81,    47,    82,    -1,    82,    -1,    85,    39,
      89,    -1,    83,    -1,    80,    -1,    12,    89,    13,    82,
      87,    -1,    19,    29,    39,    89,     6,    89,    18,    82,
      -1,    -1,    43,    49,    84,    50,    -1,    40,    49,    88,
      50,    -1,    29,    49,    88,    50,    -1,    29,    -1,    85,
      -1,    84,    51,    85,    -1,    29,    86,    -1,    -1,    54,
      88,    55,    -1,    -1,    14,    82,    -1,    88,    51,    89,
      -1,    89,    -1,    90,    34,    90,    -1,    90,    -1,    91,
      -1,    90,    24,    91,    -1,    92,    -1,    91,    35,    92,
      -1,    64,    -1,    85,    -1,    29,    49,    88,    50,    -1,
      49,    89,    50,    -1,    25,    92,    -1,    27,    92,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    95,    95,   108,   130,   155,   169,   181,   196,   202,
     213,   256,   302,   311,   326,   335,   346,   352,   360,   366,
     398,   427,   460,   472,   502,   522,   534,   547,   591,   597,
     612,   632,   647,   732,   810,   818,   831,   844,   856,   866,
     877,   897,   926,   936,   945,   955,  1005,  1009,  1014,  1035,
    1085,  1093,  1122,  1150,  1210,  1241,  1251,  1264,  1327,  1334,
    1347,  1353,  1366,  1379,  1393,  1435,  1456,  1466,  1488,  1498,
    1555,  1564,  1574,  1649,  1659,  1681
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "FUNCTION", "PROCEDURE", "TO",
  "DOWNTO", "ARRAY", "TYPE", "CONST", "RECORD", "IF", "THEN", "ELSE",
  "CASE", "OF", "WHILE", "DO", "FOR", "REPEAT", "UNTIL", "BEGIN_", "END",
  "ADDOP", "NOT", "PLUS", "UMINUS", "CONSTASSIGNOP", "ID", "CHAR",
  "INT_NUM", "REAL_NUM", "BASIC_TYPE", "RELOP", "MULOP", "STRING_", "VAR",
  "SUBCATALOG", "ASSIGNOP", "WRITE", "WRITELN", "SEP", "READ", "READLN",
  "TRUE", "FALSE", "';'", "'.'", "'('", "')'", "','", "'='", "':'", "'['",
  "']'", "$accept", "programstruct", "program_head", "program_body",
  "idlist", "const_declarations", "const_declaration", "const_value",
  "num", "var_declarations", "var_declaration", "type", "basic_type",
  "periods", "period", "subprogram_declarations", "subprogram",
  "subprogram_body", "subprogram_head", "formal_parameter", "parameters",
  "parameter", "var_parameter", "value_parameter", "compound_statement",
  "statement_list", "statement", "procedure_call", "variable_list",
  "variable", "id_varpart", "else_part", "expression_list", "expression",
  "simple_expression", "term", "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,    59,    46,    40,
      41,    44,    61,    58,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    63,    64,    64,    65,    65,
      66,    66,    67,    67,    68,    69,    69,    70,    71,    71,
      72,    73,    74,    74,    75,    75,    76,    76,    77,    77,
      78,    79,    80,    81,    81,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    83,    84,    84,    85,    86,    86,
      87,    87,    88,    88,    89,    89,    90,    90,    91,    91,
      92,    92,    92,    92,    92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     2,     4,     1,     3,     0,     3,
       3,     5,     2,     2,     1,     1,     1,     1,     0,     3,
       3,     5,     1,     6,     1,     3,     1,     3,     0,     3,
       3,     3,     5,     3,     0,     3,     3,     1,     1,     1,
       2,     3,     3,     3,     1,     3,     1,     1,     5,     8,
       0,     4,     4,     4,     1,     1,     3,     2,     0,     3,
       0,     2,     3,     1,     3,     1,     1,     3,     1,     3,
       1,     1,     4,     3,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     4,     1,     8,     0,     0,     0,
      18,     6,     0,     0,     0,     2,     0,    28,     3,     0,
       0,     9,     0,     0,     0,     7,     0,     0,    15,    16,
      17,    10,    14,     0,     0,    19,     0,     0,    50,     0,
       0,     5,    12,    13,     0,     0,    24,    20,    22,     0,
      34,    34,     0,     0,    54,     0,     0,    47,     0,    44,
      46,     0,    29,     8,    11,     0,     0,     0,     0,    33,
       0,     0,    58,     0,    70,    71,     0,    65,    66,    68,
       0,     0,     0,    57,     0,     0,    42,    50,     0,    18,
      30,     0,     0,    26,    21,     0,     0,     0,    37,    38,
      39,     0,    74,    75,     0,     0,    50,     0,     0,     0,
       0,     0,    63,     0,     0,    58,     0,    55,    43,    45,
       0,     0,     0,     0,    40,     0,     0,    35,    32,     0,
      73,    60,    67,    64,    69,     0,    53,     0,    59,    52,
      51,     0,    31,    27,    25,     0,    41,    36,    72,    50,
      48,     0,    62,    56,    23,    61,     0,    50,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,    96,    10,    14,    91,    74,    17,
      23,    47,    48,    92,    93,    24,    39,    90,    40,    68,
      97,    98,    99,   100,    57,    58,    59,    60,   116,    75,
      83,   150,   111,   112,    77,    78,    79
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -81
static const yytype_int16 yypact[] =
{
      10,     7,    51,     9,    14,   -81,    70,    38,    69,    58,
      62,   -81,    35,    55,    61,   -81,    38,   -81,   -81,    80,
      27,    81,    11,    65,    13,   -81,    57,    57,   -81,   -81,
     -81,   -81,   -81,    63,     0,    38,    84,    85,     2,    71,
      73,   -81,   -81,   -81,    27,    67,   -81,   -81,   -81,    22,
      68,    68,    12,    87,    16,    74,    75,   -81,    -7,   -81,
     -81,    83,   -81,    70,   -81,    27,     0,    -9,    72,   -81,
      12,    12,    17,    12,   -81,   -81,   113,    -5,    92,   -81,
      89,    12,    12,   -81,    12,   100,   -81,     2,    12,    62,
     -81,    93,    21,   -81,   -81,    38,    30,    32,   -81,   -81,
     -81,    97,   -81,   -81,    12,    82,     2,    12,    12,    12,
      12,    40,   -81,    23,    42,    79,    44,   -81,   -81,   -81,
     112,    27,    27,   119,   -81,    97,    -9,   -81,   -81,    46,
     -81,   122,    92,   114,   -81,   131,   -81,    12,   -81,   -81,
     -81,   100,   -81,   -81,   -81,     0,   -81,   -81,   -81,     2,
     -81,    12,   -81,   -81,   -81,   -81,   121,     2,   -81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,   -81,   -81,    -1,    77,   -81,   -19,   -17,    52,
     -81,   -61,   -79,   -81,    20,   -81,   -81,   -81,   -81,    94,
     -81,    18,   -81,    48,   -20,   -81,   -80,   -81,   -81,   -38,
     -81,   -81,   -52,   -50,    39,    41,   -59
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -59
static const yytype_int16 yytable[] =
{
      61,    31,    76,    32,    41,    94,    12,   118,    45,    42,
      43,   102,   103,     1,    52,    22,    86,    36,    37,   107,
      11,    53,   128,   105,    38,    64,   131,    32,    95,   108,
     113,    54,   114,    46,    49,    38,     4,    70,   119,    71,
      87,    72,    55,    29,    30,    56,   146,   117,    32,    61,
     134,     5,   129,    26,    27,   -58,     6,    28,    29,    30,
     135,    73,    19,     7,    34,    81,   104,    11,    61,   155,
      82,    82,   122,    19,   137,    66,   123,   158,   138,   126,
       8,    19,   127,   125,   154,    18,    19,   152,    29,    30,
     136,   137,   139,   137,   140,   141,   148,   137,    13,    16,
     142,   156,   143,   153,    32,    32,    15,    20,    21,    25,
      33,    61,    35,    50,    51,    44,    80,    67,    62,    61,
      63,    65,    88,    84,    85,   101,   106,   109,   110,   115,
      46,   121,   130,    82,    38,   145,   149,   151,   107,   157,
      89,   120,   144,   124,   147,    69,     0,   133,   132
};

static const yytype_int16 yycheck[] =
{
      38,    20,    52,    20,    24,    66,     7,    87,     8,    26,
      27,    70,    71,     3,    12,    16,    23,     4,     5,    24,
      29,    19,   101,    73,    22,    44,   106,    44,    37,    34,
      82,    29,    84,    33,    35,    22,    29,    25,    88,    27,
      47,    29,    40,    31,    32,    43,   125,    85,    65,    87,
     109,     0,   104,    26,    27,    39,    47,    30,    31,    32,
     110,    49,    51,    49,    53,    49,    49,    29,   106,   149,
      54,    54,    51,    51,    51,    53,    55,   157,    55,    47,
      10,    51,    50,    53,   145,    50,    51,   137,    31,    32,
      50,    51,    50,    51,    50,    51,    50,    51,    29,    37,
     120,   151,   121,   141,   121,   122,    48,    52,    47,    29,
      29,   149,    47,    29,    29,    52,    29,    49,    47,   157,
      47,    54,    39,    49,    49,    53,    13,    35,    39,    29,
      33,    38,    50,    54,    22,    16,    14,     6,    24,    18,
      63,    89,   122,    95,   126,    51,    -1,   108,   107
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    57,    58,    29,     0,    47,    49,    10,    59,
      61,    29,    60,    29,    62,    48,    37,    65,    50,    51,
      52,    47,    60,    66,    71,    29,    26,    27,    30,    31,
      32,    63,    64,    29,    53,    47,     4,     5,    22,    72,
      74,    80,    64,    64,    52,     8,    33,    67,    68,    60,
      29,    29,    12,    19,    29,    40,    43,    80,    81,    82,
      83,    85,    47,    47,    63,    54,    53,    49,    75,    75,
      25,    27,    29,    49,    64,    85,    89,    90,    91,    92,
      29,    49,    54,    86,    49,    49,    23,    47,    39,    61,
      73,    63,    69,    70,    67,    37,    60,    76,    77,    78,
      79,    53,    92,    92,    49,    89,    13,    24,    34,    35,
      39,    88,    89,    88,    88,    29,    84,    85,    82,    89,
      65,    38,    51,    55,    79,    53,    47,    50,    68,    88,
      50,    82,    91,    90,    92,    89,    50,    51,    55,    50,
      50,    51,    80,    63,    70,    16,    68,    77,    50,    14,
      87,     6,    89,    85,    67,    82,    89,    18,    82
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (real_ast, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, real_ast); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, pascals::ast::AST *real_ast)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, real_ast)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    pascals::ast::AST *real_ast;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (real_ast);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, pascals::ast::AST *real_ast)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, real_ast)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    pascals::ast::AST *real_ast;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, real_ast);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, pascals::ast::AST *real_ast)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, real_ast)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    pascals::ast::AST *real_ast;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , real_ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, real_ast); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, pascals::ast::AST *real_ast)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, real_ast)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    pascals::ast::AST *real_ast;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (real_ast);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (pascals::ast::AST *real_ast);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (pascals::ast::AST *real_ast)
#else
int
yyparse (real_ast)
    pascals::ast::AST *real_ast;
#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    {   
        // program -> program_head  ';'program_body '.'
        auto node = std::make_shared<ProgramNode>();
        node->append_child(std::move((yyvsp[(1) - (4)].program_head_node))); // head
        node->append_child(std::move((yyvsp[(2) - (4)].token_info))); // body

        if((!error_flag) && (!semantic_error_flag) && (!lex_error_flag)){
            real_ast->set_root(std::move(node));
            real_ast->set_valid(true);
        }
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    {
        if(error_flag) YYABORT;
        
        // 构建AST节点
        auto head_node = std::make_shared<ProgramHeadNode>();
        head_node->append_child(std::make_shared<LeafNode>((yyvsp[(2) - (5)].token_info).value));
        
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
        
        (yyval.program_head_node) = std::move(head_node);
    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    {
    // program_head -> PROGRAM ID 
    if(error_flag)
        YYABORT;
        
    auto head_node = std::make_shared<ProgramHeadNode>();
    auto leaf_node = std::make_shared<LeafNode>((yyvsp[(2) - (2)].token_info).value);
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
    
    (yyval.program_head_node) = std::move(head_node);
;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    {
        // program_body -> const_declarations var_declarations subprogram_declarations compound_statement
        if(error_flag)
            YYABORT;
            
        auto body_node = std::make_shared<ProgramBodyNode>();
        body_node->append_child(std::move((yyvsp[(1) - (4)].const_declarations_node)));//const_declarations
        body_node->append_child(std::move((yyvsp[(2) - (4)].var_declarations_node)));//var_declarations
        body_node->append_child(std::move((yyvsp[(3) - (4)].subprogram_declarations_node)));//subprogram_declarations
        body_node->append_child(std::move((yyvsp[(4) - (4)].compound_statement_node)));//compound_statement
        
        (yyval.program_body_node) = std::move(body_node);
    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    {
        // idlist -> ID
        (yyval.id_list_node_info).id_name_list = std::make_shared<std::vector<std::pair<std::string, int>>>();//创建
        (yyval.id_list_node_info).id_name_list->push_back(std::make_pair((yyvsp[(1) - (1)].token_info).value.get<string>(), (yyvsp[(1) - (1)].token_info).column_num));
        
        if(error_flag)
            YYABORT;
            
        (yyval.id_list_node_info).idlist_node = std::make_shared<IdListNode>(IdListNode::GrammarType::SINGLE_ID);
        auto leaf_node = std::make_shared<LeafNode>((yyvsp[(1) - (1)].token_info).value);
        (yyval.id_list_node_info).idlist_node->append_child(std::move(leaf_node));
    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 181 "parser.y"
    { 
        // idlist -> idlist ',' ID
        (yyvsp[(1) - (3)].id_list_node_info).id_name_list->push_back(std::make_pair((yyvsp[(3) - (3)].token_info).value.get<string>(), (yyvsp[(3) - (3)].token_info).column_num));//引用前一个标识符列表
        (yyval.id_list_node_info).id_name_list = std::move((yyvsp[(1) - (3)].id_list_node_info).id_name_list);//添加当前标识符
        (yyval.id_list_node_info).idlist_node = std::make_shared<IdListNode>(IdListNode::GrammarType::MULTIPLE_ID);
        
        if(error_flag)
            YYABORT;
            
        auto leaf_node = std::make_shared<LeafNode>((yyvsp[(3) - (3)].token_info).value);
        (yyval.id_list_node_info).idlist_node->append_child(std::move((yyvsp[(1) - (3)].id_list_node_info).idlist_node));
        (yyval.id_list_node_info).idlist_node->append_child(std::move(leaf_node));
    ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {
        // const_declarations -> empty
        if(error_flag)
            YYABORT;
        (yyval.const_declarations_node) = std::make_shared<ConstDeclarationsNode>();
    ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    {   
        // const_declarations -> CONST const_declaration ';'
        if(error_flag)
            YYABORT;
            
        (yyval.const_declarations_node) = std::make_shared<ConstDeclarationsNode>(); 
        (yyval.const_declarations_node)->append_child(std::move((yyvsp[(2) - (3)].const_declaration_node)));
    ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 214 "parser.y"
    {
        // 错误检查（使用token_info访问行号）
        if(error_flag || !(yyvsp[(3) - (3)].value_node_info).const_variable_node) {
            YYABORT;
        }

        // 1. 获取符号表和常量名（通过token_info访问）
        auto current_table = symbol_table_queue.top();
        std::string const_name = (yyvsp[(1) - (3)].token_info).value.get<std::string>();

        // 2. 创建常量标识符
        auto const_identifier = std::make_shared<pascals::ConstIdentifier>(
            const_name,
            (yyvsp[(3) - (3)].value_node_info).value,  // 直接访问ValueInfo的value
            (yyvsp[(1) - (3)].token_info)..line_num  // 必须通过token_info访问
        );

        // 3. 插入符号表
        if(!current_table->insert_element(const_name, const_identifier)) {
            semantic_error(real_ast, 
                "redefinition of '" + const_name + "'",
                (yyvsp[(1) - (3)].token_info).line_num,  // 必须通过token_info
                (yyvsp[(1) - (3)].token_info).column_num
            );
            YYABORT;
        }

        // 4. 构建AST节点（注意$$的类型是const_declaration_node）
        (yyval.const_declaration_node) = std::make_shared<pascals::ast::ConstDeclarationNode>(
            pascals::ast::ConstDeclarationNode::GrammarType::VALUE,
            (yyvsp[(3) - (3)].value_node_info).type  // 直接访问ValueInfo的type
        );

        // 5. 添加子节点
        (yyval.const_declaration_node)->append_child(
            std::make_shared<pascals::ast::LeafNode>((yyvsp[(1) - (3)].token_info).value)
        );
        (yyval.const_declaration_node)->append_child(
            (yyvsp[(3) - (3)].value_node_info).const_variable_node  // 直接访问ValueInfo的节点
        );
    ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 257 "parser.y"
    {
        // 错误检查
        if(error_flag || !(yyvsp[(5) - (5)].value_node_info).const_variable_node) {
            YYABORT;
        }

        // 1. 获取当前符号表和常量名
        auto current_table = symbol_table_queue.top();
        std::string const_name = (yyvsp[(3) - (5)].token_info).value.get<std::string>();

        // 2. 创建常量标识符（使用shared_ptr）
        auto const_fier = std::make_shared<pascals::ConstIdentifier>(
            const_name,
            (yyvsp[(5) - (5)].value_node_info).value,  // 来自const_value的value
            (yyvsp[(3) - (5)].token_info).line_num
        );

        // 3. 尝试插入符号表
        if(!current_table->insert_element(const_name, const_identifier)) {
            semantic_error(real_ast, 
                "redefinition of '" + const_name + "'",
                (yyvsp[(3) - (5)].token_info).line_num,
                (yyvsp[(3) - (5)].token_info).column_num
            );
            YYABORT;
        }

        // 4. 构建AST节点
        (yyval.const_declaration_node) = std::make_shared<pascals::ast::ConstDeclarationNode>(
            pascals::ast::ConstDeclarationNode::GrammarType::DECLARATION,
            (yyvsp[(5) - (5)].value_node_info).type  // 使用shared_ptr<BasicType>
        );

        // 5. 添加子节点
        if ((yyvsp[(1) - (5)].const_declaration_node)) {
            (yyval.const_declaration_node)->append_child((yyvsp[(1) - (5)].const_declaration_node));
        }
        (yyval.const_declaration_node)->append_child(
            std::make_shared<pascals::ast::LeafNode>((yyvsp[(3) - (5)].token_info).value)
        );
        (yyval.const_declaration_node)->append_child((yyvsp[(5) - (5)].value_node_info).const_variable_node);
    ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 303 "parser.y"
    {  
        // 处理正号数值
        (yyval.value_node_info).type = (yyvsp[(2) - (2)].value_node_info).type;  // 使用shared_ptr<BasicType>
        (yyval.value_node_info).value = (yyvsp[(2) - (2)].value_node_info).value;
        if(error_flag)
            YYABORT;
        (yyval.value_node_info).const_variable_node = std::make_shared<pascals::ast::LeafNode>((yyvsp[(2) - (2)].value_node_info).value);
    ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 312 "parser.y"
    {  
        // 处理负号数值
        (yyval.value_node_info).type = (yyvsp[(2) - (2)].value_node_info).type;
        
        // 类型安全的取负操作
        if ((yyvsp[(2) - (2)].value_node_info).type == TYPE_INTEGER) {
            (yyval.value_node_info).value = ConstValue(-(yyvsp[(2) - (2)].value_node_info).value.get<int>());
        } else  ((yyvsp[(2) - (2)].value_node_info).type == TYPE_REAL) {
            (yyval.value_node_info).value = ConstValue(-(yyvsp[(2) - (2)].value_node_info).value.get<float>());
        } 
        if(error_flag)
            YYABORT;
        (yyval.value_node_info).const_variable_node = std::make_shared<pascals::ast::LeafNode>((yyval.value_node_info).value);
    ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 327 "parser.y"
    {   
        // 处理无符号数值
        (yyval.value_node_info).type = (yyvsp[(1) - (1)].value_node_info).type;
        (yyval.value_node_info).value = (yyvsp[(1) - (1)].value_node_info).value;
        if(error_flag)
            YYABORT;
        (yyval.value_node_info).const_variable_node = std::make_shared<pascals::ast::LeafNode>((yyvsp[(1) - (1)].value_node_info).value);
    ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 336 "parser.y"
    {
        // 处理字符字面量
        (yyval.value_node_info).type = TYPE_CHAR;
        (yyval.value_node_info).value = (yyvsp[(1) - (1)].token_info).value;  // 通过token_info访问
        if(error_flag)
            YYABORT;
        (yyval.value_node_info).const_variable_node = std::make_shared<pascals::ast::LeafNode>((yyvsp[(1) - (1)].token_info).value);
    ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 347 "parser.y"
    {
        // num -> INT_NUM
        (yyval.value_node_info).type = TYPE_INT;
        (yyval.value_node_info).value = (yyvsp[(1) - (1)].token_info).value;
    ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 353 "parser.y"
    {   
        // num -> REAL_NUM
        (yyval.value_node_info).type = TYPE_REAL;
        (yyval.value_node_info).value = (yyvsp[(1) - (1)].token_info).value;
    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    {
        // var_declarations -> empty
        if(error_flag)
            YYABORT;
        (yyval.var_declarations_node) = std::make_shared<VarDeclarationsNode>();
    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 367 "parser.y"
    {
        // var_declarations -> VAR var_declaration ';'
        if(error_flag)
            YYABORT;
            
        // 使用智能指针管理 Identifier
        for (auto& i : *((yyvsp[(2) - (3)].var_declaration_node_info).record_info)){
            int line = (yyvsp[(2) - (3)].var_declaration_node_info).pos_info->find(i.first)->second.first;
            int row = (yyvsp[(2) - (3)].var_declaration_node_info).pos_info->find(i.first)->second.second;
            
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
        
        (yyval.var_declarations_node) = std::make_shared<VarDeclarationsNode>();
        (yyval.var_declarations_node)->append_child(std::move((yyvsp[(2) - (3)].var_declaration_node_info).variable_declaration_node));
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 399 "parser.y"
    {
        // var_declaration -> idlist ':' type
        if(error_flag)
            YYABORT;
        
        // 保持原有record_info和pos_info声明方式
        (yyval.var_declaration_node_info).record_info = std::make_shared<std::unordered_map<std::string, std::shared_ptr<TypeTemplate>>>();
        (yyval.var_declaration_node_info).pos_info = std::make_shared<std::unordered_map<std::string, std::pair<int,int>>>();
        
        // 保持原有循环结构
        for (auto& i : *((yyvsp[(1) - (3)].id_list_node_info).id_name_list)){
            // 插入类型信息（使用shared_ptr）
            auto res = (yyval.var_declaration_node_info).record_info->insert({i.first, (yyvsp[(3) - (3)].type_node_info).type});
            (yyval.var_declaration_node_info).pos_info->insert({i.first, {line_count, i.second}});
            
            if (!res.second){
                semantic_error(real_ast, "redefinition of '"+ i.first +"'", line_count, i.second);
            }
        }
        
        // 保持原有节点创建方式
        (yyval.var_declaration_node_info).variable_declaration_node = std::make_shared<VariableDeclarationNode>(
            VariableDeclarationNode::GrammarType::SINGLE_DECL, 
            VariableDeclarationNode::ListType::TYPE
        );
        (yyval.var_declaration_node_info).variable_declaration_node->append_child(std::move((yyvsp[(1) - (3)].id_list_node_info).idlist_node));
        (yyval.var_declaration_node_info).variable_declaration_node->append_child(std::move((yyvsp[(3) - (3)].type_node_info).type_node));
    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 428 "parser.y"
    {
        // var_declaration -> var_declaration ';' idlist ':' type
        if(error_flag)
            YYABORT;
        
        // 保持原有信息转移方式
        (yyval.var_declaration_node_info).record_info = std::move((yyvsp[(1) - (5)].var_declaration_node_info).record_info);
        (yyval.var_declaration_node_info).pos_info = std::move((yyvsp[(1) - (5)].var_declaration_node_info).pos_info);
        
        // 保持原有循环结构
        for (auto& i : *((yyvsp[(3) - (5)].id_list_node_info).id_name_list)){
            auto res = (yyval.var_declaration_node_info).record_info->insert({i.first, (yyvsp[(5) - (5)].type_node_info).type});
            (yyval.var_declaration_node_info).pos_info->insert({i.first, {line_count, i.second}});
            
            if (!res.second){
                semantic_error(real_ast, "redefinition of '"+ i.first +"'", line_count, i.second);
            }
        }
        
        // 保持原有节点创建方式
        (yyval.var_declaration_node_info).variable_declaration_node = std::make_shared<VariableDeclarationNode>(
            VariableDeclarationNode::GrammarType::MULTIPLE_DECL, 
            VariableDeclarationNode::ListType::TYPE
        );
        (yyval.var_declaration_node_info).variable_declaration_node->append_child(std::move((yyvsp[(1) - (5)].var_declaration_node_info).variable_declaration_node));
        (yyval.var_declaration_node_info).variable_declaration_node->append_child(std::move((yyvsp[(3) - (5)].id_list_node_info).idlist_node));
        (yyval.var_declaration_node_info).variable_declaration_node->append_child(std::move((yyvsp[(5) - (5)].type_node_info).type_node));
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 461 "parser.y"
    {
        // type -> basic_type (保持所有原始操作)
        (yyval.type_node_info).main_type = (TypeAttr::MainType)0;
        (yyval.type_node_info).type = (yyvsp[(1) - (1)].basic_type_node_info).type;
        if(error_flag)
            break;
        (yyval.type_node_info).type_node = std::make_shared<TypeNode>(TypeNode::GrammarType::BASIC_TYPE);
        (yyval.type_node_info).base_type_node = (yyval.type_node_info).type_node;                        
        (yyval.type_node_info).type_node->set_base_type_node((yyval.type_node_info).type_node);         
        (yyval.type_node_info).type_node->append_child((yyvsp[(1) - (1)].basic_type_node_info));
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 473 "parser.y"
    {
        // type -> ARRAY [...] OF type (保持所有原始操作)
        (yyval.type_node_info).main_type = (TypeAttr::MainType)1;
        (yyval.type_node_info).base_type_node = (yyvsp[(6) - (6)].type_node_info).base_type_node;
        (yyval.type_node_info).bounds = (yyvsp[(3) - (6)].periods_node_info).bounds;
        if ((yyvsp[(3) - (6)].periods_node_info).bounds){
            auto merged_bounds = std::make_shared<std::vector<ArrayType::ArrayBound>>();
            for (auto i : *((yyvsp[(3) - (6)].periods_node_info).bounds)){
                merged_bounds->push_back(i);
            }
            auto basic_type = (yyvsp[(6) - (6)].type_node_info).type;
            if((yyvsp[(6) - (6)].type_node_info).type->template_type() == TypeTemplate::TYPE::ARRAY) {
                for (auto i : *((yyvsp[(6) - (6)].type_node_info).bounds)){
                    merged_bounds->push_back(i);
                    (yyval.type_node_info).bounds->push_back(i);  
                }
                basic_type = std::dynamic_pointer_cast<ArrayType>((yyvsp[(6) - (6)].type_node_info).type)->base_type();
            }
            (yyval.type_node_info).type = std::make_shared<ArrayType>(basic_type, *merged_bounds);
        }
        if(error_flag)
            break; 
        (yyval.type_node_info).type_node = std::make_shared<TypeNode>(TypeNode::GrammarType::ARRAY);
        (yyval.type_node_info).type_node->set_base_type_node((yyvsp[(6) - (6)].type_node_info).base_type_node);  // 保持方法调用
        (yyval.type_node_info).type_node->append_child((yyvsp[(3) - (6)].periods_node_info).periods_node);
        (yyval.type_node_info).type_node->append_child((yyvsp[(6) - (6)].type_node_info).type_node);
    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 503 "parser.y"
    {
        // basic_type -> BASIC_TYPE (保持所有原始操作)
        string typestr = (yyvsp[(1) - (1)].token_info).value.get<string>();
        if (typestr == "integer"){
            (yyval.basic_type_node_info).type = TYPE_INT;
        } else if(typestr == "real"){
            (yyval.basic_type_node_info).type = TYPE_REAL;
        } else if(typestr == "boolean"){
            (yyval.basic_type_node_info).type = TYPE_BOOL;
        } else{
            (yyval.basic_type_node_info).type = TYPE_CHAR;
        }
        if(error_flag)
            break;
        (yyval.basic_type_node_info). = std::make_shared<BasicTypeNode>();
        (yyval.basic_type_node_info)->set_type(std::dynamic_pointer_cast<BasicType>((yyval.basic_type_node_info).type));
    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 523 "parser.y"
    {
        // periods -> periods ',' period
        (yyval.periods_node_info).bounds = (yyvsp[(1) - (3)].periods_node_info).bounds; // 共享指针
        (yyval.periods_node_info).bounds->push_back(*((yyvsp[(3) - (3)].period_node_info).bound));
        
        if(error_flag) YYABORT;
        
        (yyval.periods_node_info).periods_node = std::make_shared<PeriodsNode>();
        (yyval.periods_node_info).periods_node->append_child((yyvsp[(1) - (3)].periods_node_info).periods_node);
        (yyval.periods_node_info).periods_node->append_child((yyvsp[(3) - (3)].period_node_info).period_node);
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 535 "parser.y"
    {
        // periods -> period
        (yyval.periods_node_info).bounds = std::make_shared<std::vector<ArrayType::ArrayBound>>();
        (yyval.periods_node_info).bounds->push_back(*((yyvsp[(1) - (1)].period_node_info).bound));
        
        if(error_flag) YYABORT;
        
        (yyval.periods_node_info).periods_node = std::make_shared<PeriodsNode>();
        (yyval.periods_node_info).periods_node->append_child((yyvsp[(1) - (1)].period_node_info).period_node);
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 548 "parser.y"
    {     
        // period -> const_value SUBCATALOG const_value
        (yyval.period_node_info).bound = std::make_shared<ArrayType::ArrayBound>();
        int arr_len = 0;
        
        // 类型检查
        if ((yyvsp[(1) - (3)].value_node_info).type == TYPE_INT && (yyvsp[(3) - (3)].value_node_info).type == TYPE_INT) {
            arr_len = (yyvsp[(3) - (3)].value_node_info).value.get<int>() - (yyvsp[(1) - (3)].value_node_info).value.get<int>();
            (yyval.period_node_info).bound->type_ = TYPE_INT;
            (yyval.period_node_info).bound->lb_ = (yyvsp[(1) - (3)].value_node_info).value.get<int>();
            (yyval.period_node_info).bound->ub_ = (yyvsp[(3) - (3)].value_node_info).value.get<int>();
        } 
        else if ((yyvsp[(1) - (3)].value_node_info).type == TYPE_CHAR && (yyvsp[(3) - (3)].value_node_info).type == TYPE_CHAR) {
            arr_len = static_cast<int>((yyvsp[(3) - (3)].value_node_info).value.get<char>() - (yyvsp[(1) - (3)].value_node_info).value.get<char>());
            (yyval.period_node_info).bound->type_ = TYPE_CHAR;
            (yyval.period_node_info).bound->lb_ = static_cast<int>((yyvsp[(1) - (3)].value_node_info).value.get<char>());
            (yyval.period_node_info).bound->ub_ = static_cast<int>((yyvsp[(3) - (3)].value_node_info).value.get<char>());
        } 
        else {
            semantic_error(real_ast, "array bound should be integer or char", 
                          (yyvsp[(2) - (3)].token_info).line_num, (yyvsp[(2) - (3)].token_info).column_num);
            YYABORT;
        }

        // 边界检查
        if (arr_len < 0) {
            semantic_error(real_ast, "array upper bound must >= lower bound",
                          (yyvsp[(2) - (3)].token_info).line_num, (yyvsp[(2) - (3)].token_info).column_num);
            arr_len = 0; // 容错处理
        }

        (yyval.period_node_info).period_node = std::make_shared<PeriodNode>();
        (yyval.period_node_info).period_node->set_len(arr_len + 1);
        (yyval.period_node_info).period_node->append_child((yyvsp[(1) - (3)].value_node_info).const_variable_node);
        (yyval.period_node_info).period_node->append_child((yyvsp[(3) - (3)].value_node_info).const_variable_node);
    ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 591 "parser.y"
    {
        // subprogram_declarations -> empty
        if(error_flag)
            YYABORT;
        (yyval.subprogram_declarations_node).subprogram_declarations_node = std::make_shared<SubprogramDeclarationsNode>();
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 598 "parser.y"
    {
        // subprogram_declarations -> subprogram_declarations subprogram ';'
        if(error_flag)
            YYABORT;
        
        // 创建新节点（使用智能指针）
        (yyval.subprogram_declarations_node).subprogram_declarations_node = std::make_shared<SubprogramDeclarationsNode>();
        (yyval.subprogram_declarations_node).subprogram_declarations_node->append_child((yyvsp[(1) - (3)].subprogram_declarations_node).subprogram_declarations_node);
        (yyval.subprogram_declarations_node).subprogram_declarations_node->append_child((yyvsp[(2) - (3)].subprogram_node));
        
        // 符号表处理（自动管理内存）
        symbol_table_queue.pop(); // shared_ptr会自动释放
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 613 "parser.y"
    {
        // subprogram -> subprogram_head ';' subprogram_body
        if(error_flag)
            YYABORT;
        
        // 1. 创建子程序节点
        (yyval.subprogram_node) = std::make_shared<SubprogramDeclarationNode>();
        (yyval.subprogram_node)->append_child((yyvsp[(1) - (3)].subprogram_head_node));
        (yyval.subprogram_node)->append_child((yyvsp[(3) - (3)].subprogram_body_node));
        
        // 2. 弹出当前子程序的符号表（退出作用域）
        if(!symbol_table_queue.empty()) {
            symbol_table_queue.pop(); // 自动释放shared_ptr
        } else {
            semantic_error(real_ast, "symbol table stack underflow", (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column);
        }
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 633 "parser.y"
    {
        // subprogram_body -> const_declarations var_declarations compound_statement
        if(error_flag)
            YYABORT;
            
        // 创建子程序体节点
        (yyval.subprogram_body_node) = std::make_shared<SubprogramBodyNode>();
        (yyval.subprogram_body_node)->append_child((yyvsp[(1) - (3)].const_declarations_node).const_declarations_node);
        (yyval.subprogram_body_node)->append_child((yyvsp[(2) - (3)].var_declarations_node));
        (yyval.subprogram_body_node)->append_child((yyvsp[(3) - (3)].compound_statement_node));
        
     
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 648 "parser.y"
    {
        // subprogram_head -> FUNCTION ID formal_parameter ':' basic_type
        std::shared_ptr<FunctionIdentifier> tmp;
        const std::string func_name = (yyvsp[(2) - (5)].token_info).value.get<std::string>();
        const int decl_line = (yyvsp[(2) - (5)].token_info).line_num;

        // 创建函数符号
        if((yyvsp[(3) - (5)].formal_parameter_node_info).parameters){
            tmp = std::make_shared<FunctionIdentifier>(
                func_name, 
                (yyvsp[(5) - (5)].basic_type_node_info).type,
                decl_line,
                *((yyvsp[(3) - (5)].formal_parameter_node_info).parameters)
            );
        } else {
            tmp = std::make_shared<FunctionIdentifier>(
                func_name,
                (yyvsp[(5) - (5)].basic_type_node_info).type,
                decl_line
            );
        }

        // 检查重复定义
        if (auto existing = symbol_table_queue.top()->get_identifier_by_name(func_name)) {
            semantic_error(real_ast,"redefinition of function '"+func_name+"'",
                         (yyvsp[(2) - (5)].token_info).line_num,(yyvsp[(2) - (5)].token_info).column_num);
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
            (yyvsp[(5) - (5)].basic_type_node_info).type,
            decl_line
        );
        
        symbol_table_queue.top()->insert_element(tag, tmp2);
        symbol_table_queue.top()->insert_element("__"+tag+"__", tmp3);

        // 处理参数
        if ((yyvsp[(3) - (5)].formal_parameter_node_info).parameters){
            int cnt = 0;
            for (auto& param : *((yyvsp[(3) - (5)].formal_parameter_node_info).parameters)){
                auto param_symbol = std::make_shared<Identifier>(
                    param.param_name,
                    param.param_type,
                    param.is_reference,
                    decl_line
                );
                
                if(!symbol_table_queue.top()->insert_element(param.param_name, param_symbol)){
                    const auto& pos = (yyvsp[(3) - (5)].formal_parameter_node_info).pos_info->at(cnt);
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
        (yyval.subprogram_head_node) = std::make_shared<SubprogramHeadNode>(
            SubprogramHeadNode::GrammarType::FUNCTION
        );
        (yyval.subprogram_head_node)->append_child(
            std::make_shared<LeafNode>((yyvsp[(2) - (5)].token_info).value)
        );
        (yyval.subprogram_head_node)->append_child((yyvsp[(3) - (5)].formal_parameter_node_info).formal_parameter_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[(5) - (5)].basic_type_node_info));
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 733 "parser.y"
    {
        // subprogram_head -> PROCEDURE ID formal_parameter 
        if(error_flag)
            YYABORT;

        std::shared_ptr<FunctionIdentifier> tmp;
        const std::string proc_name = (yyvsp[(2) - (3)].token_info).value.get<std::string>();
        const int decl_line = (yyvsp[(2) - (3)].token_info).line_num;

        // 创建过程符号（适配新Parameter结构）
        if((yyvsp[(3) - (3)].formal_parameter_node_info).parameters){
            tmp = std::make_shared<FunctionIdentifier>(
                proc_name, 
                nullptr,  // 过程无返回值类型
                decl_line,
                *((yyvsp[(3) - (3)].formal_parameter_node_info).parameters)  // 直接传递参数列表
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
                         (yyvsp[(2) - (3)].token_info).line_num, (yyvsp[(2) - (3)].token_info).column_num);
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
        if ((yyvsp[(3) - (3)].formal_parameter_node_info).parameters){
            int cnt = 0;
            for (const auto& param : *((yyvsp[(3) - (3)].formal_parameter_node_info).parameters)){  // 使用新结构体字段
                auto param_symbol = std::make_shared<Identifier>(
                    param.param_name,       // 使用结构体字段
                    param.param_type,       // 直接获取类型指针
                    decl_line,
                    param.is_reference      // 直接获取引用标志
                );
                
                // 插入参数符号
                if(!symbol_table_queue.top()->insert_element(param.param_name, param_symbol)){
                    const auto& pos = (yyvsp[(3) - (3)].formal_parameter_node_info).pos_info->at(cnt);  // 保持位置信息获取方式
                    semantic_error(real_ast, "redefinition of parameter '" + param.param_name + "'",
                                  pos.first, pos.second);
                    yynote(param.param_name, 
                          symbol_table_queue.top()->get_identifier_by_name(param.param_name)->get_declare_line());
                }
                cnt++;
            }
        }

        // 构建AST节点（保持原结构）
        (yyval.subprogram_head_node) = std::make_shared<SubprogramHeadNode>(
            SubprogramHeadNode::GrammarType::PROCEDURE
        );
        (yyval.subprogram_head_node)->append_child(
            std::make_shared<LeafNode>((yyvsp[(2) - (3)].token_info).value)
        );
        (yyval.subprogram_head_node)->append_child((yyvsp[(3) - (3)].formal_parameter_node_info).formal_parameter_node);
    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 810 "parser.y"
    {   
        // formal_parameter -> empty
        (yyval.formal_parameter_node_info).parameters = std::make_shared<std::vector<FunctionSymbol::Parameter>>();
        (yyval.formal_parameter_node_info).pos_info = std::make_shared<std::vector<std::pair<int,int>>>();
        if(error_flag)
            YYABORT;
        (yyval.formal_parameter_node_info).formal_parameter_node = std::make_shared<FormalParamNode>();
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 819 "parser.y"
    {
        // formal_parameter -> '(' parameter ')'
        (yyval.formal_parameter_node_info).parameters = (yyvsp[(2) - (3)].parameter_lists_node_info).parameters;
        (yyval.formal_parameter_node_info).pos_info = (yyvsp[(2) - (3)].parameter_lists_node_info).pos_info;
        if(error_flag)
            YYABORT;
        (yyval.formal_parameter_node_info).formal_parameter_node = std::make_shared<FormalParamNode>();
        (yyval.formal_parameter_node_info).formal_parameter_node->append_child((yyvsp[(2) - (3)].parameter_lists_node_info).param_lists_node);
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 832 "parser.y"
    {   
        // parameters -> parameters ';' parameter
        (yyval.parameter_lists_node_info).parameters = std::move((yyvsp[(1) - (3)].parameter_lists_node_info).parameters);
        (yyval.parameter_lists_node_info).pos_info = std::move((yyvsp[(1) - (3)].parameter_lists_node_info).pos_info);
        (yyval.parameter_lists_node_info).parameters->insert((yyval.parameter_lists_node_info).parameters->end(), (yyvsp[(3) - (3)].parameter_list_node_info).parameters->begin(), (yyvsp[(3) - (3)].parameter_list_node_info).parameters->end());
        (yyval.parameter_lists_node_info).pos_info->insert((yyval.parameter_lists_node_info).pos_info->end(),(yyvsp[(3) - (3)].parameter_list_node_info).pos_info->begin(), (yyvsp[(3) - (3)].parameter_list_node_info).pos_info->end());
        if(error_flag)
            YYABORT;
        (yyval.parameter_lists_node_info).param_lists_node = std::make_shared<ParamListsNode>(ParamListsNode::GrammarType::MULTIPLE_PARAM_LIST);
        (yyval.parameter_lists_node_info).param_lists_node->append_child(std::move((yyvsp[(1) - (3)].parameter_lists_node_info).param_lists_node));
        (yyval.parameter_lists_node_info).param_lists_node->append_child(std::move((yyvsp[(3) - (3)].parameter_list_node_info).param_list_node));
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 845 "parser.y"
    {  
        // parameters -> parameter
        (yyval.parameter_lists_node_info).parameters = std::move((yyvsp[(1) - (1)].parameter_list_node_info).parameters);
        (yyval.parameter_lists_node_info).pos_info = std::move((yyvsp[(1) - (1)].parameter_list_node_info).pos_info);
        if(error_flag)
            YYABORT;
        (yyval.parameter_lists_node_info).param_lists_node = std::make_shared<ParamListsNode>(ParamListsNode::GrammarType::SINGLE_PARAM_LIST);
        (yyval.parameter_lists_node_info).param_lists_node->append_child(std::move((yyvsp[(1) - (1)].parameter_list_node_info).param_list_node));
    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 857 "parser.y"
    {   
        // parameters -> var_parameter
        (yyval.parameter_list_node_info).parameters = std::move((yyvsp[(1) - (1)].var_parameter_node_info).parameters);
        (yyval.parameter_list_node_info).pos_info = std::move((yyvsp[(1) - (1)].var_parameter_node_info).pos_info);
        if(error_flag)
            YYABORT;
        (yyval.parameter_list_node_info).param_list_node = std::make_shared<ParamListNode>();
        (yyval.parameter_list_node_info).param_list_node->append_child(std::move((yyvsp[(1) - (1)].var_parameter_node_info).var_parameter_node));
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 867 "parser.y"
    {   
        // parameters -> value_parameter
        (yyval.parameter_list_node_info).parameters = std::move((yyvsp[(1) - (1)].value_parameter_node_info).parameters);
        (yyval.parameter_list_node_info).pos_info = std::move((yyvsp[(1) - (1)].value_parameter_node_info).pos_info);
        if(error_flag)
            YYABORT;
        (yyval.parameter_list_node_info).param_list_node = std::make_shared<ParamListNode>();
        (yyval.parameter_list_node_info).param_list_node->append_child(std::move((yyvsp[(1) - (1)].value_parameter_node_info).value_parameter_node));
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 878 "parser.y"
    {   
        // var_parameter → VAR value_parameter
        auto& params = (yyvsp[(2) - (2)].value_parameter_node_info).parameters;  // 直接使用 $2.parameters 访问参数列表
        for (auto& param : *params) {
            param.is_reference = true;  // 标记所有参数为引用传递
        }

        // 传递参数列表和位置信息
        (yyval.var_parameter_node_info).parameters = std::move(params);
        (yyval.var_parameter_node_info).pos_info = std::move((yyvsp[(2) - (2)].value_parameter_node_info).pos_info);  // 假设位置信息字段名为 pos_info

        // 构建 AST 节点
        (yyval.var_parameter_node_info).var_parameter_node = std::make_shared<pascals::ast::VarParameterNode>();
        (yyval.var_parameter_node_info).var_parameter_node->append_child((yyvsp[(2) - (2)].value_parameter_node_info).value_parameter_node);  // 直接添加子节点

        if (error_flag) YYABORT;
    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 898 "parser.y"
    {   
        // value_parameter → idlist ':' basic_type
        (yyval.value_parameter_node_info).parameters = std::make_shared<std::vector<FunctionIdentifier::Parameter>>();
        (yyval.value_parameter_node_info).pos_info = std::make_shared<std::vector<std::pair<int, int>>>();
        
        // 遍历标识符列表，构造参数对象
        for (const auto& id_pair : *((yyvsp[(1) - (3)].id_list_node_info).id_name_list)) {
            FunctionIdentifier::Parameter param;
            param.param_name = id_pair.first;                   // 参数名
            param.param_type = (yyvsp[(3) - (3)].basic_type_node_info).type;                     // 参数类型（来自 basic_type）
            param.is_reference = false;                         // 值参数，标记为非引用
            (yyval.value_parameter_node_info).parameters->push_back(param);
            
            // 记录位置信息
            (yyval.value_parameter_node_info).pos_info->push_back(std::make_pair(yylineno, id_pair.second));
        }
        
        // 构建AST节点
        (yyval.value_parameter_node_info).value_parameter_node = std::make_shared<pascals::ast::ValueParameterNode>();
        (yyval.value_parameter_node_info).value_parameter_node->append_child((yyvsp[(1) - (3)].id_list_node_info).id_list_node);  // 添加 idlist 节点
        (yyval.value_parameter_node_info).value_parameter_node->append_child((yyvsp[(3) - (3)].basic_type_node_info)); // 添加 basic_type 节点
        
        if (error_flag) YYABORT;
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 927 "parser.y"
    {
        // compound_statement -> BEGIN_ statement_list END
        if(error_flag)
            YYABORT;
        (yyval.compound_statement_node) = std::make_shared<CompoundStatementNode>();
        (yyval.compound_statement_node)->append_child(std::move((yyvsp[(2) - (3)].statement_list_node)));
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 937 "parser.y"
    {
        // statement_list -> statement_list ';' statement
        if(error_flag)
            YYABORT;
        (yyval.statement_list_node) = std::make_shared<StatementListNode>();
        (yyval.statement_list_node)->append_child(std::move((yyvsp[(1) - (3)].statement_list_node)));
        (yyval.statement_list_node)->append_child(std::move((yyvsp[(3) - (3)].statement_node)));
    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 946 "parser.y"
    {
        // statement_list -> statement
        if(error_flag)
            YYABORT;
        (yyval.statement_list_node) = std::make_shared<StatementListNode>();
        (yyval.statement_list_node)->append_child(std::move((yyvsp[(1) - (1)].statement_node)));
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 956 "parser.y"
    {   
        // statement → variable ASSIGNOP expression
        if (error_flag) YYABORT;

        // 获取变量和表达式的类型指针
        auto var_type = (yyvsp[(1) - (3)].variable_node_info).type;
        auto expr_type = (yyvsp[(3) - (3)].expression_node_info).type;
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
            semantic_error((yyloc), "Incompatible types: cannot assign '" + tn2 + "' to '" + tn1 + "'");
            YYABORT;
        }


        // 构建AST节点
        (yyval.statement_node) = std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::VAR_ASSIGN_OP_EXP
        );
        (yyval.statement_node)->append_child((yyvsp[(1) - (3)].variable_node_info).variable_node);
        (yyval.statement_node)->append_child((yyvsp[(3) - (3)].expression_node_info).expression_node);
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 1006 "parser.y"
    {
        (yyval.statement_node) = std::move((yyvsp[(1) - (1)].procedure_call_node));
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 1010 "parser.y"
    {
        (yyval.statement_node) = std::move((yyvsp[(1) - (1)].compound_statement_node));
    ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 1015 "parser.y"
    {   
        // IF expression THEN statement else_part
        if (error_flag) YYABORT;

        // 类型检查：表达式必须为布尔类型
        auto expr_type = std::dynamic_pointer_cast<BasicType>((yyvsp[(2) - (5)].expression_node_info).type);
        if (!expr_type || expr_type->get_basic_type() != BasicType::BASIC_TYPE::BOOLEAN) {
            std::string tn = (yyvsp[(2) - (5)].expression_node_info).type->get_pascal_name();
            semantic_error((yyloc), "IF condition cannot be of type '" + tn + "', expected boolean");
            YYABORT;
        }

        // 构建AST节点
        (yyval.statement_node) = std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::IF_STATEMENT
        );
        (yyval.statement_node)->append_child((yyvsp[(2) - (5)].expression_node_info).expression_node);  // 条件表达式
        (yyval.statement_node)->append_child((yyvsp[(4) - (5)].statement_node));   // THEN语句
        (yyval.statement_node)->append_child((yyvsp[(5) - (5)].else_node));        // ELSE部分
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 1036 "parser.y"
    {
        // FOR ID ASSIGNOP expression updown expression DO statement
        if (error_flag) YYABORT;

        // 符号表查找：检查循环变量是否声明
        std::string var_name = (yyvsp[(2) - (8)].token_info).value.get<std::string>();
        auto identifier = symbol_table_queue.top()->SearchEntry<Identifier>(var_name);
        if (!identifier) {
            semantic_error((yylsp[(2) - (8)]), "'" + var_name + "' is undeclared");
            YYABORT;
        }

        // 类型检查1：循环变量必须是基本类型
        auto var_type = std::dynamic_pointer_cast<BasicType>(identifier->get_value_type());
        if (!var_type) {
            semantic_error((yylsp[(2) - (8)]), "Loop variable must be of basic type");
            YYABORT;
        }

        // 类型检查2：初始值和终止值必须与变量类型兼容
        auto init_type = std::dynamic_pointer_cast<BasicType>((yyvsp[(4) - (8)].expression_node_info).type);
        auto end_type = std::dynamic_pointer_cast<BasicType>((yyvsp[(6) - (8)].expression_node_info).type);
        if (!init_type || !end_type || 
            var_type->get_basic_type() != init_type->get_basic_type() || 
            init_type->get_basic_type() != end_type->get_basic_type()) {
            std::string tn_var = var_type->get_pascal_name();
            std::string tn_init = init_type ? init_type->get_pascal_name() : "unknown";
            std::string tn_end = end_type ? end_type->get_pascal_name() : "unknown";
            semantic_error((yylsp[(4) - (8)]), "Incompatible types in FOR loop: variable '" + tn_var + 
                              "', initial '" + tn_init + "', end '" + tn_end + "'");
            YYABORT;
        }

        // 类型检查3：禁止实数类型循环变量
        if (var_type->get_basic_type() == BasicType::BASIC_TYPE::REAL) {
            semantic_error((yylsp[(2) - (8)]), "FOR loop variable cannot be of type 'real'");
            YYABORT;
        }

        // 构建AST节点
        (yyval.statement_node) = std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::FOR_STATEMENT
        );
        (yyval.statement_node)->append_child(std::make_shared<pascals::ast::LeafNode>((yyvsp[(2) - (8)].token_info).value));  // 循环变量
        (yyval.statement_node)->append_child((yyvsp[(4) - (8)].expression_node_info).expression_node);   // 初始值
        (yyval.statement_node)->append_child((yyvsp[(6) - (8)].expression_node_info).expression_node);   // 终止值
        (yyval.statement_node)->append_child((yyvsp[(8) - (8)].statement_node));    // 循环体
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 1085 "parser.y"
    {
        // EPSILON产生式
        if (error_flag) YYABORT;
        (yyval.statement_node) = std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::EPSILON
        );
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 1094 "parser.y"
    { 
        // READ '(' variable_list ')'
        if (error_flag) YYABORT;

        // 类型检查：变量列表中的每个变量必须是基础类型或字符数组
        for (const auto& type : *(yyvsp[(3) - (4)].variable_list_node_info).type_list) {
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
                semantic_error((yylsp[(3) - (4)]), "READ statement requires basic type or char array, got '" + tn + "'");
                YYABORT;
            }
        }
        // 构建AST节点
        (yyval.statement_node)= std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::READ_STATEMENT
        );
        (yyval.statement_node)->append_child((yyvsp[(3) - (4)].variable_list_node_info).variable_list_node);
    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 1123 "parser.y"
    { 
        // WRITE '(' expression_list ')'
        if (error_flag) YYABORT;

        // 类型检查：表达式必须是基础类型或字符串
        for (const auto& type : *(yyvsp[(3) - (4)].expression_list_node_info).type_list) {
            bool valid = false;
            if (auto basic_type = std::dynamic_pointer_cast<BasicType>(type)) {
                valid = true;  // 基础类型合法
            } else if (type == TYPE_STRING) {
                valid = true;  // 字符串类型合法
            }

            if (!valid) {
                std::string tn = type->get_pascal_name();
                semantic_error((yylsp[(3) - (4)]), "WRITE statement requires basic type or string, got '" + tn + "'");
                YYABORT;
            }
        }
        // 构建AST节点
        (yyval.statement_node)= std::make_shared<pascals::ast::StatementNode>(
            pascals::ast::StatementNode::GrammarType::WRITE_STATEMENT
        );
        (yyval.statement_node)->append_child((yyvsp[(3) - (4)].expression_list_node_info).expression_list_node);
    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1151 "parser.y"
    {
        // procedure_call → ID '(' expression_list ')'
        if (error_flag) YYABORT;

        // 1. 符号表查找
        std::string proc_name = (yyvsp[(1) - (4)].token_info).value.get<std::string>();
        auto identifier = symbol_table_queue.top()->get_identifier_by_name(proc_name);

        // 检查是否为函数/过程标识符
        auto procedure = std::dynamic_pointer_cast<FunctionIdentifier>(identifier);
        if (!procedure) {
            semantic_error((yylsp[(1) - (4)]), "Undefined procedure '" + proc_name + "'");
            YYABORT;
        }

        // 2. 参数个数检查
        if (procedure->get_param_count() != (yyvsp[(3) - (4)].expression_list_node_info).type_list->size()) {
            semantic_error((yylsp[(3) - (4)]), "Argument count mismatch for procedure '" + proc_name + 
                              "', expected " + std::to_string(procedure->get_param_count()) + 
                              ", got " + std::to_string((yyvsp[(3) - (4)].expression_list_node_info).type_list->size()));
            YYABORT;
        }

        // 3. 参数类型和引用模式检查
        bool params_valid = true;
        std::string expected_params, actual_params;
        for (size_t i = 0; i < (yyvsp[(3) - (4)].expression_list_node_info).type_list->size(); ++i) {
            auto param_info = procedure->get_param_at(i);
            
            // 类型检查
            if (!is_same(param_info->param_type, (*(yyvsp[(3) - (4)].expression_list_node_info).type_list)[i])) {
                params_valid = false;
            }
            
            // 引用模式检查
            if (param_info->is_reference && !(*(yyvsp[(3) - (4)].expression_list_node_info).is_lvalue_list)[i]) {
                semantic_error((yylsp[(3) - (4)]), "Non-lvalue passed to reference parameter " + 
                                  std::to_string(i+1) + " of procedure '" + proc_name + "'");
                params_valid = false;
            }
            
            // 收集类型信息用于错误报告
            expected_params += (i > 0 ? ", " : "") + param_info->param_type->get_pascal_name();
            actual_params += (i > 0 ? ", " : "") + (*(yyvsp[(3) - (4)].expression_list_node_info).type_list)[i]->get_pascal_name();
        }

        if (!params_valid) {
            semantic_error((yylsp[(3) - (4)]), "Parameter type mismatch for procedure '" + proc_name + 
                              "', expected (" + expected_params + "), got (" + actual_params + ")");
            YYABORT;
        }

        // 构建AST节点
        (yyval.procedure_call_node) = std::make_shared<pascals::ast::ProcedureCallNode>(
            pascals::ast::ProcedureCallNode::GrammarType::ID_EXP_LIST
        );
        (yyval.procedure_call_node)->append_child(std::make_shared<pascals::ast::LeafNode>((yyvsp[(1) - (4)].token_info).value));
        (yyval.procedure_call_node)->append_child((yyvsp[(3) - (4)].expression_list_node_info).expression_list_node);
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1211 "parser.y"
    {   
        // procedure_call → ID
        if (error_flag) YYABORT;

        std::string proc_name = (yyvsp[(1) - (1)].token_info).value.get<std::string>();
        auto identifier = symbol_table_queue.top()->get_identifier_by_name(proc_name);

        // 1. 检查是否为函数/过程标识符
        auto procedure = std::dynamic_pointer_cast<FunctionIdentifier>(identifier);
        if (!procedure) {
            semantic_error((yylsp[(1) - (1)]), "Undefined procedure '" + proc_name + "'");
            YYABORT;
        }

        // 2. 检查参数个数是否为0
        if (procedure->get_param_count() != 0) {
            semantic_error((yylsp[(1) - (1)]), "Procedure '" + proc_name + "' expects " + 
                              std::to_string(procedure->get_param_count()) + " arguments, but none given");
            YYABORT;
        }

        // 构建AST节点
        (yyval.procedure_call_node) = std::make_shared<pascals::ast::ProcedureCallNode>(
            pascals::ast::ProcedureCallNode::GrammarType::ID
        );
        (yyval.procedure_call_node)->append_child(std::make_shared<pascals::ast::LeafNode>((yyvsp[(1) - (1)].token_info).value));
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 1242 "parser.y"
    { 
        // variable_list -> variable
        (yyval.variable_list_node_info).type_list = std::make_shared<std::vector<TypeTemplate*>>();
        (yyval.variable_list_node_info).type_list->push_back((yyvsp[(1) - (1)].variable_node_info).type);
        if(error_flag)
            YYABORT;
        (yyval.variable_list_node_info).variable_list_node = std::make_shared<VariableListNode>(VariableListNode::GrammarType::VARIABLE);
        (yyval.variable_list_node_info).variable_list_node->append_child(std::move((yyvsp[(1) - (1)].variable_node_info).variable_node));
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 1252 "parser.y"
    {
        // variable_list -> variable_list ',' variable
        (yyval.variable_list_node_info).type_list = std::move((yyvsp[(1) - (3)].variable_list_node_info).type_list);
        (yyval.variable_list_node_info).type_list->push_back((yyvsp[(3) - (3)].variable_node_info).type);
        if(error_flag)
            YYABORT;
        (yyval.variable_list_node_info).variable_list_node = std::make_shared<VariableListNode>(VariableListNode::GrammarType::VARIABLE_LIST_VARIABLE);
        (yyval.variable_list_node_info).variable_list_node->append_child(std::move((yyvsp[(1) - (3)].variable_list_node_info).variable_list_node));
        (yyval.variable_list_node_info).variable_list_node->append_child(std::move((yyvsp[(3) - (3)].variable_node_info).variable_node));
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 1265 "parser.y"
    {
        // variable → ID id_varpart
        if (error_flag) YYABORT;

        // 符号表查找
        std::string var_name = (yyvsp[(1) - (2)].token_info).value.get<std::string>();
        auto identifier = symbol_table_queue.top()->get_identifier_by_name(var_name);
        (yyval.variable_node_info).type = TYPE_ERROR;  // 全局错误类型
        (yyval.variable_node_info).is_lvalue = true;

        // 1. 检查标识符是否存在
        if (!identifier) {
            semantic_error((yylsp[(1) - (2)]), "'" + var_name + "' is undeclared");
            YYABORT;
        }

        // 2. 检查标识符类型
        if (auto const_identifier = std::dynamic_pointer_cast<ConstIdentifier>(identifier)) {
            // 常量不可修改
            (yyval.variable_node_info).is_lvalue = false;
            (yyval.variable_node_info).type = const_identifier->get_value_type();
        } 
        else if (auto func_identifier = std::dynamic_pointer_cast<FunctionIdentifier>(identifier)) {
            // 函数名作为右值处理
            (yyval.variable_node_info).is_lvalue = false;
            semantic_error((yylsp[(1) - (2)]), "Function name '" + var_name + "' cannot be used as variable");
            YYABORT;
        } 
        else {
            // 变量或参数
            auto var_identifier = std::dynamic_pointer_cast<VarIdentifier>(identifier);
            (yyval.variable_node_info).type = var_identifier->get_value_type();

            // 处理数组/记录的访问部分
            if (auto array_type = std::dynamic_pointer_cast<ArrayType>((yyval.variable_node_info).type)) {
                // 传递数组边界信息到 id_varpart 节点
                auto bounds = array_type->get_bounds();
                (yyvsp[(2) - (2)].id_varpart_node_info).id_varpart_node->set_bounds(bounds);
            }

            // 执行访问检查（例如数组下标或记录字段）
            (yyval.variable_node_info).type = (yyvsp[(2) - (2)].id_varpart_node_info).access_check((yyval.variable_node_info).type);
            if (!(yyval.variable_node_info).type) {
                std::string tn = (yyval.variable_node_info).type->get_pascal_name();
                semantic_error((yylsp[(2) - (2)]), "Invalid access on type '" + tn + "'");
                YYABORT;
            }

            // 处理引用类型
            if (var_identifier->is_reference()) {
                (yyval.variable_node_info).is_ref = true;  // 标记为引用类型
            }
        }

        // 构建AST节点
        (yyval.variable_node_info).variable_node = std::make_shared<pascals::ast::VariableNode>();
        (yyval.variable_node_info).variable_node->append_child(std::make_shared<pascals::ast::LeafNode>(var_name));
        (yyval.variable_node_info).variable_node->append_child((yyvsp[(2) - (2)].id_varpart_node_info).id_varpart_node);
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 1327 "parser.y"
    {
        // id_varpart -> empty.
        if(error_flag)
            YYABORT;
        (yyval.id_varpart_node_info).var_parts = std::make_shared<std::vector<VarParts>>();
        (yyval.id_varpart_node_info).id_varparts_node = std::make_shared<IDVarPartsNode>();
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1335 "parser.y"
    {   
        // id_varpart -> [expression_list].
        (yyval.id_varpart_node_info).var_part = std::make_shared<VarParts>();
        (yyval.id_varpart_node_info).var_part->flag = 0;//数组
        (yyval.id_varpart_node_info).var_part->subscript = std::move((yyvsp[(2) - (3)].expression_list_node_info).type_list);
        if(error_flag)
            YYABORT;
        (yyval.id_varpart_node_info).id_varpart_node = std::make_shared<IDVarPartNode>(IDVarPartNode::GrammarType::EXP_LIST);
        (yyval.id_varpart_node_info).id_varpart_node->append_child(std::move((yyvsp[(2) - (3)].expression_list_node_info).expression_list_node));
    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1347 "parser.y"
    {
        // else_part -> empty.
        if(error_flag)
            YYABORT;
        (yyval.else_node) = std::make_shared<ElseNode>(ElseNode::GrammarType::EPSILON);
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1354 "parser.y"
    {
        // else_part -> ELSE statement.
        if(error_flag)
            YYABORT;
        (yyval.else_node) = std::make_shared<ElseNode>(ElseNode::GrammarType::ELSE_STATEMENT);
        (yyval.else_node)->append_child(std::move((yyvsp[(2) - (2)].statement_node)));
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1367 "parser.y"
    {
        // expression_list -> expression_list ',' expression
        (yyval.expression_list_node_info).type_list = std::move((yyvsp[(1) - (3)].expression_list_node_info).type_list);
        (yyval.expression_list_node_info).type_list->push_back((yyvsp[(3) - (3)].expression_node_info).type);
        (yyval.expression_list_node_info).is_lvalue_list = std::move((yyvsp[(1) - (3)].expression_list_node_info).is_lvalue_list);
        (yyval.expression_list_node_info).is_lvalue_list->push_back((yyvsp[(3) - (3)].expression_node_info).is_lvalue);
        if(error_flag)
            YYABORT;
        (yyval.expression_list_node_info).expression_list_node = std::make_shared<ExpressionListNode>((ExpressionListNode::GrammarType)1);
        (yyval.expression_list_node_info).expression_list_node->append_child(std::move((yyvsp[(1) - (3)].expression_list_node_info).expression_list_node));
        (yyval.expression_list_node_info).expression_list_node->append_child(std::move((yyvsp[(3) - (3)].expression_node_info).expression_node));
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1380 "parser.y"
    {
        // expression_list -> expression
        (yyval.expression_list_node_info).type_list = std::make_shared<std::vector<TypeTemplate*>>();
        (yyval.expression_list_node_info).type_list->push_back((yyvsp[(1) - (1)].expression_node_info).type);
        (yyval.expression_list_node_info).is_lvalue_list = std::make_shared<std::vector<bool>>();
        (yyval.expression_list_node_info).is_lvalue_list->push_back((yyvsp[(1) - (1)].expression_node_info).is_lvalue);
        if(error_flag)
            YYABORT;
        (yyval.expression_list_node_info).expression_list_node = std::make_shared<ExpressionListNode>((ExpressionListNode::GrammarType)0);
        (yyval.expression_list_node_info).expression_list_node->append_child(std::move((yyvsp[(1) - (1)].expression_node_info).expression_node));
    ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1394 "parser.y"
    {
        // expression → simple_expression RELOP simple_expression
        if (error_flag) YYABORT;

        // 类型检查：操作数必须为基础类型
        auto type1 = std::dynamic_pointer_cast<BasicType>((yyvsp[(1) - (3)].simple_expression_node_info).type);
        auto type2 = std::dynamic_pointer_cast<BasicType>((yyvsp[(3) - (3)].simple_expression_node_info).type);
        if (!type1 || !type2) {
            std::string tn1 = (yyvsp[(1) - (3)].simple_expression_node_info).type->get_pascal_name();
            std::string tn2 = (yyvsp[(3) - (3)].simple_expression_node_info).type->get_pascal_name();
            std::string op = (yyvsp[(2) - (3)].token_info).value.get<std::string>();
            semantic_error((yyloc), "Invalid operands to binary operator '" + op + 
                              "', types '" + tn1 + "' and '" + tn2 + "' are not basic types");
            YYABORT;
        }

        // 计算运算结果类型
        auto result_type = compute(type1, type2, (yyvsp[(2) - (3)].token_info).value.get<std::string>());
        if (result_type == TYPE_ERROR) {
            std::string tn1 = type1->get_pascal_name();
            std::string tn2 = type2->get_pascal_name();
            std::string op = (yyvsp[(2) - (3)].token_info).value.get<std::string>();
            semantic_error((yyloc), "Invalid operands to binary operator '" + op + 
                              "' (have '" + tn1 + "' and '" + tn2 + "')");
            YYABORT;
        }

        // 构建AST节点
        (yyval.expression_node_info).expression_node = std::make_shared<pascals::ast::ExpressionNode>();
        (yyval.expression_node_info).type = result_type;
        (yyval.expression_node_info).is_lvalue = false;

        // 处理运算符符号（例如将 '<>' 转换为 '!='）
        std::string relop = (yyvsp[(2) - (3)].token_info).value.get<std::string>();
        if (relop == "<>") relop = "!=";

        auto relop_node = std::make_shared<pascals::ast::LeafNode>(ConstValue(relop));
        (yyval.expression_node_info).expression_node->append_child((yyvsp[(1) - (3)].simple_expression_node_info).simple_expression_node);
        (yyval.expression_node_info).expression_node->append_child(relop_node);
        (yyval.expression_node_info).expression_node->append_child((yyvsp[(3) - (3)].simple_expression_node_info).simple_expression_node);
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1436 "parser.y"
    {
        // expression → simple_expression
        (yyval.expression_node_info).type = (yyvsp[(1) - (1)].simple_expression_node_info).type;
        (yyval.expression_node_info).is_lvalue = (yyvsp[(1) - (1)].simple_expression_node_info).is_lvalue;

        if (error_flag) YYABORT;

        // 处理数组类型标记
        if (auto array_type = std::dynamic_pointer_cast<ArrayType>((yyval.expression_node_info).type)) {
            (yyval.expression_node_info).expression_node = std::make_shared<pascals::ast::ExpressionNode>(
                pascals::ast::ExpressionNode::TargetType::VAR_ARRAY
            );
        } else {
            (yyval.expression_node_info).expression_node = std::make_shared<pascals::ast::ExpressionNode>();
        }

        (yyval.expression_node_info).expression_node->append_child((yyvsp[(1) - (1)].simple_expression_node_info).simple_expression_node);
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1457 "parser.y"
    {   
        // simple_expression -> term.
        (yyval.simple_expression_node_info).type = (yyvsp[(1) - (1)].term_node_info).type;
        (yyval.simple_expression_node_info).is_lvalue = (yyvsp[(1) - (1)].term_node_info).is_lvalue;
        if(error_flag)
            YYABORT;
        (yyval.simple_expression_node_info).simple_expression_node = std::make_shared<SimpleExpressionNode>();
        (yyval.simple_expression_node_info).simple_expression_node->append_child(std::move((yyvsp[(1) - (1)].term_node_info).term_node));
    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1467 "parser.y"
    {
        // simple_expression -> simple_expression or term.、
        //类型检查
        if((yyvsp[(1) - (3)].simple_expression_node_info).type!=(yyvsp[(3) - (3)].term_node_info).type){
            string tn1 = type_name((yyvsp[(1) - (3)].simple_expression_node_info).type);
            string tn2 = type_name((yyvsp[(3) - (3)].term_node_info).type);
            semantic_error(real_ast,"invalid operands to binary or (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        (yyval.simple_expression_node_info).is_lvalue = false;
        (yyval.simple_expression_node_info).type = (yyvsp[(1) - (3)].simple_expression_node_info).type;

        if(error_flag)
            YYABORT;
        (yyval.simple_expression_node_info).simple_expression_node = std::make_shared<SimpleExpressionNode>();
        auto addop_node = std::make_shared<LeafNode>(ConstValue("||"));
        (yyval.simple_expression_node_info).simple_expression_node->append_child(std::move((yyvsp[(1) - (3)].simple_expression_node_info).simple_expression_node));
        (yyval.simple_expression_node_info).simple_expression_node->append_child(std::move(addop_node));
        (yyval.simple_expression_node_info).simple_expression_node->append_child(std::move((yyvsp[(3) - (3)].term_node_info).term_node));
    ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1489 "parser.y"
    {   
        // term → factor
        (yyval.term_node_info).type = (yyvsp[(1) - (1)].factor_node_info).type;
        (yyval.term_node_info).is_lvalue = (yyvsp[(1) - (1)].factor_node_info).is_lvalue;
        if (error_flag) YYABORT;
        
        (yyval.term_node_info).term_node = std::make_shared<pascals::ast::TermNode>();
        (yyval.term_node_info).term_node->append_child((yyvsp[(1) - (1)].factor_node_info).factor_node);
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1499 "parser.y"
    {  
        // term → term MULOP factor
        if (error_flag) YYABORT;

        // 类型检查：操作数必须为基础类型
        auto type1 = std::dynamic_pointer_cast<BasicType>((yyvsp[(1) - (3)].term_node_info).type);
        auto type2 = std::dynamic_pointer_cast<BasicType>((yyvsp[(3) - (3)].factor_node_info).type);
        if (!type1 || !type2) {
            std::string tn1 = (yyvsp[(1) - (3)].term_node_info).type->get_pascal_name();
            std::string tn2 = (yyvsp[(3) - (3)].factor_node_info).type->get_pascal_name();
            std::string op = (yyvsp[(2) - (3)].token_info).value.get<std::string>();
            semantic_error((yyloc), "Invalid operands to binary operator '" + op + 
                              "', types '" + tn1 + "' and '" + tn2 + "' are not basic types");
            YYABORT;
        }

        // 计算运算结果类型
        auto result_type = compute(type1, type2, (yyvsp[(2) - (3)].token_info).value.get<std::string>());
        if (result_type == TYPE_ERROR) {
            std::string tn1 = type1->get_pascal_name();
            std::string tn2 = type2->get_pascal_name();
            std::string op = (yyvsp[(2) - (3)].token_info).value.get<std::string>();
            semantic_error((yyloc), "Invalid operands to binary operator '" + op + 
                              "' (have '" + tn1 + "' and '" + tn2 + "')");
            YYABORT;
        }

        // 运算符转换逻辑
        std::string mulop = (yyvsp[(2) - (3)].token_info).value.get<std::string>();
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
            (yyvsp[(1) - (3)].term_node_info).term_node->set_op_div(true);
        }

        // 构建AST节点
        (yyval.term_node_info).term_node = std::make_shared<pascals::ast::TermNode>();
        auto mulop_node = std::make_shared<pascals::ast::LeafNode>(ConstValue(mulop));
        (yyval.term_node_info).term_node->append_child((yyvsp[(1) - (3)].term_node_info).term_node);
        (yyval.term_node_info).term_node->append_child(mulop_node);
        (yyval.term_node_info).term_node->append_child((yyvsp[(3) - (3)].factor_node_info).factor_node);
        (yyval.term_node_info).type = result_type;
        (yyval.term_node_info).is_lvalue = false;
    ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1556 "parser.y"
    {
        (yyval.factor_node_info).type = (yyvsp[(1) - (1)].value_node_info).type;
        if(error_flag)
            YYABORT;
        auto num_node = std::make_shared<LeafNode>((yyvsp[(1) - (1)].value_node_info).value);
        (yyval.factor_node_info).factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::NUM);
        (yyval.factor_node_info).factor_node->append_child(std::move(num_node));
    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1565 "parser.y"
    {   
        // factor -> variable.
        (yyval.factor_node_info).type = (yyvsp[(1) - (1)].variable_node_info).type;
        (yyval.factor_node_info).is_lvalue = (yyvsp[(1) - (1)].variable_node_info).is_lvalue;
        if(error_flag)
            YYABORT;
        (yyval.factor_node_info).factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::VARIABLE);
        (yyval.factor_node_info).factor_node->append_child(std::move((yyvsp[(1) - (1)].variable_node_info).variable_node));
    ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1575 "parser.y"
    {
        if(error_flag)
            YYABORT;

        // 1. 符号表查找
        std::string func_name = (yyvsp[(1) - (4)].token_info).value.get<std::string>();
        auto symbol_table = symbol_table_queue.top();
        auto identifier = symbol_table->get_identifier_by_name(func_name);

        // 检查是否为函数标识符
        auto func = std::dynamic_pointer_cast<pascals::FunctionIdentifier>(identifier);
        if (!func) {
            std::string error_msg = "undefined function '" + func_name + "'";
            semantic_error(real_ast, error_msg, (yyvsp[(1) - (4)].token_info).line_num, (yyvsp[(1) - (4)].token_info).column_num);
            YYABORT;
        }

        // 2. 参数个数检查
        if (func->get_param_count() != (yyvsp[(3) - (4)].expression_list_node_info).type_ptr_list->size()) {
            std::string error_msg = "Argument count mismatch for function '" + func_name + 
                                    "', expected " + std::to_string(func->get_param_count()) + 
                                    ", got " + std::to_string((yyvsp[(3) - (4)].expression_list_node_info).type_ptr_list->size());
            semantic_error(real_ast, error_msg, line_count, 0);
            YYABORT;
        }

        // 3. 参数类型和引用模式检查
        bool params_valid = true;
        std::string expected_params, actual_params;
        for (size_t i = 0; i < (yyvsp[(3) - (4)].expression_list_node_info).type_ptr_list->size(); ++i) {
            auto param_info = func->get_param_at(i);
            
            // 类型检查
            if (!is_same(param_info->param_type.get(), (*(yyvsp[(3) - (4)].expression_list_node_info).type_ptr_list)[i])) {
                params_valid = false;
            }
            
            // 引用模式检查
            if (param_info->is_reference && !(*(yyvsp[(3) - (4)].expression_list_node_info).is_lvalue_list)[i]) {
                std::string error_msg = "Non-lvalue passed to reference parameter " + 
                                        std::to_string(i+1) + " of function '" + func_name + "'";
                semantic_error(real_ast, error_msg, line_count, 0);
                params_valid = false;
            }
            
            // 收集类型信息用于错误报告
            expected_params += (i > 0 ? ", " : "") + param_info->param_type->name();
            actual_params += (i > 0 ? ", " : "") + (*(yyvsp[(3) - (4)].expression_list_node_info).type_ptr_list)[i]->name();
        }

        if (!params_valid) {
            std::string error_msg = "Parameter type mismatch for function '" + func_name + 
                                    "', expected (" + expected_params + "), got (" + actual_params + ")";
            semantic_error(real_ast, error_msg, line_count, 0);
            YYABORT;
        }

        // 构建AST节点
        (yyval.factor_node_info).is_lvalue = false;
        (yyval.factor_node_info).type = func->get_value_type().get();
        (yyval.factor_node_info).factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::ID_EXP_LIST);
        auto id_node = std::make_shared<pascals::ast::LeafNode>((yyvsp[(1) - (4)].token_info).value);
        (yyval.factor_node_info).factor_node->append_child(std::move(id_node));
        (yyval.factor_node_info).factor_node->append_child((yyvsp[(3) - (4)].expression_list_node_info).expression_list_node);

        // 设置引用信息
        auto ref_vec = func->ParamRefVec();
        auto ref_stack = std::make_shared<std::stack<bool>>();
        for (auto i : ref_vec){
            ref_stack->push(i);
        }
        (yyvsp[(3) - (4)].expression_list_node_info).expression_list_node->set_ref(ref_stack.get());

    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1650 "parser.y"
    {
        // factor -> (expression).
        (yyval.factor_node_info).type = (yyvsp[(2) - (3)].expression_node_info).type;
        (yyval.factor_node_info).is_lvalue = false;
        if(error_flag)
            YYABORT;
        (yyval.factor_node_info).factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::EXP);
        (yyval.factor_node_info).factor_node->append_child(std::move((yyvsp[(2) - (3)].expression_node_info).expression_node));
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1660 "parser.y"
    {   
        // factor -> not factor.
        // 类型检查
        if(!is_basic((yyvsp[(2) - (2)].factor_node_info).type)){
            semantic_error(real_ast,"wrong type argument to unary not",line_count,0);
            YYABORT;
        }
        auto result=compute((BasicType*)(yyvsp[(2) - (2)].factor_node_info).type, "not");
        
        if(result==TYPE_ERROR){
            semantic_error(real_ast,"wrong type argument to unary not",line_count,0);
            YYABORT;
        }
        (yyval.factor_node_info).is_lvalue = false;
        (yyval.factor_node_info).type = result;

        if(error_flag)
            YYABORT;
        (yyval.factor_node_info).factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::NOT);
        (yyval.factor_node_info).factor_node->append_child(std::move((yyvsp[(2) - (2)].factor_node_info).factor_node));
    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1682 "parser.y"
    {   
        
        (yyval.factor_node_info).type = (yyvsp[(2) - (2)].factor_node_info).type;
        (yyval.factor_node_info).is_lvalue = false;
        if(error_flag)
            YYABORT;
        (yyval.factor_node_info).factor_node = std::make_shared<FactorNode>(FactorNode::GrammarType::UMINUS);
        (yyval.factor_node_info).factor_node->append_child(std::move((yyvsp[(2) - (2)].factor_node_info).factor_node));
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 3494 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (real_ast, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (real_ast, yymsg);
	  }
	else
	  {
	    yyerror (real_ast, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, real_ast);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, real_ast);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (real_ast, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, real_ast);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, real_ast);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1691 "parser.y"

 

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

