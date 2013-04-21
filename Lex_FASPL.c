P			[.]
D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include <stdio.h>
#include <string.h>
#include "header.h"

void comment();
void line_comment();
void count();
int lineno;

%}


%%

"//"			{ line_comment();  }
"/*"			{ comment();  }


"return"		{ return RETURN; }
"void"			{ return VOID; }
"int"			{ return INT; }
"double"			{ return DOUBLE; }
"dataset"		{ return DATASET; }
"string"		{ return STRING; }
"input"		{ return INPUT; }
"output"		{ return OUTPUT; }

({D}*|{D}*{P}{D}*)		{ return NUMBER; }
{L}({L}|{D})*		{ return check_type(); }

\"(\\.|[^\\"])*\"	{ return STRING_LITERAL; }

">>"			{ return READ; }
"<<"			{ return WRITE; }
"[+]"			{ return ATTRIBUTE_JOIN; }
"{+}"			{ return BLOCK_JOIN; }
"&&"			{ return AND; }
"||"			{ return OR; }
"<"				{ return LT; }
"<="				{ return LTE; }
">"				{ return GT; }
">="				{ return GTE; }
"=="				{ return IE; }
"!="				{ return NE; }
"!"				{ return NOT; }
":"			{ return ':'; }
";"			{ return ';'; }
"{"			{ return '{'; }
"}"			{ return '}'; }
","			{ return ','; }
"="			{ return '='; }
"+"			{ return '+'; }
"-"			{ return '-'; }
"*"			{ return '*'; }
"/"			{ return '/'; }
"%"			{ return '%'; }
"("			{ return '('; }
")"			{ return ')'; }
"["			{ return '['; }
"]"			{ return ']'; }

[\n\r]		{ lineno++; }
[ \t\v\f]		{  ; }
.			{ return yytext[0];}
<<EOF>>		{return EOF;}

%%

int yywrap()
{
	return 1;
}


void comment()
{
	char c;
	char c1;

	while(1){
		c = input();
		while (c != '*' && c != 0)
		{
	
			if(c=='\n' || c=='\r'){
				lineno++;
			}
			c = input();
		}
	
		if ((c1 = input()) == '/' || c == 0)
		{
			break;
		}
		else
		{
			unput(c1);
		}
	}

	if (c != 0)
	{
/*
		putchar(c1);
*/
	}
}

void line_comment()
{
	char c, c1;

	while ((c = input()) != '\n' && c != '\r' && c != 0)
	{
	}
	lineno++;
	if (c != 0)
	{
/*
		putchar(c1);
*/
	}
}


int check_type ()
{ 
	int i;
	for (i=0;i<MAXRESERVED;i++)
		if (!strcmp(yytext,reservedWords[i].str))
			return reservedWords[i].tok;
	return IDENTIFIER;
}

void printToken( int token, const char* tokenString )
{ 
	switch (token)
	{ 
		case RETURN:
		case VOID:
		case DATASET:
		case INT:
		case STRING:
		case IF:
		case WHILE:
		case FOR:
/*
			fprintf(listing,"reserved word: %s\n",tokenString);
*/
			printf("reserved word \t %s\n",tokenString);
			break;
		case COMMENT: 
			break;
		case '=':
			printf("special symbol \t =\n"); 
			break;
		case READ:
			printf("special symbol \t >>\n"); 
			break;
		case WRITE:
			printf("special symbol \t <<\n"); 
			break;
		case ATTRIBUTE_JOIN:
			printf("special symbol \t [+]\n"); 
			break;
		case BLOCK_JOIN:
			printf("special symbol \t {+}\n"); 
			break;
		case AND:
			printf("special symbol \t &&\n"); 
			break;
		case OR:
			printf("special symbol \t ||\n"); 
			break;
		case LT:
			printf("special symbol \t <\n"); 
			break;
		case LTE:
			printf("special symbol \t <=\n"); 
			break;
		case GT:
			printf("special symbol \t >\n"); 
			break;
		case GTE:
			printf("special symbol \t >=\n"); 
			break;
		case IE:
			printf("special symbol \t ==\n"); 
			break;
		case NE:
			printf("special symbol \t !=\n"); 
			break;
		case '(':
			printf("special symbol \t (\n"); 
			break;
		case ')':
			printf("special symbol \t )\n"); 
			break;
		case ';':
			printf("special symbol \t ;\n"); 
			break;
		case ',':
			printf("special symbol \t ,\n"); 
			break;
		case '{':
			printf("special symbol \t {\n"); 
			break;
		case '}':
			printf("special symbol \t }\n"); 
			break;

		case ENDFILE: 
			printf("EOF\n"); 
			break;
		case STRING_LITERAL:
			printf("string \t\t %s\n",tokenString);
			break;
		case IDENTIFIER:
			printf("identifier \t\t %s\n",tokenString);
			break;
		case NUMBER:
			printf("number \t\t %s\n",tokenString);
			break;
		case ERROR:
			printf("ERROR: \t %s\n",tokenString);
			break;
		default: 
			printf("special symbol \t %s\n", tokenString);
	}
}

int getLine(void)
{
	return lineno;
}
void setLine(void)
{
	lineno=1;
}

/*
int getToken()
{ 
	int i;
	static int firstTime = TRUE;
	int currentToken;
	if (firstTime)
	{ 
		firstTime = FALSE;
		lineno++;
		yyin = stdin;
		yyout = stdout;
	}

	yytext = (char *) calloc(slength(FASPLtext), sizeof(char));
	strcpy(yytext, FASPLtext);

	tokenString = FASPLtext;

	currentToken = FASPLlex();

	if(currentToken == COMMENT || currentToken == WHITESPACE)
	{
		return yylex();
	}

	return currentToken;
}

int main(int argc, char *argv[], char *envp[])
{
	int holder;
	int i;
	FILE * input;
	
	for(i=1;i<argc;i++)
	{
		printf("%s:\n", argv[i]);
		input = fopen(argv[i], "r");
		stdin = input;
		lineno=1;

		do 
		{
			holder = getToken();
		}while( holder != ERROR && holder!= ENDFILE && holder!= -1);
		fclose(input);
		printf("%d\n", lineno);
	}
	

	return 0;
}
*/

