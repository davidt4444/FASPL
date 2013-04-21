/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BUFLEN = 259,
     MAXTOKENLEN = 256,
     ENDFILE = 260,
     ERROR = 261,
     RETURN = 262,
     VOID = 263,
     DATASET = 264,
     INT = 265,
     IDENTIFIER = 266,
     NUMBER = 267,
     STRING_LITERAL = 268,
     ATTRIBUTE_JOIN = 269,
     BLOCK_JOIN = 270,
     PAR = 271,
     AND = 272,
     OR = 273,
     LT = 274,
     LTE = 275,
     GT = 276,
     GTE = 277,
     IE = 278,
     NE = 279,
     NOT = 280,
     COMMENT = 281,
     COMPOUND_DATASET = 282,
     DATSET_INFO = 283,
     IF = 284,
     WHILE = 285,
     FOR = 286,
     DO = 287,
     ELSE = 288,
     STRING = 289,
     DOUBLE = 290,
     COORDINATE = 291,
     READ = 292,
     WRITE = 293,
     INPUT = 294,
     OUTPUT = 295
   };
#endif
/* Tokens.  */
#define BUFLEN 259
#define MAXTOKENLEN 256
#define ENDFILE 260
#define ERROR 261
#define RETURN 262
#define VOID 263
#define DATASET 264
/**/
#define INT 265
#define IDENTIFIER 266
#define NUMBER 267
#define STRING_LITERAL 268
#define ATTRIBUTE_JOIN 269
#define BLOCK_JOIN 270
#define PAR 271
#define AND 272
#define OR 273
#define LT 274
#define LTE 275
#define GT 276
#define GTE 277
#define IE 278
#define NE 279
#define NOT 280
#define COMMENT 281
#define COMPOUND_DATASET 282
#define DATSET_INFO 283
#define IF 284
#define WHILE 285
#define FOR 286
#define DO 287
#define ELSE 288
#define STRING 289
#define DOUBLE 290
#define COORDINATE 291
#define READ 292
#define WRITE 293
#define INPUT 294
#define OUTPUT 295




/* Copy the first part of user declarations.  */
#line 1 "YACC_Grammar_FASPL.c"

#include "header.h"

#define YYSTYPE TreeNode * /* this line will be explained below */
#define YYSTYPE_IS_DECLARED 1
/* this seems to be needed if you use Bison */
/*
#define alloca 
*/
/* to access the scanner's global var */
extern char * yytext; 

