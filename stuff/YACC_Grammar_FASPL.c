%{
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
%}

%token BUFLEN 259
%token MAXTOKENLEN 256
%token ENDFILE 260
%token ERROR 261
%token RETURN 262
%token VOID 263
%token DATASET 264
%token INT 265
%token IDENTIFIER 266
%token NUMBER 267
%token STRING_LITERAL 268
%token ATTRIBUTE_JOIN 269
%token BLOCK_JOIN 270
%token PAR 271
%token AND 272
%token OR 273
%token LT 274
%token LTE 275
%token GT 276
%token GTE 277
%token IE 278
%token NE 279
%token NOT 280
%token COMMENT 281
%token COMPOUND_DATASET 282
%token DATSET_INFO 283
%token IF 284
%token WHILE 285
%token FOR 286
%token DO 287
%token ELSE 288
%token STRING 289
%token DOUBLE 290
%token COORDINATE 291
%token READ 292
%token WRITE 293
%token INPUT 294
%token OUTPUT 295


%start program
%%

program
	: declaration_list
		{ 
			if(verbose)printf("Entering program\n");
			root = $1; 
			if(verbose)printf("Leaving program\n");
		}
	;

declaration_list
	: declaration declaration_list
		{ 
			if(verbose)printf("Entering declaration_list\n");
			$$ = $1; 
			$$->sibling = $2; 
			if(verbose)printf("leaving declaration_list\n");
		}
	| declaration
		{ 
			if(verbose)printf("Entering declaration_list\n");
			$$ = $1; 
			if(verbose)printf("leaving declaration_list\n");
		}
	;

declaration
	: DATASET id '(' parameter_list ')' '{' compound_statement '}'
		{
			if(verbose)printf("Entering declaration\n");
			$$ = newNode();
			$$->type = DATASET;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "function");
			$$->left = newNode();;
			$$->left->type=DATASET;
			$$->left->tokenString = (char *) calloc(8, sizeof(char));
			strcpy($$->left->tokenString, "dataset");
			$$->left->left=$2;
			$$->left->right=$4;
			$$->right = $7;
			if(verbose)printf("leaving declaration\n");
		}
	| DATASET id '(' ')' '{' compound_statement '}'
		{
			if(verbose)printf("Entering declaration\n");
			$$ = newNode();
			$$->type = DATASET;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "function");
			$$->left = newNode();;
			$$->left->type=DATASET;
			$$->left->tokenString = (char *) calloc(8, sizeof(char));
			strcpy($$->left->tokenString, "dataset");
			$$->left->left=$2;
			$$->left->right=0;
			$$->right = $6;
			if(verbose)printf("leaving declaration\n");
		}
	| INT id '(' parameter_list ')' '{' compound_statement '}'
		{
			if(verbose)printf("Entering declaration\n");
			$$ = newNode();
			$$->type = INT;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "function");
			$$->left = newNode();;
			$$->left->type=INT;
			$$->left->tokenString = (char *) calloc(4, sizeof(char));
			strcpy($$->left->tokenString, "int");
			$$->left->left=$2;
			$$->left->right=$4;
			$$->right = $7;
			if(verbose)printf("leaving declaration\n");
		}
	| INT id '(' ')' '{' compound_statement '}'
		{
			if(verbose)printf("Entering declaration\n");
			$$ = newNode();
			$$->type = INT;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "function");
			$$->left = newNode();;
			$$->left->type=INT;
			$$->left->tokenString = (char *) calloc(4, sizeof(char));
			strcpy($$->left->tokenString, "int");
			$$->left->left=$2;
			$$->left->right=0;
			$$->right = $6;
			if(verbose)printf("leaving declaration\n");
		}
	| DOUBLE id '(' parameter_list ')' '{' compound_statement '}'
		{
			if(verbose)printf("Entering declaration\n");
			$$ = newNode();
			$$->type = DOUBLE;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "function");
			$$->left = newNode();;
			$$->left->type=DOUBLE;
			$$->left->tokenString = (char *) calloc(4, sizeof(char));
			strcpy($$->left->tokenString, "double");
			$$->left->left=$2;
			$$->left->right=$4;
			$$->right = $7;
			if(verbose)printf("leaving declaration\n");
		}
	| DOUBLE id '(' ')' '{' compound_statement '}'
		{
			if(verbose)printf("Entering declaration\n");
			$$ = newNode();
			$$->type = DOUBLE;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "function");
			$$->left = newNode();;
			$$->left->type=DOUBLE;
			$$->left->tokenString = (char *) calloc(4, sizeof(char));
			strcpy($$->left->tokenString, "double");
			$$->left->left=$2;
			$$->left->right=0;
			$$->right = $6;
			if(verbose)printf("leaving declaration\n");
		}
	| STRING id '(' parameter_list ')' '{' compound_statement '}'
		{
			if(verbose)printf("Entering declaration\n");
			$$ = newNode();
			$$->type = STRING;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "function");
			$$->left = newNode();;
			$$->left->type=STRING;
			$$->left->tokenString = (char *) calloc(7, sizeof(char));
			strcpy($$->left->tokenString, "string");
			$$->left->left=$2;
			$$->left->right=$4;
			$$->right = $7;
			if(verbose)printf("leaving declaration\n");
		}
	| STRING id '(' ')' '{' compound_statement '}'
		{
			if(verbose)printf("Entering declaration\n");
			$$ = newNode();
			$$->type = STRING;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "function");
			$$->left = newNode();;
			$$->left->type=STRING;
			$$->left->tokenString = (char *) calloc(7, sizeof(char));
			strcpy($$->left->tokenString, "string");
			$$->left->left=$2;
			$$->left->right=0;
			$$->right = $6;
			if(verbose)printf("leaving declaration\n");
		}
	;

