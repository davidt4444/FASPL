/*  
Comments can be placed anywhere white space can appear (that is, comments cannot be
placed within tokens) and may include more than one line.  Comments may
not be nested.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * preprocessor_total_file;
char preprocessor_buffer[256];
char * preprocessor_temp_filename;
int preprocessor_appendage(char * filename, int length);
int preprocessor_body(char * filename);


/* 
	BUFLEN = length of the input buffer for
	source code lines 
*/
#define BUFLEN 259

/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN 256
#define MAXRESERVED 13
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

/* book-keeping tokens */
#define ENDFILE 260
#define ERROR 261

/* reserved words */
#define RETURN 262
#define VOID 263
#define DATASET 264
#define INT 265

/* multicharacter tokens */
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
#define DATASET_INFO 283

/* more reserved words */
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
#define WHITESPACE 296



/* states in scanner DFA */
typedef enum
{ 
	START,
	INASSIGN,
	INCOMMENT,
	INNUM,
	INID,
	DONE 
}StateType;

/* lookup table of reserved words */
static struct
{ 
	char* str;
	int tok;
} reservedWords[MAXRESERVED]= {
		{"return", RETURN},
		{"void", VOID},
		{"dataset", DATASET},
		{"int", INT},
		{"double", DOUBLE},
		{"string", STRING},
		{"input", INPUT},
		{"output", OUTPUT},
		{"if", IF},
		{"else", ELSE},
		{"while", WHILE},
		{"for", FOR},
		{"do", DO}
};

typedef struct treeNode
{ 
	struct treeNode * left;
	struct treeNode * right;
	struct treeNode * otherChild;
	struct treeNode * sibling;
	int lineno;
	int type;
	int number;
	double float_number;
	char * tokenString;
	int is_double;
	int is_file;
	int is_input;
} TreeNode;

typedef enum
{ 
	TYPE_VOID,
	TYPE_INT,
	TYPE_DOUBLE,
	TYPE_STRING,
	TYPE_DATASET
}Type;

typedef struct symbol
{
	struct symbol * next;
	char * name;
	int scope;
	Type symbolType;
	int function;
	int lineno;
	int offset;
	double float_num;
	int num;
	struct symbol * param_list;
	TreeNode * instructions;
	TreeNode * value;
	int is_double;
	int is_file;
	int is_input;
	FILE * stream;
} Symbol;

typedef struct componentlist
{
	int bounds_count;
	int maps_count;
	char * bounds;
	char * maps;
} ComponentList;


int stats;
int return_flag;

/* 
lexeme of identifier or reserved word 
*/
/*
int yylex(void);
char * yytext;
int FASPLlex(void);
char * tokenString;
*/
char tokenString[MAXTOKENLEN+1];

static char lineBuf[BUFLEN]; /* holds the current line */
static int linepos = 0; /* current position in LineBuf */
static int bufsize = 0; /* current size of buffer string */
static int EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */


static int currentToken;
static int token;
/* 
	getNextChar fetches the next non-blank character
	from lineBuf, reading in a new line if lineBuf is
	exhausted 
*/
static char getNextChar(void);

/* 
	ungetNextChar backtracks one character
	in lineBuf 
*/
static void ungetNextChar(void);

/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static int reservedLookup (char * s);

void printToken( int token, const char* tokenString );

/****************************************/
/* the primary function of the scanner  */
/****************************************/
/* function getToken returns the 
 * next token in source file
 */
 
int getLine(void);
void setLine(void);
int getToken(void);

/* Error = TRUE prevents further passes if an error occurs */
int Error; 

TreeNode * t1;
TreeNode * t2;
TreeNode * t3;

Symbol * symbolTable[26];
char * currentIdentifier;
int currentLine;
int main_found;
int return_dataset;
int return_int;
int return_double;
int return_string;

int opcounter;



int position_counter;
int slength(char * s );

int column;
void count();
int check_type ();
void printToken( int token, const char* tokenString );
int getLine(void);
void setLine(void);




int yyerror(char *message );
TreeNode * newNode(void);
void printTree(TreeNode * root, int tab);
void deleteTree(TreeNode * root, int tab);
TreeNode * parse();



void scopeError();
void voidMainError();
void intMainError();
void mainNotFoundError();
void mainParamNotVoid();
void mainNotLastError();
void mainDeclaredMultipleTimes();
void semanticIntError(char * message);
void semanticSymbolError(char * message);
void returnTypeMismatchError(int errorLineNumber);
void returnMissingError(char * message);
Symbol * newSymbol(char * name, int scope, Type symbolType, int function, int lineno);
Symbol * lookup(Symbol * s);
void insertSymbol(Symbol * s);
void popSymbolsByScope(int scope);
void variables(TreeNode * root, int tab);
int subDataset(TreeNode * root, int tab);
int subInt(TreeNode * root, int tab);
void block(TreeNode * root, int tab);
void function_call(TreeNode * root, int tab);
void traverse(TreeNode * root, int tab);
void printTableRow(Symbol * s1);
void deleteTableRow(Symbol * s1);
TreeNode * analyze();
Symbol * get_symbolTable(int val);
void set_symbolTable(int val, Symbol * symbol_row);
void set_main_found(int val);
int get_main_found();




Symbol * interpreter_newSymbol(char * name, int scope, Type symbolType, int function, int lineno);
Symbol * interpreter_lookup(Symbol * s);
void interpreter_insertSymbol(Symbol * s);
void interpreter_popSymbolsByScope(int scope);
TreeNode * interpreter_variables(TreeNode * root, int tab);
TreeNode * interpreter_datasetList_label(TreeNode * root, int tab);
TreeNode * interpreter_datasetList_coordinate(TreeNode * root, int tab);
TreeNode * interpreter_subDataset(TreeNode * root, int tab);
TreeNode * interpreter_subInt(TreeNode * root, int tab);
TreeNode * interpreter_blockDataset(TreeNode * root, int tab);
TreeNode * interpreter_blockInt(TreeNode * root, int tab);
TreeNode * interpreter_function_call(TreeNode * root, int tab);
TreeNode * interpreter_traverse(TreeNode * root, int tab);
void interpreter_printTableRow(Symbol * s1);
void interpreter_deleteTableRow(Symbol * s1);
TreeNode * interpreter_analyze();
void interpreter_set_main_found(int val);
int interpreter_get_main_found();

int verbose1;
int currentLine;
int currentCodeLine;
int notFirst;
int main_found;
int return_int;
char instruction[55];
FILE * output;
FILE * actual_out;

ComponentList * gen_XFDLComponentList(char * file_path, int tab, FILE * shortcut);
char * gen_datasetList_label(TreeNode * root, int tab, FILE * shortcut);
char * gen_datasetList_coordinate(TreeNode * root, int tab, FILE * shortcut);
ComponentList * gen_subDataset(TreeNode * root, int tab, FILE * shortcut);