TreeNode * root;
int yyerror(char *);
TreeNode * newNode(void);
void printTree(TreeNode * root, int tab);
int verbose;


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 205 "YACC_Grammar_FASPL.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   355

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNRULES -- Number of states.  */
#define YYNSTATES  227

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    52,     2,     2,
      41,    42,    50,    48,    45,    49,     2,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,    46,
       2,    47,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     4,     2,     2,     3,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     1,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    19,    27,    36,    44,
      53,    61,    70,    78,    82,    84,    87,    90,    93,    96,
      99,   102,   104,   107,   109,   111,   114,   116,   120,   124,
     128,   132,   136,   140,   143,   145,   147,   149,   151,   155,
     158,   160,   163,   165,   168,   178,   184,   192,   198,   206,
     208,   210,   212,   216,   218,   222,   224,   228,   230,   234,
     238,   242,   246,   250,   254,   256,   260,   264,   266,   270,
     274,   276,   280,   282,   286,   290,   292,   296,   300,   303,
     306,   308,   312,   316,   321,   323,   331,   339,   344,   349,
     351,   353,   357,   359,   363,   365,   367,   369,   373,   375,
     379,   381,   383
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    -1,    59,    58,    -1,    59,    -1,
       9,    87,    41,    60,    42,    43,    62,    44,    -1,     9,
      87,    41,    42,    43,    62,    44,    -1,    10,    87,    41,
      60,    42,    43,    62,    44,    -1,    10,    87,    41,    42,
      43,    62,    44,    -1,    35,    87,    41,    60,    42,    43,
      62,    44,    -1,    35,    87,    41,    42,    43,    62,    44,
      -1,    34,    87,    41,    60,    42,    43,    62,    44,    -1,
      34,    87,    41,    42,    43,    62,    44,    -1,    61,    45,
      60,    -1,    61,    -1,     9,    87,    -1,    10,    87,    -1,
      35,    87,    -1,    34,    87,    -1,    39,    87,    -1,    40,
      87,    -1,     8,    -1,    63,    65,    -1,    63,    -1,    65,
      -1,    64,    63,    -1,    64,    -1,    10,    87,    46,    -1,
      35,    87,    46,    -1,     9,    87,    46,    -1,    34,    87,
      46,    -1,    39,    87,    46,    -1,    40,    87,    46,    -1,
      66,    65,    -1,    66,    -1,    68,    -1,    69,    -1,    70,
      -1,    43,    62,    44,    -1,    43,    44,    -1,    67,    -1,
      71,    46,    -1,    46,    -1,     7,    67,    -1,    31,    41,
      71,    46,    71,    46,    71,    42,    66,    -1,    30,    41,
      71,    42,    66,    -1,    32,    66,    30,    41,    71,    42,
      46,    -1,    29,    41,    71,    42,    66,    -1,    29,    41,
      71,    42,    66,    33,    66,    -1,    73,    -1,    72,    -1,
      74,    -1,    72,    37,    87,    -1,    87,    -1,    73,    38,
      74,    -1,    87,    -1,    87,    47,    74,    -1,    75,    -1,
      76,    24,    75,    -1,    76,    23,    75,    -1,    76,    20,
      75,    -1,    76,    22,    75,    -1,    76,    19,    75,    -1,
      76,    21,    75,    -1,    76,    -1,    77,    48,    76,    -1,
      77,    49,    76,    -1,    77,    -1,    78,    50,    77,    -1,
      78,    51,    77,    -1,    78,    -1,    79,    52,    78,    -1,
      79,    -1,    80,    14,    79,    -1,    80,    15,    79,    -1,
      80,    -1,    81,    17,    80,    -1,    81,    18,    80,    -1,
      49,    80,    -1,    25,    80,    -1,    81,    -1,    41,    71,
      42,    -1,    87,    41,    42,    -1,    87,    41,    82,    42,
      -1,    87,    -1,    87,    53,    83,    54,    43,    85,    44,
      -1,    87,    43,    85,    44,    53,    83,    54,    -1,    87,
      53,    83,    54,    -1,    87,    43,    85,    44,    -1,    89,
      -1,    88,    -1,    71,    45,    82,    -1,    71,    -1,    84,
      45,    83,    -1,    84,    -1,    71,    -1,     8,    -1,    86,
      45,    85,    -1,    86,    -1,    71,    55,    71,    -1,    11,
      -1,    12,    -1,    13,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    64,    64,    73,    80,    89,   105,   121,   137,   153,
     169,   185,   201,   220,   227,   236,   246,   256,   266,   276,
     288,   300,   309,   330,   336,   345,   352,   361,   371,   381,
     391,   401,   413,   428,   435,   444,   450,   456,   462,   468,
     474,   483,   489,   498,   511,   524,   535,   549,   560,   575,
     581,   587,   596,   607,   616,   627,   636,   647,   656,   667,
     678,   689,   700,   711,   722,   730,   741,   752,   760,   771,
     782,   790,   801,   809,   820,   831,   840,   851,   862,   872,
     882,   891,   897,   907,   918,   924,   940,   956,   972,   988,
     994,  1003,  1010,  1019,  1026,  1035,  1041,  1054,  1061,  1070,
    1086,  1097,  1118
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BUFLEN", "MAXTOKENLEN", "ENDFILE",
  "ERROR", "RETURN", "VOID", "DATASET", "INT", "IDENTIFIER", "NUMBER",
  "STRING_LITERAL", "ATTRIBUTE_JOIN", "BLOCK_JOIN", "PAR", "AND", "OR",
  "LT", "LTE", "GT", "GTE", "IE", "NE", "NOT", "COMMENT",
  "COMPOUND_DATASET", "DATSET_INFO", "IF", "WHILE", "FOR", "DO", "ELSE",
  "STRING", "DOUBLE", "COORDINATE", "READ", "WRITE", "INPUT", "OUTPUT",
  "'('", "')'", "'{'", "'}'", "','", "';'", "'='", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'['", "']'", "':'", "$accept", "program",
  "declaration_list", "declaration", "parameter_list", "parameter",
  "compound_statement", "variable_list", "variable", "statement_list",
  "statement", "expression_statement", "return_statement",
  "iteration_statement", "selection_statement", "expression",
  "read_expression", "write_expression", "assignment_expression",
  "simple_expression", "add_expression", "mul_expression",
  "mod_expression", "join_expression", "term", "factor", "argument_list",
  "info_list", "info", "coordinate_list", "coordinate", "id", "num",
  "string", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   296,   297,   259,   256,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    40,    41,   123,   125,    44,    59,    61,    43,    45,
      42,    47,    37,    91,    93,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    59,
      59,    59,    59,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    62,    62,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    65,    65,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    69,    69,    69,    70,    70,    71,
      71,    71,    72,    72,    73,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    76,    76,    76,    77,    77,
      77,    78,    78,    79,    79,    79,    80,    80,    80,    80,
      80,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    82,    82,    83,    83,    84,    84,    85,    85,    86,
      87,    88,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     8,     7,     8,     7,     8,
       7,     8,     7,     3,     1,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     1,     3,     2,
       1,     2,     1,     2,     9,     5,     7,     5,     7,     1,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     2,     2,
       1,     3,     3,     4,     1,     7,     7,     4,     4,     1,
       1,     3,     1,     3,     1,     1,     1,     3,     1,     3,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     4,   100,     0,
       0,     0,     0,     1,     3,     0,     0,     0,     0,    21,
       0,     0,     0,     0,     0,     0,     0,     0,    14,     0,
       0,     0,     0,     0,     0,    15,    16,    18,    17,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,    23,
      26,    24,    34,    40,    35,    36,    37,     0,    50,    49,
      51,    57,    64,    67,    70,    72,    75,    80,    84,    90,
      89,     0,    13,     0,     0,     0,     0,     0,     0,    43,
       0,     0,    79,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,     0,    78,     6,    22,    25,    33,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     0,    12,     0,    10,     0,    29,
      27,     0,     0,     0,     0,    30,    28,    31,    32,    81,
      38,    52,    54,    84,    62,    60,    63,    61,    59,    58,
      65,    66,    68,    69,    71,    73,    74,    76,    77,    82,
      92,     0,     0,     0,    98,    56,    96,    95,     0,    94,
       5,     7,    11,     9,     0,     0,     0,     0,     0,    83,
       0,    88,     0,    87,     0,    47,    45,     0,     0,    91,
      99,     0,    97,     0,    93,     0,     0,     0,     0,     0,
      48,     0,    46,    86,    85,     0,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,    27,    28,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,   181,   188,   189,   183,
     184,    88,    89,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -172