parameter_list
	: parameter ',' parameter_list
		{
			if(verbose)printf("Entering parameter_list\n");
			$$=$1;
			$$->sibling=$3;
			if(verbose)printf("leaving parameter_list\n");
		}
	| parameter
		{
			if(verbose)printf("Entering parameter_list\n");
			$$=$1;
			if(verbose)printf("leaving parameter_list\n");
		}
	;

parameter
	: DATASET id
		{
			if(verbose)printf("Entering parameter\n");
			$$ = newNode();
			$$->type = DATASET;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			$$->left = $2;
			if(verbose)printf("leaving parameter\n");
		}
	| INT id
		{
			if(verbose)printf("Entering parameter\n");
			$$ = newNode();
			$$->type = INT;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			$$->left = $2;
			if(verbose)printf("leaving parameter\n");
		}
	| DOUBLE id
		{
			if(verbose)printf("Entering parameter\n");
			$$ = newNode();
			$$->type = DOUBLE;
 			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			$$->left = $2;
			if(verbose)printf("leaving parameter\n");
		}
	| STRING id
		{
			if(verbose)printf("Entering parameter\n");
			$$ = newNode();
			$$->type = STRING;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			$$->left = $2;
			if(verbose)printf("leaving parameter\n");
		}
	| INPUT id
		{
			if(verbose)printf("Entering parameter\n");
			$$ = newNode();
			$$->type = STRING;
			$$->is_file = 1;
			$$->is_input = 1;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			$$->left = $2;
			if(verbose)printf("leaving parameter\n");
		}
	| OUTPUT id
		{
			if(verbose)printf("Entering parameter\n");
			$$ = newNode();
			$$->type = STRING;
			$$->is_file = 1;
			$$->is_input = 0;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			$$->left = $2;
			if(verbose)printf("leaving parameter\n");
		}
	| VOID
		{
			if(verbose)printf("Entering parameter\n");
			$$ = 0;
			if(verbose)printf("leaving parameter\n");
		}
	;

