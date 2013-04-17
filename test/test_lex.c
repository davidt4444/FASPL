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
int lineno;
void comment();
void line_comment();

%}


%%

"/*"			{ comment();}
"//"			{ line_comment(); /*return(COMMENT);*/}

"return"		{ ;  }
"void"			{ ;  }
"int"			{ ;  }
"double"			{ ;  }
"dataset"		{ ;  }
"string"		{ ;  }
"input"		{ ;  }
"output"		{ ;  }

({D}*|{D}*{P}{D}*)		{ ;  }
{L}({L}|{D})*		{ ;  }

\"(\\.|[^\\"])*\"	{ ; ECHO; }

">>"			{ ;  }
"<<"			{ ;  }
"[+]"			{ ;  }
"{+}"			{ ;  }
"&&"			{ ;  }
"||"			{ ;  }
"<"				{ ;  }
"<="				{ ;  }
">"				{ ;  }
">="				{ ;  }
"=="				{ ;  }
"!="				{ ;  }
"!"				{ ;  }
":"			{ ;  }
";"			{ ;  }
"{"			{ ;  }
"}"			{ ;  }
","			{ ;  }
"="			{ ;  }
"+"			{ ;  }
"-"			{ ;  }
"*"			{ ;  }
"/"			{ ;  }
"%"			{ ;  }
"("			{ ;  }
")"			{ ;  }
"["			{ ;  }
"]"			{ ;  }

[ \t\v\f]		{ ; }
[ \n\r]		{ lineno++; }
.			{ ;}
<<EOF>>		{return EOF;}

%%

int yywrap()
{
	return(1);
}

void comment()
{
	char c;
	char c1;

	while(1){
		c = input();
		while (c != '*' && c != 0)
		{
	
			if(c == '\n' || c == '\r' )
			{
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
			holder = yylex();
		}while( holder!= EOF && holder!= -1);
		fclose(input);
		printf("%d\n", lineno);
	}
	

	return 0;
}