static const yytype_int16 yypact[] =
{
       3,    -9,    -9,    -9,    -9,    24,  -172,     3,  -172,    -1,
       4,    15,    17,  -172,  -172,   266,   275,   284,   294,  -172,
      -9,    -9,    -9,    -9,    -9,    -9,   -11,    -6,    19,    39,
      20,    52,    56,    58,    72,  -172,  -172,  -172,  -172,  -172,
    -172,   221,    76,    57,   221,    79,   221,    81,   221,    84,
      77,    -9,    -9,  -172,  -172,   246,    87,    91,    92,   118,
      -9,    -9,    -9,    -9,   246,   180,  -172,   246,    93,   118,
      -5,  -172,   118,  -172,  -172,  -172,  -172,    88,   104,   107,
    -172,  -172,    55,    38,    43,    99,    90,    89,   300,  -172,
    -172,   221,  -172,   108,   221,   110,   221,   113,   221,  -172,
     114,   116,  -172,   -20,   246,   246,   246,   133,   119,   122,
     140,   154,   159,  -172,   158,  -172,  -172,  -172,  -172,  -172,
    -172,    -9,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   224,   246,
     246,    14,   160,  -172,   162,  -172,   163,  -172,   164,  -172,
    -172,   161,   171,   170,   176,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,   -33,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
     173,   183,   167,   194,   182,  -172,  -172,  -172,   185,   195,
    -172,  -172,  -172,  -172,   118,   118,   246,   246,   246,  -172,
     246,   188,   246,   199,    14,   210,  -172,   198,   203,  -172,
    -172,    14,  -172,   246,  -172,   118,   246,   201,   200,   204,
    -172,   226,  -172,  -172,  -172,   118,  -172
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -172,  -172,   256,  -172,     0,  -172,   -37,   202,  -172,   -28,
     -59,   219,  -172,  -172,  -172,   -58,  -172,  -172,  -121,    71,
     -17,   -15,   144,   -14,   -52,  -172,    80,  -151,  -172,  -171,
    -172,    48,  -172,  -172
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -56
static const yytype_int16 yytable[] =
{
     107,   162,     8,   102,    51,    52,   112,    93,   138,    95,
     139,    97,     1,     2,   140,   115,    30,    32,    34,   185,
     141,   138,   186,   139,    13,     8,    53,    54,   114,    60,
      61,   212,    41,   141,    62,    63,    42,     3,     4,    55,
      15,   117,   219,    92,   119,    16,   151,   152,   153,     9,
      10,    11,    12,   214,   142,    64,    17,   144,    18,   146,
     218,   148,    45,    67,    43,    19,    20,    21,    35,    36,
      37,    38,    39,    40,   123,   124,   125,   126,   127,   128,
     180,   182,    44,   187,   177,   178,   129,   130,     8,    53,
      54,    22,    23,   131,   132,    46,    24,    25,    47,   100,
     101,    48,    55,   103,   134,   135,   136,   137,   108,   109,
     110,   111,   170,   171,    49,   103,   172,   173,    64,    91,
     175,   176,    94,    66,    96,    50,    67,    98,   104,     8,
      53,    54,   105,   106,   120,   205,   206,   116,   207,   208,
     180,   121,   210,    55,   182,   122,   187,    56,    57,    58,
      59,   133,   143,   187,   145,   182,   220,   147,   221,    64,
     149,    65,   150,   154,    66,   155,   226,    67,   156,   161,
     163,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   157,    50,   163,    51,
      52,     8,    53,    54,   164,   165,   166,   167,   168,   169,
     158,   159,   160,   194,   190,    55,   191,   192,   193,    56,
      57,    58,    59,   195,    60,    61,   196,   197,   198,    62,
      63,    64,   200,    65,   113,   199,    66,   202,    50,    67,
      51,    52,     8,    53,    54,     8,    53,    54,   201,   203,
     204,   211,   213,   215,   216,   217,    55,   222,   224,    55,
      56,    57,    58,    59,   223,    60,    61,     8,    53,    54,
      62,    63,    64,    14,    65,    64,   179,    66,   225,    99,
      67,    55,   118,    67,    19,    20,    21,   174,   209,     0,
       0,     0,     0,    19,    20,    21,     0,    64,     0,     0,
       0,     0,    19,    20,    21,    67,     0,     0,     0,     0,
      22,    23,    19,    20,    21,    24,    25,     0,    26,    22,
      23,     0,     0,     0,    24,    25,     0,    29,    22,    23,
       0,     0,     0,    24,    25,     0,    31,     0,    22,    23,
       0,     0,     0,    24,    25,     0,    33,   -53,   -55,     0,
       0,   138,   -53,   139,   -53,   -53,   -53,   140,     0,     0,
       0,     0,     0,   141,   -53,   -53
};

static const yytype_int16 yycheck[] =
{
      59,   122,    11,    55,     9,    10,    64,    44,    41,    46,
      43,    48,     9,    10,    47,    67,    16,    17,    18,   140,
      53,    41,     8,    43,     0,    11,    12,    13,    65,    34,
      35,   202,    43,    53,    39,    40,    42,    34,    35,    25,
      41,    69,   213,    43,    72,    41,   104,   105,   106,     1,
       2,     3,     4,   204,    91,    41,    41,    94,    41,    96,
     211,    98,    42,    49,    45,     8,     9,    10,    20,    21,
      22,    23,    24,    25,    19,    20,    21,    22,    23,    24,
     138,   139,    43,   141,   136,   137,    48,    49,    11,    12,
      13,    34,    35,    50,    51,    43,    39,    40,    42,    51,
      52,    43,    25,    55,    14,    15,    17,    18,    60,    61,
      62,    63,   129,   130,    42,    67,   131,   132,    41,    43,
     134,   135,    43,    46,    43,     7,    49,    43,    41,    11,
      12,    13,    41,    41,    46,   194,   195,    44,   196,   197,
     198,    37,   200,    25,   202,    38,   204,    29,    30,    31,
      32,    52,    44,   211,    44,   213,   215,    44,   216,    41,
      46,    43,    46,    30,    46,    46,   225,    49,    46,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,    46,     7,   140,     9,
      10,    11,    12,    13,   123,   124,   125,   126,   127,   128,
      46,    42,    44,    42,    44,    25,    44,    44,    44,    29,
      30,    31,    32,    42,    34,    35,    46,    41,    45,    39,
      40,    41,    55,    43,    44,    42,    46,    45,     7,    49,
       9,    10,    11,    12,    13,    11,    12,    13,    44,    54,
      45,    53,    43,    33,    46,    42,    25,    46,    44,    25,
      29,    30,    31,    32,    54,    34,    35,    11,    12,    13,
      39,    40,    41,     7,    43,    41,    42,    46,    42,    50,
      49,    25,    70,    49,     8,     9,    10,   133,   198,    -1,
      -1,    -1,    -1,     8,     9,    10,    -1,    41,    -1,    -1,
      -1,    -1,     8,     9,    10,    49,    -1,    -1,    -1,    -1,
      34,    35,     8,     9,    10,    39,    40,    -1,    42,    34,
      35,    -1,    -1,    -1,    39,    40,    -1,    42,    34,    35,
      -1,    -1,    -1,    39,    40,    -1,    42,    -1,    34,    35,
      -1,    -1,    -1,    39,    40,    -1,    42,    37,    38,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    34,    35,    57,    58,    59,    11,    87,
      87,    87,    87,     0,    58,    41,    41,    41,    41,     8,
       9,    10,    34,    35,    39,    40,    42,    60,    61,    42,
      60,    42,    60,    42,    60,    87,    87,    87,    87,    87,
      87,    43,    42,    45,    43,    42,    43,    42,    43,    42,
       7,     9,    10,    12,    13,    25,    29,    30,    31,    32,
      34,    35,    39,    40,    41,    43,    46,    49,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    87,    88,
      89,    43,    60,    62,    43,    62,    43,    62,    43,    67,
      87,    87,    80,    87,    41,    41,    41,    66,    87,    87,
      87,    87,    71,    44,    62,    80,    44,    65,    63,    65,
      46,    37,    38,    19,    20,    21,    22,    23,    24,    48,
      49,    50,    51,    52,    14,    15,    17,    18,    41,    43,
      47,    53,    62,    44,    62,    44,    62,    44,    62,    46,
      46,    71,    71,    71,    30,    46,    46,    46,    46,    42,
      44,    87,    74,    87,    75,    75,    75,    75,    75,    75,
      76,    76,    77,    77,    78,    79,    79,    80,    80,    42,
      71,    82,    71,    85,    86,    74,     8,    71,    83,    84,
      44,    44,    44,    44,    42,    42,    46,    41,    45,    42,
      55,    44,    45,    54,    45,    66,    66,    71,    71,    82,
      71,    53,    85,    43,    83,    33,    46,    42,    83,    85,
      66,    71,    46,    54,    44,    42,    66
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
      yyerror (YY_("syntax error: cannot back up")); \
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 65 "YACC_Grammar_FASPL.c"
    { 
			if(verbose)printf("Entering program\n");
			root = (yyvsp[(1) - (1)]); 
			if(verbose)printf("Leaving program\n");
		;}
    break;

  case 3:
#line 74 "YACC_Grammar_FASPL.c"
    { 
			if(verbose)printf("Entering declaration_list\n");
			(yyval) = (yyvsp[(1) - (2)]); 
			(yyval)->sibling = (yyvsp[(2) - (2)]); 
			if(verbose)printf("leaving declaration_list\n");
		;}
    break;

  case 4:
#line 81 "YACC_Grammar_FASPL.c"
    { 
			if(verbose)printf("Entering declaration_list\n");
			(yyval) = (yyvsp[(1) - (1)]); 
			if(verbose)printf("leaving declaration_list\n");
		;}
    break;

  case 5:
#line 90 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering declaration\n");
			(yyval) = newNode();
			(yyval)->type = DATASET;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "function");
			(yyval)->left = newNode();;
			(yyval)->left->type=DATASET;
			(yyval)->left->tokenString = (char *) calloc(8, sizeof(char));
			strcpy((yyval)->left->tokenString, "dataset");
			(yyval)->left->left=(yyvsp[(2) - (8)]);
			(yyval)->left->right=(yyvsp[(4) - (8)]);
			(yyval)->right = (yyvsp[(7) - (8)]);
			if(verbose)printf("leaving declaration\n");
		;}
    break;

  case 6:
#line 106 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering declaration\n");
			(yyval) = newNode();
			(yyval)->type = DATASET;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "function");
			(yyval)->left = newNode();;
			(yyval)->left->type=DATASET;
			(yyval)->left->tokenString = (char *) calloc(8, sizeof(char));
			strcpy((yyval)->left->tokenString, "dataset");
			(yyval)->left->left=(yyvsp[(2) - (7)]);
			(yyval)->left->right=0;
			(yyval)->right = (yyvsp[(6) - (7)]);
			if(verbose)printf("leaving declaration\n");
		;}
    break;

  case 7:
#line 122 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering declaration\n");
			(yyval) = newNode();
			(yyval)->type = INT;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "function");
			(yyval)->left = newNode();;
			(yyval)->left->type=INT;
			(yyval)->left->tokenString = (char *) calloc(4, sizeof(char));
			strcpy((yyval)->left->tokenString, "int");
			(yyval)->left->left=(yyvsp[(2) - (8)]);
			(yyval)->left->right=(yyvsp[(4) - (8)]);
			(yyval)->right = (yyvsp[(7) - (8)]);
			if(verbose)printf("leaving declaration\n");
		;}
    break;

  case 8:
#line 138 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering declaration\n");
			(yyval) = newNode();
			(yyval)->type = INT;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "function");
			(yyval)->left = newNode();;
			(yyval)->left->type=INT;
			(yyval)->left->tokenString = (char *) calloc(4, sizeof(char));
			strcpy((yyval)->left->tokenString, "int");
			(yyval)->left->left=(yyvsp[(2) - (7)]);
			(yyval)->left->right=0;
			(yyval)->right = (yyvsp[(6) - (7)]);
			if(verbose)printf("leaving declaration\n");
		;}
    break;

  case 9:
#line 154 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering declaration\n");
			(yyval) = newNode();
			(yyval)->type = DOUBLE;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "function");
			(yyval)->left = newNode();;
			(yyval)->left->type=DOUBLE;
			(yyval)->left->tokenString = (char *) calloc(4, sizeof(char));
			strcpy((yyval)->left->tokenString, "double");
			(yyval)->left->left=(yyvsp[(2) - (8)]);
			(yyval)->left->right=(yyvsp[(4) - (8)]);
			(yyval)->right = (yyvsp[(7) - (8)]);
			if(verbose)printf("leaving declaration\n");
		;}
    break;

  case 10:
#line 170 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering declaration\n");
			(yyval) = newNode();
			(yyval)->type = DOUBLE;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "function");
			(yyval)->left = newNode();;
			(yyval)->left->type=DOUBLE;
			(yyval)->left->tokenString = (char *) calloc(4, sizeof(char));
			strcpy((yyval)->left->tokenString, "double");
			(yyval)->left->left=(yyvsp[(2) - (7)]);
			(yyval)->left->right=0;
			(yyval)->right = (yyvsp[(6) - (7)]);
			if(verbose)printf("leaving declaration\n");
		;}
    break;

  case 11:
#line 186 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering declaration\n");
			(yyval) = newNode();
			(yyval)->type = STRING;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "function");
			(yyval)->left = newNode();;
			(yyval)->left->type=STRING;
			(yyval)->left->tokenString = (char *) calloc(7, sizeof(char));
			strcpy((yyval)->left->tokenString, "string");
			(yyval)->left->left=(yyvsp[(2) - (8)]);
			(yyval)->left->right=(yyvsp[(4) - (8)]);
			(yyval)->right = (yyvsp[(7) - (8)]);
			if(verbose)printf("leaving declaration\n");
		;}
    break;

  case 12:
#line 202 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering declaration\n");
			(yyval) = newNode();
			(yyval)->type = STRING;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "function");
			(yyval)->left = newNode();;
			(yyval)->left->type=STRING;
			(yyval)->left->tokenString = (char *) calloc(7, sizeof(char));
			strcpy((yyval)->left->tokenString, "string");
			(yyval)->left->left=(yyvsp[(2) - (7)]);
			(yyval)->left->right=0;
			(yyval)->right = (yyvsp[(6) - (7)]);
			if(verbose)printf("leaving declaration\n");
		;}
    break;

  case 13:
#line 221 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter_list\n");
			(yyval)=(yyvsp[(1) - (3)]);
			(yyval)->sibling=(yyvsp[(3) - (3)]);
			if(verbose)printf("leaving parameter_list\n");
		;}
    break;

  case 14:
#line 228 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter_list\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving parameter_list\n");
		;}
    break;

  case 15:
#line 237 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter\n");
			(yyval) = newNode();
			(yyval)->type = DATASET;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			(yyval)->left = (yyvsp[(2) - (2)]);
			if(verbose)printf("leaving parameter\n");
		;}
    break;

  case 16:
#line 247 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter\n");
			(yyval) = newNode();
			(yyval)->type = INT;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			(yyval)->left = (yyvsp[(2) - (2)]);
			if(verbose)printf("leaving parameter\n");
		;}
    break;

  case 17:
#line 257 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter\n");
			(yyval) = newNode();
			(yyval)->type = DOUBLE;
 			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			(yyval)->left = (yyvsp[(2) - (2)]);
			if(verbose)printf("leaving parameter\n");
		;}
    break;

  case 18:
#line 267 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter\n");
			(yyval) = newNode();
			(yyval)->type = STRING;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			(yyval)->left = (yyvsp[(2) - (2)]);
			if(verbose)printf("leaving parameter\n");
		;}
    break;

  case 19:
#line 277 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter\n");
			(yyval) = newNode();
			(yyval)->type = STRING;
			(yyval)->is_file = 1;
			(yyval)->is_input = 1;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			(yyval)->left = (yyvsp[(2) - (2)]);
			if(verbose)printf("leaving parameter\n");
		;}
    break;

  case 20:
#line 289 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter\n");
			(yyval) = newNode();
			(yyval)->type = STRING;
			(yyval)->is_file = 1;
			(yyval)->is_input = 0;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			(yyval)->left = (yyvsp[(2) - (2)]);
			if(verbose)printf("leaving parameter\n");
		;}
    break;

  case 21:
#line 301 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter\n");
			(yyval) = 0;
			if(verbose)printf("leaving parameter\n");
		;}
    break;

  case 22:
#line 310 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering compound_statement\n");
			(yyval)=(yyvsp[(1) - (2)]);
			t1=t2=t3=0;
			t1 = (yyval);
			while(t1)
			{
				t2=t1->sibling;
				if(t2)
				{
					t1=t2;
				}
				else
				{
					break;
				}
			}
			t1->sibling=(yyvsp[(2) - (2)]);	
			if(verbose)printf("leaving compound_statement\n");
		;}
    break;

  case 23:
#line 331 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering compound_statement\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving compound_statement\n");
		;}
    break;

  case 24:
#line 337 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering compound_statement\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving compound_statement\n");
		;}
    break;

  case 25:
#line 346 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering variable_list\n");
			(yyval)=(yyvsp[(1) - (2)]);
			(yyval)->sibling=(yyvsp[(2) - (2)]);	
			if(verbose)printf("leaving variable_list\n");
		;}
    break;

  case 26:
#line 353 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering variable_list\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving variable_list\n");
		;}
    break;

  case 27:
#line 362 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering variable\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(2) - (3)]);
			(yyval)->type = INT;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			if(verbose)printf("leaving variable\n");
		;}
    break;

  case 28:
#line 372 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering variable\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(2) - (3)]);
			(yyval)->type = DOUBLE;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			if(verbose)printf("leaving variable\n");
		;}
    break;

  case 29:
#line 382 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering variable\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(2) - (3)]);
			(yyval)->type = DATASET;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			if(verbose)printf("leaving variable\n");
		;}
    break;

  case 30:
#line 392 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering variable\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(2) - (3)]);
			(yyval)->type = STRING;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			if(verbose)printf("leaving variable\n");
		;}
    break;

  case 31:
#line 402 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter\n");
			(yyval) = newNode();
			(yyval)->type = STRING;
			(yyval)->is_file = 1;
			(yyval)->is_input = 1;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			(yyval)->left = (yyvsp[(2) - (3)]);
			if(verbose)printf("leaving parameter\n");
		;}
    break;

  case 32:
#line 414 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering parameter\n");
			(yyval) = newNode();
			(yyval)->type = STRING;
			(yyval)->is_file = 1;
			(yyval)->is_input = 0;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			(yyval)->left = (yyvsp[(2) - (3)]);
			if(verbose)printf("leaving parameter\n");
		;}
    break;

  case 33:
#line 429 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering statement_list\n");
			(yyval)=(yyvsp[(1) - (2)]);
			(yyval)->sibling=(yyvsp[(2) - (2)]);
			if(verbose)printf("leaving statement_list\n");
		;}
    break;

  case 34:
#line 436 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering statement_list\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving statement_list\n");
		;}
    break;

  case 35:
#line 445 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering statement\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving statement\n");
		;}
    break;

  case 36:
#line 451 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering statement\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving statement\n");
		;}
    break;

  case 37:
#line 457 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering statement\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving statement\n");
		;}
    break;

  case 38:
#line 463 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering statement\n");
			(yyval)=(yyvsp[(2) - (3)]);
			if(verbose)printf("leaving statement\n");
		;}
    break;

  case 39:
#line 469 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering statement\n");
			(yyval)=(yyvsp[(2) - (2)]);
			if(verbose)printf("leaving statement\n");
		;}
    break;

  case 40:
#line 475 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering statement\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving statement\n");
		;}
    break;

  case 41:
#line 484 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering expression_statement\n");
			(yyval)=(yyvsp[(1) - (2)]);
			if(verbose)printf("leaving expression_statement\n");
		;}
    break;

  case 42:
#line 490 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering expression_statement\n");
			(yyval)=0;
			if(verbose)printf("leaving expression_statement\n");
		;}
    break;

  case 43:
#line 499 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering return_statement\n");
			(yyval) = newNode();
			(yyval)->type = RETURN;
			(yyval)->tokenString = (char *) calloc(7, sizeof(char));
			strcpy((yyval)->tokenString, "return");
			(yyval)->left = (yyvsp[(2) - (2)]);
			if(verbose)printf("leaving return_statement\n");
		;}
    break;

  case 44:
#line 512 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering iteration_statement\n");
			(yyval) = newNode();
			(yyval)->type = FOR;
			(yyval)->tokenString = (char *) calloc(4, sizeof(char));
			strcpy((yyval)->tokenString, "for");
			(yyval)->left = (yyvsp[(3) - (9)]);
			(yyvsp[(3) - (9)])->sibling = (yyvsp[(5) - (9)]);
			(yyvsp[(5) - (9)])->sibling = (yyvsp[(7) - (9)]);
			(yyval)->right = (yyvsp[(9) - (9)]);
			if(verbose)printf("leaving iteration_statement\n");
		;}
    break;

  case 45:
#line 525 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering iteration_statement\n");
			(yyval) = newNode();
			(yyval)->type = WHILE;
			(yyval)->tokenString = (char *) calloc(6, sizeof(char));
			strcpy((yyval)->tokenString, "while");
			(yyval)->left = (yyvsp[(3) - (5)]);
			(yyval)->right = (yyvsp[(5) - (5)]);
			if(verbose)printf("leaving iteration_statement\n");
		;}
    break;

  case 46:
#line 536 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering iteration_statement\n");
			(yyval) = newNode();
			(yyval)->type = DO;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "do");
			(yyval)->left = (yyvsp[(5) - (7)]);
			(yyval)->right = (yyvsp[(2) - (7)]);
			if(verbose)printf("leaving iteration_statement\n");
		;}
    break;

  case 47:
#line 550 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering selection_statement\n");
			(yyval) = newNode();
			(yyval)->type = IF;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "if");
			(yyval)->left = (yyvsp[(3) - (5)]);
			(yyval)->right = (yyvsp[(5) - (5)]);
			if(verbose)printf("leaving selection_statement\n");
		;}
    break;

  case 48:
#line 561 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering selection_statement\n");
			(yyval) = newNode();
			(yyval)->type = IF;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "if");
			(yyval)->left = (yyvsp[(3) - (7)]);
			(yyval)->right = (yyvsp[(5) - (7)]);
			(yyval)->otherChild = (yyvsp[(7) - (7)]);
			if(verbose)printf("leaving selection_statement\n");
		;}
    break;

  case 49:
#line 576 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering expression\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving expression\n");
		;}
    break;

  case 50:
#line 582 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering expression\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving expression\n");
		;}
    break;

  case 51:
#line 588 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering expression\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving expression\n");
		;}
    break;

  case 52:
#line 597 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering read_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(3) - (3)]);
			(yyval)->type = READ;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, ">>");
			(yyval)->right = (yyvsp[(1) - (3)]);
			if(verbose)printf("leaving read_expression\n");
		;}
    break;

  case 53:
#line 608 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering read_expression\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving read_expression\n");
		;}
    break;

  case 54:
#line 617 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering write_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = WRITE;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "<<");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving write_expression\n");
		;}
    break;

  case 55:
#line 628 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering write_expression\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving write_expression\n");
		;}
    break;

  case 56:
#line 637 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering assignment_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = '=';
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, "=");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving assignment_expression\n");
		;}
    break;

  case 57:
#line 648 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering assignment_expression\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving assignment_expression\n");
		;}
    break;

  case 58:
#line 657 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering simple_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = NE;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "!=");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving simple_expression\n");
		;}
    break;

  case 59:
#line 668 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering simple_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = IE;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "==");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving simple_expression\n");
		;}
    break;

  case 60:
#line 679 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering simple_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = LTE;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "<=");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving simple_expression\n");
		;}
    break;

  case 61:
#line 690 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering simple_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = GTE;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, ">=");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving simple_expression\n");
		;}
    break;

  case 62:
#line 701 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering simple_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = LT;
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, "<");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving simple_expression\n");
		;}
    break;

  case 63:
#line 712 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering simple_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = GT;
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, ">");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving simple_expression\n");
		;}
    break;

  case 64:
#line 723 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering simple_expression\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving simple_expression\n");
		;}
    break;

  case 65:
#line 731 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering add_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = '+';
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, "+");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving add_expression\n");
		;}
    break;

  case 66:
#line 742 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering add_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = '-';
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, "-");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving add_expression\n");
		;}
    break;

  case 67:
#line 753 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering add_expression\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving add_expression\n");
		;}
    break;

  case 68:
#line 761 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering mul_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = '*';
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, "*");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving mul_expression\n");
		;}
    break;

  case 69:
#line 772 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering mul_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = '/';
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, "/");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving mul_expression\n");
		;}
    break;

  case 70:
#line 783 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering mul_expression\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving mul_expression\n");
		;}
    break;

  case 71:
#line 791 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering mod_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = '%';
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, "%");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving mod_expression\n");
		;}
    break;

  case 72:
#line 802 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering mod_expression\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving mod_expression\n");
		;}
    break;

  case 73:
#line 810 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering join_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = ATTRIBUTE_JOIN;
			(yyval)->tokenString = (char *) calloc(4, sizeof(char));
			strcpy((yyval)->tokenString, "[+]");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving join_expression\n");
		;}
    break;

  case 74:
#line 821 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering join_expression\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = BLOCK_JOIN;
			(yyval)->tokenString = (char *) calloc(4, sizeof(char));
			strcpy((yyval)->tokenString, "{+}");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving join_expression\n");
		;}
    break;

  case 75:
#line 832 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering join_expression\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving join_expression\n");
		;}
    break;

  case 76:
#line 841 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering term\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = AND;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "&&");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving term\n");
		;}
    break;

  case 77:
#line 852 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering term\n");
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->type = OR;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "||");
			(yyval)->right = (yyvsp[(3) - (3)]);
			if(verbose)printf("leaving term\n");
		;}
    break;

  case 78:
#line 863 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering term\n");
			(yyval) = newNode();
			(yyval)->type = '-';
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, "-");
			(yyval)->right = (yyvsp[(2) - (2)]);
			if(verbose)printf("leaving term\n");
		;}
    break;

  case 79:
#line 873 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering term\n");
			(yyval) = newNode();
			(yyval)->type = NOT;
			(yyval)->tokenString = (char *) calloc(2, sizeof(char));
			strcpy((yyval)->tokenString, "!");
			(yyval)->right = (yyvsp[(2) - (2)]);
			if(verbose)printf("leaving term\n");
		;}
    break;

  case 80:
#line 883 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering term\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving term\n");
		;}
    break;

  case 81:
#line 892 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval)=(yyvsp[(2) - (3)]);
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 82:
#line 898 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = newNode();
			(yyval)->type = PAR;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "()");
			(yyval)->left = (yyvsp[(1) - (3)]);
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 83:
#line 908 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = newNode();
			(yyval)->type = PAR;
			(yyval)->tokenString = (char *) calloc(3, sizeof(char));
			strcpy((yyval)->tokenString, "()");
			(yyval)->left = (yyvsp[(1) - (4)]);
			(yyval)->right = (yyvsp[(3) - (4)]);
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 84:
#line 919 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 85:
#line 925 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = newNode();
			(yyval)->type = COMPOUND_DATASET;
			(yyval)->tokenString = (char *) calloc(13, sizeof(char));
			strcpy((yyval)->tokenString, "dataset []{}");
			(yyval)->left = (yyvsp[(1) - (7)]);
			(yyval)->right = newNode();
			(yyval)->right->type = DATASET_INFO;
			(yyval)->right->tokenString = (char *) calloc(5, sizeof(char));
			strcpy((yyval)->right->tokenString, "[]{}");
			(yyval)->right->left = (yyvsp[(3) - (7)]);
			(yyval)->right->right = (yyvsp[(6) - (7)]);
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 86:
#line 941 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = newNode();
			(yyval)->type = COMPOUND_DATASET;
			(yyval)->tokenString = (char *) calloc(13, sizeof(char));
			strcpy((yyval)->tokenString, "dataset []{}");
			(yyval)->left = (yyvsp[(1) - (7)]);
			(yyval)->right = newNode();
			(yyval)->right->type = DATASET_INFO;
			(yyval)->right->tokenString = (char *) calloc(5, sizeof(char));
			strcpy((yyval)->right->tokenString, "[]{}");
			(yyval)->right->left = (yyvsp[(6) - (7)]);
			(yyval)->right->right = (yyvsp[(3) - (7)]);
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 87:
#line 957 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = newNode();
			(yyval)->type = COMPOUND_DATASET;
			(yyval)->tokenString = (char *) calloc(13, sizeof(char));
			strcpy((yyval)->tokenString, "dataset []{}");
			(yyval)->left = (yyvsp[(1) - (4)]);
			(yyval)->right = newNode();
			(yyval)->right->type = DATASET_INFO;
			(yyval)->right->tokenString = (char *) calloc(5, sizeof(char));
			strcpy((yyval)->right->tokenString, "[]{}");
			(yyval)->right->left = (yyvsp[(3) - (4)]);
			(yyval)->right->right = 0;
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 88:
#line 973 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = newNode();
			(yyval)->type = COMPOUND_DATASET;
			(yyval)->tokenString = (char *) calloc(13, sizeof(char));
			strcpy((yyval)->tokenString, "dataset []{}");
			(yyval)->left = (yyvsp[(1) - (4)]);
			(yyval)->right = newNode();
			(yyval)->right->type = DATASET_INFO;
			(yyval)->right->tokenString = (char *) calloc(5, sizeof(char));
			strcpy((yyval)->right->tokenString, "[]{}");
			(yyval)->right->left = 0;
			(yyval)->right->right = (yyvsp[(3) - (4)]);
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 89:
#line 989 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 90:
#line 995 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = (yyvsp[(1) - (1)]);
			if(verbose)printf("leaving factor\n");
		;}
    break;

  case 91:
#line 1004 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering argument_list\n");
			(yyval)=(yyvsp[(1) - (3)]);
			(yyval)->sibling=(yyvsp[(3) - (3)]);
			if(verbose)printf("leaving argument_list\n");
		;}
    break;

  case 92:
#line 1011 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering argument_list\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving argument_list\n");
		;}
    break;

  case 93:
#line 1020 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering info_list\n");
			(yyval)=(yyvsp[(1) - (3)]);
			(yyval)->sibling=(yyvsp[(3) - (3)]);
			if(verbose)printf("leaving info_list\n");
		;}
    break;

  case 94:
#line 1027 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering info_list\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving info_list\n");
		;}
    break;

  case 95:
#line 1036 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering info\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving info\n");
		;}
    break;

  case 96:
#line 1042 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering info\n");
			(yyval) = newNode();
			(yyval)->left = 0;
			(yyval)->type = VOID;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");
			if(verbose)printf("leaving info\n");
		;}
    break;

  case 97:
#line 1055 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering coordinate_list\n");
			(yyval)=(yyvsp[(1) - (3)]);
			(yyval)->sibling=(yyvsp[(3) - (3)]);
			if(verbose)printf("leaving coordinate_list\n");
		;}
    break;

  case 98:
#line 1062 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering coordinate_list\n");
			(yyval)=(yyvsp[(1) - (1)]);
			if(verbose)printf("leaving coordinate_list\n");
		;}
    break;

  case 99:
#line 1071 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering coordinate\n");
			(yyval)=(yyvsp[(1) - (3)]);
			(yyval) = newNode();
			(yyval)->left = (yyvsp[(1) - (3)]);
			(yyval)->right = (yyvsp[(3) - (3)]);
			(yyval)->type = COORDINATE;
			(yyval)->tokenString = (char *) calloc(9, sizeof(char));
			strcpy((yyval)->tokenString, "variable");

			if(verbose)printf("leaving coordinate\n");
		;}
    break;

  case 100:
#line 1087 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering id\n");
			(yyval) = newNode();
			(yyval)->type = IDENTIFIER;
			(yyval)->tokenString = (char *) calloc(slength(yytext), sizeof(char));
			strcpy((yyval)->tokenString, yytext);
			if(verbose)printf("leaving id\n");
		;}
    break;

  case 101:
#line 1098 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering num\n");
			(yyval) = newNode();
			(yyval)->type = NUMBER;
			if(type_check(yytext))
			{
				(yyval)->is_double =  1;
			}
			else
			{
				(yyval)->is_double =  0;
			}
			(yyval)->tokenString = (char *) calloc(slength(yytext), sizeof(char));
			strcpy((yyval)->tokenString, yytext);
			(yyval)->number = atoi(yytext);
			(yyval)->float_number =  atof(yytext);
			if(verbose)printf("leaving num\n");
		;}
    break;

  case 102:
#line 1119 "YACC_Grammar_FASPL.c"
    {
			if(verbose)printf("Entering factor\n");
			(yyval) = newNode();
			(yyval)->type = STRING_LITERAL;
			(yyval)->tokenString = (char *) calloc(slength(yytext), sizeof(char));
			strcpy((yyval)->tokenString, &yytext[1]);
			(yyval)->tokenString[slength(yytext)-3]='\0';
			escape_character((yyval)->tokenString);
			if(verbose)printf("leaving factor\n");
		;}
    break;


/* Line 1267 of yacc.c.  */
#line 2906 "YACC_Grammar_FASPL.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


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
      yyerror (YY_("syntax error"));
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
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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


#line 1131 "YACC_Grammar_FASPL.c"

int yyerror(char *message )
{
   printf("%s on line %d\n", message, getLine());
   printf("Current tokenstring is \"%s\"\n", yytext);
   Error = TRUE;
   exit(0);
   
   return 0;
}
int type_check(char * s )
{
   int i;

   i=0;
   while(s[i]!='\0')
   {
		if(s[i]=='.')
		{
			return 1;
		}
		i++;
   }
   return 0;
}
int slength(char * s )
{
   int i;

   i=0;
   while(s[i]!='\0')
   {
		i++;
   }
   i++;
   return i;
}

int escape_character(char * s )
{
   int i;
   int j;
   int k;
   int num;
   char * hex;

   i=0;
   while(s[i]!='\0')
   {
		if(s[i]=='\\')
		{
			if(s[i+1]=='a')
			{
				s[i]='\a';

				j=i+1;
				while(s[j+1]!='\0')
				{
					s[j]=s[j+1];
					j++;
				}
				s[j]='\0';
			}
			else if(s[i+1]=='b')
			{
				s[i]='\b';

				j=i+1;
				while(s[j+1]!='\0')
				{
					s[j]=s[j+1];
					j++;
				}
				s[j]='\0';
			}
			else if(s[i+1]=='f')
			{
				s[i]='\f';

				j=i+1;
				while(s[j+1]!='\0')
				{
					s[j]=s[j+1];
					j++;
				}
				s[j]='\0';
			}
			else if(s[i+1]=='n')
			{
				s[i]='\n';

				j=i+1;
				while(s[j+1]!='\0')
				{
					s[j]=s[j+1];
					j++;
				}
				s[j]='\0';
			}
			else if(s[i+1]=='r')
			{
				s[i]='\r';

				j=i+1;
				while(s[j+1]!='\0')
				{
					s[j]=s[j+1];
					j++;
				}
				s[j]='\0';
			}
			else if(s[i+1]=='t')
			{
				s[i]='\t';

				j=i+1;
				while(s[j+1]!='\0')
				{
					s[j]=s[j+1];
					j++;
				}
				s[j]='\0';
			}
			else if(s[i+1]=='\\')
			{
				s[i]='\\';

				j=i+1;
				while(s[j+1]!='\0')
				{
					s[j]=s[j+1];
					j++;
				}
				s[j]='\0';
			}
			else if(s[i+1]=='\'')
			{
				s[i]='\'';

				j=i+1;
				while(s[j+1]!='\0')
				{
					s[j]=s[j+1];
					j++;
				}
				s[j]='\0';
			}
			else if(s[i+1]=='\"')
			{
				s[i]='\"';

				j=i+1;
				while(s[j+1]!='\0')
				{
					s[j]=s[j+1];
					j++;
				}
				s[j]='\0';
			}
		}
		i++;
   }
   i++;
   return i;
}

TreeNode * newNode(void)
{ 
	TreeNode * root = (TreeNode *) calloc(1, sizeof(TreeNode));
	int i;
	if (root==NULL)
		printf("Out of memory error at line %d\n",getLine());
	else 
	{
		root->left = NULL;
		root->right = NULL;
		root->otherChild = NULL;
		root->sibling = NULL;
		root->lineno = getLine();
		root->type = 0;
		root->tokenString = 0;
	}
/*
stats++;
printf("Node number %d\n", stats);
*/
	return root;
}
void printTree(TreeNode * root, int tab)
{
	int i = 0;
	TreeNode * currentNode = root;	
	if(currentNode)
	{
		printToken(currentNode->type, currentNode->tokenString);
		if(currentNode->otherChild)
		{
			for(i=0; i<tab; i++)
			{
				printf("\t");
			}
			printf("OC:");
			printTree((currentNode->otherChild), tab+1);
		}	
		if(currentNode->left)
		{
			for(i=0; i<tab; i++)
			{
				printf("\t");
			}
			printf("L:");
			printTree((currentNode->left), tab+1);
		}	
		if(currentNode->right)
		{
			for(i=0; i<tab; i++)
			{
				printf("\t");
			}
			printf("R:");
			printTree((currentNode->right), tab+1);
		}	
		if(currentNode->sibling)
		{
			for(i=0; i<tab; i++)
			{
				printf("\t");
			}
			printf("");
			printTree((currentNode->sibling), tab);
		}	
	} 
}
void deleteTree(TreeNode * root, int tab)
{
	int i = 0;
	TreeNode * currentNode = root;	
	if(currentNode)
	{
		if(currentNode->otherChild)
		{
			deleteTree((currentNode->otherChild), tab+1);
		}	
		if(currentNode->left)
		{
			deleteTree((currentNode->left), tab+1);
		}	
		if(currentNode->right)
		{
			deleteTree((currentNode->right), tab+1);
		}	
		if(currentNode->sibling)
		{
			deleteTree((currentNode->sibling), tab);
		}	
		free(currentNode);
	} 
}
/*
int yylex(void)
{
	return getToken();
}
*/
TreeNode * parse()
{
	verbose=0;
	setLine();
	if(!yyparse())
	{
/*
		printf("\n");
		printTree(root, 0);
*/
	}
	else
	{
		yyerror("File ends before expression!");
	}
	return root;
}

/*
int main()
{
	verbose=0;
	setLine();
	if(!yyparse())
	{
		printf("\n");
		printTree(root, 0);
	}
	else
	{
		yyerror("File ends before expression!");
	}
	return 0;
}
*/