compound_statement
	: variable_list statement_list
		{
			if(verbose)printf("Entering compound_statement\n");
			$$=$1;
			t1=t2=t3=0;
			t1 = $$;
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
			t1->sibling=$2;	
			if(verbose)printf("leaving compound_statement\n");
		}
	| variable_list
		{
			if(verbose)printf("Entering compound_statement\n");
			$$=$1;
			if(verbose)printf("leaving compound_statement\n");
		}
	| statement_list
		{
			if(verbose)printf("Entering compound_statement\n");
			$$=$1;
			if(verbose)printf("leaving compound_statement\n");
		}	
	;

variable_list
	: variable variable_list
		{
			if(verbose)printf("Entering variable_list\n");
			$$=$1;
			$$->sibling=$2;	
			if(verbose)printf("leaving variable_list\n");
		}
	| variable
		{
			if(verbose)printf("Entering variable_list\n");
			$$=$1;
			if(verbose)printf("leaving variable_list\n");
		}	
	;

variable
	: INT id ';'
		{
			if(verbose)printf("Entering variable\n");
			$$ = newNode();
			$$->left = $2;
			$$->type = INT;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			if(verbose)printf("leaving variable\n");
		}
	| DOUBLE id ';'
		{
			if(verbose)printf("Entering variable\n");
			$$ = newNode();
			$$->left = $2;
			$$->type = DOUBLE;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			if(verbose)printf("leaving variable\n");
		}
	| DATASET id ';'
		{
			if(verbose)printf("Entering variable\n");
			$$ = newNode();
			$$->left = $2;
			$$->type = DATASET;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			if(verbose)printf("leaving variable\n");
		}
	| STRING id ';'
		{
			if(verbose)printf("Entering variable\n");
			$$ = newNode();
			$$->left = $2;
			$$->type = STRING;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			if(verbose)printf("leaving variable\n");
		}
	| INPUT id ';'
		{
			if(verbose)printf("Entering parameter\n");
			$$ = newNode();
			$$->type = STRING;
			$$->is_file = 1;
			$$->is_input = 1;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			$$->left = $2;
			if(verbose)printf("leaving parameter\n");
		}
	| OUTPUT id ';'
		{
			if(verbose)printf("Entering parameter\n");
			$$ = newNode();
			$$->type = STRING;
			$$->is_file = 1;
			$$->is_input = 0;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			$$->left = $2;
			if(verbose)printf("leaving parameter\n");
		}
	;

statement_list		
	: statement statement_list
		{
			if(verbose)printf("Entering statement_list\n");
			$$=$1;
			$$->sibling=$2;
			if(verbose)printf("leaving statement_list\n");
		}
	| statement
		{
			if(verbose)printf("Entering statement_list\n");
			$$=$1;
			if(verbose)printf("leaving statement_list\n");
		}
	;

statement
	: return_statement
		{
			if(verbose)printf("Entering statement\n");
			$$=$1;
			if(verbose)printf("leaving statement\n");
		}
	| iteration_statement
		{
			if(verbose)printf("Entering statement\n");
			$$=$1;
			if(verbose)printf("leaving statement\n");
		}
	| selection_statement
		{
			if(verbose)printf("Entering statement\n");
			$$=$1;
			if(verbose)printf("leaving statement\n");
		}
	| '{' compound_statement '}'
		{
			if(verbose)printf("Entering statement\n");
			$$=$2;
			if(verbose)printf("leaving statement\n");
		}
	| '{' '}'
		{
			if(verbose)printf("Entering statement\n");
			$$=$2;
			if(verbose)printf("leaving statement\n");
		}
	| expression_statement
		{
			if(verbose)printf("Entering statement\n");
			$$=$1;
			if(verbose)printf("leaving statement\n");
		}
	;
	
expression_statement
	: expression ';'
		{
			if(verbose)printf("Entering expression_statement\n");
			$$=$1;
			if(verbose)printf("leaving expression_statement\n");
		}
	| ';'
		{
			if(verbose)printf("Entering expression_statement\n");
			$$=0;
			if(verbose)printf("leaving expression_statement\n");
		}
	;

return_statement
	: RETURN expression_statement
		{
			if(verbose)printf("Entering return_statement\n");
			$$ = newNode();
			$$->type = RETURN;
			$$->tokenString = (char *) calloc(7, sizeof(char));
			strcpy($$->tokenString, "return");
			$$->left = $2;
			if(verbose)printf("leaving return_statement\n");
		}
	;

iteration_statement
	: FOR '(' expression ';' expression ';' expression ')' statement
		{
			if(verbose)printf("Entering iteration_statement\n");
			$$ = newNode();
			$$->type = FOR;
			$$->tokenString = (char *) calloc(4, sizeof(char));
			strcpy($$->tokenString, "for");
			$$->left = $3;
			$3->sibling = $5;
			$5->sibling = $7;
			$$->right = $9;
			if(verbose)printf("leaving iteration_statement\n");
		}
	| WHILE '(' expression ')' statement
		{
			if(verbose)printf("Entering iteration_statement\n");
			$$ = newNode();
			$$->type = WHILE;
			$$->tokenString = (char *) calloc(6, sizeof(char));
			strcpy($$->tokenString, "while");
			$$->left = $3;
			$$->right = $5;
			if(verbose)printf("leaving iteration_statement\n");
		}
	| DO statement WHILE '(' expression ')' ';' 
		{
			if(verbose)printf("Entering iteration_statement\n");
			$$ = newNode();
			$$->type = DO;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "do");
			$$->left = $5;
			$$->right = $2;
			if(verbose)printf("leaving iteration_statement\n");
		}
	;

selection_statement
	: IF '(' expression ')' statement
		{
			if(verbose)printf("Entering selection_statement\n");
			$$ = newNode();
			$$->type = IF;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "if");
			$$->left = $3;
			$$->right = $5;
			if(verbose)printf("leaving selection_statement\n");
		}
	| IF '(' expression ')' statement ELSE statement
		{
			if(verbose)printf("Entering selection_statement\n");
			$$ = newNode();
			$$->type = IF;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "if");
			$$->left = $3;
			$$->right = $5;
			$$->otherChild = $7;
			if(verbose)printf("leaving selection_statement\n");
		}
	;

expression 
	: write_expression
		{
			if(verbose)printf("Entering expression\n");
			$$ = $1;
			if(verbose)printf("leaving expression\n");
		}
	| read_expression
		{
			if(verbose)printf("Entering expression\n");
			$$ = $1;
			if(verbose)printf("leaving expression\n");
		}
	| assignment_expression
		{
			if(verbose)printf("Entering expression\n");
			$$=$1;
			if(verbose)printf("leaving expression\n");
		}
	; 

read_expression 
	:  read_expression READ id
		{
			if(verbose)printf("Entering read_expression\n");
			$$ = newNode();
			$$->left = $3;
			$$->type = READ;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, ">>");
			$$->right = $1;
			if(verbose)printf("leaving read_expression\n");
		}
	| id
		{
			if(verbose)printf("Entering read_expression\n");
			$$ = $1;
			if(verbose)printf("leaving read_expression\n");
		}
	;

write_expression 
	:  write_expression WRITE assignment_expression
		{
			if(verbose)printf("Entering write_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = WRITE;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "<<");
			$$->right = $3;
			if(verbose)printf("leaving write_expression\n");
		}
	| id
		{
			if(verbose)printf("Entering write_expression\n");
			$$ = $1;
			if(verbose)printf("leaving write_expression\n");
		}
	;

assignment_expression 
	: id '=' assignment_expression
		{
			if(verbose)printf("Entering assignment_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = '=';
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, "=");
			$$->right = $3;
			if(verbose)printf("leaving assignment_expression\n");
		}
	| simple_expression
		{
			if(verbose)printf("Entering assignment_expression\n");
			$$=$1;
			if(verbose)printf("leaving assignment_expression\n");
		}
	; 

simple_expression
	: add_expression NE simple_expression
		{
			if(verbose)printf("Entering simple_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = NE;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "!=");
			$$->right = $3;
			if(verbose)printf("leaving simple_expression\n");
		}
	| add_expression IE simple_expression
		{
			if(verbose)printf("Entering simple_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = IE;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "==");
			$$->right = $3;
			if(verbose)printf("leaving simple_expression\n");
		}
	| add_expression LTE simple_expression
		{
			if(verbose)printf("Entering simple_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = LTE;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "<=");
			$$->right = $3;
			if(verbose)printf("leaving simple_expression\n");
		}
	| add_expression GTE simple_expression
		{
			if(verbose)printf("Entering simple_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = GTE;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, ">=");
			$$->right = $3;
			if(verbose)printf("leaving simple_expression\n");
		}
	| add_expression LT simple_expression
		{
			if(verbose)printf("Entering simple_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = LT;
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, "<");
			$$->right = $3;
			if(verbose)printf("leaving simple_expression\n");
		}
	| add_expression GT simple_expression
		{
			if(verbose)printf("Entering simple_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = GT;
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, ">");
			$$->right = $3;
			if(verbose)printf("leaving simple_expression\n");
		}
	| add_expression
		{
			if(verbose)printf("Entering simple_expression\n");
			$$ = $1;
			if(verbose)printf("leaving simple_expression\n");
		}
	;
add_expression
	: mul_expression '+' add_expression
		{
			if(verbose)printf("Entering add_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = '+';
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, "+");
			$$->right = $3;
			if(verbose)printf("leaving add_expression\n");
		}
	| mul_expression '-' add_expression
		{
			if(verbose)printf("Entering add_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = '-';
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, "-");
			$$->right = $3;
			if(verbose)printf("leaving add_expression\n");
		}
	| mul_expression
		{
			if(verbose)printf("Entering add_expression\n");
			$$ = $1;
			if(verbose)printf("leaving add_expression\n");
		}
	;
mul_expression
	: mod_expression '*' mul_expression
		{
			if(verbose)printf("Entering mul_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = '*';
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, "*");
			$$->right = $3;
			if(verbose)printf("leaving mul_expression\n");
		}
	| mod_expression '/' mul_expression
		{
			if(verbose)printf("Entering mul_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = '/';
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, "/");
			$$->right = $3;
			if(verbose)printf("leaving mul_expression\n");
		}
	| mod_expression
		{
			if(verbose)printf("Entering mul_expression\n");
			$$ = $1;
			if(verbose)printf("leaving mul_expression\n");
		}
	;
mod_expression
	: join_expression '%' mod_expression
		{
			if(verbose)printf("Entering mod_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = '%';
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, "%");
			$$->right = $3;
			if(verbose)printf("leaving mod_expression\n");
		}
	| join_expression
		{
			if(verbose)printf("Entering mod_expression\n");
			$$ = $1;
			if(verbose)printf("leaving mod_expression\n");
		}
	;
join_expression
	: term ATTRIBUTE_JOIN join_expression
		{
			if(verbose)printf("Entering join_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = ATTRIBUTE_JOIN;
			$$->tokenString = (char *) calloc(4, sizeof(char));
			strcpy($$->tokenString, "[+]");
			$$->right = $3;
			if(verbose)printf("leaving join_expression\n");
		}
	| term BLOCK_JOIN join_expression
		{
			if(verbose)printf("Entering join_expression\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = BLOCK_JOIN;
			$$->tokenString = (char *) calloc(4, sizeof(char));
			strcpy($$->tokenString, "{+}");
			$$->right = $3;
			if(verbose)printf("leaving join_expression\n");
		}
	| term
		{
			if(verbose)printf("Entering join_expression\n");
			$$ = $1;
			if(verbose)printf("leaving join_expression\n");
		}
	;

term
	: factor AND term
		{
			if(verbose)printf("Entering term\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = AND;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "&&");
			$$->right = $3;
			if(verbose)printf("leaving term\n");
		}
	| factor OR term
		{
			if(verbose)printf("Entering term\n");
			$$ = newNode();
			$$->left = $1;
			$$->type = OR;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "||");
			$$->right = $3;
			if(verbose)printf("leaving term\n");
		}
	| '-' term
		{
			if(verbose)printf("Entering term\n");
			$$ = newNode();
			$$->type = '-';
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, "-");
			$$->right = $2;
			if(verbose)printf("leaving term\n");
		}
	| NOT term
		{
			if(verbose)printf("Entering term\n");
			$$ = newNode();
			$$->type = NOT;
			$$->tokenString = (char *) calloc(2, sizeof(char));
			strcpy($$->tokenString, "!");
			$$->right = $2;
			if(verbose)printf("leaving term\n");
		}
	| factor
		{
			if(verbose)printf("Entering term\n");
			$$ = $1;
			if(verbose)printf("leaving term\n");
		}
	;

factor
	: '(' expression ')'
		{
			if(verbose)printf("Entering factor\n");
			$$=$2;
			if(verbose)printf("leaving factor\n");
		}
	| id '(' ')'
		{
			if(verbose)printf("Entering factor\n");
			$$ = newNode();
			$$->type = PAR;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "()");
			$$->left = $1;
			if(verbose)printf("leaving factor\n");
		}
	| id '(' argument_list ')'
		{
			if(verbose)printf("Entering factor\n");
			$$ = newNode();
			$$->type = PAR;
			$$->tokenString = (char *) calloc(3, sizeof(char));
			strcpy($$->tokenString, "()");
			$$->left = $1;
			$$->right = $3;
			if(verbose)printf("leaving factor\n");
		}
	| id
		{
			if(verbose)printf("Entering factor\n");
			$$ = $1;
			if(verbose)printf("leaving factor\n");
		}
	| id '[' info_list ']' '{' coordinate_list '}'
		{
			if(verbose)printf("Entering factor\n");
			$$ = newNode();
			$$->type = COMPOUND_DATASET;
			$$->tokenString = (char *) calloc(13, sizeof(char));
			strcpy($$->tokenString, "dataset []{}");
			$$->left = $1;
			$$->right = newNode();
			$$->right->type = DATASET_INFO;
			$$->right->tokenString = (char *) calloc(5, sizeof(char));
			strcpy($$->right->tokenString, "[]{}");
			$$->right->left = $3;
			$$->right->right = $6;
			if(verbose)printf("leaving factor\n");
		}
	| id '{' coordinate_list '}' '[' info_list ']' 
		{
			if(verbose)printf("Entering factor\n");
			$$ = newNode();
			$$->type = COMPOUND_DATASET;
			$$->tokenString = (char *) calloc(13, sizeof(char));
			strcpy($$->tokenString, "dataset []{}");
			$$->left = $1;
			$$->right = newNode();
			$$->right->type = DATASET_INFO;
			$$->right->tokenString = (char *) calloc(5, sizeof(char));
			strcpy($$->right->tokenString, "[]{}");
			$$->right->left = $6;
			$$->right->right = $3;
			if(verbose)printf("leaving factor\n");
		}
	| id '[' info_list ']'
		{
			if(verbose)printf("Entering factor\n");
			$$ = newNode();
			$$->type = COMPOUND_DATASET;
			$$->tokenString = (char *) calloc(13, sizeof(char));
			strcpy($$->tokenString, "dataset []{}");
			$$->left = $1;
			$$->right = newNode();
			$$->right->type = DATASET_INFO;
			$$->right->tokenString = (char *) calloc(5, sizeof(char));
			strcpy($$->right->tokenString, "[]{}");
			$$->right->left = $3;
			$$->right->right = 0;
			if(verbose)printf("leaving factor\n");
		}
	| id '{' coordinate_list '}'
		{
			if(verbose)printf("Entering factor\n");
			$$ = newNode();
			$$->type = COMPOUND_DATASET;
			$$->tokenString = (char *) calloc(13, sizeof(char));
			strcpy($$->tokenString, "dataset []{}");
			$$->left = $1;
			$$->right = newNode();
			$$->right->type = DATASET_INFO;
			$$->right->tokenString = (char *) calloc(5, sizeof(char));
			strcpy($$->right->tokenString, "[]{}");
			$$->right->left = 0;
			$$->right->right = $3;
			if(verbose)printf("leaving factor\n");
		}
	| string
		{
			if(verbose)printf("Entering factor\n");
			$$ = $1;
			if(verbose)printf("leaving factor\n");
		}
	| num
		{
			if(verbose)printf("Entering factor\n");
			$$ = $1;
			if(verbose)printf("leaving factor\n");
		}
	;

argument_list
	:  expression ',' argument_list
		{
			if(verbose)printf("Entering argument_list\n");
			$$=$1;
			$$->sibling=$3;
			if(verbose)printf("leaving argument_list\n");
		}
	| expression
		{
			if(verbose)printf("Entering argument_list\n");
			$$=$1;
			if(verbose)printf("leaving argument_list\n");
		}
	;

info_list
	: info ',' info_list
		{
			if(verbose)printf("Entering info_list\n");
			$$=$1;
			$$->sibling=$3;
			if(verbose)printf("leaving info_list\n");
		}
	| info
		{
			if(verbose)printf("Entering info_list\n");
			$$=$1;
			if(verbose)printf("leaving info_list\n");
		}
	;

info
	: expression
		{
			if(verbose)printf("Entering info\n");
			$$=$1;
			if(verbose)printf("leaving info\n");
		}
	| VOID
		{
			if(verbose)printf("Entering info\n");
			$$ = newNode();
			$$->left = 0;
			$$->type = VOID;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");
			if(verbose)printf("leaving info\n");
		}
	;

coordinate_list
	: coordinate ',' coordinate_list
		{
			if(verbose)printf("Entering coordinate_list\n");
			$$=$1;
			$$->sibling=$3;
			if(verbose)printf("leaving coordinate_list\n");
		}
	| coordinate
		{
			if(verbose)printf("Entering coordinate_list\n");
			$$=$1;
			if(verbose)printf("leaving coordinate_list\n");
		}
	;

coordinate
	: expression ':' expression
		{
			if(verbose)printf("Entering coordinate\n");
			$$=$1;
			$$ = newNode();
			$$->left = $1;
			$$->right = $3;
			$$->type = COORDINATE;
			$$->tokenString = (char *) calloc(9, sizeof(char));
			strcpy($$->tokenString, "variable");

			if(verbose)printf("leaving coordinate\n");
		}
	;

id
	: IDENTIFIER
		{
			if(verbose)printf("Entering id\n");
			$$ = newNode();
			$$->type = IDENTIFIER;
			$$->tokenString = (char *) calloc(slength(yytext), sizeof(char));
			strcpy($$->tokenString, yytext);
			if(verbose)printf("leaving id\n");
		}
	;
num
	: NUMBER
		{
			if(verbose)printf("Entering num\n");
			$$ = newNode();
			$$->type = NUMBER;
			if(type_check(yytext))
			{
				$$->is_double =  1;
			}
			else
			{
				$$->is_double =  0;
			}
			$$->tokenString = (char *) calloc(slength(yytext), sizeof(char));
			strcpy($$->tokenString, yytext);
			$$->number = atoi(yytext);
			$$->float_number =  atof(yytext);
			if(verbose)printf("leaving num\n");
		}
	;
string
	: STRING_LITERAL
		{
			if(verbose)printf("Entering factor\n");
			$$ = newNode();
			$$->type = STRING_LITERAL;
			$$->tokenString = (char *) calloc(slength(yytext), sizeof(char));
			strcpy($$->tokenString, &yytext[1]);
			$$->tokenString[slength(yytext)-3]='\0';
			escape_character($$->tokenString);
			if(verbose)printf("leaving factor\n");
		}
	;

%%
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